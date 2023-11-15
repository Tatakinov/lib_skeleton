LIBRARY			= popup.dll
CXX					= clang++
CXXFLAGS		= -I . -Wall -Ofast -std=c++17
LD					= clang++
LDFLAGS			= -shared -lmsvcrt -Xlinker /NODEFAULTLIB:LIBCMT
OBJS				= lib.o \
					  util.o \
					  windows/dll.o \
					  sstp/header.o sstp/request.o sstp/response.o
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
	rm -f *.o windows/*.o sstp/*.o *.exp *.lib *.exe *.dll
