INCLUDES := $(shell pkg-config --cflags opencv) 
LIBS := $(shell pkg-config --libs opencv) 
CFLAGS += $(CLI_INCLUDES) $(SRV_INCLUDES)

OBJ := \
       functions.o	\
       main.o

all: main 

main: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

clean:
	$(RM) $(CLI_OBJ) $(SRV_OBJ) $(MTN_OBJ) main
