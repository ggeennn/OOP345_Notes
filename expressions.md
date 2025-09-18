[Skip to main content](https://advoop.sdds.ca/D-Processing/expressions#)

On this page

# Expressions

- Classify operations into categories under rules of precedence
- Categorize expressions as lvalues, xvalues and prvalues
- Describe the features of expressions for each type-wise operator

> "C \[and hence C++\] has an unusually rich set of operators that provide access to most of the operations provided by the underlying hardware." Harbison and Steele (2002)

Expressions specify computations. They consist of sequences of operators and operands and may produce a result, possibly with side effects. A C++ expression has a non-reference type and belongs to a value category. The expression may be primary or compound as illustrated below. A compound expression consists of an operator and one or more operands. A compound expression is ultimately decomposable into a set of primary expressions connected by operators.

![Expressions](https://advoop.sdds.ca/assets/images/expressions-c5e9ed5288bc895ce1fea799ccd8bbad.svg)

The order of evaluation of the operations in a compound expression determines the value of the expression. C++ defines this order through precedence rules for all of its operators.

This chapter describes the value categories of C++ expressions, the precedence rules that apply to operators in compound expressions and the specific features associated with each operator. Expressions based on bit-wise operators are described in a later chapter entitled [Bit-Wise Expressions](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions).

## Value Categories [​](https://advoop.sdds.ca/D-Processing/expressions\#value-categories "Direct link to heading")

The value categories of C++ expressions are the basis for rules that compilers follow when creating, copying, and moving temporary objects during the evaluation of expressions. Awareness of these categories helps the programmer understand how the compiler evaluates expressions and interpret error messages that the compiler generates.

Any C++ expression is one of:

- **prvalue** \- a value that does not occupy a location in storage
- **xvalue** \- an expiring value that does occupy a location in storage (an object near the end of its lifetime)
- **lvalue** \- a locator value that occupies a location in storage

When the compiler creates a temporary object it converts a prvalue into an xvalue, which is temporarily located in memory - this is called a _temporary materialization conversion_.

Both lvalues and xvalues occupy a region of memory and together are called glvalues. A glvalue is a generalized lvalue. It evaluates to an object or a function. On the other hand, prvalues and xvalues are called rvalues. An rvalue is a temporary object or subobject, or a value not assocaited with an object.

In summary, C++17 categorizes expressions according to the taxonomy illustrated below. Any expression is either a glvalue or an rvalue.

![Value Categories](https://advoop.sdds.ca/assets/images/value-categories-2c1d6d81d7b1d0c76d7b7c6b0d7d9d8e.svg)

Many expressions evaluate to prvalues, some to lvalues, some to xvalues and some to no value. The specific descriptions below identify the category to which each expression evaluates.

### lvalue Operands [​](https://advoop.sdds.ca/D-Processing/expressions\#lvalue-operands "Direct link to heading")

lvalue operands include:

- a name that is not an array name
- an array element - `a[i]`
- `(expression)` \- where `expression` is itself an lvalue
- a direct member selection - `expression.member` \- where expression is itself an lvalue
- an indirect member selection - `expression->member` \- where expression points to an lvalue
- a dereferenced address - `*expression`
- a string literal (actually an array of characters)

The operands associated with the following three operators must be lvalues:

- `&`
- `++`
- `--`

The left operands associated with the assignment operators must be lvalues:

- `=`
- `+=`
- `-=`
- `*=`
- `/=`
- `%=`

## Operator Precedence [​](https://advoop.sdds.ca/D-Processing/expressions\#operator-precedence "Direct link to heading")

Expressions are divided into six operand-related classifications:

- primary
- postfix
- prefix
- unary
- binary
- ternary

Primary expressions are the fundamental expressions from which all other expressions are built. A primary expression consists of a single operand without any operator. The operand may be the name of an entity or a literal. Non-primary expressions consist of one operator and one or more operands. The operands may be primary or compound expressions.

### Order of Evaluation [​](https://advoop.sdds.ca/D-Processing/expressions\#order-of-evaluation "Direct link to heading")

A compound expression evaluates according to rules defined through the precedence table below. These rules cannot be changed. The compiler evaluates the expression with the operator that has a higher precedence before evaluating any other expression. Some operators associate from left to right, while other operators associate from right to left.

| Precedence | Class | Operator | Description | Associates |
| --- | --- | --- | --- | --- |
| 18 | primary |  | name, literal |  |
| 18 | binary | `::` | scope resolution |  |
| 17 | postfix | `[]` | array subscripting | left-to-right |
| 17 | postfix | `( )` | function call | left-to-right |
| 17 | postfix | `.` | direct selection | left-to-right |
| 17 | postfix | `->` | indirect selection | left-to-right |
| 17 | postfix | `++` `--` | postfix increment, decrement | left-to-right |
| 17 | postfix | `typeid()` | type name | left-to-right |
| 17 | postfix | `const_cast` | constant type conversion | left-to-right |
| 17 | postfix | `dynamic_cast` | dynamic type conversion | left-to-right |
| 17 | postfix | `reinterpret_cast` | reinterpreted type conversion | left-to-right |
| 17 | postfix | `static_cast` | static type conversion | left-to-right |
| 16 | prefix | `++` `--` | prefix increment, decrement | right-to-left |
| 16 | unary | `sizeof` | size | right-to-left |
| 16 | unary | `!` | logical negation | right-to-left |
| 16 | unary | `~` | bit-wise negation | right-to-left |
| 16 | unary | `-` `+` | arithmetic negation, plus | right-to-left |
| 16 | unary | `&` | address of | right-to-left |
| 16 | unary | `*` | indirection | right-to-left |
| 16 | unary | `new` `new[]` | dynamic memory allocation | right-to-left |
| 16 | unary | `delete` `delete[]` | dynamic memory deallocation | right-to-left |
| 16 | unary | `alignof(type)` | alignment requirement | right-to-left |
| 16 | unary | `noexcept()` | controls exception throwing | right-to-left |
| 16 | unary | `(type)` | type casting | right-to-left |
| 15 | binary | `.*` | object to member pointer | left-to-right |
| 15 | binary | `->*` | pointer to member pointer | left-to-right |
| 14 | binary | `*` `/` `%` | multiplicative | left-to-right |
| 13 | binary | `+` `-` | additive | left-to-right |
| 12 | binary | `<<` `>>` | left and right bit shifting | left-to-right |
| 11 | binary | `<` `>` `<=` `>=` | relational | left-to-right |
| 10 | binary | `==` `!=` | equality, inequality | left-to-right |
| 9 | binary | `&` | bit-wise logical and | left-to-right |
| 8 | binary | `^` | bit-wise logical exclusive or | left-to-right |
| 7 | binary | `ǀ` | bit-wise logical or | left-to-right |
| 6 | binary | `&&` | logical and | left-to-right |
| 5 | binary | `ǀǀ` | logical or | left-to-right |
| 4 | ternary | `?:` | conditional | right-to-left |
| 3 | binary | `=` `+=` `-=` `*=` `/=` `%=` | compound type-wise assignment | right-to-left |
| 3 | binary | `~=` `&=` `^=` `ǀ=` `>>=` `<<=` | compound bit-wise assignment | right-to-left |
| 2 | unary | `throw` | transfers control to exception handler | left-to-right |
| 1 | binary | `,` | sequencing | left-to-right |

To override the order defined in this table, we enclose the expressions to be evaluated first within parentheses.

## Postfix Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#postfix-expressions "Direct link to heading")

Postfix expressions are expressions in which a postfix operator follows a single operand or the first operand of two operands. Postfix operators include the subscripting operator, the function call operator, the member selection operator, the postfix increment operator, and the postfix decrement operator.

### Subscripting Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#subscripting-operator "Direct link to heading")

The subscripting operator takes as its left operand a pointer of type `T` and as its right operand a value of integral type. The expression identifies a modifiable lvalue at the offset from the address stored in the first operand specified by the second operand. The result of the operation is an lvalue of type `T`. For example,

```codeBlockLines_e6Vv
double a[10];
int i = 2;

a[i] = 6; // lvalue

```

`a` holds the address of array `a[10]`, `i` is an integral type, and `a[i]` refers to the `i`-th element beyond the start of `a`.

C++ accepts negative subscripts provided that the element is within the array's bounds. For example,

```codeBlockLines_e6Vv
char  name[] = "Jane Doe";
char* surname = nullptr;

surname = &name[5];
surname[-1] = '.';  // changes "Jane Doe" to "Jane.Doe"

```

### Member Selection [​](https://advoop.sdds.ca/D-Processing/expressions\#member-selection "Direct link to heading")

The member selection operators identify an object by their left operand and the name of a member by their right operand. A selection operation takes either of two forms: direct selection and indirect selection.

#### Direct Selection [​](https://advoop.sdds.ca/D-Processing/expressions\#direct-selection "Direct link to heading")

The direct selection operator ( `.`) takes an object of complete class type as its left operand and the member name as its right operand:

```codeBlockLines_e6Vv
// Direct Selection
// direct.cpp

#include <iostream>

typedef struct
{
    int x;
    double y;
} S;

int main()
{
    S s = {0, 0.0};

    s.x = 1; // lvalue
    std::cout << "x = " << s.x << "; y = " << s.y << std::endl;
}

```

```codeBlockLines_e6Vv
x = 1; y = 0

```

#### Indirect Selection [​](https://advoop.sdds.ca/D-Processing/expressions\#indirect-selection "Direct link to heading")

The indirect selection operator ( `->`) takes a pointer to an object of complete class type as its left operand and the member name as its right operand

```codeBlockLines_e6Vv
// Indirect Selection
// indirect.cpp

#include <iostream>

typedef struct
{
    int x;
    double y;
} S;

S* add2(S *s)
{
    s->x += 2;
    s->y += 2;
    return s;
}

int main()
{
    S s = {0, 0};

    add2(&s)->x++;  // add2(&s) is modifiable
    std::cout << "x = " << s.x << "; y = " << s.y << std::endl;
}

```

```codeBlockLines_e6Vv
x = 3; y = 2

```

### Postfix Increment and Decrement [​](https://advoop.sdds.ca/D-Processing/expressions\#postfix-increment-and-decrement "Direct link to heading")

The postfix increment and decrement operators change an lvalue by one unit _after_ accessing the value. The operand is of integral, floating-point, or pointer type and followed by the increment ( `++`) or decrement ( `--`) operator. The operand must be a modifiable lvalue and the expression itself is a prvalue.

```codeBlockLines_e6Vv
// Post-Fix Operators
// postfix.cpp

#include <iostream>

int main()
{
    int i = 10;

    std::cout << i++ << std::endl;
    (i++)++;           // ERROR (i++) is a prvalue, not an lvalue
    std::cout << i << std::endl;
}

```

#### Results at Integer Limits [​](https://advoop.sdds.ca/D-Processing/expressions\#results-at-integer-limits "Direct link to heading")

If the operand is of `unsigned` type and its value is `0u`, the decrement operator changes the lvalue to the largest storable value. If the operand is of `unsigned` type and its value is the largest storable value, the increment operator changes the lvalue to 0u.

```codeBlockLines_e6Vv
// Post-Fix Operators on Unsigned Values
// unsigned.cpp

#include <iostream>

int main()
{
    unsigned i = 0u;

    i--;
    std::cout << i++ << std::endl;
    std::cout << i << std::endl;
}

```

```codeBlockLines_e6Vv
4294967295
0

```

If the operand is of `signed` integral type, floating-point type, or pointer type, and the increment/decrement operation produces an overflow/underflow, the result is undefined.

### `typeid()` Operator (optional for OOP345) [​](https://advoop.sdds.ca/D-Processing/expressions\#typeid-operator-optional-for-oop345 "Direct link to heading")

The type identifier operator queries information about a type. The operator takes either a type or an expression and refers to a `std::type_info` that represents the dynamic type of the expression. The `std::type_info` object holds implementation-specific information about a type, which includes its name and the means to compare for equality. For an example of how this operator is used see the section entitled [Dynamic Type Identification](https://advoop.sdds.ca/C-Class-Relationships/inheritance-and-inclusion-polymorphism#dynamic-type-identification-optional) in the Chapter [Inheritance and Inclusion Polymorphism](https://advoop.sdds.ca/C-Class-Relationships/inheritance-and-inclusion-polymorphism).

### Constrained Cast Operators [​](https://advoop.sdds.ca/D-Processing/expressions\#constrained-cast-operators "Direct link to heading")

#### `static_cast` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#static_cast-operator "Direct link to heading")

The `static_cast<T>(v)` operator converts expression `v` to type `T`. If `T` is an lvalue reference type or an rvalue reference to a function type, the result is an lvalue. If `T` is an rvalue reference to an object type, the result is an xvalue. Otherwise, the result is a prvalue.

The `static_cast<T>(v)` operator can perform the following conversions

- Standard (Implicit) Conversions and their opposite
  - lvalue to rvalue
  - integral or floating-point promotions
  - conversions: integral, floating-point, floating-point to integral, integral to floating-point, pointer, pointer to member, boolean
  - `void*` to pointer type
- between related classes
- enumerator to integral or floating-point
- scoped enumerator to integral or floating-point
- rvalue references
- any type to void discarding the value

The `static_cast<T>(v)` operator cannot cast away `const`-ness.

#### `reinterpret_cast` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#reinterpret_cast-operator "Direct link to heading")

The `reinterpret_cast<T>(v)` operator converts expression `v` to type `T`. If `T` is an lvalue reference type or an rvalue reference to a function type, the result is an lvalue. If `T` is an rvalue reference to an object type, the result is an xvalue. Otherwise, the result is a prvalue.

The `reinterpret_cast<T>(v)` operator can perform the following conversions

- pointer to member to pointer to member of different type
- pointer to integral, integral or enumeration type to pointer
- function pointer to function pointer of different type
- object pointer to an object pointer of different type
- function pointer to object pointer (conditionally supported)

The `reinterpret_cast<T>(v)` operator cannot cast away `const`-ness.

#### `const_cast` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#const_cast-operator "Direct link to heading")

The `const_cast<T>(v)` operator converts expression `v` to type `T`. If `T` is an lvalue reference to an object type, the result is an lvalue. If `T` is an rvalue reference to an object type, the result is an xvalue. Otherwise, the result is a prvalue.

#### `dynamic_cast` Operator (optional for OOP345) [​](https://advoop.sdds.ca/D-Processing/expressions\#dynamic_cast-operator-optional-for-oop345 "Direct link to heading")

The `dynamic_cast<T>(v)` operator converts expression `v` to type `T`. `T` is a pointer or reference to a complete type. If `T` is a pointer type, `v` shall be an lvalue of a complete class and the result is an lvalue of the type referred to by `T`. If `T` is an rvalue reference to an object type, `v` shall be an glvalue of a complete class and the result is an xvalue of the type referred to by `T`.

The `dynamic_cast<T>(v)` operator cannot cast away `const`-ness.

For an example of how this operator is used see the section entitled [Specializing an Operation for a Dynamic Type](https://advoop.sdds.ca/C-Class-Relationships/inheritance-and-inclusion-polymorphism#specializing-an-operation-for-a-dynamic-type-optional) in the Chapter [Inheritance and Inclusion Polymorphism](https://advoop.sdds.ca/C-Class-Relationships/inheritance-and-inclusion-polymorphism).

## Prefix Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#prefix-expressions "Direct link to heading")

The prefix expressions are increment and decrement expressions in which the operator precedes the operand and associates from right to left.

### Prefix Increment and Decrement [​](https://advoop.sdds.ca/D-Processing/expressions\#prefix-increment-and-decrement "Direct link to heading")

The prefix increment ( `++`) and decrement ( `--`) operators change an lvalue by one unit before accessing the value. The result of the operation is an lvalue, unlike their post-fix counterparts. The operand may be of any integral type, floating-point type, or pointer type, but must be a modifiable lvalue. For example,

```codeBlockLines_e6Vv
// Pre-Fix Operators
// prefix.cpp

#include <iostream>

int main()
{
    int i = 10;

    std::cout << ++i << std::endl;
    ++(++i);           // OK (++i) is an lvalue
    std::cout << i << std::endl;
}

```

```codeBlockLines_e6Vv
11
13

```

#### Results at the Limit [​](https://advoop.sdds.ca/D-Processing/expressions\#results-at-the-limit "Direct link to heading")

The results of a prefix increment and decrement operation on upper and lower limit values of `unsigned` types and signed types are similar to those for postfix increment and decrement operations.

If the operand is of `unsigned` type and its value is 0, the decrement operation evaluates to the largest storable value. If the operand in a prefix expression is of `unsigned` type and its value is the largest storable value, the increment operation evaluates to 0.

If the operand is of `signed` integral type, floating-point type, or pointer type, and the increment/decrement operation produces an overflow/underflow, the result is undefined.

## Unary Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#unary-expressions "Direct link to heading")

The unary expressions are expressions in which the operator precedes a single operand. They include size evaluation, logical and bit-wise negation, arithmetic plus and negation, addressing, indirection, and type casting. Unary operators associate from right to left.

### `sizeof()`, `sizeof` [​](https://advoop.sdds.ca/D-Processing/expressions\#sizeof-sizeof "Direct link to heading")

The `sizeof()` operator evaluates the **type** of its operand and returns its size in bytes. The `sizeof` operator (without the parentheses) returns the number of bytes used by a variable, object, or expression. The result of either `sizeof` operation is a constant of type `size_t` (an unsigned integral type). For example,

```codeBlockLines_e6Vv
// Size of a Type
// sizeof.cpp

#include <iostream>

int main()
{
    double x;

    std::cout << "On this machine, \n"
                 "the size of an int is " << sizeof(int)
              << "bytes,\nthe size of x is "
              << sizeof x << "bytes" << std::endl;
}

```

```codeBlockLines_e6Vv
On this machine,
the size of an int is 4 bytes,
the size of x is 8 bytes.

```

`sizeof()` takes a type, while `sizeof` takes a variable, object, or expression. With some compilers, the syntax is interchangeable.

The compiler evaluates `sizeof` expressions at compile time. If its operand is an expression, the compiler does not evaluate that expression:

```codeBlockLines_e6Vv
// sizeof Operator
// sizeof.cpp

#include <iostream>

int main()
{
    int j = 1;

    std::cout << sizeof j++ << std::endl;
    std::cout << j << std::endl; // j is still 1
}

```

```codeBlockLines_e6Vv
4
1

```

If the operand is an array name and the size of the array is within the scope of the expression, the `sizeof` operator returns the size of the array in bytes; that is, the number of elements in the array times the size of the type of one array element. However, if the operand is a function parameter that holds the address of an array, the operator returns the size of the pointer that holds the address, and not the size of the array:

```codeBlockLines_e6Vv
// sizeof Operator
// sizeofArray.cpp

#include <iostream>

int foo(double a[])
{
    a[0] = 1.0;
    return sizeof a;
}

int main()
{
    double a[] = {1.1, 2.2, 3.3, 4.4};

    std::cout << sizeof a << std::endl;
    std::cout << foo(a) << std::endl;
}

```

```codeBlockLines_e6Vv
32
4

```

If the operand is an object of class type, the operation returns the sum of the sizes of the subobjects including any padding. The result is implementation dependent. For example,

```codeBlockLines_e6Vv
// sizeof Operator
// sizeofStruct.cpp

#include <iostream>

typedef struct
{
    char a;
    int b;
} A;

int main()
{
    A s;

    std::cout << sizeof s << std::endl;
}

```

```codeBlockLines_e6Vv
8

```

### Logical Negation [​](https://advoop.sdds.ca/D-Processing/expressions\#logical-negation "Direct link to heading")

The logical negation operator ( `!`) converts its operand to a `bool` value and returns the converse of that value. The operand may be of integral type, floating-point type, or pointer type. The expression evaluates to a prvalue. If the operand is `0`, `0.0` or `nullptr`, the expression evaluates to `true`. If the operand is any value other, the expression evaluates to `false`.

### Bit-Wise Negation [​](https://advoop.sdds.ca/D-Processing/expressions\#bit-wise-negation "Direct link to heading")

See [Bit-Wise Operators](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions) for the bit-wise operator ( `~`).

### Arithmetic Negation [​](https://advoop.sdds.ca/D-Processing/expressions\#arithmetic-negation "Direct link to heading")

The unary negation operator ( `-`) evaluates to its operand with its sign reversed. The result is a prvalue of the same type as the operand after any promotions.

#### Results for Unsigned Types [​](https://advoop.sdds.ca/D-Processing/expressions\#results-for-unsigned-types "Direct link to heading")

The negation operator ( `-`) applied to an operand of unsigned type deserves special attention. The result of the expression is of unsigned type and equal to 2n2^n2n-operand where nnn is the number of bits used to store the operand:

```codeBlockLines_e6Vv
// Arithmetic Negation
// minus.cpp

#include <iostream>
#include <iomanip>

int main()
{
    unsigned a = 2u;
    unsigned c = 1u;
    unsigned e = 0u;

    std::cout << a << std::setw(11) << -a << std::endl;
    std::cout << c << std::setw(11) << -c << std::endl;
    std::cout << e << std::setw(11) << -e << std::endl;
}

```

```codeBlockLines_e6Vv
2 4294967294
1 4294967295
0          0

```

The arithmetic negation of an operand of signed integer type or floating-point type is undefined if overflow occurs.

### Arithmetic Plus [​](https://advoop.sdds.ca/D-Processing/expressions\#arithmetic-plus "Direct link to heading")

The unary plus operator ( `+`) evaluates to its operand. The result is a prvalue of the same type as the operand after any promotions. The operator is present in the language for symmetry.

### Address of [​](https://advoop.sdds.ca/D-Processing/expressions\#address-of "Direct link to heading")

The address-of operator ( `&`) returns a pointer to its operand: the value is the address of the operand. The operand must be an lvalue that is not of storage class `register`. The expression is a prvalue.

We cannot take the address of a bit field and there are no pointers to bit fields of user-defined type.

### Indirection [​](https://advoop.sdds.ca/D-Processing/expressions\#indirection "Direct link to heading")

The indirection operator ( `*`) returns the value stored in the address that the operand contains. The expression is itself an lvalue.

The indirection and address-of operators are inverses of one another. The result of `*&x` is `x`.

```codeBlockLines_e6Vv
// Indirection
// indirection.cpp

#include <iostream>
#include <iomanip>

int main()
{
    int x = 3;
    int* p = &x;
    std::cout << x << std::setw(11) << p << std::endl;

    *&x = 4;
    std::cout << x << std::setw(11) << p << std::endl;
}

```

```codeBlockLines_e6Vv
3   002BF824
4   002BF824

```

### Cast [​](https://advoop.sdds.ca/D-Processing/expressions\#cast "Direct link to heading")

The type-cast operator consists of a type name followed by an operand and converts the operand to the specified type. The operand may not be the name of an array. The expression is a prvalue.

There are two styles of casting:

- C-style casts - enclose the target type within parentheses
- C++-function-style casts - enclose the operand within parentheses

We may C-style cast an operand of integral or floating-point type to an integral or floating-point type; an operand of pointer type to any other pointer type or any integral type; and an operand of integral type, generic pointer type, or non-generic pointer type to a pointer type.

We may function-style cast an operand of integral or floating-point type to an integral or floating-point type; and an operand of pointer type to any integral type.

### `alignof()` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#alignof-operator "Direct link to heading")

The `alignof()` operator returns the alignment requirement of its operand. The operand may be a type identifier representing the type of a complete object, or an array or a reference to one of those types. The operation returns an integral constant of type `std::size_t`.

For an example, see section entitled [Type Alignment](https://advoop.sdds.ca/B-Types/fundamental-types#type-alignment) in the Chapter [Fundamental Types](https://advoop.sdds.ca/B-Types/fundamental-types).

### `decltype()` Specifier [​](https://advoop.sdds.ca/D-Processing/expressions\#decltype-specifier "Direct link to heading")

The `decltype()` specifier evaluates to the type and value category of its argument. The operand may be an entity or an expression. The value category of the expression affects the type:

- if the value category of the expression is an xvalue, then the type is `T&&`
- if the value category of the expression is an lvalue, then the type is `T&`
- if the value category of the expression is a prvalue, then the type is `T`

```codeBlockLines_e6Vv
// decltype with expressions
// decltype_expre.cpp

#include <iostream>

int main()
{
    int i = 3, j = 6;
    double x = 4.5;
    double& r = x;

    decltype(i + j) y = i + j; // int y
    decltype(i + x) z = i + x; // double z
    decltype(r) s = r;         // double& s

    std::cout << y << std::endl;
    std::cout << z << std::endl;
    std::cout << s << std::endl;
}

```

```codeBlockLines_e6Vv
9
7.5
4.5

```

### `noexcept()` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#noexcept-operator "Direct link to heading")

The no exception operator ( `noexcept()`) returns true if the argument does not throw an exception. This compile-time function evaluates to a prvalue of type `bool`. This operator does not evaluate the argument passed to it. This operator returns `false` if the expression contains:

- a call to function that does not have a non-throwing exception specification ( `noexcept`), unless it is a constant expression
- a throw expression
- a `dynamic_cast` expression when the target type is a reference type and conversion needs a run-time check
- a `typeid` expression when the argument is a polymorphic type

A function with a `noexcept` specification in its declaration should be a non-throwing function. If a function marked `noexcept` allows an uncaught exception to escape at run-time, the program terminates immediately. For further details, see the section on [No Exceptions](https://advoop.sdds.ca/D-Processing/error-handling#noexcept) in the Chapter entitled [Error Handling](https://advoop.sdds.ca/D-Processing/error-handling).

### `throw` Operator [​](https://advoop.sdds.ca/D-Processing/expressions\#throw-operator "Direct link to heading")

The throw operator ( `throw`) identifies an exception to normal execution. The operator creates a temporary object from its operand and transfers control to the exception handler. The exception object is an lvalue of the type of the operand of the throw expression. This operand is analogous to an argument passed to a function and received in its parameter. For example,

```codeBlockLines_e6Vv
// Throw Operator
// throw.cpp

#include <iostream>

int divide(int x, int y)
{
    if (y == 0)
        throw "divide by zero inadmissible";
    else
        return x / y;
}

int main ()
{
    int dividend, divisor, quotient = 0;

    std::cout << "Enter dividend : ";
    std::cin >> dividend;
    std::cout << "Enter divisor  : ";
    std::cin >> divisor;

    //... execute function successfully or throw exception

    quotient = divide(dividend, divisor);

    // ... handle exception

    std::cout << "Quotient = " << quotient << std::endl;
}

```

For details on handling an exception that has been thrown see the section on [Exceptions](https://advoop.sdds.ca/D-Processing/error-handling#exceptions) in the Chapter entitled [Error Handling](https://advoop.sdds.ca/D-Processing/error-handling).

## Binary Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#binary-expressions "Direct link to heading")

Binary expressions consist of two operands and one operator. They include arithmetic, relative, logical, and bit-wise expressions. They evaluate to prvalues.

### Arithmetic [​](https://advoop.sdds.ca/D-Processing/expressions\#arithmetic "Direct link to heading")

#### Multiplicative [​](https://advoop.sdds.ca/D-Processing/expressions\#multiplicative "Direct link to heading")

A multiplicative expression evaluates the product, quotient, or remainder of its operands. The operator separates the operands. The operands are of integral or floating-point type for product and quotient operations ( `*` `/`). The operands for the remainder operation ( `%`) are of integral or unscoped enumeration type; the remainder operation ( `%`) is undefined for operands of floating-point type.

#### Addition [​](https://advoop.sdds.ca/D-Processing/expressions\#addition "Direct link to heading")

The addition operator ( `+`) adds the values of its operands. The operands may be of integral type, floating-point type, or non-generic pointer type. If one operand is of pointer type, the other must be of integral or unscoped enumeration type. For additions to an operand of pointer type see the section entitled [Expressions](https://advoop.sdds.ca/F-MemoryModel/raw-pointers#expressions) in the chapter [Raw Pointers](https://advoop.sdds.ca/F-MemoryModel/raw-pointers).

#### Subtraction [​](https://advoop.sdds.ca/D-Processing/expressions\#subtraction "Direct link to heading")

The subtraction operator ( `-`) subtracts the value of its second operand from the value of its first operand. The operands may be of integral type, floating-point type, or non-generic pointer type. If the left operand is of pointer type, the right operand must be of integral, unscoped enumeration or pointer type. For subtractions from an operand of pointer type see the section entitled [Expressions](https://advoop.sdds.ca/F-MemoryModel/raw-pointers#expressions) in the chapter [Raw Pointers](https://advoop.sdds.ca/F-MemoryModel/raw-pointers).

### Bit-Shifting [​](https://advoop.sdds.ca/D-Processing/expressions\#bit-shifting "Direct link to heading")

See the chapter entitled [Bit-Wise Expressions](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions) for the bit-shifting operators ( `<<` `>>`).

### Relational [​](https://advoop.sdds.ca/D-Processing/expressions\#relational "Direct link to heading")

A relational expression compares the values of two operands for relative magnitude, equality, or inequality. The operands are of arithmetic, enumeration, or pointer type. If one of the operands is of pointer type, then the other operand must be of compatible pointer type or the `nullptr` constant. A relational expression is of type `bool` and evaluates to either `true` or `false`.

#### Less-Than [​](https://advoop.sdds.ca/D-Processing/expressions\#less-than "Direct link to heading")

The less-than operators ( `<`, `<=`) compare the relative magnitude of their operands' values.

#### Greater-Than [​](https://advoop.sdds.ca/D-Processing/expressions\#greater-than "Direct link to heading")

The greater-than operators ( `>`, `>=`) compare the relative magnitude of their operands' values.

#### Equality [​](https://advoop.sdds.ca/D-Processing/expressions\#equality "Direct link to heading")

The equality operator ( `==`) compares the values of its operands for identity.

#### Inequality [​](https://advoop.sdds.ca/D-Processing/expressions\#inequality "Direct link to heading")

The inequality operator ( `!=`) compares the values of its operands for lack of identity.

If the right operand is zero-valued, we may omit it and the operator and thereby convert the left operand into a truth evaluation. That is, the expression in the first sample below evaluates to the same result as the expression on the second one:

```codeBlockLines_e6Vv
if (x != 0)
{
    // ...
}

```

```codeBlockLines_e6Vv
if (x)
{
    // ...
}

```

### Bit-Wise and [​](https://advoop.sdds.ca/D-Processing/expressions\#bit-wise-and "Direct link to heading")

See the chapter entitled [Bit-Wise Expressions](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions) for the bit-wise and operator ( `&`).

### Bit-Wise or [​](https://advoop.sdds.ca/D-Processing/expressions\#bit-wise-or "Direct link to heading")

See the chapter entitled [Bit-Wise Expressions](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions) for the bit-wise or operator ( `|`).

### Bit-Wise Exclusive or [​](https://advoop.sdds.ca/D-Processing/expressions\#bit-wise-exclusive-or "Direct link to heading")

See the chapter entitled [Bit-Wise Expressions](https://advoop.sdds.ca/H-Deeper-Detail/bit-wise-expressions) for the bit-wise exclusive or operator ( `^`).

### Logical [​](https://advoop.sdds.ca/D-Processing/expressions\#logical "Direct link to heading")

Binary logical expressions evaluate the combined truthfulness of their operands. The operands may be of integral type, floating-point type, or pointer type. The type of one operand may differ from the type of the other. Logical expressions evaluate to values of type `bool`: `false` or `true`.

#### Intersection and Union [​](https://advoop.sdds.ca/D-Processing/expressions\#intersection-and-union "Direct link to heading")

The logical 'and' operator ( `&&`) compares its operands and returns their intersection. The following rules apply:

- `true`, if both operands are `true`
- `false`, if either of the operands is `false`

The logical 'or' operator ( `||`) compares its operands and returns their union. The following rules apply:

- `true`, if either operand is `true`
- `false`, if both of the operands are `false`

#### Left to Right [​](https://advoop.sdds.ca/D-Processing/expressions\#left-to-right "Direct link to heading")

Logical expressions evaluate their operands left-to-right as necessary. In this respect, they differ from other binary expressions. If the left operand determines the result, the right operand is **not** evaluated. For instance, if the left operand is `false` and the operator is `&&`, the right operand is not evaluated. Similarly, if the left operand is true and operator is `||`, the right operand is not evaluated.

The following program does not increment either `j` or `i`:

```codeBlockLines_e6Vv
// Logical Expressions
// logical.cpp

#include <iostream>

int main()
{
    int i = 1, j = 1;

    std::cout << (i < 2 || j++ == 1) << ' ' << j << std::endl;
    std::cout << (j == 2 && i++ == 1) << ' ' << i << std::endl;
}

```

```codeBlockLines_e6Vv
1 1
0 1

```

#### Order Matters [​](https://advoop.sdds.ca/D-Processing/expressions\#order-matters "Direct link to heading")

Because logical expressions guarantee left to right evaluation, the order of their operands matters. Consider the expression

```codeBlockLines_e6Vv
int* a = nullptr;
if ( nullptr != a && 6 == a[i] ) // OK - Correct Order
    std::cout << "a[" << i << "] is " << a[i] << std::endl;
else
    std::cout << "Memory not allocated!" << std::endl;

```

This code will not crash since `a != nullptr`. However, if we switched the order of the two conditions, we would expose the possibility of a crash at the evaluation of `a[i]`:

```codeBlockLines_e6Vv
int* a = nullptr;
if ( 6 == a[i] && nullptr != a ) // ERROR - Wrong Order
    std::cout << "a[" << i << "] is " << a[i] << std::endl;
else
    std::cout << "Memory not allocated!" << std::endl;

```

### Assignment Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#assignment-expressions "Direct link to heading")

An assignment expression copies from the right operand to the left operand. The left operand must be a modifiable lvalue. Because assignment expressions associate from right to left, cascading is possible. The expressions may be simple or compound.

#### Simple Assignment [​](https://advoop.sdds.ca/D-Processing/expressions\#simple-assignment "Direct link to heading")

The simple assignment operator ( `=`) copies the value of the right operand without modification into the left operand. We can cascade the assignment to several variables of a single value:

```codeBlockLines_e6Vv
// Assignment Expressions
// assignment.cpp

#include <iostream>

int main()
{
    int i, j, k;

    i = j = k = 3;
    std::cout << i << ' ' << j << ' ' << k << std::endl;
}

```

```codeBlockLines_e6Vv
3 3 3

```

If we encapsulate an array in a class type, we can copy all of its elements in a simple assignment. For example,

```codeBlockLines_e6Vv
// Assignment Expressions
// copyArray.cpp

#include <iostream>

typedef struct
{
    int a[20];
} Array;

int main()
{
    Array original = {1, 2, 3, 4, 5}, copy;

    copy = original;

    for (int i = 0; i < 5; i++)
        std::cout << copy.a[i] << ' ';
    std::cout << std::endl;
}

```

```codeBlockLines_e6Vv
1 2 3 4 5

```

#### Compound Assignment [​](https://advoop.sdds.ca/D-Processing/expressions\#compound-assignment "Direct link to heading")

The compound operators ( `+=` `-=` `*=` `/=` `%=` `>>=` `<<=` `~=` `&=` `|=` `^=`) perform the operation specified by the first character in the operator on the two operands before copying the result into the left operand.

### Sequential Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#sequential-expressions "Direct link to heading")

The comma operator ( `,`) divides expressions for separate evaluation in sequence from the left. The operands may be expressions themselves and may be of any type. The type and value of the result of a sequential expression is that of its rightmost operand.

A common use of the comma operator is in definitions and iteration constructs

```codeBlockLines_e6Vv
void reverse(char *s)
{
    char t;

    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

```

### Mixed-Type Binary Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#mixed-type-binary-expressions "Direct link to heading")

The above descriptions apply to binary expressions on operands of compatible type. If the operands in the expression are not of the type defined for the operator, one of the operands must be converted to a compatible type. The compiler promotes operands types if necessary to evaluate a binary expression. It converts the operand of lower type to a higher type using the following hierarchy:

|  |  |
| --- | --- |
| `long double` | highest |
| `double` | ... |
| `float` | ... |
| `unsigned long long` | ... |
| `long long` | ... |
| `unsigned long` | ... |
| `long` | ... |
| `unsigned int` | ... |
| `int` | ... |
| `unsigned char` | ... |
| `char` | ... |
| `bool` | lowest |

If one pointer is of generic ( `void*`) type and the operation requires pointers of compatible type, the compiler converts the non-generic pointer to generic ( `void*`) type.

#### The Unsigned Trap [​](https://advoop.sdds.ca/D-Processing/expressions\#the-unsigned-trap "Direct link to heading")

If one of the operands is of `unsigned` integral type and the other is of a `signed` integral type, the compiler promotes the value of the `signed` type to a value of `unsigned` type. This particular promotion may produce a counter-intuitive result. For example,

```codeBlockLines_e6Vv
// Relational Expressions
// relational.cpp

#include <iostream>

int main()
{
    unsigned len = 0u;

    std::cout << (len > -1) << std::endl; // might expect true
                                          // evaluates to false
}

```

```codeBlockLines_e6Vv
0

```

The expression in parentheses has a value of `false` (0) because the compiler promoted -1 to the largest unsigned integer 4294967295u before evaluating the expression.

### Good Design Practice [​](https://advoop.sdds.ca/D-Processing/expressions\#good-design-practice "Direct link to heading")

#### Avoid Implicit Promotions [​](https://advoop.sdds.ca/D-Processing/expressions\#avoid-implicit-promotions "Direct link to heading")

Implicit promotions are not necessarily portable. Type promotions may vary across platforms. Hence, it is preferable to cast the operand of lower type explicitly.

#### Sub-Divide Complex Binary Expressions [​](https://advoop.sdds.ca/D-Processing/expressions\#sub-divide-complex-binary-expressions "Direct link to heading")

Complex binary expressions are not always portable. Consider

```codeBlockLines_e6Vv
int x = 3;
x = x + ++x;  // the result may be either 7 or 8

```

The order of evaluation of the operands in a binary expression is implementation dependent. To ensure identical results on all platforms, we subdivide complex binary expressions into multiple statements that clarify our intent:

```codeBlockLines_e6Vv
int x = 3;
++x;
x = x + x;  // increment first = 8

```

```codeBlockLines_e6Vv
int x = 3, y;
y = x;
++x;
x = y + x;  // add using the old value of x = 7

```

## Ternary Expression [​](https://advoop.sdds.ca/D-Processing/expressions\#ternary-expression "Direct link to heading")

The ternary expression is a conditional expression. The first operator ( `?`) identifies the expression as a selection construct; the second operator ( `:`) separates the choices.

The leftmost operand may be of integral type, floating-point or pointer type. If it evaluates to `true`, the expression evaluates the second operand, but not the third operand. If the leftmost operand evaluates to `false`, the expression evaluates the third operand, but not the second operand. The result is a value of the type of the evaluated operand.

The conditional expression provides a simple method of avoiding multiple returns:

```codeBlockLines_e6Vv
int sign(int x)
{
    return x < 0 ? -1 : 1;
}

```

If the second or third operands are not primary expressions, the compiler introduces run-time code to evaluate them based upon the truth value of the leftmost operand. Some compilers require that the second and third operands be of compatible type.

Since the conditional operator has low precedence, using it within another expression usually requires enclosure within parentheses.

- [Value Categories](https://advoop.sdds.ca/D-Processing/expressions#value-categories)
  - [lvalue Operands](https://advoop.sdds.ca/D-Processing/expressions#lvalue-operands)
- [Operator Precedence](https://advoop.sdds.ca/D-Processing/expressions#operator-precedence)
  - [Order of Evaluation](https://advoop.sdds.ca/D-Processing/expressions#order-of-evaluation)
- [Postfix Expressions](https://advoop.sdds.ca/D-Processing/expressions#postfix-expressions)
  - [Subscripting Operator](https://advoop.sdds.ca/D-Processing/expressions#subscripting-operator)
  - [Member Selection](https://advoop.sdds.ca/D-Processing/expressions#member-selection)
    - [Direct Selection](https://advoop.sdds.ca/D-Processing/expressions#direct-selection)
    - [Indirect Selection](https://advoop.sdds.ca/D-Processing/expressions#indirect-selection)
  - [Postfix Increment and Decrement](https://advoop.sdds.ca/D-Processing/expressions#postfix-increment-and-decrement)
    - [Results at Integer Limits](https://advoop.sdds.ca/D-Processing/expressions#results-at-integer-limits)
  - [`typeid()` Operator (optional for OOP345)](https://advoop.sdds.ca/D-Processing/expressions#typeid-operator-optional-for-oop345)
  - [Constrained Cast Operators](https://advoop.sdds.ca/D-Processing/expressions#constrained-cast-operators)
