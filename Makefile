CODEDIRS=. ./radix
INCDIRS=. ./radix

SOURCE := $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.cpp))
EXCLUDE := ./main.cpp
LIBS := $(filter-out $(EXCLUDE), $(SOURCE))
OBJS	= $(patsubst %.cpp,%.o,$(LIBS))
DEPFILES = $(patsubst %.cpp,%.d,$(SOURCE))

OUT	= main.exe
CC	 = g++
DEPFLAGS= $(foreach D, $(INCDIRS), -I$(D)) -MP -MD
FLAGS	 = -O0 -g -Wall -std=c++17
OBJFLAGS = -c -o

all: $(OUT)

main.exe: main.cpp $(OBJS)
	$(CC) $^ -g -o $@

%.o: %.cpp
	$(CC) $(FLAGS) $(DEPFLAGS) $(OBJFLAGS) $@ $<

cleanAll: clean cleanBin cleanTxt cleanCsv

clean:
	rm -f $(OBJS) $(DEPFILES) $(OUT)

cleanBin:
	rm -f *.bin

cleanTxt:
	rm -f *.txt

cleanCsv:
	rm -f *.csv

wcleanAll: wclean wcleanBin wcleanTxt wcleanCsv

wclean:
	del /Q /S $(notdir $(OBJS)) $(notdir $(DEPFILES)) $(notdir $(OUT))

wcleanBin:
	del /Q *.bin

wcleanTxt:
	del /Q *.txt

wcleanCsv:
	del /Q *.csv