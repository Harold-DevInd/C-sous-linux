.SILENT:

OBJS=main.o mywindow.o moc_mywindow.o FichierUtilisateur.o
PROGRAM=UNIX_Exercice2
LIBQT=-DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

#all:
#	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	echo "Compilation de l' executable $(PROGRAM)"
	g++  -o UNIX_Exercice2 main.o mywindow.o moc_mywindow.o FichierUtilisateur.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

main.o:	main.cpp
	echo "Compilation du main.o"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC $(LIBQT) -o main.o main.cpp

mywindow.o:	mywindow.cpp
	echo "Compilation du mywindow.o"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC $(LIBQT) -o mywindow.o mywindow.cpp

moc_mywindow.o: moc_mywindow.cpp
	echo "Compilation du moc_mywindow.o"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC $(LIBQT) -o moc_mywindow.o moc_mywindow.cpp

FichierUtilisateur.o:	FichierUtilisateur.cpp
	echo "Compilation du FichierUtilisateur.o"
	g++ -c FichierUtilisateur.cpp

clean:
	echo "Suppression des fichiers objets suivant : $(OBJS)"
	rm -f $(OBJS)

clobber: clean
	echo "Suppression de tous les programmes obtenues apres compilation : $(PROGRAM)"
	rm -f $(PROGRAM)