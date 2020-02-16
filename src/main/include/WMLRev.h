#pragma once

#ifdef  __WML__REV__

#include <frc/SpeedController.h>
#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>

#include <functional>

#include "sensors/Encoder.h"
#include "actuators/VoltageController.h"

namespace wml {
  /**
   * Wrapper around the REV SPARK MAX
   */
  class SparkMax : public wml::actuators::MotorVoltageController, public frc::SpeedController, public wml::sensors::Encoder {
   public:
    enum class MotorType {
      kBrushed = (int)rev::CANSparkMax::MotorType::kBrushed,
      kBrushless = (int)rev::CANSparkMax::MotorType::kBrushless,

      kNEO = kBrushless,
    };

    /**
     * Create a new SPARK MAX.
     * 
     * @param port The device ID of the SPARK MAX on the CAN Bus.
     */
    SparkMax(int port, MotorType motorType, rev::CANEncoder::EncoderType encoderType, int encoderTicksPerRotation);
    SparkMax(int port, MotorType motorType, int encoderTicksPerRotation = -1);
    // ~SparkMax();

    /**
     * Get the CAN Device ID of the SPARK MAX.
     */
    int GetPort();

    /**
     * Set or unset this SPARK MAX as 'inverted' for all calls to .Set().
     */
    void SetInverted(bool invert) override;

    /**
     * Get whether this SPARK MAX is inverted.
     */
    bool GetInverted() const override;

    /**
     * Stop the motor
     */
    void Disable() override;

    /**
     * Stop the motor
     */
    void StopMotor() override;

    void PIDWrite(double output) override;

    /**
     * Set the speed of the SPARK MAX, in the range -1 Full Reverse, 0 Neutral and 1 Full Forward
     * 
     * @param speed The speed. -1 Full Reverse, 0 Neutral, 1 Full Forward 
     */
    void Set(double speed) override;

    /**
     * Get the current value of the SPARK MAX.
     * 
     * @returns The value of the motor controller.
     */
    double Get() const override;

    /**
     * Get the current sensor position, in rotations.
     * 
     * @return The current sensor position, in rotations.
     */
    double GetSensorPosition();

    /**
     * Get the current sensor velocity, in RPM.
     * 
     * @return The current sensor velocity, in RPM.
     */
    double GetSensorVelocity();

    int GetEncoderRawTicks() override;
    double GetEncoderTickVelocity() override;
    void ZeroEncoder() override;
    
   private:
    rev::CANSparkMax _handle;
    rev::CANEncoder *_encoder = nullptr;
    
    int _port;
    MotorType _motorType;
    double _value;
  };

}

#endif
