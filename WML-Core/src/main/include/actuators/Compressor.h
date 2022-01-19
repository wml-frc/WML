#pragma once

#include <frc/Compressor.h>

#include "actuators/BinaryActuator.h"

namespace wml {
  namespace actuators {
    class Compressor : protected frc::Compressor, public BinaryActuator {
      public:
      Compressor(std::string name = "<Compressor>", BinaryActuatorState initialState = actuators::kReverse) : frc::Compressor(frc::PneumaticsModuleType::CTREPCM), BinaryActuator(name, initialState) { EnableDigital(); };
      Compressor(int pcmID, PneumaticsModuleType pcmType, std::string name = "<Compressor>", BinaryActuatorState initialState = actuators::kReverse) : frc::Compressor(pcmID, (frc::PneumaticsModuleType)pcmType), BinaryActuator(name, initialState) { EnableDigital(); };

      virtual void UpdateActuator(double dt) override;
      virtual void Stop() final {};
      virtual bool IsDone() override;
    };
  } // ns actuators
} // ns wml
