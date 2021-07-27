#pragma once
#include "Object.h"
#include "glm/glm.hpp"
#include <array>
#include <memory>

struct Entity;

enum Planes {
    Near,
    Far,
    Left,
    Right,
    Top,
    Bottom
};

struct Plane {
    glm::vec3 normal;
    float DistanceToPoint(const glm::vec3& point) const;
    float distanceToOrigin;
};

class ViewFrustum {
public:
    void Update(const glm::mat4& mat);
    bool IsInFrustum(const Object& object);
private:
    std::array<Plane, 6> planes;
};

