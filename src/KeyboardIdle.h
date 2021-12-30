#ifndef KEYBOARDIDLE_H
#define KEYBOARDIDLE_H

#include <QObject>
#include <g810-led/Keyboard.h>

class KeyboardIdle : public QObject {
  Q_OBJECT

  static constexpr uint8_t segment = 0xFF / 5;

public:
  KeyboardIdle();
  ~KeyboardIdle();

public Q_SLOTS:
  void timeoutReached(int id, int timeout);
  void resumeEvent();

private:
  void setupBacklight(uint8_t intensity);
  void setupCycle();
  void initKeyboard(LedKeyboard &kbd);
};

#endif /* KEYBOARDIDLE_H */
