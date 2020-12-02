#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <mutex>
#include <queue>
#include <vector>
#include <utility>
#include <memory>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <future>

class ThreadPool {
  private:
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> workThreads;
    std::condition_variable newTask;
    std::atomic<bool> finished;
    std::mutex mutex;
    size_t size;

  public:
    ThreadPool():
      finished(false),
      size(std::thread::hardware_concurrency()) {
        for (size_t i = 0; i < size; i++) {
          workThreads.push_back(std::thread([this] {
            this->threadFunction();
          }));
        }
    }

    explicit ThreadPool(size_t poolSize):
      finished(false),
      size(poolSize) {
        for (size_t i = 0; i < poolSize; i++) {
          workThreads.push_back(std::thread([this] {
            this->threadFunction();
          }));
        }
    }

    ~ThreadPool() {
      finished = true;
      newTask.notify_all();
      for (size_t i = 0; i < size; ++i) {
        workThreads[i].join();
      }
    }

    void threadFunction() {
      while (!finished) {
        std::unique_lock<std::mutex> lock(mutex);
        if (tasks.size() != 0) {
          auto task = std::move(tasks.front());
          tasks.pop();
          lock.unlock();
          task();
        } else {
          newTask.wait(lock);
        }
      }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
      auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
          ([func, args...]() {
        return func(args...);
      });
      auto result = task->get_future();
      tasks.push([task]() {
        (*task)();
      });
      newTask.notify_one();
      return result;
    }
};

#endif  // THREAD_POOL_HPP_
