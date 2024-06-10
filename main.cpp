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

// Stocks
// Stock update classes
class NaspersStock {
public:
    float price;
    explicit NaspersStock(float p) : price(p) {}
};

class SasolStock {
public:
    float price;
    explicit SasolStock(float p) : price(p) {}
};

// Observer that handles integer and string updates
class ConcreteObserver : public MultiTypeObserver<TypeList<NaspersStock, SasolStock>> {
private:
    string name;
public:
    ConcreteObserver(const string& observerName) : name(observerName) {}

    void update(const NaspersStock& data) override {
        cout << name << " has been notified that Naspers Stock price has changed to: " << data.price << endl;
    }

    void update(const SasolStock& data) override {
        cout << name << " has been notified that Sasol Stock price has changed to: " << data.price << endl;
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
    SubjectImplementation<NaspersStock> naspersSubject;
    SubjectImplementation<SasolStock> sasolSubject;

    auto John = make_shared<ConcreteObserver>("John");
    auto Steve = make_shared<ConcreteObserver>("Steve");

    naspersSubject.addObserver(John);
    sasolSubject.addObserver(John);
    sasolSubject.addObserver(Steve);

    naspersSubject.notifyAll(NaspersStock(2500.50));
    sasolSubject.notifyAll(SasolStock(320.75));

    return 0;
}
