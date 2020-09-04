#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>
#include <random>
#include "Ray.h"

constexpr float EPS = 1e-9;

int dcmp(float v);

template<typename value_type, glm::qualifier Q>
value_type cross2(glm::vec<2, value_type, Q> v1, glm::vec<2, value_type, Q> v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

glm::vec2 lineIntersection(glm::vec2 l1, glm::vec2 d1, glm::vec2 l2, glm::vec2 d2);


float randFloat();
