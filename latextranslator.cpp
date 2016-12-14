#include "latextranslator.h"

#include "languageelement.h"
#include <QString>
#include <QDebug>

LatexTranslator::LatexTranslator()
{

}

QString LatexTranslator::translate(LanguageElement element)
{
    qDebug() << element;
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
                output += "\\documentclass["+punti+"pt]{book}\n"
                          "\n"
                          "\\usepackage{graphicx}\n" //per imamgini
                          "\\usepackage{amsmath}\n" //per la matematica
                          "\\usepackage[utf8x]{inputenc}\n" //per gli accenti
                          "\\usepackage{varioref}" //per i riferimenti
                          "\\usepackage{blindtext}\n" //lorem ipsum per testing. Uso:
                                                      //\blindtext o \blindtext[numero_di_ripetizioni] es \blindtext[5]
                          "\n"
                          "\\begin{document}\n"
                          "\n";
            }
        }

        if(data=="fine:tesi"){
            output += "\n"
                      "\\end{document}\n";
        }

        qDebug() << element;
        //se il tag è "immagine"...
        if(data=="immagine"){
            //recupero il nome dell'imamgine e la dimensione
            QString descrizione = element.getAttribute("descrizione");
            if(descrizione.isEmpty()){ descrizione = ""; }
            QString dim = element.getAttribute("dim");
            if(dim.isEmpty()){ dim = ".5"; }
            QString nome = element.getAttribute("nome");
            if(nome.isEmpty()){ nome = ""; }
            output += "\\begin{figure}[tb]\n"
                      "\\centering\n"
                      "\\includegraphics[width="+dim+"\\textwidth]{"+nome+"}\n";
            if(!descrizione.isEmpty()){ output += "\\caption{"+descrizione+"}\n"; }
            output += "\\label{"+nome+"}\n"
                      "\\end{figure}\n"
                      "\n";
        }

        //se il tag è "formula"...
        if(data=="formula"){
            //numerazione o no
            QString numerazione = element.getAttribute("numerazione");
            if(numerazione.isEmpty()){ output += "\\begin{equation*}\n"; }
// DA SISTEMARE (se non ha 'numerazione' metti *. Se 'numerazione'='si' allora non metterlo, altrimenti metti *
//            if(!numerazione.isEmpty()){
//                if(element.containsAttribute("numerazione")){
//                    if(QString numerazione = "si"){
//                        output += "\\begin{equation}\n";
//                    }
//                    else{
//                        output += "\\begin{equation*}\n";
//                    }
//                }
//            }
//            temp = numerazione;
       }

        if(data=="fine:formula"){
// output da cancellare dopo aver sistemato la questione della numerazione
            output += "\n"
                      "\\end{equation*}\n"
                      "\n";
//            QString numerazione = temp;
//            if(numerazione.isEmpty()){ output += "\n"
//                                                 "\\end{equation*}\n"
//                                                 "\n"; }
//            if(!numerazione.isEmpty()){
//                if(element.containsAttribute("numerazione")){
//                QString numerazione = "si";
//                output += "\n"
//                          "\\end{equation}\n"
//                          "\n";
//                }
//                else{
//                output += "\n"
//                          "\\end{equation*}\n"
//                          "\n";
//                }
//            }
        }

        if(data=="capitolo"){
            if(element.containsAttribute("titolo")){
                QString titolo = element.getAttribute("titolo");
                output += "\n"
                          "\\chapter{"+titolo+"}\n"
                          "\n";
            }
        }

        if(data=="sezione"){
            if(element.containsAttribute("titolo")){
                QString titolo = element.getAttribute("titolo");
                output += "\n"
                          "\\section{"+titolo+"}\n"
                          "\n";
            }
        }

        if(data=="sottosezione"){
            if(element.containsAttribute("titolo")){
                QString titolo = element.getAttribute("titolo");
                output += "\n"
                          "\\subsection{"+titolo+"}\n"
                          "\n";
            }
        }

        if(data=="nota"){
            if(element.containsAttribute("testo")){
                QString testo = element.getAttribute("testo");
                output += "\\footnote{"+testo+"}";
            }
        }

        //nota: dà problemi se per un'immagine si fanno 2 o più riferimenti
        if(data=="fig"){
            if(element.containsAttribute("nome")){
                QString nome = element.getAttribute("nome");
                output += "fig.~\\vref{"+nome+"}";
            }
        }

    } else {
        output += data;
    }

    return output;
}

//qua vanno inseriti i tag demo che vengono aggiunti con il menù "inserisci"
QString LatexTranslator::getImage(QString path)
{
    return QString("[immagine dim=\".5\" nome=\""+path+"\"]");
}

QString LatexTranslator::getCapitolo()
{
    return QString("[capitolo titolo=\"\"]");
}

QString LatexTranslator::getSezione()
{
    return QString("[sezione titolo=\"\"]");
}

QString LatexTranslator::getSottosezione()
{
    return QString("[sottosezione titolo=\"\"]");
}

QString LatexTranslator::getNota()
{
    return QString("[nota testo=\"\"]");
}

QString LatexTranslator::getRiferimento()
{
    return QString("[fig nome=\"\"]");
}
