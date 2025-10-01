# 本学期语法速记 (Semester Syntax Quick Reference)

## Week 2:
- 枚举 (Enumerations)
- 移动操作 (Move Operations)

## Week 3:
- 模板特化、继承 (Template Specialization, Inheritance)
- 静态成员 (Static Members)

## Week 5:
- 尾随返回类型声明 (Trailing Return-Type Declaration): `auto identifier(parameter-type-list) -> return-type;`
- 静态函数 (Static Functions)

  ### 静态 vs 内联函数比较 (Static vs Inline Functions Comparison)

  | 特性 (Feature) | static (文件作用域 / File Scope) | inline (函数 / Function) |
  |----------------|----------------------------------|--------------------------|
  | 链接性 (Linkage) | 内部链接 (Internal Linkage) | 外部链接 (External Linkage) |
  | ODR (单一定义原则 / One Definition Rule) | 不适用。每个副本都视为一个独立的函数。 (Not applicable. Each copy is treated as an independent function.) | 适用。要求所有副本必须语义相同，且链接器只保留一个最终实现。 (Applicable. All copies must be semantically identical, and the linker keeps only one final implementation.) |
  | 最终可执行文件 (Final Executable) | 包含多个同名函数的机器码副本。 (Contains multiple copies of machine code for the same-named function.) | 只包含一个函数的机器码实现。 (Contains only one machine code implementation of the function.) |
  | 主要目的 (Main Purpose) | 限制作用域，避免命名冲突。 (Limits scope to avoid naming conflicts.) | 允许多重定义，同时提示编译器进行优化。 (Allows multiple definitions while hinting the compiler for optimization.) |

- 函数指针 (Function Pointer): `return-type (*identifier)(parameter-type-list) [= fn];`
- 函数数组指针 (Array of Function Pointers): `return-type (*identifier[n])(parameter-type-list) = { initialization-list };`
- 函数对象 (Function Objects)
- **Lambda 表达式 (Lambda Expressions)**
  Lambda 表达式是 C++ 中一种创建匿名函数的语法，它允许你像创建变量一样创建可调用的对象。

  ### Lambda 表达式的语法 (Lambda Expression Syntax)
  Lambda 表达式的完整语法是：
  ```cpp
  [capture-list](parameter-declaration-clause) -> optional-return-type { function body }
  ```
  - `[capture-list]`：**捕获列表**，用于从外部作用域捕获变量。
  - `(...)`：**参数列表**，和普通函数一样。
  - `-> ...`：**可选的返回类型**。
  - `{ ... }`：**函数体**。

  ### 捕获列表 (Capture List)
  捕获列表决定了 Lambda 如何访问其外部的变量。
  - `[]`：不捕获任何变量。
  - `[=]`：**按值捕获**所有在 Lambda 内部使用的非局部变量。Lambda 内部持有的是这些变量的副本。
  - `[&]`：**按引用捕获**所有在 Lambda 内部使用的非局部变量。Lambda 内部对这些变量的修改会影响外部变量。
  - `[=, &x]`：按值捕获所有变量，但 `x` 除外，`x` 按引用捕获。
  - `[&, y]`：按引用捕获所有变量，但 `y` 除外，`y` 按值捕获。
  - `[x, &y]`：按值捕获 `x`，按引用捕获 `y`。
  - `[this]`：按值捕获 `this` 指针。

  ### `mutable` 关键字 (The `mutable` Keyword)
  `mutable` 用于允许按值捕获的 Lambda 表达式修改其内部的变量副本。
  ```cpp
  [=]() mutable { /* ... */ }
  ```

  ### 类型推导 (Type Deduction)
  #### `auto` 关键字 (The `auto` Keyword)
  `auto` 用于在编译时自动推导变量的类型。
  - 局部变量：`auto myVar = 10;`
  - Lambda 表达式：`auto myLambda = [](){ return 1; };`

  在 `auto` 泛型 Lambda 中，`auto` 也可以用于参数类型：
  ```cpp
  auto myLambda = [](auto x) { return x; };
  ```

  #### Lambda 返回类型推导 (Lambda Return Type Deduction)
  - **单一 `return` 语句**：编译器可以自动推导返回类型，因此 `->` 符号是可选的。
  - **多个 `return` 语句**：如果返回类型不一致，必须使用 `->` 显式指定返回类型。
  - **`void` 返回**：在 C++14 之后，可以省略 `-> void`。

  ### 模板与类型推导 (Templates and Type Deduction)
  模板是 C++ 中实现泛型编程的蓝图，它们在编译时根据传入的类型实例化为具体的函数或类。

  #### `template` vs `auto`
  - `template <typename T>`：用于函数或类的模板定义，它声明了一个类型占位符 `T`。
  - `auto`：用于局部变量或泛型 Lambda 的类型推导。

  #### 模板实例化过程 (Template Instantiation Process)
  1. **模板解析**：编译器仅检查模板语法。此时，它不生成机器码，也无法确定依赖于模板参数的类型（例如 `T + U` 的结果类型）。
  2. **模板实例化**：当你调用一个模板时，编译器用具体的类型替换模板参数，生成一个具体的函数实例。
  3. **代码生成**：实例化后的具体函数被编译成机器码。

  #### 模板返回类型推导的矛盾 (Contradiction in Template Return Type Deduction)
  在 C++11 中，编译器在实例化模板之前需要知道其返回类型，但返回类型又依赖于实例化时传入的参数类型，这造成了死循环。

  `-> decltype(a + b)` 语法解决了这个问题，它告诉编译器：“返回类型是 `a + b` 表达式的类型”。

  在 C++14 之后，编译器变得更智能，可以直接从 `return` 语句推导模板函数的返回类型，从而简化了语法。

  ### 总结 (Summary)
  Lambda 表达式是带有捕获列表的可调用对象。`auto` 和 `->` 提供了强大的类型推导功能，使得 Lambda 和模板的结合更加简洁和灵活。`template` 定义了泛型蓝图，而 Lambda 作为一种特殊的函数对象，可以完美地作为模板函数的参数，实现强大的通用编程模式。

### 函数指针语法总结 (Function Pointer Syntax Summary)

| 特性 (Feature) | `int (*ptr)(int);` | `typedef int(*FnPtr)(int);` | `using FnPtr = int(*)(int);` |
|----------------|--------------------|-----------------------------|-----------------------------|
| 创建对象 (Object Creation) | 函数指针变量 (Function Pointer Variable) | 函数指针类型别名 (Function Pointer Type Alias) | 函数指针类型别名 (Function Pointer Type Alias) |
| 本质 (Nature) | 一个变量，可以直接赋值。 (A variable, can be directly assigned.) | 一个类型，不能直接赋值。 (A type, cannot be directly assigned.) | 一个类型，不能直接赋值。 (A type, cannot be directly assigned.) |
| 语法 (Syntax) | `int (*ptr)(int);` | `typedef int(*FnPtr)(int);` | `using FnPtr = int(*)(int);` |
| 使用方式 (Usage) | `ptr = someFunc;` | `FnPtr myPtr = someFunc;` | `FnPtr myPtr = someFunc;` |
| 兼容性 (Compatibility) | C/C++ | C/C++ | C++11 及以后 (C++11 and later) |
| 模板支持 (Template Support) | 否 (No) | 否 (No) | 是 (Yes) |

1.  **基础语法 (Basic Syntax)**
    `int (*ptr)(int);`

    声明了一个名为 `ptr` 的函数指针变量。 (Declares a function pointer variable named `ptr`.)

    `(*ptr)` 表明 `ptr` 是一个指针。 (`(*ptr)` indicates `ptr` is a pointer.)

    `int` 是返回值类型。 (`int` is the return type.)

    `(int)` 是参数列表。 (`(int)` is the parameter list.)

    你可以直接给这个变量赋值：`ptr = myFunc;`。 (You can directly assign a value to this variable: `ptr = myFunc;`.)

2.  **`typedef`**
    `typedef int(*FnPtr)(int);`

    为函数指针类型创建了一个别名，名为 `FnPtr`。 (Creates an alias for the function pointer type, named `FnPtr`.)

    `FnPtr` 是一个类型，不是变量。 (`FnPtr` is a type, not a variable.)

    `typedef` 语法绕，别名 `FnPtr` 夹在中间。 (`typedef` syntax is convoluted, with the alias `FnPtr` in the middle.)

    不支持模板。 (Does not support templates.)

3.  **`using`**
    `using FnPtr = int(*)(int);`

    为函数指针类型创建了一个别名，名为 `FnPtr`。 (Creates an alias for the function pointer type, named `FnPtr`.)

    `FnPtr` 是一个类型，不是变量。 (`FnPtr` is a type, not a variable.)

    `using` 语法更直观，可读性更好。 (`using` syntax is more intuitive and readable.)

    支持模板，使其比 `typedef` 更强大。例如：`template <typename T> using FuncPtr = T (*)(T);`。 (Supports templates, making it more powerful than `typedef`. For example: `template <typename T> using FuncPtr = T (*)(T);`.)

4.  **赋值 (Assignment)**
    函数名（如 `myFunc`）在表达式中会自动退化为该函数的地址。 (A function name (e.g., `myFunc`) automatically decays to the function's address in an expression.)

    因此，`ptr = myFunc;` 等价于 `ptr = &myFunc;`。 (Therefore, `ptr = myFunc;` is equivalent to `ptr = &myFunc;`.)

5.  **`int (*)(int)` (无变量名) (Without a variable name)**
    这是一个纯粹的函数指针类型，没有变量名。 (This is a pure function pointer type, without a variable name.)

    通常用于 `decltype` 或作为函数参数类型。 (Typically used with `decltype` or as a function parameter type.)

    例如：`decltype(&myFunc)` 的类型就是 `int (*)(int)`。 (For example, the type of `decltype(&myFunc)` is `int (*)(int)`.)
