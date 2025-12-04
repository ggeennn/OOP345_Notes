Photo ID (required)
Scrap paper and pen/pencil You are allowed one sheet of scrap paper for rough work and walk-throughs.

## Structure of the Final Assessment
- Part 1: Concept and Debugging – ~20 minutes
- Part 2: Programming – ~70 to 80 minutes (depending on when you submit Part 1)
These two parts are delivered as two separate Blackboard tests:

For Part 1, you are allowed one sheet of scrap paper (with your name and student number printed in font size 24 on both sides) and a pen/pencil.
When you finish Part 1, you will:
- Submit Part 1 on Blackboard.
- Hand in your scrap paper.
- Receive the code needed to start the programming test (Part 2).
The programming test (Part 2) ends at the end of the lab period. You will have at least 70 minutes, and possibly more, depending on how early you submit Part 1.

## Concept / Debugging questions
Focus on the following areas but may include any topic covered throughout the semester:

- Multithreading (threads, joining, mutex, deadlock, race conditions, etc.)
- Preprocessor directives
- STL containers and algorithms
- Wrappers
- Binary files and random access
- Pointers and pointer arithmetic
- Smart pointers
- Named casts (`static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`)

## Programming:
Below is an outline of what each programming question on the final assessment is about, and what you should review to be ready.

(The exact wording of the questions will be different on the test.)

### Question 1 – Validated Smart Pointer (class template & ownership)
**What it’s about:**
Writing a class template `Pointer<T, Validator>` that owns a dynamically allocated object (`T*`).
Using a callable validator (functor / lambda) to decide whether a dynamically allocated object is “valid” and should be kept or deleted.
**Implementing:**
- A constructor
- A destructor
- A setter that takes ownership of a `T*`
- Accessor methods (const and non-const versions).
- A move process that transfers ownership. (either assignment or construction)
- Disabling moving or copying
**What to study:**
- Class templates: `template<typename T, typename Validator>`.
- Raw dynamic memory: single-object `new`/`delete` and ownership.
- RAII basics: destructor responsibility, avoiding leaks and double delete.
- Functors and callables (objects with `operator()` and simple lambdas).
- Move semantics (move constructor) and deleting copy operations.
- Basic pointer checks (`nullptr`) and simple resource management patterns.

### Question 2 – Chunk Processing Functor (functor, vectors, ranges)
**What it’s about:**
A functor class that:
- Stores a const vector smart pointers created in question one & and a `[begin, end)` index range.
- In `operator()`, from `m_begin` to `m_end`, checks each smart pointer for validity, and collects the underlying `int` values into a vector of the underlaying type
- Returns that vector.
**What to study:**
- Type aliases: `using NewDataType = SomeTemplate<whatever, whatever>;`.
- Class design with member initialiser lists for references and indices.
- `std::vector`: indexing with `size_t`, `push_back`, `size()`.
- Writing and using a functor with `operator()()` that returns a value.
- Checking pointers for validity and dereferencing them safely.

### Question 3 – Parallel Filtering with `std::async` (futures & concurrency)
**What it’s about:**
Splitting a large `vector<DataPtr>` into chunks based on the number of hardware threads.
For each chunk:
- Creating a `ChunkFilter` object for a `[start, end)` range.
- Launching it with `std::async(std::launch::async, ...)`.
- Storing the returned `std::future` of vectors of underlying smart pointer types in a vector of futures.
After launching all tasks:
- Calling `.get()` on each future.
- Appending all returned `vector<int>` values into a single `vector<int> allValid`.
**What to study:**
- `std::async` and `std::launch::async`.
- `std::future` and `.get()`.
- Find number of available threads and using it to choose the number of tasks.
- Dividing work over a range `[0, size)` into roughly equal chunks.
- Basic use of vectors of `std::futures` of vectors of underlying smart pointer types (or equivalent).
- Avoiding data races by only reading shared data and returning results by value.

### Question 4 – Parallel Algorithms & File Output (algorithms, execution policies, binary file I/O)
**What it’s about:**
Using standard algorithms with execution policies on a vectors of underlying smart pointer types:
- `std::copy_if` with an execution policy (from `<execution>`) to copy only valid smart pointers (of question 1) elements into another vector of smart pointer (only valid ones).
- Opening a binary output file
- Using `std::for_each` with an execution policy to write the underlying `int` values (of outcome of `copy_if` algo.) to the file in binary form.
**What to study:**
- `<algorithm>`: `std::copy_if`, `std::for_each`.
- `<execution>` policies: `std::execution::seq`, `par`, `par_unseq` and when they are safe to use.
- Lambdas used with algorithms (capturing containers / streams by reference).
- Basic binary file I/O with `std::ofstream`:
  - Opening with `ios::binary`.
  - Using `.write(reinterpret_cast<const char*>(&value), sizeof(value));`.
  - Using an accessors (like `get()` and etc...) to obtain the raw pointers from the smart pointer (in question one)
- Ensuring operations are thread-safe with chosen execution policies when accessing shared read-only data and a single output stream (based on how it’s used in the question and as taught in class).

If you understand and can code these ideas, you will be in a good position for the final assessment.
