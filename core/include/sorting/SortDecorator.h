#pragma once

#include "sorting/ISortStrategy.h"
#include <vector>
#include <chrono>

namespace core {
namespace sorting {

template<typename T>
class SortTimerDecorator : public ISortStrategy<T> {
private:
    std::unique_ptr<ISortStrategy<T>> wrapped_;
    long long lastDurationMs_ = 0;

public:
    explicit SortTimerDecorator(std::unique_ptr<ISortStrategy<T>> wrapped)
        : wrapped_(std::move(wrapped)) {}

    void doSort(std::vector<T>& data) override {
        // We use doSort here to fit the Template Method, though the decorator wraps sort()
    }

    void sort(std::vector<T>& data) {
        auto start = std::chrono::high_resolution_clock::now();
        wrapped_->sort(data);
        auto end = std::chrono::high_resolution_clock::now();
        lastDurationMs_ = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    void addObserver(patterns::IObserver<T>* observer) {
        wrapped_->addObserver(observer);
    }

    void removeObserver(patterns::IObserver<T>* observer) {
        wrapped_->removeObserver(observer);
    }

    std::string getName() const override {
        return wrapped_->getName() + " (Timed)";
    }

    long long getLastDurationMs() const {
        return lastDurationMs_;
    }
};

} // namespace sorting
} // namespace core
