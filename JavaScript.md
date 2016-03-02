**Achtung: this is no longer current since experimentation with the [QtScriptBindings](QtScriptBindings.md) started (20080913). Don't use the JS bindings at all in versions newer than 20080913 until this notice is gone.**

See also: [JSSnippets](JSSnippets.md)

# Introduction #

Starting with version 20080827, QBoard is getting JavaScript support. This document gives an overview of what's possible with the current code.

The things it can currently do:

  * Load new pieces by class name.
  * Set most basic properties (numbers, colors, and positions), though using a bit of an odd workaround (see the examples). By setting properties, pieces can be controlled in various ways.

Things that it cannot currently do:

  * Set piece properties using the natural JS properties syntax (it requires a function call instead).
  * Non-trivial properties cannot be properly _read_, only set. This includes QColor and QPoint objects, both of which are used in script code for various piece properties.

Some of those are on the to-fix list, but i'm not currently sure how/if some of it can be properly done (that is, the way i want to see it work).

Some notable things which need improving include:

  * Send print() output somewhere sensible. It currently goes to stdout, which is only (marginally) useful if you launch QBoard from a console (i always do).
  * Child objects. It's not currently possible to traverse or manipulate them.
  * Use of JS property syntax to get at object properties.
  * Useful script-side representations of some basic Qt types, like QPoint.
  * Attach JS script code as event handlers for native objects. The catch here is that the native objects currently don't know about the underlying JS engine, and so they have nowhere to actually run the JS code.

# Running JavaScript files #

To run a JS file in QBoard, simply double-click it. The JS print() command will send the output to stdout (your console, if you started QBoard from a console). Exceptions thrown from the script will be shown (with a stacktrace) in a dialog window.

# QBoard data types in JS #

Currently only the following QBoard-related types are even remotely scriptable:

  * QGIPiece - the basic piece type, represented by a small image file.
  * QGIDot - a colorful dot
  * QGIHtml - like little notes you can paste on your board

QPoint and QColor objects can be created for use as property values, but cannot be used in any other way (you can't currently get at their values from script code).

# Examples #

Here are some example of things which currently work:

```
qboard.clear(); // clears the board of all items
qboard.board.loadPixmap( "maps/myMap.jpg" );
var pc = qboard.createObject('QGIHtml'); // create new piece
qboard.props( pc,{ // set a few properties:
  html:"<body bgcolor='#ffffff'>This is my text</body>",
  pos:QPoint(30,50)
});
// Create a new piece:
pc = qboard.createObject('QGIPiece');
qboard.props(pc,{
  pixmap:'counters/sample/003-mage.png',
  pos:QPoint(50,50),
  color:QColor(255,0,0,127)
});
```

Aside from creating objects and setting properties, there's not much it can currently do. That said, using properties one can control almost all aspects of a piece which can be customized via the popup menus.

# Native vs. JS properties #

The "native" (C++) objects use a completely different properties system than JS-side code does. This means it isn't feasible for us to provide a 100% JS-natural syntax for setting properties of objects.

Native properties can be set using `qboard.prop()` or `qboard.props()`. JS properties are access via normal JS syntax (`myObject.myProperty`). Though `qboard.prop()` exists to fetch native values, they cannot all be used directly from JS code, as they often represent native types which have no inherent meaning in JS. Unfortunate, but true.

Do not use JS syntax for the properties which are used by a piece to control its behaviour (see below). Doing so may cause weird or broken behaviour. Also, do not try to pass JS-side objects as values to the native property setters. Doing so will, again, result in weird or broken behaviour.

# The qboard object #

The JS engine includes a global object called qboard. That object is essentially the same as the C++-side GameState object, with some additions for purposes of scripting.

Here is an overview of the public member functions and properties of the qboard object.

| **Property/Function** | **Description** |
|:----------------------|:----------------|
| board                 | The game state's QBoard (game board) object. |
| QObject createObject(ClassName[,Object props]) | Creates a new QGraphicsItem/QObject object of the given _type name_ (e.g. 'QGIDot' or 'QGIHtml'). If props is non-null, it sets the object's properties as per props(). The exact type and API of the return object depends on the class name passed to it. |
| Array items()         | Returns an array of all selected items. Each item will be some sort of QObject-derived native type. |
| prop(item,key,value)  | Sets the given property in the given item. |
| props(item,Object}    | For each key/value pair in the given Object, it copies that property to the given item |
| scene                 | The underlying QBoardScene object. |
| value prop(item,key)  | Returns the given property value from the given object. Not all types are currently usable from script code (e.g. QPoint and QColor), but they can be passed around as arguments. |
| view                  | A QBoardView object. This is only available running a script from the QBoard main window, in the context of the main GameState instance. |



# Common piece properties #

Here is an overview of the list of common properties (in alphabetical order), their expected data types, and the piece types which support this property. The piece types are listed by their class name, and is the name which can be passed to `qboard.createObject("ClassName")` to create a new object. Note that it is not recommended to use standard JavaScript notation when getting/setting these properties, as there are synchronization and type conversion issues which can't currently be addressed via that syntax. Use `qboard.prop()` and `qboard.props()` to get/set the properties instead.

| **Property** | **JS data type** | **Piece types** | **Description** |
|:-------------|:-----------------|:----------------|:----------------|
| `alpha`      | integer or floating point | QGIPiece, QGIDot | Alpha level (transparency) of the piece's color. If the number is less than or equal to 1.0 is it considered to be a relative alpha level between 0.0 and 1.0, otherwise it is assumed to be an integer value between 2 (very nearly transparent) and 255 (fully opaque). |
| `angle`      | integer or floating point | QGIHtml, QGIPiece, QGIDot | rotation angle  |
| `borderAlpha` | as for `colorAlpha` | QGIPiece        | alpha level of a piece's border |
| `borderColor` | as for `color`   | QGIPiece        |color of the piece's border |
| `color`      | string or QColor(r,g,b[,a]) | QGIPiece, QGIDot |The color of the object. The string may be a common color name ("red" or "lightblue") or HTML notation ("#RRGGBB"). |
| `html`       | text             | QGIHtml         | HTML (a subset, actually) text to display. |
| `pixmap`     | image filename, relative to QBoard Home | QGIPiece, the game board |The image file used for an item. This determines the piece's size. Any image format supported by Qt is okay. |
| `pos`        | QPoint(X,Y)      | QGIPiece, QGIHtml, QGIDot | The position of the piece, in x/y coordinates. This is normally the top/left corner of the piece, but some pieces (e.g. QGIDot) are centered. Note that moving a piece moves all children of that piece as well. |
| `scale`      | positive floating-point number | QGIPiece, QGIHtml, QGIDot | Relative scale of the item, 1.0 being normal, 0.0 being non-existent, and 2.0 being double normal size. |

The on-board lines (QGILine) are not currently scriptable because they will be replaced at some point (their current model requires to much special-case handling of events and serialization).

(Note, however, that this work is ongoing, and the above list will change.)

# Common piece member functions #

Versions 20080906 and higher have the following member functions for pieces of all types, but _only for pieces created via script_ (not for pieces created via C++ code).

| **Function** | Description |
|:-------------|:------------|
| move(number x, number y) | Move the piece to the given position |
| move(QPointF(x,y) ) | Same as move(x,y) |
| Array childItems() | Returns an array of all child items (an empty array if there are no children) |
| prop(key,value) | Sets the given _native_ property. |
| QVariant prop(key) | Returns the given _native_ property as a QVariant. Not all such values are usable from script code! See below for more detail. |
| number posX(), number posY() | Returns the object's X or Y position. (This is a workaround, actually) |

Properties fetched via the `item.prop()` and `qboard.prop()` routines actually come back to the user as a C++-native QVariant type which have certain member functions not available to most properties:

| Function | Description |
|:---------|:------------|
| value jsValue() | Tries to convert the underlying variant to a JS-supported type, and returns the value. |
| string toSource() | Tries to convert the contained value into a JS source code string, and returns that string. The string will be a JS-only representation of the value, and cannot be used as a game item property value. It can, however, be eval()'d and use from JS code.|
| string toVariantString() | Returns a string value for the object. This is NOT the same the conventional JS toString(), and is only intended for debugging purposes. |
| int variantType() | Returns the value of QVariant::userType() for the underlying variant object. Useful primarily for debugging. |