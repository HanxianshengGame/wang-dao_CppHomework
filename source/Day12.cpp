// Authors: Handling
// Created by 15870 on 2020/10/5.
// This is Derive
#include <iostream>
#include <utility>
using namespace std;
namespace derive {
const double PI = 3.1415926;

class Circle {
 private:
  double radius_;
 public:
  Circle(): radius_(0) {}
  explicit Circle(double  radius): radius_(radius) {}

  double GetArea() const { return radius_ * radius_ * PI; }
  double GetPerimeter() const { return 2 * PI * radius_; }
  void Show() const;
};
void Circle::Show() const {
  cout << "radius: " << radius_ << endl
       << "area:" << GetArea() << endl
       << "perimeter: " << GetPerimeter() << endl;
}

class Cylinder: public Circle {
 private:
  double height_;
 public:
  Cylinder(double radius, double height):
           Circle(radius), height_(height) { }
  double GetVolume() const { return GetArea() * height_; }
  double ShowVolume() const ;
};
double Cylinder::ShowVolume() const {
  cout << "volume: " << GetVolume() << endl;
}


class Person {
 private:
  string name_;
  int    age_;
 public:
  Person(string name, int age) :
         name_(std::move(name)), age_(age) { }
  void Display() const;
};
void Person::Display() const {
  cout << "name: " << name_
       << "age: " << age_;
}

class Employee: Person {
 private:
  string department_; //部门
  double salary_;      //工资
 public:
  Employee(string name, int age, string department, double salary):
	  Person(std::move(name), age), department_(std::move(department)),
	  salary_(salary) { }

  void Display() const;

};
void Employee::Display() const {
  Person::Display();
  cout << "department: " << department_
	   << "salary: " << salary_ << endl;
}

}



