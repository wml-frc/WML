#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>


#define __NTUTIL__SLAVE__MACRO_FACTORY__(MainT, LongT)  \
__NTUTIL__SLAVE__CTOR_FACTORY__(MainT, LongT)           \
__NTUTIL__SLAVE__METHOD_FACTORY__(MainT, LongT)

#define __NTUTIL__SLAVE__CTOR_FACTORY__(MainT, LongT)                                                                         \
template <std::enable_if<std::is_convertible<T, MainT>::value>* = nullptr>                                                           \
Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, MainT *value) : _table(table), _name(name), _val(value) {    \
  _entry = table->GetEntry(name);                                                                                             \
  _entry.ForceSet##LongT(*value);                                                                                             \
  _listener = _entry.AddListener([=](const nt::EntryNotification &evt) {                                                      \
    *_val = evt.value->Get##LongT();                                                                                          \
  }, NT_NOTIFY_UPDATE);                                                                                                       \
}

#define __NTUTIL__SLAVE__METHOD_FACTORY__(MainT, LongT)                       \
std::enable_if_t<std::is_convertible<T, MainT>::value>                        \
Override(MainT newVal) { _entry.ForceSet##LongT(newVal); *_val = newVal; }


namespace wml {
  namespace NTUtil {
    template <typename T>
    class Slave {
     public:
      __NTUTIL__SLAVE__MACRO_FACTORY__(bool, Boolean)
      __NTUTIL__SLAVE__MACRO_FACTORY__(double, Double)
      __NTUTIL__SLAVE__MACRO_FACTORY__(std::string, String)

      // __NTUTIL__SLAVE__MACRO_FACTORY__(std::string, Raw)

      __NTUTIL__SLAVE__MACRO_FACTORY__(std::vector<int>, BooleanArray)
      __NTUTIL__SLAVE__MACRO_FACTORY__(std::vector<double>, DoubleArray)
      __NTUTIL__SLAVE__MACRO_FACTORY__(std::vector<std::string>, StringArray)


      template <std::enable_if<false>* = nullptr>
      Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, void* *value); // T *value

      Slave(const Slave &other) : Slave(other._table, other._name, other._val) {}
      ~Slave() { _table->RemoveEntryListener(_listener); }

      std::enable_if_t<false>
      Override(void* newVal); // T newVal
      
     private:
      std::shared_ptr<nt::NetworkTable> _table;
      nt::NetworkTableEntry _entry;
      NT_EntryListener _listener;
      std::string _name;
      T *_val;
    };
  } // namespace NTUtil
}  // namespace wml


#undef __NTUTIL__SLAVE__MACRO_FACTORY__
#undef __NTUTIL__SLAVE__CTOR_FACTORY__
#undef __NTUTIL__SLAVE__METHOD_FACTORY__
