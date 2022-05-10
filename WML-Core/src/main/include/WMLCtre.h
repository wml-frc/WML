// ~~Bindings to CTRE's Phoenix API, since they don't provide working simulation builds.~~
// ~~See src/main/cpp, src/robot/cpp, and src/simulation/cpp for implementations.~~

#pragma once

#include <frc/motorcontrol/MotorController.h>

#ifndef Phoenix_No_WPI
#define Phoenix_WPI
#endif

#include "ctre/phoenix/CANifier.h"
#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
#include "ctre/phoenix/HsvToRgb.h"
#include "ctre/phoenix/LinearInterpolation.h"
#include "ctre/phoenix/led/CANdle.h"
#include "ctre/phoenix/motion/BufferedTrajectoryPointStream.h"
#include "ctre/phoenix/motion/MotionProfileStatus.h"
#include "ctre/phoenix/motion/TrajectoryPoint.h"
#include "ctre/phoenix/motorcontrol/can/TalonFX.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/DemandType.h"
#include "ctre/phoenix/motorcontrol/Faults.h"
#include "ctre/phoenix/motorcontrol/FollowerType.h"
#include "ctre/phoenix/motorcontrol/IMotorController.h"
#include "ctre/phoenix/motorcontrol/IMotorControllerEnhanced.h"
#include "ctre/phoenix/motorcontrol/InvertType.h"
#include "ctre/phoenix/motorcontrol/SensorCollection.h"
#include "ctre/phoenix/music/Orchestra.h"
#include "ctre/phoenix/sensors/CANCoder.h"
#include "ctre/phoenix/sensors/PigeonIMU.h"
#include "ctre/phoenix/sensors/Pigeon2.h"
#include "ctre/phoenix/signals/MovingAverage.h"
#include "ctre/phoenix/tasking/Schedulers/ConcurrentScheduler.h"
#include "ctre/phoenix/tasking/ILoopable.h"
#include "ctre/phoenix/tasking/IProcessable.h"
#include "ctre/phoenix/Utilities.h"

#ifdef Phoenix_WPI
#include "ctre/phoenix/motorcontrol/can/WPI_TalonFX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h"
#include "ctre/phoenix/sensors/WPI_CANCoder.h"
#include "ctre/phoenix/sensors/WPI_PigeonIMU.h"
#include "ctre/phoenix/sensors/WPI_Pigeon2.h"
#include "ctre/phoenix/tasking/ButtonMonitor.h"
#endif

#include <functional>

#include "sensors/Encoder.h"
#include "actuators/Port.h"
#include "actuators/VoltageController.h"

#define WML_CTRE_CAN ctre::phoenix::motorcontrol::can

namespace wml {

  /**
   * Wrapper around the CTRE Talon SRX.
   */
  class TalonSrx : public wml::actuators::MotorVoltageController, public frc::MotorController, public wml::sensors::Encoder {
   public:
    using Configuration = ctre::phoenix::motorcontrol::can::TalonSRXConfiguration;
    using ControlMode = ctre::phoenix::motorcontrol::ControlMode;

    /**
     * Create a new Talon SRX.
     * 
     * @param port The device ID of the Talon SRX on the CAN Bus (and on the PDP (optional)).
     */
    TalonSrx(actuators::Port port, int encoderTicksPerRotation = 2048);
    ~TalonSrx();

    /**
     * Set the Talon SRX Packet Update Rate in Hz
     */
    void SetUpdateRate(int hz);

    /**
     * Get the CAN Device ID (and Physical Port) of the Talon SRX.
     */
    actuators::Port GetPort();

    // Override
    virtual int GetPhysicalPort() override { return GetPort()._PDP; };

    /**
     * Set or unset this Talon SRX as 'inverted' for all calls to .Set().
     */
    void SetInverted(bool invert) override;

    /**
     * Get whether this Talon SRX is inverted.
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

    /**
     * Set the speed of the Talon SRX, in the range -1 Full Reverse, 0 Neutral and 1 Full Forward
     * 
     * @param speed The speed. -1 Full Reverse, 0 Neutral, 1 Full Forward 
     */
    void Set(double speed) override;
    
    /**
     * Set the value of the Talon SRX in a given control mode. 
     * 
     * @param mode The control mode of the Talon SRX. See @ref ControlMode.
     * @param value The value to set. Units dependent on value of mode.
     */
    void Set(ControlMode mode, double value);

    /**
     * Get the currently active control mode of the Talon SRX.
     * 
     * @returns The control mode of the Talon SRX. See @ref ControlMode.
     */
    ControlMode GetMode();

    /**
     * Get the current value of the Talon SRX.
     * 
     * @returns The value of the motor controller, dependent on the active control mode.
     */
    double Get() const override;

    /**
     * Get the supply current to the Talon SRX.
     * 
     * @returns The supply current for the Talon SRX. Should be identical to the value from the PDP.
     */
    virtual double GetCurrent() override;

    /**
     * Get the current sensor position, in encoder ticks.
     * 
     * @return The current sensor position, in encoder ticks.
     */
    int GetSensorPosition();

    /**
     * Get the current sensor velocity, in encoder ticks per 100 millisecond.
     * 
     * @return The current sensor velocity, in encoder ticks per 100 millisecond.
     */
    int GetSensorVelocity();

    int GetEncoderRawTicks() override;
    double GetEncoderTickVelocity() override;
    void ZeroEncoder() override;


    /**
     * Load a talon Configuration.
     * 
     * @param Configuration The talon Configuration
     */
    void LoadConfig(Configuration &config);

    /**
     * Save (get) the current talon Configuration
     * 
     * @returns The current talon Configuration
     */
    Configuration SaveConfig();

    /**
     * Modify a talon Configuration. This is the equivilent of calling @ref SaveConfig(), changing
     * a value, followed by @ref LoadConfig(Configuration &).
     * 
     * @param func The Configuration function. This is a function that takes in a Configuration reference.
     */
    void ModifyConfig(std::function<void(Configuration &)> func);
    
    actuators::Port _port;
    void *_handle;
    double _value;
  };

  /**
   * Curtin FRC Wrapper around the CTRE Victor SPX.
   */
  class VictorSpx : public wml::actuators::MotorVoltageController, public frc::MotorController {
   public:
    using Configuration = ctre::phoenix::motorcontrol::can::VictorSPXConfiguration;
    using ControlMode = ctre::phoenix::motorcontrol::ControlMode;

    /**
     * Create a new Victor SPX.
     * 
     * @param port The device ID of the Victor SPX on the CAN Bus.
     */
    VictorSpx(actuators::Port port);
    ~VictorSpx();

    /**
     * Set the Victor SPX Packet Update Rate in Hz
     */
    void SetUpdateRate(int hz);

    /**
     * Get the CAN Device ID (and Physical Port) of the Victor SPX.
     */
    actuators::Port GetPort();

    // Override
    virtual int GetPhysicalPort() override { return GetPort()._PDP; };

    /**
     * Set or unset this Victor SPX as 'inverted' for all calls to .Set().
     */
    void SetInverted(bool invert) override;

    /**
     * Get whether this Victor SPX is inverted.
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

    /**
     * Set the speed of the Victor SPX, in the range -1 Full Reverse, 0 Neutral and 1 Full Forward
     * 
     * @param speed The speed. -1 Full Reverse, 0 Neutral, 1 Full Forward 
     */
    void Set(double speed) override;
    
    /**
     * Set the value of the Victor SPX in a given control mode. 
     * 
     * @param mode The control mode of the Victor SPX. See @ref ControlMode.
     * @param value The value to set. Units dependent on value of mode.
     */
    void Set(ControlMode mode, double value);

    /**
     * Get the currently active control mode of the Victor SPX.
     * 
     * @returns The control mode of the Victor SPX. See @ref ControlMode.
     */
    ControlMode GetMode();

    /**
     * Get the current value of the Victor SPX.
     * 
     * @returns The value of the motor controller, dependent on the active control mode.
     */
    double Get() const override;

    /**
     * Load a victor Configuration.
     * 
     * @param Configuration The victor Configuration
     */
    void LoadConfig(Configuration &config);

    /**
     * Save (get) the current victor Configuration
     * 
     * @returns The current victor Configuration
     */
    Configuration SaveConfig();

    /**
     * Modify a victor Configuration. This is the equivilent of calling @ref SaveConfig(), changing
     * a value, followed by @ref LoadConfig(Configuration &).
     * 
     * @param func The Configuration function. This is a function that takes in a Configuration reference.
     */
    void ModifyConfig(std::function<void(Configuration &)> func);
    
    actuators::Port _port;
    void *_handle;
    double _value;
  };

  class TalonFX : public wml::actuators::MotorVoltageController, public frc::MotorController, public wml::sensors::Encoder {
   public:
    using Configuration = ctre::phoenix::motorcontrol::can::TalonFXConfiguration;
    using ControlMode = ctre::phoenix::motorcontrol::ControlMode;

    /**
     * @brief Construct a TalonFX Motor controller
     * 
     * @param port // CAN Port for motor controller
     * @param encoderTicksPerRotation // Ticks per rotation [default = 2048]
     */
    TalonFX(actuators::Port port, int encoderTicksPerRotation = 2048);
    ~TalonFX();

    void SetUpdateRate(int hz);

    actuators::Port GetPort();

    virtual int GetPhysicalPort() override { return GetPort()._PDP;};

    void SetInverted(bool invert) override;

    bool GetInverted() const override;

    void Disable() override;

    void StopMotor() override;

    void Set(double speed) override;

    void Set(ControlMode mode, double value);

    ControlMode GetMode();

    double Get() const override;

    virtual double GetCurrent() override;

    int GetSensorPosition();

    int GetSensorVelocity();

    int GetEncoderRawTicks() override;
    double GetEncoderTickVelocity() override;
    void ZeroEncoder() override;
  
    void LoadConfig(Configuration &config);

    Configuration SaveConfig();

    void ModifyConfig(std::function<void(Configuration &)> func);

    actuators::Port _port;
    void *_handle;
    double _value;
  };

}