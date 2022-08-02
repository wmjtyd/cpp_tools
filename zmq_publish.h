//
// Created by mac on 2022/8/2.
//

#ifndef C___TEST_ZMQ_PUBLISH_H
#define C___TEST_ZMQ_PUBLISH_H

#include <string>
#include <stdio.h>
#include <assert.h>
#include <zmq.h>
#include <pthread.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <functional>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace zmq_pub_sub{
    /** Implementing of publish
     * using an inline implementation.
     */
    class Publish
    {
    public:
        /**
         * @param name
         */
        Publish(const std::string& name)
                : name_(name){}

        ~Publish(){
            zmq_close(publisher_);
            zmq_ctx_destroy(context_);
        }

        /** init
         * @return 0 -- OK, others -- errors.
         */
        inline int connect(){
            int ret = -1;
            int recv_size = -1;

            context_ = zmq_ctx_new();
            publisher_ = zmq_socket(context_, ZMQ_PUB);
            ret = zmq_bind(publisher_, name_.c_str());
            if(ret < 0) {
                init_ = false;
                printf("=== Bind failed %s\n", name_.c_str());
            }else{
                ret = 0;
                init_ = true;
            }
            return ret;
        }

        /** send message
         * @return int size of message
         */
        inline int send_message(const std::string& message){
            int rc = zmq_send(publisher_, message.c_str(), strlen(message.c_str()), 0);
            //printf("rc=%d\n",rc);
            return rc;
        }

        /** Get the name.
         * @return name.
         */
        inline std::string get_name() const{
            return name_;
        }

    private:
        std::string name_ = "tcp://127.0.0.1:5556";
        bool init_ = false;
        void *context_ = nullptr;
        void *publisher_ = nullptr;
    };
}

#endif //C___TEST_ZMQ_PUBLISH_H
