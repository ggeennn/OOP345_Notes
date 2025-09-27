# OOP345 Week 6-2: 容器和迭代器 (Containers and Iterations)

## 学习路径图 (Learning Path)
```
容器和迭代器
├── 顺序容器 (Sequential Containers)
│   ├── array (固定大小数组)
│   ├── vector (动态数组)
│   ├── deque (双端队列)
│   ├── forward_list (单向链表)
│   └── list (双向链表)
├── 容器适配器 (Container Adapters)
│   ├── stack (栈)
│   ├── queue (队列)
│   └── priority_queue (优先队列)
└── 迭代器 (Iterators)
    ├── 基本概念
    ├── 成员函数
    ├── 遍历操作
    └── 插入删除
```

## 目录 (Table of Contents)
1. [容器概述 (Containers Overview)](#容器概述-containers-overview)
2. [顺序容器 (Sequential Containers)](#顺序容器-sequential-containers)
3. [容器适配器 (Container Adapters)](#容器适配器-container-adapters)
4. [迭代器 (Iterators)](#迭代器-iterators)
5. [FAQ (常见问题)](#faq-常见问题)
6. [实践示例 (Practice Examples)](#实践示例-practice-examples)
7. [学习建议 (Study Tips)](#学习建议-study-tips)

## 容器概述 (Containers Overview)

### 概念名称 (Containers | 容器) 🟢
- 定义 | Definition
  - 中文解释：容器是用于存储和管理对象集合的类模板，提供不同的数据结构和操作接口
  - 英文解释：Containers are class templates used to store and manage collections of objects, providing different data structures and operation interfaces

- 示例 | Example
  - 实际应用场景：存储学生信息、商品列表、任务队列等数据集合

- 💡实践提示 | Practice Tips
  - 根据具体需求选择合适的容器类型，考虑访问模式、插入删除频率等因素

## 顺序容器 (Sequential Containers)

### 概念名称 (Sequential Containers | 顺序容器) 🟢
- 定义 | Definition
  - 中文解释：顺序容器按顺序存储元素，支持按位置访问和遍历操作
  - 英文解释：Sequential containers store elements in sequence and support positional access and traversal operations

- 示例 | Example
  - 实际应用场景：需要保持元素顺序且支持随机访问的场景

### vector容器 (Vector Container | vector容器) 🟢
- 定义 | Definition
  - 中文解释：`std::vector`是动态数组，支持快速随机访问和尾部插入删除
  - 英文解释：`std::vector` is a dynamic array that supports fast random access and insertion/deletion at the end

- 核心成员函数 | Core Member Functions
  - `vector()` - 默认构造函数，创建一个没有元素的容器
  - `vector(int n)` - 创建一个包含n个元素的容器
  - `vector(int n, const T& t)` - 创建一个包含n个元素，每个元素初始化为值t的容器
  - `vector(const vector& v)` - 复制构造函数，将容器v的内容复制到当前对象
  - `vector(vector&& v) noexcept` - 移动构造函数，将容器v的内容移动到当前对象
  - `~vector()` - 析构函数，销毁容器
  - `vector& operator=(const vector& v)` - 赋值运算符，将容器v的内容复制到当前对象
  - `vector& operator=(vector&& v) noexcept` - 移动赋值运算符，将容器v的内容移动到当前对象
  - `size_t size() const` - 返回当前对象中元素的数量
  - `size_t capacity() const` - 返回当前对象的容量
  - `bool empty() const` - 如果当前对象没有元素则返回true
  - `T& operator[](size_t i)` - 返回元素i的引用
  - `const T& operator[](size_t i) const` - 返回元素i的不可修改引用
  - `T& at(size_t i)` - 返回元素i的引用并检查边界，抛出异常
  - `const T& at(size_t i) const` - 返回元素i的不可修改引用并检查边界，抛出异常
  - `T* data() noexcept` - 返回指向底层数组的指针
  - `const T* data() const noexcept` - 返回指向不可修改底层数组的指针
  - `T& front()` - 返回第一个元素的引用
  - `const T& front() const` - 返回第一个元素的不可修改引用
  - `T& back()` - 返回最后一个元素的引用
  - `const T& back() const` - 返回最后一个元素的不可修改引用
  - `void push_back(const T& t)` - 在容器末尾添加元素t
  - `void pop_back()` - 删除容器的最后一个元素
  - `void clear()` - 删除容器的所有元素

- 详细说明 | Detailed Description
  - `at(int)`成员函数检查接收的索引是否在边界内，而下标运算符不检查边界以提高效率
  - vector对象将其元素存储在连续的存储位置上，访问效率接近数组
  - vector对象将其元素存储在自由存储区，可以根据需要调整大小

- 示例 | Example
  - 实际应用场景：需要频繁随机访问且数据量变化不大的场景

- 💡实践提示 | Practice Tips
  - vector是默认首选的容器类型，性能优异且接口友好

### deque容器 (Deque Container | deque容器) 🟡
- 定义 | Definition
  - 中文解释：`std::deque`是双端队列，支持在两端高效插入删除
  - 英文解释：`std::deque` is a double-ended queue that supports efficient insertion/deletion at both ends

- 核心成员函数 | Core Member Functions
  - `deque()` - 默认构造函数，创建一个空容器
  - `deque(int n)` - 创建一个包含n个元素的容器
  - `deque(int n, const T& d)` - 创建一个包含n个元素，每个元素初始化为值d的容器
  - `deque(const deque& d)` - 复制构造函数，将容器d的内容复制到当前对象
  - `deque(deque&& d) noexcept` - 移动构造函数，将容器d的内容移动到当前对象
  - `~deque()` - 析构函数，销毁容器
  - `deque& operator=(const deque& d)` - 赋值运算符，将容器d的内容复制到当前对象
  - `deque& operator=(deque&& d) noexcept` - 移动赋值运算符，将容器d的内容移动到当前对象
  - `size_t size() const` - 返回当前对象中元素的数量
  - `size_t capacity() const` - 返回当前对象的容量
  - `bool empty() const` - 如果当前对象没有元素则返回true
  - `T& operator[](size_t i)` - 返回元素i的引用
  - `const T& operator[](size_t i) const` - 返回元素i的不可修改引用
  - `T& at(size_t i)` - 返回元素i的引用并检查边界，抛出异常
  - `const T& at(size_t i) const` - 返回元素i的不可修改引用并检查边界，抛出异常
  - `T& front()` - 返回第一个元素的引用
  - `const T& front() const` - 返回第一个元素的不可修改引用
  - `T& back()` - 返回最后一个元素的引用
  - `const T& back() const` - 返回最后一个元素的不可修改引用
  - `void push_back(const T& t)` - 在容器末尾添加元素t
  - `void push_front(const T& t)` - 在容器开头添加元素t
  - `void pop_back()` - 删除容器的最后一个元素
  - `void pop_front()` - 删除容器的第一个元素
  - `void clear()` - 删除容器的所有元素

- 详细说明 | Detailed Description
  - `at(int)`成员函数检查接收的索引是否在边界内，而下标运算符不检查边界以提高效率
  - deque在两端的插入和删除操作是高效的
  - 元素可能分散在内存的不同块中，不保证连续存储

- 示例 | Example
  - 实际应用场景：需要频繁在两端操作的队列场景

### list容器 (List Container | list容器) 🟡
- 定义 | Definition
  - 中文解释：`std::list`是双向链表，适合频繁插入删除操作
  - 英文解释：`std::list` is a doubly linked list, suitable for frequent insertion/deletion operations

- 核心成员函数 | Core Member Functions
  - `list()` - 默认构造函数，创建一个空容器
  - `list(int n)` - 创建一个包含n个元素的容器
  - `list(int n, const T& val)` - 创建一个包含n个元素，每个元素初始化为值val的容器
  - `list(const list& other)` - 复制构造函数，将容器other的内容复制到当前对象
  - `list(list&& other) noexcept` - 移动构造函数，将容器other的内容移动到当前对象
  - `~list()` - 析构函数，销毁容器
  - `list& operator=(const list& other)` - 赋值运算符，将容器other的内容复制到当前对象
  - `list& operator=(list&& other) noexcept` - 移动赋值运算符，将容器other的内容移动到当前对象
  - `size_t size() const` - 返回当前对象中元素的数量
  - `bool empty() const` - 如果当前对象没有元素则返回true
  - `T& front()` - 返回第一个元素的引用
  - `const T& front() const` - 返回第一个元素的不可修改引用
  - `T& back()` - 返回最后一个元素的引用
  - `const T& back() const` - 返回最后一个元素的不可修改引用
  - `void push_back(const T& elem)` - 在容器末尾添加元素elem
  - `void push_front(const T& elem)` - 在容器开头添加元素elem
  - `void pop_back()` - 删除容器的最后一个元素
  - `void pop_front()` - 删除容器的第一个元素
  - `iterator insert(iterator position, const T& elem)` - 在迭代器position位置添加元素elem
  - `iterator erase(const_iterator position)` - 删除迭代器position位置的元素
  - `void clear()` - 删除容器的所有元素

- 详细说明 | Detailed Description
  - list不支持下标运算符和at()成员函数，这些在其他顺序容器中提供直接元素访问的功能
  - list定义了insert()和erase()成员函数，这些函数使用迭代器
  - list针对在较大序列中的任意位置插入和删除元素进行了优化
  - 对于快速随机访问，vector和deque模板更高效

- 示例 | Example
  - 实际应用场景：需要频繁在中间插入删除元素的场景

## 容器适配器 (Container Adapters)

### 概念名称 (Container Adapters | 容器适配器) 🟡
- 定义 | Definition
  - 中文解释：容器适配器是基于基础容器提供特定接口的适配器
  - 英文解释：Container adapters are adapters that provide specific interfaces based on underlying containers

- 示例 | Example
  - 实际应用场景：栈、队列等特定数据结构的使用

### stack适配器 (Stack Adapter | stack适配器) 🟢
- 定义 | Definition
  - 中文解释：`std::stack`提供后进先出(LIFO)的数据结构接口
  - 英文解释：`std::stack` provides a last-in, first-out (LIFO) data structure interface

- 核心成员函数 | Core Member Functions
  - `explicit stack()` - 默认构造函数，创建一个没有元素的栈
  - `explicit stack(const Container& c)` - 创建一个栈，初始化为容器c的副本
  - `stack& operator=(const stack& s)` - 赋值运算符，将栈s的内容复制到当前对象
  - `~stack()` - 析构函数，销毁栈
  - `size_t size() const` - 返回当前对象中元素的数量
  - `bool empty() const` - 如果当前对象没有元素则返回true
  - `T& top()` - 返回栈顶元素的引用
  - `const T& top() const` - 返回栈顶元素的不可修改引用
  - `void push(const T& t)` - 在栈顶添加元素t
  - `void pop()` - 删除栈顶元素

- 详细说明 | Detailed Description
  - stack默认使用deque作为底层容器
  - stack提供LIFO（后进先出）的数据结构接口
  - 只能访问栈顶元素，不支持随机访问

- 示例 | Example
  - 实际应用场景：函数调用栈、撤销操作等

### queue适配器 (Queue Adapter | queue适配器) 🟢
- 定义 | Definition
  - 中文解释：`std::queue`提供先进先出(FIFO)的数据结构接口
  - 英文解释：`std::queue` provides a first-in, first-out (FIFO) data structure interface

- 核心成员函数 | Core Member Functions
  - `explicit queue()` - 默认构造函数，创建一个没有元素的队列
  - `explicit queue(const Container& c)` - 创建一个队列，初始化为容器c的副本
  - `size_t size() const` - 返回当前对象中元素的数量
  - `bool empty() const` - 如果当前对象没有元素则返回true
  - `void push(const T& t)` - 在队列末尾添加元素t
  - `void pop()` - 删除队列的第一个元素
  - `T& front()` - 返回队列第一个元素的引用
  - `const T& front() const` - 返回队列第一个元素的不可修改引用
  - `T& back()` - 返回队列最后一个元素的引用
  - `const T& back() const` - 返回队列最后一个元素的不可修改引用

- 详细说明 | Detailed Description
  - queue默认使用deque作为底层容器
  - queue提供FIFO（先进先出）的数据结构接口
  - stack模板中缺少最后4个成员函数

- 示例 | Example
  - 实际应用场景：任务队列、消息队列等

## 迭代器 (Iterators)

### 概念名称 (Iterators | 迭代器) 🟢
- 定义 | Definition
  - 中文解释：迭代器是用于遍历容器元素的抽象指针，提供统一的访问接口
  - 英文解释：Iterators are abstract pointers used to traverse container elements, providing a unified access interface

- 核心成员函数 | Core Member Functions
  - `iterator begin() noexcept` - 返回指向序列中第一个元素的迭代器
  - `iterator end() noexcept` - 返回指向序列末尾后一个位置的迭代器
  - `const_iterator cbegin() const noexcept` - 返回指向序列中第一个元素的常量迭代器
  - `const_iterator cend() noexcept` - 返回指向序列末尾后一个位置的常量迭代器

- 迭代器操作 | Iterator Operations
  - `++iterator` - 自增运算符，将迭代器更新为指向下一个元素
  - `--iterator` - 自减运算符，将迭代器更新为指向前一个元素
  - `*iterator` - 解引用运算符，返回迭代器指向元素的值

- 详细说明 | Detailed Description
  - 迭代器模拟了简单数组中原始指针的访问方式
  - 不支持连续存储的容器类需要迭代器来访问其元素
  - 使用迭代器可以在序列中插入元素或从中删除元素

- 示例 | Example
  - 实际应用场景：遍历容器元素、范围操作等

- 💡实践提示 | Practice Tips
  - 迭代器提供了一种统一的容器访问方式，类似于指针操作

### 迭代器类型 (Iterator Types | 迭代器类型) 🟢
- 定义 | Definition
  - 中文解释：不同容器支持不同类型的迭代器，功能各异
  - 英文解释：Different containers support different types of iterators with varying capabilities

- 详细说明 | Detailed Description
  - 迭代器的定义形式为：`Container<type>::iterator identifier`
  - 例如：`std::vector<double>::iterator iter`

- 示例 | Example
  - 实际应用场景：根据容器类型选择合适的迭代器

### 迭代器操作 (Iterator Operations | 迭代器操作) 🟢
- 定义 | Definition
  - 中文解释：迭代器支持指针般的操作，包括解引用、自增等
  - 英文解释：Iterators support pointer-like operations including dereferencing, incrementing, etc.

- 核心操作 | Core Operations
  - `iterator = container.begin()` - 获取指向第一个元素的迭代器
  - `iterator != container.end()` - 检查是否到达末尾
  - `++iterator` - 移动到下一个元素
  - `*iterator` - 访问当前元素的值

- 详细说明 | Detailed Description
  - 可以使用auto关键字简化迭代器声明
  - 范围for循环提供了更简洁的遍历方式

- 示例 | Example
  - 实际应用场景：遍历访问容器元素

## 原文引用 (Source Quote)
> 原文：[By default, use vector when you need a container]
> Source: [By default, use vector when you need a container]

💡 解析步骤 | Analysis Steps:
1. 关键词提取 | Key Terms:
   - vector (向量容器)
   - default (默认选择)
   - container (容器)

2. 核心概念 | Core Concepts:
   - 容器选择的最佳实践

3. 简化解释 | Simplified Explanation:
   - vector通常是容器类型的首选

4. 具体示例 | Concrete Examples:
   - 各种容器的性能对比和适用场景

## 复杂概念处理 (Complex Concept Processing)
1. 分解步骤 | Breaking Down
   - 识别关键词：Sequential Containers
   - 提取核心概念：容器分类和特性
   - 理解概念关系：不同容器类型的适用场景

2. 简化解释 | Simplification
   - 使用类比：vector像可变长的数组，list像链条
   - 提供具体例子：vector用于随机访问，list用于频繁插入删除
   - 从简单到复杂：从基本操作到高级算法应用

3. 代码示例 | Code Examples
   - 最小可运行示例：展示各种容器的基本用法
   - 逐步解释代码：详细说明容器的特性和用法
   - 注释双语对照：中英文注释并存

## 代码示例 (Code Examples)

### vector基本用法 (Vector Basic Usage)
```cpp
// 完整示例结构 | Complete example structure
#include <vector>
#include <iostream>

// 1. 目的说明 | Purpose explanation
//    演示vector的基本操作和特性
// 2. 预期输出 | Expected output
//    显示vector的动态增长和访问操作
// 3. 关键步骤 | Key steps
//    创建vector、添加元素、访问修改

int main() {
    // 代码实现 | Implementation
    std::vector<double> prices; // 初始为空

    // 检查是否为空
    if (prices.empty()) {
        std::cout << "prices向量为空" << std::endl;
    }

    // 添加元素
    prices.push_back(10.43); // 添加10.43
    prices.push_back(20.54); // 添加20.54
    prices.push_back(32.43); // 添加32.43

    // 遍历显示
    std::cout << "所有价格: ";
    for (int i = 0; i < prices.size(); i++) {
        std::cout << prices[i] << "  ";
    }
    std::cout << std::endl;

    // 修改第一个元素
    prices.front() = 54.11;
    // 删除最后一个元素
    prices.pop_back();

    // 再次显示
    std::cout << "修改后: ";
    for (int i = 0; i < prices.size(); i++) {
        std::cout << prices[i] << "  ";
    }
    std::cout << std::endl;

    return 0;
}
```

### deque双端操作 (Deque Double-Ended Operations)
```cpp
// 完整示例结构 | Complete example structure
#include <deque>
#include <iostream>

// 1. 目的说明 | Purpose explanation
//    演示deque的双端操作特性
// 2. 预期输出 | Expected output
//    显示deque在两端的插入删除操作
// 3. 关键步骤 | Key steps
//    创建deque、前后端操作、遍历访问

int main() {
    // 代码实现 | Implementation
    std::deque<double> prices(3, 10.50); // 初始化3个10.50

    // 修改最后一个元素
    prices.back() = 32.43;
    // 删除第一个元素
    prices.pop_front();

    // 显示当前状态
    std::cout << "当前deque: ";
    for (int i = 0; i < prices.size(); i++) {
        std::cout << prices[i] << "  ";
    }
    std::cout << std::endl;

    // 在前端添加元素
    prices.push_front(5.64);
    prices.push_front(20.31);

    // 修改第二个元素
    prices.at(1) += 10.0;

    // 最终显示
    std::cout << "最终结果: ";
    for (int i = 0; i < prices.size(); i++) {
        std::cout << prices[i] << "  ";
    }
    std::cout << std::endl;

    return 0;
}
```

### list插入删除操作 (List Insertion and Deletion)
```cpp
// 完整示例结构 | Complete example structure
#include <list>
#include <iostream>

// 1. 目的说明 | Purpose explanation
//    演示list的插入删除操作
// 2. 预期输出 | Expected output
//    显示list在任意位置的插入删除
// 3. 关键步骤 | Key steps
//    创建list、使用迭代器定位、插入删除

int main() {
    // 代码实现 | Implementation
    std::list<double> prices;

    // 添加初始元素
    prices.push_back(10.43);
    prices.push_back(20.54);
    prices.push_back(32.43);

    // 在末尾前插入12.52
    prices.insert(--prices.end(), 12.52);

    // 删除第二个元素
    prices.erase(++prices.begin());

    // 显示结果
    std::cout << "最终列表: ";
    for (auto it = prices.begin(); it != prices.end(); it++) {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 迭代器遍历 (Iterator Traversal)
```cpp
// 完整示例结构 | Complete example structure
#include <vector>
#include <iostream>

// 1. 目的说明 | Purpose explanation
//    演示迭代器的基本用法
// 2. 预期输出 | Expected output
//    显示迭代器的遍历操作
// 3. 关键步骤 | Key steps
//    创建容器、使用迭代器遍历、访问元素

int main() {
    // 代码实现 | Implementation
    std::vector<double> prices;
    prices.push_back(10.43);
    prices.push_back(20.54);
    prices.push_back(32.43);

    // 使用迭代器遍历
    std::cout << "使用迭代器遍历: ";
    for (auto it = prices.begin(); it != prices.end(); it++) {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;

    // 使用auto简化
    std::cout << "使用auto简化: ";
    for (auto price : prices) {
        std::cout << price << "  ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 常见误区 (Common Mistakes)

### 英文
1. **Iterator Invalidation**: Using invalidated iterators after container modification
2. **Container Selection**: Choosing wrong container type for specific use cases
3. **Bounds Checking**: Forgetting that operator[] doesn't perform bounds checking

### 中文
1. **迭代器失效**: 在容器修改后使用已失效的迭代器
2. **容器选择**: 为特定用例选择错误的容器类型
3. **边界检查**: 忘记operator[]不执行边界检查

## 实践应用 (Practical Application)

### 基础应用（必做）| Basic application (Required)
1. 掌握vector的基本操作（添加、访问、删除）
2. 理解迭代器的基本概念和用法
3. 学会选择合适的容器类型

### 进阶应用（选做）| Advanced application (Optional)
1. 实现自定义容器适配器
2. 使用迭代器进行复杂遍历操作
3. 性能优化和内存管理

## 问题诊断 (Problem Diagnosis)

### 常见错误示例 | Common error examples
```cpp
// 错误示例：迭代器失效
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = vec.begin() + 2; // 指向元素3
vec.push_back(6); // 可能导致重新分配，it失效
std::cout << *it << std::endl; // 未定义行为
```

### 调试技巧 | Debugging tips
1. 使用断言检查迭代器有效性
2. 利用调试器查看容器状态
3. 检查迭代器是否在有效范围内

### 解决方案 | Solutions
1. 在修改容器后重新获取迭代器
2. 使用容器提供的成员函数而非直接操作
3. 合理使用at()函数进行边界检查

## 代码优化 (Code Optimization)

### 代码风格 | Coding style
- 使用auto推导迭代器类型
- 合理使用const迭代器
- 遵循RAII原则管理资源

### 性能优化 | Performance optimization
- 预留vector容量避免重新分配
- 选择合适的容器类型
- 减少不必要的拷贝操作

### 最佳实践 | Best practices
- 优先使用vector unless specific needs require other containers
- 使用范围for循环简化迭代器操作
- 注意迭代器失效的情况

## 快速复习指南 (Quick Review Guide) 📝
- Day 1: vector和基本迭代器操作
- Day 2: deque和list的特性对比
- Day 3: 容器适配器和高级迭代器用法

## 重点概念框架 (Key Concepts Framework)
```
核心概念
├── 基础知识
│   ├── 容器分类
│   ├── 迭代器概念
│   └── 基本操作
└── 进阶内容
    ├── 性能优化
    ├── 容器选择
    └── 高级算法
```

## 版本控制 (Version Control)
更新日期：2024-09-27
版本号：v1.0
更新内容：
- 初始创建容器和迭代器学习文档
- 整合顺序容器和容器适配器知识
- 添加迭代器操作和示例代码

## 待办标记 (TODO Marks)
TODO: 需要补充更多容器适配器的详细用法
NOTE: 迭代器分类和算法部分需要扩展
