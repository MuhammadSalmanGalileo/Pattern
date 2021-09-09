#pragma once

#include <list>
#include <iterator>
#include <functional>

class Observable;

class Observer {
  public:
    virtual void update(Observable *source) = 0;
};

class Observable {
    protected:
        std::list<Observer*> observers;
        void updateObservers() {
            std::list<Observer*>::iterator it;
            for(it = observers.begin(); it != observers.end(); ++it) {
                (*it)->update(this);
            }
        };
    public:
        void addObserver(Observer *observer) {
            observers.push_front(observer);
        };
        void removeObserver(Observer *observer) {
            observers.remove(observer);
        };
};

template <typename T>
class State {
    public:
        virtual T getState() = 0;
};

template <typename T>
class ObservableState: public Observable, public State<T> {};

template <typename T>
class ObserverFunction: public Observer {
    private:
        ObservableState<T> *_source;
        std::function<void(T)> _func;
    public:
        ObserverFunction(ObservableState<T> *source, std::function<void(T)> func): 
            _source(source), _func(func){}
        
        virtual void update(Observable *source) {
            if(_source == source) {
                _func(_source->getState());
            }
        };
};