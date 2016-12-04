CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = history.o grid.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o main.o coordinate.o level.o level0.o level1.o level2.o level3.o level4.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
