#include <gtest/gtest.h>
#include "sorting/QuickSort.h"
#include "sorting/MergeSort.h"

using namespace core::sorting;

TEST(SortingTests, QuickSortBasic) {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};
    std::vector<int> expected = {1, 2, 5, 5, 6, 9};

    QuickSort<int> qs;
    qs.sort(data);

    EXPECT_EQ(data, expected);
}

TEST(SortingTests, MergeSortBasic) {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};
    std::vector<int> expected = {1, 2, 5, 5, 6, 9};

    MergeSort<int> ms;
    ms.sort(data);

    EXPECT_EQ(data, expected);
}

TEST(SortingTests, EmptyArray) {
    std::vector<int> data = {};
    std::vector<int> expected = {};

    QuickSort<int> qs;
    qs.sort(data);
    EXPECT_EQ(data, expected);

    MergeSort<int> ms;
    ms.sort(data);
    EXPECT_EQ(data, expected);
}

TEST(SortingTests, AlreadySorted) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    QuickSort<int> qs;
    qs.sort(data);
    EXPECT_EQ(data, expected);
}
