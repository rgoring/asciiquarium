
#include "stdafx.h"
//#include <windows.h>

#include "ChronoPrecis.h" 




Chrono::Chrono()
{
    LARGE_INTEGER Frequency;

    dispo = QueryPerformanceFrequency(&Frequency)!=0;
    Frequence = Frequency.QuadPart;

    Start();
}

Chrono::~Chrono()
{
}

BOOL  Chrono::EstDisponible(void)
{
    return(dispo);
}

void Chrono::Start(void)
{
    QueryPerformanceCounter( &count1 ); 
    count2 = count1;
    t0=count1.QuadPart;
    t1=count2.QuadPart;
}

ULONG Chrono::Stop(void)
{
    QueryPerformanceCounter( &count2 ); 
    t1=count2.QuadPart;
    return( GetTemps_ms() );
}


ULONG Chrono::GetTemps_ms(void)
{
    if (!dispo) return(0);


    ULONG duree = (ULONG)( (t1-t0)*1000/Frequence ); // en ms

    return(duree);
}

ULONG Chrono::GetTemps_micros(void)
{
    if (!dispo) return(0);

    ULONG duree = (ULONG)( (t1-t0)*1000000/Frequence ); // en micro-s

    return(duree);
}

ULONG Chrono::GetElapsed_micros(void)
{
    if (!dispo) return(0);

    QueryPerformanceCounter( &count2 ); 
    t1=count2.QuadPart;
    ULONG duree = (ULONG)( (t1-t0)*1000000/Frequence ); // en micro-s

    return(duree);
}
    
ULONG Chrono::GetElapsed_ms(void)
{
    if (!dispo) return(0);

    QueryPerformanceCounter( &count2 ); 
    t1=count2.QuadPart;
    ULONG duree = (ULONG)( (t1-t0)*1000/Frequence ); // en ms

    return(duree);
}
    
