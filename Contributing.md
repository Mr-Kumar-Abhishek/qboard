The main reason for moving QBoard to Google Code was to help attract other developers. With more developers, each with their own views of right and wrong, which QLayout to use, and which shade of blue looks best on Jennifer Connelly, really increases the innovation level of a project.

Believe it or not, filing bug and request-for-enhancement reports is a great form of contribution. :) (See the Issues link at the top of this page!)

If you would like to contribute, please get in touch:

http://wanderinghorse.net/home/stephan/

Some particular areas i'd like to see _someone else_ work on are:

  * i18n. There's not terribly much text in the app, so there's no much actual translation work to do. Someone with knowledge of how to set up the translations infrastructure would be really appreciated, though.
  * Figuring out how to solve the weird bugs which show up in Qt4.3 but not 4.4.
  * A graphics wiz to help add more features to the QGraphicsView-based parts.
  * Custom game graphics would be really cool. i've actually got tons of them, but i'm no graphics artist and have no real talent for making _nice looking_ graphics.
  * Windows platforms. i don't have any of them, but i'd love to see it working on Windows.
  * Improved drag/drop support. e.g. it appears to be impossible to drag items across different QGraphicsViews, even if they all belong to the same QGraphicsScene. To make this work would mean completely reimplementing the built-in drag/drop features, i think. The drag/drop support and copy/paste implementations are closely related, actually, and the copy/cut works already (well, for Serializable types, anyway).