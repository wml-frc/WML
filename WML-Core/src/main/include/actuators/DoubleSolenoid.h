#pragma once

#include <frc/DoubleSolenoid.h>

#include "actuators/BinaryActuator.h"

namespace wml {
	namespace actuators {
		class DoubleSolenoid : protected frc::DoubleSolenoid, public BinaryActuator {
		public:

			static constexpr double StandardActuationTime = 0.2;
			DoubleSolenoid(int forwardChannel, int reverseChannel, double actuationTime, std::string name = "<DoubleSolenoid>", BinaryActuatorState initialState = actuators::kReverse) : frc::DoubleSolenoid(frc::PneumaticsModuleType::CTREPCM, forwardChannel, reverseChannel), BinaryActuator(name, initialState), _actuationTime(actuationTime) {};
			DoubleSolenoid(PneumaticsModuleType pcmType, int forwardChannel, int reverseChannel, double actuationTime, std::string name = "<DoubleSolenoid>", BinaryActuatorState initialState = actuators::kReverse) : frc::DoubleSolenoid((frc::PneumaticsModuleType)pcmType, forwardChannel, reverseChannel), BinaryActuator(name, initialState), _actuationTime(actuationTime) {};
			DoubleSolenoid(int pcmID, PneumaticsModuleType pcmType, int forwardChannel, int reverseChannel, double actuationTime, std::string name = "<DoubleSolenoid>", BinaryActuatorState initialState = actuators::kReverse) : frc::DoubleSolenoid(pcmID, (frc::PneumaticsModuleType)pcmType, forwardChannel, reverseChannel), BinaryActuator(name, initialState), _actuationTime(actuationTime) {};

			virtual void UpdateActuator(double dt) override;
			virtual void Stop() final {};
			virtual bool IsDone() override;

		protected:
			virtual void Init() override;

		private:
			double _actuationTime;
			double _timer;
		};
	} // ns actuators
} // ns wml
