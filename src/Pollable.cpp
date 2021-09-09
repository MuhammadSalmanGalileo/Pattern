#include "Pollable.h"

void IntervalPollable::poll() {
    unsigned long currentTime = _timeFunc();
    if((currentTime - _lastTime >= _interval) || _first) {
        _first = false;
        _lastTime = currentTime;
        intervalPoll();
    }
}