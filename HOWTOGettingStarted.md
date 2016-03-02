# HOWTO: getting started with QBoard #

This guide gives a brief overview of how to get started with QBoard and how to use its more significant features.

For instructions on compiling QBoard, see the [CompilingQBoard](CompilingQBoard.md) page.

## First: QBoard Home Directory ##

To allow us to save relative paths in our data files, we need a common root directory which is portable across platforms. To that end, we request that you store all QBoard-related data files under the QBoard home directory (`~/.QBoard`). QBoard tries its best to make sure you stay inside the home directory. For example, when loading graphics files for pieces and boards, it uses a path relative to the home, if possible, as this makes the saved data portable to other machines (or if the QBoard home dir changes).

## Graphics Files ##

Before getting started with QBoard, you will need to put some files in the home dir, namely:

  * Graphics for boards.
  * Graphics for pieces.
  * Any .txt or .html files you may want to load from within QBoard.

You may structure your data however you like under the home directory, with the
exception that the subdirectory named `QBoard` is reserved for use with
QBoard-specific application data. If you need some ideas, see the available [Gamesets](Gamesets.md).


## Loading Files ##

  * Double-clicking an image file will load it as a game board (if it is bigger than 10KB) or a game piece (if it is smaller). Pieces loaded this way will be placed on the board at the same spot where the yellow and red "placemarker" is.
  * Double-clicking on other files will attempt to load them. What exactly happens here depends on the file type. The same happens when using the Open File menu/button.
  * Double-clicking a .txt or .html file will open it in a browser (only when compiled against Qt 4.4!).
  * Double-clicking a .wiki file will open it in the built-in wiki browser, which accepts a subset of the wiki syntax supported by Google Code Wiki (e.g. this page).

## Saving ##

  * To save a game, click the Save button or File->Save menu item. That will save the entire game state.
  * It is in principal possible to save any in-game object individually (e.g. individual pieces or JUST the board, without the pieces), but there is currently no UI for doing so.
  * Use the Quicksave and Quickload features to quickly save and load.

## Manipulating items ##

Most items have a popup menu (accessible via right-clicking). If an item is selected and its menu is activated, many of the menu operations may apply to all selected pieces (e.g. Destroy, Cut/Copy, rotation, etc.). If a piece is not selected, actions taken through its popup menu will affect only that item (and potentially child items).

Explore the menus for the available options. Note that different types of game pieces will have different menus.


## Minimaps ##

QBoard has a main board view and any number of "minimaps", which are simply copies of the board view which start out at a smaller scale. The minimaps can be zoomed in/out to any degree the main map supports by using Ctrl-ScrollWheel while hovering over the view.

However - having any scaled board view active _drastically_ cuts performance of on-board drag operations, especially once a few items are selected. As in "unusably slow". There are two known workarounds:

  * Use the right-click menues to enable OpenGL mode in the mini view and disable it in the main view, and keep the main view _unscaled_. In my experience, this solves the "drag slowdowns" problem (but can cause other graphics glitches in the minimap, at least on my platform).
  * Open a minimap only when you need it, and close it when you're done. :/

In any case, try to avoid zooming the main view unless you need it temporarily. There's a hotkey to zoom back to 100% - look in the Board menu of QBoard for the key combination.

If you don't use minimaps, it is normally a good idea to turn on GL mode on the main board, as doing so drastically speeds up any operations when the board is scaled. However, GL mode is known to cause graphics glitches at times (e.g. pieces become temporarily invisible).

## Piece style templates ##

The colorful squares in the bottom/left of the main window are piece style templates. If you click one of those, newly-added pieces will take on that style. Use the right-click menu to edit them. You can also paste items copied from the board into this area, so you can customize your templates in any ways you like, including adding new ones or removing them.

The templates area is saved automatically when QBoard exits. If you have hosed your templates beyond repair and want to start with a new set, close QBoard, delete the file `~/.QBoard/QBoard/persistance/MainWindow/default-templates`, then start QBoard. Deleting or replacing the file while QBoard is open will have no effect, as the file will be replaced or overwritten when QBoard exits.


## The clipboard ##

Most in-play objects can be copied, cut, and pasted within the board. When objects are copied or cut, their data is available as text in the Qt clipboard, which means you can paste it into another application (e.g. a text editor). From there, you can edit it, copy it, and paste it back into QBoard. Some people might call that cheating, but this ability is often useful for testing, or even as a poor man's substitute for File-->Save. It's also useful for pasting in sets of pieces which are commonly used.