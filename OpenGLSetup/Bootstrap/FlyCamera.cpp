#include "FlyCamera.h"

FlyCamera::FlyCamera()
{
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float)
{
}

void FlyCamera::setPerspective(float, float, float, float)
{
}
void FlyCamera::setLookatTeacher(vec3 eye, vec3 center, vec3 up)
{

	 
	vec3 z = normalize(eye - center);
	vec3 x = normalize(cross(up, z));
	vec3 y = cross(z, x);

	mat4 view = mat4(
		vec4(x.x, y.x, z.x, 0),
		vec4(x.y, y.y, z.y, 0),
		vec4(x.z, y.z, z.z, 0),
		vec4(0.0, 0.0, 0.0, 1)
	);

	mat4 trans = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-eye.x, -eye.y, -eye.z, 1)

	);

	mat4 m_view = view * trans;
	mat4 m_world = inverse(m_view);
	mat4 m_projection = glm::perspective(1, 1, 1, 1);
	mat4 m_projectionView = m_projection * m_view;

}
void FlyCamera::setLookat(vec3 eye, vec3 center, vec3 up)
{
	vec3 f = eye - center;
	vec3 z = glm::normalize(f);
	vec3 s = glm::cross(up, z);
	vec3 x = glm::normalize(s);
	vec3 u = glm::cross(z, x);
	vec3 y = glm::normalize(u);
	
	mat4 view = mat4(
		// x
		vec4(x.x, y.x, z.x, 0),
		// y
		vec4(x.y, y.y, z.y, 0),
		// z
		vec4(x.z, y.z, z.z, 0),
		// translation
		vec4(0, 0, 0, 1)
	);		
	
	mat4 trans = mat4(
		// x
		vec4(1, 0, 0, 0),
		// y 
		vec4(0, 1, 0, 0),
		// z
		vec4(0, 0, 1, 0),
		// translation
		vec4(-eye.x, -eye.y, -eye.z, 1)
	);
	//((test).value)[2]   {x=-0.707106769 y=-0.408248246 z=0.577350199 ...}
	//((m_view).value)[2] {x=-0.707106769 y=-0.408248305 z=0.577350199 ...}
		
	mat4 m_view = view * trans;

	mat4 test = glm::lookAt(eye, center, up);

	assert(m_view == test);



}

void FlyCamera::setPostion(vec3)
{
}

 