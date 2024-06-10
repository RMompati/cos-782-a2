#include <tuple>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

template<class... Ts>
struct TypeList {};

template<class T>
class AbstractObserver {
    public:
        virtual void update(const T& data) = 0;
        virtual ~AbstractObserver() {}
};

template<class T>
class ConcreteObserver : public AbstractObserver<T>{
    public:
        void update(const T& data) override {
            cout << "Update data: " << data << endl;
        }
};

template<class T>
class AbstractSubject {
    public:
        virtual void registerObserver(std::shared_ptr<AbstractObserver<T> > observer) = 0;
        virtual void notifyObservers(const T& data) = 0;
        virtual ~AbstractSubject() {}
};

template<class T>
using ObserverList = vector< shared_ptr <AbstractObserver<T> > >;

template<class TypeList>
class Subject;

template<class T>
class Subject : public AbstractSubject<T> {
    ObserverList<T> observers;

    public:
        void registerObserver(shared_ptr< AbstractObserver<T> > observer) override {
            // auto& observerList = get<ObserverList<T> >(observers);
            observers.push_back(observer);
        }

        void notifyObservers(const T& data) override {
            // auto& observerList = get<ObserverList<T> >(observers);
            for (auto& observer : observers){
                observer->update(data);
            }
        }
};

int main() {
    Subject<string> subject;

    auto intObserver = make_shared<ConcreteObserver<string> >();
    auto itObserver = make_shared<ConcreteObserver<string> >();

    subject.registerObserver(intObserver);
    subject.registerObserver(itObserver);

    subject.notifyObservers("43");

    return 0;
}
