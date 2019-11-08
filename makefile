enigma: enigma.o helper.o plugboard.o rotor.o reflector.o
	g++ enigma.o helper.o plugboard.o rotor.o reflector.o -o enigma 

enigma.o: enigma.cpp helper.h errors.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c enigma.cpp

helper.o: helper.cpp helper.h errors.h
	g++ -Wall -g -c helper.cpp

plugboard.o: plugboard.cpp plugboard.h helper.h errors.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: plugboard.cpp plugboard.h helper.h errors.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h helper.h errors.h
	g++ -Wall -g -c rotor.cpp

clean:
	rm -f *.o enigma
