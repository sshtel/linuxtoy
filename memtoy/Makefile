CXX=arm-none-linux-gnueabi-g++
CXX=g++


OUTPUT_DIR=$(PWD)/../bin
OUTPUT=$(OUTPUT_DIR)/memtoy

SRCS = main.cpp meminfo.cpp proc_status.cpp

all:
	$(CXX) $(SRCS)  -o $(OUTPUT) 

clean:
	rm -rf $(OUTPUT)
