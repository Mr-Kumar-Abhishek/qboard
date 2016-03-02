Current as of 20080828...

# Introduction #

QBoard _could_ have been implemented as a library and a thin wrapper client app around it, but it's not. Maybe someday it will be restructured to be so, but today it's not. This page provides an overview of the app parts and major classes.

Historical note: the primary (probably only) reason for not building QBoard as a library is because on Windows platforms libs11n cannot work as a DLL (due to linker rules which completely break down where class templates are involved). Thus we have to build libs11n as part of the application, so that we can hopefully get QBoard building on Windows some day.

# The core data types #

Here is an overview of the major C++ classes in QBoard.

## GameState ##

This class acts as a wrapper for a QGraphicsScene, QBoard (game board), and an arbitrary number of QGraphicsItems (managed by the QGraphicsScene). GameState can serialize the parts as a whole, which is what happens when you use the Load/Save menus/buttons.

To add a piece to a game, one must create a QGraphicsItem (abbreviated QGI) and call GameState::addItem().

## QBoard / QBoardView ##

The QBoard class is an abstraction of a game board. It currently doesn't do much - just holds the name of an image file to represent a playing surface.

QBoardView is a QGraphicsView subclass which is specialized for viewing a QBoard object. It supports scaling, rotating, and a few other options.

## QGraphicsItems / game pieces ##

QBoard uses QGraphicsItems (QGI) to represent game pieces of various types. In principal, QBoard can display any QGI type, but to be fully integrated into QBoard (including copy/paste support), the QGI subclasses must also subclass QObject and Serializable. The QObject dependency is because the framework uses QObject::setProperty() extensively to control the appearance of objects, and QObject::deleteLater() to work around timing-related problems with regards to object destruction during event handling. The Serializable dependency provides a common serialization interface. That allows, e.g., the clipboard and load/save support, along with things like polymorphic cloning and the ability to save/load individual items to/from arbitrary files or streams.

The current QGI types which come with QBoard are:

  * QGIPiece: basic playing pieces, represented by a small image file.
  * QGIDot: a round dot which can be resized and recolored.
  * QGIHtml: for annotating a board with arbitrary text (it allows a subset of HTML, actually).
  * QGILine: a line between two points on the board.

### Game piece properties ###

The game piece objects are designed to be controlled via the setting of properties. Properties are key/value pairs with strings as keys and QVariants as values. (This is the approach used by the underlying QObject class.)

The [serialization layer](S11nQt.md) can serialize a variety of native types supported by QVariant, and we can therefor fully serialize all game-related properties of a piece. This approach allows us to uniformly handle the control and serialization of all game piece objects. As an example of this uniformity, the vast majority of the item-specific menu entries are all of the same type, a QAction subclass which sets a given property to a given QVariant value when the action is triggered.


## MainWindowImpl ##

This class is the main window UI element. It wraps up the functionality of the other stuff into a usable interface. The GUI is mostly managed using Qt Designer, but the implementation code is in `MainWindowImpl.{h,cpp}`.

## Serializable / s11n ##

s11n is the name of the underlying serialization framework (http://s11n.net). It is responsible for the process of serializing (saving) and deserializing (loading) all game data. This support is the second core-most component of the framework, right behind Qt. The libs11n support is mostly encapsulated in the `Serializable` base class, which many other classes in the tree inherit from. The Qt/s11n proxying code (so we can de/serialize Qt types) is in `S11n*.{h,cpp}`. There are many examples in the source tree of how to use it (simply grep **.cpp for "::serialize" and "::deserialize").**

## Misc. ##

There are tons of other less important classes and files, and lots of things which we hope to go into detail about someday.