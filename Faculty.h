#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"
#include "LinkedList.h"

class Faculty: public Person {
public:
  Faculty(); //Default constructor
  Faculty(int id, string name, string level, string department, LinkedList<int> *advisees); //Overloaded constructor
  ~Faculty(); //Destructor

  //from person class
  void setId(int id);
  int getId();
  void setName(string name);
  string getName();
  void setLevel(string level);
  string getLevel();

  //setter and getter methods
  void setDepartment(string department);
  string getDepartment();
  void setAdvisees(LinkedList<int> *advisees);
  LinkedList<int>* getAdvisees();

  //create compareTo method
  int compareTo(Faculty *f); //print 1 if this object is ID less than other, or 0

private:
  int m_ID;
  string m_name;
  string m_level;
  string m_department;
  LinkedList<int> *m_advisees;
};

#endif
