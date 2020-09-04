#include "Utils.h"

int dcmp(float v) {
    if (fabs(v) < EPS) return 0;
    return v > 0 ? 1 : -1;
}

glm::vec2 lineIntersection(glm::vec2 l1, glm::vec2 d1, glm::vec2 l2, glm::vec2 d2) {
    float t = cross2(d2, l1 - l2) / cross2(d1, d2);
    return l1 + d1 * t;
}

std::mt19937 random;
float randFloat() {
    return random() / (float)random.max();
}

void drawRectangle(glm::vec2 start, glm::vec2 size, FrameBuffer& frame) {
    glm::vec3 red = glm::vec3(1, 0, 0);
    for (int i = start.x; i <= start.x + size.x; i++) {
        frame.set_pixel(glm::ivec2(i, start.y), red);
        frame.set_pixel(glm::ivec2(i, start.y + size.y), red);
    }
    for (int i = start.y; i <= start.y + size.y; i++) {
        frame.set_pixel(glm::ivec2(start.x, i), red);
        frame.set_pixel(glm::ivec2(start.x + size.x, i), red);
    }
}
