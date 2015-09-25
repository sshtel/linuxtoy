--- bmpfile.c	2015-09-25 11:02:36.897796128 +0900
+++ bmpfile_new.c	2015-09-25 11:02:30.241796362 +0900
@@ -420,8 +420,10 @@
 rgb_pixel_t
 bmp_get_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y)
 {
+    rgb_pixel_t dummy;
+    memset(&dummy, 0, sizeof(dummy));
   if ((x >= bmp->dib.width) || (y >= bmp->dib.height))
-    return NULL;
+    return dummy;
 
   return bmp->pixels[x][y];
 }
