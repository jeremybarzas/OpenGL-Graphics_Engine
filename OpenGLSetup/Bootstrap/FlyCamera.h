#pragma once
#include "Camera.h"
class FlyCamera :
	public Camera
{
public:
	FlyCamera();
	virtual ~FlyCamera();

	// Inherited via Camera
	void update(float) override;
	void setPerspective(float, float, float, float) override;
	void setLookat(vec3, vec3, vec3) override;
	void setPostion(vec3) override;
	void setLookatTeacher(vec3 eye, vec3 center, vec3 up);

private:
	float speed;
	vec3 up;
};

