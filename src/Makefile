CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: main.o rsdl.o FieldRunners.o Player.o Towers.o Enemy.o Timer.o Shot.o stdin.o PositionHandler.o
	$(CC) rsdl.o main.o FieldRunners.o Player.o Towers.o Enemy.o Timer.o Shot.o stdin.o PositionHandler.o $(CCFLAGS) -o FieldRunners.out

FieldRunners.o: FieldRunners.cpp rsdl.hpp defines.hpp FieldRunners.hpp Player.hpp Towers.hpp Enemy.hpp Timer.hpp Shot.hpp PositionHandler.hpp
	$(CC) -c FieldRunners.cpp

main.o: main.cpp rsdl.hpp defines.hpp FieldRunners.hpp Player.hpp Towers.hpp Enemy.hpp Timer.hpp stdin.hpp
	$(CC) -c main.cpp

Player.o: Player.cpp rsdl.hpp defines.hpp Player.hpp
	$(CC) -c Player.cpp

Towers.o: Towers.cpp rsdl.hpp defines.hpp Towers.hpp Timer.hpp
	$(CC) -c Towers.cpp

Enemy.o: Enemy.cpp rsdl.hpp defines.hpp Enemy.hpp Timer.hpp Shot.hpp defines.hpp
	$(CC) -c Enemy.cpp

Timer.o: Timer.cpp rsdl.hpp Timer.hpp
	$(CC) -c Timer.cpp

Shot.o: Shot.cpp rsdl.hpp Shot.hpp Towers.hpp defines.hpp
	$(CC) -c Shot.cpp

stdin.o: stdin.hpp
	$(CC) -c stdin.cpp

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp

PositionHandler.o: PositionHandler.cpp rsdl.hpp PositionHandler.hpp defines.hpp
	$(CC) -c PositionHandler.cpp

clean:
	rm *.o FieldRunners.out

