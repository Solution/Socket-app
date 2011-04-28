/* 
 * File:   Application.h
 * Author: patriktomasik
 * Application singleton
 * Created on 28. duben 2011, 23:44
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

class Application
{
private:
    Application() {}
    static Application* app;
    static bool appFlag;
    
public:
    ~Application();
    
    static Application* createInstance();
};

#endif	/* APPLICATION_H */

