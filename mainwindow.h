#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simplelatexparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();
    void saveFile();
    void loadFile();
    void generate();
    void onParsingError(QString error);

private:
    Ui::MainWindow *ui;
    SimpleLatexParser * parser;
};

#endif // MAINWINDOW_H
