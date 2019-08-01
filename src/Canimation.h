#if !defined(CANIMATION_H_INCLUDED)
#define CANIMATION_H_INCLUDED

#include "Csprite.h"

#define MAX_ELEMENT 200
class Canimation
{
public:
    Canimation();
    ~Canimation();

    int m_nb_shape;
    Csprite   m_sprite[MAX_ELEMENT];
    int depth_index[MAX_ELEMENT]; // index des shape , classé par profondeur de champ croissant
//    SPRITECALLBACK m_timecallback[MAX_ELEMENT];

    int add_sprite(Csprite &s, int x, int y, double dx, double dy, double ddx, double ddy); // return index
       // ,SPRITECALLBACK animCallback); // return index
    void del_sprite(int index); // index, returned by add_sprite();
	void del_sprite(Csprite *spr);
    void create_depth_index(void);

    void move_sprite(void);
    void timestep(void);
    void drawscene(void);
    void clear(void); // efface tout

	void detect_collisions(void);

    int width() {return xSize;};
    int height(){return ySize;};
//private:
    int xSize, ySize;
    int waterlimit;

    int m_timetick;
    bool spriteListChanged;
};

extern Csprite Splat;

#endif // defined(CANIMATION_H_INCLUDED)