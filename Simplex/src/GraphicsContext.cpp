
// Precompiled Header
#include "sxpch.h"
//

#include "GraphicsContext.h"

#include <Native/OpenGL/OpenGLContext.h>

#include <Simplex.h>

Ref<GraphicsContext> GraphicsContext::Create(GraphicsConfig config)
{
    switch (config.desiredAPI)
    {
        case RendererAPI::SXG_OPENGL: return CreateRef<OpenGLContext>();
    }

    LOG_CRITICAL("The desired graphics API is currently not supported");
    return nullptr;
}
