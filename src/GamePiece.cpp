#include <QList>
#include <QByteArray>
#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QPalette>
#include <s11n.net/s11n/s11n.hpp>
#include <s11n.net/s11n/functional.hpp>

#include <iterator>
#include <algorithm>

#include "GamePiece.h"
#include "utility.h"
#include "S11nQt.h"

/* s11n proxy for GamePieces.*/
struct GamePiece_s11n
{
	/**
		Serializes src to dest.
		
		All properties of src set via setProperty() or setPieceProperty()
		will be serialized. See QObjectProperties_s11n for how this is
		handled.
	*/
	bool operator()( S11nNode & dest, GamePiece const & src ) const;
	/** Deserializes dest from src.	*/
	bool operator()( S11nNode const & src, GamePiece & dest );
};

struct GamePiece::Impl
{
	int viewCount;
	bool destructing;
	Impl() : viewCount(0),destructing(false)
	{}
	~Impl(){}
};

GamePiece::GamePiece() : Serializable("GamePiece"),impl(new Impl)
{
	this->s11nFileExtension(".QBoardPiece");
}

GamePiece::~GamePiece() 
{
	impl->destructing = true;
	//qDebug() << "~GamePiece() pixmap="<<this->property("pixmap");
	emit destructing(this);
	emit destroyed(); // we do this here to ensure that the proper polymorphic type is available when destroyed() is fired.
	delete impl;
}

void GamePiece::addViewRef()
{
	++(impl->viewCount); 
}
void GamePiece::removeViewRef()
{
	if( (!impl->destructing) && (0 == --(impl->viewCount)))
	{
		this->deleteLater();
	}
}


bool GamePiece::hasProperty( char const * key )
{
	return this->property(key).isValid();
}

bool GamePiece::setPieceProperty( char const * name, QVariant const & v)
{
	if( ! QVariant_s11n::canHandle( v.type() ) )
	{
		qDebug() << "GamePiece::setPieceProperty(["<<name<<"],["<<v<<"]) rejecting unknown QVariant type.";
		return false;
	}
	bool ret = this->setProperty(name,v);
	emit piecePropertySet( name, this );
	return ret;
}

bool GamePiece::event( QEvent * e )
{
#if 0
/**
	To contemplate: maybe emit piecePropertySet() from here. HOWEVER:
	it is sometimes useful to avoid firing a signal on a property change
	by calling setProperty() instead of setPieceProperty(), so we don't
	necessarily want to fire here. Still thinking about it.
*/
	if( e->type() == QEvent::DynamicPropertyChange )
	{
		e->accept();
		QDynamicPropertyChangeEvent *chev = dynamic_cast<QDynamicPropertyChangeEvent *>(ev);
		if( ! chev ) return false; 
		emit piecePropertySet( chev->propertyName().constData(), this );
		return true;
	}
#endif
	return QObject::event(e);
}


QRect GamePiece::geom() const
{
	return QRect( this->property("pos").toPoint(),
				this->property("size").toSize() );
}

bool GamePiece_s11n::operator()( S11nNode & dest, GamePiece const & src ) const
{
	S11nNode & ch( s11n::create_child(dest, "properties"));
	S11nNodeTraits::class_name(ch,"list");
	return QObjectProperties_s11n()( ch, src ); 
}

bool GamePiece_s11n::operator()( S11nNode const & src, GamePiece & dest )
{
	S11nNode const * ch = s11n::find_child_by_name(src, "properties");
	if( ! ch ) return false;
	return QObjectProperties_s11n()( *ch, dest );
}

bool GamePiece::serialize( S11nNode & dest ) const
{
	if( ! this->Serializable::serialize( dest ) ) return false;
	return GamePiece_s11n()( dest, *this );
}

bool GamePiece::deserialize( S11nNode const & src )
{
	if( ! this->Serializable::deserialize( src ) ) return false;
	return GamePiece_s11n()( src, *this );
}

//
/**
void GamePiece::setPixmap(QPixmap const & px)
{
	this->m_p = px;
	QSize isz( px.size() );
	this->resize(isz);
	this->setBrush(QBrush(m_p));
	//QRectF rect( 0, 0, isz.width(),  isz.height() );
}
*/

GamePieceList::GamePieceList() : Serializable("GamePieceList")
{
	this->s11nFileExtension(".QBoardGamePieceList");
}
GamePieceList::~GamePieceList()
{
    //qDebug() << "~GamePieceList()";
	this->clearPieces();
}

void GamePieceList::connect( GamePiece * gp )
{
	this->QObject::connect(gp,SIGNAL(destructing(GamePiece *)),this,SLOT(removePiece(GamePiece*)));
}
void GamePieceList::disconnect( GamePiece * gp )
{
	QObject::disconnect(gp,SIGNAL(destructing(GamePiece *)),this,SLOT(removePiece(GamePiece*)));
}

void GamePieceList::clearPieces()
{
	iterator it = this->begin();
	for( ; it != this->end(); ++it )
	{
		this->disconnect(*it);
		delete (*it);
	}
	this->m_list.clear();
}

void GamePieceList::clearNoDelete()
{
	this->m_list.clear();
}

void GamePieceList::addPiece( GamePiece * gp )
{
	this->connect(gp);
	this->m_list.insert( gp );
	emit pieceAdded(gp);
}

bool GamePieceList::removePiece( GamePiece * gp )
{
	iterator it =this->m_list.find(gp);
	if( m_list.end() == it ) return false;
	this->disconnect(gp); 
	this->m_list.erase(it);
	emit pieceRemoved(gp);
	return true;
}

void GamePieceList::takePieces( GamePieceList &other )
{
	ListType tmp( other.m_list );
	other.m_list.clear();
	iterator it = tmp.begin();
	iterator et = tmp.end();
	for( ; et != it; ++it )
	{
		this->addPiece(*it);
	}
}

bool GamePieceList::serialize( S11nNode & dest ) const
{
	if( ! this->Serializable::serialize( dest ) ) return false;
	std::for_each( this->m_list.begin(), this->m_list.end(),
				s11n::ser_to_subnode_unary_f( dest, "piece" ) );
	return true; 
}

#include <memory>
bool GamePieceList::deserialize( S11nNode const & src )
{
	if( ! this->Serializable::deserialize( src ) ) return false;
	this->clearPieces();
	typedef S11nNodeTraits NT;
	NT::child_list_type::const_iterator it = NT::children(src).begin();
	NT::child_list_type::const_iterator et = NT::children(src).end();
	typedef std::auto_ptr<GamePiece> GP;
	for( ; et != it; ++it )
	{
		GP gp( new GamePiece );
		if( ! s11n::deserialize<S11nNode,GamePiece>( *(*it), *gp ) )
		{
			return false;
		}
		this->addPiece(gp.release());
	}
	return true;
}
