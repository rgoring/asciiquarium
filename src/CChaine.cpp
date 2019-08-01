
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include "CChaine.h"
//////////////////////////////////////////
char *allouecharbuffer(int len) // alloue len+1 octets
{
    char *ret;
    
    ret = (char*)malloc( len+1 );
    return(ret);
}

char *dupliqueChaine(const char *source)
{
    char *ret;
    
    if (source==NULL)
        return(NULL);
    
    ret = allouecharbuffer( strlen(source) );
    if (ret==NULL)
        return(NULL);

    strcpy(ret, source);
    return(ret);
}

char *dupliqueConcatChaine(const char *source1, const char *source2)
{
    char *ret;
    
    if (source1==NULL && source2==NULL)
        return(NULL);
    
    if (source1==NULL)
        return( dupliqueChaine(source2) );
    if (source2==NULL)
        return( dupliqueChaine(source1) );

    ret = allouecharbuffer( strlen(source1)+strlen(source2) );
    if (ret==NULL)
        return(NULL);

    strcpy(ret, source1);
    strcat(ret, source2);
    return(ret);
}


void libereDuplicationChaine(char **str)
{
    if (*str)
    {
        free(*str);
        (*str)=NULL;
    }
}

char *dupliqueAddChaine(char **source, const char *source2) // renvoi source
{
    char *newsource;
    newsource = dupliqueConcatChaine( *source, source2);
    libereDuplicationChaine(source);
    *source= newsource;
    return(newsource);
}

/////////////////////////////////////////////////////////////


CChaine::CChaine()
{
    m_str=NULL;
    acquirecount=0;
};
CChaine::CChaine(const char*source)
{
    m_str=dupliqueChaine(source);
    acquirecount=0;
};
CChaine::~CChaine()
{
    libereDuplicationChaine(&m_str);
}
CChaine& CChaine::operator = ( const char *source )
{
    libereDuplicationChaine(&m_str);
    m_str=dupliqueChaine(source);
    return(*this);
}
CChaine& CChaine::operator = ( const CChaine &source )
{
    //const char* s=source.getstr();
    *this = source.m_str;
    return(*this);
}
int CChaine::lenght(void)
{
    if (!m_str) return(0);
    return(strlen(m_str));
}

void CChaine::AddChaine(const char *source)
{
    char *newsource;
    newsource = dupliqueConcatChaine( m_str, source);
    libereDuplicationChaine(&m_str);
    m_str= newsource;
}
