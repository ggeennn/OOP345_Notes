// Quiz 2: Custom Exceptions, Function Pointers, and Lambdas (Revision: No Containers)
#include <iostream>
#include <string>
#include <cstddef> // Required for size_t

using ProcessItemFunc = bool (*)(int); 

// 2. Sample Data (C-style array and size)
const size_t DATA_SIZE = 8;
// Use const int* or const int data[] syntax for safety, here we use array definition.
const int data[DATA_SIZE] = { 5, 12, 18, 25, 30, 41, 55, 60 };

// 3. Provided Function (First Function Pointer)
// Goal: Checks if the value is a multiple of 5 (e.g., 5, 25, 55).
bool checkMultipleOfFive(int value) {
    // If the value is a multiple of 5, it passes the check
    return (value % 5 == 0); 
}

// Your Task 1: Create your custom exception class here (inherits from std::exception)
class NotValid: public std::exception{
    std::string msg{};
public:
    NotValid():msg("invalid number!"){}
    const char* what() const noexcept{ return msg.c_str(); }
};
// Your Task 2: Write the search function here.
// Signature Hint: 
// The search function must iterate over the C-style array using the size parameter.
void searchAndThrow(const int* data,const size_t size,bool(*check1)(int),bool(*check2)(int)){
    bool valid = true;
    for(int i=0; i<size;i++){
        valid = check1(data[i]) && check2(data[i]);
        if(!valid) throw NotValid();
    }
}
int main() {
    std::cout << "--- Quiz 2 Start ---\n";

    // Your Task 3: Implement the try/catch block here.
    try{
        auto lam = [](int data){ return data < 100; };
        searchAndThrow(data,DATA_SIZE,checkMultipleOfFive,lam);
    }catch(NotValid e){
        std::cout<< e.what()<<std::endl;
    }


    std::cout << "--- Quiz 2 End ---\n";
    return 0;
}