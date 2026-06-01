//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <functional>

// template<class F>
// function(F) -> function<see-below>;

// UNSUPPORTED: c++03, c++11, c++14

#include <cstddef>
#include <functional>
#include <utility>

#include "test_macros.h"

struct R { };
struct A1 { };
struct A2 { };
struct A3 { };

#define DECLARE_FUNCTIONS_WITH_QUALS(N, ...)                              \
  struct f0_##N  { R operator()() __VA_ARGS__           { return {}; } }; \
  struct f1_##N  { R operator()(A1) __VA_ARGS__         { return {}; } }; \
  struct f2_##N  { R operator()(A1, A2) __VA_ARGS__     { return {}; } }; \
  struct f3_##N  { R operator()(A1, A2, A3) __VA_ARGS__ { return {}; } }  \
/**/

#if TEST_STD_VER >= 23
#define DECLARE_THIS_FUNCTIONS_WITH_QUALS(N, ...)                                    \
  struct sf0_##N  { R operator()(this sf0_##N __VA_ARGS__)             { return {}; } }; \
  struct sf1_##N  { R operator()(this sf1_##N __VA_ARGS__, A1)         { return {}; } }; \
  struct sf2_##N  { R operator()(this sf2_##N __VA_ARGS__, A1, A2)     { return {}; } }; \
  struct sf3_##N  { R operator()(this sf3_##N __VA_ARGS__, A1, A2, A3) { return {}; } };  \
  struct sfne0_##N  { R operator()(this sfne0_##N __VA_ARGS__)             noexcept { return {}; } }; \
  struct sfne1_##N  { R operator()(this sfne1_##N __VA_ARGS__, A1)         noexcept { return {}; } }; \
  struct sfne2_##N  { R operator()(this sfne2_##N __VA_ARGS__, A1, A2)     noexcept { return {}; } }; \
  struct sfne3_##N  { R operator()(this sfne3_##N __VA_ARGS__, A1, A2, A3) noexcept { return {}; } }  \
/**/
#endif

DECLARE_FUNCTIONS_WITH_QUALS(0, /* nothing */);
DECLARE_FUNCTIONS_WITH_QUALS(1, const);
DECLARE_FUNCTIONS_WITH_QUALS(2, volatile);
DECLARE_FUNCTIONS_WITH_QUALS(3, const volatile);
DECLARE_FUNCTIONS_WITH_QUALS(4, &);
DECLARE_FUNCTIONS_WITH_QUALS(5 , const &);
DECLARE_FUNCTIONS_WITH_QUALS(6 , volatile &);
DECLARE_FUNCTIONS_WITH_QUALS(7 , const volatile &);
DECLARE_FUNCTIONS_WITH_QUALS(8 , noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(9 , const noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(10, volatile noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(11, const volatile noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(12, & noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(13, const & noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(14, volatile & noexcept);
DECLARE_FUNCTIONS_WITH_QUALS(15, const volatile & noexcept);

#if TEST_STD_VER >= 23
DECLARE_THIS_FUNCTIONS_WITH_QUALS(0, /* nothing */);
DECLARE_THIS_FUNCTIONS_WITH_QUALS(1, const);
DECLARE_THIS_FUNCTIONS_WITH_QUALS(4, &);
DECLARE_THIS_FUNCTIONS_WITH_QUALS(5 , const &);
DECLARE_THIS_FUNCTIONS_WITH_QUALS(6 , volatile &);
DECLARE_THIS_FUNCTIONS_WITH_QUALS(7 , const volatile &);
#endif

template<typename... Args> void whatis();

int main(int, char**) {
#define CHECK_FUNCTIONS(N)                                                    \
  do {                                                                        \
    /* implicit */                                                            \
    std::function g0 = f0_##N{};                                              \
    ASSERT_SAME_TYPE(decltype(g0), std::function<R()>);                       \
                                                                              \
    std::function g1 = f1_##N{};                                              \
    ASSERT_SAME_TYPE(decltype(g1), std::function<R(A1)>);                     \
                                                                              \
    std::function g2 = f2_##N{};                                              \
    ASSERT_SAME_TYPE(decltype(g2), std::function<R(A1, A2)>);                 \
                                                                              \
    std::function g3 = f3_##N{};                                              \
    ASSERT_SAME_TYPE(decltype(g3), std::function<R(A1, A2, A3)>);             \
                                                                              \
    /* explicit */                                                            \
    std::function g4{f0_##N{}};                                               \
    ASSERT_SAME_TYPE(decltype(g4), std::function<R()>);                       \
                                                                              \
    std::function g5{f1_##N{}};                                               \
    ASSERT_SAME_TYPE(decltype(g5), std::function<R(A1)>);                     \
                                                                              \
    std::function g6{f2_##N{}};                                               \
    ASSERT_SAME_TYPE(decltype(g6), std::function<R(A1, A2)>);                 \
                                                                              \
    std::function g7{f3_##N{}};                                               \
    ASSERT_SAME_TYPE(decltype(g7), std::function<R(A1, A2, A3)>);             \
                                                                              \
    /* from std::function */                                                  \
    std::function<R(A1)> unary;                                               \
    std::function g8 = unary;                                                 \
    ASSERT_SAME_TYPE(decltype(g8), std::function<R(A1)>);                     \
                                                                              \
    std::function g9 = std::move(unary);                                      \
    ASSERT_SAME_TYPE(decltype(g9), std::function<R(A1)>);                     \
                                                                              \
    std::function<R(A1&&)> unary_ref;                                         \
    std::function g10 = unary_ref;                                            \
    ASSERT_SAME_TYPE(decltype(g10), std::function<R(A1&&)>);                  \
                                                                              \
    std::function g11 = std::move(unary_ref);                                 \
    ASSERT_SAME_TYPE(decltype(g11), std::function<R(A1&&)>);                  \
  } while (false)                                                             \
/**/

  // Make sure we can deduce from function objects with valid call operators
  CHECK_FUNCTIONS(0);
  CHECK_FUNCTIONS(1);
  CHECK_FUNCTIONS(2);
  CHECK_FUNCTIONS(3);
  CHECK_FUNCTIONS(4);
  CHECK_FUNCTIONS(5);
  CHECK_FUNCTIONS(6);
  CHECK_FUNCTIONS(7);
  CHECK_FUNCTIONS(8);
  CHECK_FUNCTIONS(9);
  CHECK_FUNCTIONS(10);
  CHECK_FUNCTIONS(11);
  CHECK_FUNCTIONS(12);
  CHECK_FUNCTIONS(13);
  CHECK_FUNCTIONS(14);
  CHECK_FUNCTIONS(15);

#if TEST_STD_VER >= 23
#  define CHECK_THIS_FUNCTIONS(N)                                                                                      \
    do {                                                                                                               \
      /* implicit */                                                                                                   \
      std::function g0 = sf0_##N{};                                                                                    \
      ASSERT_SAME_TYPE(decltype(g0), std::function<R()>);                                                              \
                                                                                                                       \
      std::function g1 = sf1_##N{};                                                                                    \
      ASSERT_SAME_TYPE(decltype(g1), std::function<R(A1)>);                                                            \
                                                                                                                       \
      std::function g2 = sf2_##N{};                                                                                    \
      ASSERT_SAME_TYPE(decltype(g2), std::function<R(A1, A2)>);                                                        \
                                                                                                                       \
      std::function g3 = sf3_##N{};                                                                                    \
      ASSERT_SAME_TYPE(decltype(g3), std::function<R(A1, A2, A3)>);                                                    \
                                                                                                                       \
      /* explicit */                                                                                                   \
      std::function g4{sf0_##N{}};                                                                                     \
      ASSERT_SAME_TYPE(decltype(g4), std::function<R()>);                                                              \
                                                                                                                       \
      std::function g5{sf1_##N{}};                                                                                     \
      ASSERT_SAME_TYPE(decltype(g5), std::function<R(A1)>);                                                            \
                                                                                                                       \
      std::function g6{sf2_##N{}};                                                                                     \
      ASSERT_SAME_TYPE(decltype(g6), std::function<R(A1, A2)>);                                                        \
                                                                                                                       \
      std::function g7{sf3_##N{}};                                                                                     \
      ASSERT_SAME_TYPE(decltype(g7), std::function<R(A1, A2, A3)>);                                                    \
                                                                                                                       \
      /* noexcept */                                                                                                   \
      /* implicit */                                                                                                   \
      std::function gne0 = sfne0_##N{};                                                                                \
      ASSERT_SAME_TYPE(decltype(gne0), std::function<R()>);                                                            \
                                                                                                                       \
      std::function gne1 = sfne1_##N{};                                                                                \
      ASSERT_SAME_TYPE(decltype(gne1), std::function<R(A1)>);                                                          \
                                                                                                                       \
      std::function gne2 = sfne2_##N{};                                                                                \
      ASSERT_SAME_TYPE(decltype(gne2), std::function<R(A1, A2)>);                                                      \
                                                                                                                       \
      std::function gne3 = sfne3_##N{};                                                                                \
      ASSERT_SAME_TYPE(decltype(gne3), std::function<R(A1, A2, A3)>);                                                  \
                                                                                                                       \
      /* explicit */                                                                                                   \
      std::function gne4{sfne0_##N{}};                                                                                 \
      ASSERT_SAME_TYPE(decltype(gne4), std::function<R()>);                                                            \
                                                                                                                       \
      std::function gne5{sfne1_##N{}};                                                                                 \
      ASSERT_SAME_TYPE(decltype(gne5), std::function<R(A1)>);                                                          \
                                                                                                                       \
      std::function gne6{sfne2_##N{}};                                                                                 \
      ASSERT_SAME_TYPE(decltype(gne6), std::function<R(A1, A2)>);                                                      \
                                                                                                                       \
      std::function gne7{sfne3_##N{}};                                                                                 \
      ASSERT_SAME_TYPE(decltype(gne7), std::function<R(A1, A2, A3)>);                                                  \
                                                                                                                       \
    } while (false) /**/

  CHECK_THIS_FUNCTIONS(0);
  CHECK_THIS_FUNCTIONS(1);
  CHECK_THIS_FUNCTIONS(4);
  CHECK_THIS_FUNCTIONS(5);
  CHECK_THIS_FUNCTIONS(6);
  CHECK_THIS_FUNCTIONS(7);
#endif

  return 0;
}

// Make sure we fail in a SFINAE-friendly manner when we try to deduce
// from a type without a valid call operator.
template <typename F, typename = decltype(std::function{std::declval<F>()})>
constexpr bool can_deduce_test(int) { return true; }
template <typename F>
constexpr bool can_deduce_test(...) { return false; }

template <typename F>
constexpr bool can_deduce = can_deduce_test<F>(0);

struct valid { int operator()() const; };
struct invalid1 { };
struct invalid2 {
  template <typename ...Args>
  void operator()(Args ...);
};
struct invalid3 {
  void operator()(int);
  void operator()(long);
};
static_assert( can_deduce<valid>);
static_assert(!can_deduce<invalid1>);
static_assert(!can_deduce<invalid2>);
static_assert(!can_deduce<invalid3>);


// LWG 3238. Insufficiently-defined behavior of std::function deduction guides
// https://cplusplus.github.io/LWG/issue3238
// The deduction guides for std::function do not handle rvalue-ref qualified
// call operators and C-style variadics. It also doesn't deduce from nullptr_t.
// Make sure we stick to the specification.

struct invalid_rvalue_ref { R operator()() && { return {}; } };
struct invalid_c_vararg { R operator()(int, ...) { return {}; } };

static_assert(!can_deduce<invalid_rvalue_ref>);
static_assert(!can_deduce<invalid_c_vararg>);
static_assert(!can_deduce<std::nullptr_t>);
