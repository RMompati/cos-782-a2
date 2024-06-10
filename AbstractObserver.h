#ifndef ABSTRACTOBSERVER_H
#define ABSTRACTOBSERVER_H

using namespace std;

template<class T>
class AbstractObserver {
    public:
        virtual void update(const T& data) = 0;
        virtual ~Observer() {}
};

#endif