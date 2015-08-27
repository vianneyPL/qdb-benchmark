#pragma once

#include <condition_variable>
#include <mutex>

namespace utils
{
class master_slave_barrier
{
public:
    master_slave_barrier(int slaves) : _slaves(slaves), _ready_slaves(0), _waking_slaves(0)
    {
    }

    void wait_slaves()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [=]
                 {
                     return _ready_slaves == _slaves;
                 });
        _ready_slaves = 0;
    }

    template <class Rep, class Period>
    bool wait_slaves_for(const std::chrono::duration<Rep, Period> & rel_time)
    {
        std::unique_lock<std::mutex> lock(_mutex);
        bool ok = _cv.wait_for(lock, rel_time, [=]
                               {
                                   return _ready_slaves == _slaves;
                               });
        if (!ok) return false;
        _ready_slaves = 0;
        return true;
    }

    void notify_master()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _ready_slaves++;
        lock.unlock();
        _cv.notify_all();
    }

    void wait_master()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [=]
                 {
                     return _waking_slaves > 0;
                 });
        _waking_slaves--;
    }

    void notify_slaves()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _waking_slaves = _slaves;
        lock.unlock();
        _cv.notify_all();
    }

private:
    std::condition_variable _cv;
    std::mutex _mutex;
    int _slaves, _ready_slaves, _waking_slaves;
};
}