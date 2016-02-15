#ifndef PROFILER_H
#define PROFILER_H
#include <genesis.h>
#include <kdebug.h>

#define PROFILER_PROBE_QTY 3

typedef struct profiler profiler;
struct profiler{
	u32 subTickTotal[PROFILER_PROBE_QTY];
	u32 subTickSart[PROFILER_PROBE_QTY];
	u32 subTickEnd[PROFILER_PROBE_QTY];
	u32 vblCurrent;
	u16 id[PROFILER_PROBE_QTY];
	u16 idNext;	
	char *name[PROFILER_PROBE_QTY][10];
};

profiler profilerMake();
u16 profilerAddProbe(profiler *prfl, const char *lib);
void profilerDebug(profiler *prfl, u32 vblFrq);
void profilerStartProbe(profiler *prfl, u16 id);
u32 profilerStopProbe(profiler *prfl, u16 id);
#endif
