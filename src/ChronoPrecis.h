

#ifndef INC_CHRONO_H
#define INC_CHRONO_H


class Chrono
{
public:
    Chrono();
    ~Chrono();
    
    void Start(void);
    ULONG Stop(void); // renvoi le tps en ms

    ULONG GetTemps_ms(void);
    ULONG GetTemps_micros(void);

    BOOL  EstDisponible(void);


    ULONG Chrono::GetElapsed_micros();
    ULONG Chrono::GetElapsed_ms();

private:
    BOOL dispo;
    __int64 Frequence;
    LARGE_INTEGER count1, count2;
    __int64 t0;
    __int64 t1;

};




#endif // INC_CHRONO_H //////////////////////////
