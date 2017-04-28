#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
using namespace glm;

#define TimePos  double

struct BoneKeyFrame
{
	TimePos timepos;

	quat rotation;
	vec3 shift;
};

