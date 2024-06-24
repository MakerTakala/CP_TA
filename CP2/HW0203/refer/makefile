TARGET=hw0203
SRCS=./srcs
HEADERS=$(shell find $(SRCS) -name "*.h")
OBJECTS=$(addprefix objs/, $(notdir $(HEADERS:.h=.o)))
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJECTS) $(TARGET).c
	$(CC) $(OBJECTS) $(TARGET).c -I$(SRCS) -o $@

$(OBJECTS): $(HEADERS) $(@:objs/%.o=$(SRCS)/%.c)
	$(CC) -c $(@:objs/%.o=$(SRCS)/%.c) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
