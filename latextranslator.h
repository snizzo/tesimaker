#ifndef LATEXTRANSLATOR_H
#define LATEXTRANSLATOR_H

#include <QString>
#include "languageelement.h"

class LatexTranslator
{
public:
    LatexTranslator();

    static QString translate(LanguageElement element);
};

#endif // LATEXTRANSLATOR_H
