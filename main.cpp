#include <tuple>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

// Define a typelist to store multiple types
template<typename... Types>
struct TypeList {};

// Base Observer Interface for handling updates of different types
class BaseObserver {
public:
    virtual ~BaseObserver() {}
};

// Templated Observer Interface
template<typename DataType>
class ObserverInterface : public BaseObserver {
public:
    virtual void update(const DataType& data) = 0;
};

// Concrete Observer that can observe multiple data types
template<typename TypeList>
class MultiTypeObserver;

// Specialization for TypeList
template<typename... Types>
class MultiTypeObserver<TypeList<Types...> > : public ObserverInterface<Types>... {
public:
    using ObserverInterface<Types>::update...;
};

// Observer that handles integer and string updates
class ConcreteObserver : public MultiTypeObserver<TypeList<int, string> > {
public:
    void update(const int& data) override {
        cout << "Integer update: " << data << endl;
    }

    void update(const string& data) override {
        cout << "String update: " << data << endl;
    }
};

// Subject interface
template<typename DataType>
class SubjectInterface {
public:
    virtual void addObserver(std::shared_ptr<ObserverInterface<DataType> > observer) = 0;
    virtual void notifyAll(const DataType& data) = 0;
    virtual ~SubjectInterface() {}
};

// Concrete subject implementation
template<typename DataType>
class SubjectImplementation : public SubjectInterface<DataType> {
    vector<shared_ptr<ObserverInterface<DataType> > > observers;

public:
    void addObserver(shared_ptr<ObserverInterface<DataType> > observer) override {
        observers.push_back(observer);
    }

    void notifyAll(const DataType& data) override {
        for (auto& observer : observers) {
            observer->update(data);
        }
    }
};

int main() {
    SubjectImplementation<int> intSubject;
    SubjectImplementation<string> stringSubject;

    auto observer = make_shared<ConcreteObserver>();

    intSubject.addObserver(observer);
    stringSubject.addObserver(observer);

    intSubject.notifyAll(42);
    stringSubject.notifyAll("Hello, world!");

    return 0;
}
