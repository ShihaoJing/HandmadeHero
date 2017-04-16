//
// Created by Shihao Jing on 4/15/17.
//

#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <functional>
#include <queue>
#include <vector>
#include "Message.h"

class MessageBus {
public:
  MessageBus() {};
  ~MessageBus() {};

  void addReceiver(std::function<void (Message)> messageReceiver)
  {
    receivers.push_back(messageReceiver);
  }

  void sendMessage(Message msg)
  {
    messageQueue.push(msg);
  }

  void notify()
  {
    while (!messageQueue.empty())
    {
      for (auto iter = receivers.begin(); iter != receivers.end(); ++iter)
      {
        (*iter)(messageQueue.front());
      }
      messageQueue.pop();
    }
  }

private:
  std::vector<std::function<void (Message)>> receivers;
  std::queue<Message> messageQueue;
};

#endif //ENGINE_MESSAGEBUS_H
