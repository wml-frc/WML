#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>

#include "NTUtil/SlaveBase.h"


#define __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(MainT, LongT)                     \
template <>                                                                         \
class Slave<MainT> : public SlaveBase<MainT> {                                      \
  public:                                                                           \
  /* using SlaveBase::SlaveBase; */                                                 \
 protected:                                                                         \ 
  virtual void ForceSetEntryValue(MainT newVal) { _entry.ForceSet##LongT(newVal); } \
  virtual MainT GetEntryValue() { return evt.value->Get##LongT(); }                 \
};


namespace wml {
  namespace NTUtil {
    template <typename T>
    class Slave : public SlaveBase<T>;

    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(bool, Boolean)
    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(double, Double)
    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(std::string, String)

    // __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(std::string, Raw)

    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(std::vector<int>, BooleanArray)
    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(std::vector<double>, DoubleArray)
    __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__(std::vector<std::string>, StringArray)
  } // namespace NTUtil
}  // namespace wml


#undef __NTUTIL__SLAVE__IMPLEMENTATION_FACTORY__
