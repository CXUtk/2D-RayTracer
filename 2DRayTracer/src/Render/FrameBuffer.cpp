#include "FrameBuffer.h"


FrameBuffer::FrameBuffer(int width, int height, int numChannel) : _numChannel(numChannel), _width(width), _height(height) {
    _data = new unsigned char[width * height * numChannel];
    memset(_data, 0, sizeof(unsigned char) * width * height * numChannel);
}

void FrameBuffer::set_pixel(glm::ivec2 pos, const glm::vec3& color) {
    pos.y = _height - 1 - pos.y;
    int start = _numChannel * (pos.y * _width + pos.x);

    _data[start] = (unsigned char)floor(glm::clamp(color.r, 0.f, 0.999f) * 256);
    _data[start + 1] = (unsigned char)floor(glm::clamp(color.g, 0.f, 0.999f) * 256);
    _data[start + 2] = (unsigned char)floor(glm::clamp(color.b, 0.f, 0.999f) * 256);
}
