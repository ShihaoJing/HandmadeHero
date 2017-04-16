#include <iostream>
#include "Channel.h"

int main() {
    MyEvent a{ 123 };
    MyHandler b, c;
    MyIntHandler d, e, f;
    Channel::add<MyEvent>(&b);
    Channel::add<MyEvent>(&c);

    Channel::broadcast(a);
    Channel::broadcast(MyEvent{ 456 });
    Channel::broadcast(a);

    Channel::remove<MyEvent>(&b);
    Channel::broadcast(MyEvent{ 789 });

    Channel::broadcast(111);

    Channel::add<int>(&d);
    Channel::add<int>(&e);
    Channel::add<int>(&f);

    Channel::broadcast(222);

    Channel::remove<int>(&e);

    Channel::broadcast(333);
}