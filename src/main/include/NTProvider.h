#pragma once

#include <string>
#include <vector>

#include <networktables/NetworkTableInstance.h>

#include "sensors/BinarySensor.h"
#include "sensors/DoubleSensor.h"

#include "devices/StateDevice.h"
#include "NTUtil/Master.h"
#include "NTUtil/Slave.h"

namespace wml {
  class NTProvider {
   public:
    NTProvider(std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("Robot Data")) : _table(table) {};

    void Update();

    void Register(sensors::BinarySensor *binarySensor);
    void Register(sensors::DoubleSensor *doubleSensor);

    void Register(devices::StateDeviceBase *stateDevice);

    void Enslave(bool *var, std::string name);
    void Enslave(double *var, std::string name);
    void Enslave(std::string *var, std::string name);
    void Enslave(std::vector<int> *varList, std::string name);
    void Enslave(std::vector<double> *varList, std::string name);
    void Enslave(std::vector<std::string> *varList, std::string name);

    void Obey(bool *var, std::string name);
    void Obey(double *var, std::string name);
    void Obey(std::string *var, std::string name);
    void Obey(std::vector<int> *varList, std::string name);
    void Obey(std::vector<double> *varList, std::string name);
    void Obey(std::vector<std::string> *varList, std::string name);

   private:
    std::shared_ptr<nt::NetworkTable> _table;

    std::vector<sensors::BinarySensor*> _binarySensors;
    std::vector<sensors::DoubleSensor*> _doubleSensors;

    std::vector<devices::StateDeviceBase*> _stateDevices;

    std::vector<NTUtil::Slave<bool>> _slaveBool;
    std::vector<NTUtil::Slave<double>> _slaveDouble;
    std::vector<NTUtil::Slave<std::string>> _slaveString;
    std::vector<NTUtil::Slave<std::vector<int>>> _slaveBoolArray;
    std::vector<NTUtil::Slave<std::vector<double>>> _slaveDoubleArray;
    std::vector<NTUtil::Slave<std::vector<std::string>>> _slaveStringArray;

    std::vector<NTUtil::MasterBase*> _masters;
  };
}
