.SILENT:

OBJS=mainex4.o mainwindowex4.o moc_mainwindowex4.o
OBJST=maintraitement.o mainwindowtraitement.o moc_mainwindowtraitement.o
PROGRAM=UNIX_Exercice4
LIBG=-c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++
LIBQT=/usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so 
LIBMSQL=-L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl 

all: $(PROGRAM) 
	$(PROGRAM)

$(PROGRAM):	$(OBJS) Traitement
	echo "Compilation de l' executable UNIX_Exercice4"
	g++ -o UNIX_Exercice4 $(OBJS) $(LIBQT)

Traitement:	$(OBJST)
	echo "Compilation de l' executable Traitement"
	g++ $(LIBMSQL) -o Traitement $(OBJST) $(LIBQT)

mainex4.o:	mainex4.cpp
	echo "Compilation du mainex4.o"
	g++ $(LIBG) -o mainex4.o mainex4.cpp

mainwindowex4.o:	mainwindowex4.cpp
	echo "Compilation du mainwindowex4.o"
	g++ $(LIBG) -o mainwindowex4.o mainwindowex4.cpp

moc_mainwindowex4.o: moc_mainwindowex4.cpp
	echo "Compilation du moc_mainwindowex4.o"
	g++ $(LIBG) -o moc_mainwindowex4.o moc_mainwindowex4.cpp

maintraitement.o: maintraitement.cpp
	echo "Compilation du maintraitement.o"
	g++ $(LIBG) -o maintraitement.o maintraitement.cpp

mainwindowtraitement.o: mainwindowtraitement.cpp
	echo "Compilation du mainwindowtraitement.o"
	g++ $(LIBG) -I/usr/include/mysql -m64 -o mainwindowtraitement.o mainwindowtraitement.cpp

moc_mainwindowtraitement.o: moc_mainwindowtraitement.cpp
	echo "Compilation du moc_mainwindowtraitement.o"
	g++ $(LIBG) -o moc_mainwindowtraitement.o moc_mainwindowtraitement.cpp

clean:
	echo "Suppression des fichiers objets suivant : $(OBJS) $(OBJST)"
	rm -f $(OBJS) $(OBJST)

clobber: clean
	echo "Suppression de tous les programmes obtenues apres compilation : $(PROGRAM)"
	rm -f $(PROGRAM) Traitement
