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
    matLight2->setLightColor(glm::vec3(1, 1, 1));
    auto matNoLight = std::make_shared<Material>();
    matNoLight->setLight(false);
    matNoLight->setReflectivity(0.5f);
    matNoLight->setDiffuseColor(glm::vec3(0, 0.5f, 0));

    auto matNoLight2 = std::make_shared<Material>();
    matNoLight2->setLight(false);
    matNoLight2->setReflectivity(0.5f);
    matNoLight2->setDiffuseColor(glm::vec3(0.3, 0.3, 0.3));
    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(400, 150), 40, matNoLight));
    _sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(300, 400), 40, matLight));
    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(500, 400), 40, matNoLight));
    _sceneObjects.push_back(ShapeFactory::createRectangle(100, 100, glm::vec2(350, 250), matLight2));

    _sceneObjects.push_back(ShapeFactory::createRectangle(800, 2, glm::vec2(0, 0), matNoLight2));
    _sceneObjects.push_back(ShapeFactory::createRectangle(800, 2, glm::vec2(0, 598), matNoLight2));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 600, glm::vec2(0, 0), matNoLight2));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 600, glm::vec2(798, 0), matNoLight2));

    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 100, glm::vec2(100, 300), matNoLight2));
    _sceneObjects.push_back(ShapeFactory::createRectangle(2, 100, glm::vec2(100, 150), matNoLight2));

    //_sceneObjects.push_back(std::make_shared<Circle>(glm::vec2(550, 300), 50, matNoLight);

    _bvhTree = std::make_unique<BVHTree>();
    _bvhTree->build(_sceneObjects);
    IntersectionInfo info;
    glm::vec2 unit = glm::normalize(glm::vec2(1, 1));
    bool test = _bvhTree->rayIntersect(Ray(glm::vec2(0, 0), unit), info);
    std::cout << "test" << std::endl;
}

Scene::~Scene() {
}

float clamp(float v, float minn, float maxx) {
    return std::min(std::max(v, minn), maxx);
}

glm::vec3 Scene::castRay(const Ray& ray, int depth) {
    if (depth == 4) return glm::vec3(0);
    IntersectionInfo intersectInfo;
    if (!_bvhTree->rayIntersect(ray, intersectInfo)) return glm::vec3(0);
    if (intersectInfo.isInside()) {
        return intersectInfo.getHitObject()->getDiffuseColor(glm::vec2(0));
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

    auto hitObj = intersectInfo.getHitObject();
    if (hitObj) {
        auto normal = intersectInfo.getNormal();
        float r = hitObj->getMaterial()->getReflectivity();
        auto hitPos = intersectInfo.getHitPos();
        glm::vec2 p = hitPos + normal;
        float rad = randFloat() * glm::pi<float>() - glm::pi<float>() / 2;
        float rad2 = atan2(normal.y, normal.x) + rad;
        glm::vec2 dir2 = glm::vec2(cos(rad2), sin(rad2));
        // glm::vec2 reflect = glm::reflect(ray.getDir(), normal);
        glm::vec3 diffuse = hitObj->getDiffuseColor(glm::vec2(0));
        float d = intersectInfo.getDistance() / 200.f;
        if (hitObj->getMaterial()->isLight()) {
            return clamp(1 / d, 0, 1) * (hitObj->getSampleColor(glm::vec2(0)) + r * diffuse * castRay(Ray(hitPos + normal, dir2), depth + 1) * glm::pi<float>());
        }
        return clamp(1 / d, 0, 1) * r * diffuse * castRay(Ray(hitPos + normal, dir2), depth + 1) * glm::pi<float>();
    }
    return glm::vec3(0);
}
