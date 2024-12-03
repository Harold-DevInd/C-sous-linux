.SILENT:

TARGET=UNIX_exercice1
COMP=g++ -Wall -pipe -g -std=gnu++11 -W -D_REENTRANT -fPIC
OBJS=main.o mainwindow.o moc_mainwindow.o
LIBQT=-DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

$(TARGET):	main.o mainwindow.o moc_mainwindow.o
	echo "Compilation de l executable $(TARGET)"
	g++ -o $(TARGET) main.o mainwindow.o moc_mainwindow.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

main.o:	main.cpp
	echo "Compilation du main"
	$(COMP) -c $(LIBQT)  -o main.o main.cpp

mainwindow.o:	mainwindow.cpp
	echo "Compilation du mainWindow"
	$(COMP) -c $(LIBQT) -o mainwindow.o mainwindow.cpp

moc_mainwindow.o:	moc_mainwindow.cpp
	echo "Compilation du moc_mainwindow"
	$(COMP) -c $(LIBQT) -o moc_mainwindow.o moc_mainwindow.cpp

clean: 
	echo "Suppression des librairie .o : $(OBJS)"
	rm -f $(OBJS) core

clobber: clean
	echo "Suppression des librairie $(TARGET)"
	rm -f $(TARGET)
