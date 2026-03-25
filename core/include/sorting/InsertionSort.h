#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>

namespace core {
namespace sorting {

template<typename T>
class InsertionSort : public ISortStrategy<T> {
public:
    std::string getName() const override {
        return "Insertion Sort";
    }

protected:
    void doSort(std::vector<T>& data) override {
        int n = data.size();
        for (int i = 1; i < n; i++) {
            T key = data[i];
            int j = i - 1;

            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j = j - 1;
                this->notifyObservers(data);
            }
            data[j + 1] = key;
            this->notifyObservers(data);
        }
    }
};

} // namespace sorting
} // namespace core
