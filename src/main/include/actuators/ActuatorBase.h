#pragma once

#include "../devices/StateDevice.h"

namespace wml {
  namespace actuators {
    template <typename StateName, typename SetType>
    class ActuatorBase : public devices::StateDevice<StateName> {
     public:
      ActuatorBase(std::string name = "<Actuator Base>", StateName initialState = (StateName)0) : StateDevice(name, initialState) {};

      virtual std::string GetStateString() = 0;

      virtual void Set(SetType setpoint) = 0;
      virtual SetType Get() = 0;

      virtual bool IsDone() = 0;
      virtual void Stop() = 0;

     protected:
      virtual void InitActuatorBase(StateName newState, StateName oldState) = 0;
      virtual void UpdateActuatorBase(double dt) = 0;

     private:
      virtual void OnStateChange(StateName newState, StateName oldState) { InitActuatorBase(newState, oldState); };
      virtual void OnStatePeriodic(StateName state, double dt) { UpdateActuatorBase(dt); if (IsDone()) Stop(); };
    };
  }
}
