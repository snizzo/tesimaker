#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

#include <QtGui/QColor>
#include <QtCore/QDebug>

#include "Qsci/qscilexerpython.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    ## Choose a lexer
    lexer = QsciLexerPython()
    lexer.setDefaultFont(font)
    editor.setLexer(lexer)
    */

    ui->textEdit->setMarginWidth(0,"00000");
    ui->textEdit->setMarginLineNumbers(0, true);

    //ui->textEdit->setEdgeMode(QsciScintilla::EdgeLine);
    //ui->textEdit->setEdgeColumn(80);
    //ui->textEdit->setEdgeColor(QColor("#FF0000"));

    ui->textEdit->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    ui->textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    ui->textEdit->setCaretLineVisible(true);
    ui->textEdit->setCaretLineBackgroundColor(QColor("#CDA869"));
    ui->textEdit->setMarginsBackgroundColor(QColor("#333333"));
    ui->textEdit->setMarginsForegroundColor(QColor("#CCCCCC"));
    ui->textEdit->setFoldMarginColors(QColor("#99CC66"),QColor("#333300"));

    QsciLexerPython * lexer = new QsciLexerPython;
    ui->textEdit->setLexer(lexer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about;
    about.exec();
}
