#include "controller.h"

using namespace std;

Controller::Controller() {
    model = new Model(4, 4);
    view = new View("Concentration!", 1024, 768);
    row = -1;
    column = -1;
}

Controller::~Controller() {
    delete model;
    delete view;
}

/**
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    while(!model->gameOver()) {
        view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                model->end();
                break;
            case SDL_MOUSEBUTTONDOWN:
                row = e.button.y / 80;
                column = e.button.x / 80;
                model->flip(e.button.y / 80, e.button.x / 80);
                if (model->elementsVisible())
                {
                    view->show(model);
                    SDL_Delay(300);
                    model->flip(e.button.y / 80, e.button.x / 80);
                }
                break;
            }
        }
    }
    view->show(model);
    SDL_Delay(5250);
}


