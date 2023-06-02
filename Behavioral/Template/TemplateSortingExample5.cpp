#include <iostream>
#include <vector>

class Sorter {
public:
    // Template method that sorts an array of integers using the selected algorithm
    void sort(std::vector<int>& arr) {
        doSort(arr);
    }

protected:
    // Protected virtual method that performs the actual sorting algorithm
    virtual void doSort(std::vector<int>& arr) = 0;
};

class BubbleSorter : public Sorter {
protected:
    // Implementation of the bubble sort algorithm
    void doSort(std::vector<int>& arr) override {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
};

class MergeSorter : public Sorter {
protected:
    // Implementation of the merge sort algorithm
    void doSort(std::vector<int>& arr) override {
        if (arr.size() < 2) {
            return;
        }

        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        MergeSorter().sort(left);
        MergeSorter().sort(right);

        std::merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
    }
};

class QuickSorter : public Sorter {
protected:
    // Implementation of the quicksort algorithm
    void doSort(std::vector<int>& arr) override {
        if (arr.size() < 2) {
            return;
        }

        int pivot = arr[0];
        std::vector<int> left, right;

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < pivot) {
                left.push_back(arr[i]);
            }
            else {
                right.push_back(arr[i]);
            }
        }

        QuickSorter().sort(left);
        QuickSorter().sort(right);

        std::copy(left.begin(), left.end(), arr.begin());
        arr[left.size()] = pivot;
        std::copy(right.begin(), right.end(), arr.begin() + left.size() + 1);
    }
};

int main() {
    // Sort the array using bubble sort
    std::vector<int> arr1 = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    BubbleSorter().sort(arr1);
    for (int i : arr1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Sort the array using merge sort
    std::vector<int> arr2 = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    MergeSorter().sort(arr2);
    for (int i : arr2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    // Sort the array using quick sort
    std::vector<int> arr3 = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    QuickSorter().sort(arr3);
    for (int i : arr3) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


}