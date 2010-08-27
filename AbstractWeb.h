#ifndef ABSTRACT_WEB_H
#define ABSTRACT_WEB_H

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>

class AbstractWeb : public QObject
{
  Q_OBJECT

public:
  AbstractWeb                   (const QString&, const QByteArray&);
  ~AbstractWeb                  ();

protected:
  uint now                      () const;
  void start                    ();

protected slots:
  virtual void replyFinished    (QNetworkReply*) = 0;

protected:
  QNetworkAccessManager*        m_manager;
  QString                       m_address;
  QByteArray                    m_sender;
  static uint                   m_time;
};

#endif