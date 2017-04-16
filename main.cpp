#include <iostream>
#include "Channel.h"
#include "Systems.h"

int main() {
  MessageBus messageBus;
  Console console(&messageBus);
  Input input(&messageBus);

  for (int i = 0; i < 50; ++i) {
    input.update();
    messageBus.notify();
  }

  return 0;
}