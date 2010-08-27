#include "G.h"
#include "ReplyHandler.h"
#include <QCoreApplication>
#include <QList>

Connection::Connection(const QString& server, const quint16& port) : m_server(server), m_port(port)
{
  m_socket = new QTcpSocket(this);

  connect(m_socket, SIGNAL( connected() ),    SLOT( login() ));
  connect(m_socket, SIGNAL( disconnected() ), SLOT( quit() ));
  connect(m_socket, SIGNAL( error(QAbstractSocket::SocketError) ), SLOT( errorOccured(QAbstractSocket::SocketError) ));
  connect(m_socket, SIGNAL( readyRead() ),    SLOT( load() ));
  connect(this,     SIGNAL( readySend(const QByteArray&) ), SLOT( sendData(const QByteArray&) ));

  m_socket->connectToHost(m_server, m_port);
  G::out->display("Connecting to " + m_server + "...", Output::SEND);
}

Connection::~Connection()
{
  delete m_socket;
}

void Connection::send(const QByteArray& data)
{
  emit readySend(data);
}

void Connection::errorOccured(QAbstractSocket::SocketError)
{
  G::out->display( m_socket->errorString(), Output::ERROR);
}

void Connection::load()
{
  QByteArray data = m_socket->readAll();
  QList<QByteArray> replies = data.split('\n');
  QList<QByteArray>::iterator i;

  for (i = replies.begin(); i != replies.end(); ++i) {
    *i = i->trimmed();
    if(i->length()) {
      ReplyHandler::handle(*i);
    }
  }
}

void Connection::login()
{
  G::out->display("Connected. Authorization process started.", Output::SEND);
  QByteArray data;
  data.append("PASS nopass\r\n");
  data.append("NICK " + G::nick + "\r\n");
  data.append("USER audiobota bohnicecz xray :Pamela Anderson");
  send(data);
}

void Connection::sendData(const QByteArray& data)
{
  m_socket->write(data + "\r\n");
  m_socket->flush();
}

void Connection::quit()
{
  G::out->display("Disconnected.", Output::READ);
  m_socket->close();

  QCoreApplication::exit();
}
