#include "simplelatexparser.h"

//qt specific
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QVector>

//program specific
#include "languageelement.h"

SimpleLatexParser::SimpleLatexParser()
{

}

/**
 * @brief generateAndCompileCode
 * Directly called by mainwindow.
 * All others are internals.
 */
QVector<LanguageElement> SimpleLatexParser::generateElements(QString data)
{
    return buildCommandList(data);
}

/**
 * @brief SimpleLatexParser::buildCommandList
 * @return command list after a simple parsing operation
 */
QVector<LanguageElement> SimpleLatexParser::buildCommandList(QString data)
{
    QVector<LanguageElement> content;

    QString buffer;

    ParserStatus status = PARSING;

    for(int i=0;i<data.length();i++){

        //open brackets
        if(data[i]==QLatin1Char('[')){
            switch(status){
                case(PARSING):
                    status = INSIDETAG;
                    if(!buffer.isEmpty()){
                        LanguageElement e;
                        e.setType("text");
                        e.setData(buffer);
                        content.append(e);
                        buffer.clear();
                    }
                    continue;
                case(INSIDETAG):
                    emit errorParsing(QString("Errore: Stai cercando di aprire un tag dentro ad un altro tag!"));
                    break;
            }
        }

        //close brackets
        if(data[i]==QLatin1Char(']')){
            switch(status){
                case(PARSING):
                    emit errorParsing(QString("Errore: Stai cercando di chiudere un tag senza averne aperto uno!"));
                    break;
                case(INSIDETAG):
                    status = PARSING;
                    if(!buffer.isEmpty()){
                        LanguageElement e;
                        e.setType("tag");
                        e.setData(buffer);
                        content.append(e);
                        buffer.clear();
                    }
                    continue;
            }
        }

        //ignore scintilla newline
        if(data[i]==QLatin1Char('\xa')){
            continue;
        }

        //default case
        buffer.append(data[i]);
    }

    return content;
}
