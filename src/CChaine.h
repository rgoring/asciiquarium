
#if !defined(CCHAINE_H_INCLUDED)
#define CCHAINE_H_INCLUDED

class CChaine
{
public:
    CChaine();
    CChaine(const char*source);
    ~CChaine();
    CChaine& operator = ( const char *source );
    CChaine& operator = ( const CChaine &source );
    void AddChaine(const char *source2);
    int lenght(void);

    const char*getstr(){ return(m_str);};
    char* acquire(){ acquirecount++; return(m_str);}; // pas vraiment implémenter...
    void release(){ acquirecount--;};                // pas vraiment implémenter...

private:
    int acquirecount;
    char *m_str;
};

#endif // defined(CCHAINE_H_INCLUDED)