#ifndef CICD_LOGGER_H
#define CICD_LOGGER_H

#include <string>
#include "cicd_core.h"

namespace cicd
{
  class Logger
  {
  public:
    enum class Level
    {
      None,
      Info,
      Warning,
      Error,
      Fatal,
      Panic
    };

    Logger();

    void Info(std::string message);

  private:
    void _line(Level level, std::string message);
  };
}

#endif /* CICD_LOGGER_H */
