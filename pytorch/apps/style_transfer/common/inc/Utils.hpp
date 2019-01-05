#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#include "NotCopyable.hpp"

class Utils : public NotCopyable
{
  public:
    Utils() {}
    ~Utils() {}
    int ExecuteCommand(std::string &cmd);
};

#endif // UTILS_HPP
