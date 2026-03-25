#pragma once

#include "patterns/Memento.h"
#include <vector>
#include <any>

namespace core {
namespace sorting {

template<typename T>
class SortStateMemento : public patterns::Memento {
private:
    std::vector<T> state;
public:
    explicit SortStateMemento(const std::vector<T>& data) : state(data) {}
    
    std::any getState() const override {
        return state;
    }
    
    std::vector<T> getVector() const {
        return state;
    }
};

} // namespace sorting
} // namespace core
