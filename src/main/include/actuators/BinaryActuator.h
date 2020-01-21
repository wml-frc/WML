#pragma once

#include <string>

#include "../actuators/ActuatorBase.h"

namespace wml {
  namespace actuators {
    enum class BinaryActuatorState { kReverse = 0, kForward };

    class BinaryActuator : public BoundedActuator<BinaryActuatorState, BinaryActuatorState> {
     public:
      BinaryActuator(std::string name = "<Binary Actuator>", BinaryActuatorState initialState = kReverse) : StateDevice(name, initialState) {};
      using ActuatorState = BinaryActuatorState;

      virtual std::string GetStateString() final {
        switch (Get()) {
         case kReverse:
          return "kReverse";

         case kForward:
          return "kForward";
        }

        return "<state error>";
      };

      void Set(BinaryActuatorState state) { SetState(state); if (_lastState != _state) Init(); };
      virtual void Stop() override {};
      virtual bool IsDone() override { return true; };

      virtual BinaryActuatorState Get() override { return GetState(); };

     protected:
      virtual void InitBinaryActuator(BinaryActuatorState newState, BinaryActuatorState oldState) {};
      virtual void UpdateBinaryActuator(double dt) {};

     private:
      virtual void InitActuatorBase(BinaryActuatorState newState, BinaryActuatorState oldState) final { InitBinaryActuator(newState, oldState); };
      virtual void UpdateActuatorBase(double dt) final { UpdateBinaryActuator(dt); };
    };
  } // ns actuators
} // ns wml
