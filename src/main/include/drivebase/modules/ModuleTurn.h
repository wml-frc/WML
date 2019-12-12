#pragma once

#include <string>

#include "control/PIDController.h"
#include "devices/StateDevice.h"

namespace wml {
  namespace drivebase {
    namespace modules {
      enum class ModuleTurnState { kManual = 0, kDirection, kIdle };

      class ModuleTurn : devices::StateDevice<ModuleTurnState> {
       public:
        ModuleTurn(control::PIDGains gains = { "ModuleTurn Gains" }, bool inverted = false, std::string name = "<ModuleTurn>") : StateDevice(name), _pid(gains), _inverted(inverted) {};

        std::string GetStateString() override;


        void SetManual(double setpoint);

        void Set(double setpoint);
        void SetDirection(double heading);

        void SetIdle();


        double GetSetpoint();
        virtual double GetDirection() = 0;  // required for kDirection

        void SetInverted(bool inverted = false);
        bool GetInverted();

       protected:
        void OnStateChange(ModuleTurnState newState, ModuleTurnState oldState) override;
        void OnStatePeriodic(ModuleTurnState state, double dt) override;

        virtual void OnManual(double setpoint) = 0;
        virtual void OnDirection(double pidOutput) = 0;
        virtual void OnIdle() {};

        virtual void OnInversion(bool newInversion) = 0;

       private:
        control::PIDController _pid;

        double _setpoint = 0;
        bool _inverted;
      };
    }
  }
}
