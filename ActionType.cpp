#include "ActionType.h"

ActionType::ActionType() {
  m_action = "";
}

ActionType::ActionType(string action) {
  m_action = action;
}

ActionType::~ActionType() {

}

string ActionType::getAction() {
  return m_action;
}
