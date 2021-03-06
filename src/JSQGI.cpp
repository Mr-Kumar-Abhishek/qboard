/*
 * This file is (or was, at some point) part of the QBoard project
 * (http://code.google.com/p/qboard)
 *
 * Copyright (c) 2008 Stephan Beal (http://wanderinghorse.net/home/stephan/)
 *
 * This file may be used under the terms of the GNU General Public
 * License versions 2.0 or 3.0 as published by the Free Software
 * Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
 * included in the packaging of this file.
 *
 */

#include <qboard/JSQGI.h>
#include <QGraphicsItem>
#include <QScriptEngine>
#include <qboard/ScriptQt.h>
#include <qboard/utility.h>

#define SELF(RV) QGraphicsItem *self = this->self(); \
    QScriptEngine * js = this->engine(); \
    if(!self || !js) return RV;
#define SELFOBJ(RV) SELF(RV); \
    QObject *selfobj = dynamic_cast<QObject*>(self); \
    if(!selfobj) return RV;

namespace qboard {
struct JSQGI::Impl
{
    Impl()
    {
    }
    ~Impl()
    {
    }
};

JSQGI::JSQGI( QObject * parent )
    : QObject( parent ),
      QScriptable(),
      impl(new Impl)
{
}

JSQGI::~JSQGI()
{
    delete impl;
}

QScriptValue JSQGI::posXY()
{
    SELF(QScriptValue());
    QPointF p( self->pos() );
    QString code = QString("({x:%1,y:%2})").
	arg(p.x()).
	arg(p.y())
	;
    return js->evaluate( code, "JSQGI::posXY()");
}

bool JSQGI::setParentItem( QScriptValue const & pv )
{
    SELF(false);
    QGraphicsItem * p = dynamic_cast<QGraphicsItem*>(pv.toQObject());
    // ^^^ qscriptvalue_cast() doesn't work here, but dynamic_cast() does!
    qDebug() << "JSQGI::setParentItem() tried direct cast:"<<p;
    if( ! p )
    {
	QVariant var( pv.toVariant() );
	p = var.value<QGraphicsItem*>();
	qDebug() << "JSQGI::setParentItem() tried variant cast:"<<p;
    }
    if( ! p ) return false;
    self->setParentItem(p);
    return true;
}

QGraphicsItem* JSQGI::parentItem()
{
    SELF(0);
    return self->parentItem();
}


void JSQGI::moveBy( QPointF const & p )
{
    SELF();
    self->setPos( self->pos() + p );
}
void JSQGI::moveBy( qreal x, qreal y )
{
    this->moveBy(QPointF(x,y));
}

void JSQGI::setPos( QPointF const & p )
{
    SELF();
    self->setPos(p);
}

void JSQGI::setPos( qreal x, qreal y )
{
    this->setPos( QPointF(x,y) );
}

qreal JSQGI::posX()
{
    SELF(0.0);
    return self->pos().x();
}
qreal JSQGI::posY()
{
    SELF(0.0);
    return self->pos().y();
}

void JSQGI::setZValue( qreal z)
{
    SELF();
    self->setZValue(z);
}
qreal JSQGI::zValue()
{
    SELF(0.0);
    return self->zValue();
}

QScriptValue JSQGI::prop(QString const & key)
{
    char const * ckey = key.toAscii().constData();
    if( ! ckey || !*ckey ) return QScriptValue();
    SELFOBJ(QScriptValue());
    QVariant var = selfobj->property(ckey);
    QScriptValue ret;
    if( var.isValid() )
    {
	ret = js->newVariant(var);
	ret.setPrototype( js->globalObject().property("JSVariantPrototype") );
    }
    return ret;
}
bool JSQGI::prop(QString const & key, QScriptValue const & val )
{
    char const * ckey = key.toAscii().constData();
    if( ! ckey || !*ckey ) return false;
    SELFOBJ(false);
    selfobj->setProperty( ckey, val.toVariant() );
    return true;
}

QList<QGraphicsItem*> JSQGI::childItems()
{
    SELF(QList<QGraphicsItem*>());
    return qboard::childItems( self );
}


QGraphicsItem * JSQGI::self()
{
    // qscriptvalue_cast<QGraphicsItem*>(thisObject());
    QVariant var( thisObject().data().toVariant() );
    qDebug() << "JSQGI::self() variant:"<<var;
    QGraphicsItem * s = var.value<QGraphicsItem*>();
    qDebug() << "JSQGI::self() QGI:"<<s;
    if( ! s )
    {
	this->context()->throwError("JSQGI::self() got a null pointer.");
    }
    return s;
}

} // namespace
#undef SELF
#undef SELFOBJ
