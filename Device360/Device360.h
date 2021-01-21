#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Device360.h"

class Device360 : public QMainWindow
{
    Q_OBJECT

public:
    Device360(QWidget *parent = Q_NULLPTR);

private:
    Ui::Device360Class ui;
};
