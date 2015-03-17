#include "model.h"
#include "view.h"
#include <vector>
#include <iostream>

#ifndef _CONTROLLER_H
#define _CONTROLLER_H


// Handle input
class Controller {
public:
    Controller();
    ~Controller();
    // Event loop
    void loop();

private:
    int row;
    int column;
    Model * model;
    View * view;
};
#endif
