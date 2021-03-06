#include <qboard/QBoardHomeView.h>

#include <QItemSelectionModel>

#define QBOARD_USE_FSMODEL (0 && (QT_VERSION >= 0x040400))
#if QBOARD_USE_FSMODEL
#  include <QFileSystemModel> // would seem to be more suitable, but QFileSystemModel::setRootPath() isn't working how i'd expect
#else
#  include <QDirModel>
#endif
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>

#include <qboard/utility.h>

// If QBHomeView_USE_DIRICON is a string then: if a dir entry has a file named that
// string (e.g. ".diricon.png") then that icon is used in place of the default one.
// To turn this of, undefine QBHomeView_USE_DIRICON 
#define QBHomeView_USE_DIRICON ".diricon.png"
#ifdef QBHomeView_USE_DIRICON
#include <QRegExp>
#endif

// If QBHomeView_GENERATE_MINIICONS is true then code is enabled which tries to
// generate preview icons for "small" image files. Whe a list entry has the
// suffix 'png' or 'xpm' and that file is under a certain size (e.g. 8k) then
// it is loaded as a pixmap, scaled to 16x16, and used as its own icon.
#define QBHomeView_GENERATE_MINIICONS 1
#if QBHomeView_GENERATE_MINIICONS
#include <QPixmapCache>
#include <QRegExp>
#endif

#define QBHomeView_USE_QBOARD_FILEEXT_RESOURCES 1
#if QBHomeView_USE_QBOARD_FILEEXT_RESOURCES
#include <QRegExp>
#include <QResource>
#endif

// Qt bug? Q_EMIT is never getting defined for me
#ifndef Q_EMIT
#define Q_EMIT
#endif

QBoardFileIconProvider::QBoardFileIconProvider() :
    QFileIconProvider()
{
}

QBoardFileIconProvider::~QBoardFileIconProvider()
{}

QIcon QBoardFileIconProvider::icon( const QFileInfo & info ) const
{
#ifdef QBHomeView_USE_DIRICON
    if( info.isDir() )
    {
	//QString check( QDir::toNativeSeparators(info.canonicalFilePath()+"/dir
	QDir dir(info.canonicalFilePath());
	if( dir.exists(QBHomeView_USE_DIRICON) )
	{
	    return QIcon(QDir::toNativeSeparators(dir.filePath(QBHomeView_USE_DIRICON)));
	}
    }
#endif // QBHomeView_USE_DIRICON
#if QBHomeView_GENERATE_MINIICONS
    static const int thresh = 8 * 1024;
    if( (info.size()<thresh)
	&& (0 == QRegExp("(png|xpm)",Qt::CaseInsensitive).indexIn(info.suffix()) )
	)
    {
	QString key( info.canonicalFilePath() );
	QPixmap pix;
	if( ! QPixmapCache::find(key,pix) )
	{
	    if( pix.load( key ) )
	    {
		pix = pix.scaled(16,16);
		QPixmapCache::insert(key,pix);
	    }
	}
	if( ! pix.isNull() )
	{
	    return QIcon(pix);
	}
    }
#endif // QBHomeView_GENERATE_MINIICONS
#if QBHomeView_USE_QBOARD_FILEEXT_RESOURCES
    if( ! info.isDir() )
    {
	char const * fmt = ":/QBoard/icon/fileext/%1.png";
	QString res = QString(fmt).
	    arg(info.completeSuffix());
	QPixmap pm( res ); // when i use QIcon here, isNull() always returns false
	if( pm.isNull() )
	{
	    res = QString(fmt).arg(info.suffix());
	    pm = QPixmap(res);
	}
	if( ! pm.isNull() )
	{
	    return QIcon(pm);
	}
    }
#endif // QBHomeView_USE_QBOARD_FILEEXT_RESOURCES
    return this->QFileIconProvider::icon(info);
}


struct QBoardHomeView::Impl
{
#if QBOARD_USE_FSMODEL
    typedef QFileSystemModel ModelType;
#else
    typedef QDirModel ModelType;
#endif
    ModelType * model;
    QItemSelectionModel * sel;
    QModelIndex current;
    static QBoardFileIconProvider * iconer;
    Impl() : model( new ModelType ), // QDirModel ),
	     sel( new QItemSelectionModel(model) ),
	     current()
    {
	++instCount;
	if( ! iconer )
	{
	    iconer = new QBoardFileIconProvider;
	}
	model->setIconProvider( iconer );
#if ! QBOARD_USE_FSMODEL
	model->setSorting( QDir::DirsFirst | QDir::IgnoreCase );
#endif
	model->setReadOnly( false );
    }
    ~Impl()
    {
	delete sel;
	delete model;
	if( 0 == --instCount )
	{
	    delete iconer;
	    iconer = 0;
	}
    }
private:
    static size_t instCount;
};
size_t QBoardHomeView::Impl::instCount = 0;
QBoardFileIconProvider * QBoardHomeView::Impl::iconer = 0;

QBoardHomeView::QBoardHomeView( QWidget * parent ) :
    QTreeView(parent),
    impl(new Impl)
{
    this->setModel( impl->model );
#if ! QBOARD_USE_FSMODEL
    this->setRootIndex( impl->model->index(qboard::home().absolutePath()) );
#else
    //impl->model->setFilter( QDir::AllEntries | QDir::Hidden );
    //impl->model->setNameFilterDisables(false);
    //impl->model->setRootPath( qboard::home().absolutePath() );
    impl->model->setRootIndex(model->index(qboard::home().absolutePath()));
    qDebug() << "QBoardHomeView: model root =="<<impl->model->rootPath();
#endif
    for( int i = 1; i < 4; ++i )
    {
	this->setColumnHidden(i, true);
    }
    this->setUniformRowHeights(true);
//#if QT_VERSION >= 0x040400
//     this->QTreeView::setHeaderHidden(true);
//#endif
    connect( impl->sel, SIGNAL(currentChanged( const QModelIndex &, const QModelIndex & )),
	     this, SLOT(currentChanged( const QModelIndex &, const QModelIndex & )));
    //this->setSortingEnabled(true);
}

QBoardHomeView::~QBoardHomeView()
{
    delete impl;
}

void QBoardHomeView::mouseDoubleClickEvent( QMouseEvent * event )
{
    /**
       This readOnly flag kludge is to keep a double-click from
       causing the view to go into item-rename mode, but still allow
       renaming via the standard hotkey F2.
    */
    impl->model->setReadOnly( true );
    this->QTreeView::mouseDoubleClickEvent(event);
    impl->model->setReadOnly( false );
    if(0) qDebug() << "QBoardHomeView::mouseDoubleClickEvent(): "
		   << impl->model->filePath(impl->current);
    if( impl->current.isValid() )
    {
	QFileInfo fi( impl->model->fileInfo(impl->current) );
	if( fi.isFile() )
	{
	    Q_EMIT itemActivated( fi );
	}
    }
}

void QBoardHomeView::keyReleaseEvent( QKeyEvent * event )
{
    if( event->key() == Qt::Key_Delete )
    {
	QModelIndex cur = impl->current;
	QString fn = qboard::homeRelative( impl->model->filePath(cur) );
	QString msg = QString("Please confirm deletion of file:\n%1").
	    arg(fn);
	event->accept();
	int rc = QMessageBox::question( this,
					"Delete file?",
					msg,
					QMessageBox::Ok
					| QMessageBox::Cancel );
	if( QMessageBox::Ok == rc )
	{
	    impl->model->remove( cur );
	}
	return;
    }
    return QTreeView::keyReleaseEvent(event);
}
void QBoardHomeView::refresh()
{
#if ! QBOARD_USE_FSMODEL
    QModelIndex h = impl->model->index("./"); // qboard::home().absolutePath());
    //     if( h.isValid() )
    //     {
    this->setRootIndex( h );
    impl->model->refresh(h); // causes a segfault when called during ctor
    //     }
#else
    //impl->model->setRootPath( qboard::home().absolutePath() );
    impl->model->setRootIndex(model->index(qboard::home().absolutePath()));
#endif
}

void QBoardHomeView::currentChanged( const QModelIndex & current,
				     const QModelIndex & /* previous */ )
{
    impl->current = current;
    if(0) qDebug() << "QBoardHomeView::currentChanged(): "
		   << impl->model->filePath(current);
}
