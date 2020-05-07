#include <iostream>
using namespace std;

class ActionType {
  public:
    ActionType();
    ActionType(string action);
    ~ActionType();

    string getAction();

  private:
    string m_action;
};
