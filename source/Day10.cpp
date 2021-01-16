// Authors: Handling
// Created by 15870 on 2020/9/26.
// This is  PIMPL
// PIMPL（Private Implementation 或 Pointer to Implementation）是通过一个私有的成员指针，将指针所指向的类的内部实现数据进行隐藏。
// 单例模式的4种释放
// 实现写时复制（cow）的string，让其operator[] 能区分出读写操作
#include <bits/stdc++.h>
namespace pimpl{
class Line {
 public:
  Line(int x1, int y1, int x2, int y2);
  void PrintLine() const;
  ~Line();

  class LinePimpl;
 private:
  LinePimpl *pimpl_;
};
class Line::LinePimpl {
 private:
  class Point {
   private:
    int ix_;
    int iy_;
   public:
    explicit Point(int ix = 0, int iy = 0):ix_(ix), iy_(iy) {
      std::cout << "Point(int=0,int=0)" << std::endl;
    }
    void Print() const {
      std::cout << "(" << ix_ << "," << iy_ << ")";
    }
    ~Point() {
      std::cout << "~Point()" << std::endl;
    }
  };
 private:
  Point pt1_;
  Point pt2_;
 public:
  LinePimpl(int x1, int y1, int x2, int y2): pt1_(x1, y1), pt2_(x2, y2) {
    std::cout << "LinePimpl(int,int,int,int)" << std::endl;
  }
  void PrintLinePimpl() const {
    pt1_.Print();
    std::cout << "--->";
    pt2_.Print();
    std::cout << std::endl;
  }
  ~LinePimpl() {
    std::cout << "~LinePimpl()" << std::endl;
  }

};
Line::Line(int x1, int y1, int x2, int y2):pimpl_(new LinePimpl(x1,y1,x2,y2)){
  std::cout << "Line(int,int,int,int)" << std::endl;
}
void Line::PrintLine() const {
  pimpl_->PrintLinePimpl();
}
Line::~Line() {
  std::cout << "~Line()" << std::endl;
  if(pimpl_)
   delete pimpl_;
  pimpl_ = nullptr;
}
}
namespace singletonautorelease1{
// 利用另外一个友元类的析构函数保证安全释放
class AutoRelease;
class Singleton {
  friend class AutoRelease;
 private:

  Singleton() {
    std::cout << "Singleton()" << std::endl;
  }
  ~Singleton() {
    std::cout << "~Singleton()" << std::endl;
  }
  static Singleton *instance_;
  static std::mutex mutex_;
 public:
  static Singleton *Instance() {
    if(instance_ == nullptr) {
      std::unique_lock<std::mutex> mutex;
      if(instance_ == nullptr)
        instance_ = new Singleton();
    }
    return instance_;
  }
#if 0
  static void Destory() {
    if(instance_) {
      delete instance_;
      instance_ = nullptr;
    }
  }
#endif
};
class AutoRelease {
  ~AutoRelease() {
    if(Singleton::instance_) {
	  delete Singleton::instance_;
	  Singleton::instance_ = nullptr;
    }
  }
};
}

namespace singletonautorelease2 {
//内部类+静态成员的方法
class Singleton {
  friend class AutoRelease;

 public:
  static Singleton *Instance() {
    if(nullptr == instance_) {
      std::unique_lock<std::mutex> lck;
      if(nullptr == instance_) {
        instance_ = new Singleton();
      }
    }
	return instance_;
  }
 private:
  class AutoRelease {
   public:
    AutoRelease() {
      std::cout << "AutoRelease()" << std::endl;
    }
    ~AutoRelease() {
      std::cout << "~AutoRelease()" << std::endl;
      if(instance_) {
		delete instance_;
		instance_ = nullptr;
      }
    }
  };
 private:
  static std::mutex mutex_;
  static Singleton *instance_;
  static AutoRelease auto_release_;
};
Singleton *Singleton::instance_ = Instance();
Singleton::AutoRelease Singleton::auto_release_;
}


namespace singletonautorelease3 {
//饿汉， 在程序执行时就进行空间的分配，并注册在exit退出时执行的回调
//函数
class Singleton {
 public:
  static Singleton *Instance() {
    if(nullptr == instance_) {
      instance_ = new Singleton();
      atexit(Destory);
    }
  }
  static void Destory() {
    if(instance_) {
	  delete instance_;
	  instance_ = nullptr;
    }
  }
 private:
  Singleton() {
    std::cout << "Singleton()" << std::endl;
  }
  ~Singleton() {
    std::cout << "~Singleton()" << std::endl;
  }
  static Singleton *instance_;
};
Singleton *Singleton::instance_ = Instance();
}

namespace singletonautorelease4 {
//pthread_once + atexit: 在所有线程下只执行一次
class Singleton {
 public:
  static Singleton *Instance() {
    pthread_once(&once_, Init);
    return instance_;
  }
  static void Init() {
    instance_ = new Singleton();
    atexit(Destory);
  }
  static void Destory() {
    if(instance_) {
	  delete instance_;
	  instance_ = nullptr;
    }
  }
 private:
  Singleton() {
    std::cout << "Singleton()" << std::endl;
  }
  ~Singleton() {
    std::cout << "~Singleton()" << std::endl;
  }
  static Singleton *instance_;
  static pthread_once_t once_;
};
Singleton *Singleton::instance_ = nullptr;
pthread_once_t Singleton::once_ = PTHREAD_ONCE_INIT;
}

namespace writtencowstring {
class MyString {
 public:
  explicit MyString():shared_count_(new int(1)), str_(nullptr){}
  MyString(const MyString &lhs);
  MyString& operator=(const MyString &lhs);
  ~MyString();
  char& operator[](size_t sz);
  const char& operator[](size_t sz) const;
 private:
  int *shared_count_;
  char *str_;
};
MyString::MyString(const MyString &lhs) {
  shared_count_ = lhs.shared_count_;
  str_ = lhs.str_;
  ++*shared_count_;
}
MyString &MyString::operator=(const MyString &lhs) {
  if(&lhs != this) {
	MyString tmp(lhs);
	std::swap(tmp.str_, str_);
	std::swap(tmp.shared_count_, shared_count_);
  }
  return *this;
}
char &MyString::operator[](size_t pos) {
  if(pos >= strlen(str_))
    throw std::out_of_range("sz >= arr_len");
  if(*shared_count_ > 1) {
	MyString tmp(*this);
	shared_count_ = nullptr;
	shared_count_ = new int(1);
	str_ = new char[strlen(tmp.str_)]{};
	strncpy(str_, tmp.str_, strlen(tmp.str_));
  }
  return str_[pos];
}
const char &MyString::operator[](size_t pos) const {
  if(pos >= strlen(str_))
	throw std::out_of_range("sz >= arr_len");

  return str_[pos];
}
MyString::~MyString() {
  --*shared_count_;
  if(*shared_count_ == 0) {
	delete shared_count_;
  }
}
}