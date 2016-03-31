#include <genesis.h>
#define CIRCLE_MAX	5	//5
#define CIRCLE_RES	9	//9
#define PIXEL_MAX	45	//CIRCLE_MAX x CIRCLE_RES 45
#define LINE_MAX	45	//CIRCLE_MAX x CIRCLE_RES 45

#define _PIXEL_ON	0
#define _LINE_ON	1

static void tunnel();

int main(){
	tunnel();
	return 0;
}

static void tunnel(){
	u16 vblCount = 0;
	u16 seq = 0;

	u16 pixel_on = _PIXEL_ON;
	u16 line_on = _LINE_ON;
	
	typedef struct Circle_ Circle_;
	struct Circle_{
		s16 x;
		s16 y;
		s16 size;
		u16 col;
		u16	res;
	};
	

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
	static inline void pixel_record(s16 x, s16 y, u8 c){
		p_cache[p_cache_index].pt.x = x;
		p_cache[p_cache_index].pt.y = y;
		p_cache[p_cache_index].col = c;
		p_cache_index++;
	}
	#define pixel_draw BMP_setPixels(p_cache, PIXEL_MAX);
	
	//_____________________________________________________
	//			LINE FUNC
	static inline void line_record(s16 x, s16 y, s16 w, s16 z, u8 c){
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
	static inline void circle_pixel_record(s16 x, s16 y, s16 size, u16 col, u16 res){
		c_cache[c_cache_index].x = x;
		c_cache[c_cache_index].y = y;
		c_cache[c_cache_index].size = size;
		c_cache[c_cache_index].col = col;
		c_cache[c_cache_index].res = res;
		c_cache_index++;
		u16 j = 1024 / res;
		u16 i;
		for(i = j; i <= 1024; i+=j){
			pixel_record(x + (sinFix32(i) / size), y + (cosFix32(i) / size), 0xFF );
		}
	}
	
	static inline void circle_line_record(s16 x, s16 y, s16 size, u16 col, u16 res){
		c_cache[c_cache_index].x = x;
		c_cache[c_cache_index].y = y;
		c_cache[c_cache_index].size = size;
		c_cache[c_cache_index].col = col;
		c_cache[c_cache_index].res = res;
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

	static inline void circle_pixel_update(){
		u16 k = 0;
		u16 l = 0;
		for(k = 0; k < CIRCLE_MAX; k++){
			u16 j = 1024 / c_cache[k].res;
			u16 i;
			for(i = j; i <= 1024; i+=j){
				p_cache[l].pt.x = c_cache[k].x + (sinFix32(i) / c_cache[k].size);
				p_cache[l].pt.y = c_cache[k].y + (cosFix32(i) / c_cache[k].size);
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
							c_cache[k].x + (sinFix32(i) / c_cache[k].size),
							c_cache[k].y + (cosFix32(i) / c_cache[k].size),
							c_cache[k].x + (sinFix32(i + j) / c_cache[k].size),
							c_cache[k].y + (cosFix32(i + j) / c_cache[k].size),
							0xFF
							);
			}
			
		}
		
	}
	//_____________________________________________________
	//		PRE LOOP
	if(line_on == 1){
		circle_line_record(100, 100, 100, 0xFF, CIRCLE_RES);
		circle_line_record(100, 100,  80, 0xFF, CIRCLE_RES);
		circle_line_record(100, 100,  60, 0xFF, CIRCLE_RES);
		circle_line_record(100, 100,  40, 0xFF, CIRCLE_RES);
		circle_line_record(100, 100,  20, 0xFF, CIRCLE_RES);
	}
	if(pixel_on == 1){
		circle_pixel_record(100, 100, 100, 0xFF, CIRCLE_RES);
		circle_pixel_record(100, 100,  80, 0xFF, CIRCLE_RES);
		circle_pixel_record(100, 100,  60, 0xFF, CIRCLE_RES);
		circle_pixel_record(100, 100,  40, 0xFF, CIRCLE_RES);
		circle_pixel_record(100, 100,  20, 0xFF, CIRCLE_RES);
	}
	
	while(1){
		//______________________________________________
		//		PRECA HERE
		p_cache_index = 0;
		l_cache_index = 0;
		c_cache_index = 0;
		
		if(line_on == 1) circle_line_update();
		if(pixel_on == 1) circle_pixel_update();
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
		u16 i = 0;
		for(i = 0; i < CIRCLE_MAX; i++){
			c_cache[i].size--;
			if(c_cache[i].size == 0){ c_cache[i].size = 100; }
		}
		
		BMP_flip(1);

	}
	

}
