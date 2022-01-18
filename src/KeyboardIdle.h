#pragma once

#include <QObject>
#include <g810-led/Keyboard.h>

class KeyboardIdle : public QObject {
  Q_OBJECT

  static constexpr uint8_t maxValue = 0xFF;

public:
  KeyboardIdle();
  ~KeyboardIdle();

public Q_SLOTS:
  void timeoutReached(int id, int timeout);
  void resumeEvent();

private:
  void setupBacklight(uint8_t intensity);
  void setupCycle(uint8_t intensity, uint8_t duration);
  void initKeyboard(LedKeyboard &kbd);
};
