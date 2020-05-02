#include "FileIO.h"

//initialzie file names for the .bin files
FileIO::FileIO() {
  string studentFile = "studentTable.bin";
  string facultyFile = "facultyTable.bin";
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
    cout << "File doesn't exist. Program will create an empty student table" << endl;
    DBSimulation *simulate = new DBSimulation();
    simulate->userSelection();
    //serialize after user finishes doing everything
    serialize();
  } else {
    //files are not emoty so start deserializing and put into BST member variables
    deserialize();
  }

  inFS.close();
}

//use this method to deserialize the files if they do exist
void FileIO::deserialize() {

  //first do the student file
  inFS.open(m_studentFile);
  Student *s;
  while (inFS.read((char*)&s, sizeof(s))) {
    int key = s->getId(); //get the key before inserting into tree
    studentTable->insert(key, s);
  }

  inFS.close();

  //now read in the faculty file
  inFS.open(m_facultyFile);
  Faculty *f;
  while (inFS.read((char*)&f, sizeof(f))) {
    int key = f->getId(); //get the key before inserting into tree
    facultyTable->insert(key, f);
  }

  inFS.close();

  DBSimulation *simulate = new DBSimulation(studentTable, facultyTable);
  simulate->userSelection();
  //update the trees in this class with the trees that were updated in the database
  studentTable = simulate->getStudentTree();
  facultyTable = simulate->getFacultyTree();
  serialize();
}


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
  o.write((char*)&(node->key), sizeof(node->key));
  traverseStudents(node->right, o);
}

void FileIO::traverseFaculty(TreeNode<Faculty> *node, ofstream &o) {
  if (node == NULL) {
    return;
  }
  traverseFaculty(node->left, o);
  o.write((char*)&(node->key), sizeof(node->key));
  traverseFaculty(node->right, o);
}
