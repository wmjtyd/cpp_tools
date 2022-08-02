//
// Created by mac on 2022/8/2.
//
#include "zmq_subscribe.h"
#include <iostream>

class Test{
public:
    Test(){

    }

    void eventCallbackHandler(const std::string& message){
        // Handle the reported event.
        std::cout<<"eventCallbackHandler No[" <<count_<<"]:"<< message<<"\n";
        count_++;
    }

    void run(){
        using namespace zmq_pub_sub;
        Subscribe sub =  Subscribe("ipc:///tmp/pubsub1.ipc");

        using MyFunction = std::function<void(const std::string&)>;
        MyFunction fun = std::bind(&Test::eventCallbackHandler, this, std::placeholders::_1);
        sub.setEventCallback(fun);

        std::cout<<"sub name:"<<sub.get_name()<<"\n";
        int ret = sub.init();
        std::cout<<"ret="<<ret<<"\n";
        sub.run();
    }

private:
    long long count_ = 0;
};

int main(){
    Test test;
    test.run();
    return 0;

}