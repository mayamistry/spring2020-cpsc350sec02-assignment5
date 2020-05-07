#include "GenStack.h"
#include "Student.h"
#include "Faculty.h"
#include "ActionType.h"

class Rollback {
  public:
    Rollback();
    ~Rollback();

    void addStudentAction(Student *s, string action); //adding the action to the stack (action should be the opposite of user did)
    void addFacultyAction(Faculty *f, string action);
    string undoAction(); //this is where pop off the action stack

    Student* popStudent();
    Faculty* popFaculty();

    bool checkIfEmpty();

  private:
    GenStack<Student> *m_studentStack;
    GenStack<Faculty> *m_facultyStack;
    GenStack<ActionType> *m_actionStack;
};
