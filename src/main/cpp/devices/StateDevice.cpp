#include "devices/StateDevice.h"

using namespace wml::devices;

bool StateDevice::AddState(State *state) {
  if (state == nullptr) return false;
  if (_states.count(state) != 0) return false;

  _states[state] = state;
  return true;
}

std::vector<bool> StateDevice::AddState(std::vector<State*> states) {
  int statesSize = states.size();
  std::vector<bool> ret(statesSize);

  for (int i = 0; i < statesSize; i++) ret[i] = AddState(states[i]);

  return ret;
}

bool StateDevice::AddConnection(StateDevice::StateConnection connection) {
  if (connection.originalState == connection.finalState) return false;

  if (connection.originalState == nullptr) return false;
  if (connection.finalState == nullptr) return false;

  if (_states.count(connection.originalState) != 1) return false;
  if (_states.count(connection.finalState) != 1) return false;

  if (_stateConnections.count(connection.originalState) == 1)
    if (_stateConnections[connection.originalState].count(connection.finalState) == 1)
      return false;

  _stateConnections[connection.originalState][connection.finalState] = connection.func;
  return true;
}

std::vector<bool> StateDevice::AddConnection(std::vector<StateDevice::StateConnection> connections) {
  int connectionsSize = connections.size();
  std::vector<bool> ret(connectionsSize);

  for (int i = 0; i < connectionsSize; i++) ret[i] = AddConnection(connections[i]);

  return ret;
}



// Common Connections:
std::vector<StateDevice::StateConnection> StateDevice::DualConnection(State *a, State *b, SDFunc<bool> onChange) {
  return { StateDevice::StateConnection(a, b, onChange), StateDevice::StateConnection(b, a, onChange) };
}
