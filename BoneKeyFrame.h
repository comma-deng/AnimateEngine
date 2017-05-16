#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
using namespace glm;

#define TimePos  double

class BoneKeyFrame
{
public:
	BoneKeyFrame(TimePos timePos,quat rotation,vec3 position):
		timepos(timePos),rotation(rotation),position(position)
	{}

	TimePos timepos;
	quat rotation;
	vec3 position;
};

