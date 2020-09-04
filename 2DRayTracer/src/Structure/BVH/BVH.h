#pragma once
#include "Structure/BoundingBox.h"
#include "Structure/Object.h"
#include "Structure/Ray.h"
#include "Structure/IntersectionInfo.h"
#include <vector>
struct BVHNode {
    BoundingBox box;
    Object* object;
    int ch[2];

    BVHNode() :box(glm::vec2(std::numeric_limits<float>::max()), glm::vec2(std::numeric_limits<float>::min())), object(nullptr) { ch[0] = ch[1] = 0; }
};
class BVHTree {
public:
    BVHTree();
    ~BVHTree();
    void build(const std::vector<std::shared_ptr<Object>>& objects);
    bool rayIntersect(const Ray& ray, IntersectionInfo& info) const;
private:
    int _tot, _root;
    BVHNode _nodes[4096];
    std::vector<Object*> _objects;

    int newNode(Object* optr);
    void push_up(int p);
    void _build(int& p, int l, int r, int d);
    bool ray_test(int p, const Ray& ray, IntersectionInfo& info, int d) const;
};
