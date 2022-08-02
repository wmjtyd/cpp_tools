//
// Created by mac on 2022/8/2.
//
#include "zmq_publish.h"
#include <iostream>
#include <chrono>
#include <thread>

class Test{
public:
    Test(){
    }

    void run(){
        using namespace zmq_pub_sub;
        Publish pub =  Publish("ipc:///tmp/pubsub1.ipc");
        int ret = pub.connect();
        if (ret ==0){
            for(int i=0;i<count_; ++i){
                std::string message="message from publisher No." + std::to_string(i);
                pub.send_message(message);
                std::cout<<"sent:"<<message<<"\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

private:
    long long count_ = 10;
};

int main(){
    Test test;
    test.run();
    return 0;
}