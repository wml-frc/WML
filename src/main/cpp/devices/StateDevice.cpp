#include "devices/StateDevice.h"

using namespace wml::devices;
using namespace wml::devices::functions;

//public

StateDevice::StateDevice(std::string name, std::vector<State*> states, std::vector<Connection<State>> connections) : Named(name) {
  AddState(states);
  AddConnection(connections);
}



// private

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

bool StateDevice::AddConnection(Connection<State> connection) {
  if (connection.original == connection.final) return false;

  if (connection.original == nullptr) return false;
  if (connection.final == nullptr) return false;

  if (_states.count(connection.original) != 1) return false;
  if (_states.count(connection.final) != 1) return false;

  if (_connections.count(connection.original) == 1)
    if (_connections[connection.original].count(connection.final) == 1)
      return false;

  _connections[connection.original][connection.final] = connection;
  return true;
}

std::vector<bool> StateDevice::AddConnection(std::vector<Connection<State>> connections) {
  int connectionsSize = connections.size();
  std::vector<bool> ret(connectionsSize);

  for (int i = 0; i < connectionsSize; i++) ret[i] = AddConnection(connections[i]);

  return ret;
}



// Common Connections:
std::vector<Connection<State>> StateDevice::DualConnection(State *a, State *b, constructorOptions::ConnectionOptions opt = {}) {
  return {
    Connection<State>(a, b, opt),
    Connection<State>(b, a, opt)
  };
}
