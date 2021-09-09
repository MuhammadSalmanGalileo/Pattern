#pragma once
#include <list>
#include <iterator>
#include <Pollable.h>

class SyncDispatcher: public Pollable {
    protected:
        std::list<Pollable*> pollables;

    public:
        void addPollable(Pollable* pollable);
        void removePollable(Pollable *pollable);
        virtual void poll();
};