# QBoard ChangeLog #

This is the informal ChangeLog for the QBoard project. Newest items
are at the top. Dates written extra large are release dates.


---


**2008 Nov 30**

- Reversed zoom in/out mouse wheel, to match Firefox. Build changes to accommodate seemingly harmless change in qmake 4.4.3 which broke my builds. More JS experimentation, but all that stuff is in the air right now.

**2008 Oct 16**

- Main window geometry is now persistant across sessions.


## **2008 Sept 14** ##

Going ahead and doing a release because:

- My RSI is acting up from all the typing the past weeks (during the days at work, and 8-10 hours/night at home). i don't know if i'll be able to code much the next few weeks.

- The app essentially does everything i want it to do. Most of what i want to do now is refinement.

- The JS bindings need some re-thought, and i think i'm going to strip out the current work and start from scratch on those, basing the bindings off of the work from the Qt Script Generator project. That will take more time than i can currently commit to, though.


**2008 Sept 13**

- Fixed: wiki parser now disables other inlined markup inside of a `TT block`, like Google Code does.

- Managed to get the Qt Script Generator working and generated JS bindings for a significant portion of the Qt API. It doesn't all work, but the basic stuff seems to. HOWEVER... those bits require Qt 4.4 and will be available as a separate download at some point. Because i have no desire to somehow back-port some 14MB of generated code to Qt4.3, only the most basic scripting features will available to QBoard built with Qt4.3, as opposed to Qt4.4. The Qt Script Generator itself is available from:

> http://labs.trolltech.com/page/Projects/QtScript/Generator

or check the downloads page for pre-generated copies of the bindings, ready for building as a Qt plugin.

**2008 Sept 11**

- Added full JS wrapper for the QBoardView type using about 90% generated code. This generator will make writing JS wrappers for the other QObject types significantly easier.

- Holy cow - the downloads page says some 18 people have downloaded QBoard since yesterday, which probably means a link was posted somewhere.


**2008 Sept 10**

- QGIHider (covered pieces) can now be colored as one likes. They can't be rotated/scaled independently because doing so causes graphics artefacts when the items are uncovered.

- When a QGIDot has been split into a line, a new menu option appears which allows one to clone the dot along with its incoming line (attached to the original parent dot).


**2008 Sept 9**

- Minor improvements in the JS stuff, particularly in the handling of QPoint/QRect/QSize/QColor types. Added JS-side include() to include other JS files.


**2008 Sept 7**

- Fixed: line width property wasn't properly handled for QGIDots (bug introduced yesterday).

- Fixed: borderWidth property wasn't handled property for QGIPieces (bug introduced yesterday).

- Fixed: pieces loaded via double-clicking had their absolute image paths saved in save files. They are now relative to the QBoard Home.

- Refactored how QGIPiece objects store their visualization-related properties. Older data is still readable, but newer saves are not backwards compatible. This also incidentally makes getting some of the property values essentially impossible from JS code. :/


## 2008 Sept 6 ##

- Fixed a couple compile warnings/erros on certain compiler versions.

- Improvements in JavaScript scriptability. It's now possible to add new children to pieces, to set properties on them via a member function, and to query and set their position. It's also possible to attach JS double-click handlers to QGIPiece and QGIDot objects.

- Renamed some properties. Older data is still usable, but new saves will use the newer property names.

- The color selection menus now include an option to pick a custom color.

- Restructured the menus and toolbar, to group related functionality better.

- Restructured the build tree considerably. It is now built as a couple of libraries and a main app which links those libraries. This won't work on Win32 platforms (for long, boring reason), but until i hear from someone trying to use QBoard on Windows, i won't worry about it. See [CompilingQBoard](CompilingQBoard.md) for details.

- For Unix platforms, added ability to read/write gzip-compressed s11n files. Should work (with the appropriate linker args) on any platform with zlib (which is everywhere).


**2008 Sept 4**

- Added a file viewer capable of reading Wiki files, following the Google Code Wiki
syntax (the same one used by this site). It supports the basic markup featurs,
including bold, italics, headings, bullet/number lists (not nested!) and tables. Double-clicking a .wiki file will open it in a docked window. This will eventually allow us to ship the current website wiki pages as documentation files for QBoard itself.


**2008 Sept 1**

- Improvements in the JS-side interface. It's now possible to create new pieces, change them via setting properties, and delete them. _Querying_ certain types of piece properties is still problematic, and will be for the forseeable future.

- QGIDot objects can now be rotated. While rotating a circle might not have much visual effect, any children of the dot are rotated relative to the dot, so the rotation will be visible when a dot has been split or otherwise had children added to it.

- Added piece menu option to shuffle selected items. This only shows up when two or more items are selected, and randomly swaps the positions of the selected items. Parented items are not shuffled (it causes coordinate translation problems). This can be used, e.g., to randomly shuffle covered pieces or cards.

- Added board menu entries to create new dots and html items.


## **2008 August 31:** ##

- Removed the annoying warning dialog when building on Qt 4.3, since (a) most of the weird bugs are in Qt 4.4 now and (b) 4.3 is my main development target for the time being.

- Fixed: rotating the board no longer undoes the scaling.

- The lines created when "splitting" QGIDots are now configurable. To configure a given line, right-click the dot to which the line points (where the arrow points). Multiple lines can be configured by selecting all relevant dots and then right-clicking one of them.

- Fixed some focus/menu bugs in QGIHtml, caused by different event handling in Qt 4.3/4.4.

- Improvements to board scrolling and rotating. These actions will now attempt to keep the current center of the viewport intact (i.e. rotating/scaling around that point).


**2008 August 30:**

- A QGIDot can now create any number of child dots with a line connecting the children to the parent. I'm not at all happy with the parent/child relationship (and its effects on moving items), but i currently have no way to properly re-build the line/dot connections during deserialization if they're not hierarchical. The line properties are not currently configurable.

- Refactoring of the s11n support cut the build time by ~~about 1/3rd~~ almost 1/2. (Registration of s11n'able types takes a significant amount of compiler time/effort.)

**2008 August 29:**

- In the tree browser view, clicking Refresh to update the file view no longer collapses open dirs (unless those dirs no longer exist). Correction: this works only in Qt4.3. In Qt4.4 all open dirs are collapsed.

- Tapping the Delete key in the tree view will now delete the selected file (after asking for confirmation).

- Changed: QGIHtml needs only a single middle-click to launch the editor, instead of a double-middle-click.


**2008 August 28:**

- Fixed a few instances of mis-serialization of the zLevel, which caused pieces to be mis-stacked when loaded.

- Improved the piece "covers" significantly. All QGIs can be covered (not just QGIPiece). Covered items are now replaced by a proxy piece and they don't reveal what they're covering (at least, not to the casual observer).

- Changed: to set the board "placemarker" position, double-click the board instead of middle-clicking.

- Middle-clicking most items will now lower them to the bottom of the stack. Left-clicking them will, as ever, raise them to the top.


## **2008 August 27:** ##

- Fixed serialization of 'pos' property of QGIDot objects, which sometimes caused pasted dots to be mis-placed.

- Minor forward movement on the JS scriptability of pieces.


**2008 August 26:**

- Double-clicking .js files now runs them in the GameState's JavaScript engine.

- The Clone command now works properly for child objects (i.e. gives the clone the same parent).


**2008 August 25:**

- Removed the classes GamePiece, QGIGamePiece, and friends. This means that games saved with QBoard older than v20080820 will no longer load (or at least not completely load).

- Added Clone option to the copy/cut item menus. Cloning an item (or selected items) creates a copy of those items and places it directly on top of the original item, offset by a small amount.

- Started adding JavaScript support. Not yet sure where that's going, but it could be pretty cool.

- Removed QBoardBatch because JS will quickly make it useless.


**2008 August 24:**

- Replaced the file browser with a tree-based view - much more useful than before.

- Pieces can now be "covered." When covered, their images are not shown.

- Fixed: in Qt 4.3 the HTML widgets would become immobile after editing them via double-clicking them.


## **2008 August 23:** ##

- Added new item type, QGIDot - a simple dot to place around the board or as a child of another piece.


**2008 August 22:**

- i can't seem to get QGIHtml to intercept Ctrl-C/X/V/Z properly, but i've changed it to show the text editor's popup menu when in editor mode, so it's still possible to copy/cut/paste from there.

- Pieces can now have child objects. When a parent is moved, the children move relative to it. A child may also be dragged around independently. This can currently be used to attach QGIHtml objects to pieces, such that the QGIHtml will follow the piece around. There will be other uses at some point. TODO: draw lines between parent and children (i tried it, the lines only show up in GL mode).

- A few minor touch-ups.

- QGIPiece now uses a cache for its rendering options, which saves tons of redrawing (but also introduced 5+ hours of debugging the finer details of getting the borders to draw properly in the face of tiny rounding errors).

- Seem to have gotten rid of the "paint streaks" that happened when dragging pieces with larger border sizes.

**2008 August 21:**

- _**Fixed a very significant memory leak**_ in the menu handlers. One of them
was leaking like a sieve before.

- Pieces and HTML widgets can now be scaled independently of the board.
Now we can scale down larger piece graphics for use with game boards which have small hexes :). (Well, i've had that problem, anyway.)

- We can now copy ANY s11n-serializable type to a QVariant :), via a simple
proxy type.


## **2008 August 20:** ##

- The popup menus have been more unified. e.g. using Rotate will now
rotate all selected objects which support that property, instead of all
objects of the same type as the selected object.

- Started removing the split-brain GamePiece/QGIGamePiece combination
with a single object, QGIPiece. This allows me to remove several ugly workarounds
in places which shouldn't have them. Older saved files will (should) still load,
but new save files will have a slightly different structure.

- More cleanups in the positioning of pasted data.

- In theory older versions of QBoard can still load the newer saved data, but
there's no guaranty.


**2008 August 19:**

- Significant improvements in copy/paste, including:

  * Ctrl-C/Ctrl-X/Ctrl-V do the conventional things. Copy/cut requires that the board have at least one selected item.
  * Pasting with the mouse over the board will paste to that board position, otherwise it will try to restore the original position where the data was copied/cut from.

- Added underlying support to allow libs11n to (indirectly) use QIODevices as input/output source/targets. That means we can serialize directly to or from, e.g. QFile or QBuffer.


**2008 August 17:**

- QGIHtml (the on-board text widgets) can now be rotated.

- Improved pasting a bit. e.g.
  * pasted objects are now selected by default, since the most common action after a paste is adjusting the position of the group.
  * Can now paste more types of data into the game (namely GamePiece, QBoard, and Serializable QGraphicsItems).

- Clipboard is now better synchronized with the global Qt/X11 clipboard.


## **2008 August 16:** ##

- Added s11n support for QMap, plus QByteArray and QPixmap with compression.


**2008 August 15:**

- Added quicksave/quickload (Alt-S and Alt-L), which save/load to/from a predefined game file.

- Added ability to serialize QDate, QTime, and QDateTime properties.

- The "Clear board" action now leaves the underlying board graphic intact. This was an accident, but i like it better this way, so it stays.

- Fixed: board view now updates properly when a new board graphic is loaded. That is,
one no longer has to scroll the board to get the new image to show up.

- Added "Help" context menu item to some in-game objects.

- Copy/cut/paste is basically working. On-board lines don't paste in the proper location, but that's part of a bigger problem. Unfortunately, we can't currently bind keyboard shortcuts to copy/cut/paste because where those are caught we don't have access to the necessary widgets to initiate the copy/paste.

**2008 August 13:**

- Added a "placemarker" to the board. Pieces loaded via double-clicking
in the file browser will be set to the placemarker's position. To move
the placemarker, middle-click the board or drag the placemarker around.

- Added basic skeleton code for plugins support, using Qt's plugins framework.
It's not well integrated yet (you can't select plugins to open), but i was able
to load a plugin which had compiled-in PNG files (as resources), and was able
to use those resources as pixmap sources for in-play pieces. So the basics
seem to work, anyway.


## **2008 August 11:** ##

- Added "piece templates" to the main UI. The appearance of the
currently-selected template is used as the basis when loading piece
graphics from files. All changed made to the piece templates are
persistant across QBoard sessions.

- Fixed the mis-scaling of boards in Qt 4.3.

- Minimaps now keep their scale when a new board is loaded.

- Added basic support for locking a piece's position (simply disables dragging for the piece).


**2008 August 9:**

- Corrected several compile warnings caught by gcc 4.2.3.

## **2008 June 15:** ##

- Fixed a major bug under Qt 4.3 which caused non-piece gameboard items
to be not removed. The end effect was duplicate or extra items at
load-time.

- The main app can now process .qbbatch script files (the same files
read by qboardbatch).


**2008 June 14:**

- Fixed the broken app icons for qt 4.3. This was caused by an inconsistency
in how Qt Designer 4.3/4.4 handle icons associated with QActions.

- Too many little changes to remember.

- Added initial copy/cut support.  Paste is on the todo list, but
pasting is inherently target- and source-specific, so that'll take a
bit of work.

- Board now has a popup menu with a couple options. You wouldn't believe
what a bitch it was to get the event handling right in conjunction with
overlapping pieces and the board.


## **2008 June 13:** ##

- Initial release via Google Code.