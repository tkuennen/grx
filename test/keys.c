#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "grx20.h"
#include "grxkeys.h"

#if defined(PENTIUM_CLOCK) && (!defined(__GNUC__) || !defined(__i386__))
#undef PENTIUM_CLOCK
#endif

#ifdef PENTIUM_CLOCK
/******************************************************************************
** This is modified version of keys.c that checks also work of GrKeyPressed()
** and measures time spent in this procedure (at first set divider to clock
** frequency of Your CPU (I have 90MHz): gcc -DPENTIUM_CLOCK=90.
**    A.Pavenis (pavenis@acad.latnet.lv)
*******************  Some time measurements stuff  ***************************
** Macrodefinition RDTSC reads Pentium CPU timestamp counter. It is counting
** CPU clocks. Attempt to use it under 386 or 486 will cause an invalid
** instruction
*/
#define RDTSC(h,l) __asm__ ("rdtsc" : "=a"(l) , "=d"(h))
inline  long   rdtsc(void)  { long h,l; RDTSC(h,l); return l; }
/* ***************************************************************************/
#endif /* PENTIUM_CLOCK */

#if (GRX_VERSION_API-0) <= 0x0225
#ifdef __GO32__
#include <pc.h>
#endif
int GrKeyPressed(void) {
  return kbhit();
}

GrKeyType GrKeyRead(void) {
  return (GrKeyType) getkey();
}
/*
int GrKeyStat(void) {
  return getkbstat();
}
*/
#endif

#define ISPRINT(k) (((unsigned int)(k)) <= 255 && isprint(k))

typedef struct { GrKeyType key;
                 char     *name; } KeyEntry;

static KeyEntry Keys[] = {
  { GrKey_NoKey              , "GrKey_NoKey" },
  { GrKey_OutsideValidRange  , "GrKey_OutsideValidRange" },
  { GrKey_Control_A          , "GrKey_Control_A" },
  { GrKey_Control_B          , "GrKey_Control_B" },
  { GrKey_Control_C          , "GrKey_Control_C" },
  { GrKey_Control_D          , "GrKey_Control_D" },
  { GrKey_Control_E          , "GrKey_Control_E" },
  { GrKey_Control_F          , "GrKey_Control_F" },
  { GrKey_Control_G          , "GrKey_Control_G" },
  { GrKey_Control_H          , "GrKey_Control_H" },
  { GrKey_Control_I          , "GrKey_Control_I" },
  { GrKey_Control_J          , "GrKey_Control_J" },
  { GrKey_Control_K          , "GrKey_Control_K" },
  { GrKey_Control_L          , "GrKey_Control_L" },
  { GrKey_Control_M          , "GrKey_Control_M" },
  { GrKey_Control_N          , "GrKey_Control_N" },
  { GrKey_Control_O          , "GrKey_Control_O" },
  { GrKey_Control_P          , "GrKey_Control_P" },
  { GrKey_Control_Q          , "GrKey_Control_Q" },
  { GrKey_Control_R          , "GrKey_Control_R" },
  { GrKey_Control_S          , "GrKey_Control_S" },
  { GrKey_Control_T          , "GrKey_Control_T" },
  { GrKey_Control_U          , "GrKey_Control_U" },
  { GrKey_Control_V          , "GrKey_Control_V" },
  { GrKey_Control_W          , "GrKey_Control_W" },
  { GrKey_Control_X          , "GrKey_Control_X" },
  { GrKey_Control_Y          , "GrKey_Control_Y" },
  { GrKey_Control_Z          , "GrKey_Control_Z" },
  { GrKey_Control_LBracket   , "GrKey_Control_LBracket" },
  { GrKey_Control_BackSlash  , "GrKey_Control_BackSlash" },
  { GrKey_Control_RBracket   , "GrKey_Control_RBracket" },
  { GrKey_Control_Caret      , "GrKey_Control_Caret" },
  { GrKey_Control_Underscore , "GrKey_Control_Underscore" },
  { GrKey_Space              , "GrKey_Space" },
  { GrKey_ExclamationPoint   , "GrKey_ExclamationPoint" },
  { GrKey_DoubleQuote        , "GrKey_DoubleQuote" },
  { GrKey_Hash               , "GrKey_Hash" },
  { GrKey_Dollar             , "GrKey_Dollar" },
  { GrKey_Percent            , "GrKey_Percent" },
  { GrKey_Ampersand          , "GrKey_Ampersand" },
  { GrKey_Quote              , "GrKey_Quote" },
  { GrKey_LParen             , "GrKey_LParen" },
  { GrKey_RParen             , "GrKey_RParen" },
  { GrKey_Star               , "GrKey_Star" },
  { GrKey_Plus               , "GrKey_Plus" },
  { GrKey_Comma              , "GrKey_Comma" },
  { GrKey_Dash               , "GrKey_Dash" },
  { GrKey_Period             , "GrKey_Period" },
  { GrKey_Slash              , "GrKey_Slash" },
  { GrKey_0                  , "GrKey_0" },
  { GrKey_1                  , "GrKey_1" },
  { GrKey_2                  , "GrKey_2" },
  { GrKey_3                  , "GrKey_3" },
  { GrKey_4                  , "GrKey_4" },
  { GrKey_5                  , "GrKey_5" },
  { GrKey_6                  , "GrKey_6" },
  { GrKey_7                  , "GrKey_7" },
  { GrKey_8                  , "GrKey_8" },
  { GrKey_9                  , "GrKey_9" },
  { GrKey_Colon              , "GrKey_Colon" },
  { GrKey_SemiColon          , "GrKey_SemiColon" },
  { GrKey_LAngle             , "GrKey_LAngle" },
  { GrKey_Equals             , "GrKey_Equals" },
  { GrKey_RAngle             , "GrKey_RAngle" },
  { GrKey_QuestionMark       , "GrKey_QuestionMark" },
  { GrKey_At                 , "GrKey_At" },
  { GrKey_A                  , "GrKey_A" },
  { GrKey_B                  , "GrKey_B" },
  { GrKey_C                  , "GrKey_C" },
  { GrKey_D                  , "GrKey_D" },
  { GrKey_E                  , "GrKey_E" },
  { GrKey_F                  , "GrKey_F" },
  { GrKey_G                  , "GrKey_G" },
  { GrKey_H                  , "GrKey_H" },
  { GrKey_I                  , "GrKey_I" },
  { GrKey_J                  , "GrKey_J" },
  { GrKey_K                  , "GrKey_K" },
  { GrKey_L                  , "GrKey_L" },
  { GrKey_M                  , "GrKey_M" },
  { GrKey_N                  , "GrKey_N" },
  { GrKey_O                  , "GrKey_O" },
  { GrKey_P                  , "GrKey_P" },
  { GrKey_Q                  , "GrKey_Q" },
  { GrKey_R                  , "GrKey_R" },
  { GrKey_S                  , "GrKey_S" },
  { GrKey_T                  , "GrKey_T" },
  { GrKey_U                  , "GrKey_U" },
  { GrKey_V                  , "GrKey_V" },
  { GrKey_W                  , "GrKey_W" },
  { GrKey_X                  , "GrKey_X" },
  { GrKey_Y                  , "GrKey_Y" },
  { GrKey_Z                  , "GrKey_Z" },
  { GrKey_LBracket           , "GrKey_LBracket" },
  { GrKey_BackSlash          , "GrKey_BackSlash" },
  { GrKey_RBracket           , "GrKey_RBracket" },
  { GrKey_Caret              , "GrKey_Caret" },
  { GrKey_UnderScore         , "GrKey_UnderScore" },
  { GrKey_BackQuote          , "GrKey_BackQuote" },
  { GrKey_a                  , "GrKey_a" },
  { GrKey_b                  , "GrKey_b" },
  { GrKey_c                  , "GrKey_c" },
  { GrKey_d                  , "GrKey_d" },
  { GrKey_e                  , "GrKey_e" },
  { GrKey_f                  , "GrKey_f" },
  { GrKey_g                  , "GrKey_g" },
  { GrKey_h                  , "GrKey_h" },
  { GrKey_i                  , "GrKey_i" },
  { GrKey_j                  , "GrKey_j" },
  { GrKey_k                  , "GrKey_k" },
  { GrKey_l                  , "GrKey_l" },
  { GrKey_m                  , "GrKey_m" },
  { GrKey_n                  , "GrKey_n" },
  { GrKey_o                  , "GrKey_o" },
  { GrKey_p                  , "GrKey_p" },
  { GrKey_q                  , "GrKey_q" },
  { GrKey_r                  , "GrKey_r" },
  { GrKey_s                  , "GrKey_s" },
  { GrKey_t                  , "GrKey_t" },
  { GrKey_u                  , "GrKey_u" },
  { GrKey_v                  , "GrKey_v" },
  { GrKey_w                  , "GrKey_w" },
  { GrKey_x                  , "GrKey_x" },
  { GrKey_y                  , "GrKey_y" },
  { GrKey_z                  , "GrKey_z" },
  { GrKey_LBrace             , "GrKey_LBrace" },
  { GrKey_Pipe               , "GrKey_Pipe" },
  { GrKey_RBrace             , "GrKey_RBrace" },
  { GrKey_Tilde              , "GrKey_Tilde" },
  { GrKey_Control_Backspace  , "GrKey_Control_Backspace" },
  { GrKey_Alt_Escape         , "GrKey_Alt_Escape" },
  { GrKey_Control_At         , "GrKey_Control_At" },
  { GrKey_Alt_Backspace      , "GrKey_Alt_Backspace" },
  { GrKey_BackTab            , "GrKey_BackTab" },
  { GrKey_Alt_Q              , "GrKey_Alt_Q" },
  { GrKey_Alt_W              , "GrKey_Alt_W" },
  { GrKey_Alt_E              , "GrKey_Alt_E" },
  { GrKey_Alt_R              , "GrKey_Alt_R" },
  { GrKey_Alt_T              , "GrKey_Alt_T" },
  { GrKey_Alt_Y              , "GrKey_Alt_Y" },
  { GrKey_Alt_U              , "GrKey_Alt_U" },
  { GrKey_Alt_I              , "GrKey_Alt_I" },
  { GrKey_Alt_O              , "GrKey_Alt_O" },
  { GrKey_Alt_P              , "GrKey_Alt_P" },
  { GrKey_Alt_LBracket       , "GrKey_Alt_LBracket" },
  { GrKey_Alt_RBracket       , "GrKey_Alt_RBracket" },
  { GrKey_Alt_Return         , "GrKey_Alt_Return" },
  { GrKey_Alt_A              , "GrKey_Alt_A" },
  { GrKey_Alt_S              , "GrKey_Alt_S" },
  { GrKey_Alt_D              , "GrKey_Alt_D" },
  { GrKey_Alt_F              , "GrKey_Alt_F" },
  { GrKey_Alt_G              , "GrKey_Alt_G" },
  { GrKey_Alt_H              , "GrKey_Alt_H" },
  { GrKey_Alt_J              , "GrKey_Alt_J" },
  { GrKey_Alt_K              , "GrKey_Alt_K" },
  { GrKey_Alt_L              , "GrKey_Alt_L" },
  { GrKey_Alt_Semicolon      , "GrKey_Alt_Semicolon" },
  { GrKey_Alt_Quote          , "GrKey_Alt_Quote" },
  { GrKey_Alt_Backquote      , "GrKey_Alt_Backquote" },
  { GrKey_Alt_Backslash      , "GrKey_Alt_Backslash" },
  { GrKey_Alt_Z              , "GrKey_Alt_Z" },
  { GrKey_Alt_X              , "GrKey_Alt_X" },
  { GrKey_Alt_C              , "GrKey_Alt_C" },
  { GrKey_Alt_V              , "GrKey_Alt_V" },
  { GrKey_Alt_B              , "GrKey_Alt_B" },
  { GrKey_Alt_N              , "GrKey_Alt_N" },
  { GrKey_Alt_M              , "GrKey_Alt_M" },
  { GrKey_Alt_Comma          , "GrKey_Alt_Comma" },
  { GrKey_Alt_Period         , "GrKey_Alt_Period" },
  { GrKey_Alt_Slash          , "GrKey_Alt_Slash" },
  { GrKey_Alt_KPStar         , "GrKey_Alt_KPStar" },
  { GrKey_F1                 , "GrKey_F1" },
  { GrKey_F2                 , "GrKey_F2" },
  { GrKey_F3                 , "GrKey_F3" },
  { GrKey_F4                 , "GrKey_F4" },
  { GrKey_F5                 , "GrKey_F5" },
  { GrKey_F6                 , "GrKey_F6" },
  { GrKey_F7                 , "GrKey_F7" },
  { GrKey_F8                 , "GrKey_F8" },
  { GrKey_F9                 , "GrKey_F9" },
  { GrKey_F10                , "GrKey_F10" },
  { GrKey_Home               , "GrKey_Home" },
  { GrKey_Up                 , "GrKey_Up" },
  { GrKey_PageUp             , "GrKey_PageUp" },
  { GrKey_Alt_KPMinus        , "GrKey_Alt_KPMinus" },
  { GrKey_Left               , "GrKey_Left" },
  { GrKey_Center             , "GrKey_Center" },
  { GrKey_Right              , "GrKey_Right" },
  { GrKey_Alt_KPPlus         , "GrKey_Alt_KPPlus" },
  { GrKey_End                , "GrKey_End" },
  { GrKey_Down               , "GrKey_Down" },
  { GrKey_PageDown           , "GrKey_PageDown" },
  { GrKey_Insert             , "GrKey_Insert" },
  { GrKey_Delete             , "GrKey_Delete" },
  { GrKey_Shift_F1           , "GrKey_Shift_F1" },
  { GrKey_Shift_F2           , "GrKey_Shift_F2" },
  { GrKey_Shift_F3           , "GrKey_Shift_F3" },
  { GrKey_Shift_F4           , "GrKey_Shift_F4" },
  { GrKey_Shift_F5           , "GrKey_Shift_F5" },
  { GrKey_Shift_F6           , "GrKey_Shift_F6" },
  { GrKey_Shift_F7           , "GrKey_Shift_F7" },
  { GrKey_Shift_F8           , "GrKey_Shift_F8" },
  { GrKey_Shift_F9           , "GrKey_Shift_F9" },
  { GrKey_Shift_F10          , "GrKey_Shift_F10" },
  { GrKey_Control_F1         , "GrKey_Control_F1" },
  { GrKey_Control_F2         , "GrKey_Control_F2" },
  { GrKey_Control_F3         , "GrKey_Control_F3" },
  { GrKey_Control_F4         , "GrKey_Control_F4" },
  { GrKey_Control_F5         , "GrKey_Control_F5" },
  { GrKey_Control_F6         , "GrKey_Control_F6" },
  { GrKey_Control_F7         , "GrKey_Control_F7" },
  { GrKey_Control_F8         , "GrKey_Control_F8" },
  { GrKey_Control_F9         , "GrKey_Control_F9" },
  { GrKey_Control_F10        , "GrKey_Control_F10" },
  { GrKey_Alt_F1             , "GrKey_Alt_F1" },
  { GrKey_Alt_F2             , "GrKey_Alt_F2" },
  { GrKey_Alt_F3             , "GrKey_Alt_F3" },
  { GrKey_Alt_F4             , "GrKey_Alt_F4" },
  { GrKey_Alt_F5             , "GrKey_Alt_F5" },
  { GrKey_Alt_F6             , "GrKey_Alt_F6" },
  { GrKey_Alt_F7             , "GrKey_Alt_F7" },
  { GrKey_Alt_F8             , "GrKey_Alt_F8" },
  { GrKey_Alt_F9             , "GrKey_Alt_F9" },
  { GrKey_Alt_F10            , "GrKey_Alt_F10" },
  { GrKey_Control_Print      , "GrKey_Control_Print" },
  { GrKey_Control_Left       , "GrKey_Control_Left" },
  { GrKey_Control_Right      , "GrKey_Control_Right" },
  { GrKey_Control_End        , "GrKey_Control_End" },
  { GrKey_Control_PageDown   , "GrKey_Control_PageDown" },
  { GrKey_Control_Home       , "GrKey_Control_Home" },
  { GrKey_Alt_1              , "GrKey_Alt_1" },
  { GrKey_Alt_2              , "GrKey_Alt_2" },
  { GrKey_Alt_3              , "GrKey_Alt_3" },
  { GrKey_Alt_4              , "GrKey_Alt_4" },
  { GrKey_Alt_5              , "GrKey_Alt_5" },
  { GrKey_Alt_6              , "GrKey_Alt_6" },
  { GrKey_Alt_7              , "GrKey_Alt_7" },
  { GrKey_Alt_8              , "GrKey_Alt_8" },
  { GrKey_Alt_9              , "GrKey_Alt_9" },
  { GrKey_Alt_0              , "GrKey_Alt_0" },
  { GrKey_Alt_Dash           , "GrKey_Alt_Dash" },
  { GrKey_Alt_Equals         , "GrKey_Alt_Equals" },
  { GrKey_Control_PageUp     , "GrKey_Control_PageUp" },
  { GrKey_F11                , "GrKey_F11" },
  { GrKey_F12                , "GrKey_F12" },
  { GrKey_Shift_F11          , "GrKey_Shift_F11" },
  { GrKey_Shift_F12          , "GrKey_Shift_F12" },
  { GrKey_Control_F11        , "GrKey_Control_F11" },
  { GrKey_Control_F12        , "GrKey_Control_F12" },
  { GrKey_Alt_F11            , "GrKey_Alt_F11" },
  { GrKey_Alt_F12            , "GrKey_Alt_F12" },
  { GrKey_Control_Up         , "GrKey_Control_Up" },
  { GrKey_Control_KPDash     , "GrKey_Control_KPDash" },
  { GrKey_Control_Center     , "GrKey_Control_Center" },
  { GrKey_Control_KPPlus     , "GrKey_Control_KPPlus" },
  { GrKey_Control_Down       , "GrKey_Control_Down" },
  { GrKey_Control_Insert     , "GrKey_Control_Insert" },
  { GrKey_Control_Delete     , "GrKey_Control_Delete" },
  { GrKey_Control_Tab        , "GrKey_Control_Tab" },
  { GrKey_Control_KPSlash    , "GrKey_Control_KPSlash" },
  { GrKey_Control_KPStar     , "GrKey_Control_KPStar" },
  { GrKey_Alt_KPSlash        , "GrKey_Alt_KPSlash" },
  { GrKey_Alt_Tab            , "GrKey_Alt_Tab" },
  { GrKey_Alt_Enter          , "GrKey_Alt_Enter" },
  { GrKey_Alt_LAngle         , "GrKey_Alt_LAngle" },
  { GrKey_Alt_RAngle         , "GrKey_Alt_RAngle" },
  { GrKey_Alt_At             , "GrKey_Alt_At" },
  { GrKey_Alt_LBrace         , "GrKey_Alt_LBrace" },
  { GrKey_Alt_Pipe           , "GrKey_Alt_Pipe" },
  { GrKey_Alt_RBrace         , "GrKey_Alt_RBrace" },
  { GrKey_Print              , "GrKey_Print" },
  { GrKey_Shift_Insert       , "GrKey_Shift_Insert" },
  { GrKey_Shift_Home         , "GrKey_Shift_Home" },
  { GrKey_Shift_End          , "GrKey_Shift_End" },
  { GrKey_Shift_PageUp       , "GrKey_Shift_PageUp" },
  { GrKey_Shift_PageDown     , "GrKey_Shift_PageDown" },
  { GrKey_Alt_Up             , "GrKey_Alt_Up" },
  { GrKey_Alt_Left           , "GrKey_Alt_Left" },
  { GrKey_Alt_Center         , "GrKey_Alt_Center" },
  { GrKey_Alt_Right          , "GrKey_Alt_Right" },
  { GrKey_Alt_Down           , "GrKey_Alt_Down" },
  { GrKey_Alt_Insert         , "GrKey_Alt_Insert" },
  { GrKey_Alt_Delete         , "GrKey_Alt_Delete" },
  { GrKey_Alt_Home           , "GrKey_Alt_Home" },
  { GrKey_Alt_End            , "GrKey_Alt_End" },
  { GrKey_Alt_PageUp         , "GrKey_Alt_PageUp" },
  { GrKey_Alt_PageDown       , "GrKey_Alt_PageDown" },
  { GrKey_Shift_Up           , "GrKey_Shift_Up" },
  { GrKey_Shift_Down         , "GrKey_Shift_Down" },
  { GrKey_Shift_Right        , "GrKey_Shift_Right" },
  { GrKey_Shift_Left         , "GrKey_Shift_Left" }
};

#define KEYS (sizeof(Keys)/sizeof(Keys[0]))

void main(void) {
  int spaces_count = 0;
  KeyEntry *kp;
  GrKeyType k;
  int ok;

  /* need to initialize X11 drivers before using keyboard && mouse functions */
#if (GRX_VERSION_API-0) >= 0x0229
  if ( GrGetLibrarySystem() == GRX_VERSION_GENERIC_X11)
    GrSetMode(GR_320_200_graphics);
#elif (GRX_VERSION == GRX_VERSION_GENERIC_X11)
  GrSetMode(GR_320_200_graphics);
#endif

  printf("\n\n Checking GrKey... style interface"
           "\n Type 3 spaces to quit the test\n\n");
  while (spaces_count < 3) {
#ifdef PENTIUM_CLOCK
    int keyPressed=0;
    do
    {
        static double old_tm = -1.0;
        double  tm;
        unsigned s,e;
        s = rdtsc();
        keyPressed = GrKeyPressed();
        e = rdtsc();
        tm = ((double) (e-s))/(1000.0*PENTIUM_CLOCK);
        if (fabs(tm-old_tm) > 0.01) {
          printf ("%5.2f ",tm);
          fflush (stdout);
          old_tm = tm;
        }
    } while (!keyPressed);
#endif /* PENTIUM_CLOCK */
    k = GrKeyRead();
    if (k == ' ') ++spaces_count; else spaces_count = 0;

    ok = 0;
    for ( kp = Keys; kp < &Keys[KEYS]; ++kp ) {
      if (k == kp->key) {
        printf("code 0x%04x\tsymbol %s\n", (unsigned)k, kp->name);
        ok = 1;
        break;
      }
    }
    if (!ok)
      printf("code 0x%04x\tsymbol UNKNOWN\n", (unsigned)k);
  }

  printf("\n\n Now checking getch()"
           "\n Type 3 spaces to quit the test\n\n");
  spaces_count = 0;
  while (spaces_count < 3) {
    k = getch();
    if (k == ' ') ++spaces_count; else spaces_count = 0;

    printf("code 0x%02x\tchar ", (unsigned)k);
    if (ISPRINT(k))
      printf("'%c'\n", (char)k);
    else
      printf("not printable\n");

  }

  printf("\n\n Now checking getkey()"
           "\n Type 3 spaces to quit the test\n\n");
  spaces_count = 0;
  while (spaces_count < 3) {
    k = getkey();
    if (k == ' ') ++spaces_count; else spaces_count = 0;

    printf("code 0x%04x\tchar ", (unsigned)k);
    if (ISPRINT(k))
      printf("'%c'\n", (char)k);
    else
      printf("not printable\n");
  }

}
