#pragma once

template <typename T>
class Operation {
    public:
        virtual bool invoke(T data) = 0;
};

template <typename T, typename U>
class Adapter: Operation<T> {
    protected:
        Operation<U> *next;
        
        bool invokeNext(U data) {
            if(next == nullptr) {
                return false;
            };
            return next->invoke(data);
        };
    public:
        Adapter(): next(nullptr) {};
        void setNext(Operation<U> *operation) {
            next = operation;
        };
};

template <typename T>
class Pipeline: public Adapter<T, T> {};