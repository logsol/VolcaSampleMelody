#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include "RtMidi.h"
#include <CoreAudio/CoreAudio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listMidiInputPorts();
    listMidiOutputPorts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listMidiInputPorts()
{
    QStringList list;
    RtMidiIn midiIn;
    unsigned int nPorts = midiIn.getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        list << QString::fromStdString(midiIn.getPortName(i));
      }
      catch ( RtMidiError &error ) {
        ui->statusBar->showMessage(QString::fromStdString(error.getMessage()));
      }
    }
    ui->inputPorts->addItems(list);
}
void MainWindow::listMidiOutputPorts()
{
    QStringList list;
    RtMidiOut midiOut;
    unsigned int nPorts = midiOut.getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        list << QString::fromStdString(midiOut.getPortName(i));
      }
      catch ( RtMidiError &error ) {
        ui->statusBar->showMessage(QString::fromStdString(error.getMessage()));
      }
    }
    ui->outputPorts->addItems(list);
}
