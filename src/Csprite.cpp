
#include <windows.h>

#include <iostream>

#include "CChaine.h"
#include "Csprite.h"
#include "utils.h"

Csprite::Csprite()
{
	sprite_defaults();
	init_sprite("","");
}

Csprite::Csprite(const char *dessin,const char *colormask, COLORS defaultcolor, int depth, direction_e sens, char*comment) : m_comment(comment)
{
	sprite_defaults();
	init_sprite(dessin, colormask, defaultcolor, depth, sens);
}

Csprite::Csprite(const char **dessin, int nbshape, const char *colormask, COLORS defaultcolor, int depth, direction_e sens, char*comment) : m_comment(comment)
{
	sprite_defaults();
	init_sprite(dessin[0],colormask, defaultcolor, depth,sens);
    if( nbshape > 1)
    {
		for (int i = 1; i < nbshape; i++) {
			add_shape(dessin[i]);
		}
    }

}

void Csprite::sprite_defaults(void)
{
	m_valid = false;
	m_height = -1;
	m_width = -1;
	m_nextshape = 0;
	m_colormask_initial = NULL;
	m_colormask = NULL;
	m_sens = DIR_RIGHT;
	m_underwater_only = false;
	m_life_duration = -1;
	m_animperiod = -1;
	m_lifetick = 1;
	m_creationtime = 0;
	m_generation = NULL;
	m_deathcallback = NULL;
	m_collcallback = NULL;
	m_bouncetop = false;
	m_bouncebottom = false;
	m_bounceleft = false;
	m_bounceright = false;
	m_collX = 0;
	m_collY = 0;
}

void Csprite::clear(void)
{
    clear_m_shape();
	m_valid = false;
	m_colormask_initial=NULL;
	m_colormask=NULL;
	m_comment=NULL;
}

// Foncteur servant à libérer un pointeur - applicable à n'importe quel type
struct Delete 
{ 
   template <class T> void operator ()(T*& p) const 
   { 
      delete p;
      p = NULL;
   } 
};

Csprite::~Csprite()
{
    /*
    std::for_each(m_shape.begin(), m_shape.end(), Delete() ); 
    m_shape.clear();
    */
    clear();//_m_shape();
}

void Csprite::clear_m_shape(void)
{
     m_height= m_width = -1;

    //supprime le contenu de la liste puis la liste
    for (unsigned int i=0; i<m_shape.size(); i++)
    {
        delete m_shape[i];
        m_shape[i]=NULL;
    }
    m_shape.clear();
}

void Csprite::init_sprite(const char **dessin, int nbshape,const char *colormask, COLORS defaultcolor, int depth, direction_e sens)
{
    clear_m_shape();
    for ( int i=0; i<nbshape; i++)
    {
        add_shape(dessin[i] );
    }

    if (colormask)
	{
		m_colormask_initial = colormask;
		m_colormask         = colormask;
		set_rand_colormask();
	}
	else m_colormask="";

	m_defaultcolor = defaultcolor;
	set_depth(depth);
    m_sens = sens;
}

void Csprite::init_sprite(const char *dessin,const char *colormask, COLORS defaultcolor, int depth, direction_e sens)
{
    init_sprite(&dessin, 1,colormask, defaultcolor, depth, sens);
}

void Csprite::init_sprite(vector<CChaine*> &shape,const char *colormask, COLORS defaultcolor, int depth, direction_e sens)
{
    init_sprite(NULL, 0,colormask, defaultcolor, depth, sens);

    clear_m_shape();
    for (unsigned int i=0; i<shape.size(); i++)
    {
        add_shape(shape[i]->getstr() );
    }
}

void Csprite::add_shape(const char *dessin)
{
    m_height= m_width = -1;

    m_shape.push_back(new CChaine(dessin)); 
}

int  Csprite::get_nb_shape(void)
{
    return(m_shape.size());
}

void Csprite::set_shape(unsigned int index, CChaine &dessin)
{
    m_height= m_width = -1;

    if (index>=0 && index<m_shape.size())
        *m_shape[index] = dessin; 
}

void Csprite::add_colormask(const char *colormask)
{
}

void Csprite::set_depth(int depth)
{
    m_depth    = depth;
}

int Csprite::get_depth(void)
{
    return(m_depth);
}

void Csprite::set_rand_colormask(void)
{
    char colors[] = {'c','C','r','R','y','Y','b','B','g','G','m','M'};
	int index[10];

	for(int i=0; i<10;i++)
		index[i]=randomval(0, NB_ELEMENT(colors)-1 );

	const char *possrc;
    char *posdest;
    possrc=m_colormask_initial.getstr();
    _ASSERT(possrc);
    posdest=m_colormask.acquire();
	while (*possrc)
	{
        if (*possrc=='4' )  // 4 remplacer par W (blanc: les yeux des poissons)
            *posdest = 'W';
        else
		if (*possrc>='1' && *possrc<='9')
			*posdest = colors[index[*possrc-'1']];
		else
			*posdest =*possrc;
		*posdest++;
		*possrc++;
	}
    m_colormask.release();
}

void Csprite::copy(Csprite *src)
{
    init_sprite(src->m_shape, src->m_colormask.getstr(), src->m_defaultcolor, src->m_depth);

    m_generation		= src->m_generation;
    m_deathcallback		= src->m_deathcallback;
	m_collcallback		= src->m_collcallback;

    m_underwater_only	= src->m_underwater_only;
    m_animperiod		= src->m_animperiod;
    m_life_duration		= src->m_life_duration;
    //m_resurection_time = src->m_resurection_time;
    m_sens				= src->m_sens;
    m_comment			= src->m_comment;
    m_lifetick			= src->m_lifetick;
    m_creationtime		= src->m_creationtime;
    m_nextshape			= src->m_nextshape;
	callback_data1		= src->callback_data1;
	callback_data2		= src->callback_data2;
	callback_data3		= src->callback_data3;

    m_bouncetop			= src->m_bouncetop;
    m_bouncebottom		= src->m_bouncebottom;
    m_bounceleft		= src->m_bounceleft;
    m_bounceright		= src->m_bounceright;

	m_collX				= src->m_collX;
	m_collY				= src->m_collY;
	m_valid				= src->m_valid;
}

Csprite& Csprite::operator = ( const Csprite &source )
{
    copy((Csprite *)&source);
    return(*this);
}

int Csprite::get_height(void)
{
    if (m_height>=0) return(m_height);

    // = nb de ligne
    int maxy=0;

    vector <CChaine*>::iterator shapeIt;
    for ( shapeIt = m_shape.begin() ; shapeIt != m_shape.end() ; shapeIt++ )
    {
        int y=1;
        const char *posc=/*m_shape[0].*/(*shapeIt)->getstr();
        while(*posc)
        {
            if (*posc=='\n') y++;
            posc++;
        }
        maxy=max(y,maxy);
    }
    m_height= maxy;
    return(maxy);
}

int Csprite::get_width(void)
{
    if(m_width>=0) return(m_width);

    // = plus grande largeur de ligne
    int maxx=0;

    vector <CChaine*>::iterator shapeIt;
    for ( shapeIt = m_shape.begin() ; shapeIt != m_shape.end() ; shapeIt++ )
    {
        int x=0;
        const char *posc=/*m_shape[0].*/(*shapeIt)->getstr();
        while(*posc)
        {
            // 
            if (*posc=='\n') 
            { 
                maxx=max(maxx,x);
                x=0;
            }
            else
                x++;
            posc++;
        }
		maxx=max(maxx,x); // cas 1 seul ligne sans \n final
    }
    m_width =maxx;
    return(maxx);
}

bool isClipping(int x,int y, int clipxleft, int clipytop, int clipxright, int clipybottom)
{
    if ( y<clipytop || y>clipybottom ) return(true);
    if ( x<clipxleft || x>clipxright) return(true);

    return(false);
}
#define CAR_TRANSPARENT '$'  // caratère non dessiné, il faut preendre un caracère inutilisé pour ledessin et compatible avec les sequ d'echapement (pb avec ? et \)

// renvoi true si en dehors du rectangle de clipping
bool Csprite::dessine(int posx, int posy, int clipxleft, int clipytop, int clipxright, int clipybottom, int tick, Canimation*anim)
{
    bool ret=true;
    bool clipping;
    int x,y;
    const char *posc;	
    const char *poscolor;	


	// shape suivant ?
    int nbs=m_shape.size();
    if(nbs==0) return(ret); // rien à dessiner
	if(m_comment.getstr()==NULL)
	{
		int x=0;
	}
    if (m_comment.getstr() && strcmp(m_comment.getstr(),"seaweed")==0 )
    {
        int i=0;
    }

	if (m_nextshape>=nbs  )
		m_nextshape = 0;

    posc    =m_shape[m_nextshape]->getstr();
    poscolor=m_colormask.getstr();

    x=posx;
    y=posy;
    /*
    clipping = isClipping(x,y, clipxleft, clipytop, clipxright, clipybottom);
    if (!clipping)
    gotoxy(x,y);
    */
    while(*posc)
    {
        // 
        if (*posc=='\n')
        {
            y++;
            x=posx;
            //clipping = isClipping(x,y, clipxleft, clipytop, clipxright, clipybottom);
        }
        else
        {
            //	my @colors = ('c','C','r','R','y','Y','b','B','g','G','m','M');


  //  DARKGRAY,       /* light colors */

            COLORS color;
            switch(*poscolor)
            {
            case 'c': color=CYAN; break;
            case 'r': color=RED; break;
            case 'b': color=BLUE; break;
            case 'g': color=GREEN; break;
            case 'm': color=MAGENTA; break;
            case 'y': color=BROWN; break;
            case 'w': color=LIGHTGRAY; break;

            case 'C': color=LIGHTCYAN; break;
            case 'R': color=LIGHTRED; break;
            case 'B': color=LIGHTBLUE; break;
            case 'G': color=LIGHTGREEN; break;
            case 'M': color=LIGHTMAGENTA; break;
            case 'Y': color=YELLOW; break;
            case 'W': color=WHITE; break;

            default: // ' ',  '\n'
                color=m_defaultcolor;
            }

            clipping = isClipping(x,y, clipxleft, clipytop, clipxright, clipybottom);
            if ( !clipping && *posc != CAR_TRANSPARENT )
            {
                ret=false;
                setviewportcursor(x,y);
                setviewportcursorcolor(color);
                outputviewport(*posc);
            }
            x++;


            //			_cprintf("%c",*posc);
        }

        //si fin de ligne de caractere et pas de couleur, va en fin de ligne de couleur
        if (*posc=='\n' && *poscolor!='\n')
        {
            while (*poscolor && *poscolor!='\n')
                poscolor++;
        }

        //si fin de ligne de couleur et pas de caractère, attent la fin de ligne de caratère
        if (*poscolor=='\n' && *posc=='\n')
            poscolor++;
        else if (*poscolor && *poscolor!='\n')
            poscolor++;

        posc++;
    }

    if(m_generation)
        m_generation(tick,anim, this,posx, posy);

    if ( m_lifetick % m_animperiod == 0 || m_animperiod==-1)
		m_nextshape++;

    return(ret);
}

void Csprite::setCollisionOffset(int x, int y)
{
	//x offset from current position
	m_collX = x;
	//y offset from current position
	m_collY = y;
}

void Csprite::setValid(bool v)
{
	m_valid = v;
}

bool Csprite::isValid(void)
{
	return m_valid;
}

bool Csprite::collidesWith(Csprite &c)
{
	std::pair<int, int> cp = getCollisionPoint();
	if ((cp.first > c.m_pos.m_x)
		&& (cp.first < (c.m_pos.m_x + c.get_width()))
		&& (cp.second > c.m_pos.m_y)
		&& (cp.second < (c.m_pos.m_y + c.get_height()))
		) {
		return true;
	}
	return false;
}

std::pair<int, int> Csprite::getCenterPoint(void)
{
	return std::pair<int, int>(m_pos.m_x + get_width() / 2, m_pos.m_y + get_height() / 2);
}

std::pair<int, int> Csprite::getCollisionPoint(void)
{
	int x, y;

	x = (m_sens == DIR_RIGHT) ? m_pos.m_x + m_width + m_collX : m_pos.m_x - m_collX ;
	y = m_pos.m_y + m_collY;

	return std::pair<int, int>(x, y);
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

Cposition::Cposition()
{
	m_x = m_y = 0.0;
	m_dx = m_dy = 0.0;
	m_ddx = m_ddy = 0.0;
}

Cposition::Cposition(int x, int y, double dx, double dy, double ddx, double ddy)
{
	m_x = (double)x;
	m_y = (double)y;
	m_dx = dx;
	m_dy = dy;
	m_ddx = ddx;
	m_ddy = ddy;
}

void Cposition::computeNewPostition(
	int left, int top, int right, int bottom,
	int widthobj, int heightobj,

	bool m_bounceleft,
	bool m_bouncetop,
	bool m_bounceright,
	bool m_bouncebottom)
{
	m_x += m_dx;
	if (m_dx>0 && (m_dx + m_ddx) <= 0) m_ddx = -m_ddx; // on veut pas de rebrousement=>on inverse l'acceleration
	if (m_dx<0 && (m_dx + m_ddx) >= 0) m_ddx = -m_ddx; // on veut pas de rebrousement=>on inverse l'acceleration
	m_dx += m_ddx;

	if (m_bouncetop)
	{
		int x = 0;
	}
	if (m_bouncetop && m_y + m_dy < top && m_dy<0)
	{
		m_dy = -m_dy;
	}
	else if (m_bouncebottom && m_y + heightobj - 1 + m_dy > bottom && m_dy>0)
	{
		m_dy = -m_dy;
	}
	m_y += m_dy;


	m_dy += m_ddy;
}


