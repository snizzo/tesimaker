#ifndef SIMPLELATEXPARSER_H
#define SIMPLELATEXPARSER_H

#include <QStringList>
#include <QObject>
#include <QVector>

#include "languageelement.h"

class SimpleLatexParser : public QObject
{
    Q_OBJECT
    enum ParserStatus { PARSING,INSIDETAG };

public:
    SimpleLatexParser();

    QVector<LanguageElement> generateElements(QString data);
    QVector<LanguageElement> buildCommandList(QString data);

signals:
    void errorParsing(QString error);
};

#endif // SIMPLELATEXPARSER_H
