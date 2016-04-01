/*
 * declfn
 *
 * Copyright (c) 2016 "0of" Magnus
 * Licensed under the Apache License, Version 2.0
 * https://github.com/0of/declfn/blob/master/LICENSE
 */

#include <functional>
#include "../declfn.h"

#define ECHO(message) _Pragma(R"(message("message"))")

// function
static bool raw_returned_fn() { return true; }
static void raw_int_arg_fn(int) {}
static void raw_ref_arg_fn(int& ) {}

namespace Functor {
  class returned {
  public:
      bool operator()() { return true; }
  };
}

class NormalClass {};


int main(int argc, const char * argv[]) {    
ECHO("it should be cast to `std::function<bool()>` when given raw_returned_fn")
  static_assert(std::is_same<std::function<bool()>, declfn(raw_returned_fn)>::value, "!");
ECHO("it should be cast to `std::function<void(int)>` when given raw_int_arg_fn")
  static_assert(std::is_same<std::function<void(int)>, declfn(raw_int_arg_fn)>::value, "!");
ECHO("it should be cast to `std::function<void(int&)>` when given raw_ref_arg_fn")
  static_assert(std::is_same<std::function<void(int&)>, declfn(raw_ref_arg_fn)>::value, "!");

ECHO("it should be cast to `std::function<bool()>` when given Functor::returned instance")
  {
    Functor::returned functor;
    static_assert(std::is_same<std::function<bool()>, declfn(functor)>::value, "!");
  }

ECHO("it should be cast to `std::function<bool()>` when given returned lambda expression")
  {
    auto lambda = [] { return true; };
    static_assert(std::is_same<std::function<bool()>, declfn(lambda)>::value, "!");
  }

ECHO("it should be cast to `std::function<void(int)>` when given returned lambda expression")
  {
    auto lambda = [](int) {};
    static_assert(std::is_same<std::function<void(int)>, declfn(lambda)>::value, "!");
  }

ECHO("it should be same to `std::function<bool(void)>` when given `std::function<bool(void)>` instance")
  {
    std::function<bool(void)> fn;
    static_assert(std::is_same<std::function<bool(void)>, declfn(fn)>::value, "!");
  }

ECHO("it should be false type when given non-callable")
  {
    NormalClass instance;
    static_assert(std::is_same<std::false_type, declfn(instance)>::value, "!");
  }
  return 0;
}
