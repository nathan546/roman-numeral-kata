
OUTPUT_DIR         := build
STORY_DIR          := stories
SRC_DIR            := src tests
STORY_FILES        := $(foreach storydir,$(STORY_DIR),$(wildcard $(storydir)/*.equations))
STORY_PATHS        := $(foreach storyfile,$(STORY_FILES), ../$(storyfile))
SOURCES            := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJECTS_TO_COMPILE := $(SOURCES:.c=.o)
OBJECTS_COMPILED   := $(addprefix $(OUTPUT_DIR)/, $(OBJECTS_TO_COMPILE))
INCLUDE            := $(foreach sdir,$(SRC_DIR),-I$(sdir)/include)
CC                 :=  gcc
CFLAGS             := $(INCLUDE) -c -O0
LFLAGS             := 
PFLAGS             := -lcheck -lm -lrt -lpthread -lsubunit
EXECUTABLE         := romanNumeralCalculator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_TO_COMPILE)
	$(CC) $(LFLAGS) $(OBJECTS_COMPILED) $(PFLAGS) -o $(OUTPUT_DIR)/$@
	rm -f $(OUTPUT_DIR)/*.equations
	ln -s $(STORY_PATHS) $(OUTPUT_DIR)

.c.o:
	$(CC) $(CFLAGS) $< -o $(OUTPUT_DIR)/$@

clean:
	rm -f $(OBJECTS_COMPILED) $(OUTPUT_DIR)/$(EXECUTABLE) $(OUTPUT_DIR)/*.equations
