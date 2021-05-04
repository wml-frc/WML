#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>


namespace wml {
  namespace NTUtil {
    template <typename T>
    class SlaveBase {
     public:
      SlaveBase(std::shared_ptr<nt::NetworkTable> table, std::string name, T *value) : _table(table), _name(name), _val(value) {
        _entry = table->GetEntry(name);
        // ForceSetEntryValue(*value); // This breaks everything <- nathan your problem
        _listener = _entry.AddListener([=](const nt::EntryNotification &evt) {
          *_val = GetValue(evt.value);
        }, NT_NOTIFY_UPDATE);
      }

      SlaveBase(const SlaveBase<T> &other) : SlaveBase(other._table, other._name, other._val) {}
      ~SlaveBase() { _table->RemoveEntryListener(_listener); }

      void Override(T newVal) {
        ForceSetEntryValue(newVal);
        *_val = newVal;
      };

     protected:
      virtual void ForceSetEntryValue(T newVal) = 0; // overrides the value in `_entry` using the appropriate typed method
      virtual T GetValue(std::shared_ptr<nt::Value> ntValue) = 0; // gets the value of `_entry` using the appropriate typed method
      
      std::shared_ptr<nt::NetworkTable> _table;
      nt::NetworkTableEntry _entry;
      NT_EntryListener _listener;
      std::string _name;
      T *_val;
    };
  } // namespace NTUtil
}  // namespace wml
