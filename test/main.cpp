/*
 * declfn
 *
 * Copyright (c) 2016 "0of" Magnus
 * Licensed under the Apache License, Version 2.0
 * https://github.com/0of/declfn/blob/master/LICENSE
 */

#include <functional>
#include "../declfn.h"

// function
static bool raw_returned_fn() { return true; }
static void raw_int_arg_fn(int) {}
static void raw_ref_arg_fn(int& ) {}

// member function
// TODO: not support
// class Class {
// public:
//     bool returned_mem_fn() { return true; }
//     void int_arg_mem_fn(int) {}
//     void int_arg_const_mem_fn(int) const {}
//     void int_arg_cv_mem_fn(int) const volatile {}
//     void int_arg_volatile_mem_fn(int) volatile {}
// };

namespace Functor {
  class returned {
  public:
      bool operator()() { return true; }
  };
  
  class int_arg {
      void operator()(int) {}
  };

  class int_arg_const {
      void operator()(int) const {}
  };
  
  class int_arg_cv {
      void operator()(int) const volatile {}
  };

  class int_arg_volatile {
      void operator()(int) volatile {}
  };
}

int main(int argc, const char * argv[]) {    
#warning "it should be cast to `std::function<bool()>` when given raw_returned_fn"
  static_assert(std::is_same<std::function<bool()>, declfn(raw_returned_fn)>::value, "!");
#warning "it should be cast to `std::function<void(int)>` when given raw_int_arg_fn"
  static_assert(std::is_same<std::function<void(int)>, declfn(raw_int_arg_fn)>::value, "!");
#warning "it should be cast to `std::function<void(int&)>` when given raw_ref_arg_fn"
  static_assert(std::is_same<std::function<void(int&)>, declfn(raw_ref_arg_fn)>::value, "!");

#warning "it should be cast to `std::function<bool()>` when given Functor::returned instance"
  {
    Functor::returned functor;
    static_assert(std::is_same<std::function<bool()>, declfn(functor)>::value, "!");
  }
// #warning "it should be cast to `std::function<void(int)>` when given Functor::int_arg instance"
//   {
//     Functor::int_arg functor;
//     static_assert(std::is_same<std::function<void(int)>, declfn(functor)>::value, "!");
//   }
// #warning "it should be cast to `std::function<void(int)>` when given Functor::int_arg_const instance"
//   {
//     Functor::int_arg_const functor;
//     static_assert(std::is_same<std::function<void(int)>, declfn(functor)>::value, "!");
//   }
// #warning "it should be cast to `std::function<void(int)>` when given Functor::int_arg_cv instance"
//   {
//     Functor::int_arg_cv functor;
//     static_assert(std::is_same<std::function<void(int)>, declfn(functor)>::value, "!");
//   } 
// #warning "it should be cast to `std::function<void(int)>` when given Functor::int_arg_volatile instance"
//   {
//     Functor::int_arg_volatile functor;
//     static_assert(std::is_same<std::function<void(int)>, declfn(functor)>::value, "!");
//   }

// #warning "it should be cast to `std::function<bool()>` when given bind raw_returned_fn"
//    static_assert(std::is_same<std::function<void()>, declfn(std::bind(raw_int_arg_fn, 6))>::value, "!");

    return 0;
}
