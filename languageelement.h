#ifndef LANGUAGEELEMENT_H
#define LANGUAGEELEMENT_H

#include <QString>
#include <QMap>

class LanguageElement
{
    /*
     * Can be "tag" or "text"
     *
     * Being tag an actual tag to be translated
     * and text real human readable text with possible
     * latex.
     */
    QString type;
    /*
     * If the type is "tag", data will contain the name of the tag. E.g. [tesi] will have element->getData() being "tesi"
     * If the type is "text", data will contain the actual text data of the block
     */
    QString data;
    QMap<QString, QString> attributes;

    //internal parametere parsing
    enum ParserStatus { TITLE,PARAMID,PARAMVALUE };

    public:
        LanguageElement();

        void setType(QString t);
        QString getType();

        void addAttribute(QString key, QString value);
        bool containsAttribute(QString key);
        QString getAttribute(QString key);

        void setData(QString d);
        QString getData();
        void parseAttributes(QString str);

        //operator override
        operator QString() const;

};

#endif // LANGUAGEELEMENT_H
