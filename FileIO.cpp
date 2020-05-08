#include "FileIO.h"

//initialzie file names for the .bin files
FileIO::FileIO() {
  m_studentFile = "studentTable.txt";
  m_facultyFile = "facultyTable.txt";
  studentTable = new BST<Student>();
  facultyTable = new BST<Faculty>();
}

FileIO::~FileIO() {
  delete studentTable;
  delete facultyTable;
}

//need to check if files are empty before proceeding
void FileIO::checkIfEmpty() {
  inFS.open(m_studentFile);
  //if the student file doesn't exist, that means the faculty one doesn't either

  if (!inFS.is_open()) {
    inFS.close();
    cout << "Files don't exist. Program will create an empty student and faculty table" << endl;
    DBSimulation *simulate = new DBSimulation();
    cout << endl;
    cout << "NOTICE: Since database is empty, insert new faculty members first before adding students!!" << endl;
    simulate->userSelection();
    //serialize after user finishes doing everything

    studentTable = simulate->getStudentTree();
    facultyTable = simulate->getFacultyTree();
    serialize();

  } else {
    //files are not empty so start deserializing and put into BST member variables
    inFS.close();
    deserialize();
  }
}

//use this method to deserialize the files if they do exist
//DESERIALIZE DOESN'T WORK
void FileIO::deserialize() {

  //first do the student file
  inFS.open(m_studentFile);
  string currLine = "";

  while (!inFS.eof()) {
    getline(inFS, currLine);
    if(!inFS.fail()) {
      int size = currLine.size();
      //input the name first
      string idTemp = "";
      string name = "";
      string level = "";
      string major = "";
      string gpaTemp = "";
      string advisorTemp = "";
      bool idCheck = false;
      bool nameCheck = false;
      bool levelCheck = false;
      bool majorCheck = false;
      bool gpaCheck = false;
      bool advisorCheck = false;
      //Input the id
      int i = 0;
      while (!idCheck) {
        if (currLine[i] == '|') {
          ++i;
          idCheck = true;
          break;
        } else {
          idTemp += currLine[i];
          ++i;
        }
      }
      //Input the name
      while (!nameCheck) {
        if (currLine[i] == '|') {
          ++i;
          nameCheck = true;
          break;
        } else {
          name += currLine[i];
          ++i;
        }
      }
      //Input the level
      while (!levelCheck) {
        if (currLine[i] == '|') {
          ++i;
          levelCheck = true;
          break;
        } else {
          level += currLine[i];
          ++i;
        }
      }
      //Input the major
      while (!majorCheck) {
        if (currLine[i] == '|') {
          ++i;
          majorCheck = true;
          break;
        } else {
          major += currLine[i];
          ++i;
        }
      }
      //Input the gpa
      while (!gpaCheck) {
        if (currLine[i] == '|') {
          ++i;
          gpaCheck = true;
          break;
        } else {
          gpaTemp += currLine[i];
          ++i;
        }
      }
      while (!advisorCheck) {
        if (currLine[i] == '|') {
          ++i;
          advisorCheck = true;
          break;
        } else {
          advisorTemp += currLine[i];
          ++i;
        }
      }
      //Input the advisor
      int id = stoi(idTemp);
      double gpa = stof(gpaTemp);
      int advisor = stoi(advisorTemp);
      Student *s = new Student(id, name, level, major, gpa, advisor);
      studentTable->insert(id, s);
    }
  }

  inFS.close();

  //then do the faculty file
  inFS.open(m_facultyFile);

  string currLine1 = "";

  while (!inFS.eof()) {
    getline(inFS, currLine1);
    if(!inFS.fail()) {
      int size = currLine1.size();
      //input the name first
      string idTemp = "";
      string name = "";
      string level = "";
      string department = "";
      string advisee = "";
      LinkedList<int> *advisees = new LinkedList<int>();
      bool idCheck = false;
      bool nameCheck = false;
      bool levelCheck = false;
      bool departmentCheck = false;
      bool adviseesCheck = false;
      //Input the id
      int i = 0;
      while (!idCheck) {
        if (currLine1[i] == '|') {
          ++i;
          idCheck = true;
          break;
        } else {
          idTemp += currLine1[i];
          ++i;
        }
      }
      //Input the name
      while (!nameCheck) {
        if (currLine1[i] == '|') {
          ++i;
          nameCheck = true;
          break;
        } else {
          name += currLine1[i];
          ++i;
        }
      }
      //Input the level
      while (!levelCheck) {
        if (currLine1[i] == '|') {
          ++i;
          levelCheck = true;
          break;
        } else {
          level += currLine1[i];
          ++i;
        }
      }
      //Input the department
      while (!departmentCheck) {
        if (currLine1[i] == '|') {
          ++i;
          departmentCheck = true;
          break;
        } else {
          department += currLine1[i];
          ++i;
        }
      }
      //Input the advisees
      //first check if list is empty
      if (currLine[i] == 'e') {
        //then do nothing
        adviseesCheck == true;
      }
      while (!adviseesCheck) {
        if (currLine1[i] == '|') {
          ++i;
          adviseesCheck = true;
          break;
        } else if (currLine1[i] != ' ') {
          advisee += currLine1[i];
          ++i;
        } else {
          int a = stoi(advisee);
          advisees->insertFront(a);
          advisee = "";
          ++i;
        }
      }
      int id = stoi(idTemp);
      Faculty *f = new Faculty(id, name, level, department);
      f->setAdvisees(advisees);
      facultyTable->insert(id, f);
    }
  }

  inFS.close();
  //
  //
  // int key = s->getId();
  // studentTable->insert(key, s);


  // cout << "Check 2" << endl;
  // while (inFS.good()) {
  //   Student *s;
  //   cout << "Check 3" << endl;
  //   inFS.read((char*)&s, sizeof(*s));
  //   cout << "Check 4" << endl;
  //   if (inFS.good()) {
  //     cout << "Check 5" << endl;
  //     int key = s->getId();
  //     cout << "Check 6" << endl;
  //     studentTable->insert(key,s);
  //   }
  // }




  // //now read in the faculty file
  // inFS.open(m_facultyFile);
  // Faculty *f;
  // inFS.read((char*)&f, sizeof(f));
  // inFS.close();
  //
  // int key1 = f->getId();
  // facultyTable->insert(key1, f);

  DBSimulation *simulate = new DBSimulation(studentTable, facultyTable);
  simulate->userSelection();
  //update the trees in this class with the trees that were updated in the database
  studentTable = simulate->getStudentTree();
  facultyTable = simulate->getFacultyTree();

  //remove contents from binary files before serializing
  remove("studentTable.txt");
  remove("facultyTable.txt");

  serialize();
}


//I think serialize doesn't work right now
void FileIO::serialize() {
  //first serialize the studentTable
  outFS.open(m_studentFile);
  TreeNode<Student>* root = studentTable->getRootNode();
  traverseStudents(root, outFS);

  outFS.close();

  //then serialize the facultyTable
  outFS.open(m_facultyFile);
  TreeNode<Faculty>* root1 = facultyTable->getRootNode();
  traverseFaculty(root1, outFS);

  outFS.close();
}

void FileIO::traverseStudents(TreeNode<Student> *node, ofstream &o) {
  if (node == NULL) {
    return;
  }
  traverseStudents(node->left, o);
  Student *s = node->value;
  //o.write((char*)&s, sizeof(s));
  o << s->getId() << "|" << s->getName() << "|" << s->getLevel() << "|" << s->getMajor() << "|" << s->getGpa() << "|" << s->getAdvisor() << "|" << endl;
  traverseStudents(node->right, o);
}

void FileIO::traverseFaculty(TreeNode<Faculty> *node, ofstream &o) {
  if (node == NULL) {
    return;
  }
  traverseFaculty(node->left, o);
  Faculty *f = node->value;
  //o.write((char*)&f, sizeof(f));
  o << f->getId() << "|" << f->getName() << "|" << f->getLevel() << "|" << f->getDepartment() << "|" << f->adviseesForFile() << "|" << endl;
  traverseFaculty(node->right, o);
}
