#pragma once
#include <list>
#include <functional>

class Pollable {
    public:
        virtual void poll() = 0;
};

class PollableFunction: public Pollable {
    private:
        std::function<void(void)> func;
    public:
        PollableFunction(std::function<void(void)> func): func(func) {};
        virtual void poll() {
            func();
        };
};

template<class T>
class TIntervalPollable: public Pollable {
    private:
        bool _first;
        T _lastTime;
        const T _interval;
        const std::function<T(void)> _timeFunc;
    protected:
        virtual void intervalPoll() = 0;
    public:
        TIntervalPollable(T interval, std::function<T(void)> timeFunc): 
            _first(true), _interval(interval), _timeFunc(timeFunc) {
            _lastTime = _timeFunc();
        }

        virtual void poll() {
            T currentTime = _timeFunc();
            if((currentTime - _lastTime >= _interval) || _first) {
                _first = false;
                _lastTime = currentTime;
                intervalPoll();
            }
        }
};

using IntervalPollable = TIntervalPollable<unsigned long>;