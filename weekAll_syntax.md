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
- 函数指针 (Function Pointer): `return-type (*identifier)(parameter-type-list) [= fn];`
- 函数数组指针 (Array of Function Pointers): `return-type (*identifier[n])(parameter-type-list) = { initialization-list };`

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
