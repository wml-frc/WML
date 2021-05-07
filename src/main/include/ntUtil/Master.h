#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>

#include "loops/LoopSystem.h"


namespace wml {
  namespace ntUtil {
    // workaround for gcc (see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85282):
    namespace {
      template <typename T> struct _ForceSetEntryValue { static void exec(std::shared_ptr<nt::NetworkTableEntry> entry, T newVal); };

      #define __NTUTIL__SLAVE__BASE__METHOD__IMPLEMENTATION_FACTORY__(MainT, LongT)     \
      template <> struct _ForceSetEntryValue<MainT> {                                   \
        static void exec(std::shared_ptr<nt::NetworkTableEntry> entry, MainT newVal) {  \
          entry->ForceSet##LongT(newVal);                                               \
        }                                                                               \
      };

      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(bool, Boolean)
      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(double, Double)
      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(std::string, String)

      /* __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(std::string, Raw) */

      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(std::vector<int>, BooleanArray)
      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(std::vector<double>, DoubleArray)
      __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(std::vector<std::string>, StringArray)

      #undef __NTUTIL__SLAVE__BASE__METHOD__IMPLEMENTATION_FACTORY__
    }

    template <typename T>
    class Master : public loops::LoopSystem {
     public:
      Master(std::shared_ptr<nt::NetworkTable> table, std::string name, T *value) : _table(table), _name(name), _val(value) {
        _entry = std::make_shared<nt::NetworkTableEntry>(table->GetEntry(name));
        UpdateOnce();
      }

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
      std::shared_ptr<nt::NetworkTableEntry> _entry; // ? might not need to be a shared_ptr
      std::string _name;
      T *_val;
    };
  } // namespace ntUtil
}  // namespace wml


#undef __NTUTIL__MASTER__MACRO_FACTORY__
#undef __NTUTIL__MASTER__CTOR_FACTORY__
#undef __NTUTIL__MASTER__METHOD_FACTORY__
