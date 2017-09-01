#include "RenderGeometryApp.h"
#include <CameraApp.h>

int main()
{
	Application* app = new RenderGeometryApp();
	app->run(1200, 800, "Render Geometry Application", 0);		
	return 0;
}