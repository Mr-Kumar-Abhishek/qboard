**Achtung: this is no longer current since experimentation with the [QtScriptBindings](QtScriptBindings.md) started (20080913).**

See also: [JavaScript](JavaScript.md)

# Introduction #

Here is a collection of JavaScript snippets which can be used with QBoard.

**Achtung**: as the JS bindings are very much a work in progress, there are no guarantees that any of these snippets will work with a particular QBoard version. Have faith that they have been shown to work in at least one version of QBoard :).

# Creating new pieces #

A new dot:

```
var pc = qboard.createObject('QGIDot',{
    pos:qboard.placementPos(),
    color:'red'
});
// QGIDot has a custom function which can "split" the
// dot into two, connected by a line:
pc.split();
```


A new HTML item:
```
qboard.createObject('QGIHtml',{
    pos:QPoint(100,150),
    html:'this is my text'
});
```


A new graphical piece:
```
qboard.createObject('QGIPiece',{
    pos:qboard.placementPos(),
    pixmap:'mygame/counters/soldier.png'
});
```

## Setting properties after creation ##

```
// Set a single property:
qboard.prop( pc, 'scale', 1.5 );
// or several properties at once:
qboard.props( pc, {angle:90,scale:1.0} );
```

For the list of properties supported by each piece type, and
their required types, see [the JavaScript page](JavaScript.md).

# Destroying items #

```
var pc = qboard.createObject(...);
...
pc.deleteLater();
```

The `deleteLater()` routine queues the item for deletion once the current event handling queue is at a safe point. Because of a potential delay, after calling deleteLater(), pc should be treated as a null pointer, even though it might technically (and briefly) still be alive. Note that:

```
delete pc;
```

is NOT the same. That only deletes the script-side representation of the object, and not _necessarily_ the native (C++-side) object (it depends on where the object was created, and its current parentage).

# Dialog boxes #

A simple message box:

```
alert("Hi, world!");
```

A confirmation dialog:
```
if( confirm("Really do it?") ) {
   ... do it ...
}
```

# Random numbers #

Examples of generating random numbers:
```
var r1 = randomInt(6); // a number in the range 0 to 5
var r2 = randomInt(1,6); // a number in the range 1 to 6
```

The two-argument form of randomInt() can be used for certain customized dice types,
like Fudge dice, which have 6 sides, two each of (-1), (0), and (1):

```
randomInt(-1,1); // a number between -1 and 1
```