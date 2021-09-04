#include <SFML/Window/Window.hpp>
#include<SFML/Window/Event.hpp>
#include<Renderer.h>
using namespace sf;
int main()
{
    ContextSettings ctxSettings;
    ctxSettings.antialiasingLevel = 1;
    ctxSettings.depthBits = 24;
    ctxSettings.majorVersion = 3;
    ctxSettings.minorVersion = 3;
    ctxSettings.stencilBits = 0;
    Window mainWindow(VideoMode(1280, 720),
                      "Omni-Directional-Light-Example",
                      Style::Default, ctxSettings);
    Renderer::instance().init();
    while(1){
        Event event;
        while(mainWindow.pollEvent(event)){
            switch (event.type)
            {
            case Event::Closed :
                mainWindow.close();
                return 0;
                break;

            default:
                break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mainWindow.display();
    }
}