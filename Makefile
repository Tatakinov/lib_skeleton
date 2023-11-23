LIBRARY			= library.dll
CXX					= clang++
CXXFLAGS		= -I . -Wall -Ofast -std=c++17
LD					= clang++
LDFLAGS			= -shared -lmsvcrt -Xlinker /NODEFAULTLIB:LIBCMT
OBJS				= lib.o \
					  util.o \
					  windows/dll.o \
					  base/header.o
ALL					= all

.SUFFIXES: .cc .o

.PHONY: all
$(ALL): $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(LD) $(LDFLAGS) -o $(LIBRARY) $(OBJS)

.cc.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f *.o windows/*.o base/*.o *.exp *.lib *.exe *.dll
