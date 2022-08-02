//
// Created by mac on 2022/8/2.
//

#ifndef C___TEST_ZMQ_SUBSCRIBE_H
#define C___TEST_ZMQ_SUBSCRIBE_H

#include <string>
#include <stdio.h>
#include <zmq.h>
#include <pthread.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <functional>
#include <assert.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


namespace zmq_pub_sub{
    /** Implementing of PubServer
     * using an inline implementation.
     */
    class Subscribe
    {
    public:
        /** Create a telephone list.
         * @param name  e.g "tcp://127.0.0.1:5556"
         */
        Subscribe(const std::string& name)
                : name_(name), is_exit_(false){}

        ~Subscribe(){
            zmq_close(subscriber_);
            zmq_ctx_destroy(context_);
        }

        /** init
         * @return 0 -- OK, others -- errors.
         */
        inline int init(){
            int recv_size = 0;
            int ret = -1;
            context_ = zmq_ctx_new();
            subscriber_ = zmq_socket(context_, ZMQ_SUB);
            ret = zmq_connect(subscriber_, name_.c_str());
            assert(ret == 0);
            ret = zmq_setsockopt(subscriber_, ZMQ_SUBSCRIBE, "", 0);
            if(ret < 0) {
                init_ = false;
                printf("=== Bining failed with error code:%d\n", ret);
            }else{
                ret = 0;
                init_ = true;
            }
            return ret;
        }

        template <typename TFunc>
        void setEventCallback(TFunc&& func){
            eventCallback_ = std::forward<TFunc>(func);
        }

        void eventHandler(const std::string& message){
            if (eventCallback_) {
                // invoke registered callback object
                eventCallback_(message);
            }
        }

        /** run
         * @return none
         */
        inline void run(){
            while(!is_exit_ && init_){
                char recv_buf[1024] = {0};
                memset(recv_buf, 0, sizeof(recv_buf));
                int recv_size = zmq_recv(subscriber_, recv_buf, 1024, 0);
                //printf("recv_size=%d\n",recv_size);
                //printf("recv_buf=%s\n",recv_buf);
                if (recv_size > 0) {
                    std::string message;
                    // convertion from char string to c++ string
                    // using assign function
                    message.assign(recv_buf);
                    eventHandler(message);
                }
                //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        /** set exit
         * @return none
         */
        inline void exit(){
            is_exit_ = true;
        }

        /** Get the name  e.g "tcp://127.0.0.1:5556"
         * @return name.
         */
        inline std::string get_name() const
        {
            return name_;
        }


    private:
        std::string name_ = "tcp://127.0.0.1:5556";
        bool is_exit_ = false;
        bool init_ = false;
        void *subscriber_ = nullptr;
        void *context_ = nullptr;
        std::function<void(const std::string&)> eventCallback_;
    };
}

#endif //C___TEST_ZMQ_SUBSCRIBE_H
