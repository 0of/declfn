/*
 * declfn
 *
 * Copyright (c) 2016 "0of" Magnus
 * Licensed under the Apache License, Version 2.0
 * https://github.com/0of/declfn/blob/master/LICENSE
 */
#ifndef DECLFN_H
#define DECLFN_H

#include <type_traits>

namespace Traits {
  template<typename T>
  struct function_trait;

  template<typename Class, typename Return, typename... Arg>
  struct function_trait<Return(Class::*)(Arg...)> {
    using type = std::function<Return(Arg...)>;
  };

  template<typename Class, typename Return, typename... Arg>
  struct function_trait<Return(Class::*)(Arg...) const> : public function_trait<Return(Class::*)(Arg...)>{};

  template<typename Class, typename Return, typename... Arg>
  struct function_trait<Return(Class::*)(Arg...) volatile> : public function_trait<Return(Class::*)(Arg...)>{};

  template<typename Class, typename Return, typename... Arg>
  struct function_trait<Return(Class::*)(Arg...) const volatile> : public function_trait<Return(Class::*)(Arg...)>{};

  template<typename Return, typename... Args>
  struct function_trait<Return(Args...)> {
    using type = std::function<Return(Args...)>;
  };

  template<typename Return, typename... Args>
  struct function_trait<Return(Args...) volatile> : public function_trait<Return(Args...)> {};

  template<typename T>
  using function_trait_t = typename function_trait<T>::type;

#if __OBJC__
  // objc c++ mixing mode
  template<typename T>
  struct block_trait;

  template<typename Return, typename... Arg>
  struct block_trait<Return(__strong ^)(Arg...)> {
    using type = std::function<Return(Arg...)>;
  };

  template<typename T>
  using block_trait_t = typename block_trait<T>::type;
#endif // __OBJC__

  struct callable_trait {
    template<typename Callable>
    static auto INVOKE(Callable&& callable, std::true_type isFunction) -> Traits::function_trait_t<std::remove_pointer_t<std::decay_t
    <Callable>>>;

    template<typename Callable>
    static auto INVOKE(Callable&& callable, std::false_type isFunction) -> Traits::function_trait_t<decltype(&std::decay_t<Callable>::operator())>;

    template<typename Return, typename... Args>
    static auto INVOKE(const std::function<Return(Args...)>& fn, std::false_type isFunction) -> std::function<Return(Args...)>;

    template<typename BindExpr>
    static std::enable_if_t<std::is_bind_expression<BindExpr>::value, BindExpr> INVOKE(const BindExpr& bindExpr, std::false_type isFunction);

  #if __OBJC__
    template<typename Callable>
    static auto INVOKE(Callable&& callable, std::false_type isFunction) -> block_trait_t<std::decay_t<Callable>>;
  #endif // __OBJC__

    static auto INVOKE(...) -> std::false_type;
  };
} // Traits

#ifndef declfn
# define declfn(fn) decltype(Traits::callable_trait::INVOKE(fn, std::is_function<std::remove_pointer_t<std::remove_reference_t<decltype(fn)>>>()))
#endif // declfn

#endif // DECLFN_H
