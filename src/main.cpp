#include <tuple>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Define a typelist to store multiple types
template<typename... Types>
struct TypeList {};

// Base Observer Interface for handling updates of different types
class BaseObserver {
public:
    virtual void updateName(const string& name) = 0;
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
    string observerName;
    
public:
    ConcreteObserver(const string& name) : observerName(name) {}

    void update(const NaspersStock& data) override {
        cout << observerName << " has been notified that Naspers Stock price has changed to: " << data.price << endl;
    }

    void update(const SasolStock& data) override {
        cout << observerName << " has been notified that Sasol Stock price has changed to: " << data.price << endl;
    }

    void updateName(const string& name) override {
        observerName = name;
        cout << "Observer name updated to: " << observerName << endl;
    }
};

// Subject interface
template<typename DataType>
class SubjectInterface {
public:
    virtual void addObserver(std::shared_ptr<ObserverInterface<DataType> > observer) = 0;
    virtual void removeObserver(std::shared_ptr<ObserverInterface<DataType>> observer) = 0;
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

    void removeObserver(shared_ptr<ObserverInterface<DataType>> observer) override {
        observers.erase(
        remove_if(observers.begin(), observers.end(),
                    [&observer](const shared_ptr<ObserverInterface<DataType>>& element) {
                        return element == observer;
                    }),
        observers.end());
    }

    void notifyAll(const DataType& data) override {
        for (auto& observer : observers) {
            observer->update(data);
        }
    }
};

int main() {
    // Stock Exchange Example
    SubjectImplementation<NaspersStock> naspersSubject;
    SubjectImplementation<SasolStock> sasolSubject;

    auto John = make_shared<ConcreteObserver>("John");
    auto Steve = make_shared<ConcreteObserver>("Steve");

    cout << endl << "Adding Steve to Observe Sasol";
    cout << endl << "Adding John to Observe Sasol";
    cout << endl << "Adding John to Observe naspers" << endl << endl;

    naspersSubject.addObserver(John);
    sasolSubject.addObserver(Steve);
    sasolSubject.addObserver(John);

    cout << "Stocks changing price" << endl << endl;
    naspersSubject.notifyAll(NaspersStock(2500.50));
    sasolSubject.notifyAll(SasolStock(320.75));

    cout << endl << "Removing Steve from Observing Sasol" << endl << endl;

    sasolSubject.removeObserver(Steve);

    cout << "Stocks changing price" << endl << endl;
    naspersSubject.notifyAll(NaspersStock(2570.50));
    sasolSubject.notifyAll(SasolStock(302.75));
    return 0;
}
