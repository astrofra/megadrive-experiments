#include <genesis.h>
int main(){
VDP_setScreenWidth256();
VDP_setPalette(0, palette_green);
BMP_init(TRUE,0,FALSE);
while(1){
BMP_clear();
BMP_setPixel(10,10,255);
BMP_setPixel(20,10,255);
BMP_setPixel(30,10,255);
Line l;
Vect2D_s16 start, end;
start.x = 50;
start.y = 50;
end.x = 100;
end.y = 100;
l.pt1 = start;
l.pt2 = end;
l.col = 0xFF;
BMP_drawLine(&l);
BMP_flip(1);
BMP_waitFlipComplete();
}
}
