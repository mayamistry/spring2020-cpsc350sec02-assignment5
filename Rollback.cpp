#include "Rollback.h"

Rollback::Rollback() {
  m_studentStack = new GenStack<Student>();
  m_facultyStack = new GenStack<Faculty>(5);
  m_actionStack = new GenStack<ActionType>(5);
}

Rollback::~Rollback() {
  delete m_studentStack;
  delete m_facultyStack;
  delete m_actionStack;
}

void Rollback::addStudentAction(Student *s, string action) {
  if (m_actionStack->isFull()) {
    GenStack<ActionType> *temp = new GenStack<ActionType>(5);
    for (int i = 0; i < 5; ++i) {
      temp->push(m_actionStack->pop());
    }
    ActionType *lastItem = temp->pop();
    for (int i = 0; i < 4; ++i) {
      m_actionStack->push(temp->pop());
    }
  } else {
    m_studentStack->push(s);
    ActionType *t = new ActionType(action);
    m_actionStack->push(t);
  }
}

void Rollback::addFacultyAction(Faculty *f, string action) {
  if (m_actionStack->isFull()) {
    GenStack<ActionType> *temp = new GenStack<ActionType>(5);
    for (int i = 0; i < 5; ++i) {
      temp->push(m_actionStack->pop());
    }
    ActionType *lastItem = temp->pop();
    for (int i = 0; i < 4; ++i) {
      m_actionStack->push(temp->pop());
    }
  }
  m_facultyStack->push(f);
  ActionType *t = new ActionType(action);
  m_actionStack->push(t);
}

string Rollback::undoAction() {
  ActionType *a = m_actionStack->pop();
  string action = a->getAction();
  return action;
}

Student* Rollback::popStudent() {
  return m_studentStack->pop();
}

Faculty* Rollback::popFaculty() {
  return m_facultyStack->pop();
}

bool Rollback::checkIfEmpty() {
  if (m_actionStack->isEmpty()) {
    return true;
  } else {
    return false;
  }
}
