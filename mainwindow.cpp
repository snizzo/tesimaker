#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "simplelatexparser.h"
#include "languageelement.h"
#include "latextranslator.h"

#include <QtGui/QColor>
#include <QtCore/QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVector>
#include <QProcess>

#include "Qsci/qscilexerpython.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //instantiating parser
    parser = new SimpleLatexParser;

    ui->setupUi(this);

    ui->textEdit->setMarginWidth(0,"00000");
    ui->textEdit->setMarginLineNumbers(0, true);

    ui->textEdit->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    ui->textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    ui->textEdit->setCaretLineVisible(true);
    ui->textEdit->setCaretLineBackgroundColor(QColor("#CDA869"));
    ui->textEdit->setMarginsBackgroundColor(QColor("#333333"));
    ui->textEdit->setMarginsForegroundColor(QColor("#CCCCCC"));
    ui->textEdit->setFoldMarginColors(QColor("#99CC66"),QColor("#333300"));

    QsciLexerPython * lexer = new QsciLexerPython;
    ui->textEdit->setLexer(lexer);

    //parser connections
    connect(parser, SIGNAL(errorParsing(QString)), this, SLOT(onParsingError(QString)));
    //menu connections
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadFile()));
    connect(ui->action_Genera, SIGNAL(triggered(bool)), this, SLOT(generate()));

    /*
    QStringList translation;

    QString str2("[tesi]"
                "ciaomondo[grasetto]io sono belllo 9.45[fine:grassetto]"
                "[finee:tesi]");
    QString str("[]");

    // Insert the string into the input stream.
    YY_BUFFER_STATE bufferState = yy_scan_string(str.toUtf8().constData());

    // Parse the string.
    yyparse();

    // flush the input stream.
    yy_delete_buffer(bufferState);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile()
{
    QString filepath = QFileDialog::getSaveFileName(this,"Save file",QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                    "Tesi Maker (*.tmu);;All files (*.*)");
    if(!filepath.contains(".tmu")){
        filepath = filepath + ".tmu";
    }
    QString content = ui->textEdit->text();

    QFile file( filepath );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << content;
    } else {
        qDebug() << "error saving file!";
    }
}

void MainWindow::generate()
{
    //splitting down simple language to elements
    QVector<LanguageElement> elements = parser->generateElements(ui->textEdit->text());
    QString latex;

    //translating elements to latex
    for(int i=0;i<elements.length();i++)
    {
        latex += LatexTranslator::translate(elements.at(i));
    }

    //writing file
    QString filepath = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0)+"/tsmkr.tex";
    QFile file( filepath );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << latex;
    }

    //compiling
    QProcess latexprocess;
    latexprocess.start("pdflatex", QStringList() << "-output-directory="+QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0) << filepath);
    latexprocess.waitForFinished();

    //opening pdf
    QProcess openpdf;
    openpdf.start("xdg-open", QStringList() << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0)+"/tsmkr.pdf");
    openpdf.waitForFinished();
}

void MainWindow::loadFile()
{
    QString filepath = QFileDialog::getOpenFileName(this,"Open File",QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                    "Tesi Maker (*.tmu);;All files (*.*)");

    QFile file(filepath);
    QString content;
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        ui->textEdit->setText(stream.readAll());
    }

}

/**
 * @brief handle parsing errors
 * @param error occured when parsing text
 */
void MainWindow::onParsingError(QString error)
{

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
