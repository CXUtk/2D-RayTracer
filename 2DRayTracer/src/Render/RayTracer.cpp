#include "RayTracer.h"
#include <stb_image.h>
#include <stb_image_write.h>
#include <glm/ext/matrix_transform.hpp>
#include <thread>
#include "Structure/Utils.h"
#include <ctime>

RayTracer::RayTracer(int width, int height) :_width(width), _height(height) {
    _scene = std::make_unique<Scene>();
}

RayTracer::~RayTracer() {
}

void RayTracer::run() {
    clock_t startTime, endTime;
    startTime = clock();

    FrameBuffer buffer(_width, _height, 3);
    for (int i = 0; i < _height; i += 10) {
        std::shared_ptr<std::thread> threads[10];
        for (int k = 0; k < 10; k++) {
            threads[k] = std::make_shared<std::thread>([=, &buffer]() {
                for (int j = 0; j < _width; j++) {
                    renderPos(glm::ivec2(j, i + k), buffer);
                }
                }
            );
        }
        for (int k = 0; k < 10; k++) threads[k]->join();
        printf("%.2lf%%\n", i / (float)_height);
    }
    buffer.set_pixel(glm::ivec2(0, 0), glm::vec3(1.f, 0, 0));
    stbi_write_png("test.png", _width, _height, 3, buffer.getData(), _width * 3);

    endTime = clock();  //计时结束
    printf("The running time is: %.4lfs\n",
        (double)(endTime - startTime) / CLOCKS_PER_SEC);
}


glm::vec3 RayTracer::castRay(const Ray& ray) {
    return _scene->castRay(ray, 0);
}

void RayTracer::renderPos(glm::ivec2 pos, FrameBuffer& buffer) {
    float sampleCount = 64;
    glm::vec3 totColor(0);
    for (int i = 0; i < sampleCount; i++) {
        float r = glm::two_pi<float>() * (i + randFloat()) / sampleCount;
        glm::vec2 dir(cos(r), sin(r));
        //castRay(Ray(glm::vec2(j, i), dir))
        totColor += castRay(Ray(glm::vec2(pos), dir));
    }
    buffer.set_pixel(pos, totColor / sampleCount);
}
