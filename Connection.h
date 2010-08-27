#ifndef CONNECTION_H
#define CONNECTION_H

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Connection : public QObject
{
  Q_OBJECT

public:
  Connection                    (const QString&, const quint16& = 6667);
  ~Connection();

  void send                     (const QByteArray&);

signals:
  void readySend                (const QByteArray&);

private slots:
  void errorOccured             (QAbstractSocket::SocketError);
  void load();
  void login();
  void sendData                 (const QByteArray&);
  void quit();

private:
  QTcpSocket*                   m_socket;
  QString                       m_server;
  quint16                       m_port;
};

#endif