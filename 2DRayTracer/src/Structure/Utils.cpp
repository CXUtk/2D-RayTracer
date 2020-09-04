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
