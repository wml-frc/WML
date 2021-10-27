#pragma once

namespace wml {
  enum ToggleEvent {
    ONFALL    = -1,
    ONRISE    =  1,
    ONCHANGE  =  2
  };

  class Toggle {
  public:
    Toggle(ToggleEvent mode = ToggleEvent::ONRISE);
    Toggle(ToggleEvent mode, bool initState);

    bool Update(bool val);

    bool GetTriggered();

  private:
    ToggleEvent _mode;
    bool _triggered;
    bool _lstate;
  };
} // ns wml
