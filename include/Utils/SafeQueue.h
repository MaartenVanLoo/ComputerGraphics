
#ifndef JOMAMATCHMAKING_SAFEQUEUE_H
#define JOMAMATCHMAKING_SAFEQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

template<typename T>
class SafeQueue{
public:
    virtual ~SafeQueue() {
        terminate = true;
        popCV.notify_all();
    }

    void push(T& elem){
        if (elem == nullptr){
            std::cout << "NULL\n";
        }
        queueLock.lock();
        queue.push(elem);
        queueLock.unlock();
        popCV.notify_one();
    }
    T pop(){
        std::unique_lock<std::mutex> guard(queueLock);
        while (queue.empty()){
            popCV.wait(guard);
            if (terminate) return nullptr;
        }
        T elem= queue.front();
        queue.pop();
        return elem;
    }
    bool try_pop(T& elem){
        std::unique_lock<std::mutex> guard(queueLock);
        if (this->queue.empty()){
            return false;
        }
        elem = queue.front();
        queue.pop();
        return true;
    }

    bool wait_and_pop(T& elem){
        std::unique_lock<std::mutex> guard(queueLock);
        while (this->queue.empty()){
            popCV.wait(guard);
            if (terminate)
                return false;
        }
        elem = queue.front();
        queue.pop();
        return true;
    }
    bool wait_for_pop(T& elem, const std::chrono::duration<std::chrono::milliseconds>& rel_time){
        std::unique_lock<std::mutex> guard(queueLock);
        while (this->queue.empty()){
            if (popCV.wait_for(guard, rel_time) == std::cv_status::timeout){
                return false;
            }
            if (terminate) return false;
        }
        elem = queue.front();
        queueLock.unlock();
    }

    bool empty() const{
        std::lock_guard<std::mutex> guard(queueLock);
        return this->queue.empty();
    }

    ///Get size of queue, note this value is NOT threadsafe and thus can be wrong
    bool size() const{
        return this->queue.size();
    }

    ///Releases all threads without popping data
    void terminateQueue(){
        terminate = true;
        popCV.notify_all();
    }
private:
    std::mutex queueLock;
    std::condition_variable popCV;
    std::queue<T> queue;

    bool terminate = std::atomic<bool>(false);
};
#endif //JOMAMATCHMAKING_SAFEQUEUE_H
