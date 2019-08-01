
#if !defined(CANIMATION_H_INCLUDED)
#define CANIMATION_H_INCLUDED

#include "Csprite.h"

class Cposition
{
public:
    Cposition();
    Cposition(int x, int y, double dx, double dy, double ddx, double ddy);
    void computeNewPostition(
        int left=0, int top=0, int right=0,int bottom=0,
        int widthobj=0,int heightobj=0,
        bool bounceleft=false,
        bool bouncetop=false,
        bool bounceright=false, 
        bool bouncebottom=false);
    double m_x;
    double m_y;
    double m_dx;
    double m_dy;
    double m_ddx;
    double m_ddy;
};


#define MAX_ELEMENT 200
class Canimation
{
public:
    Canimation();
    ~Canimation();

    int m_nb_shape;
    bool      used[MAX_ELEMENT];
    Csprite   m_sprite[MAX_ELEMENT];
    Cposition m_pos[MAX_ELEMENT];
    int depth_index[MAX_ELEMENT]; // index des shape , classé par profondeur de champ croissant
//    SPRITECALLBACK m_timecallback[MAX_ELEMENT];


    int add_sprite(Csprite &s, int x, int y, double dx, double dy, double ddx, double ddy); // return index
       // ,SPRITECALLBACK animCallback); // return index
    void del_sprite(int index); // index, returned by add_sprite();
    void create_depth_index(void);

    void move_sprite(void);
    void timestep(void);
    void drawscene(void);
    void clear(void); // efface tout

    int width() {return xSize;};
    int height(){return ySize;};
//private:
    int xSize, ySize;
    int waterlimit;

    int m_timetick;
    bool spriteListChanged;
};

#endif // defined(CANIMATION_H_INCLUDED)