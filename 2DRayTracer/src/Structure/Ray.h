#pragma once
#include <glm/glm.hpp>
class Ray {
public:
    Ray(glm::vec2 start, glm::vec2 dir);
    glm::vec2 getStart() const { return _start; }
    glm::vec2 getDir() const { return _dir; }
private:
    glm::vec2 _start, _dir;
};
