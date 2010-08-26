#include <QtGui/QApplication>
#include "G.h"

// TODO Logger, History .. ?

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  G::gui = new IO();
  G::gui->show();

  G::con = new Connection("irc.rizon.net");
  G::con->start();

  return app.exec();
}
