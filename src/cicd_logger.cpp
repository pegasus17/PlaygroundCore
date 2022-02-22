#include <iostream>
#include "cicd_logger.h"

namespace cicd
{
  Logger::Logger()
  {
    
  }

  void Logger::Info(std::string message)
  {
    _line(Level::Info, message);
  }

  void Logger::_line(Level level, std::string message)
  {
    std::cout << message << std::endl;
  }
}
