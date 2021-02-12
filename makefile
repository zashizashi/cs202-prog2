CC = g++
CPPFLAGS = -std=c++11 -g -Wall
OBJTS = main.o calendar.o event.o

main: $(OBJTS)

main.o: calendar.h event.h

calendar.o: calendar.h event.h

event.o: event.h

.PHONY: clean
clean:
	$(info -- cleaning the directory --)
	rm -f *.o
	rm -f main
