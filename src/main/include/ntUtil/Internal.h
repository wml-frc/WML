#pragma once

#include <memory>
#include <string>

#include <networktables/NetworkTable.h>

namespace wml {
  namespace ntUtil {
    namespace internal {
      // used as a workaround to a gcc bug (see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85282)

      template <typename T> struct _ForceSetEntryValue { static void exec(std::shared_ptr<nt::NetworkTableEntry> entry, T newVal); };
      template <typename T> struct _GetValue { static T exec(std::shared_ptr<nt::Value> ntValue); };

      #define __NTUTIL__INTERNAL__METHOD__IMPLEMENTATION_FACTORY__(MainT, LongT)        \
      template <> struct _ForceSetEntryValue<MainT> {                                   \
        static void exec(std::shared_ptr<nt::NetworkTableEntry> entry, MainT newVal) {  \
          entry->ForceSet##LongT(newVal);                                               \
        }                                                                               \
      };                                                                                \
      template <> struct _GetValue<MainT> {                                             \
        static MainT exec(std::shared_ptr<nt::Value> ntValue) {                         \
          return ntValue->Get##LongT();                                                 \
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

      template <typename T> void ForceSetEntryValue(std::shared_ptr<nt::NetworkTableEntry> entry, T newVal) { _ForceSetEntryValue<T>::exec(entry, newVal); } // overrides the value in `_entry` using the appropriate typed method
      template <typename T> T GetValue(std::shared_ptr<nt::Value> ntValue) { return _GetValue<T>::exec(ntValue); } // gets the value of `_entry` using the appropriate typed method
      template <typename T> T GetValue(std::shared_ptr<nt::NetworkTableEntry> entry) { return GetValue<T>(entry->GetValue()); } // gets the value of `_entry` using the appropriate typed method
    }
  } // namespace ntUtil
} // namespace wml
