#include "Core/Application.h"
#include <memory>



int main(int argc, char*argv[]) {
    AbstractApplication *app = new Application();
    
    app->run();
    return 0;
}


