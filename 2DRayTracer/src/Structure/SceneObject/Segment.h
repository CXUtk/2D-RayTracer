#pragma once
#include "Structure/Object.h"



class Segment : public Object {
public:
    Segment(glm::vec2 start, glm::vec2 end, glm::vec2 normal) :start(start), end(end), normal(normal) {}

    virtual BoundingBox getBoundingBox() const override;
    virtual bool realRayIntersect(const Ray& ray, IntersectionInfo& info) const override;
    virtual glm::vec3 getDiffuseColor(const glm::vec2& pos) const override { return _material->getDiffuseColor(); }
    glm::vec3 getSampleColor(const glm::vec2& pos) const  override { return _material->getLightColor(); }
    bool rayInside(const Ray& ray) const override;
    glm::vec2 getNormal(glm::vec2 hitpos) const override { return normal; }

private:
    glm::vec2 start, end;
    glm::vec2 normal;
};
