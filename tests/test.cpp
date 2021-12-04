// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>
 
class Rectangle {
 private:
  uint width;
  uint height;
 
 public:
  Rectangle() : width(0), height(0) {
    width = 0;
    height = 0;
  }
  explicit Rectangle(const uint& width_, const uint& height_) {
    width = width_;
    height = height_;
  }
  ~Rectangle() {
    width = 0;
    height = 0;
  }
  friend bool operator==(const Rectangle& im1, const Rectangle& im2);
};
 
bool operator==(const Rectangle& im1, const Rectangle& im2) {
  if ((im1.width == im2.width) && (im1.height == im2.height)) {
    return true;
  } else {
    return false;
  }
}
 
TEST(Constructor, SharedPtr_no_args) {
  SharedPtr<int> test;
  EXPECT_EQ(test.get(), nullptr);
  EXPECT_EQ(test.use_count(), 0);
}
 
TEST(Constructor, SharedPtr_with_args) {
  SharedPtr<int> p1(new int(5));
  SharedPtr<int> p2(new int(10));
  EXPECT_EQ(*p1.get(), 5);
  EXPECT_EQ(*p2.get(), 10);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(p2.use_count(), 1);
}
 
TEST(Constructor, SharedPtr_with_SharedPtr) {
  SharedPtr<double> p1(new double(15));
  SharedPtr<double> p2(p1);
  EXPECT_EQ(*p1.get(), 15);
  EXPECT_EQ(*p2.get(), 15);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
}
 
TEST(Constructor, SharedPtr_move) {
  SharedPtr<double> p1(new double(5));
  SharedPtr<double> p2(std::move(p1));
  EXPECT_EQ(*p2.get(), 5);
  EXPECT_EQ(p2.use_count(), 1);
 
  SharedPtr<float> p3(new float(20));
  SharedPtr<float> p4(p3);
  SharedPtr<float> p5(std::move(p3));
  EXPECT_EQ(*p5.get(), 20);
  EXPECT_EQ(p5.use_count(), 2);
}
 
TEST(Equal, SharedPtr) {
  SharedPtr<double> p1(new double(5));
  SharedPtr<double> p2;
  p2 = p1;
  EXPECT_EQ(*p1.get(), 5);
  EXPECT_EQ(*p2.get(), 5);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
}
 
TEST(Equal, SharedPtr_move) {
  SharedPtr<double> p1(new double(5));
  SharedPtr<double> p2;
  p2 = std::move(p1);
  EXPECT_EQ(*p2.get(), 5);
  EXPECT_EQ(p2.use_count(), 1);
}
 
TEST(Bool, SharedPtr_not_nullptr) {
  SharedPtr<int> p1(new int(5));
  EXPECT_EQ(p1.operator bool(), 1);
}
 
TEST(Bool, SharedPtr_nullptr) {
  SharedPtr<int> p1;
  EXPECT_EQ(p1.operator bool(), 0);
}
 
TEST(Operator1, SharedPtr) {
  SharedPtr<int> p1(new int(5));
  EXPECT_EQ(*p1, 5);
}
 
TEST(Operator2, SharedPtr) {
  SharedPtr<int> p1(new int(5));
  EXPECT_EQ(*p1.operator->(), 5);
}
 
TEST(Get, SharedPtr) {
  SharedPtr<int> p1(new int(10));
  EXPECT_EQ(*p1.get(), 10);
}
 
TEST(Reset, SharedPtr_empty_1) {
  SharedPtr<int> p1(new int(10));
  p1.reset();
  EXPECT_EQ(p1.get(), nullptr);
}
 
TEST(Reset, SharedPtr_empty_2) {
  SharedPtr<int> p1;
  p1.reset();
  EXPECT_EQ(p1.get(), nullptr);
}
 
TEST(Reset, SharedPtr_T_ptr) {
  SharedPtr<int> p1(new int(10));
  p1.reset(new int(15));
  EXPECT_EQ(*p1.get(), 15);
}
 
TEST(Reset, SharedPtr_T_ptr_empty) {
  SharedPtr<int> p1;
  p1.reset(new int(10));
  EXPECT_EQ(*p1.get(), 10);
}
 
TEST(Swap, SharedPtr) {
  SharedPtr<int> p1(new int(5));
  SharedPtr<int> p3(p1);
  SharedPtr<int> p2(new int(10));
  p1.swap(p2);
  EXPECT_EQ(*p1.get(), 10);
  EXPECT_EQ(*p2.get(), 5);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(p2.use_count(), 2);
}
 
TEST(Swap, SharedPtr_empty) {
  SharedPtr<int> p1;
  SharedPtr<int> p2(new int(10));
  p1.swap(p2);
  EXPECT_EQ(*p1.get(), 10);
  EXPECT_EQ(p2.get(), nullptr);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(p2.use_count(), 0);
}
 
TEST(Use_count, SharedPtr) {
  SharedPtr<int> p1(new int(10));
  SharedPtr<int> p2 = p1;
  SharedPtr<int> p3(new int(5));
  p3 = p1;
  EXPECT_EQ(p1.use_count(), 3);
  EXPECT_EQ(p2.use_count(), 3);
  EXPECT_EQ(p3.use_count(), 3);
}
 
TEST(Destructor, Out_of_scope) {
  SharedPtr<float> p1(new float(20));
  {
    SharedPtr<float> p2(p1);
    EXPECT_EQ(p2.use_count(), 2);
  }
  EXPECT_EQ(p1.use_count(), 1);
}
 
TEST(Constructor, Custom_class) {
  SharedPtr<Rectangle> p1(new Rectangle(50, 100));
  SharedPtr<Rectangle> p2;
  p2 = p1;
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
  Rectangle im1(50, 100);
  EXPECT_EQ(*p1.get(), im1);
  EXPECT_EQ(*p2.get(), im1);
  Rectangle im2(90, 100);
  EXPECT_EQ(*p1.get() == im2, 0);
  EXPECT_EQ(*p2.get() == im2, 0);
}