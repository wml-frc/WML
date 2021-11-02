#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include <networktables/NetworkTable.h>


#define __NTUTIL__SLAVE__METHOD_FACTORY__(MainT, LongT) \
__NTUTIL__SLAVE__SET_FACTORY__(MainT, LongT)            \
__NTUTIL__SLAVE__GET_FACTORY__(MainT, LongT)

#define __NTUTIL__SLAVE__SET_FACTORY__(MainT, LongT)                                        \
template <typename U = T, typename std::enable_if<std::is_same<U, MainT>::value>::type...>  \
void ForceSetValue(MainT value) { _entry.ForceSet##LongT(value); }

#define __NTUTIL__SLAVE__GET_FACTORY__(MainT, LongT)                                        \
template <typename U = T, typename std::enable_if<std::is_same<U, MainT>::value>::type...>  \
void UpdateVar(MainT *var, const nt::EntryNotification &event) { *var = event.value->Get##LongT(); }


namespace wml {
  namespace NTUtil {
    template <typename T>
    class Slave {
     public:
      Slave(std::shared_ptr<nt::NetworkTable> table, std::string name, T *var) : _table(table), _name(name), _var(var) {
        _entry = table->GetEntry(name);
        ForceSetValue(*_var);
        _listener = _entry.AddListener([=](const nt::EntryNotification &evt) {
          UpdateVar(_var, evt);
        }, NT_NOTIFY_UPDATE);
      }

      Slave(const Slave &other) : Slave(other._table, other._name, other._var) {}
      ~Slave() { _table->RemoveEntryListener(_listener); }

      void Override(T value) {
        *_var = value;
        ForceSetValue(*_var);
      }
    
     protected:
      template <typename U = T, typename std::enable_if<!std::is_same<U, U>::value>::type...> // disabled
      void ForceSetValue(void* value);

      template <typename U = T, typename std::enable_if<!std::is_same<U, U>::value>::type...> // disabled
      void UpdateVar(void* var, const nt::EntryNotification &event);

      __NTUTIL__SLAVE__METHOD_FACTORY__(bool, Boolean)
      __NTUTIL__SLAVE__METHOD_FACTORY__(double, Double)
      __NTUTIL__SLAVE__METHOD_FACTORY__(std::string, String)
      // __NTUTIL__SLAVE__METHOD_FACTORY__(std::string, Raw)

      __NTUTIL__SLAVE__METHOD_FACTORY__(std::vector<int>, BooleanArray)
      __NTUTIL__SLAVE__METHOD_FACTORY__(std::vector<double>, DoubleArray)
      __NTUTIL__SLAVE__METHOD_FACTORY__(std::vector<std::string>, StringArray)
      
     private:
      std::shared_ptr<nt::NetworkTable> _table;
      nt::NetworkTableEntry _entry;
      NT_EntryListener _listener;
      std::string _name;
      T *_var;
    };
  } // namespace NTUtil
}  // namespace wml


#undef __NTUTIL__SLAVE__MACRO_FACTORY__
#undef __NTUTIL__SLAVE__CTOR_FACTORY__
#undef __NTUTIL__SLAVE__METHOD_FACTORY__