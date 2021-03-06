#pragma once
#include <cstdint>

class Effect {
public:
  enum EffectType { Backlight, Breathing };

  static EffectType GetEffectType(const char &str);

  Effect() {}

  Effect(EffectType type, uint8_t _intensity, uint8_t _breathDuration = 1)
      : effect{type}, intensity{_intensity}, breathDuration{_breathDuration} {}

  EffectType effect;
  uint8_t intensity;
  uint8_t breathDuration;
};
