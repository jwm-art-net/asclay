#---------------------------------------------------
# Release
#---------------------------------------------------
DEFS=-O2 -fomit-frame-pointer


#---------------------------------------------------
# Debug
#---------------------------------------------------
# DEBUG		= show various information supposedly to aid debugging.

DEFS=-ggdb -fno-inline -DDEBUG


#---------------------------------------------------
# No more options
#---------------------------------------------------

PROG=asclay
WARNS=-Wall -Wextra
CFLAGS=$(DEFS) $(WARNS)
LIBS=
SRC=$(wildcard *.cc)
OBJS=$(SRC:.cc=.o)
HEADERS=$(wildcard src/*.h)

$(PROG) : $(OBJS)
	echo Linking $(PROG)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -ldl -o $(PROG)
	echo $(PROG) was compiled with:
	echo $(CXX) $(CFLAGS)

%.o : %.cc $(HEADERS)
	echo Compiling $(<F)
	$(CXX) $(CFLAGS) -c $< -o $@

main.o: main.cc $(HEADERS)


clean:
	@rm -vf $(OBJS) $(PROG)

.PHONEY: clean
