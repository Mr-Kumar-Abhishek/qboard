include(../../config.qmake)
TEMPLATE = app
QT += script svg
QMAKE_CXXFLAGS = $$QBOARD_CXXFLAGS
RESOURCES = $$RESOURCES_DIR/icons.qrc
FORMS = \
 $$UI_SRCDIR/AboutQBoard.ui \
 $$UI_SRCDIR/MainWindow.ui \
 $$UI_SRCDIR/QGIHtmlEditor.ui \
 $$UI_SRCDIR/ScriptWindow.ui \
 $$UI_SRCDIR/SetupQBoard.ui \
 $$QBOARD_FORMS_QT44

HEADERS = \
 $$QBOARD_HEADERS_LIB \
 $$QBOARD_HEADERS_WINDOW

SOURCES = \
 $$QBOARD_SOURCES_LIB \
 $$QBOARD_SOURCES_WINDOW \
 $$QBOARD_SOURCES_MAINAPP 

OBJECTS += $$S11N_OBJECTS
