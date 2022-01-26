#pragma once

#include "Effect.h"
#include <map>
#include <memory>

class KeyboardConfig {
private:
  KeyboardConfig();

  const std::string filename = ".k810";

public:
  static std::shared_ptr<KeyboardConfig> GetConfig();

  std::map<int, Effect> effects;

  KeyboardConfig(KeyboardConfig const &) = delete;
  void operator=(KeyboardConfig const &) = delete;
};
