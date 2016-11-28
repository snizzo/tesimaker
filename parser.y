/*
   Example using Flex and Bison with Qt.
   Copyright (C) 2013  Gonzalo Exequiel Pedone

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with This program.  If not, see <http://www.gnu.org/licenses/>.

   Email   : hipersayan DOT x AT gmail DOT com
   Web-Site: http://github.com/hipersayanX/FlexBisonQt
*/

%{
#include <QtGui>

extern int yylex(void);
void yyerror(const char *s);
%}

// Here we can define some custom variable types.
// The custom types must be of static size.
%union {
    QVariant *QVariant_t;
}

// Define the types for terminal expressions.
%token <QVariant_t> TOK_INTIGER
%token <QVariant_t> TOK_FLOAT
%token <QVariant_t> TOK_BOOLEAN
%token <QVariant_t> TOK_STRING

// Define the tokens for the symbols.
%token TOK_LEFTPAREN
%token TOK_RIGHTPAREN
%token TOK_LEFTCURLYBRACKET
%token TOK_RIGHTCURLYBRACKET
%token TOK_LEFTBRACKET
%token TOK_RIGHTBRACKET
%token TOK_COMMA
%token TOK_COLON
%token TOK_WHITESPACES

// Define the tokens for the keywords.
%token TOK_SIZE
%token TOK_SIZEF
%token TOK_POINT
%token TOK_POINTF
%token TOK_RECT
%token TOK_RECTF
%token TOK_LINE
%token TOK_LINEF
%token TOK_DATE
%token TOK_TIME
%token TOK_DATETIME
%token TOK_COLOR
%token TOK_BYTES
%token TOK_URL

// Define the types for non-terminal expressions.
%type <QVariant_t> variant
%type <QVariant_t> size
%type <QVariant_t> sizeF
%type <QVariant_t> point
%type <QVariant_t> pointF
%type <QVariant_t> rect
%type <QVariant_t> rectF
%type <QVariant_t> line
%type <QVariant_t> lineF
%type <QVariant_t> date
%type <QVariant_t> time
%type <QVariant_t> dateTime
%type <QVariant_t> color
%type <QVariant_t> bytes
%type <QVariant_t> url
%type <QVariant_t> number
%type <QVariant_t> variantListItems
%type <QVariant_t> variantList
%type <QVariant_t> variantMapPair
%type <QVariant_t> variantMapItems
%type <QVariant_t> variantMap

// Prevents memory leak in non-terminal expressions.
%destructor {delete $$;} variant
%destructor {delete $$;} size
%destructor {delete $$;} sizeF
%destructor {delete $$;} point
%destructor {delete $$;} pointF
%destructor {delete $$;} rect
%destructor {delete $$;} rectF
%destructor {delete $$;} line
%destructor {delete $$;} lineF
%destructor {delete $$;} date
%destructor {delete $$;} time
%destructor {delete $$;} dateTime
%destructor {delete $$;} color
%destructor {delete $$;} bytes
%destructor {delete $$;} url
%destructor {delete $$;} number
%destructor {delete $$;} variantListItems
%destructor {delete $$;} variantList
%destructor {delete $$;} variantMapPair
%destructor {delete $$;} variantMapItems
%destructor {delete $$;} variantMap

%%

/* Main expression to check. */
start: tag

tag:    TOK_LEFTBRACKET TOK_RIGHTBRACKET

%%

/*
color: TOK_COLOR TOK_LEFTPAREN TOK_RIGHTPAREN {$$ = new QVariant(QColor());}
     | TOK_COLOR TOK_LEFTPAREN TOK_STRING TOK_RIGHTPAREN {
           $$ = new QVariant();
           *$$ = QColor($3->toString());
       }
     | TOK_COLOR TOK_LEFTPAREN number TOK_COMMA number TOK_COMMA number TOK_RIGHTPAREN {
           $$ = new QVariant();
           *$$ = QColor($3->toFloat(), $5->toFloat(), $7->toFloat());
       }
     | TOK_COLOR TOK_LEFTPAREN number TOK_COMMA number TOK_COMMA number TOK_COMMA number TOK_RIGHTPAREN {
           $$ = new QVariant();
           *$$ = QColor($3->toFloat(), $5->toFloat(), $7->toFloat(), $9->toFloat());
       }
     ;

bytes: TOK_BYTES TOK_STRING  {
           $$ = new QVariant();
           *$$ = $2->toString().toUtf8();
       }
     ;

url: TOK_URL TOK_LEFTPAREN TOK_RIGHTPAREN {$$ = new QVariant(QUrl());}
   | TOK_URL TOK_LEFTPAREN TOK_STRING TOK_RIGHTPAREN {
         $$ = new QVariant();
         *$$ = QUrl($3->toString());
     }
   ;
*/

void yyerror(const char *s)
{
    qDebug() << "error:" << s;
}
