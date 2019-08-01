#if !defined(CSPRITE_H_INCLUDED)
#define CSPRITE_H_INCLUDED

#include <vector>
#include <algorithm>

#include "viewport.h"
#include "CChaine.h"

using namespace std;
class Csprite;
class Canimation;

typedef void ( *SPRITECALLBACK  )(int tick, Canimation*anim, Csprite*sprite, int spriteposX, int spriteposY);
typedef void ( *COLLISIONCALLBACK) (Canimation *anim, Csprite *sprite1, Csprite *sprite2);

typedef enum {
	DIR_LEFT = 0,
	DIR_RIGHT = 1,
} direction_e;

class Cposition
{
public:
	Cposition();
	Cposition(int x, int y, double dx, double dy, double ddx, double ddy);
	void computeNewPostition(
		int left = 0, int top = 0, int right = 0, int bottom = 0,
		int widthobj = 0, int heightobj = 0,
		bool bounceleft = false,
		bool bouncetop = false,
		bool bounceright = false,
		bool bouncebottom = false);
	double m_x;
	double m_y;
	double m_dx;
	double m_dy;
	double m_ddx;
	double m_ddy;
};

class Csprite
{
public:
	Csprite();
	Csprite(const char *dessin,const char *colormask, COLORS defaultcolor=WHITE, int depth=0, direction_e sens=DIR_RIGHT, char*comment=NULL);
	Csprite(const char **dessin, int nbshape, const char *colormask, COLORS defaultcolor=WHITE, int depth=0, direction_e sens=DIR_RIGHT, char*comment=NULL);
	~Csprite();
	void clear(void);

	void init_sprite(const char **dessin, int nbshape,const char *colormask, COLORS defaultcolor=WHITE, int depth=0, direction_e sens=DIR_RIGHT);
	void init_sprite(const char *dessin              ,const char *colormask, COLORS defaultcolor=WHITE, int depth=0, direction_e sens=DIR_RIGHT);
    void init_sprite(vector<CChaine*> &shape         ,const char *colormask, COLORS defaultcolor=WHITE, int depth=0, direction_e sens=DIR_RIGHT);

	void copy(Csprite *src);
    Csprite& operator = ( const Csprite &source );

	void add_colormask(const char *colormask);


	void set_rand_colormask(void);
	void set_depth(int depth);

	int get_depth(void);
	int get_height(void);
	int get_width(void);

    // renvoi true si en dehors du rectangle de clipping
	bool dessine(int x,int y, int clipxleft, int clipytop, int clipxright, int clipybottom, int tick=0, Canimation*anim=NULL);

	void clear_m_shape(void);
    int  get_nb_shape(void);
  	void add_shape(const char *dessin);
  	void set_shape(unsigned int index, CChaine &dessin);

    // data
private:
	void sprite_defaults(void);
    vector<CChaine*> m_shape;
    int m_height;
    int m_width;
	int m_collX;
	int m_collY;
	bool m_valid;

public:
	Cposition m_pos;
	//CChaine m_shape;
	CChaine m_colormask_initial;
	CChaine m_colormask;
    int m_depth;
    direction_e m_sens;

    int m_underwater_only;
    bool m_bouncetop; 
    bool m_bouncebottom;
    bool m_bounceleft;
    bool m_bounceright;

    int m_life_duration;

	int m_animperiod; // nb de tick entre chaque frame
	int m_lifetick;

  	int m_creationtime;


	COLORS m_defaultcolor;

    int m_nextshape;
    CChaine m_comment;

	int callback_data1, callback_data2, callback_data3; 
    //
    SPRITECALLBACK m_generation; // appelé après dessine() à chaque 'tick'
    SPRITECALLBACK m_deathcallback; // appelé après dessine()
	COLLISIONCALLBACK m_collcallback;

	void setCollisionOffset(int x, int y);
	void setValid(bool v);
	bool isValid(void);
	bool collidesWith(Csprite &c);
	std::pair<int, int> getCenterPoint(void);
	std::pair<int, int> getCollisionPoint(void);
};
  
#endif // defined(CSPRITE_H_INCLUDED)