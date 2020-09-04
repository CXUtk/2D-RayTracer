#pragma once
#include <algorithm>
#include <glm/glm.hpp>
#include <Structure\Ray.h>
class BoundingBox {
public:
    BoundingBox(glm::vec2 minPos, glm::vec2 maxPos);
    ~BoundingBox();

    bool rayIntersect(const Ray& ray, float& tNear) const;

    glm::vec2 getCenter() const { return (_minPos + _maxPos) / 2.f; }

    BoundingBox Union(const BoundingBox& box) const {
        glm::vec2 minn(std::min(_minPos.x, box._minPos.x), std::min(_minPos.y, box._minPos.y));
        glm::vec2 maxx(std::max(_maxPos.x, box._maxPos.x), std::max(_maxPos.y, box._maxPos.y));
        return BoundingBox(minn, maxx);
    }
    BoundingBox Intersection(const BoundingBox& box) const {
        glm::vec2 minn(std::max(_minPos.x, box._minPos.x), std::max(_minPos.y, box._minPos.y));
        glm::vec2 maxx(std::min(_maxPos.x, box._maxPos.x), std::min(_maxPos.y, box._maxPos.y));
        return BoundingBox(minn, maxx);
    }

private:
    glm::vec2 _minPos, _maxPos;
};
