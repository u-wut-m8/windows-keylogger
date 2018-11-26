#pragma once

#include<chrono>
#include<thread>

class Timer{
private:
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L, repeat_count = -1L;
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;

    void SleepAndRun(){
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();
    }

    void ThreadFunc(){
        if(CallNumber == Infinite)
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
                SleepAndRun();
    }

public:
    static const long Infinite = -1L;

    Timer(){}
    Timer(const std::function<void(void)> &f) : funct(f){}
    Timer(const std::function<void(void)> &f,
         const unsigned long &i,
         const long repeat = Timer::Infinite) : funct(f), interval(std::chrono::milliseconds(i)), CallNumber(repeat) {}
    void Start(bool Async = true){
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }

    inline void Stop(){
        Alive = false;
        Thread.join();
    }

    inline void SetFunction(const std::function<void(void)> &f){funct = f;}

    inline bool IsAlive() const {return Alive;}

    void RepeatCount(const long r){
        if(Alive)
            return;
        CallNumber = r;
    }

    inline long GetLeftCount() const {return repeat_count;}

    inline long RepeatCount() const {return CallNumber;}

    void SetInterval(const unsigned long &i){
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }

    inline unsigned long Interval() const {return interval.count();}

    inline const std::function<void(void)> &Function() const {return funct;}
};
