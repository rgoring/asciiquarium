

#if !defined(ASCIIANIM_H_INCLUDED)
#define ASCIIANIM_H_INCLUDED

#include "ChronoPrecis.h" 
#include "Canimation.h"
#include <vector>


//#define FAST_ANIM

#ifdef FAST_ANIM
#define RANDOBJ_MIN_TICK 1000
#define RANDOBJ_MAX_TICK 1001
#define RANDOBJ_MIN_INIT 1000
#define RANDOBJ_MAX_INIT 1001
#else
#define RANDOBJ_MIN_TICK 15000
#define RANDOBJ_MAX_TICK 45000
#define RANDOBJ_MIN_INIT 5000
#define RANDOBJ_MAX_INIT 2000
#endif

typedef void(*ADD_RANDOM_OBJ)(Canimation *anim, int posy_waterline);

typedef struct {
	ADD_RANDOM_OBJ func;
	int weight;
	bool needsWater;
} RandObj_t;


class Caquarium
{
public:
    Caquarium();
    // si densite<0 on utilise nbfish_desired sinon on utilise densite
    // densite = densité 'linéique' !
    void init_scene(HWND hwnd, BOOL parentBackgroud /*if possible*/, int anim_period, int nbfish_desired, int sansEau, double densite, bool favoriseCredits=false);
    void close_scene(void);
    int drawnext_scene(void);// renvoi 1 si il faut arrêter

    Canimation m_anim;
    int m_xSize, m_ySize;
    int m_dispb, m_currb;

    double tmoy;
    int m_anim_period;
    Chrono chrono;

    int m_nbfish;
private:
    int m_initok;
    bool m_favoriseCredits;
	std::vector<RandObj_t> m_objList;
	int m_randTotWeight;
} ;

#endif // defined(ASCIIANIM_H_INCLUDED)
