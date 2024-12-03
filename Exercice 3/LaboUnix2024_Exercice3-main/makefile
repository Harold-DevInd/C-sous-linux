.SILENT:

OBJS=main.o mainwindowex3.o moc_mainwindowex3.o
PROGRAM=UNIX_Exercice3
LIBG=-c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++
LIBQT=/usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

all: $(PROGRAM)
	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	echo "Compilation de l' executable $(PROGRAM)"
	g++  -o UNIX_Exercice3 main.o mainwindowex3.o moc_mainwindowex3.o $(LIBQT)

main.o:	main.cpp
	echo "Compilation du main.o"
	g++ $(LIBG) -o main.o main.cpp

mainwindowex3.o:	mainwindowex3.cpp
	echo "Compilation du mainwindowex3.o"
	g++ $(LIBG) -o mainwindowex3.o mainwindowex3.cpp

moc_mainwindowex3.o: moc_mainwindowex3.cpp
	echo "Compilation du moc_mainwindowex3.o"
	g++ $(LIBG) -o moc_mainwindowex3.o moc_mainwindowex3.cpp

CreationBD:	CreationBD.cpp
	echo "Compilation du CreationBD.cpp"
	g++ -o CreationBD CreationBD.cpp -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

Lecture:	Lecture.cpp
	echo "Compilation du Lecture.cpp"
	g++ -o Lecture Lecture.cpp -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

clean:
	echo "Suppression des fichiers objets suivant : $(OBJS)"
	rm -f $(OBJS)

clobber: clean
	echo "Suppression de tous les programmes obtenues apres compilation : $(PROGRAM)"
	rm -f $(PROGRAM) Lecture CreationBD
