#include "Toggle.h"

using namespace wml;

Toggle::Toggle(ToggleEvent mode) {
  _mode = mode;
  _triggered = false;

  _lstate = false;
  switch (mode) {
   case ONCHANGE:
    _lstate = false;
    break;
    
   case ONFALL:
    _lstate = true;
    break;
  
   case ONRISE:
    _lstate = false;
    break;
  }
}

Toggle::Toggle(ToggleEvent mode, bool initState) {
  _mode = mode;
  _triggered = false;
  _lstate = initState;
}

bool Toggle::Update(bool val) {
  _triggered = _lstate != val && !val != _mode;
  _lstate = val;

  return _triggered;
}

bool Toggle::GetTriggered() { return _triggered; }
