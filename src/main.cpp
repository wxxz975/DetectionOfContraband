#include "Core/Application.h"




static const char* p_configPath = "";
int main(int argc, char*argv[]) {
  
  std::unique_ptr<Core::Application> app = std::unique_ptr<Core::Application>();

  app->run(p_configPath);


  return 0;
}



