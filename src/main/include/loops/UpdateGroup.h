#pragma once

#include <functional>
#include <vector>

#include "loops/LoopSystem.h"

namespace wml {
  namespace loops {
    static auto _dt = std::placeholders::_1;

    class UpdateGroup : public LoopSystem {
     public:
      void Register(LoopSystem *loopSystem, bool dtPriority = false);
      void Register(std::function<void(double)> func);

      virtual void Update(double dt) override;


      // operators, because why not

      void operator()();
      void operator()(double dt);

      UpdateGroup& operator+=(LoopSystem *rhs); // uses default dtPriority
      UpdateGroup& operator+=(std::function<void(double)> rhs);

     private:
      std::vector<std::function<void(double)>> _funcs;
    };
  } // ns loops
} // ns wml
