//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: no-threads
// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

// checks that CTAD works properly with explicit object parameter

#include <future>
#include <type_traits>

template <bool Noexcept>
struct Callable {
  int operator()(this Callable, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{Callable<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{Callable<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableC {
  int operator()(this const CallableC, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableC<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableC<false>{}}), std::packaged_task<int(char*)>>);

// volatile-qualified parameter is deprecated.
// template <bool Noexcept>
// struct CallableV {
//   int operator()(this volatile CallableV, char*) noexcept(Noexcept);
// };
// static_assert(std::is_same_v<decltype(std::packaged_task{CallableV<true>{}}), std::packaged_task<int(char*)>>);
// static_assert(std::is_same_v<decltype(std::packaged_task{CallableV<false>{}}), std::packaged_task<int(char*)>>);

// volatile-qualified parameter is deprecated.
// template <bool Noexcept>
// struct CallableCV {
//   int operator()(this const volatile CallableCV, char*) noexcept(Noexcept);
// };
// static_assert(std::is_same_v<decltype(std::packaged_task{CallableCV<true>{}}), std::packaged_task<int(char*)>>);
// static_assert(std::is_same_v<decltype(std::packaged_task{CallableCV<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableL {
  int operator()(this CallableL&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableL<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableL<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableCL {
  int operator()(this const CallableCL&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCL<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCL<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableVL {
  int operator()(this volatile CallableVL&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableVL<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableVL<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableCVL {
  int operator()(this const volatile CallableCVL&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCVL<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCVL<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableR {
  int operator()(this CallableR&&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableR<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableR<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableCR {
  int operator()(this const CallableCR&&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCR<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCR<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableVR {
  int operator()(this volatile CallableVR&&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableVR<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableVR<false>{}}), std::packaged_task<int(char*)>>);

template <bool Noexcept>
struct CallableCVR {
  int operator()(this const volatile CallableCVR&&, char*) noexcept(Noexcept);
};
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCVR<true>{}}), std::packaged_task<int(char*)>>);
static_assert(std::is_same_v<decltype(std::packaged_task{CallableCVR<false>{}}), std::packaged_task<int(char*)>>);
