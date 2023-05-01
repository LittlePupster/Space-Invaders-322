PROGRAM = main

CXXFLAGS = -g -Wall -Wextra -Wpedantic

LDFLAGS = -g

.PHONY: default
default: $(PROGRAM)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f core* *.o *~
        
main: main.o entity.o mainMenu.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lncurses -lstdc++
        
.PHONY: immaculate
immaculate: clean
	rm -f $(PROGRAM)
