#include <genesis.h>
int main(){
VDP_setScreenWidth256();
BMP_init(TRUE,0,FALSE);
u16 vblCount = 0;
u16 circleSize = 100;
void circle(u16 x, u16 y, u16 size, u16 plotRes){
if(size == 0) size = 1;
u16 i = 0; for(i = 0; i < 1024; i += plotRes){
BMP_setPixel(x + (sinFix32(i) / size), (y + cosFix32(i) / size), 0xFF);
}
}
while(1){
BMP_clear();
BMP_showFPS(1);
circle(100, 100, circleSize, 30);
circle(100, 100, circleSize - 40, 30);
circle(100, 100, circleSize - 60, 30);
circleSize--;
vblCount++;
BMP_flip(1);
BMP_waitFlipComplete();
}
}
