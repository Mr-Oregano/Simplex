
// Precompiled Header
#include "sxpch.h"
//

#include "VertexBuffer.h"

VertexBufferLayout::VertexBufferLayout(std::initializer_list<VertexAttribute> attributes)
    : m_Attributes(attributes), m_Stride(0)
{
    m_Stride = CalcStride();
}

int VertexBufferLayout::GetStride() const
{
    return m_Stride;
}

const std::vector<VertexAttribute> &VertexBufferLayout::GetAttributes() const
{
    return m_Attributes;
}

int VertexBufferLayout::CalcStride()
{
    int stride = 0;
    
    for (const auto &attribute : m_Attributes)
        stride += SXG::TypeSize(attribute.type);

    return stride;
}