#pragma once

#include <optional>
#include <vector>

class Depthbuffer {
public:
    Depthbuffer(int width, int height);

    std::optional<float> getDepth(int x, int y) const;

    void setDepth(int x, int y, float depth);

    void clear();

private:
    int width;
    int height;
    std::vector<float> depths;
};