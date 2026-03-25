/**
 * @file Observer.h
 * @brief Interfaces for the Observer design pattern.
 */

#pragma once

#include <vector>

namespace core {
namespace patterns {

/**
 * @brief Observer interface that receives updates from an Observable.
 * @tparam T The type of data contained in the update.
 */
template<typename T>
class IObserver {
public:
    virtual ~IObserver() = default;

    /**
     * @brief Callback method invoked when the state of the Observable changes.
     * @param data The new state of the data.
     */
    virtual void onUpdate(const std::vector<T>& data) = 0;
};

/**
 * @brief Observable base class that notifies registered observers of state changes.
 * @tparam T The type of data being observed.
 */
template<typename T>
class IObservable {
protected:
    std::vector<IObserver<T>*> observers; ///< List of registered observers

public:
    virtual ~IObservable() = default;

    /**
     * @brief Registers an observer to receive updates.
     * @param observer Pointer to the observer object.
     */
    void addObserver(IObserver<T>* observer) {
        observers.push_back(observer);
    }

    /**
     * @brief Unregisters a previously registered observer.
     * @param observer Pointer to the observer object to remove.
     */
    void removeObserver(IObserver<T>* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    /**
     * @brief Notifies all registered observers of a state change.
     * @param data The new state of the data.
     */
    void notifyObservers(const std::vector<T>& data) {
        for (auto* obs : observers) {
            obs->onUpdate(data);
        }
    }
};

} // namespace patterns
} // namespace core
