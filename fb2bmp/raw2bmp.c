#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpfile.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

typedef union {
    int pixel;
    unsigned char buf[4];
} PixToBuf;

void getBmpFromFrameBuffer(char *device, char *outfile){
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open(device, O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    int width = vinfo.xres;
    int height = vinfo.yres;
    int depth = vinfo.bits_per_pixel;
    int bytePerPixel = depth / 8;
    int widthStep = width * bytePerPixel;
    printf("%dx%d, %dbpp\n", width, height, depth);
    

    // Figure out the size of the screen in bytes
    screensize = width * height * bytePerPixel;
    unsigned char buffer[screensize];

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
            fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    
    memcpy(buffer, fbp, screensize);
    munmap(fbp, screensize);
    close(fbfd);
    
    
    bmpfile_t *bmp;
    if ((bmp = bmp_create(width, height, depth)) == NULL) {
        printf("Invalid depth value: '%d'. Try 1, 4, 8, 16, 24, or 32.\n", depth);
        exit(EXIT_FAILURE);
    }


    PixToBuf p2b;
    int iPixel;
    int i, j;
    unsigned char red, green, blue; // 8-bits each
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j ) {
            int index = (widthStep * j) + (i * bytePerPixel);
            memcpy(&iPixel, &buffer[index], 4);
//            iPixel = p2b.pixel;
            red = (unsigned char)((iPixel & 0xFF0000) >> 16);  // 8
            green = (unsigned char )((iPixel & 0x00FF00) >> 8); // 8
            blue = (unsigned char )(iPixel & 0x0000FF);         // 8
            /*
            red = (unsigned char)buffer[index + 1];
            green = (unsigned char)buffer[index + 2];
            blue = (unsigned char)buffer[index + 3];
            */

            rgb_pixel_t bpixel = {blue, green, red, 0};
            bmp_set_pixel(bmp, i, j, bpixel);
        }
    }

    bmp_save(bmp, outfile);
    bmp_destroy(bmp);



}

int main(int argc, char **argv)
{
    char* deviceName;
    char* outfile;
    //rgb_pixel_t bpixel = {128, 64, 0, 0};
    //make && ./raw565tobmp fb.rgb565 720 480 32 fb.bmp && gnome-open fb.bmp

    if (argc < 3) {
        printf("Usage: %s { device(/dev/fb0) } { outfile(out.bmp) }\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    deviceName = argv[1];
    outfile = argv[2];

    getBmpFromFrameBuffer(deviceName, outfile);

    return 0;
}
