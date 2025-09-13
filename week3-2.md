# OOP345_Week3_InheritanceAndPolymorphism.md

## 1. 文档基本规范 (Basic Document Standards) 📑
### 1.1 文件命名规则 (File Naming Convention)
`OOP345_Week3_InheritanceAndPolymorphism.md`

### 1.2 基本文档结构 (Basic Document Structure)
1. 标题和概述 (Title and Overview)
2. 学习路径图 (Learning Path)
3. 目录 (Table of Contents)
4. 知识点详解 (Detailed Content)
5. FAQ (常见问题)
6. 实践示例 (Practice Examples)
7. 学习建议 (Study Tips)

## 2. 内容格式规范 📝

### 2.1 知识点详解 (Detailed Content)

### 继承与包含多态 (Inheritance and Inclusion Polymorphism | 继承与包含多态) 🟢 基础概念
- 定义 | Definition
  - 中文解释：面向对象程序中的类之间存在各种关系。继承是其中最紧密的关系，类之间高度耦合，并构成一个支持抽象和多态的层次结构。派生类包含其父基类的整个结构，并只定义那些专门化基类的额外特性。
  - 英文解释：The classes in an object-oriented program stand in a variety of relationships to one another. These relationships exhibit various degrees of coupling. Inheritance is the tightest possible relationship. The classes are highly coupled and part of a hierarchy that supports both abstraction and polymorphism. A derived class in an inheritance hierarchy includes the entire structure of its parent base class and defines only those additional features that specialize the base class.
- 示例 | Example
  - 实际应用场景：`Shape` 基类派生出 `Cube` 和 `Sphere`，它们都继承了 `Shape` 的基本结构，并添加了各自特有的属性和行为。
- 💡实践提示 | Practice Tips
  - 继承促进代码复用，简化开发过程，并逐步提高可替换性。

### 抽象基类 (Abstract Base Class | Abstract Base Class) 🟢 基础概念
- 定义 | Definition
  - 中文解释：抽象类可以作为继承层次结构的接口。它是一个不完整的类，不能创建其实例。通过派生一个新类并添加缺失的定义来完成其实现。
  - 英文解释：An _abstract_ class can serve as an interface to an inheritance hierarchy. It is an incomplete class in the hierarchy. We cannot create an instance of an abstract class. We complete its implementation by deriving a new class that adds the missing definitions.
- 示例 | Example
  - 实际应用场景：`Shape` 类被定义为一个抽象基类，它声明了一个纯虚函数 `volume()`，但没有提供实现。
    ```cpp
    // A Shape
    // Shape.h
    #ifndef SHAPE_H
    #define SHAPE_H

    class Shape
    {
    public:
        virtual double volume() const = 0; // 纯虚函数
    };
    #endif
    ```
- 💡实践提示 | Practice Tips
  - 抽象基类通过纯虚函数定义了层次结构向客户端暴露的接口，并保证提供该功能。

### 具体类 (Concrete Class | Concrete Class) 🟢 基础概念
- 定义 | Definition
  - 中文解释：从抽象类派生并实现了所有纯虚函数的类。可以创建其实例。
  - 英文解释：We call the completed class a _concrete_ class.
- 示例 | Example
  - 实际应用场景：`Cube` 和 `Sphere` 类从 `Shape` 抽象类派生，并各自实现了 `volume()` 函数，因此它们是具体类。
    ```cpp
    // A Cube
    // Cube.h
    #include "Shape.h"
    class Cube : public Shape
    {
        double len;
    public:
        Cube(double);
        double volume() const; // 实现虚函数
    };
    ```
- 💡实践提示 | Practice Tips
  - 只有具体类才能被实例化。

### 预处理器宏 (Pre-processor Guard | Pre-processor Guard) 🟢 基础概念
- 定义 | Definition
  - 中文解释：`#ifndef` ... `#endif` 结构确保类定义在一个翻译单元中只出现一次。
  - 英文解释：The pre-processor guard ( `#ifndef` ... `#endif`) ensures that the definition of the `Shape` class occurs only once in a translation unit.
- 示例 | Example
  - 实际应用场景：`Shape.h` 文件中的 `#ifndef SHAPE_H` 和 `#define SHAPE_H`。
- 💡实践提示 | Practice Tips
  - 这是 C++ 中实现“一次定义规则”的常见设计实践。

### 纯虚函数 (Pure Virtual Function | Pure Virtual Function) 🟢 基础概念
- 定义 | Definition
  - 中文解释：在基类中声明但没有实现的虚函数，通过 `= 0` 标识。它强制派生类提供自己的实现。
  - 英文解释：The assignment to 0 identifies the function as undefined or _pure_.
- 示例 | Example
  - 实际应用场景：`virtual double volume() const = 0;`
- 💡实践提示 | Practice Tips
  - 包含纯虚函数的类是抽象类，不能直接实例化。

### 包含多态 (Inclusion Polymorphism | Inclusion Polymorphism) 🟡 中级概念
- 定义 | Definition
  - 中文解释：通过类型特定的虚函数区分层次结构中不同类的功能。允许使用基类指针或引用操作派生类对象。
  - 英文解释：Inclusion polymorphism, which distinguishes the functionality of different classes in a hierarchy through type-specific virtual functions.
- 示例 | Example
  - 实际应用场景：`displayVolume(const Shape* shape)` 函数可以接收 `Cube` 或 `Sphere` 对象的地址，并调用其对应的 `volume()` 实现。
    ```cpp
    void displayVolume(const Shape* shape)
    {
        if (shape)
            std::cout << shape->volume() << std::endl; // 动态绑定
        else
            std::cerr << "ERROR!" << std::endl;
    }
    ```
- 💡实践提示 | Practice Tips
  - C++ 在运行时提供对象的动态类型，以确定调用哪个虚函数定义。

### 多态对象 (Polymorphic Object | Polymorphic Object) 🟡 中级概念
- 定义 | Definition
  - 中文解释：在其生命周期中可以具有不同动态类型的对象。
  - 英文解释：A polymorphic object is an object that can have different dynamic types throughout its lifetime.
- 示例 | Example
  - 实际应用场景：`Shape* shape = select();` 中 `shape` 指针可以指向 `Cube` 或 `Sphere` 对象。
- 💡实践提示 | Practice Tips
  - 动态类型识别对于复制多态对象、为动态类型专门化操作以及从默认选择中排除特定类型至关重要。

### 动态绑定 (Dynamic Binding | Dynamic Binding) 🟡 中级概念
- 定义 | Definition
  - 中文解释：在程序运行时根据对象的实际类型来决定调用哪个函数实现。仅适用于虚函数。
  - 英文解释：C++ supplies the dynamic type to the function at run-time.
- 示例 | Example
  - 实际应用场景：在 `displayVolume` 函数中，`shape->volume()` 会根据 `shape` 实际指向 `Cube` 还是 `Sphere` 来调用对应的 `volume()` 方法。
    ```cpp
    // 基类 - 含虚函数
    class Animal {
    public:
        virtual void speak() const { // 关键：虚函数
            std::cout << "Animal sound!" << std::endl;
        }
    };

    // 派生类
    class Dog : public Animal {
    public:
        void speak() const override { // 重写虚函数
            std::cout << "Woof! Woof!" << std::endl;
        }
    };

    // 全局函数 - 实现动态绑定
    void makeSound(const Animal& animal) { // 1. 基类引用参数
        animal.speak(); // 2. 调用虚函数 → 动态绑定
    }

    int main() {
        Dog dog;
        makeSound(dog); // 输出 "Woof! Woof!"
        
        Animal animal;
        makeSound(animal); // 输出 "Animal sound!"
    }
    ```
- 💡实践提示 | Practice Tips
  - 全局函数本身不具备多态性，但可以通过接受基类指针/引用参数并调用虚函数来实现动态绑定行为。

### 静态绑定 (Static Binding | Static Binding) 🟢 基础概念
- 定义 | Definition
  - 中文解释：在程序编译时根据变量的声明类型来决定调用哪个函数或访问哪个成员。
  - 英文解释：( `Shape` is the static type.)
- 示例 | Example
  - 实际应用场景：
    ```cpp
    class Shape {
    public:
        // ...
    };

    class Cube : public Shape {
    public:
        double len = 10.0; // 特有成员
        // ...
    };

    int main() {
        Cube cube;
        Shape& s = cube;
        // std::cout << s.len << std::endl; // 错误：'Shape'没有'len'
        // 编译器在编译时发现Shape类没有len成员，因此报错。
    }
    ```
- 💡实践提示 | Practice Tips
  - 成员变量的访问总是静态绑定的，完全基于静态类型（编译时确定）。

### 克隆操作 (Copying Operations / Cloning | 克隆操作) 🟡 中级概念
- 定义 | Definition
  - 中文解释：在运行时复制多态对象需要知道其动态类型。通过引入 `clone()` 虚函数，可以创建对象的副本，并确保使用其动态类型进行内存分配和复制。
  - 英文解释：Copying a polymorphic object at run-time requires knowledge of its dynamic type. To determine the dynamic type at run-time we introduce a cloning member function to the hierarchy.
- 示例 | Example
  - 实际应用场景：在 `Shape` 接口中添加 `virtual Shape* clone() const = 0;`，并在 `Cube` 和 `Sphere` 中实现。
    ```cpp
    // Polymorphic Objects - Cloning
    // Shape.h
    #ifndef SHAPE_H
    #define SHAPE_H

    class Shape
    {
    public:
        virtual double volume() const = 0;
        virtual Shape* clone()  const = 0; // 克隆虚函数
    };
    #endif
    ```
    ```cpp
    // Polymorphic Objects - Cloning
    // Cube.cpp
    #include "Cube.h"
    Cube::Cube(double l) : len(l) {}
    Shape* Cube::clone() const
    {
        return new Cube(*this); // 调用Cube的拷贝构造函数
    }
    ```
- 💡实践提示 | Practice Tips
  - `clone()` 函数返回一个指向新创建的、与原对象动态类型相同的对象的指针。

### 动态类型转换 (Dynamic Cast | 动态类型转换) 🔴 高级概念
- 定义 | Definition
  - 中文解释：`dynamic_cast` 运算符用于在运行时安全地将基类指针或引用转换为派生类指针或引用。如果转换不安全（即对象不是目标类型），则返回 `nullptr`（对于指针）或抛出 `std::bad_cast` 异常（对于引用）。
  - 英文解释：In expressions that involve operands of polymorphic type, the operator functions require knowledge of the received object's dynamic type. A _dynamic cast_ returns this type.
- 示例 | Example
  - 实际应用场景：在 `Cube::operator==` 中，将 `Shape&` 参数转换为 `Cube*` 以访问 `Cube` 特有的成员 `len`。
    ```cpp
    bool Cube::operator==(const Shape& s) const
    {
        const Cube* c = dynamic_cast<const Cube*>(&s); // 动态转换
        return c ? len == c->len : false;
    }
    ```
- 💡实践提示 | Practice Tips
  - `dynamic_cast` 只能用于多态类（至少包含一个虚函数）的指针或引用。
  - 它可以实现对动态类型专门化操作。

### 运行时类型识别 (Run-Time Type Information, RTTI | 运行时类型识别) 🔴 高级概念
- 定义 | Definition
  - 中文解释：C++ 语言提供的机制，允许在程序运行时查询对象的类型信息。主要通过 `dynamic_cast` 和 `typeid` 运算符实现。
  - 英文解释：The C++ language includes two elements that hold run-time information in addition to `dynamic_cast` for identifying a polymorphic object's dynamic type.
- 示例 | Example
  - 实际应用场景：`typeid()` 运算符返回一个 `std::type_info` 对象，可以用于比较对象的类型。
    ```cpp
    #include <typeinfo> // for typeid
    // ...
    void show(const A* a)
    {
        C cref;
        if (typeid(*a) != typeid(cref)) // 比较动态类型
        {
            a->display();
        }
        else
            std::cout << typeid(cref).name() << " objects are private" << std::endl;
    }
    ```
- 💡实践提示 | Practice Tips
  - `typeid(*a).name()` 返回一个 C 风格字符串，描述类型名称，具体描述依赖于实现。

### 里氏替换原则 (Liskov Substitution Principle, LSP | 里氏替换原则) ⭐ 重点掌握
- 定义 | Definition
  - 中文解释：如果 S 是 T 的子类型，那么在程序中，所有 T 类型的对象都可以被 S 类型的对象替换，而不会改变程序的正确性。通俗地说，子类必须能够完全替代父类，而不破坏程序的正确性。
  - 英文解释："a function that uses pointers or references to base classes must be able to use objects of derived classes without knowing it". In other words, we should model our classes on their behaviors not their properties and model our data based on properties and not on behaviors.
- 示例 | Example
  - **违反 LSP 的反例**：正方形继承矩形。
    ```cpp
    class Rectangle { // 基类：矩形
    public:
        virtual void setWidth(int w) { width = w; }
        virtual void setHeight(int h) { height = h; }
        virtual int area() const { return width * height; }
    protected:
        int width = 0;
        int height = 0;
    };

    class Square : public Rectangle { // 派生类：正方形 - 违反LSP！
    public:
        void setWidth(int w) override { 
            width = height = w; // 同时修改高度，破坏父类行为约定
        }
        void setHeight(int h) override {
            width = height = h; // 同时修改宽度，破坏父类行为约定
        }
    };

    void testRectangle(Rectangle& r) {
        r.setWidth(5);
        r.setHeight(4);
        // 期望面积: 20, 实际: 传入正方形时输出 25 而不是 20！
    }
    ```
  - **符合 LSP 的设计**：矩形和正方形都继承自一个更通用的 `Shape` 接口，各自独立实现。
    ```cpp
    class Shape { // 形状
    public:
        virtual int area() const = 0;
        virtual ~Shape() = default;
    };

    class Rectangle : public Shape { // 矩形
    public:
        void setWidth(int w) { width = w; }
        void setHeight(int h) { height = h; }
        int area() const override { return width * height; }
    private:
        int width, height;
    };

    class Square : public Shape { // 正方形
    public:
        void setSide(int s) { side = s; }
        int area() const override { return side * side; }
    private:
        int side;
    };
    ```
- 💡实践提示 | Practice Tips
  - **LSP 三大铁律**：
    1. **别改父类行为**：子类方法不能改变父类原有功能。
    2. **别加额外限制**：子类不能要求比父类更严格的参数。
    3. **别减少输出保证**：子类返回值/异常不能比父类更宽松。
  - 设计类时应关注其行为而非属性，数据建模应基于属性而非行为。

## 3. 目录 (Table of Contents)
- 继承与包含多态 (Inheritance and Inclusion Polymorphism)
- 抽象基类 (Abstract Base Class)
- 具体类 (Concrete Class)
- 预处理器宏 (Pre-processor Guard)
- 纯虚函数 (Pure Virtual Function)
- 包含多态 (Inclusion Polymorphism)
- 多态对象 (Polymorphic Object)
- 动态绑定 (Dynamic Binding)
- 静态绑定 (Static Binding)
- 克隆操作 (Copying Operations / Cloning)
- 动态类型转换 (Dynamic Cast)
- 运行时类型识别 (Run-Time Type Information, RTTI)
- 里氏替换原则 (Liskov Substitution Principle, LSP)

## 4. FAQ (常见问题)
### Q1: 为什么全局函数可以做到动态绑定？
- **A1**: 全局函数本身不具备多态性，但可以通过**操作多态对象**（即接受基类指针/引用参数）并**调用虚函数**来实现动态绑定行为。动态绑定是虚函数的特性，与函数作用域无关。

### Q2: 为什么抽象类中的成员函数无法执行 `return len == s.len;`？
- **A2**: 抽象类不能实例化对象。要执行 `Cube::operator==` 这样的成员函数，必须先有一个 `Cube` 对象来调用它。由于抽象类禁止实例化，所以永远不会有 `Cube` 对象存在，其成员函数也就永远没有执行上下文，函数体内的代码自然无法执行。

### Q3: 父类是正方形，子类是矩形，这种继承关系是否符合里氏替换原则？
- **A3**: 不符合。这种设计违反了里氏替换原则。正方形的 `setWidth` 和 `setHeight` 方法会强制宽高相等，而矩形的 `setWidth` 和 `setHeight` 方法是独立改变宽高的。如果一个函数期望接收一个正方形对象，但实际传入了一个矩形对象，矩形的行为会破坏正方形的预期行为（例如，设置宽度后高度不随之改变），从而导致程序逻辑错误。正确的做法是让它们都继承自一个更通用的 `Shape` 接口，各自独立实现。

## 5. 实践示例 (Practice Examples)
### 示例1: Shape 层次结构与多态
```cpp
// Shape.h
#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

class Shape
{
public:
    virtual double volume() const = 0;
    virtual ~Shape() = default; // 虚析构函数，防止内存泄漏
};
#endif

// Cube.h
#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"

class Cube : public Shape
{
    double len;
public:
    Cube(double l) : len{l} {}
    double volume() const override;
};
#endif

// Sphere.h
#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"

class Sphere : public Shape
{
    double rad;
public:
    Sphere(double r) : rad{r} {}
    double volume() const override;
};
#endif

// Cube.cpp
#include "Cube.h"
double Cube::volume() const
{
    return len * len * len;
}

// Sphere.cpp
#include "Sphere.h"
double Sphere::volume() const
{
    return 4.18879 * rad * rad * rad; // 近似值
}

// main.cpp
#include <iostream>
#include <memory> // For std::unique_ptr
#include "Cube.h"
#include "Sphere.h"

void displayVolume(const Shape* shape)
{
    if (shape)
        std::cout << "Volume: " << shape->volume() << std::endl;
    else
        std::cerr << "ERROR: Invalid shape!" << std::endl;
}

std::unique_ptr<Shape> selectShape()
{
    double x;
    char c;
    std::cout << "s (sphere), c (cube) : ";
    std::cin >> c;
    if (c == 's')
    {
        std::cout << "dimension (radius) : ";
        std::cin >> x;
        return std::make_unique<Sphere>(x);
    }
    else if (c == 'c')
    {
        std::cout << "dimension (length) : ";
        std::cin >> x;
        return std::make_unique<Cube>(x);
    }
    else
    {
        std::cerr << "Invalid selection." << std::endl;
        return nullptr;
    }
}

int main()
{
    std::unique_ptr<Shape> shape = selectShape();
    displayVolume(shape.get()); // 使用get()获取原始指针
    // unique_ptr会自动管理内存，无需手动delete
}
```
**预期输出 (Example Output):**
```
s (sphere), c (cube) : s
dimension (radius) : 1
Volume: 4.18879
```
```
s (sphere), c (cube) : c
dimension (length) : 2
Volume: 8
```

### 示例2: 多态对象的克隆
```cpp
// Shape.h (更新)
#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

class Shape
{
public:
    virtual double volume() const = 0;
    virtual Shape* clone() const = 0; // 添加克隆虚函数
    virtual ~Shape() = default;
};
#endif

// Cube.h (更新)
#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"

class Cube : public Shape
{
    double len;
public:
    Cube(double l) : len{l} {}
    Cube(const Cube& other) : len(other.len) {} // 拷贝构造函数
    double volume() const override;
    Shape* clone() const override; // 实现克隆
};
#endif

// Sphere.h (更新)
#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"

class Sphere : public Shape
{
    double rad;
public:
    Sphere(double r) : rad{r} {}
    Sphere(const Sphere& other) : rad(other.rad) {} // 拷贝构造函数
    double volume() const override;
    Shape* clone() const override; // 实现克隆
};
#endif

// Cube.cpp (更新)
#include "Cube.h"
double Cube::volume() const
{
    return len * len * len;
}
Shape* Cube::clone() const
{
    return new Cube(*this); // 调用Cube的拷贝构造函数
}

// Sphere.cpp (更新)
#include "Sphere.h"
double Sphere::volume() const
{
    return 4.18879 * rad * rad * rad;
}
Shape* Sphere::clone() const
{
    return new Sphere(*this); // 调用Sphere的拷贝构造函数
}

// cloning_main.cpp
#include <iostream>
#include <memory>
#include "Cube.h"
#include "Sphere.h"

void displayVolume(const Shape* shape)
{
    if (shape)
        std::cout << "Volume: " << shape->volume() << std::endl;
    else
        std::cerr << "ERROR: Invalid shape!" << std::endl;
}

std::unique_ptr<Shape> selectShape()
{
    double x;
    char c;
    std::cout << "s (sphere), c (cube) : ";
    std::cin >> c;
    if (c == 's')
    {
        std::cout << "dimension (radius) : ";
        std::cin >> x;
        return std::make_unique<Sphere>(x);
    }
    else if (c == 'c')
    {
        std::cout << "dimension (length) : ";
        std::cin >> x;
        return std::make_unique<Cube>(x);
    }
    else
    {
        std::cerr << "Invalid selection." << std::endl;
        return nullptr;
    }
}

int main()
{
    std::unique_ptr<Shape> originalShape = selectShape();
    if (originalShape) {
        std::unique_ptr<Shape> clonedShape(originalShape->clone()); // 使用clone()创建副本
        
        std::cout << "Original Shape ";
        displayVolume(originalShape.get());
        std::cout << "Cloned Shape ";
        displayVolume(clonedShape.get());
    }
}
```
**预期输出 (Example Output):**
```
s (sphere), c (cube) : s
dimension (radius) : 1
Original Shape Volume: 4.18879
Cloned Shape Volume: 4.18879
```

## 6. 学习建议 (Study Tips)
1. **理解虚函数**：虚函数是实现多态的基础，务必理解其工作原理和虚函数表的作用。
2. **区分静态与动态绑定**：明确成员变量访问和非虚函数调用是静态绑定，虚函数调用是动态绑定。
3. **掌握抽象类**：理解抽象类的作用（定义接口）、纯虚函数的意义以及为什么抽象类不能实例化。
4. **LSP 是设计原则**：里氏替换原则是指导良好面向对象设计的关键，通过实践反例和正例来加深理解。
5. **多态的应用场景**：思考多态在实际编程中如何简化代码、提高可扩展性和灵活性。

## 7. 文档维护规范 (Document Maintenance Standards) 🔄
更新日期：2025-09-13
版本号：v1.0
更新内容：
- 整理了关于继承、多态、抽象类、虚函数、静态/动态绑定、LSP等知识点。
- 补充了详细的中文解释、英文原文、代码示例和图解。
- 增加了常见问题 (FAQ) 部分，解答了对话中提出的疑问。
- 提供了实践示例，展示了多态和克隆的应用。
