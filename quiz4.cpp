// Workshop/Quiz 4 Mock - C++17
#include <iostream>
#include <vector>
#include <algorithm> // sort, count_if, copy_if, for_each
#include <numeric>   // reduce
#include <execution> // execution policies (seq, par)
#include <memory>    // shared_ptr

// ---------------------------------------------------------
// PROVIDED SECTION: Do not modify the main function strictly
// ---------------------------------------------------------

// The specific container type we are working with
using DataContainer = std::vector<int>;

void processData(void* genericPtr);

int main() {
    // Simulate a dynamically allocated container from a legacy system
    // The ownership of this pointer is passed to processData
    DataContainer* rawData = new DataContainer{10, 5, 8, 3, 20, 15, 2, 7, 30, 1};

    std::cout << "--- Start Processing ---" << std::endl;
    
    // Pass as void* generic pointer
    processData(static_cast<void*>(rawData));

    std::cout << "--- End Processing ---" << std::endl;
    return 0;
}

// ---------------------------------------------------------
// TODO SECTION: Implement the processData function
// ---------------------------------------------------------

void processData(void* genericPtr) {
    // 1. SAFETY: Cast the genericPtr back to DataContainer* //    and Wrap it in a std::shared_ptr to manage memory automatically.
    //    Hint: The shared_ptr should take ownership of the pointer.
    
    // YOUR CODE HERE for Smart Pointer setup
	DataContainer* ctr = reinterpret_cast<DataContainer*> genericPtr; 
////DataContainer* ctr = static_cast<DataContainer*>(genericPtr);

    std::shared_ptr<DataContainer> ptr (new DataContainer(*ctr)); 
//std::shared_ptr<DataContainer> ptr(ctr);
    
    if (!ptr /* check if pointer is valid */ ) {
        std::cerr << "Error: Null pointer passed." << std::endl;
        return;
    }

// Fix: use ->size() instead of sizeof: ptr->size()
    std::cout << "Original size: " << sizeof(*ptr)/* access size via smart ptr */ << std::endl;


    // 2. COUNT: Use std::count_if with std::execution::par
    //    Task: Count how many numbers are greater than 10.
    //    Store result in variable 'count'.
    
    // YOUR CODE HERE
	size_t count = std::count_if(std::execution::par,(*ptr).begin(),(*ptr).end(),[](int i){return i>10;});
    // auto count = ...ptr->begin()


    // 3. REDUCE: Use std::reduce with std::execution::par
    //    Task: Calculate the sum of all elements.
    //    Note: std::reduce is preferred over std::accumulate for parallel execution.
    
    // YOUR CODE HERE
    int sum = std::reduce(std::execution::par,(*ptr).begin(),(*ptr).end(),0,[](int a,int b){return a+b;});


    // 4. COPY: Use std::copy_if with std::execution::seq (or par)
    //    Task: Copy all ODD numbers (num % 2 != 0) into a new vector named 'oddNumbers'.
    //    Hint: You need to resize or use a back_inserter (careful with parallel back_inserter).
    //    For safety in this quiz, pre-calculating size or standard copy is fine. 
    //    Let's assume we create a new vector 'oddNumbers' of correct size first or use back_inserter safely.
    
    DataContainer oddNumbers;
    // YOUR CODE HERE
// WAY A (Thread-Safe Resizing):
// oddNumbers.resize(ptr->size()); // Allocate max possible space
	/*auto endIt =*/std::copy_if(std::execution::par,(*ptr).begin(),(*ptr).end(),oddNumbers.begin(),[](int i){return i%2!=0;});
// oddNumbers.resize(std::distance(oddNumbers.begin(), endIt)); // Shrink to fit   

// WAY B (Your request: back_inserter): 
// correct: MUST use std::execution::seq if pushing back dynamically!
    std::copy_if(std::execution::seq, ptr->begin(), ptr->end(), 
                 std::back_inserter(oddNumbers), 
                 [](int i) { return i % 2 != 0; });


    // 5. SORT: Use std::sort with std::execution::par
    //    Task: Sort the 'oddNumbers' vector in Ascending order.
    
    // YOUR CODE HERE
    std::sort(oddNumbers.begin(),oddNumbers.end(),[](int a, int b){return a<b;});// switch when false?


    // 6. FOR_EACH: Use std::for_each (execution policy optional here)
    //    Task: Print the elements of 'oddNumbers' followed by a space.
    
    std::cout << "Odd Numbers Sorted: ";
    // YOUR CODE HERE
    std::for_each(oddNumbers.begin(),oddNumbers.end(),[](int i){ return std::cout<<i;});
    
    std::cout << std::endl;
    
    // 7. REPORT: Print the results from steps 2 and 3.
    std::cout << "Count > 10: " << count << std::endl;
    std::cout << "Sum of all: " << sum << std::endl;
}
