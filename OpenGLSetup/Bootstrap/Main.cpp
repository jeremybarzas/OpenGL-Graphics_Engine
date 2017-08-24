#include "TestApp.h"
#include "CameraApp.h"
#include "Camera.h"
#include <iostream>
#include "Transform.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
using std::cout;
using std::cin;

void appswitcher()
{	
	Application* app;
	int input = -1;
	bool closeApp = false;	
	
	while (closeApp == false && input > 0)
	{
		cout << "1) - Test Application\n";
		cout << "2) - Camera Application\n\n";
		cout << "Enter the number of the application to run. ";
		cin >> input;		
		system("CLS");
		
		switch (input)
		{
		case 1:
			app = new TestApp();
			app->run(800, 450, "Test Application", false);
			delete app;
			break;

		case 2:
			app = new CameraApp();
			app->run(1600, 900, "Camera Application", false);
			delete app;
			break;
		}		
		
		cout << "1) - Yes\n";
		cout << "0) - No\n";
		cout << "Do you want to close the application? ";		
		cin >> closeApp;
		system("CLS");
	}	
}

int main()
{
	// determines which application to run
	appswitcher();
	
	Transform* transform = new Transform();	
	transform->rotate(glm::pi<float>() * .25, ZAXIS);

	
		
	// default main function return
	return 0;
}
 