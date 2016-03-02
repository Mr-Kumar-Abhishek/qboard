_**As of 26 August 2008 qboardbatch has been removed. It is being replaced by JavaScript bindings, which are much more powerful.**_

# qboardbatch #

qboardbatch (we'll call it qbb for short) is part of the QBoard distribution. It is a command-line tool which reads in a simple batch scripting language for constructing games.
While QBoard does not need a script (it can read graphics files directly), practice has shown that it is often useful to be able to create game data from existing sets of game files, and this tool was created to support that.

Here's a sample script:

```
// sample qboardbatch script
board // set the "current object" to the game board
set pixmap maps/mymap.jpg

// Create a new piece:
new piece
// Set properties of the piece:
set pixmap mygame/counters/infantry.png
set color #ff0000 // colors can be in "#rrgggbb" or "R G B"
set colorAlpha 100
set pos 100 150
// qbb knows what data type to use for most common piece properties,
// but for custom properties it is sometimes useful to tell it to
// interpret a value as a specific type:
set -point customPointProperty 10 20
set -color customColor #00ff00

// Create another piece:
new piece
set pixmap mygame/counters/heavy_tank.png
set color 128 128 255
set pos 10 20

// Save the game:
save mygame
// If you want to save to stdout instead of a file,
// just leave off the 'mygame' part.
```

To anyone who's scripted anything before, what that is doing should be more or less obvious.

Assuming we saved that in a file named `mygame`, we would process it like:

```
~> qboardbatch mygame
```

The generated file will (if all goes well) be readable by QBoard. It's also readable by you, in case you feel the need to hand-edit it. Note that the exact file format is not defined, as the underlying serialization layer is ignorant of specific formats and has support for 6 or 7 formats. (See [the data formats page](DataFormats.md) for details.)

The generated file will, in all likelyhood, get an automatic file extension added to it (the exact extension depends on exactly what data is saved). These file extensions are supported by QBoard for figuring out what type of data to treat the file as, so please don't rename them.

If you want to see what qbb is doing while it's doing it, pass the `-v` option to enable verbose mode. e.g.

```
~> qboardbatch -v myfile
```

It accepts an arbitrary number of files. If you don't use the `new game` command in any of them you can use this feature to import data from multiple scripts into one game.