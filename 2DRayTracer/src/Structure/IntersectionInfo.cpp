#include "IntersectionInfo.h"

IntersectionInfo::IntersectionInfo() :_hitObject(nullptr), _distance(std::numeric_limits<float>::max()), _hitPos(0), _normal(0), _inside(false) {
}

IntersectionInfo::~IntersectionInfo() {
}
