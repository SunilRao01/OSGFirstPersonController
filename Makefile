all: camManipLib

camManipLib: myKeyboardEventHandler.cpp myKeyboardEventHandler.h
	g++ -fPIC -shared myKeyboardEventHandler.cpp -o libmyKeyboardEventHandler.so -losg -losgGA -losgViewer

install: camManipLib
	cp ./libmyKeyboardEventHandler.so /usr/lib
	cp ./myKeyboardEventHandler.h /usr/include
	ldconfig /usr/lib/libmyKeyboardEventHandler.so

exCube: examples/cube.cpp
	g++ examples/cube.cpp -lmyKeyboardEventHandler -losg -losgGA -losgViewer -o cube
