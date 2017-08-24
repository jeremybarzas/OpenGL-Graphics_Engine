#include "TestApp.h"
#include "Camera.h"

int main()
{
	Camera* testcam = new Camera();

	const vec3 eye = vec3(10, 10, 10);
	const vec3 center = vec3(0);
	const vec3 up = vec3(0, 1, 0);

	testcam->setLookat(eye, center, up);	

	// creates a Application pointer and assigns it as a TestApp
	Application* app = new TestApp();

	// invokes the base abstract "Application" class run() method
	app->run(1600, 900, "Test Window", false);

	// deletes the app after it shutsdown
	delete app;
		
	// default main function return
	return 0;
}
 