#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <string>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Framebuffer {
public:
    Framebuffer(int width, int height);
    
    int getWidth() const;
    
    int getHeight() const;

    void setPixel(int x, int y, const Color& color);

    std::optional<Color> getPixel(int x, int y) const;

    void clear(const Color& color);

    bool writePPM(const std::string& filename) const;
private:
    int width;
    int height;
    std::vector<Color> pixels;
};