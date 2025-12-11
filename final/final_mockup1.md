这是一份包含 **Part 1 (概念)** 和 **Part 2 (编程)** 完整问题与答案的模拟试卷。内容严格覆盖了你上传文件 `final_review.md` 中的所有考点（多线程、智能指针、STL 算法、二进制文件、RAII 等）。

-----

# Part 1: Concept & Debugging (Time: \~20 Mins)

这里精选了 5 道涵盖所有复习重点的概念题。

### Questions & Answers

**Q1. Multithreading & Race Conditions**

  * **Scenario:** You have a global variable `int counter = 0` and two threads that both run a loop `for(i=0; i<1000; ++i) counter++;`. The final result is consistently less than 2000.
  * **Question:** What is the specific technical term for this bug? Name the C++ object you must use to ensure only one thread updates the variable at a time.
  * **Answer:**
      * **Term:** **Race Condition** (or Data Race).
      * **Object:** **`std::mutex`** (used with `std::lock_guard` or `std::unique_lock`).

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx; // The mutex to protect the counter

void increment_counter() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        counter++;
    }
}

int main() {
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl; // Should be 2000
    return 0;
}
```
**Q2. Named Casts (Polymorphism)**

  * **Scenario:** You have a `Base* ptr` pointing to a `Derived` object. The `Base` class has a `virtual` destructor. You need to call a method `sayHello()` that only exists in `Derived`.
  * **Question:** Which C++ named cast should you use to safely convert `ptr` to `Derived*`? What does it return if the cast fails (e.g., if `ptr` actually points to a different subclass)?
  * **Answer:**
      * **Cast:** **`dynamic_cast<Derived*>(ptr)`**
      * **On Failure:** It returns **`nullptr`** (when casting pointers).

```cpp
#include <iostream>
#include <memory>

class Base {
public:
    virtual ~Base() = default; // Virtual destructor for polymorphic behavior
};

class Derived : public Base {
public:
    void sayHello() {
        std::cout << "Hello from Derived!" << std::endl;
    }
};

class AnotherDerived : public Base {
public:
    void saySomethingElse() {
        std::cout << "Something else from AnotherDerived!" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived(); // ptr points to a Derived object

    // Safely cast to Derived* using dynamic_cast
    Derived* derivedPtr = dynamic_cast<Derived*>(ptr);
    if (derivedPtr) {
        derivedPtr->sayHello(); // Call Derived's method
    } else {
        std::cout << "Cast failed!" << std::endl;
    }

    delete ptr; // Clean up

    Base* anotherPtr = new AnotherDerived(); // ptr points to AnotherDerived
    Derived* failedCastPtr = dynamic_cast<Derived*>(anotherPtr);
    if (failedCastPtr) {
        failedCastPtr->sayHello();
    } else {
        std::cout << "Cast to Derived failed for AnotherDerived object, as expected." << std::endl;
    }
    delete anotherPtr;

    return 0;
}
```
**Q3. Smart Pointers (Ownership)**

  * **Question:** Why does `std::unique_ptr` delete its copy constructor and copy assignment operator? Explain in terms of "Resource Ownership".
  * **Answer:** `std::unique_ptr` enforces **exclusive ownership**. If copying were allowed, two unique pointers would own the same raw resource, leading to a **Double Free** error (both trying to delete the same memory) when they go out of scope.

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class MyResource {
public:
    MyResource(int id) : id_(id) {
        std::cout << "MyResource " << id_ << " created." << std::endl;
    }
    ~MyResource() {
        std::cout << "MyResource " << id_ << " destroyed." << std::endl;
    }
    void doSomething() {
        std::cout << "MyResource " << id_ << " doing something." << std::endl;
    }
private:
    int id_;
};

void process_resource(std::unique_ptr<MyResource> res) {
    res->doSomething();
} // res goes out of scope here, resource is deleted

int main() {
    std::unique_ptr<MyResource> u_ptr1 = std::make_unique<MyResource>(1);
    // std::unique_ptr<MyResource> u_ptr2 = u_ptr1; // ERROR: copy constructor is deleted
    // std::unique_ptr<MyResource> u_ptr3;
    // u_ptr3 = u_ptr1; // ERROR: copy assignment operator is deleted

    // Ownership can be moved
    std::unique_ptr<MyResource> u_ptr2 = std::move(u_ptr1);
    if (u_ptr1 == nullptr) {
        std::cout << "u_ptr1 is now empty after move." << std::endl;
    }
    u_ptr2->doSomething();

    // Passing to a function by move
    process_resource(std::move(u_ptr2));
    if (u_ptr2 == nullptr) {
        std::cout << "u_ptr2 is now empty after moving to function." << std::endl;
    }

    std::unique_ptr<MyResource> u_ptr3 = std::make_unique<MyResource>(3);
    // When u_ptr3 goes out of scope at the end of main, MyResource 3 is destroyed.

    return 0;
}
```
**Q4. Wrapper & STL Algorithms**

  * **Scenario:** You want to pass a standard `int` variable `x` by reference to a thread or a binder function, but the function signature expects a value.
  * **Question:** Which wrapper from `<functional>` can you use to create a "copyable reference" (reference wrapper)?
  * **Answer:** **`std::ref(x)`** (or `std::cref(x)` for const reference).

```cpp
#include <iostream>
#include <functional> // For std::ref
#include <thread>     // For std::thread

void increment_by_value(int val) {
    val++; // Only modifies the copy
    std::cout << "Inside function (by value): " << val << std::endl;
}

void increment_by_ref(int& ref_val) {
    ref_val++; // Modifies the original variable
    std::cout << "Inside function (by ref): " << ref_val << std::endl;
}

int main() {
    int original_value = 10;
    std::cout << "Original value before calls: " << original_value << std::endl;

    // Passing by value (copy)
    increment_by_value(original_value);
    std::cout << "Original value after by-value call: " << original_value << std::endl; // Still 10

    // Passing by reference directly (not copyable for some contexts like std::thread constructor)
    // increment_by_ref(original_value); // This works directly

    // Using std::ref to pass by reference to a context that expects a copy (like std::thread)
    std::thread t(increment_by_ref, std::ref(original_value));
    t.join();
    std::cout << "Original value after std::thread with std::ref: " << original_value << std::endl; // Now 11

    // Example with std::bind (another use case for std::ref)
    auto bound_func = std::bind(increment_by_ref, std::ref(original_value));
    bound_func();
    std::cout << "Original value after std::bind with std::ref: " << original_value << std::endl; // Now 12

    return 0;
}
```
**Q5. Binary Files**

  * **Question:** When opening a file stream `std::ofstream` to write raw binary data (like an `int` directly, not text "123"), which flag must be combined with `std::ios::out`?
  * **Answer:** **`std::ios::binary`**

-----

# Part 2: Programming (Time: \~80 Mins)

### Question 1: Validated Smart Pointer (`Pointer<T, V>`)

**What it’s about:**
Writing a class template `Pointer<T, Validator>` that owns a dynamically allocated object (`T*`).
Using a callable validator (functor / lambda) to decide whether a dynamically allocated object is “valid” and should be kept or deleted.

**Implementing:**
- A constructor
- A destructor
- A setter that takes ownership of a `T*`
- Accessor methods (const and non-const versions).
- A move process that transfers ownership. (either assignment or construction)
- Disabling moving or copying

**What to study:**
- Class templates: `template<typename T, typename Validator>`.
- Raw dynamic memory: single-object `new`/`delete` and ownership.
- RAII basics: destructor responsibility, avoiding leaks and double delete.
- Functors and callables (objects with `operator()` and simple lambdas).
- Move semantics (move constructor) and deleting copy operations.
- Basic pointer checks (`nullptr`) and simple resource management patterns.

**Solution Code:**

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr
#include <utility> // For std::move
#include <functional> // For std::function (可选，但有时用于类型擦除)

// 假设这是 Pointer 类模板的定义
template <typename T, typename Validator>
class Pointer {
    T* m_ptr = nullptr;
    Validator m_valid;

public:
    // 改进后的构造函数：接受 T* 和 Validator 实例
    explicit Pointer(T* ptr = nullptr, Validator v = Validator()) 
        : m_ptr(ptr), m_valid(std::move(v)) // 使用移动语义初始化 m_valid
    {}

    // ... 其他成员函数保持不变 ...

    // 析构函数
    ~Pointer() {
        delete m_ptr;
    }

    // 删除拷贝操作
    Pointer(const Pointer&) = delete;
    Pointer& operator=(const Pointer&) = delete;

    // 移动构造函数
    Pointer(Pointer&& other) noexcept
        : m_ptr(other.m_ptr), m_valid(std::move(other.m_valid)) // 移动 Validator
    {
        other.m_ptr = nullptr;
    }

    // 移动赋值运算符
    Pointer& operator=(Pointer&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            m_valid = std::move(other.m_valid); // 移动 Validator
            other.m_ptr = nullptr;
        }
        return *this;
    }

    // Setter (这里我们使用原始的裸指针版本，但请参考上一个回复中的安全改进建议)
    void set(T* ptr) {
        delete m_ptr;
        m_ptr = ptr;
    }

    // 解引用运算符
    T& operator*() { return *m_ptr; }
    const T& operator*() const { return *m_ptr; }
    T* operator->() { return m_ptr; }
    const T* operator->() const { return m_ptr; }
    
    // 检查有效性
    bool isValid() const {
        return m_ptr != nullptr && m_valid(m_ptr); 
    }
    explicit operator bool() const {
        return m_ptr != nullptr && m_valid(m_ptr);
    }

    T* get() const { return m_ptr; }
};

int main() {
    std::cout << "--- 使用 Lambda 表达式作为 Validator ---" << std::endl;

    int upper_limit = 100; // 外部变量，将被 lambda 捕获

    // Lambda 表达式作为 Validator，捕获 upper_limit，检查值是否在 [0, upper_limit) 范围内
    auto inRangeValidator = [upper_limit](const int* valPtr) {
        return valPtr != nullptr && *valPtr >= 0 && *valPtr < upper_limit;
    };

    // 实例化 Pointer，T 为 int，Validator 为 lambda 的类型 (使用 decltype)
    Pointer<int, decltype(inRangeValidator)> p_range(new int(50), inRangeValidator);
    std::cout << "p_range (value 50, limit 100) is valid: " << (p_range.isValid() ? "true" : "false") << std::endl; // true

    p_range.set(new int(120));
    std::cout << "p_range (value 120, limit 100) is valid: " << (p_range.isValid() ? "true" : "false") << std::endl; // false

    p_range.set(new int(-10));
    std::cout << "p_range (value -10, limit 100) is valid: " << (p_range.isValid() ? "true" : "false") << std::endl; // false

    // 另一个 lambda 示例：检查指针是否指向一个非空字符串
    auto isNonEmptyString = [](const std::string* strPtr) {
        return strPtr != nullptr && !strPtr->empty();
    };

    Pointer<std::string, decltype(isNonEmptyString)> p_str(new std::string("Hello"), isNonEmptyString);
    std::cout << "p_str (value 'Hello') is valid: " << (p_str.isValid() ? "true" : "false") << std::endl; // true

    p_str.set(new std::string("")); // 空字符串
    std::cout << "p_str (value '') is valid: " << (p_str.isValid() ? "true" : "false") << std::endl; // false

    return 0;
}

```

-----

### Question 2: Chunk Processing Functor

**What it’s about:**
A functor class that:
- Stores a const vector smart pointers created in question one & and a `[begin, end)` index range.
- In `operator()`, from `m_begin` to `m_end`, checks each smart pointer for validity, and collects the underlying `int` values into a vector of the underlaying type
- Returns that vector.

**What to study:**
- Type aliases: `using NewDataType = SomeTemplate<whatever, whatever>;`.
- Class design with member initialiser lists for references and indices.
- `std::vector`: indexing with `size_t`, `push_back`, `size()`.
- Writing and using a functor with `operator()()` that returns a value.
- Checking pointers for validity and dereferencing them safely.

**Solution Code:**

```cpp
#include <vector>

// 预备知识：定义一个符合要求的 Functor，用于 Q2 的类型别名
// (原代码中的 std::less 需要两个参数，不适合这里 isValid 的单参数调用)
struct IntValidator {
    // 验证逻辑：指针不为空 且 值大于 0
    bool operator()(const int* ptr) const {
        return ptr != nullptr && *ptr > 0;
    }
};

// 1. 类型别名 (Type Alias)
// 使用 Q1 定义的模板，T=int，Validator=IntValidator
using DataPtr = Pointer<int, IntValidator>;

class ChunkFilter {
    const std::vector<DataPtr>& m_data; // Reference to source data
    size_t m_begin;
    size_t m_end;

public:
    // Member Initialiser List
    ChunkFilter(const std::vector<DataPtr>& data, size_t begin, size_t end)
        : m_data(data), m_begin(begin), m_end(end) {}

    // Operator() returning a vector of values
    std::vector<int> operator()() {
        std::vector<int> results;
        for (size_t i = m_begin; i < m_end; ++i) {
            if (i >= m_data.size()) break;
            // Check smart pointer validity
            if (m_data[i].isValid()) {
                
                // Dereference and store the underlying int
                results.push_back(*m_data[i]);
            }
        }
        return results;
    }
};
```

-----

### Question 3: Parallel Filtering with `std::async`

**What it’s about:**
Splitting a large `vector<DataPtr>` into chunks based on the number of hardware threads.
For each chunk:
- Creating a `ChunkFilter` object for a `[start, end)` range.
- Launching it with `std::async(std::launch::async, ...)`.
- Storing the returned `std::future` of vectors of underlying smart pointer types in a vector of futures.
After launching all tasks:
- Calling `.get()` on each future.
- Appending all returned `vector<int>` values into a single `vector<int> allValid`.

**What to study:**
- `std::async` and `std::launch::async`.
- `std::future` and `.get()`.
- Find number of available threads and using it to choose the number of tasks.
- Dividing work over a range `[0, size)` into roughly equal chunks.
- Basic use of vectors of `std::futures` of vectors of underlying smart pointer types (or equivalent).
- Avoiding data races by only reading shared data and returning results by value.

**Solution Code:**

```cpp
#include <future>
#include <vector>
#include <algorithm>

std::vector<int> process_parallel(const std::vector<DataPtr>& allData) {
    std::vector<int> allValid;
    
    // 1. Determine thread count
    size_t numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 1; // Safety fallback

    std::vector<std::future<std::vector<int>>> futures;
    size_t totalSize = allData.size();
    size_t chunkSize = (totalSize + numThreads - 1) / numThreads; // Ceiling division
    //size_t chunkSize = totalSize / numThreads; //v2 divide logic
    // 2. Launch Tasks
    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = std::min(start + chunkSize, totalSize);
        // size_t end = (i == numThreads-1)?totalSize:start + chunkSize; //v2 divide logic
        if (start < end) {
            // Create Functor
            ChunkFilter task(allData, start, end);
            // Launch Async
            futures.push_back(std::async(std::launch::async, task));
        }
    }

    // 3. Collect Results (.get())
    for (auto& fut : futures) {
        std::vector<int> chunkResult = fut.get(); // Blocking wait
        // Append to main vector
        allValid.insert(allValid.end(), chunkResult.begin(), chunkResult.end());
        // for (int val : chunkResult) {
        //     allValid.push_back(val);
        // } 替代写法
    }

    return allValid;
}
```

#### 💡 Code Walkthrough (Execution Logic)

> **Goal:** Visualize how threads handle the data.
>
>   * **T0 (Main Thread):** Calculates `totalSize = 1000`, `numThreads = 4`. `chunkSize = 250`.
>   * **T0:** Loop 1: Launches **Task A** (Range 0-250) on **Thread 1**. Pushes `future A`.
>   * **T0:** Loop 2: Launches **Task B** (Range 250-500) on **Thread 2**. Pushes `future B`.
>   * **State Check:** T1 and T2 are now running `ProcessChunk::operator()` in parallel. T0 continues launching.
>   * **T0:** Enters "Collection Loop". Calls `futures[0].get()`.
>   * **T0 Status:** **BLOCKED** (Waiting for Thread 1 to finish).
>   * **Thread 1:** Finishes filtering, returns `vector<int>{1, 5, 10...}`. Dies.
>   * **T0:** Unblocks. Appends T1's numbers to `allValid`.
>   * **T0:** Calls `futures[1].get()`. If Thread 2 is already done, returns immediately.
>   * **Result:** `allValid` contains data from all ranges, merged sequentially.

-----

### Question 4: Algorithms & File Output

**What it’s about:**
Using standard algorithms with execution policies on a vectors of underlying smart pointer types:
- `std::copy_if` with an execution policy (from `<execution>`) to copy only valid smart pointers (of question 1) elements into another vector of smart pointer (only valid ones).
- Opening a binary output file
- Using `std::for_each` with an execution policy to write the underlying `int` values (of outcome of `copy_if` algo.) to the file in binary form.

**What to study:**
- `<algorithm>`: `std::copy_if`, `std::for_each`.
- `<execution>` policies: `std::execution::seq`, `par`, `par_unseq` and when they are safe to use.
- Lambdas used with algorithms (capturing containers / streams by reference).
- Basic binary file I/O with `std::ofstream`:
  - Opening with `ios::binary`.
  - Using `.write(reinterpret_cast<const char*>(&value), sizeof(value));`.
  - Using an accessors (like `get()` and etc...) to obtain the raw pointers from the smart pointer (in question one)
- Ensuring operations are thread-safe with chosen execution policies when accessing shared read-only data and a single output stream (based on how it’s used in the question and as taught in class).

**Solution Code:**

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <execution> // std::execution::seq

void write_binary_sequential(const std::vector<DataPtr>& inputData) {
    // 1. 准备目标容器
    std::vector<DataPtr> validPointers;

    // 2. 使用 copy_if 筛选有效指针
    // std::execution::seq 是顺序执行，使用 std::back_inserter 是安全的
    std::copy_if(std::execution::seq, 
                 inputData.begin(), inputData.end(),
                 std::back_inserter(validPointers), // 自动扩容
                 [](const DataPtr& ptr) {
                     // 使用之前定义的 bool 转换或 isValid()
                     return static_cast<bool>(ptr); // ptr->isValid()
                 });

    // 3. 打开二进制文件
    std::ofstream file("data_seq.bin", std::ios::binary);
    if (!file) return;

    // 4. 使用 for_each 写入文件
    // 顺序写入不需要锁
    std::for_each(std::execution::seq, 
                  validPointers.begin(), validPointers.end(),
                  [&file](const DataPtr& ptr) {
                      // 获取底层数据 (假设 operator* 返回 int&)
                      int val = *ptr; 
                      
                      // 二进制写入 (reinterpret_cast 是考点)
                      file.write(reinterpret_cast<const char*>(&val), sizeof(val));
                  });
}

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <execution> // std::execution::par
#include <mutex>     // 必须引入锁

void write_binary_parallel(const std::vector<DataPtr>& inputData) {
    // --- 步骤 1: 并行筛选 (copy_if) ---
    
    // A. 预分配内存
    // 并行 copy_if 不能用 back_inserter，因为 push_back 不安全。
    // 我们先创建一个足够大的容器（最坏情况：所有都有效）。
    std::vector<DataPtr> validPointers(inputData.size());

    // B. 执行并行复制
    // copy_if 返回指向目标容器中"最后一个被复制元素之后"的迭代器
    auto endIt = std::copy_if(std::execution::par, 
                              inputData.begin(), inputData.end(),
                              validPointers.begin(), // 写入预分配的内存
                              [](const DataPtr& ptr) {
                                  return static_cast<bool>(ptr);
                              });

    // C. 调整大小
    // 截断多余的空位，只保留实际复制的元素
    validPointers.resize(std::distance(validPointers.begin(), endIt));


    // --- 步骤 2: 并行写入 (for_each) ---

    // D. 打开文件
    std::ofstream file("data_par.bin", std::ios::binary);
    if (!file) return;

    // E. 准备互斥锁 (Mutex)
    std::mutex fileMutex;

    // F. 执行并行写入
    std::for_each(std::execution::par, 
                  validPointers.begin(), validPointers.end(),
                  [&file, &fileMutex](const DataPtr& ptr) {
                      // 1. 准备数据 (可以在锁外做，提高并发度)
                      int val = *ptr; 

                      // 2. 加锁 (Critical Section)
                      // 只有写入文件这一步必须是串行的
                      std::lock_guard<std::mutex> lock(fileMutex);
                      
                      // 3. 写入
                      file.write(reinterpret_cast<const char*>(&val), sizeof(val));
                  });
}
```

*Note on Q4:* If the professor explicitly asks to use `std::execution::par` for writing, you must mention that `std::ofstream` requires a `mutex` inside the lambda to be thread-safe, otherwise the bytes will be scrambled.

-----

### Next Step

This covers the entire exam simulation.
**Would you like me to explain specific syntax details (like `reinterpret_cast` or `std::move`) or give you a blank template to try coding one of these yourself?**
