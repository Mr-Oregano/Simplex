#pragma once

#include <Simplex.h>

#include <vector>
#include <cstdint>

struct ResourceHandle
{
	template<typename T>
	friend class ResourcePool;

public:
	[[nodiscard]] bool IsValid() const { return magic != 0; }
	operator bool() const { return IsValid(); }

protected:
	std::uint32_t index : 16 { 0 };
	std::uint32_t magic : 16 { 0 };
};

// TODO: Use generation counting instead of magic number for resource validation.
// TODO: May want to cap the amount of allocations or use a fixed-size array instead.

template<typename T>
class ResourcePool
{
public:
	ResourcePool();

	const T &GetConst(ResourceHandle handle) const { return GetSlotConst(handle).data; }
	T &Get(ResourceHandle handle) { return GetSlot(handle).data; }

	ResourceHandle Emplace(T &&t);
	void Release(ResourceHandle handle);

private:
	struct Slot
	{
		T data;
		bool active = false;
		std::uint32_t magic : 16 { 0 };
	};

private:
	const Slot &GetSlotConst(ResourceHandle handle) const;
	Slot &GetSlot(ResourceHandle handle);
	std::uint32_t FindNextVacantIndex();

private:
	std::uint32_t m_NextVacantIndex = 0;
	std::uint32_t m_Counter = 0;

	std::vector<Slot> m_Slots;
};

template<typename T>
inline ResourcePool<T>::ResourcePool()
{
	m_Slots.resize(1);
}

template<typename T>
inline typename ResourcePool<T>::Slot &ResourcePool<T>::GetSlot(ResourceHandle handle)
{
	// NOTE: We const_cast here to avoid code duplication, it looks quite gorgeous doesn't it :)
	//
	const Slot &s = const_cast<ResourcePool<T>&>(*this).GetSlotConst(handle);

	return const_cast<Slot &>(s);
}

template<typename T>
inline const typename ResourcePool<T>::Slot &ResourcePool<T>::GetSlotConst(ResourceHandle handle) const
{
	ASSERT_CRITICAL(handle, "Handle to resource is null!");

	const Slot &s = m_Slots[handle.index];

	ASSERT_CRITICAL(s.active && s.magic == handle.magic, "Attempting to use handle to a deleted resource.");

	return s;
}

template<typename T>
inline ResourceHandle ResourcePool<T>::Emplace(T &&t)
{
	++m_Counter;
	m_Counter %= 0xFFFF;

	ResourceHandle handle{};
	handle.index = m_NextVacantIndex;
	handle.magic = m_Counter;

	ASSERT_CRITICAL(handle.index < m_Slots.size(), "Not enough slots in pool!");

	m_Slots[handle.index].data = t;
	m_Slots[handle.index].active = true;
	m_Slots[handle.index].magic = handle.magic;

	m_NextVacantIndex = FindNextVacantIndex();
	return handle;
}

template<typename T>
inline void ResourcePool<T>::Release(ResourceHandle handle)
{
	Slot &s = GetSlot(handle);
	s.active = false;

	if (handle.index < m_NextVacantIndex)
		m_NextVacantIndex = handle.index;
}

template<typename T>
inline std::uint32_t ResourcePool<T>::FindNextVacantIndex()
{
	for (int i = 0; i < m_Slots.size(); ++i)
		if (!m_Slots[i].active)
			return i;

	LOG_INFO("Resource pool requesting more memory.");

	std::size_t next = m_Slots.size();
	m_Slots.resize(m_Slots.size() * 2u);
	return (std::uint32_t)next;
}