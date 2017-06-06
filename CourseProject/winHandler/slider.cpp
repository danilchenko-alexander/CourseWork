#include "slider.h"

Slider :: Slider() :QDialog()
{
    spinbox = new QSpinBox;
    slider = new QSlider(Qt::Horizontal);
    spinbox->setMaximum(150);
    slider->setMaximum(150);

    box1 = new QCheckBox("In seconds");
    box2 = new QCheckBox("In minutes");

    label = new QLabel;

    ok = new QPushButton("Ok");
    ok->setEnabled(false);
    close = new QPushButton("Close");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(spinbox);
    layout->addWidget(slider);

    QVBoxLayout *right = new QVBoxLayout;
    right->addLayout(layout);
    right->addWidget(box1);
    right->addWidget(box2);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(ok);
    left->addWidget(close);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(right);
    main->addLayout(left);

    setLayout(main);
    setWindowTitle("Time");

    QObject::connect(spinbox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinbox,SLOT(setValue(int)));

    connect(box1,SIGNAL(clicked(bool)),ok,SLOT(setEnabled(bool)));
    connect(box2,SIGNAL(clicked(bool)),ok,SLOT(setEnabled(bool)));
    connect(box1,SIGNAL(clicked(bool)),box2,SLOT(setDisabled(bool)));
    connect(box2,SIGNAL(clicked(bool)),box1,SLOT(setDisabled(bool)));

    connect(close,SIGNAL(clicked()),this,SLOT(close()));
}

void Slider::ClickedWithSuspendState()
{
    setVisible(false);
    if(box1->isChecked())
        emit inSecondsSuspendState(slider->value());
    if(box2->isChecked())
        emit inMinutesSuspendState(slider->value());
}

void Slider::ClickedWithSystemShutdown()
{
    setVisible(false);
    if(box1->isChecked())
        emit inSecondsSystemShutdown(slider->value());
    if(box2->isChecked())
        emit inMinutesSystemShutdown(slider->value());
}

void Slider::ClickedWithSystemRestart()
{
    setVisible(false);
    if(box2->isChecked())
        emit inSecondsSystemRestart(slider->value());
    if(box1->isChecked())
        emit inMinutesSystemRestart(slider->value());
}
