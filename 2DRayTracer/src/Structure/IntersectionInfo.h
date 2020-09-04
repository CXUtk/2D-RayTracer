#pragma once
#include <memory>
#include "Object.h"

class Object;
class IntersectionInfo {
public:
    IntersectionInfo();
    ~IntersectionInfo();

    void setHitObject(const Object* object) { _hitObject = object; }
    void setDistance(float distance) { _distance = distance; }
    void setHitPos(glm::vec2 hitpos) { _hitPos = hitpos; }
    void setNormal(glm::vec2 normal) { _normal = normal; }
    void setInside(bool value) { _inside = value; }


    bool isInside() const { return _inside; }
    float getDistance() const { return _distance; }
    const Object* getHitObject() const { return _hitObject; }
    glm::vec2 getHitPos() const { return _hitPos; }
    glm::vec2 getNormal() const { return _normal; }

private:
    const Object* _hitObject;
    float _distance;
    bool _inside;
    glm::vec2 _hitPos;
    glm::vec2 _normal;
};
