#include "DBSimulation.h"

DBSimulation::DBSimulation() {
  //create two empty BSTs
  m_masterStudent = new BST<Student>();
  m_masterFaculty = new BST<Faculty>();
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
      TreeNode<Student>* root = m_masterStudent->getRootNode();
      printStudents(root);
    } else if (userInput == "2") {
      TreeNode<Faculty>* root = m_masterFaculty->getRootNode();
      printFaculty(root);
    } else if (userInput == "3") {
      cout << "What student ID would you like to look up? Enter it here: " << endl;
      int studentID = 0;
      cin >> studentID;
      Student *s = m_masterStudent->search(studentID);
      if (s != NULL) {
        displayStudentInfo(s);
      } else {
        cout << "Student doesn't exist in the database. Try again." << endl;
        cout << endl;
      }
    } else if (userInput == "4") {
      cout << "What faculty ID would you like to look up? Enter it here: " << endl;
      int facultyID = 0;
      cin >> facultyID;
      Faculty *f = m_masterFaculty->search(facultyID);
      if (f != NULL) {
        displayFacultyInfo(f);
      } else {
        cout << "Faculty doesn't exist in the database. Try again." << endl;
      }
    } else if (userInput == "5") {
      cout << "Which student's faculty advisor do you want to look up? Enter the student's ID: " << endl;
      int studentID = 0;
      cin >> studentID;
      Student *s = m_masterStudent->search(studentID);
      if (s != NULL) {
        printAdvisorInfo(s);
      } else {
        cout << "Student doesn't exist in the database. Try again." << endl;
        cout << endl;
      }
    } else if (userInput == "6") {
      cout << "What faculty ID would you like to look up? Enter it here: " << endl;
      int facultyID = 0;
      cin >> facultyID;
      Faculty *f = m_masterFaculty->search(facultyID);
      if (f != NULL) {
        printAdviseeInfo(f);
      } else {
        cout << "Faculty doesn't exist in the database. Try again." << endl;
        cout << endl;
      }
    } else if (userInput == "7") {
      addStudent();
    } else if (userInput == "8") {
      deleteStudent();
    } else if (userInput == "9") {
      addFaculty();
    } else if (userInput == "10") {
      deleteFaculty();
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
//using inorder traversal
void DBSimulation::printStudents(TreeNode<Student>* node) {
  if (node == NULL) {
    return;
  }
  printStudents(node->left);
  Student *s = node->value;
  cout << "Student ID: " << s->getId() << endl;
  cout << "Student name: " << s->getName() << endl;
  cout << "Field level: " << s->getLevel() << endl;
  cout << "Major: " << s->getMajor() << endl;
  cout << "GPA: " << s->getGpa() << endl;
  cout << "Advisor ID: " << s->getAdvisor() << endl;
  cout << endl;
  printStudents(node->right);
}

//option 2
void DBSimulation::printFaculty(TreeNode<Faculty>* node) {
  if (node == NULL) {
    return;
  }
  printFaculty(node->left);
  Faculty *f = node->value;
  cout << "Faculty ID: " << f->getId() << endl;
  cout << "Faculty name: " << f->getName() << endl;
  cout << "Field level: " << f->getLevel() << endl;
  cout << "Department: " << f->getDepartment() << endl;
  cout << "List of advisees (ID #'s): " << endl;
  LinkedList<int> *advisees = f->getAdvisees();
  if (advisees != NULL) {
    advisees->printList();
  }
  cout << endl;
  printFaculty(node->right);
}

//option 3
void DBSimulation::displayStudentInfo(Student *s) {
  cout << "Here is the information of the student: " << endl;
  cout << "Student ID: " << s->getId() << endl;
  cout << "Student name: " << s->getName() << endl;
  cout << "Field level: " << s->getLevel() << endl;
  cout << "Major: " << s->getMajor() << endl;
  cout << "GPA: " << s->getGpa() << endl;
  cout << "Advisor ID: " << s->getAdvisor() << endl;
  cout << endl;
}

//option 4
void DBSimulation::displayFacultyInfo(Faculty *f) {
  cout << "Here is the information of the faculty: " << endl;
  cout << "Faculty ID: " << f->getId() << endl;
  cout << "Faculty name: " << f->getName() << endl;
  cout << "Field level: " << f->getLevel() << endl;
  cout << "Department: " << f->getDepartment() << endl;
  cout << "List of advisees (ID #'s): " << endl;
  LinkedList<int> *advisees = f->getAdvisees();
  advisees->printList();
  cout << endl;
}

//option 5
void DBSimulation::printAdvisorInfo(Student *s) {
  int facultyID = s->getAdvisor();
  Faculty *f = m_masterFaculty->search(facultyID);
  displayFacultyInfo(f);
}

//option 6
void DBSimulation::printAdviseeInfo(Faculty *f) {
  cout << "Here's the list of this faculty's advisees: " << endl;
  LinkedList<int> *advisees = f->getAdvisees();
  ListNode<int> *curr = advisees->front;
  while (curr != NULL) {
    int studentID = curr->data;
    Student *s = m_masterStudent->search(studentID);
    displayStudentInfo(s);
    curr = curr->next;
  }
  cout << endl;
}

//option 7
void DBSimulation::addStudent() {
  //use getline method for all of the string methods since they might have spaces
  cout << "Enter all of the new information for the student being added: " << endl;
  cout << endl;
  int id = 0;
  cout << "Enter the ID of the student: " << endl;
  cin >> id;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> id;
  }
  string studentName = "";
  cout << "Enter the name of the student: " << endl;
  cin.ignore();
  getline(cin, studentName); //use get line because this might have spaces
  string field = "";
  cout << "Enter the field of the student (freshman, sophomore, etc.): " << endl;
  cin.ignore();
  getline(cin, field);
  string major = "";
  cout << "Enter the student's major: " << endl;
  cin.ignore();
  getline(cin, major);
  double gpa = 0.0;
  cout << "Enter the GPA of student: " << endl;
  cin >> gpa;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in a number (ex. 3.0): " << endl;
    cin.clear();
    cin.ignore();
    cin >> gpa;;
  }
  int facultyID = 0;
  //assign the student an advisor
  cout << "Here is the list of all of the advisors: " << endl;
  TreeNode<Faculty> *root = m_masterFaculty->getRootNode();
  printFaculty(root);
  cout << "Enter the faculty ID of which advisor you want: " << endl;
  cin >> facultyID;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the faculty ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> facultyID;
  }
  //need to check that the facultyID is valid
  Faculty *f = m_masterFaculty->search(facultyID);
  while (f == NULL) {
    cout << "The faculty ID you entered is invalid. Try again: " << endl;
    cin >> facultyID;
    f = m_masterFaculty->search(facultyID);
  }
  //create an object
  f->getAdvisees()->insertFront(id);

  Student *s = new Student(id, studentName, field, major, gpa, facultyID);
  m_masterStudent->insert(id, s);
  cout << endl;
}

//option 8
void DBSimulation::deleteStudent() {
  cout << "Delete student from table" << endl;
}

//option 10
void DBSimulation::deleteFaculty() {
  cout << "Delete faculty from table" << endl;
}

//option 9
void DBSimulation::addFaculty() {
  cout << "Enter all of the new information for the faculty member being added: " << endl;
  cout << endl;
  int id = 0;
  cout << "Enter the ID of the faculty: " << endl;
  cin >> id;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> id;
  }
  string facultyName = "";
  cout << "Enter the name of the faculty member: " << endl;
  cin.ignore();
  getline(cin, facultyName);
  string field = "";
  cout << "Enter the field of the student (associate, lecturer etc.): " << endl;
  cin >> field;
  string department = "";
  cout << "Enter the department of the faculty member: " << endl;
  cin.ignore();
  getline(cin, department);
  Faculty *f = new Faculty(id, facultyName, field, department);
  m_masterFaculty->insert(id, f);
  cout << endl;
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
