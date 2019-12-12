#pragma once

#include <string>

#include "devices/StateDevice.h"

namespace wml {
  namespace drivebase {
    namespace modules {
      enum class ModuleMoveState { kManual = 0, kIdle };

      class ModuleMove : devices::StateDevice<ModuleMoveState> {
       public:
        ModuleMove(bool inverted = false, std::string name = "<ModuleMove>") : StateDevice(name), _inverted(inverted) {};

        std::string GetStateString() override;


        void Set(double setpoint);
        void SetIdle();


        double GetSetpoint();
        virtual double GetSpeed() { return GetSetpoint(); };    // Override if you have some way of actually telling the speed of the module

        void SetInverted(bool inverted = false);
        bool GetInverted();

       protected:
        void OnStatePeriodic(ModuleMoveState state, double dt) override;

        virtual void OnManual(double setpoint) = 0;
        virtual void OnIdle() {};

        virtual void OnInversion(bool newInversion) = 0;

       private:
        double _setpoint = 0;
        bool _inverted;
      };
    }
  }
}
