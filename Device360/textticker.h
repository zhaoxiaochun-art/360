#pragma once
#include <QLabel>
#include <QPainter>
#include <QTimer>

class TextTicker : public QLabel
{
    Q_OBJECT
public:
    TextTicker(QWidget *parent = nullptr);
    ~TextTicker();
	QString m_showText;
	int m_allIndex;
protected:
    void paintEvent(QPaintEvent *event);
    void updateIndex();
private:
    int m_charWidth;
	int m_curIndex;
};
