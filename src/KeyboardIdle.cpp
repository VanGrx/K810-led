#include "KeyboardIdle.h"
#include "keyboardconfig.h"
#include <QDebug>
#include <kidletime.h>

KeyboardIdle::KeyboardIdle() {
  // connect to idle events
  connect(KIdleTime::instance(), &KIdleTime::resumingFromIdle, this,
          &KeyboardIdle::resumeEvent);
  connect(KIdleTime::instance(),
          qOverload<int, int>(&KIdleTime::timeoutReached), this,
          &KeyboardIdle::timeoutReached);

  setupBacklight(0xFF);

  // register to get informed for the very next user event
  KIdleTime::instance()->catchNextResumeEvent();
}

KeyboardIdle::~KeyboardIdle() {}

void KeyboardIdle::resumeEvent() {
  KIdleTime::instance()->removeAllIdleTimeouts();

  setupBacklight(0xFF);

  for (auto it : KeyboardConfig::GetConfig()->effects)
    KIdleTime::instance()->addIdleTimeout(it.first);
}

void KeyboardIdle::timeoutReached(int id, int timeout) {
  Q_UNUSED(id)

  KIdleTime::instance()->catchNextResumeEvent();

  auto effect = KeyboardConfig::GetConfig()->effects[timeout];

  if (effect.effect == Effect::EffectType::Backlight)
    setupBacklight(effect.intensity);
  else
    setupCycle(effect.intensity, effect.breathDuration);
}

void KeyboardIdle::setupBacklight(uint8_t intensity) {

  LedKeyboard kbd;
  initKeyboard(kbd);

  uint8_t colorInt = intensity;

  auto color = LedKeyboard::Color{colorInt, colorInt, colorInt};

  if (!kbd.open())
    return;
  if (!kbd.setAllKeys(color))
    return;
  if (!kbd.commit())
    return;
}

void KeyboardIdle::setupCycle(uint8_t intensity, uint8_t duration) {
  LedKeyboard kbd;
  initKeyboard(kbd);

  auto nativeEffect = LedKeyboard::NativeEffect::breathing;
  auto nativeEffectPart = LedKeyboard::NativeEffectPart::all;
  auto color = LedKeyboard::Color{intensity, intensity, intensity};
  auto period = std::chrono::seconds(duration);
  if (!kbd.open())
    return;

  if (!kbd.setNativeEffect(nativeEffect, nativeEffectPart, period, color,
                           LedKeyboard::NativeEffectStorage::none))
    return;
}

void KeyboardIdle::initKeyboard(LedKeyboard &kbd) {
  std::string serial;
  uint16_t vendorID = 0x0;
  uint16_t productID = 0x0;

  if (!kbd.open(vendorID, productID, serial)) {
    std::cout << "Matching or compatible device not found !" << std::endl;
  }
}
