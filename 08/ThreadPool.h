#pragma once
#include <iostream>
#include <pthread.h>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool{
    std::mutex m;
    std::vector<std::thread> pool;
    std::condition_variable cond;
    std::queue<std::function<void()>> task_queue;
    std::atomic<bool> stop;
public:
    explicit ThreadPool(size_t poolSize){
        stop = false;
        for (size_t i = 0; i < poolSize; ++i){
            pool.emplace_back(std::thread([this](){
                this->work();
            }));
        }
    }

    ~ThreadPool(){
        stop = true;
        cond.notify_all();
        for (size_t i = 0; i < pool.size(); ++i){
            pool[i].join();
        }
    }

    void work(){
        while (!stop){
            std::unique_lock<std::mutex> lock(m);
            if (task_queue.empty()){
                cond.wait(lock);
            } else {
                auto task(std::move(task_queue.front()));
                task_queue.pop();
                lock.unlock();
                task();
            }
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
            (std::bind(func, args...));
        auto res = task->get_future();
        std::unique_lock<std::mutex> lock(m);
        task_queue.push([task](){
            (*task)();
        });
        cond.notify_one();
        return res;
    }
};