#include "IntersectionInfo.h"

IntersectionInfo::IntersectionInfo() :_hitObject(nullptr), _distance(std::numeric_limits<float>::max()), _hitPos(0), _normal(0), _inside(false) {
}

IntersectionInfo::~IntersectionInfo() {
}

void IntersectionInfo::quickSetInfo(const Ray& ray, float t, const Object* obj) {
    auto hitpos = t * ray.getDir() + ray.getStart();
    setHitPos(hitpos);
    setDistance(t);
    setHitObject(obj);
    setNormal(obj->getNormal(hitpos, ray.getDir()));
}
