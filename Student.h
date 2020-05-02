#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"

class Student : public Person {
public:
  Student();
  Student(int id, string name, string level, string major, double gpa, int advisor);
  ~Student();

  //from person class
  void setId(int id);
  int getId();
  void setName(string name);
  string getName();
  void setLevel(string level);
  string getLevel();

  //setter and getter methods
  void setMajor(string major);
  string getMajor();
  void setGpa(double gpa);
  double getGpa();
  void setAdvisor(int advisor);
  int getAdvisor();
  int compareTo(Student *s); //print 1 if this object is ID less than other, or 0

private:
  int m_ID;
  string m_name;
  string m_level;
  string m_major;
  double m_GPA;
  int m_advisor; //store the id number of your advisor here
};

#endif
