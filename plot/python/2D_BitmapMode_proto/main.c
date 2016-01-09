#include <genesis.h>
int main(){
   VDP_setScreenWidth256();
   VDP_setPalette(0, palette_green);
    BMP_setPixel(10,10,255);
    BMP_setPixel(20,10,255);
    BMP_setPixel(30,10,255);
