#include "Utils.hpp"

#include <iostream>
// system() cmd related.
#include <stdlib.h>
#include <signal.h>

int Utils::ExecuteCommand(std::string &cmd)
{
  std::cout << "Executing CMD: " << cmd.c_str() << "\n";
  int ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
      && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
  }
  return ret;
}

