#include "Bash.h"
#include "G.h"
#include <QTimer>

Input::Input()
{
  m_stream  = new QTextStream(stdin, QIODevice::ReadOnly);
}

Input::~Input()
{
  delete m_stream;
}

void Input::handleUserCommand(QString& cmd)
{
  cmd = cmd.mid(1);

  QString param;
  int upto = cmd.indexOf(' ');
  if (upto > -1) {
    param = cmd.mid(upto+1);
    cmd = cmd.left(upto);
  }

  // Bash Cooldown
  if (cmd == "CD") {
    bool ok;
    uint cd = param.toUInt(&ok);
    if (!ok) {
      G::out->display("Setting bash CD failed.", Output::ERROR);
    } else {
      Bash::setCooldown(cd);
      QByteArray msg = "PRIVMSG " + G::channel + " :Bash cooldown sets to ";
      msg.append( cmd.setNum(cd) );
      msg.append(" sec.");
      G::con->send(msg);
    }
  }
}

void Input::run()
{
  QTimer timer;
  connect(&timer, SIGNAL( timeout() ), this, SLOT( readInput() ), Qt::DirectConnection);
  timer.start(100);

  exec();
}

void Input::readInput()
{
  QString text;
  text = m_stream->readLine();

  if ( text.isNull() || !text.trimmed().length() )
    return;

  if ( text.startsWith('.') ) {
    handleUserCommand(text);
  } else {
    G::con->send( text.toUtf8() );
    G::out->display(text, Output::SEND);
  }
}
