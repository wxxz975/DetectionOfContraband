#include "Core/Application.h"
#include <memory>

#include <unordered_map>
#include <string>





int main(int argc, char*argv[]) {
    AbstractApplication *app = new Application();

    app->run();
    return 0;
}



