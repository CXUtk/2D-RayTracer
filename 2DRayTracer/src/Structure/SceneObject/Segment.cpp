#include "Segment.h"
#include "Structure/Utils.h"

BoundingBox Segment::getBoundingBox() const {
    glm::vec2 minn, maxx;
    minn = start, maxx = end;
    minn.x = std::min(minn.x, end.x);
    minn.y = std::min(minn.y, end.y);
    maxx.x = std::max(maxx.x, end.x);
    maxx.y = std::max(maxx.y, end.y);
    return BoundingBox(minn, maxx);
}

bool Segment::realRayIntersect(const Ray& ray, IntersectionInfo& info) const {

    glm::vec2 dir = glm::normalize(end - start);
    float crs = cross2(ray.getDir(), dir);
    // 如果平行
    if (std::abs(crs) < EPS) {
        // 如果不在射线上
        if (glm::dot(end - ray.getStart(), ray.getDir()) < 0) return false;
        // 如果两个线是重叠的
        if (std::abs(cross2(end - ray.getStart(), dir)) < EPS) {
            // 如果点在线段上
            if (glm::dot(ray.getStart() - start, dir) >= 0) {
                info.setInside(true);
                info.setDistance(0);
                info.setHitObject(this);
                return true;
            }
            // 否则选一个最近端点
            float d1 = glm::distance(ray.getStart(), start);
            float d2 = glm::distance(ray.getStart(), end);
            info.setDistance(std::min(d1, d2));
            info.setHitObject(this);
            return true;
        }
        return false;
    }

    auto v = lineIntersection(ray.getStart(), ray.getDir(), start, dir);
    float d = glm::dot(ray.getDir(), v - ray.getStart());
    // 如果不在射线上
    if (d < 0) return false;

    // 如果不在线段上
    if (glm::dot(dir, v - start) < 0 || glm::distance(v, start) > glm::distance(start, end)) return false;
    info.setDistance(d);
    info.setHitObject(this);
    return true;
}

bool Segment::rayInside(const Ray& ray) const {
    return false;
}
