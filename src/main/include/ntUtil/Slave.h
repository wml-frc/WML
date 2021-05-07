#pragma once

#include <memory>
#include <string>

#include <networktables/NetworkTable.h>

#include "ntUtil/Internal.h"

namespace wml {
  namespace ntUtil {
    template <typename T>
    class Slave {
     public:
      Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, T *value) : _table(table), _name(name), _val(value) {
        _entry = std::make_shared<nt::NetworkTableEntry>(table->GetEntry(name));
        internal::ForceSetEntryValue<T>(_entry, *value);
        _listener = _entry->AddListener([=](const nt::EntryNotification &evt) {
          *_val = internal::GetValue<T>(evt.value);
        }, NT_NOTIFY_UPDATE);
      }

      Slave(const Slave<T> &other) : Slave(other._table, other._name, other._val) {}
      ~Slave() { _table->RemoveEntryListener(_listener); }

      void Override(T newVal) {
        internal::ForceSetEntryValue<T>(_entry, newVal);
        *_val = newVal;
      };

     protected:
      std::shared_ptr<nt::NetworkTable> _table;
      std::shared_ptr<nt::NetworkTableEntry> _entry;
      NT_EntryListener _listener;
      std::string _name;
      T *_val;
    };
  } // namespace ntUtil
}  // namespace wml
