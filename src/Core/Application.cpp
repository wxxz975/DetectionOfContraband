#include "Core/Application.h"


Core::Application::Application()
{
  m_context = std::make_unique<Context>();
}

void Core::Application::run(const std::string& p_configPath)
{

  m_context->init(p_configPath);  
  
  
  
  m_context->m_uiManager->Render(); 
}
