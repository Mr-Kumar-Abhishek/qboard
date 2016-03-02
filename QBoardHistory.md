# A brief history of QBoard #

Boardgames, mainly tabletop strategy games, have been a hobby of mine since i was a teenager. As i grew up and became a programmer, i naturally ended up wanting to write software to support my hobby.

In the beginning there was GUB, the Generic Universal Wargame. GUB started life as a Java applet in late 1997 or early 1998. After a few months, tired of fighting with the limitations of applets and Java incompatibilities between the Netscape and MSIE browsers, i switched from an applet to a Java application (there are technical differences, in case you don't know). GUB enabled one to load and save games and do basic things like move pieces, but it wasn't terribly advanced. At some point i had so many problems with the drag/drop support of JDK's under Linux at the time, that i gave up work on GUB.

Soon after i decided to take another whack at learning C++. So GUB became, some months later, QUB, the Q Universal Boardgame (http://qub.sourceforge.net). QUB, like QBoard, was a Qt-based application (but Qt3, not Qt4) written in C++. QUB was quite good at what it did, but it eventually became too monolithic and problematic to maintain, so i put it on ice in 2004 while i considered a rewrite. (It was also taking half an hour to build, which meant making any significant changes had a really long code/compile/test cycle.)

In the summer of 2008, i got an itch to rewrite QUB, and started working on QBoard. QBoard, while probably not as overall flexible as QUB, has many features which QUB could not have so easily provided, some examples being transparent pieces, piece scaling, and scaling of the game board. (QUB's over-flexibility was also a big contributor to its downfall - it evolved way too much special-case handling code for specific cases which didn't fit into its generic model.) QBoard also takes advantage of Qt's newer 2D graphics classes, which are much more useful for gaming purposes than normal UI widgets are.

Earlier i wrote "in the beginning there was GUB", but that wasn't exactly true. Shortly after i started work on GUB i found out about V\_MAP, a now-defunct application with only the most basic boardgame support (but rock solid at what it did). V\_MAP's simplicity has always remained an inspiration, but i need more out of a boardgame interface than V\_MAP could ever provide.

Aside from V\_MAP, other programs of this nature have also come and go. The ones i know about are:

  * [the venerable CyberBoard](http://cyberboard.brainiac.com/index.html), which is still maintained, as far as i can tell, and has always had quite a following. It's a free download, but the source code is not available.
  * Electronic Cardboard, a commercial product which doesn't appear to still exist, and which i've never used.
  * [Aide de Camp 2](http://www.hpssims.com/Pages/products/adc2/ADC2-Main.html), a commerical product which i never used.
  * [VASAL](http://www.vassalengine.org), on online-playable game engine of which i wasn't aware until today.
  * James McCann's xpbm, a more-minimalist-than-V\_MAP clone of V\_MAP which, AFAIK, never saw distribution other than between James and myself. i often used xpbm while awaiting the rewrite of QUB.

# The future of QBoard #

Where is QBoard headed? i have no clue whatsoever. i'll tinker and tinker, and we'll see what happens.