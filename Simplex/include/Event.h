#pragma once

#include <functional>

enum class EventType
{
	KeyUp,
	KeyDown,

	MouseButtonUp,
	MouseButtonDown,
	MouseMove,
	MouseDrag,
	MouseScroll,

	WindowClose,
	WindowMaximize,
	WindowResize,
	WindowMove,

	InputChar
};

struct Event
{
	virtual EventType Type() const = 0;

	template<typename T>
	void Dispatch(std::function<void(T)> callback)
	{
		if (Type() == T::StaticType())
			callback(static_cast<T&>(*this));
	}
};


struct KeyEvent : public Event
{
	int keyCode;
};

struct KeyDown : public KeyEvent
{
	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::KeyDown; }
};

struct KeyUp : public KeyEvent
{
	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::KeyUp; }
};


struct MouseEvent : public Event
{
	double x;
	double y;
};

struct MouseButtonDown : public MouseEvent
{
	int mouseButton;

	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::MouseButtonDown; }
};

struct MouseButtonUp : public MouseEvent
{
	int mouseButton;

	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::MouseButtonUp; }
};

struct MouseMove : public MouseEvent
{
	double dx;
	double dy;
	double lastX;
	double lastY;

	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::MouseMove; }
};

struct MouseDrag : public MouseEvent
{
	int mouseButton;

	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::MouseDrag; }
};

struct MouseScroll : public MouseEvent
{
	double velocityX;
	double velocityY;

	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::MouseScroll; }
};


struct SystemEvent : public Event
{

};

struct WindowClose : public SystemEvent
{
	virtual EventType Type() const override { return StaticType(); }
	static EventType StaticType() { return EventType::WindowClose; }
};

