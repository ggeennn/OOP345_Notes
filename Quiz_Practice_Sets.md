# OOP345 NBB - Quiz Practice Sets

This document contains three practice quiz sets designed to cover key concepts from the `NBB\07-Sep29` and `NBB\08-Oct02` folders, specifically focusing on custom exceptions, function pointers, and lambda expressions as per the quiz details.

---

## Common Function Signature for Function Pointers:
`bool (*ValidationLogic)(int data_item, int threshold, std::string& error_message)`
This signature represents a function that takes a data item, a threshold, and an output string for error messages. It returns `true` if the validation passes, `false` otherwise.

---

## Quiz Set 1: Data Range Validation

### Task Description:
Implement a system to validate data items against a specified range.

1.  **Custom Exception Class**: Create a custom exception class named `OutOfRangeException` that inherits from `std::exception`. Its `what()` method should return a descriptive message.
2.  **Data Processing Function**: Write a templated function `processData` with the following signature:
    ```cpp
    template<typename Func1, typename Func2>
    void processData(int* data_array, int size, int lower_bound, int upper_bound, Func1 validator1, Func2 validator2);
    ```
    This function should iterate through `data_array`. For each item, it first calls `validator1` with the item and `lower_bound`, then calls `validator2` with the item and `upper_bound`. If either validator indicates a failure (by returning `false` and setting an error message), `processData` should throw an `OutOfRangeException` with the collected error message.
3.  **Main Function (`try/catch` Block)**: In `main`, define an integer array.
    *   Define a regular function `checkLowerBound` that matches the common function signature and checks if `data_item >= threshold`.
    *   Define a lambda expression `checkUpperBound` that matches the common function signature and checks if `data_item <= threshold`.
    *   Call `processData` within a `try/catch` block, passing `checkLowerBound` as `validator1` and your `checkUpperBound` lambda as `validator2`. Catch `OutOfRangeException` and print its message.

### Concepts Covered:
*   Custom Exception (`std::exception` inheritance)
*   Function Pointers (passing regular functions)
*   Lambda Expressions (defining and passing lambdas)
*   Templates (generic function `processData`)
*   Exception Handling (`try/catch`, `throw`)
*   Input Validation Logic

### Example Code Structure:

```cpp
#include <iostream>
#include <string>
#include <vector> // Using vector for easier data management, but array is also fine

// 1. Custom Exception Class
class OutOfRangeException : public std::exception {
private:
    std::string message;
public:
    OutOfRangeException(const std::string& msg) : message("Error: " + msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Common Function Signature: bool (*ValidationLogic)(int data_item, int threshold, std::string& error_message)

// Provided Function (for validator1)
bool checkLowerBound(int data_item, int threshold, std::string& error_message) {
    if (data_item >= threshold) {
        return true;
    } else {
        error_message = "Data item " + std::to_string(data_item) + " is below lower bound " + std::to_string(threshold) + ".";
        return false;
    }
}

// 2. Data Processing Function
template<typename Func1, typename Func2>
void processData(int* data_array, int size, int lower_bound, int upper_bound, Func1 validator1, Func2 validator2) {
    std::string error_msg;
    for (int i = 0; i < size; ++i) {
        if (!validator1(data_array[i], lower_bound, error_msg)) {
            throw OutOfRangeException(error_msg);
        }
        if (!validator2(data_array[i], upper_bound, error_msg)) {
            throw OutOfRangeException(error_msg);
        }
        std::cout << "Item " << data_array[i] << " passed validation." << std::endl;
    }
}

int main() {
    int data[] = { 20, 50, 5, 80, 30 };
    int size = sizeof(data) / sizeof(data[0]);
    int lower = 10;
    int upper = 70;

    // Lambda Expression (for validator2)
    auto checkUpperBound = [](int data_item, int threshold, std::string& error_message) -> bool {
        if (data_item <= threshold) {
            return true;
        } else {
            error_message = "Data item " + std::to_string(data_item) + " is above upper bound " + std::to_string(threshold) + ".";
            return false;
        }
    };

    std::cout << "--- Quiz Set 1: Data Range Validation ---" << std::endl;
    try {
        processData(data, size, lower, upper, checkLowerBound, checkUpperBound);
        std::cout << "All data processed successfully." << std::endl;
    } catch (const OutOfRangeException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with an out-of-range value ---" << std::endl;
    int data_fail[] = { 20, 5, 50 }; // 5 is out of lower bound
    int size_fail = sizeof(data_fail) / sizeof(data_fail[0]);
    try {
        processData(data_fail, size_fail, lower, upper, checkLowerBound, checkUpperBound);
        std::cout << "All data processed successfully." << std::endl;
    } catch (const OutOfRangeException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with another out-of-range value ---" << std::endl;
    int data_fail2[] = { 20, 80, 50 }; // 80 is out of upper bound
    int size_fail2 = sizeof(data_fail2) / sizeof(data_fail2[0]);
    try {
        processData(data_fail2, size_fail2, lower, upper, checkLowerBound, checkUpperBound);
        std::cout << "All data processed successfully." << std::endl;
    } catch (const OutOfRangeException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## Quiz Set 2: Even/Odd and Divisibility Check

### Task Description:
Implement a system to check data items for even/odd properties and divisibility.

1.  **Custom Exception Class**: Create a custom exception class named `ValidationFailedException` that inherits from `std::exception`. Its `what()` method should return a descriptive message.
2.  **Data Processing Function**: Write a templated function `analyzeNumbers` with the following signature:
    ```cpp
    template<typename CheckFunc1, typename CheckFunc2>
    void analyzeNumbers(int* numbers_array, int count, int divisor, CheckFunc1 checker1, CheckFunc2 checker2);
    ```
    This function should iterate through `numbers_array`. For each item, it first calls `checker1` (e.g., to check if even/odd) and then `checker2` (e.g., to check divisibility by `divisor`). If either checker indicates a failure, `analyzeNumbers` should throw a `ValidationFailedException` with the collected error message.
3.  **Main Function (`try/catch` Block)**: In `main`, define an integer array.
    *   Define a regular function `isEven` that matches the common function signature (you can ignore the `threshold` parameter or use it for a specific purpose, e.g., `threshold=0` for even check). It checks if `data_item` is even.
    *   Define a lambda expression `isDivisibleBy` that matches the common function signature and checks if `data_item` is divisible by `threshold` (which will be `divisor`).
    *   Call `analyzeNumbers` within a `try/catch` block, passing `isEven` as `checker1` and your `isDivisibleBy` lambda as `checker2`. Catch `ValidationFailedException` and print its message.

### Concepts Covered:
*   Custom Exception (`std::exception` inheritance)
*   Function Pointers (passing regular functions)
*   Lambda Expressions (defining and passing lambdas, potentially capturing `divisor`)
*   Templates (generic function `analyzeNumbers`)
*   Exception Handling (`try/catch`, `throw`)
*   Modular Arithmetic

### Example Code Structure:

```cpp
#include <iostream>
#include <string>
#include <vector>

// 1. Custom Exception Class
class ValidationFailedException : public std::exception {
private:
    std::string message;
public:
    ValidationFailedException(const std::string& msg) : message("Validation Error: " + msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Common Function Signature: bool (*ValidationLogic)(int data_item, int threshold, std::string& error_message)

// Provided Function (for checker1)
bool isEven(int data_item, int /*threshold - ignored*/, std::string& error_message) {
    if (data_item % 2 == 0) {
        return true;
    } else {
        error_message = "Data item " + std::to_string(data_item) + " is odd.";
        return false;
    }
}

// 2. Data Processing Function
template<typename CheckFunc1, typename CheckFunc2>
void analyzeNumbers(int* numbers_array, int count, int divisor, CheckFunc1 checker1, CheckFunc2 checker2) {
    std::string error_msg;
    for (int i = 0; i < count; ++i) {
        // Check for even/odd
        if (!checker1(numbers_array[i], 0, error_msg)) { // threshold 0 is ignored for isEven
            throw ValidationFailedException(error_msg);
        }
        // Check for divisibility
        if (!checker2(numbers_array[i], divisor, error_msg)) {
            throw ValidationFailedException(error_msg);
        }
        std::cout << "Number " << numbers_array[i] << " passed analysis (even and divisible by " << divisor << ")." << std::endl;
    }
}

int main() {
    int numbers[] = { 10, 20, 15, 30, 40 };
    int count = sizeof(numbers) / sizeof(numbers[0]);
    int div = 5;

    // Lambda Expression (for checker2)
    auto isDivisibleBy = [](int data_item, int threshold, std::string& error_message) -> bool {
        if (data_item % threshold == 0) {
            return true;
        } else {
            error_message = "Data item " + std::to_string(data_item) + " is not divisible by " + std::to_string(threshold) + ".";
            return false;
        }
    };

    std::cout << "--- Quiz Set 2: Even/Odd and Divisibility Check ---" << std::endl;
    try {
        analyzeNumbers(numbers, count, div, isEven, isDivisibleBy);
        std::cout << "All numbers analyzed successfully." << std::endl;
    } catch (const ValidationFailedException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with an odd number ---" << std::endl;
    int numbers_fail[] = { 10, 7, 20 }; // 7 is odd
    int count_fail = sizeof(numbers_fail) / sizeof(numbers_fail[0]);
    try {
        analyzeNumbers(numbers_fail, count_fail, div, isEven, isDivisibleBy);
        std::cout << "All numbers analyzed successfully." << std::endl;
    } catch (const ValidationFailedException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with a non-divisible number ---" << std::endl;
    int numbers_fail2[] = { 10, 20, 22 }; // 22 is not divisible by 5
    int count_fail2 = sizeof(numbers_fail2) / sizeof(numbers_fail2[0]);
    try {
        analyzeNumbers(numbers_fail2, count_fail2, div, isEven, isDivisibleBy);
        std::cout << "All numbers analyzed successfully." << std::endl;
    } catch (const ValidationFailedException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## Quiz Set 3: Positive Value and Custom Threshold Check

### Task Description:
Implement a system to ensure data items are positive and meet a custom threshold.

1.  **Custom Exception Class**: Create a custom exception class named `DataIntegrityException` that inherits from `std::exception`. Its `what()` method should return a descriptive message.
2.  **Data Processing Function**: Write a templated function `verifyValues` with the following signature:
    ```cpp
    template<typename Predicate1, typename Predicate2>
    void verifyValues(int* values_array, int num_elements, int custom_threshold, Predicate1 checkPositive, Predicate2 checkCustom);
    ```
    This function should iterate through `values_array`. For each item, it first calls `checkPositive` (e.g., to ensure it's positive) and then `checkCustom` (e.g., to check against `custom_threshold`). If either predicate indicates a failure, `verifyValues` should throw a `DataIntegrityException` with the collected error message.
3.  **Main Function (`try/catch` Block)**: In `main`, define an integer array.
    *   Define a regular function `isPositive` that matches the common function signature (ignoring `threshold`). It checks if `data_item > 0`.
    *   Define a lambda expression `isGreaterThanThreshold` that matches the common function signature and checks if `data_item > threshold` (where `threshold` will be `custom_threshold`). This lambda should capture `custom_threshold` by value.
    *   Call `verifyValues` within a `try/catch` block, passing `isPositive` as `checkPositive` and your `isGreaterThanThreshold` lambda as `checkCustom`. Catch `DataIntegrityException` and print its message.

### Concepts Covered:
*   Custom Exception (`std::exception` inheritance)
*   Function Pointers (passing regular functions)
*   Lambda Expressions (defining and passing lambdas, capture by value)
*   Templates (generic function `verifyValues`)
*   Exception Handling (`try/catch`, `throw`)
*   Boolean Logic

### Example Code Structure:

```cpp
#include <iostream>
#include <string>
#include <vector>

// 1. Custom Exception Class
class DataIntegrityException : public std::exception {
private:
    std::string message;
public:
    DataIntegrityException(const std::string& msg) : message("Data Integrity Error: " + msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Common Function Signature: bool (*ValidationLogic)(int data_item, int threshold, std::string& error_message)

// Provided Function (for checkPositive)
bool isPositive(int data_item, int /*threshold - ignored*/, std::string& error_message) {
    if (data_item > 0) {
        return true;
    } else {
        error_message = "Data item " + std::to_string(data_item) + " is not positive.";
        return false;
    }
}

// 2. Data Processing Function
template<typename Predicate1, typename Predicate2>
void verifyValues(int* values_array, int num_elements, int custom_threshold, Predicate1 checkPositive, Predicate2 checkCustom) {
    std::string error_msg;
    for (int i = 0; i < num_elements; ++i) {
        // Check if positive
        if (!checkPositive(values_array[i], 0, error_msg)) { // threshold 0 is ignored for isPositive
            throw DataIntegrityException(error_msg);
        }
        // Check against custom threshold
        if (!checkCustom(values_array[i], custom_threshold, error_msg)) {
            throw DataIntegrityException(error_msg);
        }
        std::cout << "Value " << values_array[i] << " passed integrity checks." << std::endl;
    }
}

int main() {
    int values[] = { 10, 25, 5, 30, 12 };
    int num_elements = sizeof(values) / sizeof(values[0]);
    int threshold_val = 8;

    // Lambda Expression (for checkCustom) - captures threshold_val by value
    auto isGreaterThanThreshold = [threshold_val](int data_item, int /*threshold - ignored*/, std::string& error_message) -> bool {
        if (data_item > threshold_val) {
            return true;
        } else {
            error_message = "Data item " + std::to_string(data_item) + " is not greater than custom threshold " + std::to_string(threshold_val) + ".";
            return false;
        }
    };

    std::cout << "--- Quiz Set 3: Positive Value and Custom Threshold Check ---" << std::endl;
    try {
        verifyValues(values, num_elements, threshold_val, isPositive, isGreaterThanThreshold);
        std::cout << "All values verified successfully." << std::endl;
    } catch (const DataIntegrityException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with a non-positive value ---" << std::endl;
    int values_fail[] = { 10, -5, 20 }; // -5 is not positive
    int num_elements_fail = sizeof(values_fail) / sizeof(values_fail[0]);
    try {
        verifyValues(values_fail, num_elements_fail, threshold_val, isPositive, isGreaterThanThreshold);
        std::cout << "All values verified successfully." << std::endl;
    } catch (const DataIntegrityException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing with a value below custom threshold ---" << std::endl;
    int values_fail2[] = { 10, 20, 7 }; // 7 is not greater than 8
    int num_elements_fail2 = sizeof(values_fail2) / sizeof(values_fail2[0]);
    try {
        verifyValues(values_fail2, num_elements_fail2, threshold_val, isPositive, isGreaterThanThreshold);
        std::cout << "All values verified successfully." << std::endl;
    } catch (const DataIntegrityException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }

    return 0;
}
