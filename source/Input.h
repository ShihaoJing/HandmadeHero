//
// Created by Shihao Jing on 4/16/17.
//

#ifndef INPUT_H
#define INPUT_H

#include "System.h"
#include <iostream>

class Input : public System
{
public:
  Input(MessageBus *msgBus) : System(msgBus)
  {

  }

  void update()
  {
    //TODO Listen Keyboard Input
  }
private:
  void onNotify(Message msg)
  {

  }
};

#endif //ENGINE_INPUT_H
