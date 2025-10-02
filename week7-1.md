# OOP345_Week7_Algorithms.md 📚

## 1. 文档基本规范 (Basic Document Standards) 📑

### 1.1 文件命名规则 (File Naming Convention)
`[课程代码]_[Week/Chapter]_[主题].md`
例如：`OOP345_Week7_Algorithms.md`

### 1.2 基本文档结构 (Basic Document Structure)
1. 标题和概述 (Title and Overview)
2. 学习路径图 (Learning Path)
3. 目录 (Table of Contents)
4. 知识点详解 (Detailed Content)
5. FAQ (常见问题)
6. 实践示例 (Practice Examples)
7. 学习建议 (Study Tips)

## 2. 内容格式规范 (Content Format Standards) 📝

### 2.1 知识点格式 (Knowledge Point Format)

### Algorithms (English Name | 算法) 🟢 基础概念
- 定义 | Definition
  - C++ STL 的算法类别提供了一系列通用的编程解决方案，这些方案在容器内的元素范围上操作。
  - The algorithms category of the C++ STL provides a variety of common programming solutions that operate on ranges of elements within containers.
- 示例 | Example
  - 可用于自定义类型集合以及 STL 容器。
  - Usable with our own collections of types as well as with the STL containers.
- 💡实践提示 | Practice Tips
  - 默认情况下，优先使用算法而不是循环。
  - By default, prefer algorithms to loops.

### Functional Library (English Name | 函数库) 🟢 基础概念
- 定义 | Definition
  - 函数库定义了模板化的函数对象，这些函数对象可以作为参数传递给其他函数，包括算法模板。
  - The functional library defines templated function-objects that can be passed as arguments to other functions, including the algorithm templates.
  - 该库在 `<functional>` 头文件中定义，由三个不同的部分组成：Wrapper Class Templates, Function Templates, Operator Classes。
  - This library is defined in the header file `<functional>` and consists of three distinct parts: Wrapper Class Templates, Function Templates, Operator Classes.

#### Wrapper Class Templates (English Name | 包装器类模板) 🟡 中级概念
- 定义 | Definition
  - 包装器类模板是管理对某些底层对象访问的模板。
  - The wrapper class templates are templates that manage access to some underlying object.
- 示例 | Example
  - 包括 `function` 和 `reference_wrapper`。
  - These templates include `function` and `reference_wrapper`.

##### `std::function` Wrapper Template (English Name | `std::function` 包装器模板) 🟡 中级概念
- 定义 | Definition
  - 创建一个函数对象包装器，用于函数、其他函数对象或 lambda 表达式。
  - Creates a function-object wrapper for a function, another function-object or a lambda expression.
- 示例 | Example
  ```cpp
  // Functional - function wrapper
  // function_wrapper.cpp

  #include <iostream>
  #include <functional>

  // a simple function
  long multiply(long x, long y) { return x * y; }

  // a functor
  struct Multiply
  {
      long operator()(long x, long y) { return x * y; }
  };

  int main()
  {
      std::function<long(long, long)> f1 = multiply;
      std::function<long(long, long)> f2 = Multiply();
      std::function<long(long, long)> f3 = [](long x, long y)
                                           {
                                              return x * y;
                                           };

      std::cout << "f1(10, 2) = " << f1(10, 2) << std::endl; // Expected output: 20
      std::cout << "f2(10, 2) = " << f2(10, 2) << std::endl; // Expected output: 20
      std::cout << "f3(10, 2) = " << f3(10, 2) << std::endl; // Expected output: 20
  }
  ```
  - 实际应用场景 | Actual application scenario
    - 统一不同可调用对象（函数、函数对象、lambda）的接口。
    - Unifying interfaces for different callable objects (functions, functors, lambdas).

##### `reference_wrapper` Template (English Name | `reference_wrapper` 模板) 🟡 中级概念
- 定义 | Definition
  - 创建一个类，用于方便地复制和分配函数以及对象的引用。
  - Creates a class that facilitates the copying and assigning of references for functions as well as objects.
  - 允许在 C++ 标准禁止普通引用的地方（例如，在容器类中）使用引用。
  - This template allows utilization of references where the C++ standard forbid normal references (for example, in container classes).
- 示例 | Example
  ```cpp
  // Functional - reference wrapper
  // reference_wrapper_vector.cpp

  #include <iostream>
  #include <vector>
  #include <functional>

  int main()
  {
      std::vector<double> original(5, 10.3);
      std::vector<std::reference_wrapper<double>>  references(original.begin(), original.end());

      for (auto& e : original)
          e *= 3;

      for (auto e : references)
          std::cout << e << " "; // Expected output: 30.9 30.9 30.9 30.9 30.9
      std::cout << std::endl;
  }
  ```
  - 实际应用场景 | Actual application scenario
    - 在容器中存储引用。
    - Storing references inside container objects.
  - 💡实践提示 | Practice Tips
    - `std::reference_wrapper` 可以用于任何可以使用常规引用的地方。
    - `std::reference_wrapper` can be used anywhere a regular reference can be used.

#### Function Templates (English Name | 函数模板) 🟡 中级概念
- 定义 | Definition
  - 函数模板包括 `bind`、`ref` 和 `cref`。
  - The function templates include `bind`, `ref`, and `cref`.

##### `bind` (English Name | 绑定) 🟡 中级概念
- 定义 | Definition
  - 将一个或多个参数绑定到函数对象。
  - Binds one or more arguments to a function object.
  - `std::bind` 通过复制其值来存储传入的参数。
  - `std::bind` stores the arguments passed in by copying their values.
- 示例 | Example
  ```cpp
  // Functional - bind a function to its arguments
  // bind.cpp

  #include <iostream>
  #include <functional>

  double multiply(double x, double y) { return x * y; }

  int main()
  {
      auto p = std::bind(multiply, 10, 3);
      std::cout << "Product = " << p() << std::endl; // Expected output: 30
  }
  ```
  - 实际应用场景 | Actual application scenario
    - 创建一个带有预设参数的函数对象。
    - Creating a function object with preset arguments.

##### `ref` (English Name | 引用) 🟡 中级概念
- 定义 | Definition
  - 函数模板 `std::ref()` 返回一个 `std::reference_wrapper` 实例，用于提供的参数。
  - The function template `std::ref()` returns an `std::reference_wrapper` instance for the argument supplied.
- 示例 | Example
  ```cpp
  // Functional - create a reference wrapper
  // ref.cpp

  #include <iostream>
  #include <functional>

  void increment(int& x, int& y) { ++x, ++y; }

  int main()
  {
      int a = 10, b = 20;
      auto inc = bind(increment, std::ref(a), b); // a by reference, b by value

      inc();

      std::cout << "a = " << a << std::endl; // Expected output: 11
      std::cout << "b = " << b << std::endl; // Expected output: 20
  }
  ```
  - 实际应用场景 | Actual application scenario
    - 将参数以引用的方式传递给 `std::bind` 或其他接受函数对象的函数。
    - Passing arguments by reference to `std::bind` or other functions that accept function objects.

#### Operator Class Templates (English Name | 运算符类模板) 🟡 中级概念
- 定义 | Definition
  - 运算符类模板为核心语言中存在的大多数运算符定义了函数对象等价物。
  - The operator class templates define function object equivalents for most of the operators present in the core language.
- 示例 | Example
  - 包括 `bit_and`, `plus`, `multiplies`, `equal_to`, `greater` 等。
  - Examples include `bit_and`, `plus`, `multiplies`, `equal_to`, `greater`, etc.
- 💡实践提示 | Practice Tips
  - 这些对象指定了算法要执行的操作，可以作为 lambda 表达式或完整函数对象的替代品传递给算法。
  - These objects specify the operation to be performed by an algorithm and can be passed to an algorithm in place of a lambda expression or full-blown function object.

### Algorithm Library (English Name | 算法库) 🟢 基础概念
- 定义 | Definition
  - `algorithm` 函数模板对序列中的元素范围执行常见操作。
  - The `algorithm` function templates perform common operations on ranges of elements in a sequence.
  - 函数调用以迭代器形式接受这些范围作为参数。
  - The function calls accept these ranges as arguments in the form of iterators.
  - 它们不改变任何序列的大小或存储分配。
  - They do not change the size or storage allocation of any sequence.
  - 定义在 `<algorithm>` 头文件中，包括 Queries, Modifiers, Manipulators。
  - Defined in header `<algorithm>`, consisting of Queries, Modifiers, Manipulators.
- 💡实践提示 | Practice Tips
  - 符号 `[f, l)` 指的是从迭代器 `f` 标识的位置开始，延伸到迭代器 `l` 标识的位置之前的范围。
  - The notation `[f, l)` refers to the range starting at the position identified by iterator `f` and extending to the position immediately before that identified by iterator `l`.

#### Queries (English Name | 查询) 🟡 中级概念
- 定义 | Definition
  - 查询类模板用于检查序列中的元素。
  - The query class templates are used to inspect elements in a sequence.
- 示例 | Example
  - `all_of`, `any_of`, `none_of`, `for_each`, `find`, `find_if`, `find_if_not`, `count`, `count_if`。
  - Examples include `all_of`, `any_of`, `none_of`, `for_each`, `find`, `find_if`, `find_if_not`, `count`, `count_if`.

##### `count` (English Name | 计数) 🟡 中级概念
- 定义 | Definition
  - 计算指定值在范围 `[f, l)` 内出现的次数。
  - Counts the occurrences of a specific value within the range `[f, l)`.
- 示例 | Example
  ```cpp
  // Algorithms - Count
  // count.cpp

  #include <array>
  #include <algorithm>
  #include <iostream>

  int main()
  {
      std::array<int, 11> a = {1, 12, 4, 5, 8, 9, 12, 13, 16, 18, 12};

      int n = std::count(a.begin(), a.end(), 12);

      std::cout << "12 occurs "<< n << " times.\n"; // Expected output: 12 occurs 3 times.
  }
  ```

##### `count_if` (English Name | 条件计数) 🟡 中级概念
- 定义 | Definition
  - 计算范围 `[f, l)` 内满足谓词的元素数量。
  - Counts how many elements within the range `[f, l)` satisfy a predicate.
- 示例 | Example
  ```cpp
  // Algorithms - Count If
  // count_if.cpp

  #include <algorithm>
  #include <iostream>

  int main()
  {
      int a[] = {1, 2, 4, 5, 8, 9, 12, 13, 16, 18, 22};

      int n = std::count_if(a, a + 11, [](int i)
                                       {
                                           return !(i & 1); // Check if even
                                       });

      std::cout << "Even numbers = "<< n << std::endl; // Expected output: Even numbers = 7
  }
  ```

#### Modifiers (English Name | 修改器) 🟡 中级概念
- 定义 | Definition
  - 修改器类模板用于修改序列中的元素。
  - The modifier class templates are used to modify elements in a sequence.
- 示例 | Example
  - `copy`, `copy_if`, `transform`, `fill`, `fill_n`, `replace`, `replace_if`。
  - Examples include `copy`, `copy_if`, `transform`, `fill`, `fill_n`, `replace`, `replace_if`.

##### `copy` (English Name | 复制) 🟡 中级概念
- 定义 | Definition
  - 将范围 `[f, l)` 中的所有元素复制到从 `o` 开始的范围。
  - Copies all of the elements from range `[f, l)` into the range starting at `o`.
- 示例 | Example
  ```cpp
  // Algorithms - Copy
  // copy_.cpp

  #include <vector>
  #include <algorithm>
  #include <iostream>

  int main()
  {
      std::vector<double> v(4, 10.34); // {10.34, 10.34, 10.34, 10.34}
      std::vector<double> c(4, 20.68); // {20.68, 20.68, 20.68, 20.68}

      std::copy(v.begin(), v.begin() + 2, c.begin() + 1); // Copy first 2 elements of v to c starting at index 1

      for (auto e : c)
          std::cout << e << std::endl;
      /* Expected output:
      20.68
      10.34
      10.34
      20.68
      */
  }
  ```

##### `copy_if` (English Name | 条件复制) 🟡 中级概念
- 定义 | Definition
  - 将范围 `[f, l)` 中满足谓词的所有元素复制到从 `o` 开始的范围。
  - Copies all elements from range `[f, l)` that satisfy the predicate into the range starting at `o`.
- 示例 | Example
  ```cpp
  // Algorithms - Copy If
  // copy_if.cpp

  #include <vector>
  #include <algorithm>
  #include <iostream>

  int main()
  {
      std::vector<int> v = {1, 2, 4, 5, 7, 8, 10, 13, 17, 21, 43};
      std::vector<int> c(15); // Destination vector, needs to be large enough

      std::copy_if(v.begin(), v.begin() + 10, c.begin(), [](int i) -> bool
          {
              return i % 2; // Check if odd
          });

      for (auto e : c)
          std::cout << e << std::endl;
      /* Expected output (first 6 elements are copied, rest are default initialized to 0):
      1
      5
      7
      13
      17
      21
      0
      ...
      */
  }
  ```

##### `transform` (English Name | 转换) 🟡 中级概念
- 定义 | Definition
  - 对范围 `[f, l)` 中的所有元素应用一元操作 `u`，并将结果存储在从 `o` 开始的范围。
  - Applies the unary operation `u` to all of the elements from range `[f, l)` and stores the result starting at `o`.
  - 也可以对两个范围的元素应用二元操作 `b`。
  - Can also apply a binary operation `b` to elements from two ranges.
- 示例 | Example
  ```cpp
  // Algorithms - Transform - Unary Operation
  // transform_u.cpp

  #include <vector>
  #include <algorithm>
  #include <iostream>

  int main()
  {
      std::vector<int> v = {1, 2, 4, 5, 7, 8, 10, 13, 17, 21, 43};
      std::vector<int> c(11);

      std::transform(v.begin(), v.end(), c.begin(), [](int i)
          {
              return 3 * i; // Unary operation: multiply by 3
          });

      for (auto e : c)
          std::cout << e << std::endl;
      /* Expected output:
      3
      6
      12
      15
      21
      24
      30
      39
      51
      63
      129
      */
  }
  ```
  ```cpp
  // Algorithms - Transform - Binary Operation
  // transform_b.cpp

  #include <vector>
  #include <algorithm>
  #include <functional>
  #include <iostream>

  int main()
  {
      std::vector<int> a = {1, 2, 4, 5, 7, 8, 10, 13, 17, 21, 43};
      std::vector<int> b = {2, 1, 0, 1, 2, 3, 16, 23, 21, 17, 32};
      std::vector<int> c(11);

      std::transform(a.begin(), a.end(), b.begin(), c.begin(), std::plus<int>()); // Binary operation: addition

      for (auto e : c)
          std::cout << e << std::endl;
      /* Expected output:
      3
      3
      4
      6
      9
      11
      26
      36
      38
      38
      75
      */
  }
  ```

#### Manipulators (English Name | 操作器) 🟡 中级概念
- 定义 | Definition
  - 操作器类模板用于重新排列序列中的元素。
  - The manipulator class templates are used to rearrange elements in a sequence.
- 示例 | Example
  - `sort`, `merge`。
  - Examples include `sort`, `merge`.

##### `sort` (English Name | 排序) 🟡 中级概念
- 定义 | Definition
  - 对范围 `[f, l)` 中的元素进行升序排序。
  - Sorts the elements in the range `[f, l)` in ascending order.
  - 可以使用自定义比较器 `compare` 进行排序。
  - Can sort using a custom comparator `compare`.
- 示例 | Example
  ```cpp
  // Algorithms - Sort Descending Order
  // sort.cpp

  #include <iostream>
  #include <algorithm>
  #include <functional>

  int main()
  {
      int a[] = {3, 2, 4, 1};

      std::sort(a, &a[4], std::greater<int>()); // Sort in descending order using std::greater

      for(int e : a)
          std::cout << e <<  std::endl;
      /* Expected output:
      4
      3
      2
      1
      */
  }
  ```

### Numeric Library (English Name | 数值库) 🟢 基础概念
- 定义 | Definition
  - 数值库提供了标准的模板化函数，用于对序列中的元素范围执行数值操作。
  - The numeric library provides standard templated functions for performing numeric operations on ranges of elements in a sequence.
- 示例 | Example
  - `accumulate`, `inner_product`, `partial_sum`。
  - Examples include `accumulate`, `inner_product`, `partial_sum`.

#### `accumulate` (English Name | 累加) 🟡 中级概念
- 定义 | Definition
  - 将范围 `[f, l)` 中的值累加到 `init` 并返回结果。
  - Accumulates the values in the range `[f, l)` to `init` and returns the result.
  - 可以使用二元操作 `boper` 进行累加。
  - Can accumulate using a binary operation `boper`.
- 示例 | Example
  ```cpp
  // Algorithms - Accumulate
  // accumulate.cpp

  #include <iostream>
  #include <numeric>

  int main()
  {
      int a[] = {3, 2, 4, 1}, s;

      s = std::accumulate(a, &a[4], (int)0); // Sum of elements

      std::cout << "sum = " << s <<  std::endl; // Expected output: sum = 10

      s = std::accumulate(a, &a[4], (int)0, [](int x, int y)
          {
              return x + 2 * y; // Custom binary operation: x + 2*y
          });

      std::cout << "2 * sum = " << s <<  std::endl; // Expected output: 2 * sum = 20
  }
  ```

#### `inner_product` (English Name | 内积) 🟡 中级概念
- 定义 | Definition
  - 将范围 `[f1, l1)` 和 `[f2, ...)` 中每对元素的乘积累加到 `init` 并返回结果。
  - Accumulates the products of each pair in the ranges `[f1, l1)` and `[f2, ...)` to `init` and returns the result.
  - 可以使用两个二元操作 `boper1` 和 `boper2` 进行累加。
  - Can accumulate using two binary operations `boper1` and `boper2`.
- 示例 | Example
  ```cpp
  // Algorithms - Inner Product
  // inner_product.cpp

  #include <iostream>
  #include <numeric>
  #include <functional>

  int main()
  {
      int a[] = {3, 2, 4, 1},
          b[] = {1, 2, 3, 4},
          s;

      s = std::inner_product(a, &a[4], b, (int)0); // Dot product

      std::cout << "dot product = " << s <<  std::endl; // Expected output: dot product = 23

      s = std::inner_product(a, &a[4], b, (int)0, std::plus<int>(), // Custom operations: sum of squares of differences
                             [](int x, int y) { return (x - y) * (x - y); });

      std::cout << "sum of (a[i] - b[i]) ^ 2 = " << s <<  std::endl; // Expected output: sum of (a[i] - b[i]) ^ 2 = 14
  }
  ```

#### `partial_sum` (English Name | 部分和) 🟡 中级概念
- 定义 | Definition
  - 计算向量 `v` 的部分和，并将它们存储在从 `partialSum` 开始的集合中。
  - Calculates the partial sums for vector `v` and stores them in collection starting at `partialSum`.
  - 可以使用二元操作 `boper` 计算部分表达式。
  - Can calculate partial expressions using a binary operation `boper`.
- 示例 | Example
  ```cpp
  // Algorithms - Partial Sum
  // partial_sum.cpp

  #include <iostream>
  #include <vector>
  #include <functional>
  #include <numeric>

  int main()
  {
      std::vector<int> v = {1, 2, 3, 4}, p(4);

      std::partial_sum(v.begin(), v.end(), p.begin()); // Partial sums

      for (auto i : p)
          std::cout << i << std::endl;
      /* Expected output:
      1
      3
      6
      10
      */

      std::partial_sum(v.begin(), v.end(), p.begin(),
      std::multiplies<int>()); // Partial products

      for (auto i : p)
          std::cout << i <<  std::endl;
      /* Expected output:
      1
      2
      6
      24
      */
  }
  ```

## 3. 内容组织方法 (Content Organization Methods) 🗂️

### 3.1 知识点关联 (Knowledge Connection)
概念关系图：
Algorithms
├── Functional Library
│   ├── Wrapper Class Templates
│   │   ├── `std::function` Wrapper Template ⭐
│   │   └── `reference_wrapper` Template ⭐
│   ├── Function Templates
│   │   ├── `bind` ⭐
│   │   └── `ref` ⭐
│   └── Operator Class Templates
├── Algorithm Library
│   ├── Queries
│   │   ├── `count` ⭐
│   │   └── `count_if` ⭐
│   ├── Modifiers
│   │   ├── `copy` ⭐
│   │   ├── `copy_if` ⭐
│   │   └── `transform` ⭐
│   └── Manipulators
│       └── `sort` ⭐
└── Numeric Library
    ├── Examples
    │   ├── `accumulate` ⭐
    │   ├── `inner_product` ⭐
    │   └── `partial_sum` ⭐

## 4. 视觉优化系统 (Visual Enhancement System) 👀

### 4.1 Emoji标记系统 (Emoji Marking System)
- 📌 重点内容 | Key points
- 💡 提示信息 | Tips
- ⚠️ 注意事项 | Warnings
- 🔍 深入探讨 | In-depth discussion
- ⭐ 重点掌握 | Must master
- ❓ 待澄清概念 | Concepts to clarify
- 📖 需要补充学习 | Need more study

## 6. 文档维护规范 (Document Maintenance Standards) 🔄

### 6.1 版本控制 (Version Control)
更新日期：2025-10-01
版本号：v1.0
更新内容：
- 添加了 C++ STL Algorithms 库的知识点总结。
- 包含了 Functional, Algorithm, Numeric 库的详细介绍和示例。
