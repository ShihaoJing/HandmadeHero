//
// Created by Shihao Jing on 4/15/17.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <functional>
#include "MessageBus.h"

class System
{
public:
  System(MessageBus *messageBus)
  {
    this->messageBus = messageBus;
    this->messageBus->addReceiver(this->getNotifyFunc());
  }

  virtual void update() {};
protected:
  MessageBus *messageBus;

  std::function<void (Message)> getNotifyFunc()
  {
    auto messageListenter = [=](Message msg) -> void {
      this->onNotify(msg);
    };
    return messageListenter;
  }

  void send(Message msg)
  {
    messageBus->sendMessage(msg);
  }

  virtual void onNotify(Message message)
  {
    //Do something here
  }
};

#endif //ENGINE_SYSTEM_H
