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
    void insertOnCursor(QString text);

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();
    void saveFile();
    void loadFile();
    void realLoadFile(QString filepath);
    void generate();
    void onParsingError(QString error);

    void on_actionImage_triggered();

    void on_actionCapitolo_triggered();

    void on_actionSezione_triggered();

    void on_actionSottosezione_triggered();

    void on_actionNota_pi_di_pagina_triggered();

    void on_actionRiferimento_a_Immagine_triggered();

    void on_actionSaveNow_triggered();

private:
    Ui::MainWindow *ui;
    SimpleLatexParser * parser;

    QString project_path;
};

#endif // MAINWINDOW_H
