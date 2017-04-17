//
// Created by Shihao Jing on 4/15/17.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

class Message
{
public:
  enum class MessageType
  {
    LOG,
    INPUT,
    VIDEO,
    AUDIO
  };
  Message(const std::string &event, MessageType msgType)
  {
    messageEvent = event;
    messageType = msgType;
  }

  std::string getEvent()
  {
    return messageEvent;
  }

  MessageType getType()
  {
    return messageType;
  }

private:
  std::string messageEvent;
  MessageType messageType;
};

#endif //MESSAGE_H
