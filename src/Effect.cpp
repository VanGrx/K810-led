#include "Effect.h"

Effect::EffectType Effect::GetEffectType(const char &str) {

  if (str == 'l') {
    return EffectType::Backlight;
  } else if (str == 'b')
    return EffectType::Breathing;

  return EffectType::Backlight;
}
