#include "Bash.h"
#include "G.h"
#include <QTimer>

Input::Input()
{
  m_stream  = new QTextStream(stdin, QIODevice::ReadOnly);
  m_writeMode = false;
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
  else if (cmd == "SLAP") {
    QByteArray msg = "PRIVMSG " + G::channel + " :" + char(1) + "ACTION slaps " + param.toUtf8() + char(1);
    G::con->send(msg);
  }
  else if (cmd == "READMODON") {
    SetReadWriteMods(MOD_ENABLED,MOD_NO);
  }
  else if (cmd == "READMODOFF") {
    SetReadWriteMods(MOD_DISABLED,MOD_NO);
  }
  else if (cmd == "WRITEMODON") {
    SetReadWriteMods(MOD_NO,MOD_ENABLED);
  }
  else if (cmd == "WRITEMODOFF") {
    SetReadWriteMods(MOD_NO,MOD_DISABLED);
  }
  else if (cmd == "ALLMODSON") {
    SetReadWriteMods(MOD_ENABLED,MOD_ENABLED);
  }
  else if (cmd == "ALLMODSOFF") {
    SetReadWriteMods(MOD_DISABLED,MOD_DISABLED);
  }
}

void Input::SetReadWriteMods(uint read_mod, uint write_mod)
{
  if (read_mod == MOD_ENABLED)
  {
    G::con->setDisplay(true);
    G::out->display("Displaying messages enabled.", Output::READ);
  }
  else if (read_mod == MOD_DISABLED)
  {
    G::con->setDisplay(false);
    G::out->display("Displaying messages disabled.", Output::READ);
  }

  if (write_mod == MOD_ENABLED)
  {
    m_writeMode = true;
    G::out->display("Write mod enabled.", Output::READ);
  }
  else if (write_mod == MOD_DISABLED)
  {
    m_writeMode = false;
    G::out->display("Write mod disabled.", Output::READ);
  }
}

void Input::sendInputText(QString& string)
{
  QByteArray msg;
  // ACTION text handling
  if (string.startsWith("/me ")) {
    string = string.mid(4);
    msg = "PRIVMSG " + G::channel + " :" + char(1) + "ACTION " + string.toUtf8() + char(1);
  }
  else {
    msg = "PRIVMSG " + G::channel + " :" + string.toUtf8();
  }

  G::con->send(msg);
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
  }
  else if (m_writeMode) {
    sendInputText(text);
  }
  else {
    G::con->send( text.toUtf8() );
    G::out->display(text, Output::SEND);
  }
}
