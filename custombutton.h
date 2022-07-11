#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QToolButton>

class CustomButton : public QToolButton {
Q_OBJECT
 public:
  CustomButton(const QString &text, const QColor &color, QWidget *parent = 0);
  QSize sizeHint() const;
};

#endif // CUSTOMBUTTON_H
