#include "G.h"
#include <QCoreApplication>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  app.setApplicationName("Bota");

  G::out = new Output();
  G::in  = new Input();
  G::in->start();

  G::con = new Connection(G::server);

  return app.exec();
}
