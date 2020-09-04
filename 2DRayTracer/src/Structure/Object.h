#pragma once
#include "BoundingBox.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include "Material.h"
class IntersectionInfo;
class Object {
public:
    Object();
    virtual ~Object() = 0 {}

    virtual BoundingBox getBoundingBox() const = 0;
    virtual bool realRayIntersect(const Ray& ray, IntersectionInfo& info) const = 0;
    virtual bool rayInside(const Ray& ray) const = 0;
    virtual glm::vec3 getDiffuseColor(const glm::vec2& pos) const = 0;
    virtual glm::vec3 getSampleColor(const glm::vec2& pos) const = 0;
    virtual glm::vec2 getNormal(glm::vec2 hitpos) const = 0;

    std::shared_ptr<Material> getMaterial() const { return _material; }
    void setMaterial(std::shared_ptr<Material> material) { _material = material; }

protected:
    std::shared_ptr<Material> _material;
};
