#include "languageelement.h"
#include <QDebug>

LanguageElement::LanguageElement()
{

}

void LanguageElement::setType(QString t)
{
    this->type = t;
}

QString LanguageElement::getType()
{
    return this->type;
}

void LanguageElement::addAttribute(QString key, QString value)
{
    this->attributes.insert(key, value);
}

bool LanguageElement::containsAttribute(QString key)
{
    return this->attributes.contains(key);
}

QString LanguageElement::getAttribute(QString key)
{
    if(containsAttribute(key)){
        return this->attributes[key];
    } else {
        return "";
    }
}

void LanguageElement::setData(QString d)
{
    if(type=="text"){
        data = d;
    }

    if(type=="tag"){
        //convert data in object attributes
        parseAttributes(d);
    }
}

QString LanguageElement::getData()
{
    return data;
}

void LanguageElement::parseAttributes(QString str)
{
    if(!str.isEmpty()){
        QString buffer;

        QString buffer2;
        QString id;


        ParserStatus status = TITLE;

        for(int i=0;i<str.length();i++){
            //open brackets
            if(str[i]==QLatin1Char(' ')){
                switch(status){
                    case(TITLE):
                        if(buffer.isEmpty()){
                            continue;
                        } else {
                            status = PARAMID;
                            id = buffer;
                            buffer.clear();
                        }
                        continue;
                    case(PARAMVALUE):
                        if(buffer.isEmpty()){
                            continue;
                        } else {
                            status = PARAMID;
                            addAttribute(buffer2,buffer);
                            buffer.clear();
                            buffer2.clear();
                        }
                        continue;
                    case(PARAMID):
                    if(buffer.isEmpty()){
                        continue;
                    }
                }
            }

            //ignore scintilla newline
            if(str[i]==QLatin1Char('=')){
                switch(status){
                    case(PARAMID):
                        if(buffer.isEmpty()){
                            continue;
                        } else {
                            status = PARAMVALUE;
                            buffer2 = buffer;
                            buffer.clear();
                        }
                        continue;
                }
            }

            //default case
            buffer.append(str[i]);
        }
        if(!buffer.isEmpty()){
            if(status==TITLE){
                data = buffer;
                buffer.clear();
            }
            if(status==PARAMVALUE){
                if(!buffer2.isEmpty()){
                    addAttribute(buffer2,buffer);
                    buffer2.clear();
                    buffer.clear();
                }
            }
        }
        if(!id.isEmpty()){
            data = id;
        }
    }
}

LanguageElement::operator QString() const
{
    QString output;

    output += "type: " + type +'\n';
    output += "data: " + data +'\n';

    if(type=="tag"){
        output += "attributes:\n";
        QMapIterator<QString, QString> i(attributes);
        while (i.hasNext()) {
            i.next();
            output += i.key() + ": " + i.value() + '\n';
        }
    }

    return output;
}
