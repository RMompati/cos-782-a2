#include <tuple>
#include <memory>
#include <vector>

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

template<class T>
class AbstractSubject {
    public:
        virtual void registerObserver(std::shared_ptr<Observer<T>> observer) = 0;
        virtual void notifyObserver(const T& data) = 0;
        virtual ~AbstractSubject() {}
};

template<class T>
using ObserverList = vector<shared_ptr<AbstractObserver::Observer<T>>>;

template<class TypeList>
class Subject;

template<class... Ts>
class Subject<TypeList<Ts...>> : public AbstractSubject<Ts>... {
    tuple<ObserverList<Ts>...> observers;

    public:
        template<class T>
        void registerObserver(shared_ptr<Observer<T>> observer) override {
            auto& observerList = get<ObserverList<T>>(observers);
            observerList.push_back(observer);
        }

        template<class T>
        void notifyObservers(const T& data) override {
            auto& observerList = get<ObserverList<T>>(observers);
            for (auto& observer : observerList){
                observer->update(data);
            }
        }

        ~AbstractSubject() override{

        }
};

