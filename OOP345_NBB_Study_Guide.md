# OOP345 NBB - Exam Study Guide (Sep 29 & Oct 02)

This document summarizes key C++ concepts covered in the `NBB\07-Sep29` and `NBB\08-Oct02` folders, serving as a quick reference for exam preparation.

## 07-Sep29 Concepts

### Input Validation (Foolproof Integer Entry) 🟢
- **定义 | Definition**: Ensuring user input meets specific criteria (e.g., integer type, range) to prevent program errors.
- **英文解释 | English Explanation**: The process of checking user input to ensure it conforms to expected formats, types, and constraints before it is used by the program. This prevents unexpected behavior, crashes, or security vulnerabilities.
- **示例 | Example**:
  ```cpp
  // 示例：getInt函数确保输入是有效整数，并检查范围
  // Example: getInt function ensures input is a valid integer and checks its range
  int getInt() {
     int num{};
     bool done = false;
     do {
        std::cin >> num;
        if (std::cin.fail()) { // 检查输入是否失败 (Check if input failed)
           std::cin.clear(); // 清除错误标志 (Clear error flags)
           std::cout << "Invalid Integer, please try again\n> ";
        }
        else {
           if (std::cin.peek() != '\n') { // 检查是否有额外字符 (Check for extra characters)
              std::cout << "Only an Integer, Please try again\n> ";
           }
           else if (isAdult(num)) { // 自定义验证逻辑 (Custom validation logic)
              done = true;
           }
           else {
              std::cout << "No children or Seniors permitted...\n> ";
           }
        }
        std::cin.ignore(10000, '\n'); // 忽略剩余输入直到换行符 (Ignore remaining input until newline)
     } while (!done);
     return num;
  }
  ```
- 💡**实践提示 | Practice Tips**: Use `cin.fail()`, `cin.clear()`, `cin.ignore()`, and `cin.peek()` for robust input validation.

### Pointers and Arrays Reminder (指针与数组回顾) 🟢
- **定义 | Definition**: Pointers are variables that store memory addresses. Arrays are collections of elements of the same type stored in contiguous memory locations.
- **英文解释 | English Explanation**: Pointers are fundamental variables in C++ that hold memory addresses, allowing for indirect access to data. Arrays are contiguous blocks of memory used to store a fixed-size sequential collection of elements of the same data type. An array's name often decays into a pointer to its first element.
- **示例 | Example**:
  ```cpp
  // 示例：数组和指针的使用
  // Example: Usage of arrays and pointers
  int a[5]{ 100, 200, 300, 400, 500 };
  int* p = a; // 数组名'a'衰退为指向第一个元素的指针 (Array name 'a' decays to a pointer to its first element)
  std::cout << p[2] << std::endl; // 通过指针访问数组元素 (Access array element via pointer)
  ```
- 💡**实践提示 | Practice Tips**: `reinterpret_cast` can be used to view memory addresses of variables and functions, though it should be used with caution.

### Function Pointers (函数指针) 🟡
- **定义 | Definition**: A pointer that stores the memory address of a function, allowing functions to be passed as arguments or stored in data structures.
- **英文解释 | English Explanation**: A function pointer is a variable that stores the starting address of an executable code block (a function). It allows functions to be invoked indirectly, passed as arguments to other functions, or stored in arrays, enabling dynamic behavior and callback mechanisms.
- **示例 | Example**:
  ```cpp
  // 示例：函数指针的声明、赋值和调用
  // Example: Declaration, assignment, and call of a function pointer
  void (*funcPtr)(int, int); // 声明一个函数指针 (Declare a function pointer)
  funcPtr = sum; // 赋值函数地址 (Assign function address)
  funcPtr(10, 20); // 通过函数指针调用函数 (Call function via function pointer)
  ```
- 💡**实践提示 | Practice Tips**: Function pointers enable polymorphism at runtime and are a core concept for callbacks.

### Passing Logic to Functions (向函数传递逻辑) 🟡
- **定义 | Definition**: Using function pointers to pass custom behavior (logic) into a generic function, making the generic function more flexible.
- **英文解释 | English Explanation**: This technique involves designing a function that accepts a function pointer as one of its parameters. The passed function pointer then dictates a specific part of the logic within the generic function, allowing the generic function to perform different operations based on the provided logic without being modified itself.
- **示例 | Example**:
  ```cpp
  // 示例：getInt函数接受一个验证逻辑函数指针
  // Example: getInt function accepts a validation logic function pointer
  int getInt(bool (*isValid)(int)) {
     int num{};
     bool done = false;
     do {
        // ... input logic ...
        if (isValid(num)) { // 使用传入的函数指针进行验证 (Use the passed function pointer for validation)
           done = true;
        }
        else {
           std::cout << "Invaid value...\n> ";
        }
        // ... error handling ...
     } while (!done);
     return num;
  }
  ```
- 💡**实践提示 | Practice Tips**: This is a common pattern in C for implementing callback functions and custom validation.

### Function Pointers with Error Messages (带错误信息的函数指针) 🟡
- **定义 | Definition**: Extending the concept of passing logic by allowing the validation function to return an error message, providing more informative feedback.
- **英文解释 | English Explanation**: Instead of just returning a boolean, the validation function now takes an additional reference parameter (e.g., `std::string&`) to store a detailed error message. This allows the calling function to display specific feedback to the user when validation fails, improving user experience.
- **示例 | Example**:
  ```cpp
  // 示例：isAdult函数通过引用传递错误信息
  // Example: isAdult function passes error message by reference
  bool isAdult(int num, std::string& errMes) {
     bool res{};
     if (!(num >= 18 && num <= 65)) {
        errMes = "No children or seniors permitted!";
     }
     else {
        res = true;
     }
     return res;
  }
  ```
- 💡**实践提示 | Practice Tips**: Useful for providing detailed feedback to the user about why an input is invalid.

### Arrays of Function Pointers (函数指针数组) 🟡
- **定义 | Definition**: An array where each element is a function pointer, allowing for dynamic selection and execution of functions.
- **英文解释 | English Explanation**: An array of function pointers stores multiple function addresses of the same signature. This enables a program to select and execute different functions at runtime based on an index or other criteria, commonly used for implementing dispatch tables or menu-driven applications.
- **示例 | Example**:
  ```cpp
  // 示例：一个包含加减乘除函数的函数指针数组
  // Example: An array of function pointers for add, subtract, multiply, divide functions
  void (*func[4])(int, int) = { add, sub, mul, divid };
  for (int i = 0; i < 4; i++) {
     func[i](10, 2); // 循环调用数组中的函数 (Loop through and call functions in the array)
  }
  ```
- 💡**实践提示 | Practice Tips**: Simplifies code when you need to perform different operations based on a choice or state.

### Functors (Function Objects | 函数对象) 🟡
- **定义 | Definition**: An object that can be called like a function, typically by overloading the `operator()`. Functors can maintain state.
- **英文解释 | English Explanation**: A functor, or function object, is an instance of a class that overloads the function call operator (`operator()`). This allows objects of the class to be invoked with parentheses, just like functions. A key advantage of functors over function pointers is their ability to maintain internal state across multiple calls.
- **示例 | Example**:
  ```cpp
  // 示例：Add类作为函子，记录调用次数
  // Example: Add class as a functor, tracking call count
  class Add {
     int no{ 0 }; // 内部状态 (Internal state)
  public:
     operator int()const { return no; } // 隐式转换为int，获取调用次数 (Implicit conversion to int, get call count)
     int operator()(int num1, int num2) { // 重载函数调用运算符 (Overload function call operator)
        no++;
        return num1 + num2;
     }
  };
  // ...
  Add add;
  std::cout << add(10, 30) << std::endl; // 调用函子 (Call functor)
  std::cout << "Add was called  " << int(add) << " times" << std::endl;
  ```
- 💡**实践提示 | Practice Tips**: Functors are more powerful than function pointers because they can have member variables and functions, allowing them to store state.

### Function Pointers with Templates (模板函数指针) 🟡
- **定义 | Definition**: Combining function pointers with templates to create generic algorithms that can operate on different data types and use custom comparison logic.
- **英文解释 | English Explanation**: This involves creating a templated function (e.g., a sort algorithm) that accepts a function pointer as an argument. The function pointer itself can also be templated or accept templated arguments, allowing the generic algorithm to work with various data types and use a user-defined comparison function for sorting or other operations.
- **示例 | Example**:
  ```cpp
  // 示例：通用的冒泡排序函数，接受一个比较函数指针
  // Example: Generic bubble sort function, accepting a comparison function pointer
  template <typename T>
  void sort(T* arr, int n, bool(*comp)(T, T)) {
     for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
           if (comp(arr[j], arr[j + 1])) { // 使用传入的比较逻辑 (Use the passed comparison logic)
              T temp = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = temp;
           }
        }
     }
  }
  // ...
  sort(a, 7, ascending<int>); // 传入特定类型的比较函数 (Pass a comparison function of a specific type)
  ```
- 💡**实践提示 | Practice Tips**: Enables highly flexible and reusable algorithms, such as `std::sort` in the STL.

### `auto` and Trailing Return Types (auto与尾随返回类型) 🟡
- **定义 | Definition**: `auto` keyword for type deduction, and trailing return types for specifying function return types after the parameter list, especially useful for complex or templated return types.
- **英文解释 | English Explanation**: `auto` allows the compiler to deduce the type of a variable from its initializer, reducing verbosity. Trailing return types, specified with `-> Type` after the parameter list, provide a more readable way to declare return types, particularly for functions whose return type depends on their arguments (e.g., in templates) or for complex types.
- **示例 | Example**:
  ```cpp
  // 示例：Ticket类成员函数使用尾随返回类型
  // Example: Ticket class member function using a trailing return type
  class Ticket {
  public:
     enum class TicketType { Adult, Child };
     auto get() const->TicketType; // 尾随返回类型 (Trailing return type)
  private:
     TicketType ticketType;
  };
  auto Ticket::get() const -> TicketType { // 实现也使用尾随返回类型 (Implementation also uses trailing return type)
     return ticketType;
  }
  // ...
  auto tt = a.get(); // 使用auto推导变量类型 (Use auto to deduce variable type)
  ```
- 💡**实践提示 | Practice Tips**: Improves readability and simplifies type declarations, especially in generic programming.

### `decltype` with `auto` (decltype与auto) 🔴
- **定义 | Definition**: `decltype(expression)` yields the type of an expression. Combined with `auto` and trailing return types, it allows for perfect forwarding of return types in generic functions.
- **英文解释 | English Explanation**: `decltype` is a type specifier that queries the type of an expression. When used with `auto` and trailing return types (`auto func(...) -> decltype(expression)`), it enables the return type of a templated function to be precisely the type that results from an operation on its arguments, which is crucial for generic programming and perfect forwarding.
- **示例 | Example**:
  ```cpp
  // 示例：add函数使用decltype推导返回类型
  // Example: add function uses decltype to deduce return type
  template<typename T, typename U>
  auto add(const T& t, const U& u) -> decltype(t + u) { // 返回类型是t+u的结果类型 (Return type is the result type of t+u)
     return t + u;
  }
  // ...
  auto res = add(i, x); // res的类型将是double (The type of res will be double)
  ```
- 💡**实践提示 | Practice Tips**: Essential for writing generic code where the return type depends on the types of the arguments.

### Internal Linkage (`static` keyword | 内部链接) 🟡
- **定义 | Definition**: The `static` keyword, when applied to global functions or variables, limits their visibility to the current translation unit (source file).
- **英文解释 | English Explanation**: In C++, when `static` is used with a global function or variable, it gives it internal linkage. This means the function or variable can only be accessed within the same compilation unit (the `.cpp` file it's defined in). This prevents name collisions across different source files and promotes modularity.
- **示例 | Example**:
  ```cpp
  // file: linkage_a.cpp
  static void display() { std::cout << "in module a\n"; } // 内部链接 (Internal linkage)
  // file: linkage_b.cpp
  static void display() { std::cout << "in module b\n"; } // 内部链接 (Internal linkage)
  // 两个display函数互不影响 (The two display functions do not affect each other)
  ```
- 💡**实践提示 | Practice Tips**: Use `static` for helper functions or variables that are only relevant to a single source file to avoid naming conflicts.

### Recursion (递归) 🟡
- **定义 | Definition**: A function that calls itself to solve a problem by breaking it down into smaller, similar subproblems.
- **英文解释 | English Explanation**: Recursion is a programming technique where a function calls itself directly or indirectly to solve a problem. It typically involves a base case (a condition under which the function returns a value without making any more recursive calls) and a recursive step (where the function calls itself with a modified input, moving closer to the base case).
- **示例 | Example**:
  ```cpp
  // 示例：汉诺塔问题 (Tower of Hanoi problem)
  void hanoi(int n, char A, char C, char B) {
     if (n != 0) { // 递归终止条件 (Base case)
        hanoi(n - 1, A, B, C); // 递归调用 (Recursive call)
        std::cout << "Move ring " << n << " from " << A << " to " << C << std::endl;
        hanoi(n - 1, B, C, A); // 递归调用 (Recursive call)
     }
  }

  // 示例：阶乘计算 (Factorial calculation)
  unsigned factorial(unsigned x) {
     if (x > 2u) { // 递归终止条件 (Base case)
        return x * factorial(x - 1); // 递归调用 (Recursive call)
     }
     else {
        return x;
     }
  }
  ```
- 💡**实践提示 | Practice Tips**: Ensure a clear base case to prevent infinite recursion. Can lead to elegant solutions for problems with self-similar substructures.

### Lambda Expressions (Lambda表达式) 🟡
- **定义 | Definition**: Anonymous functions that can be defined inline and used where a function object is expected.
- **英文解释 | English Explanation**: Lambda expressions provide a concise way to define anonymous function objects directly within the code where they are used. They are particularly useful for short, one-off functions, especially when passed as arguments to algorithms (e.g., in the STL). Their syntax includes a capture list `[]`, parameters `()`, and a body `{}`.
- **示例 | Example**:
  ```cpp
  // 示例：简单的无参数lambda
  // Example: Simple no-parameter lambda
  auto hello = []() { return "Hello there!"; };
  std::cout << hello() << std::endl;

  // 示例：带参数的lambda
  // Example: Lambda with parameters
  auto dblIt = [](int n) {return n * 2; };
  std::cout << dblIt(500) << std::endl;

  // 示例：lambda作为函数参数
  // Example: Lambda as a function argument
  int age = getInt(
     [](int num) { // 匿名lambda函数作为验证逻辑 (Anonymous lambda function as validation logic)
        return num >= 18 && num <= 65; 
     }
  );
  ```
- 💡**实践提示 | Practice Tips**: Lambdas simplify code by allowing function definitions close to their point of use, improving readability for short functions.

## 08-Oct02 Concepts

### Lambda Capture by Value (Lambda值捕获) 🟡
- **定义 | Definition**: A lambda expression can capture variables from its enclosing scope by value, meaning a copy of the variable is made at the time the lambda is created.
- **英文解释 | English Explanation**: When a lambda captures a variable by value (e.g., `[=]` or `[var_name]`), a copy of that variable is made and stored within the lambda's closure object. Any modifications to the original variable after the lambda's creation will not affect the captured copy inside the lambda.
- **示例 | Example**:
  ```cpp
  // 示例：k通过值捕获，lambda内部对k的修改不影响外部k
  // Example: k captured by value, modifications to k inside lambda do not affect external k
  int k = 4;
  std::cout << add(10, 
     [=](int i) { // k by value capture
        return i + k; // k is a copy, external k remains 4
     }
  ) << std::endl;
  ```
- 💡**实践提示 | Practice Tips**: Use capture by value when the lambda needs to operate on a snapshot of the variable's state at the time of creation.

### Lambda Capture by Reference (Lambda引用捕获) 🟡
- **定义 | Definition**: A lambda expression can capture variables from its enclosing scope by reference, meaning the lambda operates directly on the original variable.
- **英文解释 | English Explanation**: When a lambda captures a variable by reference (e.g., `[&]` or `[&var_name]`), the lambda's closure object stores a reference to the original variable. Any modifications to the captured variable inside the lambda will directly affect the original variable in the enclosing scope. This can lead to unexpected behavior if the original variable goes out of scope before the lambda is executed.
- **示例 | Example**:
  ```cpp
  // 示例：k通过引用捕获，lambda内部对k的修改会影响外部k
  // Example: k captured by reference, modifications to k inside lambda affect external k
  int k = 4;
  std::cout << sub(10, [&](int i) { return i - k++; }) << std::endl; // k is modified
  std::cout << "k = " << k << std::endl; // Output: k = 5
  ```
- 💡**实践提示 | Practice Tips**: Use capture by reference when the lambda needs to modify the original variable or access its most up-to-date value. Be cautious about lifetime issues.

### Lambda Capture List Options (Lambda捕获列表选项) 🟡
- **定义 | Definition**: The capture list `[]` in a lambda specifies how variables from the enclosing scope are made available inside the lambda's body.
- **英文解释 | English Explanation**: The capture list provides fine-grained control over which variables from the surrounding scope are accessible within the lambda and how they are captured (by value or by reference).
- **示例 | Example**:
  ```
  // 捕获列表选项 | Capture List Options:
  // [=]        捕获所有外部变量（按值）| capture everything by value
  // [&]        捕获所有外部变量（按引用）| capture everything by reference
  // [=, &x]    捕获所有外部变量（按值），但x按引用 | capture everything by value, but x by reference
  // [&, x]     捕获所有外部变量（按引用），但x按值 | capture everything by reference, but x by value
  // [x, &y]    x按值捕获，y按引用捕获 | capture x by value and y by reference
  // [=, &x, &y] 所有按值捕获，x和y按引用捕获 | everything by value, capture x and y by reference
  // [this]     捕获当前对象（按引用）| capture the current object (by reference)
  ```
- 💡**实践提示 | Practice Tips**: Choose the appropriate capture mechanism based on whether the lambda needs a copy of the variable or access to the original, and consider lifetime implications.

### Lambdas with STL Algorithms (Lambda与STL算法) 🟡
- **定义 | Definition**: Lambda expressions are frequently used with Standard Template Library (STL) algorithms to provide custom predicates or operations inline.
- **英文解释 | English Explanation**: STL algorithms like `std::sort`, `std::for_each`, `std::find_if`, etc., often require a function object or predicate. Lambda expressions are a perfect fit for this, allowing developers to define the required logic directly at the call site, making the code more concise and readable than using separate named functions or functors.
- **示例 | Example**:
  ```cpp
  // 示例：使用lambda对vector进行降序排序
  // Example: Using lambda to sort a vector in descending order
  std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2, 6 };
  std::sort(v.begin(), v.end(), [](int a, int b) {return a > b; }); // lambda作为比较器 (lambda as comparator)
  for (int n : v) {
     std::cout << n << " ";
  }
  std::cout << std::endl;
  ```
- 💡**实践提示 | Practice Tips**: Lambdas greatly simplify the use of STL algorithms by providing inline custom logic.

### Exception Handling (异常处理) 🟡
- **定义 | Definition**: A mechanism to deal with runtime errors or exceptional conditions that disrupt the normal flow of program execution.
- **英文解释 | English Explanation**: Exception handling in C++ uses `try`, `throw`, and `catch` keywords. Code that might throw an exception is placed in a `try` block. If an exception occurs, it is `throw`n, and control is transferred to a matching `catch` block that can handle the specific type of exception. This separates error-handling code from normal program logic.
- **示例 | Example**:
  ```cpp
  // 示例：捕获不同类型的异常
  // Example: Catching different types of exceptions
  try {
     if (i == 0) { throwDouble(d); } // 抛出double类型异常 (Throw double type exception)
     if (i == 1) { throw str; } // 抛出C字符串异常 (Throw C string exception)
     throw i; // 抛出int类型异常 (Throw int type exception)
  }
  catch (double de) {
     std::cout << "A double exception is here: " << de << std::endl;
  }
  catch (const char* cstre) {
     std::cout << "A cString exception is here: " << cstre << std::endl;
  }
  catch (...) { // 捕获所有其他异常 (Catch all other exceptions)
     std::cout << "Something thing was thrown, I don't know what!" << std::endl;
  }
  ```
- 💡**实践提示 | Practice Tips**: Use exceptions for truly exceptional conditions, not for normal program flow control. Catch specific exceptions before a generic `catch(...)`.

### `exit()` and `atexit()` (退出函数与注册退出函数) 🟡
- **定义 | Definition**: `exit()` terminates the program immediately. `atexit()` registers functions to be called automatically when the program terminates normally.
- **英文解释 | English Explanation**: The `exit()` function causes immediate program termination. It performs cleanup operations like flushing output buffers and closing open files, but it does not call destructors for local objects. `atexit()` allows you to register functions that will be executed when the program performs a normal termination (either by returning from `main` or by calling `exit()`). These registered functions are called in reverse order of their registration.
- **示例 | Example**:
  ```cpp
  // 示例：使用atexit注册退出函数
  // Example: Registering an exit function using atexit
  void exit_1() {
     std::cerr << "In exit_1\n";
  }
  int main() {
     int i;
     std::cout << "Return(!=1), Exit(1) ? ";
     std::cin >> i;
     if (i == 1) {
        atexit(exit_1); // 注册exit_1函数 (Register exit_1 function)
        exit(1); // 终止程序，会调用exit_1 (Terminate program, will call exit_1)
     }
     return i; // 正常返回，也会调用exit_1 (Normal return, will also call exit_1)
  }
  ```
- 💡**实践提示 | Practice Tips**: `atexit()` is useful for ensuring specific cleanup routines are run before program termination, regardless of how `main` exits.

### Standard Exceptions (标准异常) 🟡
- **定义 | Definition**: C++ Standard Library provides a hierarchy of exception classes under `<exception>` for common error conditions.
- **英文解释 | English Explanation**: The C++ Standard Library defines several exception classes to represent common error scenarios. These are organized into a hierarchy, with `std::exception` as the base class. Key categories include `std::logic_error` (for programmer mistakes like `std::invalid_argument`, `std::out_of_range`) and `std::runtime_error` (for issues detected at runtime like `std::range_error`, `std::overflow_error`). `std::bad_alloc` is thrown when `new` fails to allocate memory.
- **示例 | Example**:
  ```cpp
  // 示例：捕获bad_alloc异常
  // Example: Catching bad_alloc exception
  try {
     p = new char[strlen(s) + 1]; // 可能抛出bad_alloc (May throw bad_alloc)
     // ...
  }
  catch (std::bad_alloc&) {
     std::cout << "Insufficient memory" << std::endl;
  }
  catch (std::exception& e) { // 捕获所有标准异常 (Catch all standard exceptions)
     std::cout << "Standard exception: " << e.what() << std::endl;
  }
  ```
- 💡**实践提示 | Practice Tips**: Prefer throwing and catching standard exceptions or custom exceptions derived from `std::exception` for better error classification and handling.

### `noexcept` Specifier (noexcept说明符) 🔴
- **定义 | Definition**: A specifier that indicates a function does not throw exceptions. If a `noexcept` function *does* throw, `std::terminate` is called.
- **英文解释 | English Explanation**: The `noexcept` specifier is a promise to the compiler that a function will not throw any exceptions. This allows the compiler to perform certain optimizations. If a function declared `noexcept` *does* throw an exception, the program's execution is immediately terminated by calling `std::terminate()`, rather than attempting to unwind the stack. It's crucial to ensure that `noexcept` functions truly do not throw.
- **示例 | Example**:
  ```cpp
  // 示例：noexcept函数的使用
  // Example: Usage of noexcept function
  void d() { throw "d() throws\n"; }
  void e() {
     try { d(); }
     catch (const char* msg) { std::cout << msg; }
  }
  void f() { throw "f() throws\n"; }
  void g() noexcept { e(); }  // safe, e() handles its exception
  void h() noexcept { f(); }  // unsafe! f() throws, h() is noexcept, will terminate
  // ...
  // Calling h() will terminate the program because f() throws an exception
  // and h() is declared noexcept.
  ```
- 💡**实践提示 | Practice Tips**: Use `noexcept` for functions that are guaranteed not to throw exceptions to enable compiler optimizations. Be very careful, as violating the `noexcept` guarantee leads to `std::terminate`.

### Abnormal Termination (异常终止) 🔴
- **定义 | Definition**: Program termination that occurs due to unhandled exceptions, calls to `abort()`, or other critical errors, often without proper cleanup.
- **英文解释 | English Explanation**: Abnormal termination refers to a program ending unexpectedly or forcefully. This can happen if an exception escapes a `noexcept` function, an unhandled exception propagates out of `main`, or if `std::abort()` is explicitly called. Unlike `exit()`, `abort()` typically does not perform cleanup like calling `atexit` handlers or destructors for global/static objects, leading to resource leaks. `std::terminate()` is called in various error scenarios, including unhandled exceptions.
- **示例 | Example**:
  ```cpp
  // 示例：使用abort()强制终止程序
  // Example: Forcibly terminating the program using abort()
  int main() {
     std::cout << "About to abort!" << std::endl;
     abort(); // 立即终止，无清理 (Terminates immediately, no cleanup)
     return 0;
  }
  ```
- 💡**实践提示 | Practice Tips**: Avoid abnormal termination. Always handle exceptions gracefully and ensure proper resource management.
