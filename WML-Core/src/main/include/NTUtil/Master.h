#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>

#include "loops/LoopSystem.h"


#define __NTUTIL__MASTER__METHOD_FACTORY__(MainT, LongT)  \
__NTUTIL__MASTER__SET_FACTORY__(MainT, LongT)

#define __NTUTIL__MASTER__SET_FACTORY__(MainT, LongT)                                       \
template <typename U = T, typename std::enable_if<std::is_same<U, MainT>::value>::type...>  \
void ForceSetValue(MainT value) { _entry.ForceSet##LongT(value); }


namespace wml {
  namespace NTUtil {
    template <typename T>
    class Master : public loops::LoopSystem {
     public:
      Master(std::shared_ptr<nt::NetworkTable> table, std::string name, T *var) : _table(table), _name(name), _var(var) {
        _entry = table->GetEntry(name);
        _lastValue = nullptr;
        
        UpdateOnce();
      }

      Master(const Master &other) : Master(other._table, other._name, other._var) {}

      virtual void Update(double dt) override {
        if (_lastValue == nullptr || *_lastValue != *_var) {
          *_lastValue = *_var;
          ForceSetValue(*_var);
        }
      };

     protected:
      template <typename U = T, typename std::enable_if<!std::is_same<U, U>::value>::type...> // disabled
      void ForceSetValue(void* value);

      __NTUTIL__MASTER__METHOD_FACTORY__(bool, Boolean)
      __NTUTIL__MASTER__METHOD_FACTORY__(double, Double)
      __NTUTIL__MASTER__METHOD_FACTORY__(std::string, String)
      // __NTUTIL__MASTER__METHOD_FACTORY__(std::string, Raw)

      __NTUTIL__MASTER__METHOD_FACTORY__(std::vector<int>, BooleanArray)
      __NTUTIL__MASTER__METHOD_FACTORY__(std::vector<double>, DoubleArray)
      __NTUTIL__MASTER__METHOD_FACTORY__(std::vector<std::string>, StringArray)
      
     private:
      std::shared_ptr<nt::NetworkTable> _table;
      nt::NetworkTableEntry _entry;
      std::string _name;
      T *_var;
      T *_lastValue;
    };
  } // namespace NTUtil
}  // namespace wml


#undef __NTUTIL__MASTER__MACRO_FACTORY__
#undef __NTUTIL__MASTER__CTOR_FACTORY__
#undef __NTUTIL__MASTER__METHOD_FACTORY__