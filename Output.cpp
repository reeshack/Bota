#include "G.h"

Output::Output()
{
  m_stream = new QTextStream(stdout, QIODevice::WriteOnly);

  connect(this, SIGNAL( readyDisplay(const QString&) ), SLOT( displayData(const QString&) ));
}

Output::~Output()
{
  delete m_stream;
}

void Output::display(QString str, TYPE type)
{
  switch (type) {
    case ERROR:
      str.prepend("!! ");
      break;
    case READ:
      str.prepend("<- ");
      break;
    case SEND:
      str.prepend("-> ");
      break;
    default:;
  }

  emit readyDisplay(str);
}

void Output::displayData(const QString& str)
{
  *m_stream << str << endl;
}
