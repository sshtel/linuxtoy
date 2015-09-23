CC=arm-none-linux-gnueabi-gcc
CC=gcc


OUTPUT_DIR=$(PWD)/../bin
OUTPUT=$(OUTPUT_DIR)/fb2bmp


SRCS = raw2bmp.c bmpfile.o -lm

all:
	$(CC) $(SRCS)  -o $(OUTPUT) 

clean:
	rm -rf $(OUTPUT)
