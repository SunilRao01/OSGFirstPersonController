all: camManipLib

camManipLib: FirstPersonController.cpp FirstPersonController.h
	g++ -fPIC -Wall -shared FirstPersonController.cpp -o libFirstPersonController.so -losg -losgGA -losgViewer

install: camManipLib
	cp ./libFirstPersonController.so /usr/lib
	cp ./FirstPersonController.h /usr/include
	ldconfig /usr/lib/libFirstPersonController.so

uninstall:
	rm /usr/lib/libFirstPersonController.so
	rm /usr/include/FirstPersonController.h
	ldconfig

exCube: examples/cube.cpp
	g++ -Wall examples/cube.cpp -lFirstPersonController -losg -losgGA -losgViewer -o cube

clean: 
	rm -f libFirstPersonController.so cube
