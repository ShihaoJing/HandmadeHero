//
// Created by Shihao Jing on 4/16/17.
//

#ifndef CONSOLE_H
#define CONSOLE_H

#include "System.h"

class Console : public System
{
public:
  Console(MessageBus* messageBus) : System(messageBus)
  {

  }

private:
  void onNotify(Message msg)
  {
    std::cout << "Console: " << std::endl;
    if (msg.getType() == Message::MessageType::INPUT)
    {
      std::cout << "Input System Message Received:" << std::endl;
    }
    std::cout << msg.getEvent() << std::endl;
  }
};

#endif //ENGINE_CONSOLE_H
