#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <memory>
#include "Polygon.h"

class ShapeFactory {
public:
    static std::shared_ptr<Polygon> createRectangle(float width, float height, glm::vec2 pos, std::shared_ptr<Material> material);
};
