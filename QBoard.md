# Welcome to QBoard #

QBoard is a UI for playing near-arbitrary board games. It is mainly intended as
a prototyping platform for testing/playing my own boardgame designs.

QBoard is a "re-imagining" of a much older project of mine called
[the Q Universal Boardgame](http://qub.sourceforge.net|QUB,). QUB was quite monolithic, and its sheer size eventually caused its downfall. While QBoard originally aimed to be a fairly minimalistic application, Qt makes it pretty easy to just keep adding features, so QBoard already does a lot more than was originally planned.

For information on getting started with QBoard, see [HOWTOGettingStarted](HOWTOGettingStarted.md).

## Screenshots ##

You can find screenshots on the [screenshots page](Screenshots.md).

## What can one do with QBoard? ##

Some things QBoard can be used for:

  * Quickly prototype boardgame designs.
  * Play boardgames for which you have appropriate graphics.
  * PBEM (play-by-email) gaming
  * Maintaining maps for a roleplaying game. e.g. a campaign map can be annotated, locations of the characters can be recorded with counters, etc.
  * For me, programming it has been a good way to burn hundreds of hours which i should have spent with my girlfriend and [my dog](http://picasaweb.google.com/sgbeal/TheDog).

## Features ##

  * A simple interface for quickly setting up and playing a boardgame.
  * Has powerful and flexible save and load features, making it easy to add load/save support for new data types.
  * Get right to playing - there is no tedious separate setup of "gameset" and "scenario" files, as there is in, e.g., [CyberBoard](http://cyberboard.brainiac.com/) (arguably the most well-known application in this category).
  * Has no inherent limits on how many pieces can be in play. It has been shown to easily handle more than 500 at a time.
  * As QBoard has only a fluid concept of what a "game" is, it is possible to mix and match pieces from arbitrary [Gamesets](Gamesets.md) in the same session.
  * A zoomable, rotatable playing area (game board + pieces).
  * Full control over game piece background colors, transparency, rotation, and border (color, transparency, size, line style). Finally: translucent game pieces!
  * Supports an arbitrary number of dockable "minimap" views, all fully interactive and synchronized in real time.
  * On-board HTML widgets, so you can annotate your game as much as you like. You can also attach HTML widgets directly to arbitrary game pieces.
  * On-board "dots", with varying sizes and transparency, can be used as pieces by themselves or e.g. as state markers.
  * On-board lines, with customizable colors, line size, and transparency level. Useful for marking movement paths (or histories), firing ranges or arcs, line of sight, and such.
  * Pieces can have "child objects" which follow them around when the piece is dragged. e.g. one can add a text label, a record form, or status markers to any piece.
  * Use copy, paste, and cloning to quickly set up an army of pieces.
  * "Shuffle" any items by selecting several items and using the Shuffle menu option. Useful for cards, simulating a cup of chits, and randomizing piece selection or placement.
  * JavaScript bindings are under developement. [The basic stuff works](JavaScript.md), but this work is ongoing.
  * Built-in wiki viewer which supports most of the wiki syntax provided by Google Code Wiki (e.g. this page).

See also: the [TODOs](TODOs.md) Page

## Requirements ##

  * Patience. It's beta software.
  * An implementation of the standard C++ STL. Most compiler environments have this built in.
  * Qt 4.3.x or 4.4.x with STL support enabled and optionally with OpenGL. QBoard seems to work with Qt 4.3.0-4.3.5, but sometimes shows some significantly weird behaviours which don't show up on 4.4.
  * Platforms: it tries to be platform-independent, and it "should" work on any Qt platform which supports all the big Qt features (e.g. QWebKit, STL, etc.). i would love to hear from anyone who tries it on non-Linux platforms.
  * Some graphics which you can use as game boards and playing pieces. We've got some free gaming maps at http://wanderinghorse.net/gaming/maps and free counters (playing pieces) at http://wanderinghorse.net/gaming/counters.
  * [libs11n](http://s11n.net) 1.2.7+. It comes with a standalone copy of s11n, so you don't need to download it. s11n requires a fairly recent C++ compiler - gcc 4.1+ are believed to be okay, as are newer MS compilers.


## Development Status ##

QBoard is very much beta software. It runs fine, but some important
features are as yet unimplemented, and some other things will probably
change significantly over time. QBoard is not a project which aims to ever have a "1.0" release, and to that end it uses the release date, in YYYYMMDD format, as a version number.

The copy of the source code in Subversion may or may not work at any given
moment (normally it does, though). Occasionally it reaches a point where we say, "it works! Ship it!" Those are the "official" releases (available via the
downloads link), and are _believed_ to be free of major defects
(e.g. crashes or other data loss).

That said - there will be times when a release is not strictly backwards-compatible (i.e. cannot read all data written with an earlier version). This will probably be minimal, however, because the i/o layer allows us to easily support multiple versions of an object's i/o format in many cases. There are **never** any guarantees that an older version of QBoard can read all data written by a newer version.