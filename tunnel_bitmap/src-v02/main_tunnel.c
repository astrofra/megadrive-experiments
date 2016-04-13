#include <genesis.h>
#include "main_tunnel.h"

void main_tunnel(u16 vbl_to_exit){
	u16 vblCount = 0;
	u16 seq = 0;
    
    u16 size_inc = 1;

	u16 pixel_on = _PIXEL_ON;
	u16 line_on = _LINE_ON;
	
	u16 p_cache_index = 0;
	Pixel p_cache[PIXEL_MAX];
	
	u16 l_cache_index = 0;
	Line l_cache[LINE_MAX];
	
	u16 c_cache_index = 0;
	Circle_ c_cache[CIRCLE_MAX];
	
	VDP_setScreenWidth256();
	BMP_init(TRUE, 0, FALSE);
	
	//_____________________________________________________
	//			PIXEL FUNC
	static void pixel_record(s16 x, s16 y, u8 c){
		p_cache[p_cache_index].pt.x = x;
		p_cache[p_cache_index].pt.y = y;
		p_cache[p_cache_index].col = c;
		p_cache_index++;
	}
	#define pixel_draw BMP_setPixels(p_cache, PIXEL_MAX);
	
	//_____________________________________________________
	//			LINE FUNC
	static void line_record(s16 x, s16 y, s16 w, s16 z, u8 c){
		l_cache[l_cache_index].pt1.x = x;
		l_cache[l_cache_index].pt1.y = y;
		l_cache[l_cache_index].pt2.x = w;
		l_cache[l_cache_index].pt2.y = z;
		l_cache[l_cache_index].col = c;
		l_cache_index++;
	}
	
	static inline void _line_draw(){
		u16 i = 0; l_cache_index = 0;
		for(i = 0; i < LINE_MAX; i++){
			BMP_drawLine(&l_cache[l_cache_index]);
			l_cache_index++;
		}
	}
	#define line_draw	_line_draw();
	//_____________________________________________________
	//			CIRCLE FUNC
	static void circle_pixel_record(s16 x, s16 y, s16 size, u16 col, u16 res){
		c_cache[c_cache_index].x = x;
		c_cache[c_cache_index].y = y;
		c_cache[c_cache_index].size = size;
		c_cache[c_cache_index].col = col;
		c_cache[c_cache_index].res = res;
        c_cache[c_cache_index].xOffset = CIRCLE_XOFFSET;
        c_cache[c_cache_index].yOffset = CIRCLE_YOFFSET;
		c_cache_index++;
		u16 j = 1024 / res;
		u16 i;
		for(i = j; i <= 1024; i+=j){
			pixel_record(x + (sinFix32(i) / size), y + (cosFix32(i) / size), 0xFF );
		}
	}
	
	static void circle_line_record(s16 x, s16 y, s16 size, u16 col, u16 res){
		c_cache[c_cache_index].x = x;
		c_cache[c_cache_index].y = y;
		c_cache[c_cache_index].size = size;
		c_cache[c_cache_index].col = col;
		c_cache[c_cache_index].res = res;
        c_cache[c_cache_index].xOffset = CIRCLE_XOFFSET;
        c_cache[c_cache_index].yOffset = CIRCLE_YOFFSET;
		c_cache_index++;
		u16 j = 1024 / res;
		u16 i;
		for(i = j; i <= 1024; i+=j){
			line_record(
							x + (sinFix32(i) / size),
							y + (cosFix32(i) / size),
							x + (sinFix32(i + j) / size),
							y + (cosFix32(i + j) / size),
							0xFF
						);
		}		
	}

	static void circle_pixel_update(s16 x, s16 y){
		u16 k = 0;
		u16 l = 0;
		for(k = 0; k < CIRCLE_MAX; k++){
			u16 j = 1024 / c_cache[k].res;
			u16 i;
			for(i = j; i <= 1024; i+=j){
				p_cache[l].pt.x = x + c_cache[k].x + (sinFix32(i) / c_cache[k].size);
				p_cache[l].pt.y = y + c_cache[k].y + (cosFix32(i) / c_cache[k].size);
				p_cache[l].col = c_cache[k].col;
				l++;
			}
		}
	}
    static inline void circle_line_update(){
        u16 k = 0;
        for(k = 0; k < CIRCLE_MAX; k++){
            u16 j = 1024 / c_cache[k].res;
            u16 i;
            for(i = j; i <= 1024; i+=j){
                line_record(
                            c_cache[k].xOffset + c_cache[k].x +(sinFix32(i) / c_cache[k].size),
                            c_cache[k].yOffset + c_cache[k].y +(cosFix32(i) / c_cache[k].size),
                            c_cache[k].xOffset + c_cache[k].x +(sinFix32(i + j) / c_cache[k].size),
                            c_cache[k].yOffset + c_cache[k].y +(cosFix32(i + j) / c_cache[k].size),
                            c_cache[k].col
                            );
            }			
        }		
    }
/*
    static inline void circle_line_update(){
        u16 k = CIRCLE_MAX;
        for(k = CIRCLE_MAX; k > 0; k--){
            u16 j = 1024 / c_cache[k].res;
            u16 i;
            for(i = j; i <= 1024; i+=j){
                line_record(
                            c_cache[k].xOffset + c_cache[k].x +(sinFix32(i) / c_cache[k].size),
                            c_cache[k].yOffset + c_cache[k].y +(cosFix32(i) / c_cache[k].size),
                            c_cache[k].xOffset + c_cache[k].x +(sinFix32(i + j) / c_cache[k].size),
                            c_cache[k].yOffset + c_cache[k].y +(cosFix32(i + j) / c_cache[k].size),
                            c_cache[k].col
                            );
            }			
        }		
    }
*/

    static inline void circle_size_update(){
        u16 i = 0;
        for(i = 0; i < CIRCLE_MAX; i++){
            c_cache[i].size -= size_inc;
            if(c_cache[i].size <= 0){ c_cache[i].size = 120;  c_cache[i].xOffset = CIRCLE_XOFFSET; c_cache[i].yOffset = CIRCLE_YOFFSET; }
        }
    }
    
    static inline void circle_color_update(){
        u16 i = 0;
        for (i = 0; i < CIRCLE_MAX; i++){
            if (c_cache[i].size >= 80) { c_cache[i].col = 1; }
            else if (c_cache[i].size >= 70 && c_cache[i].size < 80) { c_cache[i].col = 2; }
            else if (c_cache[i].size >= 60 && c_cache[i].size < 70) { c_cache[i].col = 3; }
            else if (c_cache[i].size >= 50 && c_cache[i].size < 60) { c_cache[i].col = 4; }
            else if (c_cache[i].size >= 40 && c_cache[i].size < 50) { c_cache[i].col = 5; }
            else if (c_cache[i].size >= 30 && c_cache[i].size < 40) { c_cache[i].col = 6; }
        }
    }
    
    static inline void circle_move_update(){
        u16 i = 0;
        switch (seq) {
            case 0:
                if(vblCount > 50){ seq++; }
                break;

            case 1:
                for(i = 0; i < CIRCLE_MAX; i++){
                    c_cache[i].xOffset++;
                }
                if(vblCount > 100){ seq++; }
                break;
            case 2:
                for(i = 0; i < CIRCLE_MAX; i++){
                    c_cache[i].xOffset -= 1;
                }
                if(vblCount > 150){ seq++; size_inc = 2; }
                break;
                
            case 3:
                for(i = 0; i < CIRCLE_MAX; i++){
                    c_cache[i].xOffset += 2;
                    c_cache[i].yOffset += 1;
                }
                if(vblCount > 200){ seq++; size_inc = 3;}
                break;

            case 4:
                for(i = 0; i < CIRCLE_MAX; i++){
                    c_cache[i].xOffset -= 3;
                    c_cache[i].yOffset -= 2;
                }
                if(vblCount > 250){ seq++; size_inc = 4; }
                break;

            case 5:
                seq = 0;
                vblCount = 0;
                break;
                
            default:
                break;
        }
    }
    
    static void circle_debug_xy(u16 x, u16 y){
        s16 xc, yc;
        char xcStr[3], ycStr[3];
        u16 i = 0, j = 1;
        for (i = 0; i < CIRCLE_MAX; i++){
            xc = c_cache[i].x;
            yc = c_cache[i].y;
            intToStr(xc, xcStr, 3);
            intToStr(yc, ycStr, 3);
            VDP_drawText(xcStr, x, y+j);
            j++;
            VDP_drawText(ycStr, x, y+j);
            j += 2;
        }
    }
    
    static void circle_debug_size(u16 x, u16 y){
        s16 size;
        char sizeStr[3];
        u16 i = 0, j = 1;
        for (i = 0; i < CIRCLE_MAX; i++){
            size = c_cache[i].size;
            intToStr(size, sizeStr, 3);
            VDP_drawText(sizeStr, x, y+j);
            j += 2;
        }
    }
    
	//_____________________________________________________
	//		PRE LOOP
    #define CIRCLE_X    100
    #define CIRCLE_Y    50
	if(line_on == 1){
		circle_line_record(CIRCLE_X, CIRCLE_Y, 121, 0xFF, CIRCLE_RES);
		circle_line_record(CIRCLE_X, CIRCLE_Y, 101, 0xFF, CIRCLE_RES);
		circle_line_record(CIRCLE_X, CIRCLE_Y,  81, 0xFF, CIRCLE_RES);
		circle_line_record(CIRCLE_X, CIRCLE_Y,  61, 0xFF, CIRCLE_RES);
        circle_line_record(CIRCLE_X, CIRCLE_Y,  41, 0xFF, CIRCLE_RES);
        circle_line_record(CIRCLE_X, CIRCLE_Y,  21, 0xFF, CIRCLE_RES);
	}
	if(pixel_on == 1){
		circle_pixel_record(CIRCLE_X, CIRCLE_Y, 121, 0xFF, CIRCLE_RES);
		circle_pixel_record(CIRCLE_X, CIRCLE_Y, 101, 0xFF, CIRCLE_RES);
		circle_pixel_record(CIRCLE_X, CIRCLE_Y,  81, 0xFF, CIRCLE_RES);
		circle_pixel_record(CIRCLE_X, CIRCLE_Y,  61, 0xFF, CIRCLE_RES);
        circle_pixel_record(CIRCLE_X, CIRCLE_Y,  41, 0xFF, CIRCLE_RES);
        circle_pixel_record(CIRCLE_X, CIRCLE_Y,  21, 0xFF, CIRCLE_RES);
	}
    
	while(1){
		//______________________________________________
		//		PRECA HERE
		p_cache_index = 0;
		l_cache_index = 0;
		c_cache_index = 0;
		
		if(line_on == 1) circle_line_update();
		if (pixel_on == 1) circle_pixel_update(c_cache[0].x, c_cache[0].y);
		//		PRECA END
		//______________________________________________

		BMP_waitFlipComplete();
		BMP_clear();
		BMP_showFPS(1);

        //______________________________________________
		//		DRAW HERE
		if(pixel_on ==1 ) pixel_draw
		if(line_on == 1) line_draw
		//		DRAW END
		//______________________________________________
			
		//______________________________________________
		//		CTRL HERE
        circle_size_update();
        circle_color_update();
        circle_move_update();
        //circle_debug_xy(20, 3);
        //circle_debug_size(20, 3);
        BMP_flip(1);
        vblCount++;
	}
    BMP_end();
}
