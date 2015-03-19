#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QStringList>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    try {
        midiIn = new RtMidiIn();
    } catch (RtMidiError &error) {
        exit(EXIT_FAILURE);
    }

    try {
        midiOut = new RtMidiOut();
    } catch (RtMidiError &error) {
        exit(EXIT_FAILURE);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_for_read()));
    timer->start(5);

    ui->setupUi(this);

    listMidiInputPorts();
    listMidiOutputPorts();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete midiIn;
    delete midiOut;
}

void MainWindow::listMidiInputPorts()
{
    QStringList list;
    unsigned int nPorts = midiIn->getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        list << QString::fromStdString(midiIn->getPortName(i));
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
    unsigned int nPorts = midiOut->getPortCount();
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        list << QString::fromStdString(midiOut->getPortName(i));
      }
      catch ( RtMidiError &error ) {
        ui->statusBar->showMessage(QString::fromStdString(error.getMessage()));
      }
    }
    ui->outputPorts->addItems(list);
}

void MainWindow::on_inputPorts_currentIndexChanged(int index)
{
    midiIn->closePort();
    inputPortIndex = index;
    midiIn->openPort(inputPortIndex);
    midiIn->ignoreTypes(true, true, true);
}

void MainWindow::on_outputPorts_currentIndexChanged(int index)
{
    midiOut->closePort();
    outputPortIndex = index;
    midiOut->openPort(outputPortIndex);
}

void MainWindow::on_pushButton_clicked()
{
    std::vector<unsigned char> outputMessage;
    outputMessage.push_back(144); // noteon ch1
    outputMessage.push_back(64);  // note 64
    outputMessage.push_back(100); // vel 100
    midiOut->sendMessage(&outputMessage);
}

void MainWindow::update_for_read()
{
    std::vector<unsigned char> message;
    midiIn->getMessage(&message);

    if (message.size() >= 3) {
        unsigned int byte0 = message.at(0);
        unsigned int byte1 = message.at(1);
        unsigned int byte2 = message.at(2);
        unsigned int channel;
        bool isNoteOn = false;
        bool isNoteOff = false;

        if (byte0 >= 128 && byte0 <= 143) {
            channel = byte0 - 127;
            isNoteOff = true;
        }
        if (byte0 >= 144 && byte0 <= 159) {
            channel = byte0 - 143;

            if (byte2 == 0) {
                isNoteOff = true;
            } else {
                isNoteOn = true;
            }
        }

        if (isNoteOn || isNoteOff) {
            if (isNoteOn) {
                std::vector<unsigned char> pitchMessage;

                // translate from key to cc value
                float pitch = ((float) byte1) / 12.0 * 32.0;

                pitchMessage.push_back(175 + selectedSample);
                pitchMessage.push_back(43); // cc for speed on volca
                pitchMessage.push_back(floor(pitch) - 72);

                midiOut->sendMessage(&pitchMessage);
            }

            message[0] = byte0 - channel + selectedSample;
            midiOut->sendMessage(&message);
        }
    }
}

void MainWindow::on_sample_currentIndexChanged(int index)
{
    selectedSample = index + 1;
}
