//
// Created by Shihao Jing on 4/16/17.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "System.h"
class Input : public System
{
public:
  Input(MessageBus *msgBus) : System(msgBus)
  {

  }

  void update()
  {
    Message::MessageType msgType = Message::MessageType::INPUT;
    Message msg("input signal W_PRESS", msgType);
    send(msg);
  }
private:
  void onNotify(Message msg)
  {

  }
};

#endif //ENGINE_INPUT_H
