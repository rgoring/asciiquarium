
#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"
#include <conio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include <vector>
#include <algorithm>

using namespace std;
#include "CChaine.h" 
#include "Csprite.h"
#include "Canimation.h"

#include "asciianim.h"
//#include "bconio.h"
#include "utils.h"



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int ANIMATION_TICK_LENGTH =50; // ms


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
Csprite Water_line("","",CYAN, 22 ,DIR_RIGHT, "water_lines");

void create_water_line(Csprite &wl, int screen_width, bool sansEau)
{
    char *water_line_segmentOK[]=
    {
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
		"^^^^ ^^^  ^^^   ^^^    ^^^^      ",
		"^^^^      ^^^^     ^^^    ^^     ",
		"^^$$$$$$^^^^$$$$$$^^^$$$$^^^^^^$$"
    };
    char *water_line_segmentVide[]=
    {
		" ",
    };

    char **water_line_segment;
    int nln;

    if( sansEau)
    {
        water_line_segment = water_line_segmentVide;
        nln = NB_ELEMENT(water_line_segmentVide);
    }
    else
    {
        water_line_segment = water_line_segmentOK;
        nln = NB_ELEMENT(water_line_segmentOK);
    }

   CChaine wlshape;

    for (int i=0; i<nln; i++)
    {
        CChaine line;

        while( line.lenght() < screen_width )
        {
            line.AddChaine(water_line_segment[i]);
        }
        line.AddChaine("\n" );
        wlshape.AddChaine(line.getstr() );
    }
    
    wl.init_sprite(wlshape.getstr(),"", wl.m_defaultcolor, wl.get_depth() );
}


Csprite Castel(
"$$$$$$$$$$$$$$$T~~\n" ""
"$$$$$$$$$$$$$$$|\n"
"$$$$$$$$$$$$$$/^\\\n"
"$$$$$$$$$$$$$/   \\\n"
" _$$$_$$$_$$/     \\$$_$$$_$$$_\n"
"[ ]_[ ]_[ ]/ _   _ \\[ ]_[ ]_[ ]\n"
"|_=__-_ =_|_[ ]_[ ]_|_=-___-__|\n"
" | _- =  | =_ = _    |= _=   |\n"
" |= -[]  |- = _ =    |_-=_[] |\n"
" | =_    |= - ___    | =_ =  |\n"
" |=  []- |-  /| |\\   |=_ =[] |\n"
" |- =_   | =| | | |  |- = -  |\n"
" |_______|__|_|_|_|__|_______|"
,

"                RR\n"
"\n"
"              yyy\n"
"             y   y\n"
"            y     y\n"
"           y       y\n"
"\n"
"\n"
"\n"
"              yyy\n"
"             yy yy\n"
"            y y y y\n"
"            yyyyyyy\n"
,
DARKGRAY, 22,DIR_RIGHT,"castel" );

Csprite Diver(
"$$$$$$$$)\n"
"$$$$$$$(\n"
"$$$$$$$$)\n"
"$$$$$$$/\n"
"$$$$$_.|._\n"
"$$$$/ _:_ \\\n"
"$$$|.(_\"_).|\n"
"$$$_\\. : ./_\n"
"$$/ |..:..| \\\n"
"$/_/ `---' \\_\\\n"
"$\\_)       (_/\n"
"$$$\\   T   /\n"
"$$$_)__|__(_\n"
"$$/....|....\\"
,
"         \n"
"        \n"
"         \n"
"        \n"
"     CC CC\n"
"    C ggg C\n"
"   C ggggg C\n"
"   YCC C CCY\n"
"  Y ryyyyyr Y\n"
" YYY rrrrr YYY\n"
" YYY       YYY\n"
"   r   r   r\n"
"   BrBBrBBrB\n"
"  BBBBBBBBBBB"
, LIGHTGRAY, 0, DIR_RIGHT, "diver" );

Csprite Skull(
/*
"$.-~~-.\n"
"(_O..O_)\n"
"$$|[]|\n"
"$$`--'"
*/

"$.---.\n"
"$\\_,(o,\n"
"$$.)\\_("

,
"",LIGHTGRAY, 0,DIR_RIGHT ,"skull");

/*
 ,---.      .---.       .---.
,o),_/      \_,(o,      \_,(o,
)_/(,         |\_(       .)\_(
*/

/*
color code:
	# 1: body
	# 2: dorsal fin
	# 3: flippers
	# 4: eye
	# 5: mouth
	# 6: tailfin
	# 7: gills
*/
Csprite fish01(
"$$$$$$$\\\n"
"$$$$$...\\..,\n"
"\\  /'       \\\n"
" >=     (  ' >\n"
"/  \\      / /\n"
"$$$$`\"'\"'/''"
,
"       2\n"
"     1112111\n"
"6  11       1\n"
" 66     7  4 5\n"
"6  1      3 1\n"
"    11111311"
,BLACK,0,DIR_RIGHT, "fish01");

Csprite fish02(
"$$$$$$/\n"  
"$$,../...\n"
" /       '\\  /\n"
"< '  )     =<\n"
" \\ \\      /  \\\n"
"$$`'\\'\"'\"'"
,
"      2\n"
"  1112111\n"
" 1       11  6\n"
"5 4  7     66\n"
" 1 3      1  6\n"
"  11311111"
,BLACK,0,DIR_LEFT, "fish02");

Csprite fish03(
"$$$$\\\n"
"\\ /--\\\n"
">=  (o>\n"
"/ \\__/\n"
"$$$$/"
,
"    2\n"
"6 1111\n"
"66  745\n"
"6 1111\n"
"    3"
,BLACK,0,DIR_RIGHT, "fish03");

Csprite fish04(
"$$/\n"
" /--\\ /\n"
"<o)  =<\n"
" \\__/ \\\n"
"$$\\"
,
"  2\n"
" 1111 6\n"
"547  66\n"
" 1111 6\n"
"  3"
,BLACK,0, DIR_LEFT, "fish04");

Csprite fish05(
"$$$$$$$\\:.\n"
"\\;,$$$,;\\\\\\,,\n"
"$$\\\\\\;;:::::::o\n"
"$$///;;::::::::<\n"
"$/;`$``/////``"
,
"       222\n"
"666   1122211\n"
"  6661111111114\n"
"  66611111111115\n"
" 666 113333311"
,BLACK,0, DIR_RIGHT, "fish05");

Csprite fish06(
"$$$$$$.:/\n"
"$$$,,///;,   ,;/\n"
" o:::::::;;///\n"
">::::::::;;\\\\\\\n"
"$$''\\\\\\\\\\'' ';\\"
,
"      222\n"
"   1122211   666\n"
" 4111111111666\n"
"51111111111666\n"
"  113333311 666"
,BLACK,0, DIR_LEFT, "fish06");

Csprite fish07(
"$$__\n"
"><_'>\n"
"$$$'"
,
"  11\n"
"61145\n"
"   3"
,BLACK,0, DIR_RIGHT, "fish07");

Csprite fish08(
"$__\n"
"<'_><\n"
"$`"
,
" 11\n"
"54116\n"
" 3"
,BLACK,0, DIR_LEFT, "fish08");

Csprite fish09(
"$$$..\\,\n"
">='   ('>\n"
"$$'''/''"
,
"   1121\n"
"661   745\n"
"  111311"
,BLACK,0, DIR_RIGHT, "fish09");

Csprite fish10(
"$$,/..\n"
"<')   `=<\n"
"$``\\```"
,
"  1211\n"
"547   166\n"
" 113111"
,BLACK,0, DIR_LEFT, "fish10");

Csprite fish11(
"$$$\\\n"
"$$/ \\\n"
">=_('>\n"
"$$\\_/\n"
"$$$/"
,
"   2\n"
"  1 1\n"
"661745\n"
"  111\n"
"   3"
,BLACK,0, DIR_RIGHT, "fish11");

Csprite fish12(
"$$/\n"
"$/ \\\n"
"<')_=<\n"
"$\\_/\n"
"$$\\"
,
"  2\n"
" 1 1\n"
"547166\n"
" 111\n"
"  3"
,BLACK,0, DIR_LEFT, "fish12");

Csprite fish13(
"$$,\\\n"
">=('>\n"
"$$'/"
,
"  12\n"
"66745\n"
"  13"
,BLACK,0, DIR_RIGHT, "fish13");

Csprite fish14(
"$/,\n"
"<')=<\n"
"$\\`"
,
" 21\n"
"54766\n"
" 31"
,BLACK,0, DIR_LEFT, "fish14");

Csprite fish15(
"$$__\n"
"\\/ o\\\n"
"/\\__/"
,
"  11\n"
"61 41\n"
"61111"
,BLACK,0, DIR_RIGHT, "fish14");

Csprite fish16(
" __\n"
"/o \\/\n"
"\\__/\\"
,
" 11\n"
"14 16\n"
"11116"
,BLACK,0, DIR_LEFT, "fish16");

Csprite fish17(
"><{{{{\">"
,
"61212141"
,BLACK,0, DIR_RIGHT, "fish17");

Csprite fish18(
"<\"}}}}><"
,
"14121216"
,BLACK,0, DIR_LEFT, "fish18");
/*
><>
><(((('>
/><{{{{">
*/

#ifdef XXXXXXXXXXXXX
                        
           .-"""-.      
          /       \     
       .--'._____.'--.  
      ( o     _     o ) 
       '-..o_|_|_o..-'  
   jgs   /        \     
       ()          ()   



             .-"^"-.
            /_....._\
        .-"`         `"-.
       (  ooo  ooo  ooo  )
        '-.,_________,.-'
            /       \
   jgs    _/         \_
         `"`         `"`

#endif //XXXXXXXXXXXX
         const char *UFOFrames[]=
           {
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooooooooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(   oooooooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  o ooooooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oo oooooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooo ooooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oooo oooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooooo ooooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oooooo oooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooooooo ooooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oooooooo oooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooooooooo ooo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oooooooooo oo  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  ooooooooooo o  )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
       "$$$$$$.-\"^\"-.\n"
       "$$$$$/_....._\\\n"
       "$.-\"`         `\"-.\n"
       "(  oooooooooooo   )\n"
       "$'-.,_________,.-'\n"
       "$$$$ / $$$$$ \\ \n"
       "$$ _/ $$$$$$$ \\_ \n"
       "$ `\"` $$$$$$$ `\"` "
,
           };
Csprite UFO(UFOFrames, NB_ELEMENT(UFOFrames),
       "      1111111\n"
       "     111111111\n"
       " 1111         1111\n"
       "1  2222222222222  1\n"
       " 11111111111111111\n"
       "     1       1 \n"
       "   11         11 \n"
       "  111         111 "
,GREEN, 0, DIR_RIGHT, "UFO");
/*
color code:
	# 1: body
	# 2: dorsal fin
	# 3: flippers
	# 4: eye
	# 5: mouth
	# 6: tailfin
	# 7: gills
*/

Csprite Ship[2] = 
{
    Csprite(	
"$$$$$|    |    |\n"
"$$$$)_)  )_)  )_)\n"
"$$$)___))___))___)\\\n"
"$$)____)____)_____)\\\\\n"
"_____|____|____|____\\\\\\__\n"
"\\                   /"
,
"     y    y    y\n"
"\n"
"                  w\n"
"                   ww\n"
"yyyyyyyyyyyyyyyyyyyywwwyy\n"
"y                   y"
 ,WHITE,21,DIR_RIGHT, "ship2right")

,
    Csprite(	
"$$$$$$$$ |    |    |\n"
"$$$$$$$ (_(  (_(  (_(\n"
"$$$$$ /(___((___((___(\n"
"$$$$//(_____(____(____(\n"
"__///____|____|____|_____\n"
"$$$$\\                   /"
,
"         y    y    y\n"
"\n"
"      w\n"
"    ww\n"
"yywwwyyyyyyyyyyyyyyyyyyyy\n"
"    y                   y"
,WHITE,21,DIR_LEFT ,"ship2left")

};


char *Whale_shapes0 =
{
"$$$$$$$$.-----:\n"
"$$$$$$.'       `.\n"
",$$$$/       (o) \\\n"
"\\`._/          ,__)"
};

char *Whale_shapes1 =
{
"$$$$:-----.\n"
"$$.'       `.\n"
"$/ (o)       \\$$$$,\n"
"(__,          \\_.'/"
};


Csprite Whale[2] = 
{
    Csprite( Whale_shapes0
,
"             C C\n"
"           CCCCCCC\n"
"           C  C  C\n"
"        BBBBBBB\n"
"      BB       BB\n"
"B    B       BWB B\n"
"BBBBB          BBBB"
,WHITE,20,DIR_RIGHT ,"whale2right")
,
    Csprite(Whale_shapes1
,
"   C C\n"
" CCCCCCC\n"
" C  C  C\n"
"    BBBBBBB\n"
"  BB       BB\n"
" B BWB       B    B\n"
"BBBB          BBBBB"
,WHITE,20,DIR_LEFT,"wale2left")
};

char *Water_spout0[]=
{
"\n"
"\n"
"$$$$:\n"
,
"\n"
"$$$$:\n"
"$$$$:\n"
,
"$$$. .\n"
"$$$-:-\n"
"$$$$:\n"
,
"$$$. .\n"
"$$.-:-.\n"
"$$$$:\n"
,
"$$$. .\n"
"$'.-:-.`\n"
"$'$$:$$'\n"
,
"\n"
"$$.- -.\n"
"$;$$:$$;\n"
,
"\n"
"\n"
"$;$$$$$;\n"
};
char *Water_spout1[]=
{
"\n"
"\n"
"$$$$$$$$$$$$$$:\n"
,
"\n"
"$$$$$$$$$$$$$$:\n"
"$$$$$$$$$$$$$$:\n"
,
"$$$$$$$$$$$$$. .\n"
"$$$$$$$$$$$$$-:-\n"
"$$$$$$$$$$$$$$:\n"
,
"$$$$$$$$$$$$$. .\n"
"$$$$$$$$$$$$.-:-.\n"
"$$$$$$$$$$$$$$:\n"
,
"$$$$$$$$$$$$$. .\n"
"$$$$$$$$$$$'.-:-.`\n"
"$$$$$$$$$$$'$$:$$'\n"
,
"\n"
"$$$$$$$$$$$$.- -.\n"
"$$$$$$$$$$$;$$:$$;\n"
,
"\n"
"\n"
"$$$$$$$$$$$;$$$$$;\n"
};

Csprite Shark[2] = 
{
    Csprite(
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ __\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$( `\\\n"
"  ,$$$$$$$$$$$$$$$$$$$$$$$$$$)   `\\\n"
";' `.$$$$$$$$$$$$$$$$$$$$$$$$(     `\\__\n"
"$;   `.$$$$$$$$$$$$$__..---''          `~~~~-._\n"
"$$`.   `.____...--''                       (b  `--._\n"
"$$$ >                     _.-'      .((      ._     )\n"
"$$.`.-`--...__         .-'     -.___.....-(|/|/|/|/'\n"
"$;.'$$$$$$$$$`. ...----`.___.',,,_______......---'\n"
" '$$$$$$$$$$$'-'"
,
"\n"
"\n"
"\n"
"\n"
"\n"
"                                           cR\n"
"\n"
"                                          cWWWWWWWW\n"
"\n"
""
,CYAN,2,DIR_RIGHT ,"shark2right")
,
    Csprite(

"$$$$$$$$$$$$$$$$$$$$ __\n"
"$$$$$$$$$$$$$$$$$$$$/' )\n"
"$$$$$$$$$$$$$$$$$$/'   ($$$$$$$$$$$$$$$$$$$$$$$$$$,\n"
"$$$$$$$$$$$$$$__/'     )$$$$$$$$$$$$$$$$$$$$$$$$.' `;\n"
"$$$$$$_.-~~~~'          ``---..__$$$$$$$$$$$$$.'   ;\n"
" _.--'  b)                       ``--...____.'   .'\n"
"(     _.      )).      `-._                     <\n"
" `\\|\\|\\|\\|)-.....___.-     `-.         __...--'-.'.\n"
"$$ `---......_______,,,`.___.'----... .'$$$$$$$$$`.;\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$`-`$$$$$$$$$$$`"
,
"\n"
"\n"
"\n"
"\n"
"\n"
"        Rc\n"
"\n"
"  WWWWWWWWc\n"
"\n"
""
,CYAN,2,DIR_LEFT ,"shark2left")
};


const char *Monster_shapes0[] =
{
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$____\n"
"$$$$$$$$$$$$__$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/   o  \\\n"
"$$$$$$$$$$/    \\$$$$$$$$_$$$$$$$$$$$$$$$$$$$$$_$$$$$$$/     ____ >\n"
"$ _$$$$$$|  __  |$$$$$/   \\$$$$$$$$_$$$$$$$$/   \\$$$$|     |\n"
" | \\$$$$$|  ||  |$$$$|     |$$$$$/   \\$$$$$|     |$$$|     |"
,
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$____\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$__$$$$$$$$$/   o  \\\n"
"$$$$$$$$$$$$$_$$$$$$$$$$$$$$$$$$$$$_$$$$$$$/    \\$$$$$/     ____ >\n"
"$$ _$$$$$$$/   \\$$$$$$$$_$$$$$$$$/   \\$$$$|  __  |$$$|     |\n"
"$ | \\$$$$$|     |$$$$$/   \\$$$$$|     |$$$|  ||  |$$$|     |"
,
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$____\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$__$$$$$$$$$$$$$$$$$$$$/   o  \\\n"
" _$$$$$$$$$$$$$$$$$$$$$$_$$$$$$$/    \\$$$$$$$$_$$$$$$$/     ____ >\n"
"| \\$$$$$$$$$$_$$$$$$$$/   \\$$$$|  __  |$$$$$/   \\$$$$|     |\n"
" \\ \\$$$$$$$/   \\$$$$$|     |$$$|  ||  |$$$$|     |$$$|     |"
,
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$____\n"
"$$$$$$$$$$$$$$$$$$$$$$$__$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/   o  \\\n"
"$ _$$$$$$$$$$_$$$$$$$/    \\$$$$$$$$_$$$$$$$$$$$$$$$$$$/     ____ >\n"
" | \\$$$$$$$/   \\$$$$|  __  |$$$$$/   \\$$$$$$$$_$$$$$$|     |\n"
"  \\ \\$$$$$|     |$$$|  ||  |$$$$|     |$$$$$/   \\$$$$|     |"
};

const char *Monster_shapes1[] =
{
"$$$ ____\n"
"$ /  o   \\$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$__\n"
"< ____     \\$$$$$$$_$$$$$$$$$$$$$$$$$$$$$_$$$$$$$$/    \\\n"
"$$$$$$|     |$$$$/   \\$$$$$$$$_$$$$$$$$/   \\$$$$$|  __  |$$$$$$_\n"
"$$$$$$|     |$$$|     |$$$$$/   \\$$$$$|     |$$$$|  ||  |$$$$$/ |"
,
"$$$ ____\n"
"$ /  o   \\$$$$$$$$$__\n"
"< ____     \\$$$$$/    \\$$$$$$$_$$$$$$$$$$$$$$$$$$$$$_\n"
"$$$$$$|     |$$$|  __  |$$$$/   \\$$$$$$$$_$$$$$$$$/   \\$$$$$$$_\n"
"$$$$$$|     |$$$|  ||  |$$$|     |$$$$$/   \\$$$$$|     |$$$$$/ |"
,
"$$$ ____\n"
"$ /  o   \\$$$$$$$$$$$$$$$$$$$$__\n"
"< ____     \\$$$$$$$_$$$$$$$$/    \\$$$$$$$_$$$$$$$$$$$$$$$$$$$$$$_\n"
"$$$$$$|     |$$$$/   \\$$$$$|  __  |$$$$/   \\$$$$$$$$_$$$$$$$$$$/ |\n"
"$$$$$$|     |$$$|     |$$$$|  ||  |$$$|     |$$$$$/   \\$$$$$$$/ /"
,
"$$$ ____\n"
"$ /  o   \\$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$__\n"
"< ____     \\$$$$$$$$$$$$$$$$$$_$$$$$$$$/    \\$$$$$$$_$$$$$$$$$$_\n"
"$$$$$$|     |$$$$$$_$$$$$$$$/   \\$$$$$|  __  |$$$$/   \\$$$$$$$/ |\n"
"$$$$$$|     |$$$$/   \\$$$$$|     |$$$$|  ||  |$$$|     |$$$$$/ /"
};

Csprite Monster[2] = 
{
    Csprite( Monster_shapes0,NB_ELEMENT(Monster_shapes0),
"\n"
"                                                            W\n"
"\n"
"\n"
""
,LIGHTGREEN, 0,DIR_RIGHT ,"monster2right")
,
    Csprite( Monster_shapes1,NB_ELEMENT(Monster_shapes1),
"\n"
"     W\n"
"\n"
"\n"
""
,LIGHTGREEN, 0,DIR_LEFT ,"monster2left")
};

const char *Duck_shapes0[] =
{
	"$$$$$$_$$$$$$$$$$_$$$$$$$$$$_\n"
	",____(')=$$,____(')=$$,____(')<\n"
	"$\\~~= ')$$$$\\~~= ')$$$$\\~~= ')"
	,
	"$$$$$$_$$$$$$$$$$_$$$$$$$$$$_\n"
	",____(')=$$,____(')<$$,____(')=\n"
	"$\\~~= ')$$$$\\~~= ')$$$$\\~~= ')"
	,
	"$$$$$$_$$$$$$$$$$_$$$$$$$$$$_\n"
	",____(')<$$,____(')=$$,____(')=\n"
	"$\\~~= ')$$$$\\~~= ')$$$$\\~~= ')"
};

const char *Duck_shapes1[] =
{
	"$$_$$$$$$$$$$_$$$$$$$$$$_$\n"
	">(')____,$$=(')____,$$=(')____,\n"
	"$(` =~~/$$$$(` =~~/$$$$(` =~~/"
	,
	"$$_$$$$$$$$$$_$$$$$$$$$$_$\n"
	"=(')____,$$>(')____,$$=(')____,\n"
	"$(` =~~/$$$$(` =~~/$$$$(` =~~/"
	,
	"$$_$$$$$$$$$$_$$$$$$$$$$_$\n"
	"=(')____,$$=(')____,$$>(')____,\n"
	"$(` =~~/$$$$(` =~~/$$$$(` =~~/"
};

Csprite Ducks[2] =
{
	Csprite(Duck_shapes0,NB_ELEMENT(Duck_shapes0),
	"      g          g          g\n"
	"wwwwwgcgy  wwwwwgcgy  wwwwwgcgy\n"
	" wwww Ww    wwww Ww    wwww Ww"
		,WHITE, 0,DIR_RIGHT ,"ducks2right")
	,
	Csprite(Duck_shapes1,NB_ELEMENT(Duck_shapes1),
	"  g          g          g\n"
	"ygcgwwwww  ygcgwwwww  ygcgwwwww\n"
	" wW wwww    wW wwww    wW wwww"
		,WHITE, 0,DIR_LEFT ,"ducks2left")
};

const char *Swan_shapes0[] =
{
"       ___\n"
",_    / _,\\\n"
"| \\   \\( \\|\n"
"|  \\_  \\\\\n"
"(_   \\_) \\\n"
"(\\_   `   \\\n"
" \\   -=~  /"
};

const char *Swan_shapes1[] =
{
" ___\n"
"/,_ \\    _,\n"
"|/ )/   / |\n"
"  //  _/  |\n"
" / ( /   _)\n"
"/   `   _/)\n"
"\\  ~=-   /"
};

Csprite Swans[2] =
{
	Csprite(Swan_shapes0,NB_ELEMENT(Swan_shapes0),
"\n"
"         g\n"
"         yy"
		,WHITE, 0,DIR_RIGHT ,"swan2right")
	,
	Csprite(Swan_shapes1,NB_ELEMENT(Swan_shapes1),
"\n"
" g\n"
"yy"
		,WHITE, 0,DIR_LEFT ,"swan2left")
};

const char *Splat_shapes[] =
{
	"$$$$$$$\n"
	"$$$$$.\n"
	"$$$$***\n"
	"$$$$$'\n"
	"$$$$$$$"
	,
	"$$$$$$$\n"
	"$$$$,*;`\n"
	"$$$\"*,**\n"
	"$$$$*\"'~'\n"
	"$$$$$$$"
	,
	"$$$$, ,\n"
	"$$$$\" \", \"'\n"
	"$$$$*\" *'\"\n"
	"$$$$\" ; ."
	"$$$$$$$"
	,
	"$$$$* ' , ' `\n"
	"$$$$' ` * . '\n"
	"$$$$' `' \",'\n"
	"$$$$* ' \" * .\n"
	"$$$$\" * ', '"
	,
	"$$$$* ' , ' `\n"
	"$$$$' ` * . '\n"
	"$$$$' `' \",'\n"
	"$$$$* ' \" * .\n"
	"$$$$\" * ', '"
};

Csprite Splat(Splat_shapes, NB_ELEMENT(Splat_shapes),
	"\n"
	"\n"
	"\n"
	"\n"
	""
	, LIGHTRED, 0, DIR_RIGHT, "splat");


Csprite Big_fish[2] = 
{
    Csprite(
" ______\n"
"`\"\"-.  `````-----.....__\n"
"$$$$$`.  .      .       `-.\n"
"$$$$$$$:     .     .       `.\n"
"$,$$$$$:   .    .          _ :\n"
": `.$$$:                  (@) `._\n"
"$`. `..'     .     =`-.       .__)\n"
"$$$;     .        =  ~  :     .-\"\n"
"$.' .'`.   .    .  =.-'  `._ .'\n"
": .'$$$:               .   .'\n"
"$'$$$.'  .    .     .   .-'\n"
"$$$.'____....----''.'=.'\n"
"$$$\"\"             .'.'\n"
"$$$$$$$$$$$$$$$''\"'`"
	,
" 111111\n"
"11111  11111111111111111\n"
"     11  2      2       111\n"
"       1     2     2       11\n"
" 1     1   2    2          1 1\n"
"1 11   1                  1W1 111\n"
" 11 1111     2     1111       1111\n"
"   1     2        1  1  1     111\n"
" 11 1111   2    2  1111  111 11\n"
"1 11   1               2   11\n"
" 1   11  2    2     2   111\n"
"   111111111111111111111\n"
"   11             1111\n"
"               11111"
,YELLOW, 0,DIR_RIGHT ,"bigfish2right")
,
    Csprite(
"$$$$$$$$$$$$$$$$$$$$$$$$$$$______\n"
"$$$$$$$$$$__.....-----'''''  .-\"\"'\n"
"$$$$$$$.-'       .      .  .'\n"
"$$$$$.'       .     .     :\n"
"$$$$: _          .    .   :$$$$$,\n"
"$_.' (@)                  :$$$.' :\n"
"(__.       .-'=     .     `..' .'\n"
" \"-.     :  ~  =        .     ;\n"
"$$$`. _.'  `-.=  .    .   .'`. `.\n"
"$$$$$`.   .               :$$$`. :\n"
"$$$$$$$`-.   .     .    .  `.$$$`\n"
"$$$$$$$$$$`.=`.``----....____`.\n"
"$$$$$$$$$$$$`.`.             \"\"\n"
"$$$$$$$$$$$$$$'`\"``"
	,
"                           111111\n"
"          11111111111111111  11111\n"
"       111       2      2  11\n"
"     11       2     2     1\n"
"    1 1          2    2   1     1\n"
" 111 1W1                  1   11 1\n"
"1111       1111     2     1111 11\n"
" 111     1  1  1        2     1\n"
"   11 111  1111  2    2   1111 11\n"
"     11   2               1   11 1\n"
"       111   2     2    2  11   1\n"
"          111111111111111111111\n"
"            1111             11\n"
"              11111"
,YELLOW, 0,DIR_LEFT ,"bigfish2left")
};

Csprite Dessin(
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$,_-=(!7(7/zs_.\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$.='  ' .`/,/!(=)Zm.\n"
"$$$$$$$$$$$$$$$.._,,._..  ,-`- `,\\ ` -` -`\\\\7//WW.\n"
"$$$$$$$$$$,v=~/.-,-\\- -!|V-s.)iT-|s|\\-.'   `///mK%.\n"
"$$$$$$$$v!`i!-.e]-g`bT/i(/[=.Z/m)K(YNYi..   /-]i44M.\n"
"$$$$$$v`/,`|v]-DvLcfZ/eV/iDLN\\D/ZK@%8W[Z..   `/d!Z8m\n"
"$$$$$//,c\\(2(X/NYNY8]ZZ/bZd\\()/\\7WY%WKKW)   -'|(][%4.\n"
"$$$,\\\\i\\c(e)WX@WKKZKDKWMZ8(b5/ZK8]Z7%ffVM,   -.Y!bNMi\n"
"$$$/-iit5N)KWG%%8%%%%W8%ZWM(8YZvD)XN(@.  [   \\]!/GXW[\n"
"$$/ ))G8\\NMN%W%%%%%%%%%%8KK@WZKYK*ZG5KMi,-   vi[NZGM[\n"
"$i\\!(44Y8K%8%%%**~YZYZ@%%%%%4KWZ/PKN)ZDZ7   c=//WZK%!\n"
",\\v\\YtMZW8W%%f`,`.t/bNZZK%%W%%ZXb*K(K5DZ   -c\\\\/KM48\n"
"-|c5PbM4DDW%f  v./c\\[tMY8W%PMW%D@KW)Gbf   -/(=ZZKM8[\n"
"2(N8YXWK85@K   -'c|K4/KKK%@  V%@@WD8e~  .//ct)8ZK%8`\n"
"=)b%]Nd)@KM[  !'\\cG!iWYK%%|   !M@KZf    -c\\))ZDKW%`\n"
"YYKWZGNM4/Pb  '-VscP4]b@W%     'Mf`   -L\\///KM(%W!\n"
"!KKW4ZK/W7)Z. '/cttbY)DKW%     -`  .',\\v)K(5KW%%f\n"
"'W)KWKZZg)Z2/,!/L(-DYYb54%  ,,`, -\\-/v(((KK5WW%f\n"
"$\\M4NDDKZZ(e!/\\7vNTtZd)8\\Mi!\\-,-/i-v((tKNGN%W%%\n"
"$'M8M88(Zd))///((|D\\tDY\\\\KK-`/-i(=)KtNNN@W%%%@%[\n"
"$$!8%@KW5KKN4///s(\\Pd!ROBY8/=2(/4ZdzKD%K%%%M8@%%\n"
"$$$'%%%W%dGNtPK(c\\/2\\[Z(ttNYZ2NZW8W8K%%%%YKM%M%%.\n"
"$$$$$*%%W%GW5@/%!e]_tZdY()v)ZXMZW%W%%%*5Y]K%ZK%8[\n"
"$$$$$$'*%%%%8%8WK\\)[/ZmZ/Zi]!/M%%%%@f\\ \\Y/NNMK%%!\n"
"$$$$$$$$'VM%%%%W%WN5Z/Gt5/b)((cV@f`  - |cZbMKW%%|\n"
"$$$$$$$$$$$'V*M%%%WZ/ZG\\t5((+)L\\'-,,/  -)X(NWW%%\n"
"$$$$$$$$$$$$$$$$`~`MZ/DZGNZG5(((\\,    ,t\\\\Z)KW%@\n"
"$$$$$$$$$$$$$$$$$$$'M8K%8GN8\\5(5///]i!v\\K)85W%%f\n"
"$$$$$$$$$$$$$$$$$$$$$YWWKKKKWZ8G54X/GGMeK@WM8%@\n"
"$$$$$$$$$$$$$$$$$$$$$$!M8%8%48WG@KWYbW%WWW%%%@\n"
"$$$$$$$$$$$$$$$$$$$$$$$$VM%WKWK%8K%%8WWWW%%%@`\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$~*%%%%%%W%%%%%%%@~\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$~*MM%%%%%%@f`\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$'''''"
,""
,DARKGRAY, 0,DIR_RIGHT ,"knot");

/*
_/\__/\__0>
___________0>
  _/\__/\__0>
*/
const char *CreditgrowFrames[]=
{
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
" ============================================= ",
"\n"
"\n"
"\n"
"\n"
"\n"
"$ ___________________________________________ $\n"
" ============================================= ",
"\n"
"\n"
"\n"
"\n"
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" ============================================= ",
"\n"
"\n"
"\n"
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" | asciiquarium V1.3   J.Sommer              | \n"
" ============================================= ",
"\n"
"\n"
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" | asciiquarium V1.3   J.Sommer              | \n"
" | Credits                                   | \n"
" ============================================= ",
"\n"
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" | asciiquarium V1.3   J.Sommer              | \n"
" | Credits                                   | \n"
" |   Kirk Baucom's: Asciiquarium perl script | \n"
" ============================================= ",
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" | asciiquarium V1.3   J.Sommer              | \n"
" | Credits                                   | \n"
" |   Kirk Baucom's: Asciiquarium perl script | \n"
" |   Joan G. Stark: ASCII artwork            | \n"
" ============================================= "
};

Csprite Creditgrow(CreditgrowFrames, NB_ELEMENT(CreditgrowFrames),
""
/*
"$GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG$\n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG \n"
*/
,LIGHTGRAY, 0, DIR_RIGHT,"credit");

Csprite Credit(
"$ ___________________________________________ $\n"
" /                                           \\ \n"
" | asciiquarium V1.3   J.Sommer              | \n"
" | Credits                                   | \n"
" |   Kirk Baucom's: Asciiquarium perl script | \n"
" |   Joan G. Stark: ASCII artwork            | \n"
" ============================================= "

,
""
/*
"$GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG$\n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" G                                           G \n"
" GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG \n"
*/
,LIGHTGRAY, 0, DIR_RIGHT,"credit");


double tick2ms(double tick)
{
 return( (tick*ANIMATION_TICK_LENGTH) );
}
int ms2tick(int ms)
{
   return( max(1,ms/ANIMATION_TICK_LENGTH ) );
}

void add_castel(Canimation *anim);
void castel_callback (int tick, Canimation *anim, Csprite *castel, int sourceposX, int sourceposY)
{
	if (!castel || !anim) { return; }
    // death callback

    add_castel(anim);
}

void add_castel(Canimation *anim)
{
    if ( anim->width()>Castel.get_width() && anim->height()- anim->waterlimit>Castel.get_height() )
    {
        Castel.m_deathcallback  = castel_callback;
        Castel.m_life_duration = ms2tick( randomval(30*1000, 5*60*1000) ); // tps avant de déplacer le chateru entre 30s to 5 minutes
        anim->add_sprite(Castel    , randomval(0,anim->width()-Castel.get_width()), anim->height()-Castel.get_height(),0,0,0,0);
    }
}

void setweedsize(Csprite *seaweed, int maxlen, int currentlen, int type /* 0=(  1={*/)
{
	if (seaweed->get_nb_shape() != 2) {
		return; // ne devrait jamais arriver...
	}

    char *typeLr[]={ "($\n", "{$\n" };
    char *typeLl[]={ "$)\n", "$}\n" };

    type=max(0,min(type,1)); // au cas ou...
    char *typer = typeLr[type];
    char *typel = typeLl[type];

    CChaine seaweed_image0;
	CChaine seaweed_image1;
	for (int i=0; i<maxlen; i++)
	{
		if(maxlen-i<=currentlen)
		{
			if ( i%2 )
			{
				seaweed_image0.AddChaine( typer );
				seaweed_image1.AddChaine( typel );
			}
			else
			{
				seaweed_image0.AddChaine( typel );
				seaweed_image1.AddChaine( typer );
			}
		}
		else
		{
			seaweed_image0.AddChaine( "\n" );
			seaweed_image1.AddChaine( "\n" );
		}
	};
    seaweed->set_shape(0,seaweed_image0);
    seaweed->set_shape(1,seaweed_image1);
//	*seaweed->m_shape[0] = seaweed_image0;
//	*seaweed->m_shape[1] = seaweed_image1;
}

void seaweed_callback(int tick, Canimation *anim, Csprite *seaweed, int sourceposX, int sourceposY)
{
	if (seaweed->m_life_duration < 1) { return; }
    // ration de 0 à 1 pour 0=naissance 1=mort
	double ratio=(double)seaweed->m_lifetick/seaweed->m_life_duration;

#define GROW_PERIOD (0.1)	
#define DEATH_PERIOD (0.05)	

	if (ratio<GROW_PERIOD)
	{
		// on va de data2 à data1
		int nbstep=seaweed->callback_data1;
		int currentstep=seaweed->callback_data2;
		if( ratio/GROW_PERIOD*nbstep > currentstep )
		{
			if (seaweed->callback_data2 < nbstep) { seaweed->callback_data2++; }
			setweedsize(seaweed,nbstep,seaweed->callback_data2, seaweed->callback_data3);
		}
	}
	else if (ratio>(1-DEATH_PERIOD))
	{
		// on va de data2 à data1
		int nbstep=seaweed->callback_data1;
		int currentstep=seaweed->callback_data2;
		ratio = ratio-(1-DEATH_PERIOD);
		if( ratio/DEATH_PERIOD*nbstep > (nbstep-currentstep) )
		{
			if (seaweed->callback_data2 > 0) { seaweed->callback_data2--; }
			setweedsize(seaweed,nbstep,seaweed->callback_data2, seaweed->callback_data3);
		};
	}

}


void add_seaweed(Canimation *anim)
{
    int height = randomval(0, max(anim->height()/5,4) ) + 3;
    CChaine seaweed_image0;
    CChaine seaweed_image1;


    int deb=randomval(0,1);
	Csprite s("",
		"", GREEN, 
        randomval(1,10)<10 ? 21  // 9 fois sur dix au fond
        : randomval(3,20)        // 1 fois sur dix à l'avant plan
        ,DIR_RIGHT,"seaweed");
	s.add_shape("");

	s.callback_data1 = height;    // data1 = taille 'adulte'
	s.callback_data2 = 1;         // data2= taille actuel de la plante
    s.callback_data3 = randomval(0,1); // data3=type de feuille

    setweedsize(&s, height, 1, s.callback_data3);

	int x = randomval(0,anim->width()-2) + 1;
	int y = anim->height() - height;

    // entre 0.5 et 2s
    s.m_animperiod = randomval( ms2tick(500) , ms2tick(2000) );
    s.m_animperiod = max(1,s.m_animperiod);

    s.m_life_duration = ms2tick( randomval(30*1000, 5*60*1000) ); //# seaweed lives for 30s to 5 minutes

	s.m_generation = seaweed_callback;

//printf("seaweed h=%d lifedurtion=%d\n", height, s.m_life_duration );

anim->add_sprite(s,x,y, 0,0,0,0);//,animate_seaweed);
}

void add_randomseaweed(Canimation *anim)
{
    static int next_creation=0;

    //2mn < m_life_duration < 12 => create 1 seaweed evry 2<12mn / seaweed_count for replacing
    // 
    if ( next_creation==0 )
    {
        int seaweed_count = anim->width() / 15;
        seaweed_count= max(seaweed_count,1);

		next_creation = anim->m_timetick + ms2tick( randomval(30*1000, 5*60*1000) )/seaweed_count;
        return;
    }
    if ( anim->m_timetick>next_creation )
    {
        next_creation=0;
        add_seaweed(anim);
    }
}

void add_all_seaweed (Canimation *anim)
{
	//# figure out how many seaweed to add by the width of the screen
	int seaweed_count = anim->width() / 15;
	for (int i=0; i<seaweed_count; i++)
    {
		add_seaweed(anim);
	}
}

//# add an splash
void add_splash (Canimation *anim, Csprite *source, int sourceposX, int sourceposY)
{
    const char *splash[]=
    {
        "\\|/\n"
        "- -\n"
        "/|\\\n",

        "\\ /\n"
        "   \n"
        "/ \\\n",

        "\\ /\n"
        "   \n"
        "/ \\\n"

        "\\ /\n"
        "   \n"
        "   \n",

        "\n"
        "*\n"
        "\n"    
    };

	Csprite b(splash
        
,NB_ELEMENT(splash)
        ,"", CYAN, 
        source->get_depth(), DIR_RIGHT ,"splash"
        );

    b.m_underwater_only = false;


    sourceposY --;
    sourceposX --;

    
    b.m_life_duration = ms2tick(200) ;
    b.m_animperiod  = max(1, b.m_life_duration/4);
    anim->add_sprite(b, sourceposX,sourceposY, 0, tick2ms(-0.005),0,0);
}

void splash_callback (int tick, Canimation *anim, Csprite *bubble, int sourceposX, int sourceposY)
{
    if (!bubble|| !anim) return;
    {
		if (randomval(0, 100) > 90) {
			add_splash(anim, bubble, sourceposX, sourceposY);
		}
	}
}



//# add an air bubble to a fish
void add_bubble (Canimation *anim, Csprite *source, int sourceposX, int sourceposY)
{
    const char*bulles[]={".","o","O","O"};
	Csprite b(bulles, NB_ELEMENT(bulles)
        ,"", CYAN, 
        source->get_depth()-1 // # bubble always goes on top of the fish
        , DIR_RIGHT, "bubble");

    b.m_underwater_only = true;


    sourceposY += source->get_height()/2;
	if (source->m_sens == DIR_RIGHT) { sourceposX += source->get_width(); }

    //    b.m_animperiod = anim->height()/5;
    int nbshape=b.get_nb_shape();
    nbshape=max(1,nbshape);
    b.m_animperiod = 1 +   (int)ms2tick(  50*(sourceposY - anim->waterlimit)/ nbshape);  
	b.m_animperiod = max(1, b.m_animperiod);
    b.m_deathcallback = splash_callback ;
    anim->add_sprite(b, sourceposX,sourceposY, 0, tick2ms(-0.02),0,0);
}

void fish_callback (int tick, Canimation *anim, Csprite *fish, int sourceposX, int sourceposY)
{
	if (!fish || !anim) { return; }
	if (fish->callback_data1 == 0) { return; }
	if( randomval(0,100) > 97 )
    {
		add_bubble(anim, fish, sourceposX, sourceposY);
	}
    /*
	my ($fish, $anim) = @_;
	if(int(rand(100)) > 97) {
		add_bubble($fish, $anim);
	}
	return $fish->move_entity($anim);
    */
}

void diver_callback(int tick, Canimation *anim, Csprite *diver, int sourceposX, int sourceposY)
{
	if (!diver || !anim) { return; }
	if (diver->callback_data1 == 0) { return; }
	if (randomval(0, 100) > 60)
	{
		add_bubble(anim, diver, sourceposX - (diver->get_width() / 2), sourceposY - 6);
	}
}



#define MINCROSSING_TIME (10000) //ms temps le plus rapide de passage d'un poisson à l'ecran
#define MAXCROSSING_TIME (20000) //ms temps le plus lent de passage d'un poisson à l'ecran
void add_fish(Canimation *anim, Csprite &fish)
{
    int x, y;
    fish.set_rand_colormask();
    fish.m_underwater_only =true;
    fish.set_depth(randomval(3,22));

	if (fish.m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - fish.get_width();
	}

    y = randomval(anim->waterlimit, anim->height()-fish.get_height() );

    int crossingtime=randomval(MINCROSSING_TIME,MAXCROSSING_TIME); // tps de traverser horizontalement 'ecran
	if (anim->width() < 40) {
		crossingtime = crossingtime / 2;
	}
    double dx = anim->width()*(double)ANIMATION_TICK_LENGTH/crossingtime; 
    double ddx = dx*randomval(-0.01, +0.01);


    crossingtime=randomval(MINCROSSING_TIME,5*MAXCROSSING_TIME); // tps de traverser verticalement l'ecran
	if (randomval(0, 1) == 1) {
		crossingtime = -crossingtime;
	}
    double dy  = randomval( -tick2ms( 0.001 ), +tick2ms( 0.001 ) );// 0; //anim->height()*(double)ANIMATION_TICK_LENGTH/crossingtime; 

    fish.m_bouncetop   =
    fish.m_bouncebottom= true;

    fish.m_generation = fish_callback;


    anim->add_sprite(fish, x, y , dx , dy , ddx,0);
}

Csprite *FishTab[]=
{
    &fish01,&fish02,&fish03,&fish04,&fish05,&fish06,&fish07,&fish08,
    &fish09,&fish10,&fish11,&fish12,&fish13,&fish14,&fish15,&fish16,
    &fish17,&fish18
};

void add_randomfish(Canimation *anim, int nbfish)
{
    if (nbfish<=0) return;
    static int next_creation=0;

    if ( next_creation==0 )
    {
        next_creation = anim->m_timetick + ms2tick(randomval(MINCROSSING_TIME, MAXCROSSING_TIME ) ) /nbfish;
        return;
    }
    if ( anim->m_timetick>next_creation )
    {
		next_creation=0;
		int f=randomval(0,NB_ELEMENT(FishTab)-1);
		FishTab[f]->callback_data1=1; // 1=avec des bulles possibles
		add_fish(anim , *FishTab[f] );
    }
}

void add_ufo(Canimation *anim, int posy_waterline)
{
	int dir = randomval(0, 1);

	if (dir) {
		UFO.m_sens = DIR_RIGHT;
	}
	else {
		UFO.m_sens = DIR_LEFT;
	}

	UFO.callback_data1 = 0;
	UFO.m_animperiod = ms2tick(50);

	add_fish(anim, UFO);
}

void add_ship(Canimation *anim, int posy_waterline)
{
    int dir=randomval(0,1);

	if (anim->width() <= Ship[dir].get_width()) {
		return;
	}
	if (anim->height() <= Ship[dir].get_height()) {
		return;
	}

    int x;
	if (Ship[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Ship[dir].get_width();
	}


    double dx=tick2ms( 0.014 );
	anim->add_sprite(Ship[dir], x, posy_waterline+1-Ship[dir].get_height() , dx , 0 , 0,0);
}

void create_whale(Csprite &w, char *initialshape)
{
    CChaine initial=initialshape;
        
    w.clear_m_shape();

    CChaine no_water_spout;
    no_water_spout = "\n\n\n";
    no_water_spout.AddChaine(initial.getstr());

    w.add_shape(no_water_spout.getstr());
    w.add_shape(no_water_spout.getstr());
    w.add_shape(no_water_spout.getstr());
    w.add_shape(no_water_spout.getstr());
    w.add_shape(no_water_spout.getstr());

    for(int i=0; i<NB_ELEMENT(Water_spout0); i++)
    {
        CChaine ws;
		if (w.m_sens == DIR_RIGHT) {
			ws = Water_spout1[i];
		}
		else {
			ws = Water_spout0[i];
		}

        ws.AddChaine(initial.getstr());
        w.add_shape(ws.getstr());
    }

}

void add_whale(Canimation *anim, int posy_waterline)
{
    int dir=randomval(0,1);

	if (anim->width() <= Whale[dir].get_width()) {
		return;
	}
	if (anim->height() <= Whale[dir].get_height()) {
		return;
	}

	int x;
	if (Whale[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Whale[dir].get_width();
	}

	Whale[dir].m_animperiod = ms2tick(randomval(20,100)); // anime le jet entre 50 et 100ms


    Whale[dir].m_animperiod = max(1,Whale[dir].m_animperiod);
    anim->add_sprite(Whale[dir], x, posy_waterline+3-Whale[dir].get_height()  ,  tick2ms(0.01) , 0 , 0,0);
}

void shark_collision(Canimation *anim, Csprite *sprite1, Csprite *sprite2)
{
	//if we didn't collide with a fish, ignore it
	if (strncmp(sprite2->m_comment.getstr(), "fish", 4) != 0) {
		return;
	}

	std::pair<int, int> center = sprite2->getCenterPoint();

	Splat.m_life_duration = ms2tick(2800);
	Splat.m_animperiod = ms2tick(700);
	Splat.m_sens = sprite2->m_sens;
	double dx = tick2ms(0.04);
	//make the fish that was eaten explode
	anim->add_sprite(Splat, center.first, center.second, 0.5, 0, 0, 0);
	anim->del_sprite(sprite2);
}

void add_shark(Canimation *anim, int posy_waterline)
{
    int dir=randomval(0,1);

	if (anim->width() <= Shark[dir].get_width()) {
		return;
	}
	if (anim->height() <= Shark[dir].get_height()) {
		return;
	}

    int x;
	if (Shark[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Shark[dir].get_width();
	}

    int y = randomval(anim->waterlimit+3, anim->height()-Shark[dir].get_height()-3 );

    double dx=  tick2ms( 0.04 );
    double ddx = dx*randomval(-0.01,0.01);

	Shark[dir].m_collcallback = &shark_collision;
	//set the collision detection for the teeth
	Shark[dir].setCollisionOffset(-3, 7);
    anim->add_sprite(Shark[dir], x, y  , dx , 0 , ddx,0);
}


void add_monster(Canimation *anim, int posy_waterline)
{
    int dir=randomval(0,1);

	if (anim->width() <= Monster[dir].get_width()) {
		return;
	}
	if (anim->height() <= Monster[dir].get_height()) {
		return;
	}

    int x;
	if (Monster[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Monster[dir].get_width();
	}


	Monster[dir].m_animperiod = ms2tick(250); //randomval( (int)(2/SPEED_COEF) , (int)(4/SPEED_COEF) );
    Monster[dir].m_animperiod = max(1,Monster[dir].m_animperiod);
    anim->add_sprite(Monster[dir], x, posy_waterline+3-Monster[dir].get_height()  ,  tick2ms(0.02) , 0 , 0,0);
}

void add_bigfish(Canimation *anim, int posy_waterline)
{
    int dir=randomval(0,1);

	if (anim->width() <= Big_fish[dir].get_width()) {
		return;
	}
	if (anim->height() <= Big_fish[dir].get_height()) {
		return;
	}


    int x;
	if (Big_fish[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Big_fish[dir].get_width();
	}

    int y = randomval(anim->waterlimit+3, anim->height()-Big_fish[dir].get_height()-3 );
	Big_fish[dir].set_rand_colormask();
	Big_fish[dir].set_depth(randomval(3,25));

    double dx= tick2ms(0.02);
    double ddx = dx*randomval(-0.01,0.01);


    anim->add_sprite(Big_fish[dir], x, y  , dx , 0 , ddx,0);
}

void add_ducks(Canimation *anim, int posy_waterline)
{
	int dir = randomval(0, 1);

	if (anim->width() <= Ducks[dir].get_width()) {
		return;
	}
	if (anim->height() <= Ducks[dir].get_height()) {
		return;
	}

	int x;
	if (Ducks[dir].m_sens == DIR_LEFT) {
		x = anim->width() - 1;
	}
	else {
		x = 1 - Ducks[dir].get_width();
	}


	Ducks[dir].m_animperiod = ms2tick(500);
	Ducks[dir].m_animperiod = max(1, Ducks[dir].m_animperiod);
	anim->add_sprite(Ducks[dir], x, posy_waterline + 1 - Ducks[dir].get_height(), tick2ms(0.015), 0, 0, 0);
}

void add_swan(Canimation *anim, int posy_waterline)
{
	int dir = randomval(0, 1);

	if (anim->width() <= Swans[dir].get_width()) {
		return;
	}
	if (anim->height() <= Swans[dir].get_height()) {
		return;
	}

	int x;
	if (Swans[dir].m_sens == DIR_LEFT)
	{
		x = anim->width() - 1;
	}
	else
	{
		x = 1 - Swans[dir].get_width();
	}


	Swans[dir].m_animperiod = ms2tick(5000);
	Swans[dir].m_animperiod = max(1, Swans[dir].m_animperiod);
	anim->add_sprite(Swans[dir], x, posy_waterline + 3 - Swans[dir].get_height(), tick2ms(0.015), 0, 0, 0);
}

void add_diver(Canimation *anim, int posey_waterline)
{
	if (anim->width() > Diver.get_width() && anim->height() - anim->waterlimit > Diver.get_height())
	{
		Diver.m_life_duration = ms2tick(randomval(5000, 20000));
		Diver.callback_data1 = 1;
		Diver.m_generation = diver_callback;
		anim->add_sprite(Diver, randomval(0, anim->width() - Diver.get_width()), anim->height() - Diver.get_height(), 0, 0, 0, 0);
	}
}

void add_Dessin(Canimation *anim, int posy_waterline)
{
    Dessin.m_underwater_only = true;

	int x= randomval(0, anim->width() - Dessin.get_width() );
    int y = anim->height()-1;
	Dessin.set_depth( randomval(0,24) );

    double dy= -tick2ms(0.02);

    anim->add_sprite(Dessin, x, y  , 0,dy ,  0,0);
}
/*
	switch( randomval(1,4) ) 
    {
    case 1:// up 
        x = randomval(0, anim->width() - Credit.get_width() );
        y = anim->height()-1;
        dx=0;
        dy=-dy;
        break;
    case 2:// down 
        x = randomval(0, anim->width() - Credit.get_width() );
        y = underwater ? anim->waterlimit : 0;
        dx=0;
        break;
    case 3://to right
        x = 1-Credit.get_width();
        y = randomval(underwater?anim->waterlimit:0, anim->height()-Credit.get_height() );
        dy=0;
        Credit.m_sens = DIR_RIGHT;
        break;
    case 4: // to left
        x = anim->width()-1;
        y = randomval(underwater?anim->waterlimit:0, anim->height()-Credit.get_height() );
        dy=0;
        Credit.m_sens = DIR_LEFT;
        break;
    }
*/

void creditgrow_callback (int tick, Canimation *anim, Csprite *bubble, int sourceposX, int sourceposY)
{
    Credit.m_life_duration = ms2tick( randomval(10*1000, 30*1000) );
    anim->add_sprite(Credit, sourceposX, sourceposY  , 0, 0 ,  0,0);
}

void add_Credit(Canimation *anim, int posy_waterline)
{
    int x,y;

    x = randomval(0, anim->width() - Credit.get_width() );
    y = anim->height()-Credit.get_height();

    // entre 0.5 et 2s
    Creditgrow.m_animperiod = ms2tick(200);
    Creditgrow.m_animperiod = max(1,Creditgrow.m_animperiod);

    Creditgrow.m_life_duration = Creditgrow.m_animperiod * 7;// 7 = nb de frame d l'animation

	Creditgrow.m_deathcallback = creditgrow_callback;
    anim->add_sprite(Creditgrow, x, y  , 0, 0 ,  0,0);
}


//void add_CreditDeath(Canimation *anim, int posy_waterline)

void add_Skull(Canimation *anim, int posy_waterline)
{
    Skull.m_underwater_only =true;
    Skull.set_depth(randomval(10,23));
    
    Skull.m_life_duration = ms2tick( randomval(30*1000, 2*60*1000) ); //# skull stay for 30s to 2 minutes

    int x = randomval(0, anim->width()-Skull.get_width()-1);
    int y = anim->height()-Skull.get_height();
    anim->add_sprite(Skull, x, y  , 0, 0 ,  0,0);

}

std::vector<RandObj_t> init_randobj_list(bool noWaterline, int *totalWeight)
{
	const RandObj_t lst[] = {
		{ add_Credit, 1, false },
		{ add_ship, 10, true },
		{ add_whale, 10, true },
		{ add_shark, 15, false },
		{ add_monster, 10, true },
		{ add_bigfish, 10, false },
		{ add_Skull, 3, false },
		{ add_swan, 10, true },
		{ add_ducks, 10, true },
		{ add_ufo, 1, false },
		{ add_diver, 10, false },
	};

	std::vector<RandObj_t> objlist;

	*totalWeight = 0;

	for (int x = 0; x < NB_ELEMENT(lst); x++) {
		if (!(noWaterline && lst[x].needsWater)) {
			objlist.push_back(lst[x]);
			*totalWeight += lst[x].weight;
		}
	}

	return objlist;
}

ADD_RANDOM_OBJ pick_random_obj(std::vector<RandObj_t> &lst, int totalWeight)
{
	int weight, idx, cur, len;

	len = lst.size();

	weight = randomval(0, totalWeight - 1);
	cur = 0;

	for (idx = 0; idx < len; idx++) {
		cur += lst[idx].weight;
		if (weight < cur) {
			return lst[idx].func;
		}
	}
	//default to a shark if the chooser fell through
	return add_shark;
}

void add_random_object(std::vector<RandObj_t> &lst, int totalWeight, Canimation *anim, int posy_waterline)
{
	static int next_creation = 0;
	static bool firsttime = true;
	ADD_RANDOM_OBJ obj;

    // en moyenne 1 ttes les 20s => entre 15 e 45s
	if (firsttime) {
		next_creation = anim->m_timetick + ms2tick(randomval(RANDOBJ_MIN_INIT, RANDOBJ_MAX_INIT));
		firsttime = false;
	}

    if ( anim->m_timetick > next_creation )
    {
		next_creation = anim->m_timetick + ms2tick(randomval(RANDOBJ_MIN_TICK, RANDOBJ_MAX_TICK));
		obj = pick_random_obj(lst, totalWeight);

		obj(anim, posy_waterline);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Caquarium::Caquarium()
{
    m_initok=false;
    m_favoriseCredits=false;
	m_randTotWeight = 0;
}

void Caquarium::init_scene(HWND hwnd, BOOL parentBackgroud /*if possible*/, int anim_period, int nbfish_desired, int sansEau, double densite, bool favoriseCredits)
{
#ifdef _DEBUG
	ShowConsoleWindow(TRUE);
#endif

#if 0 // test randomval()
	#define NBR 101

    int t[NBR];
    for(int i=0; i<NBR; i++) t[i]=0;
    for(int i=0; i<100000; i++) t[randomval(0,NBR-1)]++;
    for(int i=0; i<NBR; i++)
        printf("%u ",t[i] );
#endif

	bool noWaterline = (sansEau) ? true : false;

	m_objList = init_randobj_list(noWaterline, &m_randTotWeight);

	anim_period+=15;
	ANIMATION_TICK_LENGTH =		m_anim_period= anim_period;
	ANIMATION_TICK_LENGTH = max(15,ANIMATION_TICK_LENGTH);
    initViewPort(hwnd,parentBackgroud);

    SetViewportInputProps();

    CreateViewportBuffer(0);
    SetViewportBufferProps();

    CreateViewportBuffer(1);
    SetViewportBufferProps();

#if 0
        DisplayViewportBuffer(0);
        DisplayViewportBuffer(1);
        SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
#endif

    SetCurrentViewportBuffer(0);

    getviewport_size( &m_xSize, &m_ySize);


    initrandom((int)time(NULL));

    fish01.set_rand_colormask();

   
    m_anim.xSize = m_xSize;
    m_anim.ySize = m_ySize;

    create_water_line(Water_line, m_xSize, noWaterline);

    create_whale(Whale[0], Whale_shapes0);
    create_whale(Whale[1], Whale_shapes1);

#define WATER_YTOP (6)
    if ( !noWaterline && m_anim.height() > Water_line.get_height()+WATER_YTOP+5 )
    {
        m_anim.add_sprite(Water_line, 0, WATER_YTOP,0,0,0,0);
        m_anim.waterlimit=Water_line.get_height()+WATER_YTOP-1;
    }
	else
	{
		m_anim.waterlimit = 0;
	}

    add_castel(&m_anim);
/*
if ( m_anim.width()>Castel.get_width() && m_anim.height()-m_anim.waterlimit>Castel.get_height() )
    {
        Castel.m_deathcallback  = castel_callback;
        Castel.m_life_duration = ms2tick( randomval(30*1000, 5*60*1000) ); //# seaweed lives for 30s to 5 minutes
        m_anim.add_sprite(Castel    , randomval(0,m_xSize-Castel.get_width()), m_ySize-Castel.get_height(),0,0,0,0);
    }
*/
    add_all_seaweed(&m_anim);

	if (densite < 0)
	{
		m_nbfish = max(0, nbfish_desired);
	}
    else
    {
        m_nbfish = (int)(sqrt((double)m_xSize*m_ySize)*densite);
        if (densite>0 && m_nbfish==0) m_nbfish=1;
    }
    // check if not too dense
    if ( m_xSize*m_ySize > 0 )
    {
        if( m_nbfish/sqrt((double)m_xSize*m_ySize) > 0.5 )
        {
            m_nbfish = (int)(sqrt((double)m_xSize*m_ySize)* 0.5);
			if (m_nbfish == 0) { m_nbfish = 1; }
        }
    }

	for (int i = 0; i < m_nbfish; i++) {
		add_fish(&m_anim, *FishTab[randomval(0, NB_ELEMENT(FishTab) - 1)]);
	}

    m_dispb=0;
    m_currb=1;
    SetCurrentViewportBuffer(m_dispb);

    m_anim.drawscene();
    tmoy=ANIMATION_TICK_LENGTH;

    m_favoriseCredits = favoriseCredits;
    chrono.Start();
    m_initok=true;
}

// renvoi 1 si il faut arrêter
int Caquarium::drawnext_scene(void)
{
	if (!m_initok) { return(0); }

    DisplayViewportBuffer(m_dispb);
	if (getviewportnbevenement() > 0) { return(1); }
	//Sleep(ANIMATION_TICK_LENGTH);
    SetCurrentViewportBuffer(m_currb);

	clearviewport(); 

    
    //add_randomseaweed(&m_anim);
    add_randomfish(&m_anim, m_nbfish );
	add_random_object(m_objList, m_randTotWeight, &m_anim, WATER_YTOP);

    m_anim.timestep();
    m_anim.move_sprite();
    m_anim.drawscene();
	m_anim.detect_collisions();


    m_currb=(m_currb+1)%2;
    m_dispb=(m_dispb+1)%2;

    ULONG tps=chrono.GetElapsed_micros(); // ente total entre 2 draw

    tmoy = tmoy*0.9+0.1*tps/1000;
    {
        int static cpt=0;
        if ((++cpt)%10==0)
        {
            //printf("%g\n", tmoy);
            ANIMATION_TICK_LENGTH = (int)tmoy; // adapte ANIMATION_TICK_LENGTH au temps réellement passé
        }
    }

    chrono.Start();

    return(0);
}

void Caquarium::close_scene(void)
{
	if (!m_initok) { return; }
    m_anim.clear();
    closeViewPort();
    m_initok=false;
}
