# OOP345 Week5-2: Error Handling | OOP345 第5周-2: 错误处理

更新日期：2025-09-21  
版本号：v1.0  
更新内容：  
- 基于网页https://advoop.sdds.ca/D-Processing/error-handling全部内容整理为双语笔记 | Organized from full webpage content into bilingual notes  
- 包括所有代码示例、输出和解释 | Including all code examples, outputs, and explanations  

## 概述 (Overview) 📌
面向对象程序的模块化导致错误原因与处理位置分离。OOP语言需要专机制识别/处理错误。由于对象设计者不知使用方式，对象可能无法处理其识别错误。首选策略：将错误标识为正常执行异常，在未知对象中处理。替代：调用库函数直接处理并终止。 | Modularity in OOP separates error cause from handling location. OOP requires mechanisms for errors. Object may not handle its errors; preferred: mark as exception to normal flow, handle elsewhere. Alternative: call lib to handle and terminate immediately.  
> "优先使用异常而非错误码报告错误。当异常不可用时使用状态码。" Sutter, Alexandrescu (2005)  
> "Prefer exceptions over error codes to report errors. Use status codes for errors when exceptions cannot be used." Sutter, Alexandrescu (2005)  
结构化编程需通过返回/参数传错误码上栈，假定已知因果链接。OOP松绑单入单出原理，解耦报告/处理，自动转移控制，调用必要析构。 | Structured prog passes error codes up stack assuming known linkage. OOP decouples reporting/handling, automates control transfer, invokes destructors.  
本章描述C++异常处理设施和标准库直接退出函数。 | This chapter covers C++ exception handling and std lib functions for direct exits.  

## 学习路径图 (Learning Path) 🛤️
```
当前概念：C++错误处理
├── 前置知识 (Prerequisites) ⭐
│   ├── OOP Modularity (OOP模块化) - Separation of concerns | 关注分离
│   └── Exceptions Basics (异常基础) - Throw vs codes | 抛出 vs 代码
├── 相关概念 (Related Concepts)
│   ├── 同层次 (Same Level): RAII (资源获取即初始化) for cleanup | RAII for cleanup
│   └── 互补概念 (Complementary): Debugging (调试) in OOP | OOP debugging
└── 进阶概念 (Advanced)
    ├── 直接进阶 (Direct): Exception safety guarantees (异常安全保证) | Exception safety
    └── 扩展学习 (Extended): Custom exception classes (自定义异常类) | Custom exceptions
```
学习路径：1. 异常 (Exceptions) 🟢 → 2. 标准异常 (Std Exceptions) 🟡 → 3. 抛出表达式 (Throw Expressions) 🟡 → 4. noexcept 🟡 → 5. 标准退出 (Standard Exits) 🔴 (Normal/Abnormal)  
| Learning Path: 1. Exceptions 🟢 → 2. Std Exceptions 🟡 → 3. Throw Expressions 🟡 → 4. noexcept 🟡 → 5. Standard Exits 🔴 (Normal/Abnormal)  

## 目录 (Table of Contents) 📑
- [Error Handling Overview (错误处理概述)](#error-handling-overview)
- [Exceptions (异常)](#exceptions)
  - [Reporting and Handling (报告和处理)](#reporting-and-handling)
    - [Reporting an Exception (报告异常)](#reporting-an-exception)
    - [Handling the Exception (处理异常)](#handling-the-exception)
    - [Detecting an Exception (检测异常)](#detecting-an-exception)
  - [Standard Exceptions (标准异常)](#standard-exceptions)
  - [Expressions that Throw Exceptions (抛出异常的表达式)](#expressions-that-throw-exceptions)
  - [noexcept (无异常)](#noexcept)
- [Standard Exits (标准退出)](#standard-exits)
  - [Normal Exits (正常退出)](#normal-exits)
    - [atexit() (atexit函数)](#atexit)
    - [exit() (exit函数)](#exit)
  - [Abnormal Exits (异常退出)](#abnormal-exits)
    - [terminate() (terminate函数)](#terminate)
    - [abort() (abort函数)](#abort)
- [Exercises (练习)](#exercises)
- [FAQ (常见问题)](#faq)
- [实践示例 (Practice Examples)](#practice-examples)
- [学习建议 (Study Tips)](#study-tips)

## 知识点详解 (Detailed Content) 📚

### 错误处理概述 (Error Handling Overview) 🟢
- 定义 | Definition  
  - 中文解释：OOP模块化分离错误原因与处理。异常是异常情况（如硬件误、警告）。程序员裁量何为异常。 | OOP modularity separates error cause/handling. Exception is non-normal (e.g., hardware error, warning). Programmer discretion.  
  - English explanation: OOP programs separate error cause from handler. Exceptions are deviations from normal; discretionary.  
- 示例 | Example  
  - 实际应用场景: 图像显示OOP异常转移 vs 结构化错误码传 | Image: OOP exception transfer vs structured error code pass.  
  💡 解析步骤 | Analysis Steps:  
  1. 关键词提取 | Key Terms: Exception, modularity, single-entry single-exit | 异常, 模块化, 单入单出  
  2. 核心概念 | Core Concepts: 解耦报告/处理，自动控制转移 | Decouple report/handle, auto transfer  
  3. 简化解释 | Simplified Explanation: 如邮寄问题信件到邮局处理，而非沿途停 | Like forwarding problem mail to post office, not stop en route  
  4. 具体示例 | Concrete Examples: throw转移到catch | Throw to catch  
- 💡实践提示 | Practice Tips: 优先异常而非码报告错误 | Prefer exceptions over codes for errors.  

### 异常 (Exceptions) 🟢
- 定义 | Definition  
  - 中文解释：异常是非正常预期。处理分报告(throw)和捕获/处理(try-catch)。 | Exception is unexpected normal. Parts: report (throw), handle (try-catch).  
  - English explanation: Exception is not normal expectation. Report and handle.  
- 示例 | Example  

#### 报告和处理 (Reporting and Handling) 🟢
##### 报告异常 (Reporting an Exception) 🟢
- 定义 | Definition  
  - 中文解释：throw expression; 报告异常。形式: throw expression; 非noexcept函数。 | Throw expression reports. Form: throw expr; Not noexcept func.  
  - English explanation: Throw expr reports exception.  
- 示例 | Example: divide中throw "Outside bounds" 或 throw divisor=0 | Throw string or 0 in divide.  

##### 处理异常 (Handling the Exception) 🟢
- 定义 | Definition  
  - 中文解释：try块发起可能抛出代码；catch块处理匹配类型。第一匹配处理。... 捕获其余。 | Try: init code; catch: handle matching types. First match handles; ... others.  
  - English explanation: Try contains potential throw code; catch handles types. Ellipsis for rest.  
- 示例 | Example  
  - 实际应用场景: divide数组界/零除异常 | Divide array out-of-bounds/zero div.  
```cpp
// Exception Handling | 异常处理
// exceptions.cpp

#include <iostream>  // 标准I/O | Std I/O

void divide(double a[], int i, int n, double divisor)  // 除法函数 | Divide func
{
    if(i < 0 || i >= n)  // 界外检查 | Bounds check
        throw "Outside bounds";  // 抛出字符串 | Throw string
    else if(divisor == 0)  // 零除检查 | Zero div check
        throw divisor;  // 抛出0 | Throw 0
    else
        a[i] = i / divisor;  // 正常除 | Normal div
}

int main()  // 主 | Main
{
    bool keepdividing = true;  // 继续标志 | Continue flag
    double a[] = {1.1,2.2,3.3,4.4,5.5,6.6}, divisor;  // 测试数组 | Test array
    int i, n = sizeof a / sizeof a[0];  // 大小 | Size

    do  // 循环输入 | Loop input
    {
        try  // try块 | Try block
        {
            std::cout << "Index: ";  // 输入索引 | Input index
            std::cin >> i;
            std::cout << "Divisor: ";  // 输入除数 | Input divisor
            std::cin >> divisor;
            divide(a, i, n, divisor);  // 调用divide | Call divide
            std::cout << "a[i] = " << a[i] << std::endl;  // 输出结果 | Output result
            std::cout << "Continuing ..." << std::endl;  // 继续 | Continue
        }
        catch(const char* msg)  // 捕获字符串 | Catch string
        {
            std::cout << msg << std::endl;  // 输出msg | Output msg
            keepdividing = false;  // 停止 | Stop
        }
        catch(...)  // 捕获其余 | Catch others
        {
            std::cout << "Zero Division!" << std::endl;  // 零除 | Zero div
            std::cout << "a[i] = " << a[i] << std::endl;  // 当前a[i] | Current a[i]
            std::cout << "Continuing ..." << std::endl;  // 继续 | Continue
        }
    }
    while (keepdividing);  // 循环条件 | Loop cond
}  // 预期输入/输出: Index1 Div-1 a[1]=-1 cont; Index4 Div2 a[4]=2 cont; Index5 Div0 Zero! a[5]=6.6 cont; Index45 Div3 Outside | Expected sample inputs/outputs as page
```
概念关系图：异常栈展开  
```mermaid
graph LR
    A[main try: cin i/divisor] --> B[call divide(i,n,divisor)]
    B --> C{if i bounds?}
    C -->|No| D{if div==0?}
    D -->|Yes| E[throw div=0]
    D -->|No| F[a[i]=i/div return]
    E --> G[stack unwind: destructors]
    G --> H[catch(...): Zero Division! print a[i] cont]
    C -->|Yes| I[throw "Outside"]
    I --> G
    style E fill:#ff9999  // 抛出 | Throw
    style H fill:#90EE90  // 处理 | Handle
```
- 💡实践提示 | Practice Tips: 多catch从具体到一般顺序 | Order catches specific to general.  

##### 检测异常 (Detecting an Exception) 🟢
- 定义 | Definition  
  - 中文解释：未进入catch的抛出异常，用std::uncaught_exceptions()返回当前线程未捕获数。 | If thrown but not caught, std::uncaught_exceptions() returns count in thread during unwind.  
  - English explanation: Detect uncaught via std::uncaught_exceptions() during unwind.  
- 💡实践提示 | Practice Tips: 在栈展开中用，监控未捕获 | Use in unwind to monitor uncaught.  

### 标准异常 (Standard Exceptions) 🟡
- 定义 | Definition  
  - 中文解释：库异常类层次基exception在<exception>。派生logic_error(可预防逻辑问题: length/domain/out_of_range/invalid_arg), runtime_error(运行时: range/overflow/underflow), bad_alloc(new分配<new>), bad_cast(dynamic_cast<typeinfo>)。 | Std lib exceptions from base exception <exception>. Derived: logic_error (preventable: length_error etc.), runtime_error (runtime: range_error etc.), bad_alloc (<new>), bad_cast (<typeinfo>).  
  - English explanation: Hierarchy from exception; catch most derived first.  
- 示例 | Example  
  - 实际应用场景: new数组捕获bad_alloc前general | New array catch bad_alloc before general.  
```cpp
// Handling derived exceptions | 处理派生异常
// 示例片段 | Snippet

#include <new>  // bad_alloc | For bad_alloc
#include <exception>  // 标准异常 | Std exception
#include <cstring>  // strlen/strcpy | String funcs

try  // try块 | Try
{
    char* p = new char[std::strlen(s) + 1];  // new可能bad_alloc | New may bad_alloc
    std::strcpy(p, s);  // 拷贝 | Copy
}
catch (std::bad_alloc)  // 先捕获具体 | Catch specific first
{
    std::cout << "Insufficient memory\n";  // 内存不足 | Mem insufficient
}
catch (std::exception& e)  // 然后一般 | Then general
{
    std::cout << "Standard Exception\n";  // 标准异常 | Std ex
}  // 正确捕捉顺序: 派生先 | Correct: derived first

// 错误顺序: general先，bad_alloc unreachable | Wrong: general first, bad_alloc unreachable
try { /* same */ }
catch (std::exception& e)  // 先一般 | General first
{
    std::cout << "Standard Exception\n";
}
catch (std::bad_alloc)  // unreachable | Unreachable
{
    std::cout << "Insufficient memory\n";
}
```
- 💡实践提示 | Practice Tips: 总是从最派生开始捕获 | Always catch most derived first.  

### 抛出异常的表达式 (Expressions that Throw Exceptions) 🟡
- 定义 | Definition  
  - 中文解释：throw expr, dynamic_cast, type_id, new可能抛出。需在try-catch内捕获匹配类型。 | Throw expr, dynamic_cast, typeid, new can throw; must catch matching in try-catch.  
  - English explanation: Expressions: throw, dynamic_cast, typeid, new; catch matching types.  
- 💡实践提示 | Practice Tips: new总是潜在bad_alloc，包围try | Always try new for bad_alloc.  

### noexcept (noexcept) 🟡
- 定义 | Definition  
  - 中文解释：C++11标识不抛异常函数，允许优化。运行时未捕获逃逸则立即终止。 | C++11 marks no-throw func for opts; runtime escape terminates.  
  - English explanation: Noexcept for no-throw funcs, enables opts; uncaught escape terminates.  
- 示例 | Example  
```cpp
// No Exceptions - compile on GCC | 无异常 - GCC编译
// noexceptions.cpp

#include <iostream>  // I/O

void d() { throw "d() throws\n"; }  // d抛出 | d throws
void e()  // e捕获
{
    try
    {
        d();  // 调用d | Call d
    }
    catch(const char* msg)  // 捕获 | Catch
    {
        std::cout << msg;  // 输出 | Output
    }
}
void f() { throw "f() throws\n"; }  // f抛出 | f throws
void g() noexcept { e(); }  // g noexcept调用e | g noexcept calls e
void h() noexcept { f(); }  // h noexcept调用f | h noexcept calls f

int main()  // 主 | Main
{
    std::cout << "Calling g:";  // g:
    g();  // e捕获d，正常 | e catches d, normal
    std::cout << "Calling h:";  // h:
    h();  // f抛出，h noexcept终止 | f throws, h terminates
    std::cout << "Normal exit\n";  // unreachable for h | Unreachable
}  // 预期输出: Calling g: d() throws Calling h: (term) | Expected: g output, h terminates
```
- 💡实践提示 | Practice Tips: noexcept优化但确保无逃逸异常 | Noexcept opts but ensure no escape.  

### 标准退出 (Standard Exits) 🔴
- 定义 | Definition  
  - 中文解释：main返回int状态到OS。库函数提供除main返回外的退出: 正常(析构/刷新/atexit/exit), 异常(terminate/abort无析构)。 | Main returns int status to OS. Lib funcs for exits besides main return: normal (destruct/flush/atexit/exit), abnormal (terminate/abort no destruct).  

#### 正常退出 (Normal Exits) 🔴
##### atexit() (atexit函数) 🔴
- 定义 | Definition  
  - 中文解释：注册void(*)(void)函数，在exit终止调用。返回0成功，至少32注册。 | Register void(*)() for exit call. 0 success, >=32 regs.  
  - English explanation: Reg void(*)() for exit; 0 ok.  

##### exit() (exit函数) 🔴
- 定义 | Definition  
  - 中文解释：void exit(int)终止: 销毁线程/静态对象, 调用atexit, 刷新/关闭流, 返OS。 | Exit(int): destroy thread/static objs, call atexit, flush/close streams, to OS.  
  - English explanation: Initiates normal termination with destructors, atexit, streams.  
- 示例 | Example  
```cpp
// Normal Exits | 正常退出
// exit.cpp

#include <iostream>  // I/O
#include <cstdlib>  // exit/atexit | Exit/atexit

void exit_1()  // 注册函数 | Reg func
{
    std::cerr << "In exit_1\n";  // 输出 | Output
}

int main()  // 主
{
    int i;  // 选择 | Choice

    std::cout << "Return(!=1), Exit(1) ? ";  // 提示 | Prompt
    std::cin >> i;
    if (i == 1)  // 若1
    {
        std::atexit(exit_1);  // 注册exit_1 | Reg
        std::exit(1);  // exit(1) | Exit 1
    }
    return i;  // 否则返回 | Else return
}  // 预期i=1: In exit_1 (no main return); i=2: no output just exit | Expected i=1: In exit_1; i=2: normal
```
- 💡实践提示 | Practice Tips: atexit用于清理注册 | Atexit for cleanup reg.  

#### 异常退出 (Abnormal Exits) 🔴
##### terminate() (terminate函数) 🔴
- 定义 | Definition  
  - 中文解释：异常处理错误终止: 无handler, noexcept内抛, 析构抛, 空throw。无析构/atexit调用。优先catch(std::exception& e)。 | Terminates on ex handle errors: no handler, noexcept throw, destruct throw, empty throw. No destruct/atexit. Prefer catch std::exception.  
  - English explanation: Ex handle errors: no handler etc.; no destruct/atexit.  
- 💡实践提示 | Practice Tips: 确保handler覆盖所有可能 | Ensure handlers cover all.  

##### abort() (abort函数) 🔴
- 定义 | Definition  
  - 中文解释：SIGABRT信号终止，无析构/atexit。 | SIGABRT terminate; no destruct/atexit.  
  - English explanation: Abort via SIGABRT; no cleanup.  
- 💡实践提示 | Practice Tips: 仅紧急，如无限循环 | Only emergency, like infinite loop.  

## FAQ (常见问题) ❓
- 什么是异常处理解耦 (What is exception decoupling)?  
  OOP分离报告/处理，自动栈展开调用析构 | OOP separates report/handle, auto unwind calls destructors.  
- try-catch顺序重要性 (Why catch order matters)?  
  从最派生开始，否则一般捕获隐藏具体 | Most derived first, or general shadows specific.  
- noexcept何时用 (When use noexcept)?  
  知函数不抛，获优化；但逃逸则终止 | Known no-throw for opts; escape terminates.  
- exit vs return区别 (Exit vs return diff)?  
  exit调用atexit/刷新，返回仅main结束 | Exit calls atexit/flush; return just ends main.  
- terminate何时触发 (When terminate triggered)?  
  无handler或noexcept逃逸等 | No handler or noexcept escape etc.  
- 标准异常层次 (Std exception hierarchy)?  
  Base exception → logic_error/runtime_error → specific like bad_alloc | exception → logic/runtime → specifics.  

## 实践示例 (Practice Examples) 💻
1. 异常报告/处理 (Exceptions Report/Handle) 🟢  
   - 最小可运行示例 | Minimal: exceptions.cpp 如上  
   - 关键特性演示 | Key: try循环, catch char*/... for bounds/zero  
   - 边界条件测试 | Edge: i=-1 (bounds), div=0 (zero), i=valid div!=0 (normal)  
   - 预期输出 | Expected: Sample inputs: Index1 Div-1 a[1]=-1 cont; Index5 Div0 Zero! a[5]=6.6 cont; Index45 Div3 Outside stop  
   - 步骤 | Steps: 编译运行，多输入测试catch分支 | Compile run, test branches.  

2. 标准异常派生捕获 (Std Derived Catch) 🟡  
   - 如片段 | As snippet  
   - 预期: new成功无输出; 内存低bad_alloc "Insufficient" | New fail: Insufficient  
   - 步骤: 模拟内存低(大分配), 观察顺序 | Simulate low mem, note order.  
   - 常见错误 | Common Error: 一般catch先，具体unreachable | General first, specific unreachable  
   - 调试技巧 | Debug: 用catch(e.what())打印类型 | Print e.what() for type.  

3. noexcept终止 (Noexcept Termination) 🟡  
   - 如noexceptions.cpp | As above  
   - 预期: Calling g: d() throws (caught in e) Calling h: (abrupt end, no "Normal exit")  
   - 步骤: 编译GCC, 运行观察g正常h term | GCC compile, run g normal h term.  
   - 边界: 移除e catch, g也term | Remove e catch, g terms.  

4. 正常退出 (Normal Exit) 🔴  
   - 如exit.cpp | As above  
   - 预期 i=1: In exit_1 (atexit called); i=2: normal no extra out  
   - 步骤: 输入1/2, 观察atexit/exit vs return  
   - 优化 | Optimize: 多atexit注册顺序逆调用 | Multiple atexit called reverse order.  

5. 异常退出触发 (Abnormal Exit Trigger) 🔴  
   - 示例: 未捕获throw | Uncaught throw  
```cpp
// Simulate terminate | 模拟terminate
#include <iostream>
int main() {
    throw "Uncaught";  // 无try-catch，terminate | No try, terminate
    return 0;  // unreachable | Unreachable
}  // 预期: 立即终止，无析构 | Expected: Abrupt terminate, no cleanup
```
   - 预期: Program terminates (no output beyond throw if any) | Terminate  
   - 步骤: 运行，观察无正常结束 | Run, note no normal end.  
   - 常见错误 | Common Error: 忘记catch，导致terminate | Forget catch → terminate  
   - 解决方案 | Solution: 包围潜在throw try-catch | Wrap potential throws.  

问题诊断 | Problem Diagnosis:  
- 常见错误: noexcept内throw未捕获 | Noexcept throw uncaught  
- 调试技巧: 用uncaught_exceptions()计数 | Use uncaught_exceptions() count  
- 解决方案: noexcept只标确保无throw funcs | Noexcept only certain no-throw funcs.  

代码优化 | Code Optimization:  
- 风格: catch参考e，避免raw | Catch ref e, avoid raw  
- 性能: noexcept编译优化 | Noexcept compile opts  
- 最佳实践: 自定义异常派生std | Derive custom from std exceptions.  

## 学习建议 (Study Tips) 📖
- 📌 重点: OOP中优先异常解耦报告/处理 | Key: OOP prefer exceptions for decoupling.  
- 💡 提示: 结构化用码，OOP用异常转移控制 | Structured codes, OOP exceptions transfer.  
- ⚠️ 注意: catch顺序从具体到一般，避免隐藏 | Catch specific to general, avoid masking.  
- 🔍 深入: 阅读Wikipedia异常处理 | Read Wiki exception handling.  
- ⭐ 重点掌握: try-catch/throw/noexcept组合 | Master try-catch/throw/noexcept combo.  
- ❓ 待澄清: 异常安全级别(强/基本/无) | Clarify ex safety levels.  
- 📖 补充: 实践RAII与异常 | Practice RAII with exceptions.  

## 快速复习指南 (Quick Review Guide) 📝
- Day 1: 异常基础 🟢 (Exceptions Basics)  
- Day 2: 标准/noexcept 🟡 (Std/noexcept)  
- Day 3: 退出机制 🔴 (Exit Mechanisms)  

核心概念框架 (Key Concepts Framework):  
```
错误处理
├── 基础知识 (Basics)
│   ├── 异常 (Exceptions): throw/try-catch/...
│   └── 报告/处理 (Report/Handle): 解耦转移
├── 进阶内容 (Advanced)
│   ├── 标准异常/noexcept (Std Ex/noexcept): 层次/优化
│   └── 退出 (Exits): normal(atexit/exit)/abnormal(terminate/abort)
└── 应用 (Application): OOP模块化错误管理 | OOP modular error management
```

TODO: 添加自定义异常示例 | Add custom ex example  
NOTE: 遵循C++11+异常语义 | Follow C++11+ ex semantics  
FIXME: 如果网页更新，同步 | Sync if page updates
