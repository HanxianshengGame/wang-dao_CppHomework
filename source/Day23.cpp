// Authors: Handling
// Created by 15870 on 2020/10/16.
// This is design pattern
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using std::find;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
namespace simplefactory1 {
class TankBase {
 public:
  explicit TankBase(unsigned int attack);
  virtual void ShowAttribute() const = 0;
 protected:
  unsigned int attack_;
};
TankBase::TankBase(unsigned int attack): attack_(attack) {

}

class TankA: public TankBase {
 public:
  explicit TankA(unsigned int attack);
  void ShowAttribute() const override;
};
TankA::TankA(unsigned int attack): TankBase(attack) {

}
void TankA::ShowAttribute() const {
  cout << "TankA attack = :" << attack_ << endl;
}
class TankB: public TankBase {
 public:
  explicit TankB(unsigned int attack);
  void ShowAttribute() const override;
};
TankB::TankB(unsigned int attack): TankBase(attack) {

}
void TankB::ShowAttribute() const {
  cout << "TankB attack = :" << attack_ << endl;
}

class Factory {
 public:
  static TankBase *CreateTankA() {
	return new TankA(5);
  }
  static  TankBase *CreateTankB() {
	return new TankB(6);
  }
};
}
namespace simplefactory2 {

class TankBase {
 public:
  explicit TankBase(unsigned int attack);
  virtual void ShowAttribute() const = 0;
 protected:
  unsigned int attack_;
};
TankBase::TankBase(unsigned int attack): attack_(attack) {

}

class TankA: public TankBase {
 public:
  explicit TankA(unsigned int attack);
  void ShowAttribute() const override;
};
TankA::TankA(unsigned int attack): TankBase(attack) {

}
void TankA::ShowAttribute() const {
  cout << "TankA attack = :" << attack_ << endl;
}
class TankB: public TankBase {
 public:
  explicit TankB(unsigned int attack);
  void ShowAttribute() const override;
};
TankB::TankB(unsigned int attack): TankBase(attack) {

}
void TankB::ShowAttribute() const {
  cout << "TankB attack = :" << attack_ << endl;
}

class TankAFactory {
 public:
  static TankBase *CreateTankA() {
	return new TankA(5);
  }
};

class TankBFactory {
 public:
  static TankBase *CreateTankB() {
    return new TankB(6);
  }
};
}
namespace observerpattern {
class ObServerBase;

class Subject {
 private:
  vector<ObServerBase*> observers_;
  bool is_broadcast_;
 public:
  Subject();
  void set_is_broadcast(bool state);
  void Attack(ObServerBase *observer);
 private:
  void NotifyAllObservers() const;
};
Subject::Subject(): observers_(), is_broadcast_(false) {

}
void Subject::set_is_broadcast(bool is_broadcast) {
  is_broadcast_ = is_broadcast;
  NotifyAllObservers();
}
void Subject::Attack(ObServerBase *observer) {
  observers_.push_back(observer);
}


class ObServerBase {
 protected:
  Subject *subject_;
 public:
  explicit ObServerBase(Subject *subject);
  virtual void update() = 0;
};
ObServerBase::ObServerBase(Subject *subject): subject_(subject) {
  subject->Attack(this);
}

class ObServerA: public ObServerBase {
 public:
  explicit ObServerA(Subject *subject);
 public:
  void update() override;
};
ObServerA::ObServerA(Subject *subject): ObServerBase(subject) {
}
void ObServerA::update() {
  cout << "ObServerA get the message!" << endl;
}

class ObServerB: public ObServerBase {
 public:
  explicit ObServerB(Subject *subject);
 public:
  void update() override;
};
ObServerB::ObServerB(Subject *subject): ObServerBase(subject) {
}
void ObServerB::update() {
  cout << "ObServerB get the message!" << endl;
}

void Subject::NotifyAllObservers() const {
  for(auto observer : observers_)
	observer->update();
}
}
int main() {
// using namespace simplefactory1;
// auto tankA = unique_ptr<TankBase>(Factory::CreateTankA());
// auto tankB = unique_ptr<TankBase>(Factory::CreateTankB());
//
// tankA->ShowAttribute();
// tankB->ShowAttribute();

  using namespace observerpattern;
  //专门看老师来没来的小韩
  unique_ptr<Subject> hanzhenjiang = unique_ptr<Subject>(new Subject());

  //朱春雨与曹立爽都在看自己的小说，并嘱托小韩帮忙看老师
  unique_ptr<ObServerBase> zhuchunyu = unique_ptr<ObServerBase>(new ObServerA(hanzhenjiang.get()));
  unique_ptr<ObServerBase> caolishuang = unique_ptr<ObServerBase>(new ObServerB(hanzhenjiang.get()));

  hanzhenjiang->set_is_broadcast(true); //老师来了


}

