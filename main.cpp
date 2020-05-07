#include "FileIO.h"

int main(int argc, char**argv) {
  FileIO *file = new FileIO();
  file->checkIfEmpty();

  delete file;
  
  return 0;
}
