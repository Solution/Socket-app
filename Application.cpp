#include "Application.h"

bool Application::appFlag = false;
Application* Application::app = NULL;


Application::~Application()
{
    appFlag = false;
    delete app;
}

Application* Application::createInstance()
{
    if(appFlag == false)
    {
        app = new Application();
        appFlag = true;
        return app;
    }
}
