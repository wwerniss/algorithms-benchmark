#pragma once

#include <vector>
#include <string>
#include <functional>
#include "patterns/Observer.h"

namespace core {
namespace sorting {

template<typename T>
class ISortStrategy : public core::patterns::IObservable<T> {
public:
    virtual ~ISortStrategy() = default;
    
    // Sorts the given data (Template Method shell could be here, but usually it's in a subclass)
    // We make sort non-virtual to establish a Template Method, and subclasses implement doSort.
    void sort(std::vector<T>& data) {
        this->notifyObservers(data); // Initial state
        doSort(data);
        this->notifyObservers(data); // Final state
    }

    // Optional callback for visualizing steps (Deprecated, use Observer)
    virtual void setStepCallback(std::function<void(const std::vector<T>&)> callback) {}

    // Returns the name of the algorithm
    virtual std::string getName() const = 0;

protected:
    virtual void doSort(std::vector<T>& data) = 0;
};

} // namespace sorting
} // namespace core
