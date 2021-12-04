// Copyright 2020 Lasar1k <alf.ivan2002@gmail.com>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <atomic>
template <typename T>
class SharedPtr {
  T*Sptr = nullptr;
  std::atomic_uint* counter;

 public:
  SharedPtr(){
    Sptr = nullptr;
    counter = nullptr;
  }
  SharedPtr(T* ptr){
    Sptr = ptr;
    counter = new std::atomic_uint[1];
  }
  SharedPtr(const SharedPtr& r){
    *this = r;
  }
  SharedPtr(SharedPtr&& r){
    *this = std::move(r);
  }
  ~SharedPtr(){
    if (counter == nullptr)
    {
      return;
    }
    else
    {
      *(counter) = *(counter) - 1;
      if (*(counter) == 0)
      {
        delete Sptr;
        delete counter;
      }
      else if (*(counter) > 0)
      {
        Sptr = nullptr;
        counter = nullptr;
      }
    }
  }
  auto operator=(const SharedPtr& r){
    if (*this == r)
    {
      return *this;
    }
    this->~SharedPtr();
    Sptr = r.Sptr;
    counter = r.counter;
    counter++;
    return *this;
  }
  auto operator=(SharedPtr&& r){
    if (*this == r)
    {
      return *this;
    }
    this->~SharedPtr();
    Sptr = r.Sptr;
    counter = r.counter;
    r.Sptr = nullptr;
    r.counter = nullptr;
    *(counter) = *(counter) + 1;
    return *this;
  }
  // проверяет, указывает ли указатель на объект
  operator bool() const{
    if (*(counter) > 0) 
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  auto operator*() const{
    return *Sptr;
  }
  auto operator->() const{
    return Sptr;
  }

  auto get(){
    return Sptr;
  }
  void reset(){
    Sptr = nullptr;
    counter = nullptr;
  }
  void reset(T* ptr){
    Sptr = ptr;
    counter = new std::atomic_uint[1];
  }
  void swap(SharedPtr& r){
    if (*this == r)
    {
      return;
    }
    std::swap(Sptr, r.Sptr);
    std::swap(counter, r.counter);
  }
  // возвращает количество объектов SharedPtr,
  //которые ссылаются на тот же управляемый объект
  unsigned int use_count() const{
    if (Sptr != nullptr)
    {
      return *(counter);
    }
    else
    {
      return 0;
    }
  }
};//
// Created by lasar1k on 9/17/21.
#endif // INCLUDE_HEADER_HPP_