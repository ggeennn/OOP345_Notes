#include <iostream>
#include <utility> // for std::move
#include <cstring> // for strlen and strcpy
#include <cstddef> // for size_t

//==============================================================================
// Question 1: Move Semantics (Rule of Five Focus)
//==============================================================================
// Task: You are given a Buffer class that manages a dynamic C-style string.
// The default constructor, copy constructor, copy assignment operator, and
// destructor are provided.
//
// Your task is to implement the move semantics (move constructor and move
// assignment operator) and the ostream insertion operator (operator<<).
//
// Add the required function prototypes to the class definition and implement
// them outside the class.
//------------------------------------------------------------------------------

template<typename T>
class Buffer {
    T* m_data;
    size_t m_size;
public:
    // Default constructor
    Buffer() : m_data(nullptr), m_size(0) {}

    // Constructor with C-style string
    Buffer(const T* str) {
        if (str) {
            m_size = std::strlen(str) + 1;
            m_data = new T[m_size];
            std::strcpy(m_data, str);
        } else {
            m_data = nullptr;
            m_size = 0;
        }
    }

    // Destructor
    ~Buffer() {
        delete[] m_data;
    }

    // Copy Constructor
    Buffer(const Buffer& other) {
        m_size = other.m_size;
        if (other.m_data) {
            m_data = new T[m_size];
            std::strcpy(m_data, other.m_data);
        } else {
            m_data = nullptr;
        }
        std::cout << "Copy Constructor called.\n";
    }

    // Copy Assignment Operator
    Buffer& operator=(const Buffer& other) {
        std::cout << "Copy Assignment Operator called.\n";
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            if (other.m_data) {
                m_data = new T[m_size];
                std::strcpy(m_data, other.m_data);
            } else {
                m_data = nullptr;
            }
        }
        return *this;
    }

    // --- YOUR TASK STARTS HERE ---
    
    // 1. Add prototypes for Move Constructor and Move Assignment Operator here.
    // ... YOUR CODE HERE (Prototypes) ...
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;


    // 2. Add a friend declaration for the ostream insertion operator.
    // ... YOUR CODE HERE (Friend declaration) ...
    friend std::ostream& operator<<(std::ostream& os, const Buffer& buf);

    // --- YOUR TASK ENDS HERE ---

};

// 3. Implement the Move Constructor outside the class.
// It should "steal" the resources from the 'other' object and set 'other'
// to a safe, empty state. It should not perform any deep copy.
// ... YOUR CODE HERE (Move Constructor Implementation) ...
template<typename T>
Buffer<T>::Buffer(Buffer<T>&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
    other.m_data = nullptr;
    other.m_size = 0;
    std::cout << "Move Constructor called.\n";
}

// 4. Implement the Move Assignment Operator outside the class.
// It should handle self-assignment, release its own resources, "steal"
// the resources from 'other', and set 'other' to a safe, empty state.
// ... YOUR CODE HERE (Move Assignment Operator Implementation) ...
template<typename T>
Buffer<T>& Buffer<T>::operator=(Buffer<T>&& other) noexcept {
    std::cout << "Move Assignment Operator called.\n";
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        other.m_data = nullptr;
        other.m_size = 0;
    }
    return *this;
}

// 5. Implement the ostream insertion operator.
// It should print the string stored in the buffer to the ostream.
// If the buffer is empty, it should print "[empty]".
// ... YOUR CODE HERE (ostream insertion operator Implementation) ...
template<typename U>
std::ostream& operator<<(std::ostream& os, const Buffer<U>& buf) {
    if (buf.m_data) {
        os << buf.m_data;
    } else {
        os << "[empty]";
    }
    return os;
}


//==============================================================================
// Question 2: Function Template Specialization
//==============================================================================
// Task: You are given a generic function template `printValue`. Your task is
// to implement a specialization for the type `const char*` so that it prints
// the string surrounded by double quotes.
//------------------------------------------------------------------------------

// Generic template (DO NOT MODIFY)
template<typename T>
void printValue(T value) {
    std::cout << "Value: " << value << std::endl;
}

// ... YOUR CODE HERE: Implement the specialization for const char* ...
template<>
void printValue<const char*>(const char* value) {
    std::cout << "Value: \"" << (value ? value : "") << "\"" << std::endl;
}


//==============================================================================
// Question 3: Lambda Expression Implementation
//==============================================================================
// Task: You are given a function `applyOperation` which takes an integer and
// a function pointer. Your task is to call `applyOperation` from `main`
// using a lambda expression. The lambda should capture two local variables,
// `multiplier` and `offset`, and apply the formula: `result = (input * multiplier) + offset`.
//------------------------------------------------------------------------------

// Function that accepts a function pointer (DO NOT MODIFY)
void applyOperation(int input, int (*op)(int)) {
    int result = op(input);
    std::cout << "applyOperation(" << input << ") -> " << result << std::endl;
}

void question3_main() {
    int multiplier = 10;
    int offset = 5;
    int data = 7;

    // ... YOUR CODE HERE: Call 'applyOperation' with a lambda that captures
    // 'multiplier' and 'offset' by value.
    applyOperation(data, [multiplier, offset](int input) -> int {
        return (input * multiplier) + offset;
    });

}


//==============================================================================
// Question 4: Functor Implementation
//==============================================================================
// Task: Create a functor class named `SequenceGenerator`. This functor, when
// called, should generate a sequence of numbers starting from an initial
// value and incrementing by a fixed step. It should be a "stateful" function
// object.
//------------------------------------------------------------------------------

class SequenceGenerator {
private:
    // ... YOUR CODE HERE: Add member variables for state (e.g., current value, step) ...
    int m_current;
    int m_step;
public:
    // ... YOUR CODE HERE: Implement a constructor to initialize the state ...
    SequenceGenerator(int start, int step) : m_current(start), m_step(step) {}
    
    // ... YOUR CODE HERE: Overload the function call operator '()' ...
    // This operator should return the current value and then update the state
    // for the next call.
    int operator()() {
        int val = m_current;
        m_current += m_step;
        return val;
    }
};


//==============================================================================
// Question 5: Generic Pointers and Low-level Memory Processing
//==============================================================================
// Task: Write a function `copyBytePattern` that receives a generic pointer
// (`const void*`) to an object and the object's size. The function should
// dynamically allocate a new buffer of `unsigned char` and copy the exact
-
// byte pattern of the source object into this new buffer. The function
// should return the address of the newly created buffer. The caller is
// responsible for deallocating the buffer.
//------------------------------------------------------------------------------

struct TestStruct {
    int a;
    char b;
    double c;
};

unsigned char* copyBytePattern(const void* source, size_t size) {
    // ... YOUR CODE HERE:
    // 1. Return nullptr if source is null or size is 0.
    if (!source || size == 0) return nullptr;

    // 2. Allocate a new dynamic array of 'unsigned char' of the given 'size'.
    unsigned char* buffer = new unsigned char[size];
    
    // 3. Cast the source pointer to a type that can be read byte-by-byte.
    const unsigned char* src_bytes = static_cast<const unsigned char*>(source);
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = src_bytes[i]; // buffer[i] = static_cast<const unsigned char*>(source)[i]; 先cast成char ptr再用[]运算
    }
    
    // 5. Return the pointer to the new buffer.
    return buffer;
}


//==============================================================================
// Main function to test all questions
//==============================================================================
int main() {
    std::cout << "--- Question 1: Move Semantics ---" << std::endl;
    Buffer<char> b1("Hello");
    std::cout << "b1: " << b1 << std::endl;
    Buffer<char> b2 = b1; // Copy constructor
    std::cout << "b2 (copy of b1): " << b2 << std::endl;
    Buffer<char> b3;
    b3 = b1; // Copy assignment
    std::cout << "b3 (copy of b1): " << b3 << std::endl;
    
    std::cout << "\n--- Testing Move ---" << std::endl;
    Buffer<char> b4 = std::move(b1); // Move constructor
    std::cout << "b4 (moved from b1): " << b4 << std::endl;
    std::cout << "b1 (after move): " << b1 << std::endl;
    b3 = std::move(b2); // Move assignment
    std::cout << "b3 (moved from b2): " << b3 << std::endl;
    std::cout << "b2 (after move): " << b2 << std::endl;
    
    std::cout << "\n--- Question 2: Template Specialization ---" << std::endl;
    printValue(101);
    printValue(3.14);
    printValue("C-style String");

    std::cout << "\n--- Question 3: Lambda Expression ---" << std::endl;
    question3_main();
    
    std::cout << "\n--- Question 4: Functor ---" << std::endl;
    SequenceGenerator seq(100, 5);
    std::cout << "1st call: " << seq() << std::endl;
    std::cout << "2nd call: " << seq() << std::endl;
    std::cout << "3rd call: " << seq() << std::endl;
    
    std::cout << "\n--- Question 5: Generic Pointers ---" << std::endl;
    TestStruct myStruct = { 123, 'X', 456.789 };
    unsigned char* pattern = copyBytePattern(&myStruct, sizeof(myStruct));

    if (pattern) {
        std::cout << "Byte pattern of myStruct (size " << sizeof(myStruct) << "):\n";
        for (size_t i = 0; i < sizeof(myStruct); ++i) {
            printf("%02X ", pattern[i]); // Using printf for hex format
        }
        std::cout << std::endl;
        delete[] pattern; // IMPORTANT: Clean up dynamic memory
    } else {
        std::cout << "Failed to copy byte pattern." << std::endl;
    }
    
    return 0;
}