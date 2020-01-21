#pragma once

#include <string>

#include "../actuators/ActuatorBase.h"

namespace wml {
  namespace actuators {
    enum class BoundedActuatorState { kSeek = 0, kManual };

    class BoundedActuator : public ActuatorBase<BoundedActuatorState, double> {
     public:
      BoundedActuator(std::string name = "<Bounded Actuator>", BoundedActuatorState initialState = kSeek) : StateDevice(name, initialState) {};
      using ActuatorState = BoundedActuatorState;

      virtual std::string GetStateString() final {
        switch (GetMode()) {
         case kSeek:
          return "kSeek";

         case kManual:
          return "kManual";
        }

        return "<state error>";
      };

      virtual void Set(double setpoint) { SetState(kSeek); _setpoint = setpoint; };
      void SetManual(double setpoint) { SetState(kManual); _setpoint = setpoint; };
      
      virtual void Stop() {};
      virtual bool IsDone() { return true; };

      virtual double Get() { return _setpoint; };
      // GetCurrent'Pos' ?

     protected:
      virtual void UpdateActuator(double dt) final {
        switch (GetMode()) {
         case kSeek:
          UpdateSeek(dt);
          break;

         case kManual:
          UpdateManual(dt);
          break;
        }
      };

      virutal void InitSeek() {};
      virtual void UpdateSeek(double dt) = 0;

      virtual void InitManual() {};
      virtual void UpdateManual(double dt) {};

     private:
      double _setpoint;

      virtual void OnStateChange(BoundedActuatorState newState, BoundedActuatorState oldState) { Init(); };
      virtual void OnStatePeriodic(BoundedActuatorState state, double dt) { UpdateActuator(dt); if (IsDone()) Stop(); };
    };
  }
}
