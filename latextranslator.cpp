#include "latextranslator.h"

#include "languageelement.h"
#include <QString>
#include <QDebug>

LatexTranslator::LatexTranslator()
{

}

QString LatexTranslator::translate(LanguageElement element)
{
    /*
     * Stringa di output. Qualsiasi output in latex
     * andrà appeso alla fine della stringa output.
     *
     * esempio:
     * output += output + "ciao mondo";
     */
    QString output;
    /*
     * Contiene il tipo di elemento.
     * Se è "tag" allora l'elemento è un tag e data conterrà il nome del tag
     * se è "text" allora data conterrà direttamente il testo in formato stringa
     */
    QString type = element.getType();
    QString data = element.getData();

    /*
     * questi snippet valgono solo e solamente nel caso in cui type=="tag"
     * e quindi il tag abbia i suoi attributi chiave=valore
     */
    if(element.containsAttribute("chiave")){
        //esempio con [tesi chiave=valore]
        QString valore = element.getAttribute("chiave");
        //valore adesso conterrà la stringa "valore"
    }

    //se l'elemento è un tag...
    if(type=="tag"){

        //se il tag è "tesi"...
        if(data=="tesi"){
            //recupero il valore di punti
            if(element.containsAttribute("punti")){
                QString punti = element.getAttribute("punti");
                output += "\\documentclass["+punti+"pt]{article}\n"
                          "\\begin{document}\n";
            }
        }

        if(data=="fine:tesi"){
            output += "\\end{document}\n";
        }

    } else {
        output += data;
    }

    return output;
}
