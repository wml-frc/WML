#pragma once

#include <string>

namespace wml {
  class Named {
   public:
    Named(std::string name) : _name(name) {};

    std::string GetName() { return _name; };

   private:
    std::string _name;
  };
} // ns wml
