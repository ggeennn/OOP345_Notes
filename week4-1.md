# OOP345_Week4_Expressions.md 📚

## 1. 文档基本规范 (Basic Document Standards) 📑

### 1.1 文件命名规则 (File Naming Convention)
`OOP345_Week4_Expressions.md`

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

### 概念名称 (English Name | 中文名称) 难度标记
- 定义 | Definition
  - 中文解释
  - 英文解释
- 示例 | Example
  - 实际应用场景
- 💡实践提示 | Practice Tips

### 2.2 难度分级 (Difficulty Levels)
- 🟢 基础概念：必须完全理解 | Basic concepts: Must fully understand
- 🟡 中级概念：需要基本掌握 | Intermediate concepts: Need basic mastery
- 🔴 高级概念：了解即可 | Advanced concepts: Understanding is sufficient

### 2.3 中英对照规则 (Bilingual Format)
- 文档内所有中文：中英并列 | All Chinese content: have English side by side
- 重要概念：双语解释 | Important concepts: Bilingual explanation
- 专业词汇：括号注释 | Technical terms: Bracketed notes

## 3. 知识点详解 (Detailed Content)

### Expressions | 表达式 🟢
- 定义 | Definition
  - 表达式指定计算。它们由运算符和操作数序列组成，可能会产生结果，并可能伴有副作用。C++ 表达式具有非引用类型，并属于一个值类别。表达式可以是主要的或复合的。复合表达式由一个运算符和一个或多个操作数组成。复合表达式最终可以分解为一组由运算符连接的主要表达式。
  - Expressions specify computations. They consist of sequences of operators and operands and may produce a result, possibly with side effects. A C++ expression has a non-reference type and belongs to a value category. The expression may be primary or compound. A compound expression consists of an operator and one or more operands. A compound expression is ultimately decomposable into a set of primary expressions connected by operators.
- 示例 | Example
  - `a + b` 是一个复合表达式，由操作数 `a`, `b` 和运算符 `+` 组成。
  - `a` 和 `b` 是主要表达式。
- 💡实践提示 | Practice Tips
  - 理解表达式的构成是理解 C++ 语句和程序逻辑的基础。

### Value Categories | 值类别 🟢
- 定义 | Definition
  - C++ 表达式的值类别是编译器在评估表达式时创建、复制和移动临时对象的规则基础。了解这些类别有助于程序员理解编译器如何评估表达式以及解释编译器生成的错误消息。
  - The value categories of C++ expressions are the basis for rules that compilers follow when creating, copying, and moving temporary objects during the evaluation of expressions. Awareness of these categories helps the programmer understand how the compiler evaluates expressions and interpret error messages that the compiler generates.
- 示例 | Example
  - 见下方具体类别解释。
- 💡实践提示 | Practice Tips
  - 值类别对于理解 C++11 引入的右值引用和移动语义至关重要。

### prvalue (pure rvalue) | 纯右值 🟢
- 定义 | Definition
  - 不占用存储位置的值。
  - A value that does not occupy a location in storage.
- 示例 | Example
  - 字面量，如 `10`, `3.14`, `"hello"` (字符串字面量是 lvalue)。
  - 函数返回非引用类型的值，如 `int func() { return 10; }` 中的 `10`。
- 💡实践提示 | Practice Tips
  - prvalue 通常是临时值，在表达式求值后立即销毁。

### xvalue (expiring value) | 将亡值 🟡
- 定义 | Definition
  - 占用存储位置的将要过期值（对象生命周期即将结束）。
  - An expiring value that does occupy a location in storage (an object near the end of its lifetime).
- 示例 | Example
  - 函数返回右值引用，如 `std::move(obj)` 的结果。
  - 临时对象的临时物化转换。
- 💡实践提示 | Practice Tips
  - xvalue 是 C++11 引入的，用于支持移动语义，避免不必要的复制。

### lvalue (locator value) | 左值 🟢
- 定义 | Definition
  - 占用存储位置的定位值。
  - A locator value that occupies a location in storage.
- 示例 | Example
  - 变量名，如 `int x = 10;` 中的 `x`。
  - 数组元素，如 `a[i]`。
  - 解引用指针，如 `*ptr`。
  - 字符串字面量，如 `"hello"`。
- 💡实践提示 | Practice Tips
  - lvalue 可以出现在赋值运算符的左侧，表示一个可修改的存储位置。

### glvalue (generalized lvalue) | 泛左值 🟢
- 定义 | Definition
  - 泛化的左值，它评估为一个对象或一个函数。lvalue 和 xvalue 都占用内存区域，统称为 glvalue。
  - A generalized lvalue. It evaluates to an object or a function. Both lvalues and xvalues occupy a region of memory and together are called glvalues.
- 示例 | Example
  - 任何 lvalue 或 xvalue 都是 glvalue。
- 💡实践提示 | Practice Tips
  - glvalue 是 C++17 值类别分类中的一个顶层概念。

### rvalue (right-hand side value) | 右值 🟢
- 定义 | Definition
  - 临时对象或子对象，或不与对象关联的值。prvalue 和 xvalue 统称为 rvalue。
  - A temporary object or subobject, or a value not associated with an object. Prvalues and xvalues are called rvalues.
- 示例 | Example
  - 任何 prvalue 或 xvalue 都是 rvalue。
- 💡实践提示 | Practice Tips
  - rvalue 通常不能出现在赋值运算符的左侧（除非是右值引用）。

### lvalue Operands | 左值操作数 🟢
- 定义 | Definition
  - 某些运算符要求其操作数必须是 lvalue。
  - Certain operators require their operands to be lvalues.
- 示例 | Example
  - `&` (取地址运算符)
  - `++`, `--` (前缀和后缀增量/减量运算符)
  - 赋值运算符 (`=`, `+=`, `-=`, `*=`, `/=`, `%=` 等) 的左操作数。
- 💡实践提示 | Practice Tips
  - 尝试对非 lvalue 执行这些操作会导致编译错误，例如 `(i++)++` 是错误的，因为 `i++` 的结果是 prvalue。

### Operator Precedence | 运算符优先级 🟢
- 定义 | Definition
  - 复合表达式中操作的求值顺序由 C++ 为所有运算符定义的优先级规则确定。优先级高的运算符在优先级低的运算符之前求值。
  - The order of evaluation of the operations in a compound expression determines the value of the expression. C++ defines this order through precedence rules for all of its operators.
- 示例 | Example
  - `2 + 3 * 4` 会先计算 `3 * 4` (乘法优先级高于加法)，结果为 `14`。
- 💡实践提示 | Practice Tips
  - 使用括号 `()` 可以覆盖默认的优先级顺序，例如 `(2 + 3) * 4` 结果为 `20`。

### Order of Evaluation | 求值顺序 🟢
- 定义 | Definition
  - 复合表达式根据优先级表定义的规则进行求值。有些运算符从左到右结合，而另一些则从右到左结合。
  - A compound expression evaluates according to rules defined through the precedence table. Some operators associate from left to right, while other operators associate from right to left.
- 示例 | Example
  - 赋值运算符 (`=`) 从右到左结合，例如 `i = j = k = 3;`。
  - 乘法运算符 (`*`) 从左到右结合，例如 `a * b / c` 等同于 `(a * b) / c`。
- 💡实践提示 | Practice Tips
  - 了解结合性对于理解复杂表达式的求值顺序至关重要。

### Postfix Expressions | 后缀表达式 🟡
- 定义 | Definition
  - 后缀表达式是指后缀运算符跟随单个操作数或两个操作数中的第一个操作数的表达式。
  - Postfix expressions are expressions in which a postfix operator follows a single operand or the first operand of two operands.
- 示例 | Example
  - 数组下标 `a[i]`
  - 函数调用 `func()`
  - 成员选择 `obj.member`, `ptr->member`
  - 后缀增量/减量 `i++`, `i--`
  - 类型识别 `typeid()`
  - 强制类型转换 `static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast`
- 💡实践提示 | Practice Tips
  - 后缀增量/减量运算符在访问值 *之后* 改变 lvalue，表达式本身是 prvalue。

### Subscripting Operator `[]` | 下标运算符 `[]` 🟢
- 定义 | Definition
  - 下标运算符的左操作数是指向类型 `T` 的指针，右操作数是整数类型的值。表达式标识一个可修改的 lvalue，其偏移量由第二个操作数指定。操作结果是类型 `T` 的 lvalue。
  - The subscripting operator takes as its left operand a pointer of type `T` and as its right operand a value of integral type. The expression identifies a modifiable lvalue at the offset from the address stored in the first operand specified by the second operand. The result of the operation is an lvalue of type `T`.
- 示例 | Example
  - `double a[10]; int i = 2; a[i] = 6;` 中的 `a[i]` 是一个 lvalue。
  - `char name[] = "Jane Doe"; char* surname = &name[5]; surname[-1] = '.';` 允许负下标。
- 💡实践提示 | Practice Tips
  - C++ 允许负下标，但必须确保元素在数组边界内。

### Member Selection `.` and `->` | 成员选择 `.` 和 `->` 🟢
- 定义 | Definition
  - 成员选择运算符通过其左操作数标识一个对象，通过其右操作数标识一个成员的名称。
  - The member selection operators identify an object by their left operand and the name of a member by their right operand.
- 示例 | Example
  - **直接选择 (`.`)**: `S s; s.x = 1;` 中的 `s.x`。
  - **间接选择 (`->`)**: `S* ptr; ptr->x = 1;` 中的 `ptr->x`。
- 💡实践提示 | Practice Tips
  - `.` 用于对象，`->` 用于指向对象的指针。

### Postfix Increment and Decrement `++`, `--` | 后缀增量和减量 `++`, `--` 🟢
- 定义 | Definition
  - 后缀增量和减量运算符在访问值 *之后* 改变 lvalue。操作数是整数、浮点或指针类型，并且必须是可修改的 lvalue。表达式本身是 prvalue。
  - The postfix increment and decrement operators change an lvalue by one unit *after* accessing the value. The operand is of integral, floating-point, or pointer type and followed by the increment (`++`) or decrement (`--`) operator. The operand must be a modifiable lvalue and the expression itself is a prvalue.
- 示例 | Example
  - `int i = 10; std::cout << i++ << std::endl;` 输出 `10`，然后 `i` 变为 `11`。
  - `(i++)++;` 会导致编译错误，因为 `i++` 的结果是 prvalue，不能再次被增量。
- 💡实践提示 | Practice Tips
  - 对于无符号类型，在达到极限值时会发生环绕（wrap-around）。对于有符号类型，溢出/下溢结果是未定义的。

### `typeid()` Operator (optional for OOP345) | `typeid()` 运算符 (OOP345 可选) 🟡
- 定义 | Definition
  - 类型标识符运算符查询有关类型的信息。它接受一个类型或一个表达式，并引用一个表示表达式动态类型的 `std::type_info` 对象。
  - The type identifier operator queries information about a type. The operator takes either a type or an expression and refers to a `std::type_info` that represents the dynamic type of the expression.
- 示例 | Example
  - `typeid(int)` 或 `typeid(myObject)`。
- 💡实践提示 | Practice Tips
  - 主要用于运行时类型识别 (RTTI)。

### Constrained Cast Operators | 受限的类型转换运算符 🟡
- 定义 | Definition
  - C++ 提供了四种受限的类型转换运算符，用于执行特定类型的转换，比 C 风格的类型转换更安全、更明确。
  - C++ provides four constrained cast operators for performing specific types of conversions, which are safer and more explicit than C-style casts.

#### `static_cast` Operator | `static_cast` 运算符 🟡
- 定义 | Definition
  - `static_cast<T>(v)` 运算符将表达式 `v` 转换为类型 `T`。它执行标准（隐式）转换及其反向转换，以及相关类之间的转换等。不能用于去除 `const` 属性。
  - The `static_cast<T>(v)` operator converts expression `v` to type `T`. It can perform standard (implicit) conversions and their opposite, conversions between related classes, etc. It cannot cast away `const`-ness.
- 示例 | Example
  - `int i = 10; double d = static_cast<double>(i);`
  - `Base* b = new Derived(); Derived* d = static_cast<Derived*>(b);` (安全向下转换，但需要程序员保证类型正确)
- 💡实践提示 | Practice Tips
  - 适用于明确且安全的类型转换，例如数值类型转换、类层次结构中的向上转换。

#### `reinterpret_cast` Operator | `reinterpret_cast` 运算符 🔴
- 定义 | Definition
  - `reinterpret_cast<T>(v)` 运算符将表达式 `v` 转换为类型 `T`。它执行低级别的、位模式的重新解释转换，例如指针到指针的不同类型转换、指针到整数类型转换。不能用于去除 `const` 属性。
  - The `reinterpret_cast<T>(v)` operator converts expression `v` to type `T`. It can perform low-level, bit-pattern reinterpretation conversions, such as pointer to pointer of different type, pointer to integral, etc. It cannot cast away `const`-ness.
- 示例 | Example
  - `int* p = new int(10); char* c = reinterpret_cast<char*>(p);`
- 💡实践提示 | Practice Tips
  - 这是最危险的类型转换，应谨慎使用，因为它几乎不提供类型安全检查。

#### `const_cast` Operator | `const_cast` 运算符 🟡
- 定义 | Definition
  - `const_cast<T>(v)` 运算符将表达式 `v` 转换为类型 `T`。它主要用于添加或去除对象的 `const` 或 `volatile` 属性。
  - The `const_cast<T>(v)` operator converts expression `v` to type `T`. It is primarily used to add or remove `const` or `volatile` attributes from an object.
- 示例 | Example
  - `const int x = 10; int& ref = const_cast<int&>(x);` (修改 `ref` 可能会导致未定义行为，如果 `x` 最初是 `const`)
- 💡实践提示 | Practice Tips
  - 只能用于指针或引用类型。修改通过 `const_cast` 获得的非常量对象，如果原始对象是常量，则会导致未定义行为。

#### `dynamic_cast` Operator (optional for OOP345) | `dynamic_cast` 运算符 (OOP345 可选) 🔴
- 定义 | Definition
  - `dynamic_cast<T>(v)` 运算符将表达式 `v` 转换为类型 `T`。`T` 是指向完整类型或其引用的指针或引用。它主要用于在类层次结构中执行安全的向下转换（downcasting），并在运行时进行类型检查。不能用于去除 `const` 属性。
  - The `dynamic_cast<T>(v)` operator converts expression `v` to type `T`. `T` is a pointer or reference to a complete type. It is primarily used for safe downcasting in class hierarchies and performs runtime type checking. It cannot cast away `const`-ness.
- 示例 | Example
  - `Base* b = new Derived(); Derived* d = dynamic_cast<Derived*>(b);` (如果 `b` 实际指向 `Derived` 对象，则转换成功，否则返回 `nullptr`)
- 💡实践提示 | Practice Tips
  - 只能用于多态类（至少有一个虚函数）。如果转换失败，对于指针类型返回 `nullptr`，对于引用类型抛出 `std::bad_cast` 异常。

### Prefix Expressions | 前缀表达式 🟡
- 定义 | Definition
  - 前缀表达式是运算符位于操作数之前的增量和减量表达式，并从右到左结合。
  - The prefix expressions are increment and decrement expressions in which the operator precedes the operand and associates from right to left.
- 示例 | Example
  - 前缀增量/减量 `++i`, `--i`
- 💡实践提示 | Practice Tips
  - 前缀增量/减量运算符在访问值 *之前* 改变 lvalue，表达式本身是 lvalue。

### Prefix Increment and Decrement `++`, `--` | 前缀增量和减量 `++`, `--` 🟢
- 定义 | Definition
  - 前缀增量 (`++`) 和减量 (`--`) 运算符在访问值 *之前* 改变 lvalue。操作结果是 lvalue，与它们的后缀对应物不同。操作数必须是可修改的 lvalue。
  - The prefix increment (`++`) and decrement (`--`) operators change an lvalue by one unit *before* accessing the value. The result of the operation is an lvalue, unlike their post-fix counterparts. The operand must be a modifiable lvalue.
- 示例 | Example
  - `int i = 10; std::cout << ++i << std::endl;` 输出 `11`，然后 `i` 变为 `11`。
  - `++(++i);` 是合法的，因为 `++i` 的结果是 lvalue。
- 💡实践提示 | Practice Tips
  - 对于无符号类型，在达到极限值时会发生环绕。对于有符号类型，溢出/下溢结果是未定义的。

### Unary Expressions | 一元表达式 🟡
- 定义 | Definition
  - 一元表达式是运算符位于单个操作数之前的表达式。它们包括大小求值、逻辑和位反转、算术正负、取地址、间接寻址和类型转换。一元运算符从右到左结合。
  - The unary expressions are expressions in which the operator precedes a single operand. They include size evaluation, logical and bit-wise negation, arithmetic plus and negation, addressing, indirection, and type casting. Unary operators associate from right to left.
- 示例 | Example
  - `sizeof`, `!`, `~`, `-`, `+`, `&`, `*`, `new`, `delete`, `alignof`, `noexcept`, `(type)`
- 💡实践提示 | Practice Tips
  - 了解每个一元运算符的功能和结合性。

### `sizeof()`, `sizeof` | `sizeof()`，`sizeof` 运算符 🟢
- 定义 | Definition
  - `sizeof()` 运算符评估其操作数的 **类型** 并返回其大小（以字节为单位）。`sizeof` 运算符（不带括号）返回变量、对象或表达式所使用的字节数。结果是 `size_t` 类型（无符号整数类型）的常量。
  - The `sizeof()` operator evaluates the **type** of its operand and returns its size in bytes. The `sizeof` operator (without the parentheses) returns the number of bytes used by a variable, object, or expression. The result of either `sizeof` operation is a constant of type `size_t` (an unsigned integral type).
- 示例 | Example
  - `sizeof(int)` 返回 `int` 类型的大小。
  - `double x; sizeof x;` 返回 `double` 变量 `x` 的大小。
  - `sizeof j++;` 不会实际执行 `j++`，因为 `sizeof` 在编译时求值。
- 💡实践提示 | Practice Tips
  - `sizeof` 在编译时求值，不会执行其操作数表达式的副作用。
  - 对于数组名，`sizeof` 返回整个数组的大小；对于作为函数参数传递的数组，`sizeof` 返回指针的大小。

### Logical Negation `!` | 逻辑非 `!` 🟢
- 定义 | Definition
  - 逻辑非运算符 (`!`) 将其操作数转换为 `bool` 值并返回该值的相反值。操作数可以是整数、浮点或指针类型。表达式求值为 prvalue。
  - The logical negation operator (`!`) converts its operand to a `bool` value and returns the converse of that value. The operand may be of integral type, floating-point type, or pointer type. The expression evaluates to a prvalue.
- 示例 | Example
  - `!true` 为 `false`。
  - `!0` 为 `true`。
  - `!nullptr` 为 `true`。
- 💡实践提示 | Practice Tips
  - `0`, `0.0`, `nullptr` 被视为 `false`，其他值被视为 `true`。

### Bit-Wise Negation `~` | 按位非 `~` 🟡
- 定义 | Definition
  - 按位非运算符 (`~`) 对其整数操作数的每个位执行逻辑非操作。
  - The bit-wise negation operator (`~`) performs a logical NOT operation on each bit of its integral operand.
- 示例 | Example
  - `~0b00000001` (假设 8 位) 结果为 `0b11111110`。
- 💡实践提示 | Practice Tips
  - 仅适用于整数类型。

### Arithmetic Negation `-` | 算术负号 `-` 🟢
- 定义 | Definition
  - 一元负号运算符 (`-`) 求值为其操作数符号反转后的值。结果是操作数经过任何提升后的相同类型的 prvalue。
  - The unary negation operator (`-`) evaluates to its operand with its sign reversed. The result is a prvalue of the same type as the operand after any promotions.
- 示例 | Example
  - `-10` 结果为 `-10`。
  - 对于无符号类型，`-a` 等于 `2^n - a` (其中 `n` 是位数)。
- 💡实践提示 | Practice Tips
  - 对于有符号整数或浮点类型，如果发生溢出，结果是未定义的。

### Arithmetic Plus `+` | 算术正号 `+` 🟢
- 定义 | Definition
  - 一元正号运算符 (`+`) 求值为其操作数。结果是操作数经过任何提升后的相同类型的 prvalue。该运算符的存在是为了对称性。
  - The unary plus operator (`+`) evaluates to its operand. The result is a prvalue of the same type as the operand after any promotions. The operator is present in the language for symmetry.
- 示例 | Example
  - `+10` 结果为 `10`。
- 💡实践提示 | Practice Tips
  - 通常不改变操作数的值或类型。

### Address of `&` | 取地址 `&` 🟢
- 定义 | Definition
  - 取地址运算符 (`&`) 返回其操作数的指针：该值是操作数的地址。操作数必须是不可修改的 lvalue。表达式是 prvalue。
  - The address-of operator (`&`) returns a pointer to its operand: the value is the address of the operand. The operand must be an lvalue that is not of storage class `register`. The expression is a prvalue.
- 示例 | Example
  - `int x = 10; int* ptr = &x;`
- 💡实践提示 | Practice Tips
  - 不能对位域取地址。

### Indirection `*` | 间接寻址 `*` 🟢
- 定义 | Definition
  - 间接寻址运算符 (`*`) 返回操作数所包含地址中存储的值。表达式本身是 lvalue。
  - The indirection operator (`*`) returns the value stored in the address that the operand contains. The expression is itself an lvalue.
- 示例 | Example
  - `int* ptr = &x; *ptr = 20;`
- 💡实践提示 | Practice Tips
  - 间接寻址和取地址运算符互为逆运算，`*&x` 的结果是 `x`。

### Cast `(type)` | 类型转换 `(type)` 🟢
- 定义 | Definition
  - 类型转换运算符由类型名后跟一个操作数组成，将操作数转换为指定类型。表达式是 prvalue。
  - The type-cast operator consists of a type name followed by an operand and converts the operand to the specified type. The operand may not be the name of an array. The expression is a prvalue.
- 示例 | Example
  - **C 风格转换**: `(double)i`
  - **C++ 函数风格转换**: `double(i)`
- 💡实践提示 | Practice Tips
  - C 风格转换功能强大但不够安全，C++ 推荐使用 `static_cast` 等受限转换运算符。

### `alignof()` Operator | `alignof()` 运算符 🟡
- 定义 | Definition
  - `alignof()` 运算符返回其操作数的对齐要求。操作数可以是表示完整对象类型的类型标识符，或数组或对这些类型之一的引用。操作返回 `std::size_t` 类型的整数常量。
  - The `alignof()` operator returns the alignment requirement of its operand. The operand may be a type identifier representing the type of a complete object, or an array or a reference to one of those types. The operation returns an integral constant of type `std::size_t`.
- 示例 | Example
  - `alignof(int)` 返回 `int` 类型的对齐要求。
- 💡实践提示 | Practice Tips
  - 用于查询类型或对象的内存对齐要求。

### `decltype()` Specifier | `decltype()` 说明符 🟡
- 定义 | Definition
  - `decltype()` 说明符求值为其参数的类型和值类别。操作数可以是实体或表达式。表达式的值类别会影响类型。
  - The `decltype()` specifier evaluates to the type and value category of its argument. The operand may be an entity or an expression. The value category of the expression affects the type.
- 示例 | Example
  - `int i = 3, j = 6; decltype(i + j) y = i + j;` (`y` 的类型是 `int`)
  - `double& r = x; decltype(r) s = r;` (`s` 的类型是 `double&`)
- 💡实践提示 | Practice Tips
  - 如果表达式的值类别是 xvalue，则类型是 `T&&`。
  - 如果表达式的值类别是 lvalue，则类型是 `T&`。
  - 如果表达式的值类别是 prvalue，则类型是 `T`。

### `noexcept()` Operator | `noexcept()` 运算符 🟡
- 定义 | Definition
  - 无异常运算符 (`noexcept()`) 如果参数不抛出异常则返回 `true`。这个编译时函数求值为 `bool` 类型的 prvalue。此运算符不评估传递给它的参数。
  - The no exception operator (`noexcept()`) returns true if the argument does not throw an exception. This compile-time function evaluates to a prvalue of type `bool`. This operator does not evaluate the argument passed to it.
- 示例 | Example
  - `noexcept(some_function_call())`
- 💡实践提示 | Practice Tips
  - 用于在编译时检查表达式是否可能抛出异常。

### `throw` Operator | `throw` 运算符 🟢
- 定义 | Definition
  - `throw` 运算符标识正常执行的异常。该运算符从其操作数创建一个临时对象，并将控制权转移到异常处理程序。异常对象是 `throw` 表达式操作数类型的 lvalue。
  - The throw operator (`throw`) identifies an exception to normal execution. The operator creates a temporary object from its operand and transfers control to the exception handler. The exception object is an lvalue of the type of the operand of the throw expression.
- 示例 | Example
  - `throw "divide by zero inadmissible";`
- 💡实践提示 | Practice Tips
  - 用于在程序中抛出异常，通常与 `try-catch` 块一起使用。

### Binary Expressions | 二元表达式 🟡
- 定义 | Definition
  - 二元表达式由两个操作数和一个运算符组成。它们包括算术、关系、逻辑和位运算表达式。它们求值为 prvalue。
  - Binary expressions consist of two operands and one operator. They include arithmetic, relative, logical, and bit-wise expressions. They evaluate to prvalues.
- 示例 | Example
  - `a + b`, `x == y`, `p && q`
- 💡实践提示 | Practice Tips
  - 了解不同类型的二元运算符及其行为。

### Arithmetic Binary Operators | 算术二元运算符 🟢
- 定义 | Definition
  - 执行加、减、乘、除、取模等算术运算的二元运算符。
  - Binary operators that perform arithmetic operations such as addition, subtraction, multiplication, division, and modulo.
- 示例 | Example
  - **乘法 (`*`), 除法 (`/`), 取模 (`%`)**: `a * b`, `a / b`, `a % b`
  - **加法 (`+`)**: `a + b`
  - **减法 (`-`)**: `a - b`
- 💡实践提示 | Practice Tips
  - 取模运算符 (`%`) 仅适用于整数类型。
  - 指针算术有特殊规则。

### Bit-Shifting `<<`, `>>` | 位移 `<<`, `>>` 🟡
- 定义 | Definition
  - 位移运算符 (`<<`, `>>`) 用于将整数操作数的位向左或向右移动。
  - Bit-shifting operators (`<<`, `>>`) are used to shift the bits of an integral operand to the left or right.
- 示例 | Example
  - `1 << 2` (将 1 左移 2 位，结果为 4)
- 💡实践提示 | Practice Tips
  - 详见 [Bit-Wise Expressions](/H-Deeper-Detail/bit-wise-expressions) 章节。

### Relational Operators | 关系运算符 🟢
- 定义 | Definition
  - 关系表达式比较两个操作数的值以确定相对大小、相等或不相等。操作数可以是算术、枚举或指针类型。结果是 `bool` 类型。
  - A relational expression compares the values of two operands for relative magnitude, equality, or inequality. The operands are of arithmetic, enumeration, or pointer type. A relational expression is of type `bool` and evaluates to either `true` or `false`.
- 示例 | Example
  - **小于 (`<`), 小于等于 (`<=`)**: `a < b`, `a <= b`
  - **大于 (`>`), 大于等于 (`>=`)**: `a > b`, `a >= b`
  - **相等 (`==`)**: `a == b`
  - **不相等 (`!=`)**: `a != b`
- 💡实践提示 | Practice Tips
  - 对于指针类型，比较的是地址。
  - `if (x != 0)` 等同于 `if (x)`。

### Bit-Wise Logical Operators `&`, `|`, `^` | 按位逻辑运算符 `&`, `|`, `^` 🟡
- 定义 | Definition
  - 按位逻辑运算符 (`&`, `|`, `^`) 对其整数操作数的每个位执行逻辑 AND、OR 或 XOR 操作。
  - Bit-wise logical operators (`&`, `|`, `^`) perform logical AND, OR, or XOR operations on each bit of their integral operands.
- 示例 | Example
  - `a & b` (按位与)
  - `a | b` (按位或)
  - `a ^ b` (按位异或)
- 💡实践提示 | Practice Tips
  - 详见 [Bit-Wise Expressions](/H-Deeper-Detail/bit-wise-expressions) 章节。

### Logical Binary Operators `&&`, `||` | 逻辑二元运算符 `&&`, `||` 🟢
- 定义 | Definition
  - 逻辑二元表达式评估其操作数的组合真值。操作数可以是整数、浮点或指针类型。结果是 `bool` 类型。
  - Binary logical expressions evaluate the combined truthfulness of their operands. The operands may be of integral type, floating-point type, or pointer type. Logical expressions evaluate to values of type `bool`: `false` or `true`.
- 示例 | Example
  - **逻辑与 (`&&`)**: `true && false` 为 `false`。
  - **逻辑或 (`||`)**: `true || false` 为 `true`。
- 💡实践提示 | Practice Tips
  - **短路求值 (Short-circuit evaluation)**: 逻辑表达式从左到右求值。如果左操作数已经确定了结果，则右操作数不会被求值。例如，`false && expr` 不会求值 `expr`。
  - **求值顺序很重要 (Order Matters)**: 利用短路求值特性，可以编写更安全的条件判断，例如 `if (nullptr != a && 6 == a[i])`。

### Assignment Expressions | 赋值表达式 🟢
- 定义 | Definition
  - 赋值表达式将右操作数的值复制到左操作数。左操作数必须是可修改的 lvalue。赋值表达式从右到左结合。
  - An assignment expression copies from the right operand to the left operand. The left operand must be a modifiable lvalue. Because assignment expressions associate from right to left, cascading is possible.
- 示例 | Example
  - **简单赋值 (`=`)**: `i = 10;`
  - **复合赋值 (`+=`, `-=`, `*=`, `/=`, `%=` 等)**: `i += 5;` 等同于 `i = i + 5;`
- 💡实践提示 | Practice Tips
  - 赋值可以级联，例如 `i = j = k = 3;`。
  - 对于封装了数组的类类型，简单赋值可以复制所有元素。

### Sequential Expressions `,` | 顺序表达式 `,` 🟡
- 定义 | Definition
  - 逗号运算符 (`,`) 将表达式分隔开，按顺序从左到右单独求值。顺序表达式的结果类型和值是其最右侧操作数的类型和值。
  - The comma operator (`,`) divides expressions for separate evaluation in sequence from the left. The type and value of the result of a sequential expression is that of its rightmost operand.
- 示例 | Example
  - `for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)`
- 💡实践提示 | Practice Tips
  - 常见于 `for` 循环的初始化和步进部分。

### Mixed-Type Binary Expressions | 混合类型二元表达式 🟡
- 定义 | Definition
  - 如果表达式中的操作数类型不兼容，编译器会根据类型层次结构将较低类型的操作数提升为较高类型。
  - If the operands in the expression are not of the type defined for the operator, one of the operands must be converted to a compatible type. The compiler promotes operands types if necessary to evaluate a binary expression.
- 示例 | Example
  - `int i = 1; double d = 2.5; i + d;` (`i` 会被提升为 `double` 类型再进行加法运算)。
- 💡实践提示 | Practice Tips
  - **无符号陷阱 (The Unsigned Trap)**: 如果一个操作数是无符号整数类型，另一个是有符号整数类型，有符号类型的值会被提升为无符号类型，这可能导致反直觉的结果，例如 `(len > -1)` 对于 `unsigned len = 0u;` 会求值为 `false`。
  - **避免隐式提升 (Avoid Implicit Promotions)**: 隐式提升不一定可移植，最好显式地进行类型转换。
  - **细分复杂二元表达式 (Sub-Divide Complex Binary Expressions)**: 复杂二元表达式的求值顺序可能依赖于实现，细分可以确保结果一致性。

### Ternary Expression `?:` | 三元表达式 `?:` 🟢
- 定义 | Definition
  - 三元表达式是条件表达式。第一个运算符 (`?`) 标识表达式为选择构造；第二个运算符 (`:`) 分隔选择。如果最左边的操作数求值为 `true`，则表达式求值第二个操作数；否则求值第三个操作数。结果是求值操作数的类型和值。
  - The ternary expression is a conditional expression. The first operator (`?`) identifies the expression as a selection construct; the second operator (`:`) separates the choices. If the leftmost operand evaluates to `true`, the expression evaluates the second operand, but not the third operand. If the leftmost operand evaluates to `false`, the expression evaluates the third operand, but not the second operand. The result is a value of the type of the evaluated operand.
- 示例 | Example
  - `int sign(int x) { return x < 0 ? -1 : 1; }`
- 💡实践提示 | Practice Tips
  - 提供了一种避免多个 `return` 语句的简洁方法。
  - 由于条件运算符优先级较低，在其他表达式中使用时通常需要用括号括起来。

## 4. FAQ (常见问题)

- **Q: 什么是 lvalue 和 rvalue？**
  - **A:** lvalue (左值) 是指可以出现在赋值运算符左侧的表达式，它表示一个内存位置，例如变量名。rvalue (右值) 是指不能出现在赋值运算符左侧的表达式，它表示一个临时值或不占用存储位置的值，例如字面量或函数返回的临时对象。
  - **A:** An lvalue (left value) is an expression that can appear on the left side of an assignment operator, representing a memory location, such as a variable name. An rvalue (right value) is an expression that cannot appear on the left side of an assignment operator, representing a temporary value or a value that does not occupy a storage location, such as a literal or a temporary object returned by a function.

- **Q: 为什么 `i++` 不能再次被增量，而 `++i` 可以？**
  - **A:** `i++` (后缀增量) 的结果是一个 prvalue（纯右值），它是一个临时值，不占用可修改的存储位置，因此不能再次对其进行增量操作。而 `++i` (前缀增量) 的结果是一个 lvalue（左值），它表示一个可修改的存储位置，因此可以再次对其进行增量操作。
  - **A:** The result of `i++` (postfix increment) is a prvalue (pure rvalue), which is a temporary value that does not occupy a modifiable storage location, thus it cannot be incremented again. In contrast, the result of `++i` (prefix increment) is an lvalue (left value), which represents a modifiable storage location, and therefore can be incremented again.

- **Q: 什么是运算符的优先级和结合性？**
  - **A:** **优先级 (Precedence)** 决定了在没有括号的情况下，哪个运算符在表达式中先被求值（例如乘法高于加法）。**结合性 (Associativity)** 决定了当多个相同优先级的运算符出现在表达式中时，它们的求值顺序（例如左结合或右结合）。
  - **A:** **Precedence** determines which operator is evaluated first in an expression without parentheses (e.g., multiplication over addition). **Associativity** determines the order of evaluation when multiple operators of the same precedence appear in an expression (e.g., left-to-right or right-to-left).

## 5. 实践示例 (Practice Examples)

### 示例 1: 值类别和增量运算符
```cpp
// 目的说明 | Purpose explanation: Demonstrate lvalue, prvalue, and increment operators.
// 预期输出 | Expected output:
// 10
// ERROR (i++) is a prvalue, not an lvalue
// 11
// 13
#include <iostream>

int main() {
    int i = 10;
    std::cout << i++ << std::endl; // i++ is a prvalue, i becomes 11
    // (i++)++; // This line would cause a compile-time error: expression must be a modifiable lvalue
    std::cout << i << std::endl; // i is 11

    int j = 10;
    std::cout << ++j << std::endl; // ++j is an lvalue, j becomes 11
    ++(++j); // Valid, (++j) is an lvalue, j becomes 12, then 13
    std::cout << j << std::endl; // j is 13

    return 0;
}
```

### 示例 2: `sizeof` 运算符的行为
```cpp
// 目的说明 | Purpose explanation: Demonstrate sizeof operator behavior with variables and arrays.
// 预期输出 | Expected output:
// On this machine,
// the size of an int is 4 bytes,
// the size of x is 8 bytes
// 4
// 1
// 32
// 4
#include <iostream>

int foo(double a[]) {
    a[0] = 1.0;
    return sizeof a; // Returns size of pointer, not array
}

int main() {
    double x;
    std::cout << "On this machine, \n"
                 "the size of an int is " << sizeof(int)
              << " bytes,\nthe size of x is "
              << sizeof x << " bytes" << std::endl;

    int j = 1;
    std::cout << sizeof j++ << std::endl; // sizeof evaluated at compile time, j is not incremented
    std::cout << j << std::endl; // j is still 1

    double a[] = {1.1, 2.2, 3.3, 4.4};
    std::cout << sizeof a << std::endl; // Returns size of the entire array (8 bytes * 4 elements = 32 bytes)
    std::cout << foo(a) << std::endl; // Returns size of a double pointer (e.g., 4 or 8 bytes depending on system)

    return 0;
}
```

### 示例 3: 逻辑表达式的短路求值
```cpp
// 目的说明 | Purpose explanation: Demonstrate short-circuit evaluation in logical expressions.
// 预期输出 | Expected output:
// 1 1
// 0 1
#include <iostream>

int main() {
    int i = 1, j = 1;
    // (i < 2 || j++ == 1)
    // i < 2 is true, so j++ == 1 is not evaluated.
    std::cout << (i < 2 || j++ == 1) << ' ' << j << std::endl; // Output: 1 1

    // (j == 2 && i++ == 1)
    // j == 2 is false (j is 1), so i++ == 1 is not evaluated.
    std::cout << (j == 2 && i++ == 1) << ' ' << i << std::endl; // Output: 0 1

    return 0;
}
```

## 6. 学习建议 (Study Tips)

1.  **理解核心概念**: 重点理解 lvalue, rvalue, prvalue, xvalue, glvalue 的定义和区别，这是理解 C++ 表达式行为的基础。
2.  **掌握运算符优先级和结合性**: 熟记常用运算符的优先级和结合性，或在不确定时使用括号明确求值顺序。
3.  **注意副作用**: 了解哪些运算符会产生副作用（如增量/减量运算符），以及这些副作用何时发生。
4.  **实践短路求值**: 在编写条件逻辑时，利用逻辑运算符的短路求值特性来提高代码效率和安全性。
5.  **谨慎使用类型转换**: 优先使用 `static_cast`，避免不必要的 `reinterpret_cast` 和 `const_cast`。
6.  **避免无符号陷阱**: 在混合有符号和无符号类型时要特别小心，必要时进行显式类型转换。

## 7. 视觉优化系统 (Visual Enhancement System) 👀

### 7.1 Emoji标记系统 (Emoji Marking System)
- 📌 重点内容 | Key points
- 💡 提示信息 | Tips
- ⚠️ 注意事项 | Warnings
- 🔍 深入探讨 | In-depth discussion
- ⭐ 重点掌握 | Must master
- ❓ 待澄清概念 | Concepts to clarify
- 📖 需要补充学习 | Need more study

### 7.2 格式美化 (Format Beautification)
- 使用标题层级 | Use heading levels
- 适当留白 | Proper spacing
- 列表缩进 | List indentation
- 代码块格式化 | Code block formatting

## 8. 文档维护规范 (Document Maintenance Standards) 🔄

### 8.1 版本控制 (Version Control)
更新日期：2025-09-13
版本号：v1.0
更新内容：
- 基于 `https://advoop.sdds.ca/D-Processing/expressions` 网页内容整理 C++ 表达式知识点。
- 按照 `note_prompt.md` 规范进行结构化和格式化。

### 8.2 待办标记 (TODO Marks)
TODO: 补充更多关于位运算符的详细示例和解释，当前内容引用了其他章节。
FIXME: 检查所有中英文对照是否准确无误。
NOTE: 考虑添加更多关于表达式求值顺序中未定义行为的例子。
