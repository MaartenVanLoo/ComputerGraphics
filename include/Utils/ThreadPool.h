//
// Created by Maarten Van Loo on 14/01/2022.
//

#ifndef DEBUG
#define DEBUG false
#endif

#ifndef JOMAMATCHMAKING_THREADPOOL_H
#define JOMAMATCHMAKING_THREADPOOL_H
#include "SafeQueue.h"
#include <type_traits>
#include <atomic>
#include <sstream>
#include <sstream>
#include <iomanip> //getTime
#include "config.h"

template <typename  Result>
class Task{
public:
    virtual void run() = 0;
    Result getResult(){
        return result;
    }
private:
    Result result;
};
template <>
class Task<void>{
public:
    virtual void run() = 0;
    void getResult() = delete;
};


//https://hoani.net/posts/guides/2020-12-03-cppTemplates/
template <class Result, typename PoolTask, typename = std::enable_if_t<std::is_base_of<Task<Result>,PoolTask>::value>>
class ThreadPool {
private:
    static std::string getTime(){
        using namespace std::chrono;

        // get current time
        auto now = system_clock::now();

        // get number of milliseconds for the current second
        // (remainder after division into seconds)
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        // convert to std::time_t in order to convert to std::tm (broken time)
        auto timer = system_clock::to_time_t(now);

        // convert to broken time
        std::tm bt;
        localtime_s(&bt, &timer);

        std::ostringstream oss;

        oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return oss.str();
    }

    template<typename PoolTask>
    class Worker{
    public:
        Worker() = delete;
        explicit Worker(ThreadPool* pool, int idx){
            this->pool = pool;
            this->idx = idx;
        }

        virtual ~Worker() {
            this->alive = false;
            //wait till done before removing task pointer!
            //delete task;
        }

        void start(){
            std::stringstream ss;
            while (this->alive){
                if(pool->taskQueue.wait_and_pop(task)){
                    running = true;
                    task->run();
                    pool->completeTasksQueue.push(task);
                    running = false;

                    #if DEBUG
                        std::string time = ThreadPool::getTime();
                        ss << "[" << time << "] " << "Hello from " << idx << "\n";
                        std::cout << ss.str();
                        ss.str("");
                    #endif
                }
            }
            done = true;
        };
        void stop(){
            this->alive = false;
        }
        bool isRunning(){
            return running;
        }
    private:
        PoolTask* task = nullptr;
        ThreadPool* pool;
        int idx = -1;
        bool alive = std::atomic<bool>(true);
        bool running;
        bool done = false;
    };

public:
    ThreadPool(int processor_count = -1){
        if (processor_count == -1){
            processor_count = (int)std::thread::hardware_concurrency();
        }
        //may return 0 when not able to detect std::thread::hardware_concurrency()
        if (processor_count == 0){
            processor_count = 2; //make 2 workers by default
        }

        //preallocate memory to avoid resizing and losing references to workers?
        this->workers.reserve(processor_count);
        this->threads.reserve(processor_count);
        for (int idx = 0; idx < processor_count; idx++){
            this->workers.emplace_back(this,idx);                                            //Create workers
            this->threads.push_back(std::thread(&Worker<PoolTask>::start,&workers.back()));   //Start workers
        }
    };

    virtual ~ThreadPool() {
        terminate();
    }

    void pushTaskQueue(PoolTask* task){
        taskQueue.push(task);
    }
    PoolTask* popCompleteQueue(PoolTask* task){
        completeTasksQueue.wait_and_pop(task);
        return task;
    }

    PoolTask* getResult(){
        return std::move(completeTasksQueue.pop());
    }

    int runningWorkers(){
        int count = 0;
        for (auto& w: workers){
            if (w.isRunning()){
                count++;
            }
        }
        return count;
    }
    int queuedTasks(){
        return taskQueue.size();
    }
    int completedTasks(){
        return completeTasksQueue.size();
    }
    bool hasCompletedTasks(){
        return !completeTasksQueue.empty();
    }
    bool hasQueuedTasks(){
        return !taskQueue.empty();
    }
    int getWorkerCount(){
        return (int)workers.size();
    }

    void terminate(){
        for (int i = 0; i < this->workers.size(); i++){
            this->workers[i].stop();
        }
        taskQueue.terminateQueue();
        completeTasksQueue.terminateQueue();
        for (int i = 0; i < this->threads.size(); i++){
            if (this->threads[i].joinable()){
                this->threads[i].join();
            }
        }
    }
private:
    std::vector<std::thread> threads;
    std::vector<Worker<PoolTask>> workers;
    SafeQueue<PoolTask*> taskQueue;
    SafeQueue<PoolTask*> completeTasksQueue;
    friend class Worker<PoolTask>;
};




#endif //JOMAMATCHMAKING_THREADPOOL_H
