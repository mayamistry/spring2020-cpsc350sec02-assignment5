#include "BST.h"
#include "Rollback.h"

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

    //methods if user decides to rollback
    void deleteStudentRollback(Student *s);
    void deleteFacultyRollback(Faculty *f);
    void addStudentRollback(Student *s);
    void addFacultyRollback(Faculty *f);

    //getter methods for the tables
    BST<Student>* getStudentTree();
    BST<Faculty>* getFacultyTree();

    void iterate(TreeNode<Student> *node, Faculty *f);

  private:
    BST<Student> *m_masterStudent;
    BST<Faculty> *m_masterFaculty;
    Rollback *m_rollback;
    //list to keep students that don't have a faculty member if faculty table is empty
};
