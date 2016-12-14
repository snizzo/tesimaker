#ifndef LATEXTRANSLATOR_H
#define LATEXTRANSLATOR_H

#include <QStack>
#include <QString>
#include "languageelement.h"

class LatexTranslator
{
    //DA QUI
    static QStack<QString> temp;
    //A QUI
public:
    LatexTranslator();

    QString translate(LanguageElement element);

    //get code in simple code
    static QString getImage(QString path);
    static QString getCapitolo();
    static QString getSezione();
    static QString getSottosezione();
    static QString getNota();
    static QString getRiferimento();
};

#endif // LATEXTRANSLATOR_H
