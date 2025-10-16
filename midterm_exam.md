# OOP345 Midterm Exam Simulation

## Part 1: Concept Questions and Code Walkthroughs (30%)

### Code Walkthrough Topics

**1. Variable Shadowing**
```cpp
#include <iostream>
int x = 5;

int main() {
    int x = 10;
    {
        int x = 15;
        std::cout << x << std::endl;  // Output: ______
    }
    std::cout << x << std::endl;      // Output: ______
    std::cout << ::x << std::endl;    // Output: ______
    return 0;
}
```
Explain the output results: ______

**2. Static Methods and Attributes**
```cpp
class Counter {
    static int count;
public:
    Counter() { count++; }
    static int getCount() { return count; }
    ______ // Declare static reset method
};
______ // Initialize static member

int main() {
    Counter c1, c2;
    std::cout << Counter::getCount() << std::endl;  // Output: ______
    Counter::reset();
    Counter c3;
    std::cout << c3.getCount() << std::endl;        // Output: ______
    return 0;
}
```
Complete the missing declarations/initializations: ______

**3. Signature of main()**
```cpp
int main(______ argc, ______ argv[]) {
    std::cout << "Program name: " << ______ << std::endl;
    if(argc > 1) {
        std::cout << "First argument: " << ______ << std::endl;
    }
    return 0;
}
```
Fill in the blanks: ______

**4. References and Move References**
```cpp
void process(int& ref) {
    std::cout << "Lvalue reference: " << ref << std::endl;
}

void process(______ ref) {
    std::cout << "Rvalue reference: " << ref << std::endl;
}

int main() {
    int a = 10;
    process(a);
    process(______);
    return 0;
}
```
Complete the move reference implementation: ______

**5. #define vs typedef**
```cpp
______ PI 3.14159        // Macro definition
______ float_array float* // Type alias

int main() {
    float_array f = new float[10];
    f[0] = ______ * 2;
    // ... rest of code
}
```
Fill in the blanks and explain the difference: ______

**6. Function Template Specialization/Overloading**
```cpp
template <typename T>
T add(T a, T b) { 
    return a + b; 
}

______ // Specialize for const char*
______ add(const char* a, const char* b) {
    std::string result = ______;
    result += b;
    return ______;
}

int main() {
    std::cout << add(5, 3) << std::endl;         // Output: ______
    std::cout << add("Hello", "World") << std::endl; // Output: ______
}
```
Complete the specialization: ______

### Concept Topics
Provide brief explanations for:
1. Translation units: ______
2. Declaration vs definition: ______
3. extern keyword: ______
4. cv-qualifiers (const, volatile): ______
5. typedef keyword: ______
6. Object scopes (automatic, static, dynamic): ______
7. Compile-time vs run-time vs pre-processing: ______
8. lvalue vs rvalue: ______
9. Literal value types (L, UL, LL): ______
10. Size of unions: ______
11. Unscoped vs scoped enums: ______

---

## Part 2: Programming Tasks (70%)

### 1. Move Semantics (Rule of Five) [33 points]
```cpp
class MemoryBlock {
    size_t length;
    int* data;
public:
    // Constructor
    explicit MemoryBlock(size_t len) : length(len), data(new int[len]) {}
    
    // 1. Destructor
    ~MemoryBlock() { delete[] data; }
    
    // 2. Copy constructor
    MemoryBlock(const MemoryBlock& src):length(src.length), data(new int[src.len]){
        for(size_t i = 0; i<length; i++){
            data[i] = src.data[i];
        }
    }
    
    // 3. Copy assignment operator
    MemoryBlock& operator=(const MemoryBlock& src){
        if(this != &src){
            delete[] data;
            length = src.length;
            data = new int[length];
            for(size_t i = 0; i<length; i++){
                data[i] = src.data[i];
            }
        }
        return *this;
    }
    
    // 4. Move constructor
    MemoryBlock(MemoryBlock&& src) noexcept : length(src.length), data(src.data){
        src.length = 0;
        src.data = nullptr;
    }
    
    // 5. Move assignment operator
    MemoryBlock& operator= (MemoryBlock&& src) noexcept {
        if(this != &src){
            delete[] data;
            length = src.length;
            data = src.data;
            src.length = 0;
            src.data = nullptr;
        }
        return *this;
    }
    
    // 6. Ostream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const MemoryBlock& block) {
        for(size_t i = 0; i< length;++i){
            os << block.data[i]<<std:endl;
        }
        return os;
    }
};

// Implement methods outside class
```

### 2. Function Template Specialization [7 points]
```cpp
template <typename T>
void process(T value) {
    std::cout << "Generic: " << value << std::endl;
}

// Specialize for std::vector<int> to print all elements
template<>
void process<std::vector<int>>(std::vector<int> elements) {
    for(int e:elements){
        std::cout << e << std::endl;
    }
}

int main() {
    process(10);                  // Generic: 10
    process(std::vector<int>{1,2,3}); // Specialized: [1, 2, 3]
}
```

### 3. Lambda Expression Implementation [7 points]
```cpp
void transform_values(std::vector<int>& values, int(*func)(int)) {
    for(auto& val : values) {
        val = func(val);
    }
}

int main() {
    std::vector<int> data = {1, 2, 3};
    int multiplier = 3;
    int count = 0;

    // Call transform_values with lambda that:
    // - Captures multiplier by value and count by reference
    // - Multiplies each element by multiplier
    // - Increments count after each transformation
    auto lam = [=,&count](int i){
        ++count;
        return i *= multiplier;
    };
    transform_values(data, lam);

    std::cout << "Count: " << count << std::endl;  // Should output: Count: 3
}
```

### 4. Functor Implementation [11 points]
```cpp
// Create Accumulator functor that:
// 1. Remembers starting value
// 2. When called with new value, adds to running total
// 3. When cast to int, returns current total
class Accumulator {
    int currentValue{};
public:
    Accumulator(int start) : currentValue(start) {}
    
    void operator()(int value) {
        currentValue += value;
    }
    
    operator int() const {
        return currentValue;
    }
};

int main() {
    Accumulator acc(5);
    acc(10);
    acc(20);
    std::cout << static_cast<int>(acc) << std::endl;  // Should output 35
}
```

### 5. Generic Pointers and Memory Processing [11 points]
```cpp
#include <cstring>
#include <iomanip>
#include <sstream>

// Create function that:
// - Takes object address via void*
// - Returns hexadecimal string of object's byte pattern
std::string byte_pattern(void* obj, size_t size) {
    unsigned char* c = new unsigned char[size];
    unsigned char* src = static_cast<unsigned char*>obj;
    for (size_t i = 0; i < size; ++i){
        c[i] = src[i];
    }
    return c;
}

int main() {
    int value = 0x12345678;
    auto pattern = byte_pattern(value,sizeof(value));
    std::cout << pattern << std::endl;  // Should output byte pattern 
    delete pattern;
}
