#include "TestApp.h"
#include "CameraApp.h"
#include "Camera.h"
#include <iostream>

using std::cout;
using std::cin;

void appswitcher()
{
	Application* app;
	int input;
	bool closeApp = false;	

	while (closeApp == false)
	{
		cout << "0) - Test Application\n";
		cout << "1) - Camera Application\n\n";
		cout << "Enter the number of the application to run. ";
		cin >> input;

		switch (input)
		{
		case 0:
			app = new TestApp();
			app->run(800, 450, "Test Application", false);
			delete app;
			break;

		case 1:
			app = new CameraApp();
			app->run(1600, 900, "Camera Application", false);
			delete app;
			break;
		}
		
		cout << "0) - Yes\n";
		cout << "1) - No\n";
		cout << "Do you want to open another application? ";		
		cin >> closeApp;
	}	
}

int main()
{
	// determines which application to run
	appswitcher();
		
	// default main function return
	return 0;
}
 