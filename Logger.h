//
// Created by Shihao Jing on 4/15/17.
//

#ifndef ENGINE_LOGGER_H
#define ENGINE_LOGGER_H

#include <iostream>
#include <sstream>

class LogMessage
{
public:
  friend class Logger; // only allow the Logger class to instantiate a LogMessage
  template <typename T>
  LogMessage& operator << (const T& value)
  {
    mBuffer << value;
    return *this;
  }
  LogMessage& operator << (std::ostream& (*fn)(std::ostream& os))
  {
    fn(mBuffer);
    return *this;
  }

private:
  std::ostringstream mBuffer;

};

class Logger
{

};


#endif //ENGINE_LOGGER_H
