#ifndef OUTPUT_H
#define OUTPUT_H

#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTextCursor>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

class IO : public QMainWindow
{
  Q_OBJECT

public:
  enum TYPE {
    COMMON,
    ERROR,
    READ,
    SEND
  };

private:
  QWidget* m_central;
  QHBoxLayout* m_bottomLayout;
  QVBoxLayout* m_layout;
  QPushButton* m_button;
  QLineEdit* m_in;
  QTextEdit* m_out;

  void construct();
  void handleUserCommand(QString&);

public:
  IO(QWidget* = 0);
  ~IO();
  void display(const QString&, TYPE = COMMON);

signals:
  void toDisplay(const QString&);

private slots:
  void handleInput();
  void output(const QString&);
};

#endif