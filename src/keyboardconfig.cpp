#include "keyboardconfig.h"
#include <fstream>
#include <iomanip>
#include <iostream>

KeyboardConfig::KeyboardConfig() {

  const char *home_var = getenv("HOME");

  if (home_var == nullptr) {
    std::cerr << "HOME var not set!" << std::endl;
    return;
  }

  std::string file = std::string(home_var) + "/" + filename;
  std::ifstream infile(file);

  if (!infile.is_open()) {
    std::cerr << "Config file not found! Create one at: " << file << std::endl;
  }

  std::string line;

  while (std::getline(infile, line)) {

    int time;
    char type;
    int intensity;
    int numerator;
    int denumerator;
    int cycle;

    std::stringstream iss(line);

    iss >> time >> type >> std::hex >> intensity >> std::dec >> numerator >>
        denumerator;

    if (!iss || time < 0 || intensity < 0 || numerator < 1 || denumerator < 1)
      continue;

    auto effect = Effect::GetEffectType(type);

    if (effect == Effect::EffectType::Breathing) {
      iss >> cycle;
      if (!iss || cycle < 0)
        continue;
    }

    switch (effect) {
    case Effect::EffectType::Backlight:
      effects[time] = Effect(effect, intensity * numerator / denumerator);
      break;
    case Effect::EffectType::Breathing:
      effects[time] =
          Effect(effect, intensity * numerator / denumerator, cycle);
    }
  }
}

std::shared_ptr<KeyboardConfig> KeyboardConfig::GetConfig() {

  static std::shared_ptr<KeyboardConfig> config_singleton(new KeyboardConfig());

  return config_singleton;
}
