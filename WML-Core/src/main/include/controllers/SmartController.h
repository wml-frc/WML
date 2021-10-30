#pragma once

// #include <functional>
#include <map>
#include <utility>
#include <vector>
#include <stdexcept>

#include "controllers/Controller.h"
#include "controllers/Inputs.h"
#include "Toggle.h"

namespace wml {
  namespace controllers {
    struct tFeedback {
      int cont;
      RumbleType type;

      bool operator== (const tFeedback comp) {
        return this->cont == comp.cont && this->type == comp.type;
      };

      bool operator!= (const tFeedback comp) {
        return !(*this == comp);
      };

      tFeedback(int contIn, RumbleType typeIn) : cont(contIn), type(typeIn) {};
    };

    struct tRumble : public tFeedback { tRumble(int cont, RumbleType type) : tFeedback(cont, type) {}; };
    const tRumble noRumble(-1, RumbleType::kNoneRumble);


    struct SmartControllerConfig {
      const int nAxi;
      const int nButtons;
      const int nPOVs;
    };

    class SmartController : public Controller {
     public:
      SmartController(GenericHID *cont, SmartControllerConfig contConfig) : Controller(cont) {
        for (int i = 0; i < contConfig.nAxi; i++) _axes[i] = new inputs::Axis(new Controller(static_cast<Controller>(*this)), i);
        for (int i = 1; i <= contConfig.nButtons; i++) _buttons[i] = new inputs::Button(new Controller(static_cast<Controller>(*this)), i);
        for (int i = 0; i < contConfig.nPOVs; i++) _POVs[i] = new inputs::POV(new Controller(static_cast<Controller>(*this)), i);
      };

      // 'value' determines whether checking for existance or absence
      bool Exists(tAxis axis, bool value = true);
      bool Exists(tButton button, bool value = true);
      bool Exists(tPOV pov, bool value = true);

      bool Exists(std::vector<tAxis> axis, bool value = true);
      bool Exists(std::vector<tButton> button, bool value = true);
      bool Exists(std::vector<tPOV> pov, bool value = true);


      void Map(tAxis axis, inputs::ContAxis *newAxis, bool force = false);
      void Map(tButton button, inputs::ContButton *newButton, bool force = false);
      void Map(tPOV pov, inputs::ContPOV *newPOV, bool force = false);


      void Map(tAxis map_axis, tButton virt_button, double threshold = 0.3, bool force = false);
      void Map(tAxis map_axis, std::vector<tButton> virt_buttons, bool force = false);
      void PairAxis(tAxis primary_axis, tAxis secondary_axis, bool squared = false);

      void Map(std::pair<tButton, tButton> map_buttons, std::vector<tButton> virt_buttons, bool wrap = false, bool force = false);

      void Map(tPOV map_POV, std::map<Controller::POVPos, tButton> virt_buttons, bool force = false);


      // Controller::Get overrides
      virtual double GetAxis(int axis = 1) override { return Get(tAxis(-1, axis)); };
      virtual bool GetButton(int button = 1) override { return Get(tButton(-1, button), RAW); };
      virtual int GetPOVAngle(int pov = 0) override { return (int)Get(tPOV(-1, pov)); };
      virtual POVPos GetPOV(int pov = 0) override { return Get(tPOV(-1, pov)); };

      virtual double Get(tAxis axis);
      virtual bool Get(tButton button, ButtonMode mode = RAW);
      virtual POVPos Get(tPOV pov);

      int GetButtonCount() const { return _buttons.size(); };
      int GetAxisCount() const { return _axes.size(); };
      int GetPOVCount() const { return _POVs.size(); };


      virtual void SetRumble(RumbleType type, double value) override { Set(tRumble(-1, type), value); };

      virtual void Set(tRumble rumble, double value);


      void Update() { UpdateButtonSelectors(); };

      void UpdateButtonSelectors();

      virtual void UpdateButtonSelector(tButton button) { Get(button); };

     protected:
      inputs::ContAxis *GetAxisObj(int axis) { return GetObj(tAxis(-1, axis)); };
      inputs::ContButton *GetButtonObj(int button) { return GetObj(tButton(-1, button)); };
      inputs::ContPOV *GetPOVObj(int pov) { return GetObj(tPOV(-1, pov)); };

      inputs::ContAxis *GetObj(tAxis axis);
      inputs::ContButton *GetObj(tButton button);
      inputs::ContPOV *GetObj(tPOV pov);

     private:
      std::map<int, inputs::ContAxis*> _axes;
      std::map<int, inputs::ContButton*> _buttons;
      std::map<int, inputs::ContPOV*> _POVs;
    };
  } // ns controllers
} // ns wml
