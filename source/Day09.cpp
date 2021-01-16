// Authors: Handling
// Created by 15870 on 2020/9/25.
// This is MyString
#include <bits/stdc++.h>
namespace mystring {
class MyString {
  friend bool operator==(const MyString &lhs, const MyString &rhs);
  friend bool operator!=(const MyString &lhs, const MyString &rhs);
  friend bool operator<(const MyString &lhs, const MyString &rhs);
  friend bool operator>(const MyString &lhs, const MyString &rhs);
  friend bool operator<=(const MyString &lhs, const MyString &rhs);
  friend bool operator>=(const MyString &lhs, const MyString &rhs);
  friend std::ostream &operator<<(std::ostream &os, const MyString &rhs);
  friend std::istream &operator>>(std::istream &is, MyString &rhs);
 private:
  char *pstr_;
 public:
  MyString();
  explicit MyString(const char *str);
  MyString(const MyString &lhs);
  ~MyString();
  MyString &operator=(const MyString &lhs);
  MyString &operator=(const char *str);
  MyString &operator+=(const MyString &lhs);

  MyString &operator+=(const char *str);

  char &operator[](std::size_t index);
  const char &operator[](std::size_t index) const;

  std::size_t size() const;
  const char *c_str() const;

};
MyString operator+(const MyString &lhs, const MyString &rhs);
MyString operator+(const MyString &lhs, const char *str);
MyString operator+(const char *str, const MyString &rhs);

MyString::MyString() : pstr_(nullptr) {
}
MyString::MyString(const char *str) {
  pstr_ = nullptr;
  auto len = strlen(str);
  pstr_ = new char[len]{};
  strncpy(pstr_, str, len);
}
MyString::MyString(const MyString &lhs) {
  auto len = lhs.size();
  pstr_ = new char[len]{};
  strncpy(pstr_, lhs.pstr_, len);
}
MyString &MyString::operator=(const MyString &lhs) {
  if (&lhs != this) {
	auto tmp(lhs);
	std::swap(tmp.pstr_, pstr_);
  }
  return *this;
}
MyString &MyString::operator=(const char *str) {
  if (str != pstr_) {
	MyString tmp(str);
	std::swap(tmp.pstr_, pstr_);
  }
  return *this;
}
MyString &MyString::operator+=(const MyString &lhs) {
  auto sz = size() + lhs.size();
  MyString tmp;
  tmp.pstr_ = new char[sz]{};
  tmp.pstr_ = strcat(tmp.pstr_, pstr_);
  tmp.pstr_ = strcat(tmp.pstr_, lhs.pstr_);
  std::swap(tmp.pstr_, pstr_);
  return *this;
}
MyString &MyString::operator+=(const char *str) {
  auto sz = size() + strlen(str);
  MyString tmp;
  tmp.pstr_ = new char[sz]{};
  tmp.pstr_ = strcat(tmp.pstr_, pstr_);
  tmp.pstr_ = strcat(tmp.pstr_, str);
  std::swap(tmp.pstr_, pstr_);
  return *this;
}
char &MyString::operator[](std::size_t index) {
  if (index >= size()) {
	throw std::out_of_range("index >= arr.size()");
  }
  return pstr_[index];
}
const char &MyString::operator[](std::size_t index) const {
  ;
  return static_cast<const char &>(operator[](index));
}
std::size_t MyString::size() const {
  return strlen(pstr_);
}
const char *MyString::c_str() const {
  return pstr_;
}

bool operator==(const MyString &lhs, const MyString &rhs) {
  if (&lhs == &rhs)
	return true;
  if (strcmp(lhs.pstr_, rhs.pstr_) == 0)
	return true;
  return false;
}
bool operator!=(const MyString &lhs, const MyString &rhs) {
  return !operator==(lhs, rhs);
}
bool operator<(const MyString &lhs, const MyString &rhs) {
  return strcmp(lhs.pstr_, rhs.pstr_) < 0;
}
bool operator>(const MyString &lhs, const MyString &rhs) {
  return strcmp(lhs.pstr_, rhs.pstr_) > 0;
}
bool operator<=(const MyString &lhs, const MyString &rhs) {
  return strcmp(lhs.pstr_, rhs.pstr_) <= 0;
}
bool operator>=(const MyString &lhs, const MyString &rhs) {
  return strcmp(lhs.pstr_, rhs.pstr_) >= 0;
}
std::ostream &operator<<(std::ostream &os, const MyString &rhs) {
  if (rhs.pstr_ == nullptr)
	return os;
  auto index = 0;
  while (index != rhs.size()) {
	os << rhs.pstr_[index++];
  }
  return os;
}
std::istream &operator>>(std::istream &is,  MyString &rhs) {
  std::vector<char> tmp_vec;
  char ch = 0;
  while (is >> ch) {
	tmp_vec.push_back(ch);
  }
  MyString tmp;
  tmp.pstr_ = new char[tmp_vec.size()]{};
  std::copy(tmp_vec.begin(), tmp_vec.end(), tmp.pstr_);
  std::swap(tmp.pstr_, rhs.pstr_);
  return is;
}
MyString::~MyString() {
  delete[] pstr_;
}
}

