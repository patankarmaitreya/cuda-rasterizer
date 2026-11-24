#pragma once

#include "framebuffer.hpp"
#include "depthbuffer.hpp"

struct RenderTarget {
    Framebuffer framebuffer;
    Depthbuffer depthbuffer;

    RenderTarget(int width, int height)
        : framebuffer(width, height),
          depthbuffer(width, height) {}
};