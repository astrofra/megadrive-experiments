#include <genesis.h>
int main(){
VDP_setScreenWidth256();
BMP_init(TRUE,0,FALSE);
u16 vblCount = 0;
fix16 plotX = 0;
fix16 plotY = 0;
u16 circleRes = 1;
while(1){
BMP_clear();
u16 i = 0; for (i = 0; i < 1024; i += circleRes){
BMP_setPixel(100 + sinFix16(i), 100 + cosFix16(i), 0xFF);
}
circleRes+=1;
if (circleRes > 100){ circleRes = 1;}
vblCount+=1;
BMP_flip(1);
BMP_waitFlipComplete();
}
}
