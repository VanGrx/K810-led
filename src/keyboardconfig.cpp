#include "keyboardconfig.h"

KeyboardConfig::KeyboardConfig() {

  // TODO: Read from config file
  effects[1000] = Effect(Effect::Backlight, 0xFF / 1, 0);
  effects[2000] = Effect(Effect::Backlight, 0xFF / 2, 0);
  effects[3000] = Effect(Effect::Backlight, 0xFF / 3, 0);
  effects[4000] = Effect(Effect::Backlight, 0xFF / 4, 0);
  effects[5000] = Effect(Effect::Backlight, 0xFF / 5, 0);
  effects[6000] = Effect(Effect::Backlight, 0, 0);
  effects[7000] = Effect(Effect::Breathing, 0xFF, 5);
}

std::shared_ptr<KeyboardConfig> KeyboardConfig::GetConfig() {

  static std::shared_ptr<KeyboardConfig> config_singleton(new KeyboardConfig());

  return config_singleton;
}
