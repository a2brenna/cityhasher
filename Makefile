INCLUDE_DIR=$(shell echo ~)/local/include
LIBRARY_DIR=$(shell echo ~)/local/lib
DESDTIR=/
PREFIX=/usr

CXX=clang++
CXXFLAGS=-L${LIBRARY_DIR} -I${INCLUDE_DIR} -O2 -g -std=c++11 -fPIC -Wall -Wextra -march=native

all: cityhasher

install: cityhasher
	mkdir -p ${DESTDIR}/${PREFIX}/bin/
	cp cityhasher ${DESTDIR}/${PREFIX}/bin/

uninstall:
	rm -f ${DESTDIR}/${PREFIX}/bin/cityhasher

cityhasher: src/cityhasher.cc
	${CXX} ${CXXFLAGS} src/cityhasher.cc -o cityhasher -lboost_program_options -lcityhash

clean:
	rm -f *.o
	rm -f *.so *.a
	rm -rf cityhasher
