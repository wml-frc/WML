#include "devices/StateDevice.h"

using namespace wml::devices;

bool StateDevice::AddState(State *state) {
  if (state == nullptr) return false;
  if (_states.count(state) != 0) return false;

  _states[state] = state;
  return true;
}

bool StateDevice::AddConnection(StateConnection connection) {
  if (connection.originalState == connection.finalState) return false;

  if (connection.originalState == nullptr) return false;
  if (connection.finalState == nullptr) return false;

  if (_states.count(connection.originalState) != 1) return false;
  if (_states.count(connection.finalState) != 1) return false;

  if (_stateConnections.count(connection.originalState) == 1)
    if (_stateConnections.at(connection.originalState).count(connection.finalState) == 1)
      return false;

  _stateConnections.at(connection.originalState)[connection.finalState] = connection.func;
  return true;
}
