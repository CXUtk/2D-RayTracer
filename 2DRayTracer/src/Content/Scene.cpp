#include "Scene.h"
#include "Structure/SceneObject/Circle.h"
#include "Structure/SceneObject/Polygon.h"
#include "Structure/SceneObject/ShapeFactory.h"
#include "Structure/Utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
Scene::Scene() {
    auto matLight = std::make_shared<Material>();
    matLight->setReflectivity(0.0f);
    matLight->setLightColor(glm::vec3(1, 1, 1));


    auto matLight2 = std::make_shared<Material>();
    matLight2->setReflectivity(0.0f);
    matLight2->setLightColor(glm::vec3(0.8, 0.8, 0.8));

    auto matNoLight = std::make_shared<Material>();
    matNoLight->setLight(false);
    matNoLight->setReflectivity(0.1f);
    matNoLight->setDiffuseColor(glm::vec3(1, 1, 1));

    auto matNoLight2 = std::make_shared<Material>();
    matNoLight2->setLight(false);
    matNoLight2->setReflectivity(1.f);
    matNoLight2->setDiffuseColor(glm::vec3(1, 0, 0));
    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(400, 150), 40, matNoLight));
    _sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(300, 400), 40, matLight));
    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(500, 400), 40, matNoLight));
    _sceneObjects.push_back(ShapeFactory::createRectangle(100, 100, glm::vec2(350, 250), matLight2));

    _sceneObjects.push_back(ShapeFactory::createRectangle(700, 2, glm::vec2(50, 50), matNoLight));
    _sceneObjects.push_back(ShapeFactory::createRectangle(700, 2, glm::vec2(50, 550), matNoLight));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 500, glm::vec2(50, 50), matNoLight));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 500, glm::vec2(750, 50), matNoLight));

    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 100, glm::vec2(150, 300), matNoLight2));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 100, glm::vec2(150, 150), matNoLight2));


    //glm::vec2 center(300, 200);
    //for (float r = 0; r > -glm::pi<float>() + 0.3f; r -= 0.05) {
    //    _sceneObjects.push_back(ShapeFactory::createSegment(center + glm::vec2(cos(r), sin(r)) * 50.f, center + glm::vec2(cos(r - 0.05f), sin(r - 0.05f)) * 50.f,
    //        matNoLight2));
    //}

    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(550, 300), 50, matNoLight);
    float t;
    bool b = raySegmentIntersect(Ray(glm::vec2(0, 0), glm::vec2(1, 0)), glm::vec2(0.5, 0), glm::vec2(1, 0), t);

    _bvhTree = std::make_unique<BVHTree>();
    _bvhTree->build(_sceneObjects);
}

Scene::~Scene() {
}

float clamp(float v, float minn, float maxx) {
    return std::min(std::max(v, minn), maxx);
}
/*  intersectInfo.setDistance(std::numeric_limits<float>::max());
  for (auto objs : _sceneObjects) {
      IntersectionInfo info;
      if (objs->rayInside(ray)) {
          return objs->getDiffuseColor(glm::vec2(0));
      }
      if (objs->realRayIntersect(ray, info)) {
          if (info.getDistance() < intersectInfo.getDistance()) {
              intersectInfo = info;
          }
      }
  }*/

glm::vec3 Scene::castRay(const Ray& ray, int depth) {
    if (depth == 4) return glm::vec3(0);
    IntersectionInfo intersectInfo;
#ifdef BRUTE
    intersectInfo.setDistance(std::numeric_limits<float>::max());
    for (auto objs : _sceneObjects) {
        IntersectionInfo info;
        if (objs->rayInside(ray)) {
            return objs->getDiffuseColor(glm::vec2(0));
        }
        if (objs->realRayIntersect(ray, info)) {
            if (info.getDistance() < intersectInfo.getDistance()) {
                intersectInfo = info;
            }
        }
    }
#else
    if (!_bvhTree->rayIntersect(ray, intersectInfo)) return glm::vec3(0);
    if (intersectInfo.isInside()) {
        return intersectInfo.getHitObject()->getDiffuseColor(glm::vec2(0));
    }
#endif
    auto hitObj = intersectInfo.getHitObject();
    if (hitObj) {
        auto normal = intersectInfo.getNormal();
        float r = hitObj->getMaterial()->getReflectivity();
        auto hitPos = intersectInfo.getHitPos();
        glm::vec2 p = hitPos + normal;
        float rad = randFloat() * glm::pi<float>() - glm::pi<float>() / 2;
        float rad2 = atan2(normal.y, normal.x) + rad;
        //glm::vec2 dir2 = glm::vec2(cos(rad2), sin(rad2));
        glm::vec2 dir2 = glm::reflect(ray.getDir(), normal);
        glm::vec3 diffuse = hitObj->getDiffuseColor(glm::vec2(0));
        float d = intersectInfo.getDistance() / 200.f;
        if (hitObj->getMaterial()->isLight()) {
            return (hitObj->getSampleColor(glm::vec2(0)) + r * diffuse * castRay(Ray(hitPos + normal, dir2), depth + 1) * glm::pi<float>());
        }
        return r * diffuse * castRay(Ray(hitPos + normal, dir2), depth + 1) * glm::pi<float>();
    }
    return glm::vec3(0);
}

void Scene::showDebugInfo(FrameBuffer& frame) {
    _bvhTree->walkRectangles(frame);
}
