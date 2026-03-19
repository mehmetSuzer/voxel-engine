
#include "error.h"
#include "graphics.h"

static GraphicsState graphicsState = {
    .viewport = {
        .x      = 0, 
        .y      = 0, 
        .width  = 0, 
        .height = 0,
    },
    .depthTest = {
        .enabled = 0,
        .writeEnabled = 1,
        .func = TestFuncLess,
    },
    .stencilTest = {
        .enabled = 0,
        .func = TestFuncAlways,
        .reference = 0,
        .mask = 0xFFu,
        .stencilFail = StencilOpKeep,
        .depthFail   = StencilOpKeep,
        .depthPass   = StencilOpKeep,
    },
    .scissorTest = {
        .enabled = 0,
        .rect = {
            .x      = 0,
            .y      = 0,
            .width  = 0,
            .height = 0,
        },
    },
    .colourBlend = {
        .enabled = 0,
        .srcFactor = BlendFactorOne,
        .dstFactor = BlendFactorZero,
        .equation = BlendEquationAdd,
    },
    .faceCull = {
        .enabled = 0,
        .cullFace = FaceBack,
        .frontFace = FrontFaceCCW,
    },
    .polygonMode = {
        .face = FaceBoth,
        .mode = PolygonDrawModeFill,
    },
    .clearState = {
        .colour = {0.0f, 0.0f, 0.0f, 0.0f},
        .depth = DEPTH_FURTHEST,
        .stencil = 0u,
    }
};

void GraphicsInit(GLADloadproc loader)
{
    if (!gladLoadGLLoader(loader))
    {
        printf("Failed to initialise GLAD.\n");
        exit(EXIT_FAILURE);
    }
}

void GraphicsSetViewport(Rectangle viewport)
{
    if (graphicsState.viewport.x      != viewport.x     ||
        graphicsState.viewport.y      != viewport.y     ||
        graphicsState.viewport.width  != viewport.width ||
        graphicsState.viewport.height != viewport.height)
    {
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
        graphicsState.viewport = viewport;
    }
    glCheckErrors();
}

void GraphicsSetDepthTest(DepthTest depthTest)
{
    if (graphicsState.depthTest.enabled != depthTest.enabled)
    {
        if (depthTest.enabled) { glEnable(GL_DEPTH_TEST);  }
        else                   { glDisable(GL_DEPTH_TEST); }
    }

    if (depthTest.enabled)
    {
        if (graphicsState.depthTest.func != depthTest.func)
        {
            glDepthFunc((GLenum)depthTest.func);
        }
        if (graphicsState.depthTest.writeEnabled != depthTest.writeEnabled)
        {
            glDepthMask((GLboolean)depthTest.writeEnabled);
        }
    }
    graphicsState.depthTest = depthTest;
    glCheckErrors();
}

void GraphicsSetStencilTest(StencilTest stencilTest)
{
    if (graphicsState.stencilTest.enabled != stencilTest.enabled)
    {
        if (stencilTest.enabled) { glEnable(GL_STENCIL_TEST);  }
        else                     { glDisable(GL_STENCIL_TEST); };
    }

    if (stencilTest.enabled)
    {
        if (graphicsState.stencilTest.func      != stencilTest.func      ||
            graphicsState.stencilTest.reference != stencilTest.reference ||
            graphicsState.stencilTest.mask      != stencilTest.mask)
        {
            glStencilFunc((GLenum)stencilTest.func, stencilTest.reference, stencilTest.mask);
        }

        if (graphicsState.stencilTest.stencilFail != stencilTest.stencilFail ||
            graphicsState.stencilTest.depthFail   != stencilTest.depthFail   ||
            graphicsState.stencilTest.depthPass   != stencilTest.depthPass)
        {
            glStencilOp((GLenum)stencilTest.stencilFail, (GLenum)stencilTest.depthFail, (GLenum)stencilTest.depthPass);
        }
    }
    graphicsState.stencilTest = stencilTest;
    glCheckErrors();
}

void GraphicsSetScissorTest(ScissorTest scissorTest)
{
    if (graphicsState.scissorTest.enabled != scissorTest.enabled)
    {
        if (scissorTest.enabled) { glEnable(GL_SCISSOR_TEST);  }
        else                     { glDisable(GL_SCISSOR_TEST); }
    }

    if (scissorTest.enabled && 
        (graphicsState.scissorTest.rect.x      != scissorTest.rect.x     ||
         graphicsState.scissorTest.rect.y      != scissorTest.rect.y     ||
         graphicsState.scissorTest.rect.width  != scissorTest.rect.width ||
         graphicsState.scissorTest.rect.height != scissorTest.rect.height))
    {
        glScissor(scissorTest.rect.x, scissorTest.rect.y, scissorTest.rect.width, scissorTest.rect.height);
    }
    graphicsState.scissorTest = scissorTest;
    glCheckErrors();
}

void GraphicsSetColourBlend(ColourBlend colourBlend)
{
    if (graphicsState.colourBlend.enabled != colourBlend.enabled)
    {
        if (colourBlend.enabled) { glEnable(GL_BLEND);  }
        else                     { glDisable(GL_BLEND); }
    }

    if (colourBlend.enabled)
    {
        if (graphicsState.colourBlend.srcFactor != colourBlend.srcFactor ||
            graphicsState.colourBlend.dstFactor != colourBlend.dstFactor)
        {
            glBlendFunc((GLenum)colourBlend.srcFactor, (GLenum)colourBlend.dstFactor);
        }

        if (graphicsState.colourBlend.equation != colourBlend.equation)
        {
            glBlendEquation((GLenum)colourBlend.equation);
        }
    }
    graphicsState.colourBlend = colourBlend;
    glCheckErrors();
}

void GraphicsSetFaceCull(FaceCull faceCull)
{
    if (graphicsState.faceCull.enabled != faceCull.enabled)
    {
        if (faceCull.enabled) { glEnable(GL_CULL_FACE);  }
        else                  { glDisable(GL_CULL_FACE); }
    }

    if (faceCull.enabled)
    {
        if (graphicsState.faceCull.cullFace != faceCull.cullFace)
        {
            glCullFace((GLenum)faceCull.cullFace);
        }
        if (graphicsState.faceCull.frontFace != faceCull.frontFace)
        {
            glFrontFace((GLenum)faceCull.frontFace);
        }
    }
    graphicsState.faceCull = faceCull;
    glCheckErrors();
}

void GraphicsSetPolygonMode(PolygonMode polygonMode)
{
    if (graphicsState.polygonMode.face != polygonMode.face ||
        graphicsState.polygonMode.mode != polygonMode.mode)
    {
        glPolygonMode((GLenum)polygonMode.face, (GLenum)polygonMode.mode);
        graphicsState.polygonMode = polygonMode;
    }
    glCheckErrors();
}

void GraphicsSetClearColour(vec4 colour)
{
    if (graphicsState.clearState.colour[0] != colour[0] ||
        graphicsState.clearState.colour[1] != colour[1] ||
        graphicsState.clearState.colour[2] != colour[2] ||
        graphicsState.clearState.colour[3] != colour[3])        
    {
        glClearColor(colour[0], colour[1], colour[2], colour[3]);
        graphicsState.clearState.colour[0] = colour[0];
        graphicsState.clearState.colour[1] = colour[1];
        graphicsState.clearState.colour[2] = colour[2];
        graphicsState.clearState.colour[3] = colour[3];        
    }
    glCheckErrors();
}

void GraphicsSetClearDepth(float depth)
{
    if (graphicsState.clearState.depth != depth)
    {
        glClearDepth(depth);
        graphicsState.clearState.depth = depth;
    }
    glCheckErrors();
}

void GraphicsSetClearStencil(unsigned int stencil)
{
    if (graphicsState.clearState.stencil != stencil)
    {
        glClearStencil((GLint)stencil);
        graphicsState.clearState.stencil = stencil;
    }
    glCheckErrors();
}

void GraphicsClear(BufferBit bits)
{
    glClear((GLbitfield)bits);
    glCheckErrors();
}

