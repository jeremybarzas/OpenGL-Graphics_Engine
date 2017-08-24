#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::update(float)
{
}

void Camera::setPerspective(float fovY, float aspect, float nearZ, float farZ)
{
	m_projection = glm::perspective(fovY, aspect, nearZ, farZ);
	m_projectionView = m_projection * m_view;
}

void Camera::setLookat(vec3 eye, vec3 center, vec3 up)
{
	vec3 z = normalize(eye - center);
	vec3 x = normalize(cross(up, z));
	vec3 y = cross(z, x);

	mat4 view = mat4(
		// x
		vec4(x.x, y.x, z.x, 0),
		// y
		vec4(x.y, y.y, z.y, 0),
		// z
		vec4(x.z, y.z, z.z, 0),
		// translation
		vec4(0.0, 0.0, 0.0, 1)
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

	m_view = view * trans;

	// assert to test against glm's lookAt funtion
	mat4 test = lookAt(eye, center, up);
	assert(m_view == test);

	m_world = inverse(m_view);
}

void Camera::setPostion(vec3 position)
{
}
