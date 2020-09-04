#pragma once
#include <glm/glm.hpp>

enum class ReflectionStyle {
    Diffuse,
    Mirror,
    Refraction
};
class Material {
public:
    Material();
    ~Material();

    glm::vec3 getLightColor() const { return _lightColor; }
    glm::vec3 getDiffuseColor() const { return _diffuseColor; }
    bool isLight() const { return _light; }
    float getReflectivity() const { return _reflectivity; }
    ReflectionStyle getReflectionStyle()const { return _style; }

    void setLightColor(glm::vec3 color) { _lightColor = color; }
    void setDiffuseColor(glm::vec3 color) { _diffuseColor = color; }
    void setLight(bool value) { _light = value; }
    void setReflectivity(float value) { _reflectivity = value; }
    void setReflectionStyle(ReflectionStyle style) { _style = style; }

private:
    glm::vec3 _diffuseColor;
    glm::vec3 _lightColor;
    float _reflectivity;
    bool _light;
    ReflectionStyle _style;
};
