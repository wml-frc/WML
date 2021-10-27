#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>

#include "loops/LoopSystem.h"


#define __NTUTIL__MASTER__MACRO_FACTORY__(MainT, LongT)   \
__NTUTIL__MASTER__CTOR_FACTORY__(MainT)                   \
private:                                                  \
__NTUTIL__MASTER__METHOD_FACTORY__(MainT, LongT)          \
public:

#define __NTUTIL__MASTER__CTOR_FACTORY__(MainT)                                                                               \
template <std::enable_if<std::is_convertible<T, MainT>::value>* = nullptr>                                                    \
Master(std::shared_ptr<nt::NetworkTable> table, std::string name, MainT *value) : _table(table), _name(name), _val(value) {   \
  _entry = table->GetEntry(name);                                                                                             \
  UpdateOnce();                                                                                                               \
}

#define __NTUTIL__MASTER__METHOD_FACTORY__(MainT, LongT)                          \
std::enable_if_t<std::is_convertible<T, MainT>::value>                            \
_Update(double dt, MainT *dummy = nullptr) { _entry.ForceSet##LongT(*_val); }


namespace wml {
  namespace NTUtil {
    template <typename T>
    class Master : public loops::LoopSystem {
     public:
      __NTUTIL__MASTER__MACRO_FACTORY__(bool, Boolean)
      __NTUTIL__MASTER__MACRO_FACTORY__(double, Double)
      __NTUTIL__MASTER__MACRO_FACTORY__(std::string, String)

      // __NTUTIL__MASTER__MACRO_FACTORY__(std::string, Raw)

      __NTUTIL__MASTER__MACRO_FACTORY__(std::vector<int>, BooleanArray)
      __NTUTIL__MASTER__MACRO_FACTORY__(std::vector<double>, DoubleArray)
      __NTUTIL__MASTER__MACRO_FACTORY__(std::vector<std::string>, StringArray)


      template <std::enable_if<false>* = nullptr>
      Master(std::shared_ptr<nt::NetworkTable> table, std::string name, void* *value); // T *value

      Master(const Master &other) : Master(other._table, other._name, other._val) {}

      virtual void Update(double dt) override { _Update(dt, (T*)nullptr); };
      
     private:
      std::shared_ptr<nt::NetworkTable> _table;
      nt::NetworkTableEntry _entry;
      std::string _name;
      T *_val;
    };
  } // namespace NTUtil
}  // namespace wml


#undef __NTUTIL__MASTER__MACRO_FACTORY__
#undef __NTUTIL__MASTER__CTOR_FACTORY__
#undef __NTUTIL__MASTER__METHOD_FACTORY__