#include <QGuiApplication>

#include "KeyboardIdle.h"

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  KeyboardIdle k;

  return app.exec();
}
