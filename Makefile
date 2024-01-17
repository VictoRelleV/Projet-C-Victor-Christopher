# Makefile

# Compiler
CXX = g++
# Options de compilation
CXXFLAGS = -std=c++11 -fPIC -std=c++17

# Dossiers des fichiers d'en-tête de Qt
QT_INCLUDE = -I/usr/include/x86_64-linux-gnu/qt5/ -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets/ -I/usr/include/x86_64-linux-gnu/qt5/QtGui/

# Bibliothèques de Qt à lier
QT_LIBS = -lQt5Widgets -lQt5Core -lQt5Gui -lsfml-graphics -lsfml-window -lsfml-system 

# Nom de l'exécutable
TARGET = out

# Liste des fichiers source
SOURCES = main.cc joueur.cc match.cc fonctions.cc question.cc clickablelabel.cc lib/basketball/src/Solid.cpp lib/basketball/src/Net.cpp lib/basketball/src/Ball.cpp lib/basketball/src/Game.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	QT_QPA_PLATFORM=wayland $(CXX) $(CXXFLAGS) -o $@ $^ $(QT_INCLUDE) $(QT_LIBS)

clean:
	rm -f $(TARGET)
