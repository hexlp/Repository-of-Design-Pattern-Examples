#include <iostream>
#include <vector>

// Perform a linear search on a vector of integers
int linearSearch(const std::vector<int>& arr, int target) {
    // Add a sentinel value at the end of the vector
    arr.push_back(target);

    int index = 0;
    while (arr[index] != target) {
        index++;
    }

    // Remove the sentinel value
    arr.pop_back();

    if (index == arr.size()) {
        // Sentinel value found, indicating target not found
        return -1;
    }

    // Return the index of the target value
    return index;
}

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    int target1 = 30;
    int result1 = linearSearch(numbers, target1);
    if (result1 != -1) {
        std::cout << "Target " << target1 << " found at index " << result1 << std::endl;
    } else {
        std::cout << "Target " << target1 << " not found" << std::endl;
    }

    int target2 = 60;
    int result2 = linearSearch(numbers, target2);
    if (result2 != -1) {
        std::cout << "Target " << target2 << " found at index " << result2 << std::endl;
    } else {
        std::cout << "Target " << target2 << " not found" << std::endl;
    }

    return 0;
}
