#include "DBSimulation.h"

DBSimulation::DBSimulation() {
  //create two empty BSTs
  m_masterStudent = new BST<Student>();
  m_masterFaculty = new BST<Faculty>();
  m_rollback = new Rollback();
}

DBSimulation::DBSimulation(BST<Student> *student, BST<Faculty> *faculty) {
  m_masterStudent = student;
  m_masterFaculty = faculty;
  m_rollback = new Rollback();
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
    while (cin.fail()) {
      cout << "Wrong data type. Please type in an integer to choose an action from the menu: " << endl;
      cin.clear();
      cin.ignore();
      cin >> userInput;
    }
    cout << endl;
    if (userInput == "1") {
      TreeNode<Student>* root = m_masterStudent->getRootNode();
      if (root == NULL) {
        cout << "Student table is empty!" << endl;
        continue;
      }
      cout << "Here are all of the students in the database: " << endl;
      cout << endl;
      printStudents(root);
    } else if (userInput == "2") {
      TreeNode<Faculty>* root = m_masterFaculty->getRootNode();
      if (root == NULL) {
        cout << "Faculty table is empty!" << endl;
        continue;
      }
      cout << "Here are all of the faculty in the database: " << endl;
      cout << endl;
      printFaculty(root);
    } else if (userInput == "3") {
      cout << "What student ID would you like to look up? Enter it here: " << endl;
      int studentID = 0;
      cin >> studentID;
      while (cin.fail()) {
        cout << "Wrong data type. Please type in an integer for the ID: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
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
      while (cin.fail()) {
        cout << "Wrong data type. Please type in an integer for the ID: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
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
      while (cin.fail()) {
        cout << "Wrong data type. Please type in an integer for the ID: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
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
      while (cin.fail()) {
        cout << "Wrong data type. Please type in an integer for the ID: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
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
  cout << "-------------------------------------------------------------------------------" << endl;
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
  cout << "------------------------------------------------------------------------------" << endl;
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
  if (!advisees->isEmpty()) {
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
  if (!advisees->isEmpty()) {
    advisees->printList();
  }
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
  //Check if the student exists already
  Student *s1 = m_masterStudent->search(id);
  while (s1 != NULL) {
    cout << "This id already exists. Please enter a brand new and unique ID: " << endl;
    cin >> id;
    s1 = m_masterStudent->search(id);
  }
  string studentName = "";
  cout << "Enter the name of the student: " << endl;
  cin.ignore();
  getline(cin, studentName); //use get line because this might have spaces
  string field = "";
  cout << "Enter the field of the student (freshman, sophomore, etc.): " << endl;
  cin >> field;
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
  m_rollback->addStudentAction(s,"delete student");
}

//option 8
void DBSimulation::deleteStudent() {
  printStudents(m_masterStudent->getRootNode());
  if (m_masterStudent->isEmpty()) {
    cout << "The student table is already empty! Can't delete." << endl;
  }
  int id = 0;
  cout << "Enter the ID of the student who you want to delete: " << endl;
  cin >> id;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> id;
  }
  Student *deletedStudent = m_masterStudent->search(id);
  m_rollback->addStudentAction(deletedStudent,"add student");
  while (deletedStudent == NULL) {
    cout << "The faculty ID you entered is invalid. Try again: " << endl;
    cin >> id;
    deletedStudent = m_masterStudent->search(id);
  }
  int facultyID = deletedStudent->getAdvisor();
  displayStudentInfo(deletedStudent);
  bool check = m_masterStudent->deleteNode(id);
  if (check == true) {
    cout << "Successfully deleted this student!" << endl;
  } else {
    cout << "Could not delete this student from the table. " << endl;
  }
  //deleting student from advisor's list
  Faculty *f = m_masterFaculty->search(facultyID);
  int pos = f->getAdvisees()->search(id);
  f->getAdvisees()->removeAtPos(pos);
}

//option 10
void DBSimulation::deleteFaculty() {
  //first check if faculty list is empty before trying to delete it
  if (m_masterFaculty->isEmpty()) {
    cout << "Can't delete a faculty member becasue the table is empty. " << endl;
  } else {
    printFaculty(m_masterFaculty->getRootNode());
    cout << "Enter the ID of the faculty you want to remove: " << endl;
    int id = 0;
    cin >> id;
    while (cin.fail()) {
      cout << "Wrong data type. Please type in an integer for the ID: " << endl;
      cin.clear();
      cin.ignore();
      cin >> id;
    }
    //check if facultyID is valid before trying to remove it
    Faculty *f = m_masterFaculty->search(id);
    while (f == NULL) {
      cout << "The faculty ID you entered is invalid. Try again: " << endl;
      cin >> id;
      f = m_masterFaculty->search(id);
    }
    Faculty *temp = f; //use this temp value to redistribute advisees
    displayFacultyInfo(f);
    m_rollback->addFacultyAction(f,"add faculty");
    bool check = m_masterFaculty->deleteNode(id);
    //after getting valid faculty, need to distribute all of its advisees
    Faculty *newFaculty;
    if (!temp->getAdvisees()->isEmpty()) {
      if (!m_masterFaculty->isEmpty()) {
        //that means we need to redistrubute the advisees before actually deleting the node
        TreeNode<Faculty> *newRoot = m_masterFaculty->getRootNode();
        printFaculty(newRoot);
        cout << "Enter the ID of the faculty you want to give the advisees to: " << endl;
        int newID = 0;
        cin >> newID;
        while (cin.fail()) {
          cout << "Wrong data type. Please type in an integer for the ID: " << endl;
          cin.clear();
          cin.ignore();
          cin >> newID;
        }
        //check if facultyID is valid before trying to remove it
        newFaculty = m_masterFaculty->search(newID);
        while (newFaculty == NULL) {
          cout << "The faculty ID you entered is invalid. Try again: " << endl;
          cin >> id;
          newFaculty = m_masterFaculty->search(newID);
        }
        //found the faculty we're going to use, so redistribute
        ListNode<int> *curr = temp->getAdvisees()->front;
        while (curr != NULL) {
          int currId = curr->data;
          Student *s = m_masterStudent->search(currId);
          s->setAdvisor(newID);
          newFaculty->getAdvisees()->insertFront(currId);
          curr = curr->next;
        }
      } else {
        ListNode<int> *curr = temp->getAdvisees()->front;
        while (curr != NULL) {
          int currId = curr->data;
          Student *s = m_masterStudent->search(currId);
          s->setAdvisor(0);
          curr = curr->next;
        }
      }
    }
    if (check == true) {
      cout << "Successfully deleted this member from the table." << endl;
    } else {
      cout << "Could not delete this faculty from the table. " << endl;
    }
  }
  cout << endl;
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
  //Check if the student exists already
  Faculty *f1 = m_masterFaculty->search(id);
  while (f1 != NULL) {
    cout << "This id already exists. Please enter a brand new and unique ID: " << endl;
    cin >> id;
    f1 = m_masterFaculty->search(id);
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

  //if this new faculty is the root node, check if any students don't have faculty members
  if (f == m_masterFaculty->getRootNode()->value) {
    TreeNode<Student> *root = m_masterStudent->getRootNode();
    iterate(root, f);
  }
  m_rollback->addFacultyAction(f,"delete faculty");
}

//option 11
void DBSimulation::changeStudentAdvisor() {
  printStudents(m_masterStudent->getRootNode());
  cout << endl;
  cout << "Please enter the student's ID whos advisor you would like to change: " << endl;
  //cout << "Enter all of the new information for the student being added: " << endl;
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
  Student *s = m_masterStudent->search(id);
  while (s == NULL) {
    cout << "The faculty ID you entered is invalid. Try again: " << endl;
    cin >> id;
    s = m_masterStudent->search(id);
  }
  int currAdvisor = s->getAdvisor();
  printFaculty(m_masterFaculty->getRootNode());
  cout << "Here are all of the advisors. Enter the id of the advisor you want to switch to: " << endl;
  int idF = 0;
  cin >> idF;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> idF;
  }
  Faculty *f = m_masterFaculty->search(idF);
  while (f == NULL) {
    cout << "The faculty ID you entered is invalid. Try again: " << endl;
    cin >> id;
    f = m_masterFaculty->search(id);
  }
  //Remove student from the old advisor's list
  Faculty *oldF = m_masterFaculty->search(currAdvisor);
  int pos = oldF->getAdvisees()->search(id);
  cout << "SIZE: " << oldF->getAdvisees()->getSize() << endl;
  cout << "POSITION: " << pos << endl;
  oldF->getAdvisees()->removeAtPos(pos);
  //Set student advisor to the new faculty ID
  m_masterStudent->search(id)->setAdvisor(idF);
  //Add student to new advisor's list
  Faculty *newf = m_masterFaculty->search(idF);
  newf->getAdvisees()->insertFront(id);
  cout << "Successfuly changed advisors!" << endl;
}

//option 12
void DBSimulation::removeAdvisee() {
  //deleting student from advisor's list
  printFaculty(m_masterFaculty->getRootNode());
  cout << endl;
  cout << "Enter the faculty ID that you want to remove the student from: " << endl;
  int id = 0;
  cin >> id;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> id;
  }
  Faculty *f = m_masterFaculty->search(id);
  while (f == NULL) {
    cout << "The faculty ID you entered is invalid. Try again: " << endl;
    cin >> id;
    f = m_masterFaculty->search(id);
  }
  //now ask which student you want to delete
  f->getAdvisees()->printList();
  cout << "Here are their advisees. Enter the id of the student you want to remove: " << endl;
  int sID = 0;
  cin >> sID;
  while (cin.fail()) {
    cout << "Wrong data type. Please type in an integer for the ID: " << endl;
    cin.clear();
    cin.ignore();
    cin >> sID;
  }
  int pos = f->getAdvisees()->search(sID);
  f->getAdvisees()->removeAtPos(pos);
  //set student advisor to 0 since they're getting removed from list
  m_masterStudent->search(sID)->setAdvisor(0);
  cout << "Sucessfully removed advisee!" << endl;
}

//option 13
void DBSimulation::rollback() {
  if (m_rollback->checkIfEmpty()) {
    cout << "There are no actions to undo." << endl;
  } else {
    string action = m_rollback->undoAction();
    if (action == "add student") {
      Student *s = m_rollback->popStudent();
      addStudentRollback(s);
      cout << "Successfully did a rollback and added the student that you just deleted." << endl;
      cout << endl;
    } else if (action == "delete student") {
      Student *s = m_rollback->popStudent();
      deleteStudentRollback(s);
      cout << "Successfully did a rollback and deleted the student that you just added." << endl;
      cout << endl;
    } else if (action == "add faculty") {
      Faculty *f = m_rollback->popFaculty();
      addFacultyRollback(f);
      cout << "Successfully did a rollback and added the faculty that you just deleted." << endl;
      cout << endl;
    } else if (action == "delete faculty") {
      Faculty *f = m_rollback->popFaculty();
      deleteFacultyRollback(f);
      cout << "Successfully did a rollback and deleted the faculty that you just added." << endl;
      cout << endl;
    }
  }
}

//option 14
void DBSimulation::exit() {
  //check if the students temp list has IDs in it
  cout << "Exiting the program and serializing databases into the files." << endl;
}

BST<Student>* DBSimulation::getStudentTree() {
  return m_masterStudent;
}

BST<Faculty>* DBSimulation::getFacultyTree() {
  return m_masterFaculty;
}

void DBSimulation::iterate(TreeNode<Student> *node, Faculty* f) {
  if (node != NULL) {
    iterate(node->left, f);
    Student* s = node->value;
    if (s->getAdvisor() == 0) {
      s->setAdvisor(f->getId());
      f->getAdvisees()->insertFront(s->getId());
    }
    iterate(node->right, f);
  }
}

void DBSimulation::deleteStudentRollback(Student *s) {
  int id = s->getId();
  int facultyID = s->getAdvisor();
  bool check = m_masterStudent->deleteNode(id);

  //deleting student from advisor's list
  Faculty *f = m_masterFaculty->search(facultyID);
  int pos = f->getAdvisees()->search(id);
  f->getAdvisees()->removeAtPos(pos);
}

void DBSimulation::deleteFacultyRollback(Faculty *f) {
  int id = f->getId();
  bool check = m_masterFaculty->deleteNode(id);


  Faculty *temp = f; //use this temp value to redistribute advisees
  //after getting valid faculty, need to distribute all of its advisees
  Faculty *newFaculty;
  if (!temp->getAdvisees()->isEmpty()) {
    if (!m_masterFaculty->isEmpty()) {
      //that means we need to redistrubute the advisees before actually deleting the node
      TreeNode<Faculty> *newRoot = m_masterFaculty->getRootNode();
      printFaculty(newRoot);
      cout << "Enter the ID of the faculty you want to give the advisees to: " << endl;
      int newID = 0;
      cin >> newID;
      while (cin.fail()) {
        cout << "Wrong data type. Please type in an integer for the ID: " << endl;
        cin.clear();
        cin.ignore();
        cin >> newID;
      }
      //check if facultyID is valid before trying to remove it
      newFaculty = m_masterFaculty->search(newID);
      while (newFaculty == NULL) {
        cout << "The faculty ID you entered is invalid. Try again: " << endl;
        cin >> id;
        newFaculty = m_masterFaculty->search(newID);
      }
      //found the faculty we're going to use, so redistribute
      ListNode<int> *curr = temp->getAdvisees()->front;
      while (curr != NULL) {
        int currId = curr->data;
        Student *s = m_masterStudent->search(currId);
        s->setAdvisor(newID);
        newFaculty->getAdvisees()->insertFront(currId);
        curr = curr->next;
      }
    } else {
      ListNode<int> *curr = temp->getAdvisees()->front;
      while (curr != NULL) {
        int currId = curr->data;
        Student *s = m_masterStudent->search(currId);
        s->setAdvisor(0);
        curr = curr->next;
      }
    }
  }
  cout << endl;
}

void DBSimulation::addStudentRollback(Student *s) {
  m_masterStudent->insert(s->getId(), s);
  int facultyID = s->getAdvisor();
  if (facultyID != 0) {
    Faculty *f = m_masterFaculty->search(facultyID);
    f->getAdvisees()->insertFront(s->getId());
  }
}

void DBSimulation::addFacultyRollback(Faculty *f) {
  m_masterFaculty->insert(f->getId(), f);
  LinkedList<int> *advis = f->getAdvisees();
  ListNode<int> *curr = advis->front;
  while (curr != NULL) {
    int studentID = curr->data;
    Student *s = m_masterStudent->search(studentID);
    s->setAdvisor(f->getId());
    curr = curr->next;
  }
}
