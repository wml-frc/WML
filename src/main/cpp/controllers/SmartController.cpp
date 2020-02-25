#include "controllers/SmartController.h"

using namespace wml::controllers;


bool SmartController::Exists(tAxis axis, bool value) {
  try {
    _axes.at(axis.id);
  } catch (std::out_of_range) {
    return !value;
  }

  return value;
}

bool SmartController::Exists(tButton button, bool value) {
  try {
    _buttons.at(button.id);
  } catch (std::out_of_range) {
    return !value;
  }

  return value;
}

bool SmartController::Exists(tPOV pov, bool value) {
  try {
    _POVs.at(pov.id);
  } catch (std::out_of_range) {
    return !value;
  }

  return value;
}

bool SmartController::Exists(std::vector<tAxis> axi, bool value) {
  bool val = value;
  for (auto axis : axi) val |= Exists(axis, value);
  return val;
}

bool SmartController::Exists(std::vector<tButton> buttons, bool value) {
  bool val = value;
  for (auto button : buttons) val |= Exists(button, value);
  return val;
}

bool SmartController::Exists(std::vector<tPOV> povs, bool value) {
  bool val = value;
  for (auto pov : povs) val |= Exists(pov, value);
  return val;
}


inputs::ContAxis *SmartController::GetObj(tAxis axis) {
  return Exists(axis) ? _axes.at(axis.id) : nullptr;
}

inputs::ContButton *SmartController::GetObj(tButton button) {
  return Exists(button) ? _buttons.at(button.id) : nullptr;
}

inputs::ContPOV *SmartController::GetObj(tPOV pov) {
  return Exists(pov) ? _POVs.at(pov.id) : nullptr;
}


void SmartController::Map(tAxis axis, inputs::ContAxis *newAxis, bool force) {
  if (!force) if (Exists(axis)) return;

  _axes[axis.id] = newAxis;
}

void SmartController::Map(tButton button, inputs::ContButton *newButton, bool force) {
  if (!force) if (Exists(button)) return;

  _buttons[button.id] = newButton;
}

void SmartController::Map(tPOV pov, inputs::ContPOV *newPOV, bool force) {
  if (!force) if (Exists(pov)) return;

  _POVs[pov.id] = newPOV;
}


void SmartController::Map(tAxis map_axis, tButton virt_button, double threshold, bool force) {
  if (!Exists(map_axis)) return;

  Map(virt_button, inputs::MakeAxisButton(GetObj(map_axis), threshold).at(0), force);
  // _axes.erase(_axes.find(map_axis.id));
}

void SmartController::Map(tAxis map_axis, std::vector<tButton> virt_buttons, bool force) {
  if (!Exists(map_axis)) return;
  
  std::vector<inputs::AxisSelectorButton*> buttons = inputs::MakeAxisSelectorButtons(GetObj(map_axis), virt_buttons.size());
  for (unsigned int i = 0; i < buttons.size(); i++) {
    if (virt_buttons.at(i) != noButton) Map(virt_buttons.at(i), buttons.at(i), force);
  }
  // _axes.erase(_axes.find(map_axis.id));
}

void SmartController::PairAxis(tAxis primary_axis, tAxis secondary_axis, bool squared) {
  if (!Exists(primary_axis) || !Exists(secondary_axis)) return;

  std::pair<inputs::FieldAxis*, inputs::FieldAxis*> axi = inputs::MakeFieldAxi(new inputs::Field(std::make_pair<inputs::ContAxis*, inputs::ContAxis*>(GetObj(primary_axis), GetObj(secondary_axis)), squared));
  Map(primary_axis, axi.first, true);
  Map(secondary_axis, axi.second, true);
}


void SmartController::Map(std::pair<tButton, tButton> map_buttons, std::vector<tButton> virt_buttons, bool wrap, bool force) {
  if (!Exists(std::vector<tButton>({ map_buttons.first, map_buttons.second }))) return;

  std::vector<inputs::ButtonSelectorButton*> buttons = inputs::MakeButtonSelectorButtons({ GetObj(map_buttons.first), GetObj(map_buttons.second) }, virt_buttons.size(), wrap);
  for (unsigned int i = 0; i < buttons.size(); i++) {
    if (virt_buttons.at(i) != noButton) Map(virt_buttons.at(i), buttons.at(i), force);
  }

  // _buttons.erase(_buttons.find(map_buttons.first.id));
  // _buttons.erase(_buttons.find(map_buttons.second.id));
}



void SmartController::Map(tPOV map_POV, std::map<Controller::POVPos, tButton> virt_buttons, bool force) {
  if (!Exists(map_POV)) return;
  
  std::map<Controller::POVPos, inputs::POVButton*> buttons = inputs::MakePOVButtons(GetObj(map_POV));
  for (auto pair : virt_buttons) {
    if (pair.second != noButton) Map(pair.second, buttons.at(pair.first), force);
  }

  // _POVs.erase(_POVs.find(map_POV.id));
}



// --------------------------------------------- INPUT GETTERS ---------------------------------------------

double SmartController::Get(tAxis axis) {
  if (Exists(axis, false)) return 0;
  return GetObj(axis)->Get();
}

bool SmartController::Get(tButton button, SmartController::ButtonMode mode) {
  if (Exists(button, false)) return false;

  switch (mode) {
   case ButtonMode::RAW:
    return GetObj(button)->Get();

   case ButtonMode::ONRISE:
    return GetObj(button)->GetOnRise();

   case ButtonMode::ONFALL:
    return GetObj(button)->GetOnFall();

   case ButtonMode::ONCHANGE:
    return GetObj(button)->GetOnChange();
  }

  return false;
}

wml::controllers::Controller::POVPos SmartController::Get(tPOV pov) {
  if (Exists(pov, false)) return kNone;
  return GetObj(pov)->Get();
}



// ------------------------------------------- FEEDBACK SETTERS --------------------------------------------

void SmartController::Set(tRumble rumble, double value) {
  _cont->SetRumble(rumble.type, value);
}



// --------------------------------------------- UPDATE FUNCS ----------------------------------------------

void SmartController::UpdateButtonSelectors() {
  for (auto pair : _buttons) UpdateButtonSelector(tButton(-1, pair.first));
}
