#include <iostream>
#include "Channel.h"
#include "System.h"

class ComponentA : public System
{
public:
  ComponentA(MessageBus* messageBus) : System(messageBus) {}
private:
  void onNotify(Message msg)
  {
      std::cout << "A: I received: " << msg.getEvent() << std::endl;
  }
};

class ComponentB : public System
{
public:
  ComponentB(MessageBus* messageBus) : System(messageBus) {}

  void update()
  {
    Message greeting("Hi, I am B");
    send(greeting);
  }
private:
  void onNotify(Message msg)
  {
    std::cout << "B: I received: " << msg.getEvent() << std::endl;
  }

};

int main() {
  MessageBus messageBus;
  ComponentA compA(&messageBus);
  ComponentB compB(&messageBus);

  for (int i = 0; i < 50; ++i) {
    compA.update();
    compB.update();
    messageBus.notify();
  }

  return 0;
}