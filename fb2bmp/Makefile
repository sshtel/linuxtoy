CC=arm-none-linux-gnueabi-gcc
CC=gcc

TARGET=arm-linux


OUTPUT_DIR=$(PWD)/../bin
OUTPUT=$(OUTPUT_DIR)/fb2bmp

LIBDIR=$(PWD)/../lib
LIBBMP=libbmp-0.1.2

SRCS = raw2bmp.c bmpfile.o -lm

all: libbmp_build
	$(CC) $(SRCS)  -o $(OUTPUT) 

libbmp_unzip:
	tar -zxvf $(LIBDIR)/$(LIBBMP).tar.gz

libbmp_build: libbmp_unzip
	cd $(LIBBMP) && ./configure --target=$(TARGET) --host=$(TARGET) CC=$(CC)
	cd $(LIBBMP) && make
clean:
	rm -rf $(OUTPUT)
