#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>

namespace core {
namespace sorting {

template<typename T>
class MergeSort : public ISortStrategy<T> {
public:
protected:
    void doSort(std::vector<T>& data) override {
        if (data.size() > 1) {
            mergeSort(data, 0, data.size() - 1);
        }
    }

public:
    std::string getName() const override {
        return "Merge Sort";
    }

private:
    void merge(std::vector<T>& data, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<T> L(n1);
        std::vector<T> R(n2);

        for (int i = 0; i < n1; i++) L[i] = data[left + i];
        for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                data[k++] = L[i++];
            } else {
                data[k++] = R[j++];
            }
            this->notifyObservers(data);
        }

        while (i < n1) {
            data[k++] = L[i++];
            this->notifyObservers(data);
        }
        while (j < n2) {
            data[k++] = R[j++];
            this->notifyObservers(data);
        }
    }

    void mergeSort(std::vector<T>& data, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
};

} // namespace sorting
} // namespace core
