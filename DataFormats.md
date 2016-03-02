# Introduction #

QBoard uses [libs11n](http://s11n.net) for its serialization (save/load) support, and therefor has very flexible serialization features. The most obvious use of serialization, from a user's perspective, is saving and loading a game. A less obvious use is the clipboard. When we copy or cut objects, we don't actually put those objects in the clipboard (that can easily lead to dangling pointers). Instead, we serialize them and stuff that data (plain text) into the clipboard. There are even other, less obvious, uses, but we won't bore you with those details right now.

# What file format(s) is(are) used? #

In principal, QBoard can save and load files of any type supported by libs11n. It does not rely on a single data format - libs11n supports 6 or 7 different ones, and which one is used is a detail we don't really care about. QBoard can load any data saved by any libs11n client, but whether or not QBoard can use that data is a whole other question. Loading is inherently context-specific, and QBoard may not be able to handle data of a given type in a given context.

libs11n uses various text formats. An example of a serialized QGIPiece (standard game piece) object is:

```
(s11n::parens)
S11nClipboardData=(QGIPiece (QGIFlags 3)
    props=(PropObj
        pixmap=(QVariant (type String)
            val=(QString (ascii games/Joe/v20080613/counters/010-average1.png))
        )
<SNIP>
        borderColor=(QVariant (type Color)
            val=(QColor (rgb 255 0 0))
        )
        pos=(QVariant (type PointF)
            val=(QPointF (xy 171.8 80.8))
        )
)
```

And here's that same data in another format:
```
<!DOCTYPE s11n::simplexml>
<S11nClipboardData s11n_class="QGIPiece" QGIFlags="3">
        <props s11n_class="PropObj">
                <pixmap s11n_class="QVariant" type="String">
                        <val s11n_class="QString" ascii="games/Joe/v20080613/counters/010-average1.png" />
                </pixmap>
<SNIP>
                <borderColor s11n_class="QVariant" type="Color">
                        <val s11n_class="QColor" rgb="255 0 0" />
                </borderColor>
                <pos s11n_class="QVariant" type="PointF">
                        <val s11n_class="QPointF" xy="171.8 80.8" />
                </pos>
        </props>
</S11nClipboardData>
```

And that same data in yet another format:
```
51191011
f111S11nClipboardData08QGIPiecee108QGIFlags00013<SNIP>
f0
f104SNIP0aNoClassYetf10bborderColor08QVariante<SNIP>
51190000
```

The point is, the format doesn't interest us. QBoard only cares about the structure of the data, and uses that structure to determine whether it can or cannot handle a given set of data. The structure represents various objects, and whether or not QBoard can do anything with those objects is context dependent.

If you really want to, you can convert QBoard saved data to arbitrary s11n-supported formats using [s11nconvert](http://s11n.net/s11nconvert/).

# What exactly can QBoard save and load? #

The GUI currently provides only features for saving/loading the game as a whole, via the File->Save/Load menus and the Quicksave/Quickload features.

That said...

All QBoard objects which inherit the Serializable base class have the built-in ability to save and load themselves. At some point, item-specific menus will be added for saving/loading each object's data (independent of other game state).

Pasting from the clipboard is, in fact, the exact same process as loading (just a different data source). So whatever applies to loading also applies to pasting.

The global game state currently supports pasting of various types of data:

  * Individual QGraphicsItems _if_ they inherit Serializable.
  * `QList<Serializable*>` _if_ the contained items are also QGraphicsItems.
  * `QList<QGraphicsItem*>`
  * The clipboard data generated via Ctrl-C/Ctrl-V.
  * A serialized QBoard object (e.g. to swap out the board graphic without intefering with the in-play pieces), which you can incidentally get by using the "Copy board" item in the board's menu.

Any clipboarded data can be pasted into a text editor, saved to a file, and re-used later. _However_, we make absolutely no guarantees that the format of copy/cut data will be the same in future versions, so don't use this feature for long-term storage. (It is very useful for testing QBoard, though.)

# See also... #

  * the s11n home page: http://s11n.net
  * [S11nQt](S11nQt.md), generic libs11n bindings for Qt