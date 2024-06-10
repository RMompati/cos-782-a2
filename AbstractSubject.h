#ifndef ABSTRACTSUBJECT_H
#define ABSTRACTSUBJECT_H
#include "AbstractObserver.h"
#include <vector>

using namespace std;

template<class T>
class AbstractSubject {
    private:
        vector<shared_ptr<AbstractObserver<T>>> ObserverList; 

    public:
        virtual void registerObserver(std::shared_ptr<Observer<T>> observer) = 0;
        virtual void notifyObserver(const T& data) = 0;
        virtual ~AbstractSubject() {}
};

#endif