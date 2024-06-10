#include "AbstractObserver.h"
#include <iostream>

using namespace std;

template<class T>
class AbstractObserver {
    public:
        virtual void update(const T& data) = 0;
        virtual ~Observer() {}
};

template<class T>
class ConcreteObserver : public AbstractObserver<T>{
    public:
        void update(const T& data) override {
            std::cout << "Update data: " << data << std::endl;
        }

        ~Observer(){
            
        }
};