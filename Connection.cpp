#include "G.h"
#include "ReplyHandler.h"
#include <QtCore/QList>

Connection::Connection(const QString& server, const quint16& port) : m_server(server), m_port(port)
{
  m_socket = new QTcpSocket(this);

  connect(m_socket, SIGNAL( connected() ),    SLOT( login() ));
  connect(m_socket, SIGNAL( disconnected() ), SLOT( quit() ));
  connect(m_socket, SIGNAL( error(QAbstractSocket::SocketError) ), SLOT( errorOccured(QAbstractSocket::SocketError) ));
  connect(m_socket, SIGNAL( readyRead() ),    SLOT( load() ));

  connect(this,     SIGNAL( finished() ),     SLOT( dying() ));
}

Connection::~Connection()
{
  delete m_socket;
  G::gui->display("The Connection object has been deallocated.");
}

void Connection::run()
{
  // Make a connection
  m_socket->connectToHost(m_server, m_port);
  G::gui->display("Connecting to " + m_server + "...");
  exec();
}

void Connection::send(const QByteArray& data)
{
  m_socket->write(data + "\r\n");
  m_socket->flush();
  G::gui->display(data, IO::SEND);
}

void Connection::dying()
{
  G::gui->display("Exiting the Connection thread.");
}

void Connection::errorOccured(QAbstractSocket::SocketError error)
{
  G::gui->display( m_socket->errorString() , IO::ERROR);
}

void Connection::load()
{
  QByteArray data = m_socket->readAll();
  QList<QByteArray> replies = data.split('\n');
  QList<QByteArray>::iterator i;

  for (i = replies.begin(); i != replies.end(); ++i) {
    *i = i->trimmed();
    if(!i->length())
      continue;

    G::gui->display(*i, IO::READ);
    ReplyHandler::handle(*i);
  }
}

void Connection::login()
{
  G::gui->display("Connected.");
  QByteArray data;
  data.append("PASS nopass\r\n");
  data.append("NICK " + G::nick + "\r\n");
  data.append("USER audiobota bohnicecz xray :Pamela Anderson");
  send(data);
}

void Connection::quit()
{
  // Disconnect and dealloc
  G::gui->display("Disconnected.");
  m_socket->close();
}
