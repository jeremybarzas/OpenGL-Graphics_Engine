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
	glm::mat4 m_projectionTest = glm::perspective(fovY, aspect, nearZ, farZ);

	m_projectionView = m_projectionTest * m_view;
}

void Camera::setLookat(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	glm::vec3 z = normalize(eye - center);
	glm::vec3 x = normalize(cross(up, z));
	glm::vec3 y = cross(z, x);

	glm::mat4 view = glm::mat4(
		// x
		glm::vec4(x.x, y.x, z.x, 0),
		// y
		glm::vec4(x.y, y.y, z.y, 0),
		// z
		glm::vec4(x.z, y.z, z.z, 0),
		// translation
		glm::vec4(0.0, 0.0, 0.0, 1)
	);

	glm::mat4 trans = glm::mat4(
		// x
		glm::vec4(1, 0, 0, 0),
		// y 
		glm::vec4(0, 1, 0, 0),
		// z
		glm::vec4(0, 0, 1, 0),
		// translation
		glm::vec4(-eye.x, -eye.y, -eye.z, 1)
	);

	m_view = view * trans;

	// assert to test against glm's lookAt funtion
	glm::mat4 test = lookAt(eye, center, up);
	assert(m_view == test);

	m_world = inverse(m_view);
}

void Camera::setPostion(glm::vec3)
{
}



