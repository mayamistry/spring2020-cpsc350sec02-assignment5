#include "DBSimulation.h"

DBSimulation::DBSimulation() {
  m_masterStudent = NULL;
  m_masterFaculty = NULL;
}

DBSimulation::DBSimulation(BST<Student> *student, BST<Faculty> *faculty) {
  m_masterStudent = student;
  m_masterFaculty = faculty;
}

DBSimulation::~DBSimulation() {
  delete m_masterStudent;
  delete m_masterFaculty;
}

void DBSimulation::userSelection() {
  string userInput = "";
  //14 is the value for the user to exit
  while (userInput != "14") {
    //print options that the user can choose
    printMenu();
    cout << "Enter input here: ";
    cin >> userInput;
    cout << endl;
    if (userInput == "1") {
      printStudents();
    } else if (userInput == "2") {
      printFaculty();
    } else if (userInput == "3") {
      displayStudentInfo();
    } else if (userInput == "4") {
      displayFacultyInfo();
    } else if (userInput == "5") {
      printAdvisorInfo();
    } else if (userInput == "6") {
      printAdviseeInfo();
    } else if (userInput == "7") {
      addStudent();
    } else if (userInput == "8") {
      deleteStudent();
    } else if (userInput == "9") {
      deleteFaculty();
    } else if (userInput == "10") {
      addFaculty();
    } else if (userInput == "11") {
      changeStudentAdvisor();
    } else if (userInput == "12") {
      removeAdvisee();
    } else if (userInput == "13") {
      rollback();
    } else if (userInput == "14") {
      break;
    } else {
      cout << "Incorrect input. Enter any number from 1-14." << endl;
      cout << endl;
    }
  }
  exit();
}

void DBSimulation::printMenu() {
  cout << "Here is the menu. Enter the # of which action you want perform: " << endl;
  cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
  cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
  cout << "3. Find and display student information given the students id" << endl;
  cout << "4. Find and display faculty information given the faculty id" << endl;
  cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
  cout << "6. Given a faculty id, print ALL the names and info of his/her advisees" << endl;
  cout << "7. Add a new student" << endl;
  cout << "8. Delete a student given the id" << endl;
  cout << "9. Add a new faculty member" << endl;
  cout << "10. Delete a faculty member given the id." << endl;
  cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
  cout << "12. Remove an advisee from a faculty member given the ids" << endl;
  cout << "13. Rollback" << endl;
  cout << "14. Exit " << endl;
  cout << endl;
}

//option 1
void DBSimulation::printStudents() {
  cout << "Print all student" << endl;
}

//option 2
void DBSimulation::printFaculty() {
  cout << "Print all faculty" << endl;
}

//option 3
void DBSimulation::displayStudentInfo() {
  cout << "Display student info" << endl;
}

//option 4
void DBSimulation::displayFacultyInfo() {
  cout << "Display faculty info" << endl;
}

//option 5
void DBSimulation::printAdvisorInfo() {
  cout << "Print student's advisor info" << endl;
}

//option 6
void DBSimulation::printAdviseeInfo() {
  cout << "Print faculty's advisee info" << endl;
}

//option 7
void DBSimulation::addStudent() {
  cout << "Add student to table" << endl;
}

//option 8
void DBSimulation::deleteStudent() {
  cout << "Delete student from table" << endl;
}

//option 9
void DBSimulation::deleteFaculty() {
  cout << "Delete faculty from table" << endl;
}

//option 10
void DBSimulation::addFaculty() {
  cout << "Add faculty to table" << endl;
}

//option 11
void DBSimulation::changeStudentAdvisor() {
  cout << "Change the student's advisor" << endl;
}

//option 12
void DBSimulation::removeAdvisee() {
  cout << "Remove advisee from a faculty" << endl;
}

//option 13
void DBSimulation::rollback() {
  cout << "rollback" << endl;
}

//option 14
void DBSimulation::exit() {
  cout << "exit" << endl;
}

BST<Student>* DBSimulation::getStudentTree() {
  return m_masterStudent;
}

BST<Faculty>* DBSimulation::getFacultyTree() {
  return m_masterFaculty;
}
