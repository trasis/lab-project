CC    = g++
FLAG  = -std=c++11
SRC   = Date.o User.o Meeting.o Storage.o AgendaService.o
Test : Test.cpp Date User Meeting Storage AgendaService
	$(CC) $(FLAG) -o Test Test.cpp $(SRC)
Date : Date.cpp
	$(CC) $(FLAG) -c Date.cpp
User : User.cpp Date
	$(CC) $(FLAG) -c User.cpp
Meeting : Meeting.cpp User Date
	$(CC) $(FLAG) -c Meeting.cpp
Storage : Storage.cpp User Meeting Date
	$(CC) $(FLAG) -c Storage.cpp
AgendaService : AgendaService.cpp User Meeting Date Storage
	$(CC) $(FLAG) -c AgendaService.cpp
clean:
	rm *.o Test agenda.data
