# Serializing Qt-based objects using libs11n #

Since i'm the maintainer of the s11n project (http://s11n.net), a library for serializing
objects in C++, QBoard uses libs11n for its serialization needs (that is, loading and saving). As QBoard develops, code is written to bind Qt-based types to the s11n serialization framework. That code is independent of QBoard and may be helpful to coders working on arbitrary Qt-based projects. (Historical note: libs11n was originally written with the express intent of (someday) supporting this very application.)

# Getting the source #

The S11nQt distribution contains a complete copy of libs11n plus the Qt extensions described below. As of May 2009, it is maintained in its own library, separate from qboard. It is accessible via:

  * [its source repository](http://code.google.com/p/qboard/source/browse/#svn/S11nQt)
  * via the downloads page. Look for `libS11nQt-S11N_VERSION-RELEASE_DATE.tar.bz2`.
  * The main qboard source tree also has a copy, but that is no longer the master copy, and may eventually be phased out.

It can be used as a replacement for vanilla libs11n builds, but is intended for redistribution along with Qt client applications. If you want to add the Qt extensions to your own copy of libs11n, simply:

  * Copy [include/s11n.net/qt](http://code.google.com/p/qboard/source/browse/#svn/S11nQt/include/s11n.net/s11n/qt%3Fstate%3Dclosed) to `<s11n.net/s11n>` on your system.
  * Copy [include/s11n.net/proxy/qt](http://code.google.com/p/qboard/source/browse/#svn/S11nQt/include/s11n.net/s11n/proxy/qt) to `<s11n.net/s11n/proxy>` on your system.
  * Copy [s11n/S\*.cpp](http://code.google.com/p/qboard/source/browse/#svn/S11nQt/s11n) into your project (note that that's a capital `S*`, not lower-case!). Alternately, link them in with your local libs11n. No changes to libs11n are required.

# License #

libs11n is Public Domain, but libqt has several licensing choices and those choices depend partially on the Qt version. To be license-compatible with all versions of Qt, libS11nQt may be used under the terms of whatever license (or licenses) has (or have) been accepted for the particular version of Qt it is being compiled and linked against. For example, if it is used in conjunction with Qt 4.3 and the GPLv2 license, then libS11nQt is GPLv2 in that context. If it is used with Qt 4.5 and the LGPL, then libS11nQt is LGPL in that context. Likewise for the commercial Qt license.


# Supported Qt types #

These s11n/Qt extensions contain code for de/serializing the following Qt types:

| **Type** | **Notes** |
|:---------|:----------|
| QBitArray | Packs the bits into blocks of 32-bit integers. |
| QByteArray | Bin64-encoded. Objects over a certain (configurable) size will be compressed with zlib. |
| QBrush   | All significant properties are stored, including custom transformations and textures. |
| QColor   | RGBA data |
| QDate/QTime/QDateTime |           |
| QFont    |           |
| QLine/QLineF |           |
| QList/QVector | May contain any Serializable type (as defined by libs11n) |
| QMap     | May contain any Serializable type (as defined by libs11n) |
| QMatrix  |           |
| QRect/QRectF |           |
| QPair    | May contain any Serializable type (as defined by libs11n) |
| QPen     | All properties handled, including custom dash patterns. |
| QRegExp  |           |
| QPixmap  | Stored as a QByteArray |
| QPoint/QPointF |           |
| QPolygon | Actually `QVector<QPoint>` |
| QSize/QSizeF |           |
| QString  | Handles both ASCII and Unicode strings (using a different internal representation for each). |
| QTransform |           |
| QVariant | Many forms are supported, including above-listed types. With a little help (see below) it can work with any Serializable Type object. |

After including the proper header file(s) (which register(s) a specific Qt type with libs11n), one can use those types via the s11nlite API, e.g.:

```
#include <s11n.net/s11n/qt/S11nQt.h>
#include <s11n.net/s11n/proxy/qt/QPoint.h>
#include <s11n.net/s11n/proxy/qt/QVariant.h>
#include <s11n.net/s11n/proxy/qt/QRectF.h>
...

QPoint p(20,30);
s11nlite::save( p, std::cout );
QVariant var( QRectF(23.3,34.4,27,94) );
s11nlite::save( var, std::cout );
```


S11nQt also comes with proxy objects which allow QIODevices to be used via the STL i/ostream interfaces (so you can e.g. save s11n data out to a QFile instead of a std::ofile).

This code is central to QBoard's save/load and copy/paste features and is believed to work quite well.

Suggestions, fixes, etc., are of course always welcome.

Happy hacking!

# QVariant and Serializables #

Probably the most interesting part of the QVariant/S11n support is the ability to store arbitrary Serializable types (as defined by libs11n) in QVariants, and then pass them around. To store a Serializable in a QVariant we need to use a proxy type. That looks like this:

```
#include <s11n.net/s11n/qt/S11nQt.h>
#include <s11n.net/s11n/proxy/qt/QVariant.h>
using namespace s11n::qt;
...
QVariant var( VariantS11n(mySerializable) );
```

To deserialize it, we do:

```
if( var.canConvert<VariantS11n>() )
{
  VariantS11n sv( var.value<VariantS11n>() );
  MySerializable * my = sv.deserialize<MySerializable>();
  ...
}
```

# Notable limitations #

The Qt API has a number of useful types which we would like to be able to serialize, but cannot because they lack accessors and/or mutators for certain information. The notable example which comes to mind is QRegion, from which we can extract all data, but have no way of restoring it (the API is missing a setter or two). QIcon has similar problems. Other types, like QImage, could be serialized but it would be horribly, horribly inefficient to do so with s11n, so we don't bother.

See below for limitations regarding...

## Serializing QObjects, QWidgets, etc. ##

S11nQt doesn't have routines for directly serializing QObject trees, but:

  * Doing so is fairly trivial. We can easily serialize the parent/child trees.
  * We cannot easily serialize the signal/slot connections, mainly because such connections may span across object hierarchies and s11n's pointer-following policy doesn't play well with that.

It might be possible to de/serialize signal/slot connections by introducing another pass to the serialization process, where we tag all related objects, add that tag info to their serialized output, and re-build the connections from those tags during deserialization. Signals and slots are internally referred to by their stringified names, so that's not the problem. It's finding the correct object to reconnect to at deserialization time, that's the problem.

That said, it is possible (and trivial) to serialize QObject trees, and QBoard does so in several places.

# Why not use Qt's built-in QDataStream serialization? #

Much of the Qt API supports i/o operators for QDataStream, which can be used to de/serialize Qt-native objects. Why should one not use that for long-term storage? Because it's a proprietary binary format, not something one can re-use. The QDataStream approach is useful for IPC and such, but proprietary binary formats are not generically suitable for long-term storage of application data, IMO.