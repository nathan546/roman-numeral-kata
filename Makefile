CC                 :=  gcc
CFLAGS             := -Isrc/include/ -c -O0
LFLAGS             := 
PFLAGS             := -lcheck -lm -lrt -lpthread -lsubunit
OUTPUTFOLDER       := build
SRC_DIR            := src tests
SOURCES            := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJECTS_TO_COMPILE := $(SOURCES:.c=.o)
OBJECTS_COMPILED   := $(addprefix $(OUTPUTFOLDER)/, $(OBJECTS_TO_COMPILE))
EXECUTABLE         := romanNumeralCalculator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_TO_COMPILE)
	$(CC) $(LFLAGS) $(OBJECTS_COMPILED) $(PFLAGS) -o $(OUTPUTFOLDER)/$@

.c.o:
	$(CC) $(CFLAGS) $< -o $(OUTPUTFOLDER)/$@

clean:
	$(RM) -f $(OBJECTS_COMPILED) $(OUTPUTFOLDER)/$(EXECUTABLE)
