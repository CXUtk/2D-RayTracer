#pragma once
#include <vector>
#include <memory>
#include "Structure/Object.h"
#include "Structure/BVH/BVH.h"
class Scene {
public:
    Scene();
    ~Scene();

    glm::vec3 castRay(const Ray& ray, int depth);
private:
    std::vector<std::shared_ptr<Object>> _sceneObjects;
    std::unique_ptr<BVHTree> _bvhTree;
};
