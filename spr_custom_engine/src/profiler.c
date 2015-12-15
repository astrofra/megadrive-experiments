#include <genesis.h>
#include "profiler.h"

profiler profilerMake(){
	profiler r;
	u16 i = 0;
	r.idNext = 0;
	r.vblCurrent = 0;
	for (i = 0; i < PROFILER_PROBE_QTY; i++){
		r.id[i] = 0;
		r.subTickSart[i] = 0;
		r.subTickEnd[i] = 0;
		strcpy((char*)r.name[i],(const char*) "");		
	}
	return r;
}

void profilerDebug(profiler *prfl, u32 vblFrq){
	prfl->vblCurrent++;
	if (prfl->vblCurrent % vblFrq == 0){
		KDebug_Alert("Profiler at (VBL)");
		KDebug_AlertNumber(prfl->vblCurrent);
		KDebug_Alert(" ");

		u16 i = 0;
		for (i = 0; i < PROFILER_PROBE_QTY; i++){
			if (prfl->id[i] != 0){
				KDebug_Alert("probe name");
				KDebug_Alert((char*)prfl->name[i]);
				KDebug_Alert(" ");
				KDebug_Alert("id");
				KDebug_AlertNumber((char*)prfl->id[i]);
				KDebug_Alert(" ");
				KDebug_Alert("Average time subTick");
				KDebug_AlertNumber((char*) (prfl->subTickTotal[i] / prfl->vblCurrent) );
				KDebug_Alert(" ");
			}
		}
		KDebug_Alert("------------------------------------");
		KDebug_Alert(" ");
		
	}
}
u16 profilerAddProbe(profiler *prfl, const char *lib){
	if (prfl->idNext >= PROFILER_PROBE_QTY){
		KDebug_Alert(" ");
		KDebug_Alert("ADD MORE QTY PROBE SLOT IN DEFINITION");
		KDebug_Alert(lib);
		KDebug_Alert("FAILED");
		KDebug_Alert(" ");
		KDebug_Alert("------------------------------------");
		KDebug_Alert(" ");
		return 0;
	}
	else{
		prfl->id[prfl->idNext] = prfl->idNext + 1;
		strcpy((char*)prfl->name[prfl->idNext], (const char*)lib);
		prfl->idNext++;
		return prfl->idNext - 1;
	}
}

void profilerStartProbe(profiler *prfl, u16 id){
	prfl->subTickSart[id] = getSubTick();
}

u32 profilerStopProbe(profiler *prfl, u16 id){
	u32 diffSubTick = getSubTick() - prfl->subTickSart[id];
	prfl->subTickTotal[id] += diffSubTick;
	return diffSubTick;
}
