

#if !defined(ASCIIANIM_H_INCLUDED)
#define ASCIIANIM_H_INCLUDED

#include "ChronoPrecis.h" 
#include "Canimation.h"

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
} ;

#endif // defined(ASCIIANIM_H_INCLUDED)
