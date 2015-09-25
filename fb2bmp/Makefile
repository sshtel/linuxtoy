CC=arm-hisiv200-linux-gnueabi-gcc
#CC=gcc

TARGET=arm-linux

ROOTDIR = $(PWD)
OUTPUT_DIR=$(PWD)/../bin
OUTPUT=$(OUTPUT_DIR)/fb2bmp

LIBDIR=$(PWD)/../lib
LIBBMP=libbmp-0.1.2

SRCS = raw2bmp.c bmpfile.o
LDFLAGS = -lm

all: libbmp_unzip libbmp_patch libbmp_build
	$(CC) $(SRCS) $(LDFLAGS) -o $(OUTPUT) 

app:
	$(CC) $(SRCS)  -o $(OUTPUT) 

libbmp_unzip:
	tar -zxvf $(LIBDIR)/$(LIBBMP).tar.gz

libbmp_build: libbmp_unzip
	cd $(LIBBMP) && ./configure --target=$(TARGET) --host=$(TARGET) CC=$(CC)
	cd $(LIBBMP) && make
	cd $(LIBBMP)/src && cp bmpfile.o $(ROOTDIR)

libbmp_patch:
	cd $(LIBBMP)/src && patch -p0 < $(ROOTDIR)/patches/patch_bmpfile.c

clean:
	rm -rf $(OUTPUT)
