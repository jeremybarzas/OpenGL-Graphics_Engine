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
	
	while (closeApp == false)
	{
		cout << "0) - Camera Application\n";
		cout << "1) - Test Application\n\n";		
		cout << "Enter the number of the application to run. ";
		cin >> input;		
		system("CLS");
		
		switch (input)
		{
		case 0:
			app = new CameraApp();
			app->run(1600, 900, "Camera Application", false);
			delete app;
			break;

		case 1:
			app = new TestApp();
			app->run(800, 450, "Test Application", false);
			delete app;
			break;
		}		
		
		cout << "0) - No\n";
		cout << "1) - Yes\n";
		cout << "Do you want to close the application? ";		
		cin >> closeApp;
		system("CLS");
	}	
}

int main()
{
	
	Application* app = new CameraApp();
	app->run(1600, 900, "Camera Application", false);
	delete app;
	// determines which application to run
	//appswitcher();
		
	// default main function return
	return 0;
}
 