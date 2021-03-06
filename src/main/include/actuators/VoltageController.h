#pragma once

#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <frc/SpeedControllerGroup.h>

namespace wml {
namespace actuators { 
  /**
   * A VoltageController is analagous to a SpeedController, but in terms of voltage instead
   * of speed.
   */
  class VoltageController {
   public:
    /**
     * Set the voltage of the output.
     */
    virtual void SetVoltage(double voltage) = 0;
    /**
     * Get the voltage of the output.
     */
    virtual double GetVoltage() = 0;

    /**
     * Set the output as inverted.
     */
    virtual void SetInverted(bool invert) = 0;
    /**
     * Get whether the output is inverted
     */
    virtual bool GetInverted() = 0;

    /**
     * Get the physical port of the Voltage Controller.
     */
    virtual int GetPhysicalPort() = 0;

    /**
     * Get the current output.
     */
    virtual double GetCurrent() { return frc::PowerDistributionPanel(0).GetCurrent(GetPhysicalPort()); };
  };

  /**
   * The MotorVoltageController is an adapter for an frc::SpeedController to
   * a VoltageController.
   */
  class MotorVoltageController : public VoltageController {
   public:
    MotorVoltageController(frc::SpeedController *speedController);

    void SetVoltage(double voltage) override;
    double GetVoltage() override;

    void SetInverted(bool invert) override;
    bool GetInverted() override;

    virtual int GetPhysicalPort() override { return -1; }; // override me!

    double GetBusVoltage();

    /**
     * Create a MotorVoltageController with a given frc::SpeedController
     * subclass. Please note that this creates an unsafe pointer (will never dealloc)
     */
    template<typename T, typename ...Args>
    static MotorVoltageController Of(Args& ...args) {
      T *t = new T(args...);  // Be warned, does not deallocate!
      return MotorVoltageController{t};
    }

    template<typename ...Args>
    static MotorVoltageController Group(Args& ...args) {
      return Of<frc::SpeedControllerGroup>(args...);
    }

   private:
    frc::SpeedController *_speedController;
  };
}
}  // namespace wml