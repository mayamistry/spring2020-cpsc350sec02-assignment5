#include "DBSimulation.h"
#include <fstream>

class FileIO {
public:
  FileIO();
  ~FileIO();

  void checkIfEmpty();
  void deserialize(); //read in objects from file if they exist
  void serialize(); //writing objects to the file

  void traverseStudents(TreeNode<Student> *node, ofstream &o);
  void traverseFaculty(TreeNode<Faculty> *node, ofstream &o);

private:
  ifstream inFS;
  ofstream outFS;
  string m_studentFile;
  string m_facultyFile;
  BST<Student> *studentTable;
  BST<Faculty> *facultyTable;
};
