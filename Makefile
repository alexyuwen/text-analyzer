OBJS=yuwen_alex_assn4.o TextAnalyzer.o WordEntry.o
DEBUG=-g
CC=g++
CXXFLAGS += -std=c++11
CFLAGS=-Wall -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)
EXE=cExe

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

yuwen_alex_assn4.o: yuwen_alex_assn4.cpp BST.h TextAnalyzer.cpp TextAnalyzer.h
	$(CC) $(CFLAGS) yuwen_alex_assn4.cpp

TextAnalyzer.o: TextAnalyzer.h TextAnalyzer.cpp BST.h WordEntry.h WordEntry.cpp
	$(CC) $(CFLAGS) TextAnalyzer.b

WordEntry.o: WordEntry.h WordEntry.cpp TextAnalyzer.h TextAnalyzer.cpp BST.h
	$(CC) $(CFLAGS) WordEntry.cpp

clean:
	rm *~ *.o $(EXE) -v
