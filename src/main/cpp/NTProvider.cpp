#include "NTProvider.h"

using namespace wml;
using namespace wml::sensors;
using namespace wml::devices;


void NTProvider::Update() {
  for (auto binarySensor : _binarySensors)
    _table->GetEntry(binarySensor->GetName()).SetBoolean(binarySensor->Get());

  for (auto doubleSensor : _doubleSensors)
    _table->GetEntry(doubleSensor->GetName()).SetDouble(doubleSensor->GetScaled());


  for (auto stateDevice : _stateDevices)
    _table->GetEntry(stateDevice->GetName()).SetString(stateDevice->GetStateString());


  for (auto master : _masters) master->Update(-1);
}


void NTProvider::Register(BinarySensor *binarySensor) {
  _binarySensors.push_back(binarySensor);
}

void NTProvider::Register(DoubleSensor *doubleSensor) {
  _doubleSensors.push_back(doubleSensor);
}


void NTProvider::Register(StateDeviceBase *stateDevice) {
  _stateDevices.push_back(stateDevice);
}


#define __WML__NTPROVIDER__ENSLAVE_FACTORY__(MainT, LongT)  \
void NTProvider::Enslave(MainT* var, std::string name) {    \
  _slave##LongT.emplace_back(_table, name, var);           \
}

__WML__NTPROVIDER__ENSLAVE_FACTORY__(bool, Bool)
__WML__NTPROVIDER__ENSLAVE_FACTORY__(double, Double)
__WML__NTPROVIDER__ENSLAVE_FACTORY__(std::string, String)
__WML__NTPROVIDER__ENSLAVE_FACTORY__(std::vector<int>, BoolArray)
__WML__NTPROVIDER__ENSLAVE_FACTORY__(std::vector<double>, DoubleArray)
__WML__NTPROVIDER__ENSLAVE_FACTORY__(std::vector<std::string>, StringArray)

#undef __WML__NTPROVIDER__ENSLAVE_FACTORY__

#define __WML__NTPROVIDER__OBEY_FACTORY__(MainT)                          \
void NTProvider::Obey(MainT* var, std::string name) {                     \
  _masters.push_back(new wml::NTUtil::Master<MainT>(_table, name, var));  \
}

__WML__NTPROVIDER__OBEY_FACTORY__(bool)
__WML__NTPROVIDER__OBEY_FACTORY__(double)
__WML__NTPROVIDER__OBEY_FACTORY__(std::string)
__WML__NTPROVIDER__OBEY_FACTORY__(std::vector<int>)
__WML__NTPROVIDER__OBEY_FACTORY__(std::vector<double>)
__WML__NTPROVIDER__OBEY_FACTORY__(std::vector<std::string>)

#undef __WML__NTPROVIDER__OBEY_FACTORY__
