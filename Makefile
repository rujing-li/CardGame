CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = straights
OBJECTS = card.o deck.o table.o player.o game.o strategy.o humanstrategy.o computerstrategy.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}