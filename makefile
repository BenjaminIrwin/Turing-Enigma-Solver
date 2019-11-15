enigma: main.o enigma.o helper.o plugboard.o rotor.o reflector.o
	g++ main.o enigma.o helper.o plugboard.o rotor.o reflector.o -o enigma 

main.o: main.cpp enigma.h helper.h errors.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp enigma.h helper.h errors.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c enigma.cpp

helper.o: helper.cpp helper.h errors.h
	g++ -Wall -g -c helper.cpp

plugboard.o: plugboard.cpp plugboard.h helper.h errors.h
	g++ -Wall -g -c plugboard.cpp

rotor.o: rotor.cpp rotor.h helper.h errors.h
	g++ -Wall -g -c rotor.cpp

reflector.o: reflector.cpp helper.h errors.h
	g++ -Wall -g -c reflector.cpp

clean:
	rm -f *.o enigma
