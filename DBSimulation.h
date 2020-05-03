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
    void printStudents(TreeNode<Student> *node);
    void printFaculty(TreeNode<Faculty> *node);
    void displayStudentInfo(Student *s);
    void displayFacultyInfo(Faculty *f);
    void printAdvisorInfo(Student *s);
    void printAdviseeInfo(Faculty *f);
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
