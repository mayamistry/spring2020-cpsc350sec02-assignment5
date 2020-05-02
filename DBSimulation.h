#include "Student.h"
#include "Faculty.h"
#include "BST.h"

//Database simulation class
class DBSimulation {
  public:
    DBSimulation();
    DBSimulation(BST<Student> *student, BST<Faculty> *faculty);
    ~DBSimulation();

    void userSelection();
    void printMenu();

    //user menu actions
    void printStudents();
    void printFaculty();
    void displayStudentInfo();
    void displayFacultyInfo();
    void printAdvisorInfo();
    void printAdviseeInfo();
    void addStudent();
    void deleteStudent();
    void deleteFaculty();
    void addFaculty();
    void changeStudentAdvisor();
    void removeAdvisee();
    void rollback();
    void exit();

    //getter methods for the tables
    BST<Student>* getStudentTree();
    BST<Faculty>* getFacultyTree();

  private:
    BST<Student> *m_masterStudent;
    BST<Faculty> *m_masterFaculty;
};
