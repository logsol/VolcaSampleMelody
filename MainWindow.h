#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RtMidi.h"
#include <CoreAudio/CoreAudio.h>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void catchMidi(double deltatime, std::vector<unsigned char> *message, void *userData);

public slots:
    void update_for_read();

private slots:
    void on_inputPorts_currentIndexChanged(int index);
    void on_outputPorts_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_sample_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    RtMidiIn* midiIn;
    RtMidiOut* midiOut;
    unsigned int inputPortIndex = 0;
    unsigned int outputPortIndex = 0;
    unsigned int selectedSample = 1;

    void listMidiInputPorts();
    void listMidiOutputPorts();
};

#endif // MAINWINDOW_H
