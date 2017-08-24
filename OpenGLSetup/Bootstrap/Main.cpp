#include "TestApp.h"
#include "CameraApp.h"
#include "Camera.h"

int main()
{
	// creates a Application pointer and assigns it as a TestApp
	Application* app = new CameraApp();

	// invokes the base abstract "Application" class run() method
	app->run(1600, 900, "Test Window", false);

	// deletes the app after it shutsdown
	delete app;
		
	// default main function return
	return 0;
}
 