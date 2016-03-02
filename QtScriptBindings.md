# Qt Script Generator #

Achtung: this support requires Qt 4.4.1+. It won't work with Qt 4.4.0 and earlier.

As of 20080913, worked started on support for the Qt/JS bindings being created by the Qt Script Generator project:

http://labs.trolltech.com/page/Projects/QtScript/Generator

to simplify QBoard development using those generated bindings, we have pre-generated copies of the bindings in the QBoard source repository, and available as a download on the Downloads page (look for `QtScriptBindings-*.tar.bz2`). This copy will be kept reasonably up to date with whatever is in the Qt Script Generator source repository. This copy contains no changes, just a simplified build process over the original (because the .cpp files are already generated). It also contains a few bits i've hacked together, which aren't part of the Qt API bindings but are QtScript plugins.

The current (Sept 13 2008) status of the bindings seems to be:

  * A huge portion of the Qt API is covered, available for calling via JS scripts!
  * Not all of it works _quite_ right. A great deal does work, however, and will allow us to write all kinds of functionality in JS code instead of C++.

These bindings are much, much more powerful and complete than anything i could dream of coding up, so they will eventually replace some of the Qt/JS bindings QBoard has already (at the cost of having to sacrifice some features when QBoard is built under Qt 4.3).

# Downloading #

Follow the download link at the top of this page and look for `QtScriptBindings-*.tar.bz2`.

# JS bindings API documentation #

To get the complete JS-side API docs, see `doc/index.html` in the downloadable package.

# Using this stuff from QBoard #

If you build the bindings code (as explained in the included README file), you can use the bindings in QBoard (version 20080913+) by puting the binding DLL files (`libqtscript_*.so`) in your QBoard home dir, under `QBoard/plugins/script`. Then you can access them from JS code:

```
qt.script.importExtension('qt.core');
qt.script.importExtension('qt.gui');
...
```

The list of available modules is:

  * qt.core
  * qt.gui
  * qt.uitools
  * qt.network
  * qt.opengl
  * qt.sql
  * qt.svg
  * qt.webkit
  * qt.xml
  * qt.xmlpatterns

But since it is all beta code, any given module may or may not load.

Also be aware that it is possible to crash QBoard by creating and destroying QGraphicsItems and such indiscriminately from QBoard. It is important not to re-use JS references to native objects which have been deleted (e.g. via Cut or a popup menu open).