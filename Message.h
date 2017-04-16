//
// Created by Shihao Jing on 4/15/17.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

class Message
{
public:
  Message(const std::string &event)
  {
    messageEvent = event;
  }

  std::string getEvent()
  {
    return messageEvent;
  }

private:
  std::string messageEvent;
  std::string messageType;
};

#endif //MESSAGE_H
