#ifndef LATEXTRANSLATOR_H
#define LATEXTRANSLATOR_H

#include <QString>
#include "languageelement.h"

class LatexTranslator
{
    //DA QUI
    QString temp;
    //A QUI
public:
    LatexTranslator();

    QString translate(LanguageElement element);

    //get code in simple code
    static QString getImage(QString path);
};

#endif // LATEXTRANSLATOR_H
