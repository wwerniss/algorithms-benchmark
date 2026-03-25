#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>
#include <algorithm>

namespace core {
namespace sorting {

template<typename T>
class SelectionSort : public ISortStrategy<T> {
public:
    std::string getName() const override {
        return "Selection Sort";
    }

protected:
    void doSort(std::vector<T>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                std::swap(data[min_idx], data[i]);
                this->notifyObservers(data);
            }
        }
    }
};

} // namespace sorting
} // namespace core
