# OOP345 Week5-1: Functions | OOP345 第5周-1: 函数

更新日期：2025-09-22  
版本号：v1.2  
更新内容：  
- 添加函数指针语法总结（基于用户总结） | Added function pointer syntax summary  
- 整合到函数指针节，确保中英对照一致 | Integrated into Function Pointer section, maintaining bilingual consistency  

## 概述 (Overview) 📌
本章描述C++对函数类型的支持，包括跨模块的函数链接、递归、函数指针、函数对象和lambda表达式。 | This chapter describes C++ support for function types, covering function linkage across modules, recursion, pointers to functions, function objects, and lambda expressions.  
对象导向语言使用函数类型表示行为。这些函数实现逻辑块，驻留在内存中，可能具有全局、类或函数作用域。设计良好的函数表现出高内聚和低耦合。高内聚指专注于单一任务，低耦合指与其他函数的最小接口。 | Object-oriented languages use function types to represent behavior. These functions implement cohesive blocks of logic, residing in memory alongside other types with global, class, or function scope. Well-designed functions exhibit high cohesion (focus on a single task) and low coupling (minimal interface with other functions).  
函数类型可重载、继承、派生、模板化和嵌套。嵌套类型可访问宿主函数作用域内的变量，此类类型称为**闭包 (closures)**。C++支持lambda表达式作为闭包形式，也支持通过重载函数调用运算符 `()` 创建函数对象 (**functors**) 。 | Function types can be overloaded, inherited, derived, templated, and nested. Nested types access variables in their host function's scope and are known as closures. C++ supports closures via lambda expressions and function objects (functors) by overloading the `()` operator on classes.  
> "为什么关心lambda函数？从语法上，它们只是函数对象的糖衣。然而，它们是本质且赋能的糖衣，将改变我们编写C++代码的方式，比大多数人意识到的更频繁。" Herb Sutter (2011)  
> "Why care about lambda functions? Syntactically, they are nothing but sugar for function objects. However, they are an essential and enabling sugar that will change the way we write C++ code more often than most people realize." Herb Sutter (2011)  
函数类型可局部使用lambda简单逻辑、函数指针复杂无状态逻辑、函数对象复杂有状态逻辑。 | We use lambda expressions for simple local logic, function pointers for complex logic depending only on parameters, and function objects for complex stateful logic.  

## 学习路径图 (Learning Path) 🛤️
```
当前概念：C++函数类型
├── 前置知识 (Prerequisites) ⭐
│   ├── Fundamental Types (基本类型) - Type inference with auto | 类型推断auto
│   └── OOP Basics (OOP基础) - Classes and methods | 类和方法
├── 相关概念 (Related Concepts)
│   ├── 同层次 (Same Level): Templates (模板), Enumerations (枚举) | Templates, Enumerations
│   └── 互补概念 (Complementary): Operator Overloading (运算符重载) for functors | Operator Overloading for functors
└── 进阶概念 (Advanced)
    ├── 直接进阶 (Direct): STL Algorithms using lambdas/functors | STL Algorithms with lambdas/functors
    └── 扩展学习 (Extended): std::function and Bind (函数包装和绑定) | std::function and std::bind
```
学习路径：1. 函数语法 (Function Syntax) 🟢 → 2. 链接 (Linkage) 🟢 → 3. 递归 (Recursion) 🟡 → 4. 函数指针 (Function Pointers) 🟡 → 5. 函数对象 (Function Objects) 🔴 → 6. Lambda表达式 (Lambdas) 🔴  
| Learning Path: 1. Function Syntax 🟢 → 2. Linkage 🟢 → 3. Recursion 🟡 → 4. Function Pointers 🟡 → 5. Function Objects 🔴 → 6. Lambda Expressions 🔴  

## 目录 (Table of Contents) 📑
- [函数概述 (Functions Overview)](#函数概述-functions-overview)
- [函数语法 (Function Syntax)](#函数语法-function-syntax)
  - [尾随返回类型声明 (Trailing Return-Type Declaration)](#尾随返回类型声明-trailing-return-type-declaration)
    - [类内定义的枚举 (Enumeration defined within a class)](#类内定义的枚举-enumeration-defined-within-a-class)
    - [模板函数 (Templated Functions)](#模板函数-templated-functions)
- [链接 (Linkage)](#链接-linkage)
- [递归 (Recursion)](#递归-recursion)
  - [栈空间替代 (Stack Space Alternative)](#栈空间替代-stack-space-alternative)
- [函数指针 (Function Pointer)](#函数指针-function-pointer)
  - [函数指针数组 (Arrays of Pointers to Functions)](#函数指针数组-arrays-of-pointers-to-functions)
  - [函数指针语法总结 (Function Pointer Syntax Summary)](#函数指针语法总结-function-pointer-syntax-summary)
- [函数对象 (Function Objects)](#函数对象-function-objects)
- [Lambda表达式 (Lambda Expressions)](#lambda表达式-lambda-expressions)
  - [捕获列表 (Capture List)](#捕获列表-capture-list)
    - [空列表 (Empty List)](#空列表-empty-list)
    - [按值捕获 (Capture by Value)](#按值捕获-capture-by-value)
    - [按引用捕获 (Capture by Reference)](#按引用捕获-capture-by-reference)
    - [捕获默认的例外 (Exceptions to Capture Defaults)](#捕获默认的例外-exceptions-to-capture-defaults)
- [练习 (Exercises)](#练习-exercises)
- [FAQ (常见问题)](#faq-常见问题)
- [实践示例 (Practice Examples)](#实践示例-practice-examples)
- [学习建议 (Study Tips)](#学习建议-study-tips)

## 知识点详解 (Detailed Content) 📚

### 函数概述 (Functions Overview) 🟢
- 定义 | Definition  
  - 中文解释：面向对象语言使用函数类型表示行为，实现逻辑块。高内聚低耦合函数驻留内存，可能全局/类/函数作用域。可重载/继承/模板/嵌套，嵌套为闭包。C++支持lambda和functor。  
  - English explanation: Object-oriented languages use function types to represent behavior, implementing cohesive blocks of logic in memory with scopes. Well-designed functions have high cohesion (single task) and low coupling (minimal interfaces). Functions can be overloaded, inherited, templated, nested; nested are closures. C++ supports lambdas as closures and functors via `()` overload.  
- 💡实践提示 | Practice Tips: 设计函数时优先单一责任，减少依赖 | Prioritize single responsibility, minimize dependencies for cohesion/coupling.  

### 函数语法 (Function Syntax) 🟢
- 定义 | Definition  
  - 中文解释：C++11引入语法简化指令，如类型推断和尾随返回类型。类型推断在Fundamental Types章节介绍。用于模板或类内枚举的返回类型。 | C++11 introduced syntax for simple, least-repetitive instructions: type-inference (auto) and trailing return types. Type inference covered in Fundamental Types.  
  - English explanation: C++11 syntax improvements include type-inference declaration and trailing return type declaration.  
- 示例 | Example  
  - 实际应用场景: 用于模板或类内枚举的返回类型 | For templates or class-enum return types.  
- 💡实践提示 | Practice Tips: 使用auto简化复杂返回 | Use auto to simplify complex returns.  

#### 尾随返回类型声明 (Trailing Return-Type Declaration) 🟢
- 定义 | Definition  
  - 中文解释：编译器从标识符或参数列表推断返回类型。形式: auto identifier(parameter-type-list) -> return-type; 特别适用于类内枚举或模板函数。 | Compiler infers return type from identifier or params. Form: auto identifier(params) -> return-type; Useful for class enums or templates.  
  - English explanation: A C++ compiler infers function return type from identifier or param list.  
- 示例 | Example  
  - 实际应用场景: 类内枚举返回 | Class-internal enum returns.  
  > 原文：A return-type inference takes the form auto identifier(parameter-type-list) -> return-type;  
  > Source: Same.  
  💡 解析步骤 | Analysis Steps:  
  1. 关键词提取 | Key Terms: auto, trailing return | auto, trailing return  
  2. 核心概念 | Core Concepts: 推断返回类型 | Infer return type  
  3. 简化解释 | Simplified Explanation: 像生活中的"猜谜"，从上下文推断答案 | Like guessing from context in a riddle  
  4. 具体示例 | Concrete Examples: Ticket类get()返回TicketType | Ticket::get() returns TicketType  
```cpp
// Trailing Return - Enumeration within a class | 尾随返回 - 类内枚举
// auto_return.cpp

#include <iostream>  // 包含标准输出库 | Include standard output

class Ticket  // 定义Ticket类 | Define Ticket class
{
public:
    enum class TicketType { Adult, Child };  // 内部枚举 | Inner enum

    void set(TicketType tt);  // 设置函数 | Set function
    TicketType get() const;  // 获取函数，尾随返回 | Get function, trailing return

private:
    TicketType ticketType;  // 私有成员 | Private member
};

std::ostream& operator<<(std::ostream& os, const Ticket::TicketType& tt)  // 重载<<运算符 | Overload <<
{
    const char* label = nullptr;  // 标签指针 | Label pointer
    switch(tt)  // 开关语句匹配 | Switch on tt
    {
    case Ticket::TicketType::Adult:  // 成人票 | Adult ticket
        label = "Adult Ticket";
        break;
    case Ticket::TicketType::Child:  // 儿童票 | Child ticket
        label = "Child Ticket";
        break;
    default:
        label = "No Ticket";  // 默认无票 | Default no ticket
    }
    os << label;  // 输出标签 | Output label
    return os;  // 返回流 | Return stream
}

void Ticket::set(TicketType tt) { ticketType = tt; }  // 设置票类型 | Set ticket type

auto Ticket::get() const -> TicketType { return ticketType; }  // 尾随返回TicketType | Trailing -> TicketType

int main()  // 主函数 | Main
{
    Ticket a, b;  // 创建两个票对象 | Create two tickets

    a.set(Ticket::TicketType::Adult);  // 设置成人 | Set adult
    b.set(Ticket::TicketType::Child);  // 设置儿童 | Set child

    std::cout << a.get() << std::endl;  // 输出成人票 | Output adult
    std::cout << b.get() << std::endl;  // 输出儿童票 | Output child
}  // 预期输出: Adult Ticket Child Ticket | Expected: Adult Ticket\nChild Ticket
```
- 💡实践提示 | Practice Tips: 避免 scoping 类名在返回中；类访问顺序惯例：public 先 (接口清晰)，private 后 (数据隐藏) | Avoid class scoping in returns for simplicity. Convention: public first (interface clear), private last (hide data).  

##### 类内定义的枚举 (Enumeration defined within a class) 🟢
- 定义 | Definition  
  - 中文解释：编译器在定义时未知类内enum，返回需尾随声明。声明类内无需 trailing（scope 知），定义类外需 auto -> 推断。参数/体受益于 Ticket:: 前缀，无需 ::。 | Compiler unknown of class enum at def, use trailing. Declaration inside no trailing (scope knows); external def needs auto ->. Params/body benefit from prefix, no :: needed.  
  - English explanation: Return type (TicketType) unknown until class context recognized.  
- 示例 | Example: 如上Ticket::get()，无尾随需Ticket::TicketType返回 | As above, without trailing: Ticket::TicketType get().  
  - 生活类比 | Analogy: 声明如“家菜单”知类型；定义类外如“外单”需 -> 补全。参数如“单内地址”受益前缀；返回如“单封”独立。 | Declaration "home menu" knows type; external def "external order" specifies later (->). Params "order inside" (benefit prefix); return "envelope" ahead (independent).  
  - 常见误区 | Common Pitfalls: 以为参数总需 ::（错，有前缀省略）；忽略声明类内 vs 定义类外（类内 OK 无，类外需 auto ->）。 | Assume params always :: (wrong, prefix omits); ignore decl inside vs def outside (inside OK, outside needs auto ->).  
- 💡实践提示 | Practice Tips: 测试删 Ticket:: 前缀——参数错“unknown TicketType”。加回 OK。 | Test remove Ticket:: prefix—param error "unknown TicketType". Add back OK.  

##### 模板函数 (Templated Functions) 🟡
- 定义 | Definition  
  - 中文解释：返回类型从参数列表推断，使用decltype(t + u)。返回未知直到参数处理完。 | Return from param list, decltype for expression type. Return unknown until params processed.  
  - English explanation: Return type known after params, use decltype for t + u type.  
- 示例 | Example  
  - 实际应用场景: 运算符+返回类型；排序比较函数 | For operator+ return types; sorting comparator.  
```cpp
// decltype with templates | decltype与模板
// decltype.cpp

#include <iostream>  // 标准输入输出 | Standard I/O

template<typename T, typename U>  // 模板参数T,U | Template params T,U
auto add(const T& t, const U& u) -> decltype(t + u)  // 尾随decltype(t + u) | Trailing decltype(t + u)
{
    return t + u;  // 返回和 | Return sum
}

int main()  // 主函数 | Main
{
    int i = 3, j = 6;  // 整数 | Ints
    double x = 4.5;  // 双精度 | Double

    std::cout << add(i, j) << std::endl;  // 3+6=9 | 9
    std::cout << add(i, x) << std::endl;  // 3+4.5=7.5 | 7.5
}  // 预期输出: 9 7.5 | Expected: 9\n7.5
```
- 💡实践提示 | Practice Tips: 用于运算符+返回类型；&fn可选，隐式转换 | For operator+ return types. &fn optional, implicit.  

### 链接 (Linkage) 🟢
- 定义 | Definition  
  - 中文解释：外部链接可见于翻译单元外，内部(static)仅本单元。默认外部，main必须外部。extern冗余。 | External visible outside TU, internal (static) only in TU. Default external, main must be. extern redundant.  
  - English explanation: External linkage visible outside translation unit (TU), internal (static) invisible outside. Default external for functions.  
- 示例 | Example  
  - 实际应用场景: 模块间static display无冲突 | Static display in modules no conflict.  
```cpp
// Function Linkage - Module B | 函数链接 - 模块B
// linkage_b.cpp

#include <iostream>

static void display() {  // 内部链接 | Internal linkage
    std::cout << "in module b\n";  // 输出模块b | Output module b
}

void module_b() {  // 外部链接 | External linkage
    display();  // 调用display | Call display
}

// Module A类似，static display不同无冲突 | Module A similar, different static no conflict
// linkage_a.cpp
// static void display() { std::cout << "in module a\n"; }
// void module_b(); int main() { display(); module_b(); }  // Output: in module a\nin module b
```
  > 原文：The different definitions of display() in the two modules do not conflict. | Source: Same.  
  💡 解析步骤 | Analysis Steps:  
  1. 关键词提取 | Key Terms: extern (redundant), static | extern (redundant), static  
  2. 核心概念 | Core Concepts: 翻译单元独立 | TU independence  
  3. 简化解释 | Simplified Explanation: 如房间内灯只在本房间用 | Like room light only in that room  
  4. 具体示例 | Concrete Examples: 两个模块static函数 | Two modules static functions  
- 💡实践提示 | Practice Tips: 用static隐藏辅助函数 | Use static to hide helpers.  

### 递归 (Recursion) 🟡
- 定义 | Definition  
  - 中文解释：函数自调用，需要退出条件终止递归，避免栈溢出。控制返回初始调用者。栈空间宝贵，深递归风险。 | Function calls itself, needs exit condition to terminate and prevent stack overflow. Returns through call stack. Stack space precious, deep recursion risky.  
  - English explanation: Recursive function calls itself; requires exit condition to stop.  
- 示例 | Example  
  - 实际应用场景: 阶乘计算 | Factorial calculation.  
```cpp
// Recursive Functions | 递归函数
// fibonacci.cpp (adapted for factorial)

#include <iostream>

unsigned factorial(unsigned x)  // 递归阶乘 | Recursive factorial
{
    return (x > 2u) ? x * factorial(x - 1) : x;  // 退出: x <= 2 返回x，否则 x * fact(x-1) | Exit: x <= 2 return x, else x * fact(x-1)
}

int main()  // 主函数 | Main
{
    std::cout << "2! = " << factorial(2) << std::endl;  // 2
    std::cout << "3! = " << factorial(3) << std::endl;  // 6
    std::cout << "4! = " << factorial(4) << std::endl;  // 24
}  // 预期输出: 2! = 2 3! = 6 4! = 24 | Expected: 2! = 2\n3! = 6\n4! = 24
```
- 💡实践提示 | Practice Tips: 确保退出条件；深度<1000，避免溢出 | Ensure exit condition; depth <1000, avoid overflow.  

#### 栈空间替代 (Stack Space Alternative) 🟡
- 定义 | Definition  
  - 中文解释：迭代替代高递归逻辑，避免栈消耗。while循环计数。 | Iteration alternative to recursive logic, avoids stack use. While loop for counting.  
  - English explanation: Iteration construct (while) replaces recursion, efficient no stack.  
- 示例 | Example  
```cpp
// Iterative Functions | 迭代函数
// iteration.cpp

#include <iostream>

unsigned factorial(unsigned x)  // 迭代阶乘 | Iterative factorial
{
    unsigned result = 1u;  // 结果初始化 | Result init
    while (x > 1u)  // 循环直到x <=1 | Loop while x >1
        result = result * x--;  // 累乘并递减 | Multiply and decrement
    return result;  // 返回结果 | Return result
}

int main()  // 主函数 | Main
{
    std::cout << "2! = " << factorial(2) << std::endl;  // 2
    std::cout << "3! = " << factorial(3) << std::endl;  // 6
    std::cout << "4! = " << factorial(4) << std::endl;  // 24
}  // 预期输出同递归 | Expected same as recursion
```
- 💡实践提示 | Practice Tips: 优先迭代高效；递归优雅但栈风险 | Prefer iteration efficient; recursion elegant but stack risk. 常见误区: 无退出=栈溢出 | Common error: No exit=overflow. 调试: 打印调用栈 | Debug: Print stack.  

### 函数指针 (Function Pointer) 🟡
- 定义 | Definition  
  - 中文解释：函数驻留内存，可地址化。指针持函数地址，转控执行。形式: return-type (*identifier)(params) = fn; &fn可选（隐式）。 | Functions in memory, addressable. Pointer holds address, transfers control. Form: return (*id)(params) = fn; & optional (implicit).  
  - English explanation: Function pointer holds address of function type; same sig.  
- 示例 | Example  
  - 实际应用场景: 排序比较函数 | Sorting comparator.  
```cpp
// Function Pointers | 函数指针
// function_pointers.cpp

#include <iostream>

// 升序比较 | Ascending comparison
template <typename T>  
bool ascending(T a, T b) { return a > b; }  // a > b 返回true交换 | Return true to swap

// 降序比较 | Descending comparison
template <typename T>
bool descending(T a, T b) { return a < b; }  // a < b 返回true交换 | Return true to swap

// 冒泡排序 | Bubble sort
template <typename T>
void sort(T* a, int n, bool (*comp)(T, T))  // comp函数指针 | comp function ptr
{
    for (int i = n - 1; i > 0; i--)  // 外循环 | Outer loop
        for (int j = 0; j < i; j++)  // 内循环 | Inner loop
            if (comp(a[j], a[j+1]))  // 用comp比较 | Use comp
            {
                T temp = a[j];  // 交换 | Swap
                a[j] = a[j+1];
                a[j+1] = temp;
            }
}

template <typename T>
void display(T* a, int n)  // 显示数组 | Display array
{
    for (int i = 0; i < n; i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;
}

int main()  // 主函数 | Main
{
    int a[] = {1, 5, 2, 3, 6, 7, 2};  // 测试数组 | Test array
    int n = sizeof a / sizeof (int);  // 长度 | Size

    sort(a, n, ascending<int>);  // 升序，指定<int> | Asc sort, specify <int>
    display(a, n);  // 1 2 2 3 5 6 7 | Output asc

    sort(a, n, descending<int>);  // 降序 | Desc sort
    display(a, n);  // 7 6 5 3 2 2 1 | Output desc
}  // 预期: 升序然后降序 | Expected: asc then desc
```
- 💡实践提示 | Practice Tips: 更改: ptr = new_fn; 用于函数表选择 | Change: ptr = new_fn. For menu of functions.  

#### 函数指针数组 (Arrays of Pointers to Functions) 🟡
- 定义 | Definition  
  - 中文解释：同返回/参数的函数地址存数组。形式: return (*id[n])(params) = {fn1, fn2}; 无需类型特化若指定int。 | Array for same sig functions: return (*id[n])(params) = {...}. No specialization if int specified.  
  - English explanation: Array holds pointers to functions with same sig.  
- 示例 | Example  
```cpp
// Array of function pointers | 函数指针数组
// array_function_pointers.cpp

// ascending and descending as above | 如上

// sort and display as above | 如上

int main()  // 主函数 | Main
{
    int a[] = {1, 5, 2, 3, 6, 7, 2};  // 数组 | Array
    bool (*criterion[2])(int, int) = {ascending, descending};  // 数组初始化，无需<int>因指定int | Init array, no <int> as int specified
    int n = sizeof a / sizeof (int);

    for (int i = 0; i < 2; i++)  // 循环两种排序 | Loop 2 sorts
    {
        sort(a, n, criterion[i]);  // 用数组元素 | Use array elem
        display(a, n);  // 输出 | Output
    }  // 同上输出: 1 2 2 3 5 6 7 \n7 6 5 3 2 2 1 | Same as above
}  
```
- 💡实践提示 | Practice Tips: 用于函数表选择；边界: nullptr元素跳过 | For menu of functions. Skip nullptr elements.  

#### 函数指针语法总结 (Function Pointer Syntax Summary) 🟡
| 特性 | int (*ptr)(int); | typedef int(*FnPtr)(int); | using FnPtr = int(*)(int); |
|------|------------------|----------------------------|----------------------------|
| 创建对象 | 函数指针变量 | 函数指针类型别名 | 函数指针类型别名 |
| 本质 | 一个变量，可以直接赋值。 | 一个类型，不能直接赋值。 | 一个类型，不能直接赋值。 |
| 语法 | int (*ptr)(int); | typedef int(*FnPtr)(int); | using FnPtr = int(*)(int); |
| 使用方式 | ptr = someFunc; | FnPtr myPtr = someFunc; | FnPtr myPtr = someFunc; |
| 兼容性 | C/C++ | C/C++ | C++11 及以后 |
| 模板支持 | 否 | 否 | 是 |

1. 基础语法  
   int (*ptr)(int);  

   声明了一个名为 ptr 的函数指针变量。  

   (*ptr) 表明 ptr 是一个指针。  

   int 是返回值类型。  

   (int) 是参数列表。  

   你可以直接给这个变量赋值：ptr = myFunc;。  

2. typedef  
   typedef int(*FnPtr)(int);  

   为函数指针类型创建了一个别名，名为 FnPtr。  

   FnPtr 是一个类型，不是变量。  

   typedef 语法绕，别名 FnPtr 夹在中间。  

   不支持模板。  

3. using  
   using FnPtr = int(*)(int);  

   为函数指针类型创建了一个别名，名为 FnPtr。  

   FnPtr 是一个类型，不是变量。  

   using 语法更直观，可读性更好。  

   支持模板，使其比 typedef 更强大。例如：template <typename T> using FuncPtr = T (*)(T);。  

4. 赋值  
   函数名（如 myFunc）在表达式中会自动退化为该函数的地址。  

   因此，ptr = myFunc; 等价于 ptr = &myFunc;。  

5. int (*)(int) (无变量名)  
   这是一个纯粹的函数指针类型，没有变量名。  

   通常用于 decltype 或作为函数参数类型。  

   例如：decltype(&myFunc) 的类型就是 int (*)(int)。  

### 函数对象 (Function Objects) 🔴
- 定义 | Definition  
  - 中文解释：OO表示函数，functor重载()，构造函数持状态。可存储状态影响调用，与指针不同。 | OO function rep, functor overloads (), ctor takes state. Stateful unlike pointers.  
  - English explanation: Function object (functor) overloads (), stores state via ctor.  
- 示例 | Example  
  - 实际应用场景: 有状态排序方向 | Stateful sort direction.  
```cpp
// Function Objects | 函数对象
// function_object.cpp

#include <iostream>

enum class Order { ascending, descending };  // 顺序枚举 | Order enum

template <typename T>
class Compare  // 比较类，functor | Compare class, functor
{
    Order order;  // 状态: 方向 | State: direction
public:
    Compare(Order o) : order(o) {}  // 构造函数设置状态 | Ctor set state

    bool operator()(T& a, T& b) const  // 重载() | Overload ()
    {
        return order == Order::ascending ? a > b : a < b;  // 根据状态比较 | Compare by state
    }
};

// sort as above, but comp const Compare<T>& | sort above, comp const Compare<T>&

template <typename T>
void display(T* a, int n)  // 如上 | As above

int main()  // 主函数 | Main
{
    int a[] = {1, 5, 2, 3, 6, 7, 2};  // 数组 | Array
    int n = sizeof a / sizeof (int);

    sort(a, n, Compare<int>(Order::ascending));  // 传递functor实例 | Pass instance
    display(a, n);  // 升序 | Asc

    sort(a, n, Compare<int>(Order::descending));  // 另一个实例 | Another instance
    display(a, n);  // 降序 | Desc
}  // 预期同指针: 1 2 2 3 5 6 7 \n7 6 5 3 2 2 1 | Expected same as pointers
```
- 💡实践提示 | Practice Tips: 用于需状态的多次调用；通过构造函数参数到成员存储状态 | For repeated calls needing state. Store state via ctor to members.  

### Lambda表达式 (Lambda Expressions) 🔴
- 定义 | Definition  
  - 中文解释：局部函数对象简写，无需id，捕获非局部变量。与环境组合为闭包。形式: [capture](params) -> return {body} | Local functor shorthand, no id, captures non-locals. Closure with env. Form: [capture](params) -> return {body}.  
  - English explanation: Shorthand for local functor, captures vars, closure with env.  
- 示例 | Example  
  - 实际应用场景: 简单局部逻辑 | Simple local logic.  
- 💡实践提示 | Practice Tips: 短lambda行内；引用捕获避免拷贝大对象 | Inline short lambdas. Ref capture no copy for large objs.  

#### 捕获列表 (Capture List) 🔴
- 定义 | Definition  
  - 中文解释：传递非局部变量到body。形式: [capture-list](params) -> return {body} | Pass non-locals to body.  

##### 空列表 (Empty List) 🔴
- 定义 | Definition  
  - 中文解释：[] 无捕获，依赖参数。编译器推断返回。 | [] No capture, depend on params. Infer return.  
  - English explanation: Simplest, empty capture.  
- 示例 | Example  
```cpp
// Lambda Expressions | Lambda表达式
// lambda.cpp

#include <iostream>

int main()  // 主函数 | Main
{
    auto hello = []() { return "Hello World"; };  // 空lambda | Empty lambda
    auto add4  = [](int i) { return i + 4; };  // 参数i | Param i
    auto sub4  = [](int i) { return i - 4; };  // 参数i | Param i

    std::cout << hello()  << std::endl;  // Hello World
    std::cout << add4(10) << std::endl;  // 14
    std::cout << sub4(10) << std::endl;  // 6
}  // 预期输出: Hello World 14 6 | Expected: Hello World\n14\n6
```
- 💡实践提示 | Practice Tips: 用于无状态简单函数；多参数边界 | For stateless simple funcs. Multi-params edge.  

##### 按值捕获 (Capture by Value) 🔴
- 定义 | Definition  
  - 中文解释：[=] 所有非局部按值捕获，拷贝。 | [=] All by value, copy.  
  - English explanation: [=] Capture all by value.  
- 示例 | Example  
```cpp
// Capture by Value | 按值捕获
// capture_by_value.cpp

#include <iostream>

template<typename Func>  // 模板接收lambda | Template receive lambda
int add(int i, Func func)  // Func func | Func param
{
    return func(i);  // 调用 | Call
}

template<typename Func>
int sub(int i, Func func)
{
    return func(i);
}

int main()  // 主函数 | Main
{
    int k = 4;  // 非局部k | Non-local k
    std::cout << add(10, [=](int i){ return i + k; }) << std::endl;  // [=]捕获k值，14 | [=] capture k value, 14
    std::cout << sub(10, [=](int i){ return i - k; }) << std::endl;  // 6
}  // 预期: 14 6 | Expected: 14\n6
```
- 💡实践提示 | Practice Tips: k不变，安全拷贝 | Safe copy if k unchanged.  

##### 按引用捕获 (Capture by Reference) 🔴
- 定义 | Definition  
  - 中文解释：[&] 所有非局部按引用，允许修改。 | [&] All by ref, modifiable.  
  - English explanation: [&] Capture by ref, changes affect original.  
- 示例 | Example  
```cpp
// Capture by Reference | 按引用捕获
// capture_by_reference.cpp

#include <iostream>

template<typename Func>
int add(int i, Func func) { return func(i); }  // 如上 | As above

template<typename Func>
int sub(int i, Func func) { return func(i); }

int main()  // 主函数 | Main
{
    int k = 4;  // k=4
    std::cout << add(10, [&](int i){ return i + k++; }) << std::endl;  // [&]k++, 14, k=5
    std::cout << "k = " << k << std::endl;  // k=5

    std::cout << sub(10, [&](int i){ return i - k++; }) << std::endl;  // 5, k=6
    std::cout << "k = " << k << std::endl;  // k=6
}  // 预期: 14 k=5 5 k=6 | Expected: 14\nk = 5\n5\nk = 6
```
- 💡实践提示 | Practice Tips: 谨慎修改，追踪副作用；输出捕获值调试 | Careful mods, track side effects. Print captured for debug.  

##### 捕获默认的例外 (Exceptions to Capture Defaults) 🔴
- 定义 | Definition  
  - 中文解释：混合: [=,&x] x引用其余值；[&,x] x值其余引用；[x,&y] 指定；[this] this值。mutable允许值捕获修改。 | Mix: [=,&x] x ref others value; etc. mutable for value mods.  
  - English explanation: Exceptions like [=,&x], [this]; mutable for modifying value captures.  
- 示例 | Example  
  形式示例: [=,&x,&y](...) 或 mutable [=](...) { k++; } | Form ex: mutable [=] { modify copy }.  
- 💡实践提示 | Practice Tips: 指定捕获最小化拷贝/修改；常见错误: 捕获未用变量编译错 | Specify minimal captures for efficiency. Common error: Unused capture compile error.  

## 练习 (Exercises) 📝
- 阅读Wikipedia函数数学概念、副作用 | Read Wikipedia on mathematical functions and side effects.  
- 观看Herb Sutter的Lambda Functions视频 | Watch Herb Sutter's Lambda Functions video (https://vimeo.com/23975522).  

## FAQ (常见问题) ❓
- 什么是闭包 (What is a closure)?  
  闭包是lambda表达式与其捕获环境的组合，可访问非局部变量 | Closure is lambda with capture env, accesses non-locals.  
- 函数指针 vs Lambda (Function Pointer vs Lambda)?  
  指针无状态，仅地址；Lambda捕获状态，闭包 | Pointer stateless address; Lambda stateful closure.  
- 递归 vs 迭代优缺点 (Recursion vs Iteration pros/cons)?  
  递归优雅但栈风险；迭代高效无栈 | Recursion elegant but stack risk; iteration efficient no stack.  
- 何时用尾随返回 (When use trailing return)?  
  类内enum或模板返回未知时 | When return unknown like class enum or template.  
- Functor如何存储状态 (How functors store state)?  
  通过构造函数参数到成员 | Via ctor to members.  
- Lambda捕获mutable的作用 (Role of mutable in lambda capture)?  
  允许按值捕获的变量在body内修改拷贝 | Allows modifying value-captured copies in body.  

## 实践示例 (Practice Examples) 💻
1. 尾随返回验证 (Trailing Return Verification) 🟢  
   - 最小可运行示例 | Minimal: auto_return.cpp (Ticket) 如上  
   - 关键特性演示 | Key: 推断类内enum返回 | Infer class enum return  
   - 边界条件测试 | Edge: 无票default | Default no ticket  
   - 预期输出 | Expected: Adult Ticket\nChild Ticket  
   - 步骤 | Steps: 编译运行，观察无需Ticket::TicketType | Compile run, note no scoping needed.  

2. 模板decltype加法 (Templated decltype Add) 🟢  
   - 如decltype.cpp | As above  
   - 预期: 9\n7.5 | int+int=int, int+double=double  
   - 步骤: 测试不同类型 | Test types.  

3. 链接模块 (Linkage Modules) 🟢  
   - linkage_a.cpp 和 b.cpp 别编译链接 | Compile/link a and b separately  
   - 预期: in module a\nin module b | Separate displays  
   - 步骤: 验证static无冲突 | Verify no conflict.  

4. 递归阶乘 (Recursive Factorial) 🟡  
   - 如fibonacci.cpp (factorial) | As above  
   - 预期: 2! = 2 等 | Factorials  
   - 步骤: 测试n=0/1边界 (修改: x==0 return 1) | Test n=0/1 (mod: x==0 return 1)  
   - 常见错误 | Common Error: 无退出=栈溢出 | No exit=overflow  
   - 调试技巧 | Debug: 打印调用栈 | Print stack.  

5. 迭代阶乘替代 (Iterative Alternative) 🟡  
   - 如iteration.cpp | As above  
   - 预期同递归 | Same  
   - 优化 | Optimize: 循环计数。  

6. 函数指针排序 (Function Pointer Sort) 🟡  
   - 如function_pointers.cpp | As above  
   - 预期: 1 2 2 3 5 6 7 \n7 6 5 3 2 2 1  
   - 步骤: 传递ascending<int> | Pass <int> for type.  

7. 函数指针数组 (Array Pointers) 🟡  
   - 如array_function_pointers.cpp | As above  
   - 预期同上 | Same  
   - 边界: nullptr元素跳过 | Skip nullptr.  

8. 函数对象排序 (Functor Sort) 🔴  
   - 如function_object.cpp | As above  
   - 预期同指针 | Same  
   - 步骤: Compare<int>(Order::asc) | Pass instance.  

9. Lambda空捕获 (Empty Capture Lambda) 🔴  
   - 如lambda.cpp | As above  
   - 预期: Hello World 14 6  
   - 边界: 多参数 | Multi-params.  

10. 值/引用捕获 (Value/Ref Capture) 🔴  
    - 如capture_by_value.cpp 和 reference | As above  
    - 值: k不变 | Value: k unchanged  
    - 引用: k++ 修改 | Ref: k modified  
    - mutable ex: [=] mutable { k_copy++; } | Mutable mod copy.  

问题诊断 | Problem Diagnosis:  
- 常见错误: 捕获未用变量编译错 | Unused capture compile error  
- 调试: 输出捕获值 | Print captured  
- 解决方案: 用[&]避免拷贝大对象 | Use [&] for large objs.  

代码优化 | Code Optimization:  
- 风格: 短lambda行内 | Inline short lambdas  
- 性能: 引用捕获避免拷贝 | Ref capture no copy  
- 最佳实践: 最小捕获 | Minimal captures  

## 学习建议 (Study Tips) 📖
- 📌 重点: 高内聚低耦合设计函数 | Key: High cohesion low coupling.  
- 💡 提示: 优先lambda局部，functor状态。练习Herb Sutter视频 | Prefer lambda local, functor state. Watch Sutter vimeo.  
- ⚠️ 注意: 递归深<1000，避免溢出 | Recursion depth <1000, avoid overflow.  
- 🔍 深入: 阅读Wikipedia函数数学概念、副作用 | Read Wiki function math, side effects.  
- ⭐ 重点掌握: 捕获规则和mutable | Master captures and mutable.  
- ❓ 待澄清: std::function高级使用 | Clarify std::function advanced.  
- 📖 补充: 实践STL sort with lambda | Practice STL sort lambda.  

## 快速复习指南 (Quick Review Guide) 📝
- Day 1: 基础语法和链接 🟢 (Syntax & Linkage)  
- Day 2: 递归和指针 🟡 (Recursion & Pointers)  
- Day 3: 对象和Lambda 🔴 (Objects & Lambdas)  

核心概念框架 (Key Concepts Framework):  
```
函数类型
├── 基础知识 (Basics)
│   ├── 语法 (Syntax): auto, trailing, decltype
│   └── 链接 (Linkage): external/static
├── 进阶内容 (Advanced)
│   ├── 递归/指针 (Recursion/Pointers): 自调用/地址
│   └── 对象/Lambda (Objects/Lambdas): 状态/捕获
└── 应用 (Application):
