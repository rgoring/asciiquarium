#include <windows.h>

#include "utils.h"
#include "Canimation.h"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
Canimation::Canimation()
{
    spriteListChanged=false;
    waterlimit = 0;
    m_timetick=1;
    m_nb_shape=0;
}

Canimation::~Canimation()
{
    clear();
}

 // efface tout
void Canimation::clear(void)
{
    for (int i=0; i<MAX_ELEMENT; i++)
    {
        if ( m_sprite[i].isValid() ) 
			del_sprite(i);
    }
    waterlimit = 0;
    m_timetick=1;
}

typedef struct
{
    int depth;
    int generation;
    int index;
} TABDEPTH;

// fct de comparaison
int __cdecl compareElementDecroissant (const void *elem1, const void *elem2 )
{
    TABDEPTH *e1= (TABDEPTH *)elem1;
    TABDEPTH *e2= (TABDEPTH *)elem2;

    if ( e1->depth > e2->depth )
        return(-1);
    if ( e1->depth < e2->depth )
        return(+1);
    // si meme profondeur, on compare la génération : la plus vieille au fond
    if ( e1->generation > e2->generation )
        return(+1);
    if ( e1->generation < e2->generation )
        return(-1);
    // si meme profondeur, mem generation, utilise l'indice du tableau
    // comme ca 2 dessin de meme profondeur seront toujours dessiné de la meme manière l'un par rapport à l'autre
    if ( e1->index > e2->index )
        return(-1);
    if ( e1->index < e2->index )
        return(+1);
    return(0);
}
void Canimation::create_depth_index(void)
{
    // recréé l'index des shape classé par profondeur de champs (le ploin loin en premier)
    TABDEPTH t[MAX_ELEMENT];
    int n=0;
    for (int i=0; i<MAX_ELEMENT; i++)
    {
        if (m_sprite[i].isValid())
        {
            t[n].depth=m_sprite[i].get_depth();
            t[n].generation = m_sprite[i].m_creationtime;
            t[n].index=i;
            n++;
        }
    }
    qsort(t , n, sizeof(TABDEPTH), compareElementDecroissant );
    for (int i=0; i<n; i++)
        depth_index[i] = t[i].index;
    for (int i=n; i<MAX_ELEMENT; i++)
        depth_index[i] = -1; // not used
    
    spriteListChanged=false;

    _ASSERT(n==m_nb_shape);
}

int Canimation::add_sprite(Csprite &s, int x, int y, double dx, double dy, double ddx, double ddy/*, SPRITECALLBACK animCallback */)
{
    int id=-1;
    // cherche une place dans used
    for (int i=0; i<MAX_ELEMENT; i++)
    {
        if ( !m_sprite[i].isValid()) {id=i;break;}
    }
    if (id==-1)
        return(id);

    m_nb_shape++;
    m_sprite[id] = s;
	m_sprite[id].setValid(true);
    m_sprite[id].m_lifetick = 1; 
    m_sprite[id].m_creationtime = m_timetick;
    if ( m_sprite[id].m_sens == DIR_LEFT && dx>0) dx = -dx;
    if ( m_sprite[id].m_sens == DIR_RIGHT && dx<0) dx = -dx;
    m_sprite[id].m_pos = Cposition(x,y, dx, dy, ddx, ddy);
    //m_timecallback[id] = animCallback;

    spriteListChanged=true;

    return(id);
}

void  Canimation::del_sprite(int index) // index, returned by add_sprite();
{
	m_sprite[index].setValid(false);
	m_sprite[index].clear();
    m_nb_shape--;
    _ASSERT(m_nb_shape>=0);

    spriteListChanged=true;
}

void Canimation::del_sprite(Csprite *spr)
{
	for (int i = 0; i < MAX_ELEMENT; i++) {
		if (m_sprite[i].isValid() && &m_sprite[i] == spr) {
			del_sprite(i);
			break;
		}
	}
}

void Canimation::timestep(void)
{
    m_timetick++;
}

void Canimation::detect_collisions(void)
{
	for (int i = 0; i < MAX_ELEMENT; i++)
	{
		if (m_sprite[i].isValid() && m_sprite[i].m_collcallback)
		{
			for (int j = 0; j < MAX_ELEMENT; j++)
			{
				if (m_sprite[j].isValid() && j != i)
				{
					if (m_sprite[i].collidesWith(m_sprite[j])) {
						m_sprite[i].m_collcallback(this, &m_sprite[i], &m_sprite[j]);
					}
				}
			}
		}
	}
}

void Canimation::move_sprite(void)
{
    for (int i=0; i<MAX_ELEMENT; i++)
    {
        if ( m_sprite[i].isValid() ) 
        {
        int toplimite = m_sprite[i].m_underwater_only ? waterlimit : 0;

        m_sprite[i].m_pos.computeNewPostition(0,toplimite ,xSize-1, ySize-1,m_sprite[i].get_width(),m_sprite[i].get_height(),
            m_sprite[i].m_bounceleft, m_sprite[i].m_bouncetop, m_sprite[i].m_bounceright, m_sprite[i].m_bouncebottom);
        }
    }
}

void Canimation::drawscene(void)
{
    if (spriteListChanged)
    {
    // recréé l'index des shape classé par profondeur de champs (le ploin loin en premier)
        create_depth_index();
    }

    int local_nb_shape = m_nb_shape; // car m_nb_shape peut etre modifié dans 1 callback
    int delindex[MAX_ELEMENT];
    for (int i=0; i<local_nb_shape; i++)
    {
        bool out_of_screen;
        int id= depth_index[i];
/*
        if (id==-1)
        {
            delindex[i]=-1;
            continue; // possible si ajout d'un sprite par 1 callback
        }
        if ( !used[id] )
        {
            delindex[i]=-1;
            continue; // possible si supprimer par 1 callback
        }
*/
        int toplimite = m_sprite[id].m_underwater_only ? waterlimit : 0;
        out_of_screen=m_sprite[id].dessine( fltround_to_int(m_sprite[id].m_pos.m_x), fltround_to_int(m_sprite[id].m_pos.m_y), 0,toplimite ,xSize-1, ySize-1, m_timetick, this);

		if (out_of_screen)
            delindex[i]=id;
		else
			delindex[i]=-1;

        m_sprite[id].m_lifetick++;
        
		if (m_sprite[id].m_life_duration!=-1)
		{
			if ( m_sprite[id].m_lifetick > m_sprite[id].m_life_duration)
				delindex[i]=id;
		}

    }

    int oldnb=local_nb_shape;
    for (int i=0; i<oldnb; i++)
    {
        int id= delindex[i];

        if (id!=-1)
        {
            if ( m_sprite[id].m_deathcallback )
                m_sprite[id].m_deathcallback(m_timetick, this, &m_sprite[id],  fltround_to_int(m_sprite[id].m_pos.m_x), fltround_to_int(m_sprite[id].m_pos.m_y) );
            del_sprite(id);
        }
    }

}