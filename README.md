# cpp_vector

_This project has a [TODO](TODO.md)_

Limited implementation of std::vector. No allocator used!

+ C++17
+ `<gtest/gtest.h>` used for testing

## Makefile targets
+ `all` and `test` run tests
+ `style` formats code with `clang-format` tool
+ `clean` deletes all files that could be produced by other targets (only `test` binary in this case)

## Project Description

This is a part of the bigger project meant to implement the partial behaviour of C++ container classes. I wrote vector and array ([will be present in repository at some point](TODO.md)), it took me about a week to understand, implement and debug everything.

### std::vector

[Here](https://en.cppreference.com/w/cpp/container/vector) is the best documentation on the original container. To put it shortly:
+ std::vector is a container that encapsulates dynamic size arrays
+ The elements in vector are stored contiguously
+ vector can expand its storage automatically if needed, there are methods to expand and return extra memory to the system manually

### Fields, types and methods implemented

Member types impemented:
| Member type       | Definition    |
|-------------------|---------------|
|`value_type`       |`T`            |
|`reference`        |`T &`          |
|`const_reference`  |`const T&`     |
|`iterator`         |`T *`          |
|`const_iterator`   |`const T *`    |
|`size_type`        |`size_t`       |

Private fields implemented:
|Field      |Type       |Description           |
|-----------|-----------|----------------------|
|`values`   |`T*`       |Actual value storage  |
|`size`     |`size_type`|vector size: how many elements are here right now?|
|`capacity` |`size_type`|vector capacity: how many elements can possibly be put there without reallocating memory?|

Methods implemented:
|Method     |Description    |
|-----------|---------------|
|`vector() noexcept`|Default constructor. Creates empty (`capacity = size = 0`) vector|
|`vector(size_type n)`|Parametrized constructor. Creates vector with `capacity = size = 0`|
|`vector(std::initializer_list<value_type> const &items)`|Parametrized constructor. Creates vector with the contents of `initializer_list`|
|`vector(const vector &v)`|Copy constructor. Creates new vector with the copy of contents of `v`|
|`vector(vector &&v) noexcept`|Move constructor. Uses move semantics to construct vector with the contents of `v`|
