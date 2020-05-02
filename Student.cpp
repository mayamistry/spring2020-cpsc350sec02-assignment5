#include "Student.h"

Student::Student() {
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_major = "";
  m_GPA = 0.0;
  m_advisor = 0;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor) {
  m_ID = id;
  m_name = name;
  m_level = level;
  m_major = major;
  m_GPA = gpa;
  m_advisor = advisor;
}

Student::~Student() {
  //nothing happens here
}

void Student::setId(int id) {
  m_ID = id;
}

int Student::getId() {
  return m_ID;
}

void Student::setName(string name) {
  m_name = name;
}

string Student::getName() {
  return m_name;
}

void Student::setLevel(string level) {
  m_level = level;
}

string Student::getLevel() {
  return m_level;
}

void Student::setMajor(string major) {
  m_major = major;
}

string Student::getMajor() {
  return m_major;
}

void Student::setGpa(double gpa) {
  m_GPA = gpa;
}

double Student::getGpa() {
  return m_GPA;
}

void Student::setAdvisor(int advisorField) {
  m_advisor = advisorField;
}

int Student::getAdvisor() {
  return m_advisor;
}

int Student::compareTo(Student *s) {
  if (m_ID < s->getId()) {
    return 0;
  } else {
    return 1;
  }
}
