#pragma once

#include "patterns/Command.h"
#include "sorting/SortMemento.h"
#include <vector>
#include <memory>
#include <functional>

namespace core {
namespace sorting {

template<typename T>
class StepCommand : public patterns::ICommand {
private:
    std::unique_ptr<SortStateMemento<T>> previousState;
    std::unique_ptr<SortStateMemento<T>> newState;
    std::function<void(const std::vector<T>&)> updateCallback;

public:
    StepCommand(const std::vector<T>& prev, const std::vector<T>& next, std::function<void(const std::vector<T>&)> cb)
        : previousState(std::make_unique<SortStateMemento<T>>(prev)),
          newState(std::make_unique<SortStateMemento<T>>(next)),
          updateCallback(cb) {}

    void execute() override {
        if (updateCallback) {
            updateCallback(newState->getVector());
        }
    }

    void undo() override {
        if (updateCallback) {
            updateCallback(previousState->getVector());
        }
    }
};

} // namespace sorting
} // namespace core
