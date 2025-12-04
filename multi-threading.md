# C++ Multithreading & Performance Knowledge Base
# C++ 多线程与性能优化知识库

---

## 1. 基础概念 (Fundamentals)

| 术语 (Term) | 解释 (Explanation) |
| :--- | :--- |
| **Process (进程)** | 拥有独立内存空间的程序实例。切换开销大 (Heavyweight)。 |
| **Thread (线程)** | 进程内的执行流，共享内存空间。切换开销小 (Lightweight)。 |
| **Context Switch** | CPU 保存当前任务状态并加载新任务状态的过程。 |
| **Race Condition** | 多个线程同时访问共享内存且至少有一个是写入，导致未定义行为。 |
| **Deadlock (死锁)** | 两个或多线程互相等待对方释放资源，导致永久阻塞 (AB-BA 问题)。 |
| **Latency (延迟)** | 完成一次通信（如内存读取、I/O）所需的时间。 |

---

## 2. 线程管理 (Thread Management - `<thread>`)

| 知识点 (Key Point) | 细节 (Details) |
| :--- | :--- |
| **`std::thread`** | 代表一个系统线程的句柄。**不可复制 (Non-copyable)**，只能移动 (Move)。 |
| **RAII Rule** | `std::thread` 析构时如果处于 `joinable` 状态，程序会崩溃 (`std::terminate`)。 |
| **`join()`** | **阻塞**主线程，直到子线程执行完毕。实现同步。 |
| **`detach()`** | 将句柄与后台线程分离。后台线程成为守护线程。 |
| **参数传递** | 默认按值拷贝 (Pass-by-value)。若需引用，必须用 **`std::ref()`** 包装。 |
| **容器管理** | 不能用数组 (`thread t[10]`) 因为默认构造无意义。应使用 **`std::vector<std::thread>`** 配合 **`emplace_back`**。 |

---

## 3. 数据安全与互斥 (Data Safety & Mutexes - `<mutex>`, `<atomic>`)

| 工具 (Tool) | 描述 (Description) |
| :--- | :--- |
| **`std::atomic<T>`** | 用于保护单个变量 (int, bool)。无锁，极快。防止数据撕裂。 |
| **`std::mutex`** | 互斥锁。保护临界区 (Critical Section)。一次只允许一个线程进入。 |
| **`std::lock_guard`** | **基础 RAII 锁**。构造时 `lock`，析构时 `unlock`。**不可手动解锁**。 |
| **`std::unique_lock`** | **灵活 RAII 锁**。可以手动 `lock()`/`unlock()`。适合在临界区中包含耗时操作 (如 I/O, sleep) 时暂时释放锁以提高并发。 |
| **`std::scoped_lock`** | **(C++17) 防死锁神器**。可以同时锁定多个互斥量，内部算法保证无死锁。 |

---

## 4. 高级锁机制 (Advanced Locking - `<shared_mutex>`)

针对“读多写少”场景的优化。

| 组件 (Component) | 用途 (Usage) |
| :--- | :--- |
| **`std::shared_mutex`** | 提供共享和独占两种模式的锁资源。 |
| **`std::shared_lock`** | **读锁 (Reader)**。允许多个线程同时持有。 |
| **`std::unique_lock`** | **写锁 (Writer)**。独占访问，阻塞所有读者和其他写者。 |

---

## 5. 异步结果与通信 (Async & Futures - `<future>`)

解决 `std::thread` 无法直接返回值的问题。

| 组件 (Component) | 作用 (Role) |
| :--- | :--- |
| **`std::promise<T>`** | **生产者 (Provider)**。设置值 (`set_value`)。不可复制，传递给线程时需用 **`std::move`**。 |
| **`std::future<T>`** | **消费者 (Receiver)**。获取值 (`get`)。调用 `get()` 时会阻塞直到值就绪。 |
| **`std::async`** | 高级封装。自动创建线程和 Promise/Future 对。 |
| **`std::launch::async`** | `async` 策略：**强制**启动新线程 (真正的并发)。 |
| **`std::launch::deferred`** | `async` 策略：延迟执行，直到调用 `.get()` 时才在当前线程运行 (串行)。 |

---

## 6. 并行算法 (Parallel Algorithms - `<execution>`)

C++17 引入，利用多核加速 STL 算法。

| 策略 (Policy) | 行为 (Behavior) |
| :--- | :--- |
| **`std::execution::seq`** | **串行**。也就是老版本的默认行为。 |
| **`std::execution::par`** | **并行**。利用多线程加速。 |
| **`std::execution::par_unseq`** | **并行 + 向量化**。利用多线程 + SIMD 指令集 (极速，但限制更多)。 |

##########################################################

# C++ Key Concepts Summary / 知识点总结

## 1. Multi-threading & Concurrency (多线程与并发)

| Term (术语) | Explanation (解释) |
| :--- | :--- |
| **std::thread::hardware_concurrency()** | **Hardware Thread Count (硬件线程数)**<br>返回 CPU 支持的并发线程数量。常用于决定开启多少个线程最有效率。 |
| **std::promise** | **The "Sender" (发送端)**<br>一个“承诺”对象，用于在线程中**设置 (Set)** 值。它承诺将来会提供一个结果。 |
| **std::future** | **The "Receiver" (接收端)**<br>一个“未来”对象，用于在另一线程中**等待并获取 (Wait & Get)** `promise` 设置的结果。 |
| **Range Splitting** | **Work Partitioning (任务分割)**<br>将总任务量 (`totalCount`) 除以线程数 (`numThreads`) 得到 `chunkSize`，利用模运算 (`%`) 处理剩余部分 (`leftover`)。 |
| **Execution Policy** | **Parallel Algorithms (执行策略)**<br>C++17 引入。作为标准算法（如 `std::sort`）的第一个参数传入，如 `std::execution::par`，指示编译器自动并行化执行。 |

---

## 2. Macros & Preprocessor (宏与预处理器)

| Term (术语) | Explanation (解释) |
| :--- | :--- |
| **#define MUTEXED_IO(expr)** | **Thread-safe I/O Macro (线程安全 I/O 宏)**<br>通过宏定义封装 `std::cout` 操作，确保多线程环境下输出不混乱。 |
| **std::lock_guard** | **RAII Lock Wrapper (自动锁守卫)**<br>构造时自动加锁，作用域结束时自动解锁。防止忘记解锁导致的死锁。 |
| **do { ... } while(false)** | **Macro Scope Trick (宏作用域技巧)**<br>创建单次执行的独立作用域。允许宏像普通函数一样安全地接受分号 `;`，并在 `if/else` 语句中避免语法错误。 |
| **Backslash ( \ )** | **Line Continuation (行连接符)**<br>告诉预处理器宏定义未结束，下一行仍属于当前宏。用于编写多行宏。 |
| **#undef** | **Undefine Macro (取消定义)**<br>取消之前定义的宏。常用于重定义宏的值（如更新 `VERSION`）或清理命名空间冲突。 |

---

## 3. File Inclusion (文件包含)

| Term (术语) | Explanation (解释) |
| :--- | :--- |
| **#include <...>** | **System Headers (系统头文件)**<br>使用尖括号（如 `<iostream>`）。编译器直接在**标准系统目录**中查找文件。 |
| **#include "..."** | **Custom Headers (自定义头文件)**<br>使用双引号（如 `"my_utils.h"`）。编译器**首先在当前源文件目录**查找，找不到再去系统目录。支持相对路径或绝对路径。 |