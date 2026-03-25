/**
 * @file Memento.h
 * @brief Interfaces for the Memento design pattern for capturing and restoring object states.
 */

#pragma once

#include <memory>
#include <any>

namespace core {
namespace patterns {

/**
 * @class Memento
 * @brief Stores the internal state of an Originator object.
 *
 * This opaque object acts as a snapshot of state that can be used later to restore 
 * the Originator to its previous condition (e.g., for Undo operations).
 */
class Memento {
public:
    virtual ~Memento() = default;

    /**
     * @brief Retrieves the encapsulated state.
     * @return std::any representing the internal state data.
     */
    virtual std::any getState() const = 0;
};

/**
 * @class IOriginator
 * @brief Interface for objects that can create and restore from Mementos.
 */
class IOriginator {
public:
    virtual ~IOriginator() = default;

    /**
     * @brief Saves the current state inside a Memento object.
     * @return A unique pointer to the created Memento.
     */
    virtual std::unique_ptr<Memento> saveState() const = 0;

    /**
     * @brief Restores the object's state from a Memento.
     * @param memento The Memento containing the state to restore.
     */
    virtual void restoreState(const Memento& memento) = 0;
};

} // namespace patterns
} // namespace core
