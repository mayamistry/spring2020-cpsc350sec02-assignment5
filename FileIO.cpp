#include "FileIO.h"

//initialzie file names for the .bin files
FileIO::FileIO() {
  m_studentFile = "studentTable.bin";
  m_facultyFile = "facultyTable.bin";
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

    // Student *s = studentTable->getRootNode()->value;
    // outFS.open(m_studentFile);
    // cout << "Seg fault 1" << endl;
    // outFS.write((char*)&s,sizeof(*s));
    // outFS.close();


  } else {
    //files are not empty so start deserializing and put into BST member variables
    inFS.close();
    deserialize();
    // Student *s1;
    // cout << "Seg fault 2" << endl;
    // inFS.open(m_studentFile);
    // inFS.read((char*)&s1, sizeof(*s1));
    // inFS.close();
    //
    // cout << "Seg fault 3" << endl;
    // cout << s1->getName() << endl;
    // cout << s1->getId() << endl;
  }


  // Student *s0 = new Student(12,"Jessie","Frsh","CS",3.8,2);
  // studentTable->insert(12,s0);
  // Student *s = studentTable->getRootNode()->value;
  //
  // ofstream outFS;
  //
  // outFS.open(m_studentFile);
  //
  // outFS.write((char*)&s,sizeof(s));
  // outFS.close();
  // ifstream inFS;
  // inFS.open(m_studentFile);
  // Student *s1;
  // inFS.read((char*)&s1, sizeof(s1));
  // inFS.close();
  //
  // cout << s1->getName() << endl;
  // cout << s1->getId() << endl;
}

//use this method to deserialize the files if they do exist
//DESERIALIZE DOESN'T WORK
void FileIO::deserialize() {

  //first do the student file
  inFS.open(m_studentFile);
  Student* s;
  inFS.read((char*)&s, sizeof(*s));
  inFS.close();



  cout << s->getName() << endl;
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
  remove("studentTable.bin");
  remove("facultyTable.bin");

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
  Student s = *node->value;
  o.write((char*)&s, sizeof(s));
  traverseStudents(node->right, o);
}

void FileIO::traverseFaculty(TreeNode<Faculty> *node, ofstream &o) {
  if (node == NULL) {
    return;
  }
  traverseFaculty(node->left, o);
  Faculty f = *node->value;
  o.write((char*)&f, sizeof(f));
  traverseFaculty(node->right, o);
}
