#include "KeyboardIdle.h"
#include <QDebug>
#include <kidletime.h>

KeyboardIdle::KeyboardIdle() {
  // connect to idle events
  connect(KIdleTime::instance(), &KIdleTime::resumingFromIdle, this,
          &KeyboardIdle::resumeEvent);
  connect(KIdleTime::instance(),
          qOverload<int, int>(&KIdleTime::timeoutReached), this,
          &KeyboardIdle::timeoutReached);

  setupBacklight(5);

  // register to get informed for the very next user event
  KIdleTime::instance()->catchNextResumeEvent();
}

KeyboardIdle::~KeyboardIdle() {}

void KeyboardIdle::resumeEvent() {
  KIdleTime::instance()->removeAllIdleTimeouts();

  setupBacklight(5);

  KIdleTime::instance()->addIdleTimeout(1000);
  KIdleTime::instance()->addIdleTimeout(2000);
  KIdleTime::instance()->addIdleTimeout(3000);
  KIdleTime::instance()->addIdleTimeout(4000);
  KIdleTime::instance()->addIdleTimeout(5000);
  KIdleTime::instance()->addIdleTimeout(6000);
  KIdleTime::instance()->addIdleTimeout(7000);
}

void KeyboardIdle::timeoutReached(int id, int timeout) {
  Q_UNUSED(id)

  KIdleTime::instance()->catchNextResumeEvent();

  if (timeout < 7000)
    setupBacklight(6 - timeout / 1000);
  else
    setupCycle();
}

void KeyboardIdle::setupBacklight(uint8_t intensity) {

  LedKeyboard kbd;
  initKeyboard(kbd);

  uint8_t colorInt = intensity * segment;

  auto color = LedKeyboard::Color{colorInt, colorInt, colorInt};

  if (!kbd.open())
    return;
  if (!kbd.setAllKeys(color))
    return;
  if (!kbd.commit())
    return;
}

void KeyboardIdle::setupCycle() {
  LedKeyboard kbd;
  initKeyboard(kbd);

  auto nativeEffect = LedKeyboard::NativeEffect::breathing;
  auto nativeEffectPart = LedKeyboard::NativeEffectPart::all;
  auto color = LedKeyboard::Color{0xFF, 0xFF, 0xFF};
  auto period = std::chrono::seconds(5);
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
