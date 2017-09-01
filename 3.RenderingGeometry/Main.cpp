#include "RenderGeometryApp.h"
#include <CameraApp.h>

int main()
{
	Application* app = new CameraApp();
	app->run(1200, 800, "Render Geometry Application", 0);		
	return 0;
}