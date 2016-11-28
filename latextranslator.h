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
};

#endif // LATEXTRANSLATOR_H
