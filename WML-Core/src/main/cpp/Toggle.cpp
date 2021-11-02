#include "Toggle.h"

using namespace wml;

Toggle::Toggle(ToggleEvent mode) {
  bool initState = false;
  switch (mode) {
   case ONCHANGE:
    initState = false;
    break;
    
   case ONFALL:
    initState = true;
    break;
  
   case ONRISE:
    initState = false;
    break;
  }

  _mode = mode;
  _triggered = false;
  _lastState = initState;
}

Toggle::Toggle(ToggleEvent mode, bool initState) {
  _mode = mode;
  _triggered = false;
  _lastState = initState;
}

bool Toggle::Update(bool val) {
  if (_lastState == val) {
    _triggered = false;
  } else {
    switch (_mode) {
     case ONFALL:
      _triggered = !val;
      break;

     case ONCHANGE:
      _triggered = true;
      break;

     case ONRISE:
      _triggered = val;
      break;
    }

    _lastState = val;
  }

  return _triggered;
}

bool Toggle::GetTriggered() { return _triggered; }
