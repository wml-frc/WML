#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>


#define __NTUTIL__SLAVE__MACRO_FACTORY__(MainT, LongT)  \
__NTUTIL__SLAVE__CTOR_FACTORY__(MainT, LongT)           \
__NTUTIL__SLAVE__METHOD_FACTORY__(MainT, LongT)

#define __NTUTIL__SLAVE__CTOR_FACTORY__(MainT, LongT)                                                                         \
template <typename U = T, typename std::enable_if<std::is_same<U, MainT>::value>::type...>                                    \
Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, MainT *value) : _table(table), _name(name), _val(value) {    \
  _entry = table->GetEntry(name);                                                                                             \
  _entry.ForceSet##LongT(*value);                                                                                             \
  _listener = _entry.AddListener([=](const nt::EntryNotification &evt) {                                                      \
    *_val = evt.value->Get##LongT();                                                                                          \
  }, NT_NOTIFY_UPDATE);                                                                                                       \
}

#define __NTUTIL__SLAVE__METHOD_FACTORY__(MainT, LongT)                                     \
template <typename U = T, typename std::enable_if<std::is_same<U, MainT>::value>::type...>  \
void Override(MainT newVal) { _entry.ForceSet##LongT(newVal); *_val = newVal; }


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


      template <typename U = T, typename std::enable_if<!std::is_same<U, U>::value>::type...> // disabled
      Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, void* *value); // T *value

      Slave(const Slave &other) : Slave(other._table, other._name, other._val) {}
      ~Slave() { _table->RemoveEntryListener(_listener); }

      template <typename U = T, typename std::enable_if<!std::is_same<U, U>::value>::type...> // disabled
      void Override(void* newVal); // T newVal
      
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