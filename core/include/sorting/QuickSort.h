#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>
#include <algorithm>

namespace core {
namespace sorting {

template<typename T>
class QuickSort : public ISortStrategy<T> {
public:
    void doSort(std::vector<T>& data) override {
        if (!data.empty()) {
            quickSort(data, 0, data.size() - 1);
        }
    }

    std::string getName() const override {
        return "Quick Sort";
    }

protected:
    // Template Method pattern can be applied here for selecting the pivot
    virtual int partition(std::vector<T>& data, int low, int high) {
        T pivot = data[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
                this->notifyObservers(data);
            }
        }
        std::swap(data[i + 1], data[high]);
        this->notifyObservers(data);
        return (i + 1);
    }

private:
    void quickSort(std::vector<T>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }
};

} // namespace sorting
} // namespace core
