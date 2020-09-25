#pragma once

#include <functional>
#include <string>

#include "Named.h"

namespace wml {
  namespace devices {
    namespace functions {
      template <typename RT> using R = std::function<RT()>;
      static const R<void> none = R<void>(); // empty function
      static const R<bool> trueConst = []() { return true; }; // always returns true
    } // ns functions

    class State : public Named {
     public:
      State(std::string name = "<State>", functions::R<void> onEnteR = functions::none, functions::R<void> onExitFunc = functions::none) :
        Named(name),
        _onEnteR(onEnteR),
        _onExitFunc(onExitFunc) {};

      functions::R<void> GetOnEnteR() { return _onEnteR; };
      functions::R<void> GetOnExitFunc() { return _onExitFunc; };

     protected:
      functions::R<void> _onEnteR;
      functions::R<void> _onExitFunc;
    };
  }  // ns devices
}  // ns wml
