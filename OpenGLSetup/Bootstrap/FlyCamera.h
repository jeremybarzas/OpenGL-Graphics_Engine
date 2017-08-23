#pragma once
#include "Camera.h"
class FlyCamera :
	public Camera
{
public:
	FlyCamera();
	~FlyCamera();
	void update(float);
	void setSpeed(float);

private:
	float speed;
	vec3 up;

	// Inherited via Camera
	virtual void setPerspective(float, float, float, float) override;
	virtual void setLookat(vec3, vec3, vec3) override;
	virtual void setPostion(vec3) override;
};

