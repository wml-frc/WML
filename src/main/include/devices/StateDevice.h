#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Named.h"
#include "devices/State.h"
#include "devices/Connection.h"

namespace wml {
  namespace devices {
    class StateDevice : public Named {
     public:
      StateDevice(std::string name, std::vector<State*> states, std::vector<Connection<State>> connections);
      StateDevice(std::vector<State*> states, std::vector<Connection<State>> connections) : StateDevice("<StateDevice>", states, connections) {};


      // statics - i.e. common connections
      static std::vector<Connection<State>> DualConnection(State *a, State *b, constructorOptions::ConnectionOptions opt);

     protected:
      std::map<State*, State*> _states;
      std::map<State*, std::map<State*, Connection<State>>> _connections; // state -> state -> bool()

     private:
      bool AddState(State *state);
      std::vector<bool> AddState(std::vector<State*> states);

      bool AddConnection(Connection<State> connection);
      std::vector<bool> AddConnection(std::vector<Connection<State>> connections);
    };
  }  // ns devices
}  // ns wml
