#include "Faculty.h"

Faculty::Faculty() {
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_department = "";
  m_advisees = new LinkedList<int>();
}

Faculty::Faculty(int id, string name, string level, string department) {
  m_ID = id;
  m_name = name;
  m_level = level;
  m_department = department;
  m_advisees = new LinkedList<int>();
}

Faculty::~Faculty() {
  delete m_advisees;
}

void Faculty::setId(int id) {
  m_ID = id;
}

int Faculty::getId() {
  return m_ID;
}

void Faculty::setName(string name) {
  m_name = name;
}

string Faculty::getName() {
  return m_name;
}

void Faculty::setLevel(string level) {
  m_level = level;
}

string Faculty::getLevel() {
  return m_level;
}

void Faculty::setDepartment(string department) {
  m_department = department;
}

string Faculty::getDepartment() {
  return m_department;
}

void Faculty::setAdvisees(LinkedList<int> *advisees) {
  m_advisees = advisees;
}

LinkedList<int>* Faculty::getAdvisees() {
  if (m_advisees->isEmpty()) {
    cout << "This faculty member has no advisees. " << endl;
  }
  return m_advisees;
}

int Faculty::compareTo(Faculty *f) {
  if (m_ID < f->getId()) {
    return 0;
  } else {
    return 1;
  }
}
