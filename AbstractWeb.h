#ifndef ABSTRACT_WEB_H
#define ABSTRACT_WEB_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class AbstractWeb : public QObject
{
  Q_OBJECT

protected:
  QNetworkAccessManager* m_manager;
  QString      m_address;
  QByteArray   m_sender;
  static uint  m_time;

  void start();
  uint now();

public:
  AbstractWeb(const QString&, const QByteArray&);
  ~AbstractWeb();

protected slots:
  virtual void replyFinished(QNetworkReply*) = 0;
};

#endif