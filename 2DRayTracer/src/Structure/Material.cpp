#include "Material.h"

Material::Material() : _lightColor(glm::vec3(1)), _diffuseColor(glm::vec3(1)), _reflectivity(0.5f), _light(true),
_style(ReflectionStyle::Diffuse) {
}

Material::~Material() {
}
