#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>
#include <algorithm>

namespace core {
namespace sorting {

template<typename T>
class BubbleSort : public ISortStrategy<T> {
public:
    std::string getName() const override {
        return "Bubble Sort";
    }

protected:
    void doSort(std::vector<T>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                    this->notifyObservers(data);
                }
            }
        }
    }
};

} // namespace sorting
} // namespace core
