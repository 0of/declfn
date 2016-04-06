# declfn
`decltype` over callable and cast raw function, functor, bind expression, lambda expression and blocks in objc to `std::function` 

[![Build status](https://ci.appveyor.com/api/projects/status/wu4wi0b0xf2yd1ty?svg=true)](https://ci.appveyor.com/project/0of/declfn)
[![Build Status](https://travis-ci.org/0of/declfn.svg?branch=master)](https://travis-ci.org/0of/declfn)

# Usage
```c++
  // type: std::function<bool()>
  static bool raw_returned_fn() { return true; }
  declfn(raw_returned_fn)
  
  // type: std::function<bool()>
  class Functor {
  public:
      bool operator()() { return true; }
  };
  Functor fn;
  declfn(fn)
  
  // type: std::function<bool()>
  auto lambda = []{ return true };
  declfn(lambda)
```
