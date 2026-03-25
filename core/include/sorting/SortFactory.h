#pragma once

#include "sorting/ISortStrategy.h"
#include "sorting/QuickSort.h"
#include "sorting/MergeSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/SelectionSort.h"
#include "sorting/InsertionSort.h"
#include <memory>
#include <string>

#include "sorting/SortDecorator.h"

namespace core {
namespace sorting {

class SortFactory {
public:
    template<typename T>
    static std::unique_ptr<SortTimerDecorator<T>> create(const std::string& type) {
        std::unique_ptr<ISortStrategy<T>> strategy;
        if (type == "QuickSort") {
            strategy = std::make_unique<QuickSort<T>>();
        } else if (type == "MergeSort") {
            strategy = std::make_unique<MergeSort<T>>();
        } else if (type == "BubbleSort") {
            strategy = std::make_unique<BubbleSort<T>>();
        } else if (type == "SelectionSort") {
            strategy = std::make_unique<SelectionSort<T>>();
        } else if (type == "InsertionSort") {
            strategy = std::make_unique<InsertionSort<T>>();
        }
        
        if (strategy) {
            return std::make_unique<SortTimerDecorator<T>>(std::move(strategy));
        }
        return nullptr;
    }
};

} // namespace sorting
} // namespace core
