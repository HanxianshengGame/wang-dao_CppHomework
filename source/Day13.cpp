// Authors: Handling
// Created by 15870 on 2020/10/5.
// This is polymorphism
#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::string;
namespace polymorphism { //多态
class Figure {
 protected:
	string name_;
 public:
  virtual double GetArea() = 0;
  virtual string GetName() = 0;
  virtual void Show() = 0;
};

class Circle: public Figure {
  static const double PI;
 private:
  double radius_;
 public:
  Circle(): radius_(0) {
    name_ = "Figure";
  }
  explicit Circle(double radius): radius_(radius) {
    name_ = "Figure";
  }

  double GetRadius() const { return radius_; }
  double GetPerimeter() const { return 2*PI*radius_; }
  virtual double GetArea() const { return  PI*radius_*radius_; }
  virtual string GetName() const { return name_; }
  virtual void Show() const ;
};
void Circle::Show() const {
  cout << "radius: " << radius_
       << "area: " << GetArea()
       << "perimeter: " << GetPerimeter();
}

class Cylinder: public Circle {
 private:
  double height_;
 public:
  Cylinder(double radius, double height):
    	 	Circle(radius), height_(height){
    name_ = "Cylinder";
  }

  double GetArea() const override { return Circle::GetArea() * (2+height_);}
  string GetName() const override { return name_; }
  double GetHeight( ) const { return height_; }      //获取圆柱体的高
  double GetVolume( ) const { return Circle::GetArea() * height_; }     //获取圆柱体的体积
  void  Show() const override;      		 //将圆柱体的高、表面积、体积输出到屏幕

};
void Cylinder::Show() const {
  cout << "height: " << height_
  		<< "area: " << GetArea()
  		<< "volume: " << GetVolume();
}

}
int main() {
  using namespace polymorphism;

  return 0;
}
