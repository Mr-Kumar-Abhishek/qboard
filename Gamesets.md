# QBoard gamesets #

A "gameset", in the context of QBoard, is simply a collection of graphics and/or
text files for use with a specific game. They are normally put into a directory
of their own, and this directory lives under the QBoard home directory.
QBoard places no inherent limitations on the directory structure of a gameset or the names of its files, with the exception that all files must live somewhere under the QBoard Home directory (see [HOWTOGettingStarted](HOWTOGettingStarted.md) for details).


# Creating your own sets #

Creating gamesets is trivial - you simply need some graphics and/or text/html files for content. There is no special tool involved or anything like that. Take a look at the sets described below below to see a few possible ways to structure sets.

QBoard is very free-form and will allow you to use any directory structure you like. A set with only a few graphics might just put them all in one directory. A set with 20 different types of pieces might break then down by category or team, for example.

If you want the QBoard GUI to show you a custom icon for a given directory, put a small (16x16 pixel) PNG-format icon file named `.diricon.png` in that directory. QBoard's file list will then show that icon instead of a folder icon. QBoard does not show files with a leading period in their name, so this file will not show up in the QBoard file browser.

If you want to include HTML content in your set, you may do so, but only QBoard built with
Qt 4.4+ can use it. HTML may use IMG with paths relative to the directory containing the HTML file, and they will be displayed as expected. In this way you can, for example, create charts of the available game pieces and their descriptions. The HTML documents may also include JavaScript code, insofar as it is supported by Qt's QWebKit classes. (i have successfully used the [jQuery JS library](http://www.jquery.com) with it, and it seems to work fine.)

As an example, let's set up the directories for a game called MyGame. Below i have drawn out a virtual directory structure, to show what it might look like. Remember that the top-most directory is the [QBoard Home directory](HOWTOGettingStarted.md).

```
games
  +-- MyGame
    rules.html
    +-- counters
      +-- (.png files for game counters)
    +-- maps
      +-- (.jpg files of game maps)
```

Now, in QBoard one would load the gameset's data by simply double-clicking on a file from under `games/MyGame`. Very simple sets (say, a handful piece types and one board) may not need to be split into separate directories. For larger games, though, it is usually helpful to separate counters by category, each category in a separate directory.

That's all there is to is.

# Available sets (in alphabetical order) #

Below are short descriptions of the gamesets released via the downloads page, in
alphabetical order. To install a given gameset, simply unpack it to your QBoard home directory.


---

## BattleTech(tm) and friends ##

This set includes lots of pieces (but no maps) compatible with the [BattleTech line of games](http://www.classicbattletech.com/). They can also be used for other games with mecha, of course.
You can actually find many BattleTech maps in PDF format at:

http://www.classicbattletech.com/index.php?action=downloads

Search that page for "map". But you'll need to extract them from the PDFs before using them with QBoard (their license doesn't allow us to redistribute them here). Tip: you can
use [The Gimp](http://www.gimp.org) to open the PDFs and then save them as an image file.)


---

## GenericSciFiGroundCombat ##

This set contains tons of good-looking counters created by Fransisco "Cisco" Cestero. Originally created as printable replacements for worn-out Ogre/GEV pieces, they are generic enough to be used with a variety of ground combat games. The counters tend to have a slightly sci-fi feel to them, though, and aren't suitable for WW2-themed games.


---

## Hex ##

Hex is a very simple strategy game for two players with a whopping 1 paragraph
of rules. Each player places tokens on a hexagon-based board and attempts to
connect to the far side, blocking his opponent as he goes.


---

## Insectica ##

Insectica, written by Trevor Blake, is a game about insect combat. The premise is unique (see the included PDF file) and some of the mechanics are quite original. The gameset includes all necessary counters, a board, and the rules in PDF format.


---

## Joe ##

**Joe** is a simple strategy combat game where little plastic army men
do combat on a chessboard. Joe is an original title, by yours truly.
It can be learned and played in under half an hour, and should be flexible
enough to support a variety of play styles and options.


---

## Ogre(tm) and G.E.V.(tm) ##

[Ogre and G.E.V.](http://sjgames.com/ogre/) are classic sci-fi strategy games
by [Steve Jackson](http://sjgames.com) depicting armored combat in near-future
nuclear battlefields. This set includes a compilation of maps and playing pieces
(some "official", some not) for use with those games. The maps were originally
distributed as part of the V\_MAP Ogre gameset, but V\_MAP has long been defunct.
The pieces come in two forms:

  * The V\_MAP set: 35x35-pixel (small) pieces from the venerable V\_MAP set, created by Todd Zircher (author of V\_MAP).
  * The "Cisco" set: 48x48-pixel (1/2 inch) custom pieces created by Francisco "Cisco" Cestero, originally intended as printable replacements for the official game counters. These counters are larger than the hexes on the supplied maps, but can be used on custom maps or printed out.

While QBoard won't stop you from using those two sets together, they use
different graphics styles and scales, so interchanging them is not recommended. (One notable exception is that the Cisco Ogre counters might be appropriate for use with the V\_MAP sets.)

The counters all come in the classical black-on-white and white-on-black combinations, plus with black and white on transparent backgrounds, so one can use custom background colors and translucency.