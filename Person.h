#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

//this is our base class but I don't think it needs to be abstract
class Person{
  public:
    //setter and getter methods for ID, name, and level
    virtual void setId(int id) = 0;
    virtual int getId() = 0;
    virtual void setName(string name) = 0;
    virtual string getName() = 0;
    virtual void setLevel(string level) = 0;
    virtual string getLevel() = 0;
};

#endif
