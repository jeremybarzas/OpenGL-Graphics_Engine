#include <Application.h>
#include <CameraApp.h>

int main()
{
	Application * app = new CameraApp();
	app->run(1200, 800, "camera app", 0);
	return 0;
}