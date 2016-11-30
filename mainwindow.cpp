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
#include <QCursor>
#include <QSettings>

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

    //saving path and thesis file persistently for later use
    QSettings settings("ReavSoft", "TesiMaker");
    QString projectpath = settings.value("projectpath").toString();
    QString filepath = settings.value("projectsaved").toString();

    if(!projectpath.isEmpty()){ project_path = projectpath; }
    if(!filepath.isEmpty()){ realLoadFile(filepath); }
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
    QString filepath;
    if(project_path.isEmpty()){
        filepath = QFileDialog::getSaveFileName(this,"Save file",QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                    "Tesi Maker (*.tmu);;All files (*.*)");
    } else {
        filepath = QFileDialog::getSaveFileName(this,"Save file",project_path,
                                                    "Tesi Maker (*.tmu);;All files (*.*)");
    }

    //window has been closed without specifying a correct folder
    if(filepath.isEmpty()){
        return;
    }

    QDir d = QFileInfo(filepath).absoluteDir();
    project_path = d.absolutePath();

    //saving path and thesis file persistently for later use
    QSettings settings("ReavSoft", "TesiMaker");
    settings.setValue("projectpath", project_path);
    settings.setValue("projectsaved", filepath);


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
        LatexTranslator t;
        latex += t.translate(elements.at(i));
    }

    //writing file
    QString filepath = project_path+"/tsmkr.tex";
    QFile file( filepath );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << latex;
    }

    //saving path and thesis file persistently for later use
    QSettings settings("ReavSoft", "TesiMaker");
    QString path = settings.value("projectpath").toString();

    //compiling
    QProcess latexprocess;
    latexprocess.setWorkingDirectory(project_path);
    latexprocess.start("pdflatex", QStringList() << "-output-directory="+path << filepath);
    latexprocess.waitForFinished();

    //opening pdf
    QProcess openpdf;
    openpdf.start("xdg-open", QStringList() << path+"/tsmkr.pdf");
    openpdf.waitForFinished();
}

/**
 * @brief used as a slot for buttons
 */
void MainWindow::loadFile()
{
    //saving path and thesis file persistently for later use
    QSettings settings("ReavSoft", "TesiMaker");
    QString path = settings.value("projectpath").toString();
    QString filepath;
    if(path.isEmpty()){
        filepath = QFileDialog::getOpenFileName(this,"Open File",QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                    "Tesi Maker (*.tmu);;All files (*.*)");
    } else {
        filepath = QFileDialog::getOpenFileName(this,"Open File",path,
                                                    "Tesi Maker (*.tmu);;All files (*.*)");
    }
    //window has been closed without specifying a correct folder
    if(filepath.isEmpty()){
        return;
    }

    QDir d = QFileInfo(filepath).absoluteDir();
    project_path = d.absolutePath();

    settings.setValue("projectpath", project_path);
    settings.setValue("projectsaved", filepath);

    realLoadFile(filepath);
}

/**
 * @brief actually loads a file
 * @param file
 */
void MainWindow::realLoadFile(QString filepath)
{
    qDebug() << "loading " << filepath;
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

void MainWindow::on_actionImage_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this,"Load Image",QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0),
                                                    "All files (*.*)");

    QFileInfo fileinfo(filepath);
    QString filename(fileinfo.fileName());
    QFile::copy(filepath, project_path+"/"+filename);

    QCursor cursor = ui->textEdit->cursor();
    int line, index;
    ui->textEdit->getCursorPosition(&line,&index);
    ui->textEdit->insertAt(LatexTranslator::getImage(filename),line,index);
}
