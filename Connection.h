#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>

class Connection : public QThread
{
  Q_OBJECT

private:
  QTcpSocket* m_socket;
  QString     m_server;
  quint16     m_port;

protected:
  void run();

public:
  Connection(const QString&, const quint16& = 6667);
  ~Connection();

  void send(const QByteArray&);

private slots:
  void dying();
  void errorOccured(QAbstractSocket::SocketError);
  void load();
  void login();
  void quit();
};

#endif