# argparse

A modern, header-only C++ argument parser inspired by Python's `argparse`.

* ✅ Clean, chainable API
* ✅ Supports short/long flags, positional args, default values
* ✅ Fully tested with GoogleTest
* ✅ Designed using modern C++ (C++20/23)

---

## 🚀 Getting Started

```cpp
#include <argparse/argparse.h>

int main(int argc, char* argv[]) {
    ArgumentParser parser("myapp");

    parser.add_argument("-v", "--verbose")
          .store_true()
          .default_value(false);

    parser.add_argument("--count")
          .default_value(1)
          .action([](std::string_view val) {
              return std::stoi(std::string(val));
          });

    auto args = parser.parse(argc, argv);

    bool verbose = args.at("verbose").as<bool>();
    int count = args.at("count").as<int>();
}
```

---

## 🔧 Integration

### Using CMake + FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/mattiasgonday/argparse.git
  GIT_TAG main
)
FetchContent_MakeAvailable(argparse)

target_link_libraries(your_target PRIVATE argparse_lib)
```

### Using find_package after install

```bash
cmake --install build --prefix ~/.local
```

Then in your external CMake project:

```cmake
find_package(argparse REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE argparse::argparse_lib)
```

And in code:

```cpp
#include <argparse/argparse.h>
```

---

## 📋 Features

| Feature                      | Supported    |
| ---------------------------- | ------------ |
| Short & long flags           | ✅            |
| Positional arguments         | ✅            |
| Default values               | ✅            |
| Store true flags             | ✅            |
| `--key=value` syntax         | ✅            |
| Grouped short flags `-abc`   | ✅            |
| `nargs=*`, `+`, or exact `N` | ✅            |
| Multiple names per argument  | ✅            |
| Help text generation         | ✅            |
| Canonical name resolution    | ✅            |
| Subparsers                   | ⬜️ (planned) |
| Mutually exclusive groups    | ⬜️ (planned) |
| Argument groups              | ⬜️ (planned) |

---

## 🧪 Tests

Built and tested using [GoogleTest](https://github.com/google/googletest):

```bash
cmake -S . -B build -DENABLE_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

---

## 📄 License

Licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

## 🤝 Contributing

Pull requests are welcome. Please write tests for new features and follow the existing code style.

To test locally:

```bash
cmake -S . -B build -DENABLE_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

