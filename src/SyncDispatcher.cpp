#include "SyncDispatcher.h"

void SyncDispatcher::addPollable(Pollable* pollable) {
    pollables.push_front(pollable);
};

void SyncDispatcher::removePollable(Pollable *pollable) {
    pollables.remove(pollable);
};

void SyncDispatcher::poll() {
    std::list<Pollable*>::iterator it;
    for(it = pollables.begin(); it != pollables.end(); ++it) {
        (*it)->poll();
    }
};