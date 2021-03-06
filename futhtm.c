/* futhtm.c */

//        f_fn_prtlin  2340 - 2824    is used for
//            make_calendar_day_html_file() 
//            write_calendar_day_score(char *pname, int istress_score) {
//            NOT USED void f_fnOutPutTopOfHtmlFile(void)
//

/* read from in_docin_lines[] up to idx in_docin_last_idx
* and format and write an html output file    lll
*/

// MIT License
//
// Copyright (c) 2017 softwaredev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

  // read from input docin_lines string array
  // format and write an html output file            bbb
  // format and write to js-malloc'd  memory
  //
int gbl_logf_fnBIG_prtlin = 0;


char *gbl_space_for_HTML_fut; // space malloc'ed in js,  passed into mamb_report_big_year(), then here
int gbl_flagPrintRedline;  // after printing next line
int gbl_flagDONOTPrtRlin;
int gbl_flagMEMCPY_P_11_is_done;
char gbl_redlinebuf[8192];

  char myprevline1[2024];
  char myprevline2[2024];
  char myprevline3[2024];

int   gbl_is_first_f_fn_prtlin;
int   gbl_is_first_f_fnBIG_prtlin;
int   gbl_put_html_here; // gbl smup html code written at this location

int gbl_dGREATlineOnePrinted ;  // = 1 after 1st GREAT line printed 
int gbl_dGREATlineTwoPrinted ;  // = 0 after 2nd GREAT line printed
//int gbl_justPrinted_STRESSline;


#define NUM_PTS_WHOLE_YEAR 182
void f_fnBIGOutPutTopOfHtmlFile(void);
void fn_BIGoutputGrhAndAspects(void);
void f_fnBIG_aspect_text(char *);
void fn_BIGaspect_from_to(char *);
void f_fnBIG_prtlin(char *lin);

int hasEqualBrackets(char *inlin);

int logprtallprtlin = 0;

/* 1=yes,0=no       bbb  */
#define GBL_HTML_HAS_NEWLINES 1
/* #define GBL_HTML_HAS_NEWLINES 0 */


char gbl_prtlin_lastline[8192];

int gbl_have_hit_OMG;    // for putting blank line right color when last star exactly on stress line or OMG line
int gbl_have_hit_stress; // for putting blank line right color when last star exactly on stress line or OMG line

int gblWeAreInPREblockContent; /* 1 = yes, 0 = no */
int gblCalDayScoreIsWritten;

/* char gbl_person_name[32]; */
char gbl_name_for_fut[32];  /* for stress num table at bottom */
char gbl_year_for_fut[32];  /* for stress num table at bottom */
/* char *gbl_csv_person_string_in_htm; */
/* char gbl_BuffYearStressScore[32];   TOO LONG ?  */

int gbl_YearStressScore;
char gbl_ffnameHTML[256];
int  gbl_is_first_year_in_life;
int  gbl_do_readahead;
int  gbl_just_started_readahead;

int  gbl_do_second_line;        // for benchmark label insert
char gbl_benchmark_label[32];   // GREAT, OMG, etc.
int  insert_label_benchmark(char *line_curr, char * line_next);
void insert_minus_benchmark(char *line_to_change);
int  gbl_we_are_printing_graph;
void change_last_7_chars(char *line_to_print);
void  remove_spans(char *linethird);

/* int rkdb = 0; */ /* 0=no, 1=yes */
char have_we_hit_beg_graph[5] = "NO"; /* signal to output grh and asp */

#include "futdefs.h"
#include "futhtm.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ARGS 2

/* #define APP_NAME "Astrology for Me" */
/* #define APP_NAME "Astrology by Measurement" */
/* #define APP_NAME "Me & My BFFs" */
//#define APP_NAME "\"Me and my BFFs\""
/* #define APP_NAME "\"My BFFs and I\"" */
/* file extension for group sharing will be ".mamb" */



/* below also in mambutil.c and futdoc.c */
#define IDX_FOR_BEST_YEAR 90
#define IDX_FOR_MYSTERIOUS 91
#define IDX_FOR_BEST_DAY 92
#define IDX_FOR_UPS_AND_DOWNS_2 93 /* fix 201311 */
#define IDX_FOR_SCORE_B 95   /* best day 2nd iteration */


char s1CY[64];

#define CY_SCORELINE_cGr2 \
      strcpy(s1CY, ""      ); \
      sprintf(writebuf,\
          "<tr class='cGr2 subjectcss ' >"\
            "<td class='cGr2'></td>"\
            "<td class='scoreCYelt'> %s%d </td>"\
            "<td></td>"\
            "<td>%s</td>"\
            "<td><span style='visibility:hidden;'>X</span></td>"\
            "<td></td>"\
          "</tr>"\
        , s1CY\
        , gbl_YearStressScore \
        , gbl_name_for_fut\
      );\
      f_fnBIG_prtlin(writebuf);


#define CY_SCORELINE_cGre \
      strcpy(s1CY, ""      ); \
      sprintf(writebuf,\
          "<tr class='cGre subjectcss ' >"\
            "<td class='cGre'></td>"\
            "<td class='scoreCYelt'> %s%d </td>"\
            "<td></td>"\
            "<td>%s</td>"\
            "<td><span style='visibility:hidden;'>X</span></td>"\
            "<td></td>"\
          "</tr>"\
        , s1CY\
        , gbl_YearStressScore \
        , gbl_name_for_fut\
      );\
      f_fnBIG_prtlin(writebuf);

#define CY_SCORELINE_cNeu \
      strcpy(s1CY, ""      ); \
      sprintf(writebuf,\
          "<tr class='cNeu subjectcss ' >"\
            "<td class='cNeu'></td>"\
            "<td class='scoreCYelt'> %s%d </td>"\
            "<td></td>"\
            "<td>%s</td>"\
            "<td><span style='visibility:hidden;'>X</span></td>"\
            "<td></td>"\
          "</tr>"\
        , s1CY\
        , gbl_YearStressScore \
        , gbl_name_for_fut\
      );\
      f_fnBIG_prtlin(writebuf);

#define CY_SCORELINE_cRed \
      strcpy(s1CY, ""      ); \
      sprintf(writebuf,\
          "<tr class='cRed subjectcss ' >"\
            "<td class='cRed'></td>"\
            "<td class='scoreCYelt'> %s%d </td>"\
            "<td></td>"\
            "<td>%s</td>"\
            "<td><span style='visibility:hidden;'>X</span></td>"\
            "<td></td>"\
          "</tr>"\
        , s1CY\
        , gbl_YearStressScore \
        , gbl_name_for_fut\
      );\
      f_fnBIG_prtlin(writebuf);


#define CY_SCORELINE_cRe2 \
      if (gbl_YearStressScore < 10) strcpy(s1CY, "&nbsp;"); \
      else                          strcpy(s1CY, ""      ); \
      sprintf(writebuf,\
          "<tr class='cRe2 subjectcss ' >"\
            "<td class='cRe2'></td>"\
            "<td class='scoreCYelt'> %s%d </td>"\
            "<td></td>"\
            "<td>%s</td>"\
            "<td><span style='visibility:hidden;'>X</span></td>"\
            "<td></td>"\
          "</tr>"\
        , s1CY\
        , gbl_YearStressScore\
        , gbl_name_for_fut\
      );\
      f_fnBIG_prtlin(writebuf);

//      strcat(string_for_table_only, writebuf); 
//<.>
////        gbl_name_for_fut, gbl_YearStressScore );   
//gbl_year_for_fut
//gbl_YearStressScore
//<.>





//<.>
//      f_fnBIG_prtlin( blank_cGr2);
//      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'> </td><td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
//      f_fnBIG_prtlin( blank_cGre);
//      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
//      f_fnBIG_prtlin( blank_cNeuA);
//      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
//      f_fnBIG_prtlin( blank_cNeuB);
//      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
//      f_fnBIG_prtlin( blank_cRed);
//      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
//      //  writebuf2        is   names  of person_A  and  person_B 
//      //  gbl_YearStressScore   is   in_rank_lines[i]->score;  // save for NEW "real" string_for_table_only   below
//      sprintf(writebuf, "<tr class=\"cRe2 subjectcss \" ><td id='tdIMG11'></td> <td> %s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
//        gbl_name_for_fut, gbl_YearStressScore );   
//      f_fnBIG_prtlin( writebuf);   // score is omg cRe2
//
//      f_fnBIG_prtlin( blank_cRe2_12 );
//
//<.>
//

//      strcat(string_for_table_only, sp backslash
#define CY_BENCHLINE_cGr2 \
      f_fnBIG_prtlin( \
        "<tr class='cGr2 benchline'>"\
        "  <td id='tdIMG02zF'></td>"\
        "  <td class='cssBenchmarkText'> 90 </td>"\
        "  <td class='cssBenchmarkText'>Great</td>"\
        "  <td></td>"\
        "  <td></td>"\
        "  <td> </td>"\
        "</tr>"\
      );

#define CY_BENCHLINE_cGre \
      f_fnBIG_prtlin( \
        "<tr class='cGre benchline'>"\
        "  <td id='tdIMG04zF'></td>"\
        "  <td class='cssBenchmarkText'> 75  </td>"\
        "  <td class='cssBenchmarkText'>Good</td>"\
        "  <td></td>"\
        "  <td></td>"\
        "  <td> </td>"\
        "</tr>"\
      );

#define CY_BENCHLINE_cNeu \
      f_fnBIG_prtlin( \
        "<tr class='cNeu benchline'>"\
        "  <td id='tdIMG06zF'></td>"\
        "  <td class='cssBenchmarkText'> 50  </td>"\
        "  <td class='cssBenchmarkText'>Average</td>"\
        "  <td></td>"\
        "  <td></td>"\
        "  <td> </td>"\
        "</tr>"\
      );

#define CY_BENCHLINE_cRed \
      f_fnBIG_prtlin( \
        "<tr class='cRed benchline'>"\
        "  <td id='tdIMG08zF'></td>"\
        "  <td class='cssBenchmarkText'> 25  </td>"\
        "  <td class='cssBenchmarkText'>Stress</td>"\
        "  <td></td>"\
        "  <td></td>"\
        "  <td> </td>"\
        "</tr>"\
      );

#define CY_BENCHLINE_cRe2 \
      f_fnBIG_prtlin( \
        "<tr class='cRe2 benchline'>"\
        "  <td id='tdIMG10zF'></td>"\
        "  <td class='cssBenchmarkText'> 10  </td>"\
        "  <td class='cssBenchmarkText'>OMG</td>"\
        "  <td></td>"\
        "  <td></td>"\
        "  <td> </td>"\
        "</tr>"\
      );


void SW_put_aspect_HTML_TOP(char *aspect_code);// put TOP of aspect_container here with DATA to allow JS to draw the impact sinewaves on a tap/click
void SW_put_aspect_HDR_TOP(void);
void SW_put_aspect_HDR_BOT(void);
void SW_put_aspect_HTML_BOT(char *aspect_code);// put TOP of aspect_container here with DATA to allow JS to draw the impact sinewaves on a tap/click

// this is populated in futdoc.c and used in futhtm.c
//extern char *gbl_PSV_of_SW_CSVs;   // this is updated after each aspect in this current calendar year is "finished"
//extern char gbl_PSV_of_SW_CSVs[8192];   // this is updated after each aspect in this current calendar year is "finished"
// this is populated in futdoc.c and used in futhtm.c
char gbl_fromDoc_PSV_of_SW_CSVs[8192];   // this is passed as arg from futdoc.c

//char gbl_ALL_sineWaveDATAs[2048] = "";   // fyi char one_sineWaveDATA[128];
char gbl_PSV_of_SW_DATA_CSVs[8192] = "";   // this is passed as arg from futdoc.c


char *fN_day_of_week[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat",""};
extern char *N_mth_cap[];
/* "Mth","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}; */
/* see day_of_week() */


void write_calendar_day_score(char *pname, int istress_score);

void f_fnOutPutTopOfHtmlFile(void);

//void fn_outputGrhAndAspects(void);
 
void f_fn_prtlin(char *lin);
/* void f_fn_prtlin_aspect(char *lin); */ /* no \n at end */

char aspect_code[10];
//void fn_aspect_from_to(char *);
//void f_fn_aspect_text(char *);


/* these are in rkdebug.o */
//extern void fopen_fpdb_for_debug(void);
//extern void fclose_fpdb_for_debug(void);


/* in mambutil.c */
extern int  sall(char *s,char *set);
extern int  sfind(char s[], char c);
extern void sfill(char *s, int num, int c);
extern int mapBenchmarkNumToPctlRank(int in_score);
extern void bracket_string_of(
  char *any_of_these,
  char *in_string,   
  char *left_bracket,
  char *right_bracket  );

void scharswitch(char *s, char ch_old, char ch_new);
extern int mapNumStarsToBenchmarkNum(int category, int num_stars);

extern void strsubg(char *s, char *replace_me, char *with_me);
extern char *mkstr(char *s,char *begarg,char *end); 
extern void scharout(char *s,int c);   /* remove all c from s */
extern int  scharcnt(char *s,int c); 
extern char *sfromto(char *dest, char *srcarg, int beg, int end);
//extern void put_br_every_n(char *instr,  int line_not_longer_than_this);
//extern void fn_right_pad_with_hidden(char *s_to_pad, int num_to_pad);
extern int binsearch_asp(char *asp_code, struct aspect tab[], int num_elements);
extern char *csv_get_field(char *csv_string, char *delim, int want_fieldnum);
extern int day_of_week(int month, int day, int year);
/* in mambutil.c */



extern void f_docin_free(void);
void f_docin_get(char *in_line);

int    global_max_docin_idx;
char **global_docin_lines;
int    global_read_idx;
char doclin[8192];
int    gblIsThis1stGrhToOutput;  /* 0 false, 1 true */

char s1[8192];
char s2[8192];
char s3[8192];
char s4[8192];
char s5[8192];
char s6[8192];
char writebuf[8192];
char workbuf[8192];

//FILE *Fp_f_HTML_file;
int   n;
char *p = &writebuf[0];

#define MAX_WK 10
struct {
  char wk[133]; 
} wks[MAX_WK];
#define f_arr(nn) (wks[nn].wk)

/*  wks is array of struct size 133 chars
* 
*  (wks[k].wk)  <==>   arr(k)
*   
*  this expression:  (wks[k].wk)  
*  gives you the kth 133-char buffer in array wks.
* *
*  With the *define* below, you can say this: 
*  arr(k) for the same buffer.
*/


#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
/* # examples
* #define getGrhdata(i1,k1) (*(Grhdata+(i1)*Num_eph_grh_pts+(k1)))
* #define putGrhdata(i2,k2,m2) (*(Grhdata+(i2)*Num_eph_grh_pts+(k2))=(m2))
*/
#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/


int is_first_f_docin_get;      /* 1=yes, 0=no */
int is_first_from_to_in_doclin ;  /* 1=yes, 0=no */




/* note that is_first_from_to_in_doclin  is set at the top of
*       void fn_aspect_from_to(char *doclin)
*/
/* ***************************************************** 
*  output entire ".html" file
*  ***************************************************** */
//char *make_fut_htm_file(
  // plus new arg at bottom
int make_fut_htm_file (
//  char *in_html_filename,   // html_filename contain "webview" or not (big version for browser)
  char *arg_thumbnailInfo,
  char *arg_space_for_HTML_fut, // space malloc'ed in js,  passed into mamb_report_big_year()
  char *in_docin_lines[],
  int   in_docin_last_idx,
  char *in_BuffYearStressScore,
  int   is_first_year_in_life,
  char *arg_PSV_of_SW_CSVs         // from gbl_PSV_of_SW_CSVs in futdoc.c
)
{
//tn();
trn("in make_fut_htm_file()");
//tr("new arg");ksn(arg_PSV_of_SW_CSVs);

  strcpy(gbl_fromDoc_PSV_of_SW_CSVs, arg_PSV_of_SW_CSVs);  // same name in futdoc.c and futhtm.c confusing maybe

  gbl_dGREATlineOnePrinted   = 0;  // = 1 after 1st GREAT line printed 
  gbl_dGREATlineTwoPrinted   = 0;  // = 0 after 2nd GREAT line printed
  gbl_flagPrintRedline       = 0;  // after printing next line
  gbl_flagDONOTPrtRlin       = 0;
  gbl_flagMEMCPY_P_11_is_done = 0;
//  gbl_justPrinted_STRESSline = 0;

  gbl_is_first_f_fn_prtlin        = 1;  /* init to true */
  gbl_is_first_f_fnBIG_prtlin     = 1;  
  gbl_space_for_HTML_fut          = arg_space_for_HTML_fut;

  is_first_f_docin_get  = 1;  /* 1=yes, 0=no */


  int i;
/* trn("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"); */

kin(in_docin_last_idx);
ksn(in_BuffYearStressScore);
//int id;
//for(id=0; id < in_docin_last_idx; id++) {
//ki(id);ksn(in_docin_lines[id]);
//}

//  strcpy(gbl_ffnameHTML, in_html_filename);

  gbl_is_first_year_in_life = is_first_year_in_life;

  gblWeAreInPREblockContent   = 0;  /* init to false */
  gblCalDayScoreIsWritten = 0;
//  is_first_f_docin_get  = 1;  /* 1=yes, 0=no */

  global_max_docin_idx = in_docin_last_idx;
  global_docin_lines   = in_docin_lines;

//char myss[64];
//  strcpy(myss, in_BuffYearStressScore);
  gbl_YearStressScore = atoi(in_BuffYearStressScore);

  /* open output HTML file
  */
//  if ( (Fp_f_HTML_file = fopen(in_html_filename, "w")) == NULL ) {
//    rkabort("Error  when  futhtm.c.  fopen().");
//  }

//
//  /* output the css, headings etc.
//  */
//  if (strstr(gbl_ffnameHTML, "webview") != NULL) {
//    f_fnOutPutTopOfHtmlFile();  // webview version
//  } else {
//    f_fnBIGOutPutTopOfHtmlFile();
//  }
//

  /* 1. read until [beg_topinfo1]  (name)
  */
  for (i=0; ; i++) {
//tr("QDG_1");
    f_docin_get(doclin);
    if (strstr(doclin, "[beg_topinfo1]") != NULL) break;
  }

  /* then save lines until graph until [end_topinfo1] 
  * then put out html 
  */
  for (i=0; ; i++) {
//tr("QDG_2");
    f_docin_get(doclin);
    if (strstr(doclin, "[end_topinfo1]") != NULL) break;

    strcpy(f_arr(i), doclin);
    strcpy(gbl_name_for_fut, f_arr(1));  /* for stress num table at bottom */
    strcpy(gbl_year_for_fut, f_arr(2));  /* for stress num table at bottom */
  }
//ksn(gbl_name_for_fut);
//ksn(gbl_year_for_fut);


//      strcat(string_for_table_only,

//    f_fnBIG_prtlin(
//      "<div id=\"smup_underNAVB\" style=\"position: relative; width: 100%; \"> </div>" ); // NOW IN JS, height is added (navbar * 1.25) 
//



    // put in a container DIV for scorebox plus thumbnail  (brown bg)
    //
    f_fnBIG_prtlin( "<div id=\"divScoreThumb\" class=\"cssScoreThumb\" >"); // put in an container DIV for scorebox plus thumbnail

        // BEGIN  EMPTY SCOREBOX    BEGIN  EMPTY SCOREBOX    BEGIN  EMPTY SCOREBOX    BEGIN  EMPTY SCOREBOX    BEGIN  EMPTY SCOREBOX   
//        f_fnBIG_prtlin( "<div id=\"cydivscore\" class=\"scoreCOcss\" style=\"overflow-x:auto;\">"); // -x for responsive table
        f_fnBIG_prtlin( "<div id=\"cydivscore\"  style=\"overflow-x:auto;\">"); // -x for responsive table
          //
          // NOTE:  in JS, copy html from bottom of this html to here at the top  
          //
        f_fnBIG_prtlin( "</div>");  // id=cydivscore   for responsive div for  EMPTY SCOre table
        //   END  EMPTY SCOREBOX      END  EMPTY SCOREBOX      END  EMPTY SCOREBOX      END  EMPTY SCOREBOX      END  EMPTY SCOREBOX   


        // set up SPACE for a thumbnail of the graph
        //
        f_fnBIG_prtlin( "<div id=\"divNAIL1\" class=\"cssNAIL1\">");   



    f_fnBIG_prtlin( "<span id=\"spanlarge\" style=\"color: #e0e066; font-size: 60%;   \">Click to Enlarge</span>"); 

    // set up SPACE for  the canvas of the graph image
    //
    f_fnBIG_prtlin( "<canvas id=\"thumbCanvas\" class=\"cssTHUcanvas\" >");
    f_fnBIG_prtlin( " Your browser does not support the HTML5 canvas tag.</canvas>");

//    f_fnBIG_prtlin( "</div>");  // id=divScoreThumb class=cssScoreThumb // put in an container DIV for scorebox plus thumbnail



    // set up SPACE for the DATA for the thumbnail of the graph
    //
    //  first 2 lines look like this:  Z is eol
    //   _gbl_thumbnailInfo=[B141*002B041ZB182G002B041Z ...
    //
//    f_fnBIG_prtlin( "<div id=\"divDATAtn\" class=\"cssDATAtn\">"); // set up SPACE for the DATA for the thumbnail of the graph
//    f_fnBIG_prtlin( arg_thumbnailInfo);                             //                  the DATA for the thumbnail of the graph
//    f_fnBIG_prtlin( "</div>");                                      // set up SPACE for the DATA for the thumbnail of the graph

    sprintf(writebuf, "<div id=\"divDATAtn\" class=\"cssDATAtn\">%s</div>", arg_thumbnailInfo);
    f_fnBIG_prtlin( writebuf );

//    f_fnBIG_prtlin( "<span id=\"spanlarge\" style=\"color: #e0e066; font-size: 60%;   \">Click to Enlarge</span>"); 

    f_fnBIG_prtlin( "</div>");  // id=divNAIL1

    // ? end of divNAIL1 should go here
//    f_fnBIG_prtlin( "<br><span style=\"color: cyan;\">TEST   place bbbbb</span><br>"); 
    f_fnBIG_prtlin( "</div>");  // id=divScoreThumb class=cssScoreThumb // put in an container DIV for scorebox plus thumbnail



  /* 2. read until [beg_graph]
   */
  for (i=0; ; i++) {
//tr("QDG_3");
    f_docin_get(doclin);

/*     sfromto(s1, doclin, 1, 11); */
/*     if (strcmp("[beg_graph]", s1) == 0) break; */
    if (strstr(doclin, "[beg_graph]") != NULL) break;
  }
  strcpy(have_we_hit_beg_graph, "YES");



  /* output *ALL*  6-mth  grh+asp
   * */
  gblIsThis1stGrhToOutput = 1;  /* 0 false, 1 true */

//  while (strcmp(have_we_hit_beg_graph, "YES") == 0) {
//    strcpy(have_we_hit_beg_graph, "NO"); 
//
//    if (strstr(gbl_ffnameHTML, "webview") != NULL) {
//      fn_outputGrhAndAspects();  // webview version
//    } else {
//      fn_BIGoutputGrhAndAspects();
//    }
//  }
//
  fn_BIGoutputGrhAndAspects();


//
//  /* FLUSH and CLOSE output HTML file
//  */
//  fflush(Fp_f_HTML_file);
//  if (fclose(Fp_f_HTML_file) == EOF) {
//    ;
////trn("FCLOSE FAILED !!!   #1  ");
//  } else {
//    ;
////trn("FCLOSE SUCCESS !!!  #1  ");
//  };
//

//  return arg_space_for_HTML_fut;
  return(0);

} /* end of make_htm_file(); */



#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
* /*
* *  output "for astroloy buffs" and end html 
* *  
* *  Here we have already hit   [beg_astrobuffs],
* *  so we print the buffs table and bottom line of report
* */
* void fn_output_bot_of_html_file(void) {
*   int i;
* 
* trn(" in fn_output_bot_of_html_file() ");
* 
*   /* read until  [beg_astrobuffs]
*   *
*   */
* 
*   /* 
*   *     --------for astrology buffs--------- 
*   *     sun_10vir47 mar_13can42 nep_09lib28 
*   *     moo_21ari01 jup_21scp15 plu_13leo50 
*   *     mer_16vir24 sat_16leo10 nod_26tau21 
*   *     ven_10vir56 ura_25gem50 mc__08aqu54 
*   *     ------------------------------------
*   */
* 
*   f_fn_prtlin("<table align=center>");
*   f_fn_prtlin("  <col><col><col><col>");
*   f_fn_prtlin("  <tr>");
*   f_fn_prtlin("    <td><tt><span style=\"font-size: 90%;\">");
* 
*   /* read until  [end_astrobuffs]
*   */
*   for (i=0; ; i++) {
*     f_docin_get(doclin);
* 
* /*     sfromto(s1, doclin, 1, 16); */
* /*     if (strcmp("[end_astrobuffs]", s1) == 0) break; */
*     if (strstr(doclin, "[end_astrobuffs]") != NULL) break;
*     
*     n = sprintf(writebuf, "        %s%s\n", "<br>", doclin);
*     f_fn_prtlin(writebuf);
*   }
* 
*   f_fn_prtlin("     </span></tt></td>");
*   f_fn_prtlin("  </tr>");
*   f_fn_prtlin("</table>");
* 
* 
* /*   f_fn_prtlin("\n\n<h5>This report is for entertainment purposes only.</h5>\n"); */
* 
*   f_fn_prtlin("<h4><span style=\"background-color:#FFBAC7;\">&nbsp&nbsp&nbsp&nbsp&nbsp  This report is for entertainment purposes only.  &nbsp&nbsp&nbsp&nbsp&nbsp</span></h4>");
* 
*   f_fn_prtlin("\n</body>\n");
*   f_fn_prtlin("</html>");
* 
* } /* end of fn_output_bot_of_html_file() */
#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/







//
//void f_fnOutPutTopOfHtmlFile(void)
//{  // webview version
//  int i;
//
///* trn("in f_fnOutPutTopOfHtmlFile()");  */
//
//  /* 1. read until [beg_topinfo1]  (name)
//  */
//  for (i=0; ; i++) {
//    f_docin_get(doclin);
//    if (strstr(doclin, "[beg_topinfo1]") != NULL) break;
//  }
//
//  /* then save lines until graph until [end_topinfo1] 
//  * then put out html 
//  */
//  for (i=0; ; i++) {
//    f_docin_get(doclin);
//    if (strstr(doclin, "[end_topinfo1]") != NULL) break;
//
//    strcpy(f_arr(i), doclin);
//  }
//
//  /* trn("------------------------------------");
//  * for (k=0; k < i; k++) ksn(arr(k));
//  * trn("------------------------------------");
//  */
//
//
//
///*   f_fn_prtlin( "<!doctype html public \"-//w3c//dtd html 4.0 transitional//en\">"); */
///*   f_fn_prtlin( "  \"http://www.w3.org/TR/html4/strict.dtd\">"); */
///*   f_fn_prtlin( "  \"http://www.w3.org/TR/html4/loose.dtd\">"); */
//
///*   at end, change to STRICT  (maybe) */
//  f_fn_prtlin( "<!doctype html public \"-//w3c//dtd html 4.01 transitional//en\" ");
//  f_fn_prtlin( "  \"http://www.w3.org/TR/html4/loose.dtd\">");
//
//  f_fn_prtlin( "<html>");
//  f_fn_prtlin( "\n<head>");
//
//  /* IT TURNS OUT this <title> is used as the default filename when the html report
//  *  is emailed, you open it, and do "Save As".
//  *  Therefore, used the "real" file name with no advertising.  Rats.
//  */
//
///*   sprintf(writebuf, "  <title>%s %s Calendar Year produced by iPhone/iPad app named %s.</title>",arr(1),arr(2), APP_NAME); * lance 2013 * */
///*   sprintf(writebuf, "  <title>%s %s Calendar Year produced by iPhone app %s.</title>",arr(1),arr(2), APP_NAME);  */
//
//
//  /* if HTML filename, gbl_ffnameHTML, has any slashes, grab the basename
//  */
////  char myBaseName[256], *myptr;
////  if (sfind(gbl_ffnameHTML, '/')) {
////    myptr = strrchr(gbl_ffnameHTML, '/');
////    strcpy(myBaseName, myptr + 1);
////  } else {
////    strcpy(myBaseName, gbl_ffnameHTML);
////  }
////  sprintf(writebuf, "  <title>%s</title>", myBaseName);
//
//
//  f_fn_prtlin(writebuf);
//  
//  /* HEAD  META
//  */
//  sprintf(writebuf, "  <meta name=\"description\" content=\"Calendar Year for Person produced by iPhone App %s\"> ", APP_NAME);
//  f_fn_prtlin( writebuf);
//
//
//  f_fn_prtlin( "  <meta http-equiv=\"Content-Type\" content=\"text/html\"; charset=\"iso-8859-1\">"); 
///*   f_fn_prtlin( "  <meta name=\"Author\" content=\"Author goes here\">"); */
//
//
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"GMCR,group,member,astrology,future,past,calendar,year,compatibility,personality\"> "); */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"measure,group,member,best,match,calendar,year,passionate,personality\"> "); */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"women,woman,BFF,astrology,compatibility,group,best,match,personality,calendar,year,stress\"> "); */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,astrology,compatibility,group,best,match,personality,stress,calendar,year\"> ");  * 96 chars * */
//  f_fn_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,me,compatibility,group,best,match,personality,stress,calendar,year\"> ");  /* 89 chars */
//
//
//
//  /* get rid of CHROME translate "this page is in Galician" 
//  * do you want to translate?
//  */
//  f_fn_prtlin("  <meta name=\"google\" content=\"notranslate\">");
///*   f_fn_prtlin("  <meta http-equiv=\"Content-Language\" content=\"en\" />"); */
//  f_fn_prtlin("  <meta http-equiv=\"Content-Language\" content=\"en\">");
//
//
//  /* Using the Viewport Meta Tag  (in iOS webView)
//  * https://developer.apple.com/library/safari/documentation/AppleApplications/Reference/SafariWebContent/UsingtheViewport/UsingtheViewport.html#//apple_ref/doc/uid/TP40006509-SW25
//  *
//  * For example, TO SET THE VIEWPORT WIDTH TO THE WIDTH OF THE DEVICE, add this to your HTML file:
//  * <meta name="viewport" content="width=device-width"> 
//  * To set the initial scale to 1.0, add this to your HTML file:
//  * <meta name="viewport" content="initial-scale=1.0"> 
//  * To set the initial scale and to turn off user scaling, add this to your HTML file:
//  * <meta name="viewport" content="initial-scale=2.3, user-scalable=no">
//  */
///*   f_fn_prtlin("  <meta name=\"viewport\" content=\"width=device-width\" />"); */
//  f_fn_prtlin("  <meta name=\"viewport\" content=\"width=device-width\">");
//  /*   f_fn_prtlin("  <meta name=\"viewport\" content=\"initial-scale=0.45\">"); */
///*   f_fn_prtlin("  <meta name=\"viewport\" content=\"initial-scale=0.27\">"); */
///*   f_fn_prtlin(" <meta name=\"viewport\" content=\"initial-scale=0.28, user-scalable=no\">"); */
//
//  f_fn_prtlin("   <meta name = \"format-detection\" content = \"telephone=no\">");
//
//
//
//
//  /* HEAD   STYLE/CSS
//  */
//  f_fn_prtlin( "\n  <style type=\"text/css\">");
//  f_fn_prtlin( "    @media print { PRE {  page-break-inside:avoid; } }");
//
//  f_fn_prtlin( "    BODY {");
//
///*  f_fn_prtlin( "      background-color: #F5EFCF;"); */
//  f_fn_prtlin( "      background-color: #f7ebd1;");
//
///*   f_fn_prtlin( "      font-family: Trebuchet MS, Arial, Verdana, sans-serif;"); */
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      font-size:   medium;");
//  f_fn_prtlin( "      font-weight: normal;");
//  f_fn_prtlin( "      text-align:  center;");
///*   f_fn_prtlin( "    <!-- "); */
///*   f_fn_prtlin( "      background-image: url('mkgif1g.gif');"); */
///*   f_fn_prtlin( "    --> "); */
//  f_fn_prtlin( "    }");
//
//
///*   f_fn_prtlin( "    H1 { font-size: 137%; font-weight: bold;   line-height: 95%; text-align: center;}"); */
///*   f_fn_prtlin( "    H1 { font-size: 300%; font-weight: bold;   line-height: 100%; text-align: center;}"); */
///*   f_fn_prtlin( "    H2 { font-size: 137%;                      line-height: 25%; text-align: center;}"); */
///*   f_fn_prtlin( "    H3 { font-size: 110%; font-weight: normal; line-height: 30%; text-align: center;}"); */
///*   f_fn_prtlin( "    H4 { font-size:  75%; font-weight: bold;   line-height: 30%; text-align: center;}"); */
///*   f_fn_prtlin( "    H5 { font-size:  70%; font-weight: normal; line-height: 30%; text-align: center;}"); */
//
//
//
//
//
//  f_fn_prtlin( "@media screen and (max-device-width: 500px) {");   // CSS for SMALL screen device
//
//  f_fn_prtlin( "    PRE {");
////  f_fn_prtlin( "      margin-top: 0.5em;");
///*   f_fn_prtlin( "      border: 0;"); */
///*   f_fn_prtlin( "      padding: 0;"); */
////  f_fn_prtlin( "      margin-top: 0.1em;");
///*   f_fn_prtlin( "      margin-bottom: 0.1em;"); */
///*   f_fn_prtlin( "      margin-left: 0.1em;"); */
///*   f_fn_prtlin( "      margin-right: 0.1em;"); */
////  f_fn_prtlin( "      font-size:   90%;");
//  //f_fn_prtlin( "      font-size:   96.5%;");
//
//  //f_fn_prtlin( "      font-size:   109%;");
//  f_fn_prtlin( "      font-size:   95%;");
//
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      font-weight: normal;");
//
//  f_fn_prtlin( "      line-height: 70%;");
////  f_fn_prtlin( "      letter-spacing: -1px;");
//
////  f_fn_prtlin( "      line-height: 90%;");
///*   f_fn_prtlin( "      line-height: 30%;"); */
//  f_fn_prtlin( "    }");
///*   f_fn_prtlin( "div.spacer {"); */
///*   f_fn_prtlin( "height:2px;"); */
///*   f_fn_prtlin( "width:10%;"); */
///*   f_fn_prtlin( "color: #696969;"); */
///*   f_fn_prtlin( "background-color: #708090;"); */
///*   f_fn_prtlin( "margin: 0 0;"); */
///*   f_fn_prtlin( "padding: 0 0;"); */
///*   f_fn_prtlin( "border: 0;"); */
///*   f_fn_prtlin( "font: 1px/1px;"); */
///*   f_fn_prtlin( "}"); */
///*   f_fn_prtlin( "      margin-top: 0;"); */
///*   f_fn_prtlin( "      margin-bottom: 0;"); */
///*   f_fn_prtlin( "      margin-left: 0;"); */
///*   f_fn_prtlin( "      margin-right: 0;"); */
//
//  f_fn_prtlin( "    .myTitle {");              // webview version
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 0.5em;");
//  f_fn_prtlin( "      margin-left: 50%;");
//
////  f_fn_prtlin( "      text-align: center;");      // GOLD order #1
////  f_fn_prtlin( "      text-align: left;");      // GOLD order #1
//     // are putting spaces in code to center
//  //f_fn_prtlin( "      width: 300%;");             // GOLD order #2
//  f_fn_prtlin( "      width: 100%;");             // GOLD order
//  f_fn_prtlin( "      font-size: 300%;");         // GOLD order #3
//  f_fn_prtlin( "      font-weight: bold;"); 
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
///*   f_fn_prtlin( "margin: 0 0;"); */
///*   f_fn_prtlin( "margin: 0;"); */
///*   f_fn_prtlin( "      padding: 0 0;"); */
///*   f_fn_prtlin( "      border: 0;"); */
///*   f_fn_prtlin( "      border-style: solid;"); */
///*   f_fn_prtlin( "      border-color: black;"); */
///*   f_fn_prtlin( "      border-width: 2px;"); */
//
//  f_fn_prtlin( "    }");
//
//  f_fn_prtlin( "    .explain {");
//  f_fn_prtlin( "      margin-top: 1.4em;");
//  f_fn_prtlin( "      margin-bottom: 0.0em;");
//  //f_fn_prtlin( "      width: 300%;");
//  f_fn_prtlin( "      width: 100%;");
///*   f_fn_prtlin( "      text-align: center;");  */
//     // are putting spaces in code to center
//  f_fn_prtlin( "      line-height: 140%;");
//  f_fn_prtlin( "      text-align: left;"); 
//
//  //f_fn_prtlin( "      font-size: 120%;"); 
//  f_fn_prtlin( "      font-size: 180%;"); 
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "    }");
//
//  f_fn_prtlin( "    .fromtodates {");
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 0.1em;");
//  //f_fn_prtlin( "      width: 250%;");
//  f_fn_prtlin( "      width: 100%;");
//  f_fn_prtlin( "      text-align: center;"); 
///*   f_fn_prtlin( "      text-align: left;");  */
//  f_fn_prtlin( "      line-height: 145%;");
//  //f_fn_prtlin( "      font-size: 95%;"); 
//  f_fn_prtlin( "      font-size: 150%;"); 
//  f_fn_prtlin( "      font-weight: bold;"); 
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "    }");
//
//  f_fn_prtlin( "    .aspecttext {");
//  f_fn_prtlin("   white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 2.0em;");
///*   f_fn_prtlin( "      margin-left: 1.0em;"); */
///*   f_fn_prtlin( "      margin-right: 1.0em;"); */
///*   f_fn_prtlin( "      width: 600%;"); */
//  f_fn_prtlin( "      width: 100%;");
///*   f_fn_prtlin( "      text-align: center;");  */
//  f_fn_prtlin( "      text-align: left;"); 
///*   f_fn_prtlin( "      font-size: 200%;");  */
///*   f_fn_prtlin( "      font-size: 182%;");  */
//  f_fn_prtlin( "      font-size: 180%;"); 
//  f_fn_prtlin( "      line-height: 120%;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
///*   f_fn_prtlin( "      padding-left: 2%;"); */
///*   f_fn_prtlin( "      padding-right:10%;"); */
//  f_fn_prtlin( "      margin-left: 0.2em;");
//  f_fn_prtlin( "      margin-right: 0.5em;");
///*   f_fn_prtlin( "      border-right:3em;"); */
///*   f_fn_prtlin( "      padding-right:3em;"); */
///*   f_fn_prtlin( "      margin-right: 9em;"); */
//  f_fn_prtlin( "    }");
//
//
//
///*   f_fn_prtlin( "      display: inline-block;"); */
///*   f_fn_prtlin( "      border-style: solid;"); */
///*   f_fn_prtlin( "      border-color: #e4dfae;"); */
///*   f_fn_prtlin( "      border-width: 5px;"); */
//  f_fn_prtlin( "    .checkoutbox {");
///*   f_fn_prtlin( "      text-align: left;"); */
//
//  //f_fn_prtlin( "      margin-left: 30%;");
//  //f_fn_prtlin( "      font-size: 140%;");  
//
//  //f_fn_prtlin( "      width: 100%;");
//
//  f_fn_prtlin( "      margin-top: 0.1em;");
//  
//  //f_fn_prtlin( "      margin-left: 10%;");
//  f_fn_prtlin( "      margin-left: 5%;");
//  f_fn_prtlin( "      font-size: 1.7em;");  
//
//  f_fn_prtlin( "      display: inline-block;");
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      line-height: 130%;");
///*   f_fn_prtlin( "      font-size: 75%;"); */
//  f_fn_prtlin( "    }");
//
//  f_fn_prtlin( "    .willpower {");
//  //f_fn_prtlin( "      margin-left: 15%;");
//  //f_fn_prtlin( "      font-size: 125%;"); 
//
//  //f_fn_prtlin( "      margin-top: 0.7em;");
//  f_fn_prtlin( "      margin-top: 0.2em;");
//  f_fn_prtlin( "      margin-left: 35%;");
//  f_fn_prtlin( "      font-size: 1.7em;"); 
//
//  f_fn_prtlin( "      display: inline-block;");
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      line-height: 120%;");
///*   f_fn_prtlin( "      font-size: 75%;"); */
//  f_fn_prtlin( "    }");
//
//
//  // from perhtm.c
//  f_fn_prtlin( "    PRE.appBy {");
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "      margin-left: 45%;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  //f_fn_prtlin( "      font-size: 130%;");
//  f_fn_prtlin( "      font-size: 1.5em;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    PRE.entertainment {");
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "      margin-left: 25%;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      color:#FF0000;");
//  //f_fn_prtlin( "      font-size: 130%;"); 
//  f_fn_prtlin( "      font-size: 1.5em;"); 
//  f_fn_prtlin( "      font-weight: bold;"); 
//  f_fn_prtlin( "    }");
//
//
//  // color for name, yr, "first 6 months" title line
///*   f_fn_prtlin( "    .bgy {background-color:#ffff00;}"); */
///*   f_fn_prtlin( "    .bgy {background-color:#fcfc70;}"); */
///*   f_fn_prtlin( "      background-color: #f7ebd1;}"); */
//  f_fn_prtlin( "    .bgy { background-color:#f7ebd1;");
//
///*   f_fn_prtlin("   white-space: pre ; displayX: block; unicodeX-bidi: Xembed"); */
//  f_fn_prtlin("   white-space: pre  ; ");
///*   f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;"); */
///*   f_fn_prtlin( "      font-weight: normal;"); */
///*   f_fn_prtlin( "      font-size:   75%;"); */
///*   f_fn_prtlin( "      line-height: 70%;"); */
///*   f_fn_prtlin( "      margin:0 auto;"); */
//  f_fn_prtlin( "    }");
//
//
//  f_fn_prtlin( "    P { ");
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      width: auto;");
//  f_fn_prtlin( "      font-size:   80%;");
//  f_fn_prtlin( "      margin-top: 0;");
//  f_fn_prtlin( "      margin-bottom: 0;");
//  f_fn_prtlin( "      margin-left: auto;");
//  f_fn_prtlin( "      margin-right:auto;");
///*   f_fn_prtlin( "      padding-left: 5%;"); */
///*   f_fn_prtlin( "      padding-right:5%;"); */
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table {");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      font-size: 120%;");
//  f_fn_prtlin( "    }");
///* for table: */
///*       border: 2px solid black; */
///*       cellspacing: 0; */
///*       border-top: 0; */
///*       border-bottom: 0; */
//  f_fn_prtlin( "    table.center {");
//  f_fn_prtlin( "      margin-left:auto;");
//  f_fn_prtlin( "      margin-right:auto;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    TD {");
//  f_fn_prtlin( "      white-space: nowrap;");
//  f_fn_prtlin( "      padding: 0;");
//  f_fn_prtlin( "    }");
//
//    
///*   f_fn_prtlin("    .cGre        { background-color:#e1fdc3; }");
//*   f_fn_prtlin("    .cGr2        { background-color:#d0fda0; }");
//*   f_fn_prtlin("    .cRed        { background-color:#ffbac1; }");
//*   f_fn_prtlin("    .cRe2        { background-color:#ff596a; }");
//*/
//
///*   p_fn_prtlin( "    .cGr2        { background-color:#d0fda0; }"); */
///*   f_fn_prtlin( "    .cGr2        { background-color:#8bfd87; }"); */
///*   f_fn_prtlin( "    .cGr2        { background-color:#66ff33; }"); */
//
///*   p_fn_prtlin( "    .cGre        { background-color:#e1fdc3; }"); */
///*   f_fn_prtlin( "    .cGre        { background-color:#ccffb9; }"); */
///*   f_fn_prtlin( "    .cGre        { background-color:#84ff98; }"); */
//
///*   p_fn_prtlin( "    .cRed        { background-color:#ffd9d9; }"); */
///*   f_fn_prtlin( "    .cRed        { background-color:#ffcccc; }"); */
///*   f_fn_prtlin( "    .cRed        { background-color:#ff98a8; }"); */
//
///*   p_fn_prtlin( "    .cRe2        { background-color:#fcb9b9; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#fc8888; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#ff6094; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#ff3366; }"); */
//
//  // take away bold   "o" = ordinary
//  //
//  f_fn_prtlin("    .oGr2        { background-color:#80ff40; }");
//  f_fn_prtlin("    .oGre        { background-color:#c0ffc0; }");
//  f_fn_prtlin("    .oNeu        { background-color:#edebd8; }");
//  f_fn_prtlin("    .oRed        { background-color:#ffb5c9; }");
//  f_fn_prtlin("    .oRe2        { background-color:#ff7ba3; }");
//
//
////  f_fn_prtlin( "    .cGr2        { background-color:#66ff33; font-weight: bold; ");
//  f_fn_prtlin( "    .cGr2        { background-color:#80ff40; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin("    }");
///*   f_fn_prtlin( "    .cGre        { background-color:#84ff98; }"); */
////  f_fn_prtlin( "    .cGre        { background-color:#a8ff98; font-weight: bold; ");
//  f_fn_prtlin( "    .cGre        { background-color:#c0ffc0; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ;font-weight: bold; ");
///*   f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;"); */
///*   f_fn_prtlin( "      font-weight: normal;"); */
///*   f_fn_prtlin( "      font-size:   75%;"); */
///*   f_fn_prtlin( "      line-height: 70%;"); */
///*   f_fn_prtlin( "      margin:0 auto;"); */
//  f_fn_prtlin("    }");
////  f_fn_prtlin( "    .cRed        { background-color:#ff98a8; font-weight: bold; ");
//  f_fn_prtlin( "    .cRed        { background-color:#ffb5c9; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin("    }");
////  f_fn_prtlin( "    .cRe2        { background-color:#ff4477; font-weight: bold; ");
//  f_fn_prtlin( "    .cRe2        { background-color:#ff7ba3; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin("    }");
//
//
//  f_fn_prtlin("    .row4        { background-color:#f8f0c0; }");
//
///*   f_fn_prtlin("    .cNeu        { background-color:#e1ddc3; }"); */
////  f_fn_prtlin("    .cNeu        { background-color:#e5e2c7; font-weight: bold; ");
//  f_fn_prtlin("    .cNeu        { background-color:#edebd8; font-weight: bold; ");
////  f_fn_prtlin("    .cNeu        { background-color:#f5f4ea; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ; ");
//  f_fn_prtlin("    }");
//
//  f_fn_prtlin("    .cSky        { background-color:#3f3ffa; font-weight: bold; ");
//  f_fn_prtlin("   white-space: pre  ; ");
///*   f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;"); */
///*   f_fn_prtlin( "      font-weight: normal;"); */
///*   f_fn_prtlin( "      font-size:   75%;"); */
///*   f_fn_prtlin( "      line-height: 70%;"); */
///*   f_fn_prtlin( "      margin:0 auto;"); */
//  f_fn_prtlin("    }");
//
//
//
//  f_fn_prtlin( "   .star        { color:#f7ebd1; font-weight: bold; }");
///*   f_fn_prtlin( "   .star      {  "); */
///*   f_fn_prtlin("   white-space: pre ; "); */
///*   f_fn_prtlin("    }"); */
///*   f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;"); */
///*   f_fn_prtlin( "      font-weight: normal;"); */
///*   f_fn_prtlin( "      font-size:   75%;"); */
///*   f_fn_prtlin( "      line-height: 70%;"); */
///*   f_fn_prtlin( "      margin:0 auto;"); */
//
//
//
//  //f_fn_prtlin("    .cNam        { color:#3f3ffa;");
//  f_fn_prtlin("    .cNam        {               ");   // no blue name
//  f_fn_prtlin("                   background-color: #F7ebd1;");
//  f_fn_prtlin("                   font-size: 133%;");
//  f_fn_prtlin("    }");
//
//
//  f_fn_prtlin( "    table.trait {");
//
///*   f_fn_prtlin( "      margin-left:auto;"); */
///*   f_fn_prtlin( "      margin-right:auto;"); */
///*   f_fn_prtlin( "      margin-left: 7em;"); */
///*   f_fn_prtlin( "      text-align: left;"); */
//
///*   f_fn_prtlin( "      margin-left: 70%;"); */
//  f_fn_prtlin( "      margin-left: 60%;");
//
//  f_fn_prtlin( "      margin-top: 0.1em;");
//
//  //f_fn_prtlin( "      margin-left: 50%;");
//  //f_fn_prtlin( "      margin-right:50%;");
///*   f_fn_prtlin( "      margin-left: 6em;"); */
//
///*   f_fn_prtlin( "      margin-left: 6em;"); */
//
//
//  //f_fn_prtlin( "      font-size: 185%;"); 
//  f_fn_prtlin( "      font-size: 200%;");  
///*   f_fn_prtlin( "      font-size: 100%;"); */
//
//  f_fn_prtlin( "      white-space: pre;");
///*   f_fn_prtlin( "      margin-left: auto;"); */
///*   f_fn_prtlin( "      margin-right:auto;"); */
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait td {");
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      white-space: pre;");
///*   f_fn_prtlin( "      font-size: 75%;"); */
//  f_fn_prtlin( "      font-size: 90%;");
//  f_fn_prtlin( "      text-align: left;");
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      padding-left: 10px; ");
//  f_fn_prtlin( "      padding-right: 10px; ");
//  f_fn_prtlin( "      padding-top: 2px; ");
//  f_fn_prtlin( "      padding-bottom: 2px; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait th{");
///*   f_fn_prtlin( "      font-family: Trebuchet MS, Arial, Verdana, sans-serif;"); */
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
///*   f_fn_prtlin( "      font-size: 75%;"); */
//  f_fn_prtlin( "      font-size: 90%;");
//  f_fn_prtlin( "      padding: 10px; ");
//
///*   f_fn_prtlin( "      background-color: #e1fdc3 ;"); */
//  f_fn_prtlin( "      background-color: #fcfce0;");
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      text-align: center;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait       td { text-align: left; }");
//  f_fn_prtlin( "    table.trait    td+td { text-align: right; }");
//  f_fn_prtlin( "    table.trait td+td+td { text-align: left; }");
//
//  f_fn_prtlin( "}"); // end of  @media screen and (max-device-width: 500px)  // CSS for SMALL screen device
//
//
//
//
//  f_fn_prtlin( "@media screen and (min-device-width: 501px) {  "); // CSS for BIG SREEN  tablet, iPad, PC, Mac
//  f_fn_prtlin( "    PRE {");
//  f_fn_prtlin( "      font-size:   80%;");
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      font-weight: normal;");
//  f_fn_prtlin( "      line-height: 70%;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .myTitle {");
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 0.5em;");
//  f_fn_prtlin( "      width: 100%;");
//  f_fn_prtlin( "      font-size: 300%;");
//  f_fn_prtlin( "      font-weight: bold;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .explain {");
//  f_fn_prtlin( "      margin-top: 1.4em;");
//  f_fn_prtlin( "      margin-bottom: 0.0em;");
//  f_fn_prtlin( "      width: 100%;");
//  f_fn_prtlin( "      line-height: 140%;");
///*   f_fn_prtlin( "      font-size: 1.25em;"); */
//  f_fn_prtlin( "      font-size: 1.0em;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .fromtodates {");
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 0.1em;");
//  f_fn_prtlin( "      width: 100%;");
//  f_fn_prtlin( "      text-align: center;");
//  f_fn_prtlin( "      line-height: 145%;");
//  f_fn_prtlin( "      font-size: 1.0em;");
//  f_fn_prtlin( "      font-weight: bold;");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .aspecttext {");
//  f_fn_prtlin( "   white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "      margin-top: 0.5em;");
//  f_fn_prtlin( "      margin-bottom: 2.0em;");
//  f_fn_prtlin( "      width: 100%;");
//
///*   f_fn_prtlin( "      font-size: 1.2em;"); */
//  f_fn_prtlin( "      font-size: 1.0em;");
///*   f_fn_prtlin( "      line-height: 120%;"); */
//  f_fn_prtlin( "      line-height: 150%;");
//
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      margin-left: 0.2em;");
//  f_fn_prtlin( "      margin-right: 0.5em;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .checkoutbox {");
//  f_fn_prtlin( "      margin-top: 0.1em;");
///*   f_fn_prtlin( "      font-size: 1.0em;"); */
//  f_fn_prtlin( "      font-size: 0.9em;");
//  f_fn_prtlin( "      display: inline-block;");
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      line-height: 130%;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .willpower {");
//  f_fn_prtlin( "      margin-top: 0.2em;");
///*   f_fn_prtlin( "      font-size: 1.0em;"); */
//  f_fn_prtlin( "      font-size: 0.9em;");
//  f_fn_prtlin( "      display: inline-block;");
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      line-height: 120%;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    PRE.appBy {");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      font-size: 0.9em;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    PRE.entertainment {");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
//  f_fn_prtlin( "      color:#FF0000;");
//  f_fn_prtlin( "      font-size: 0.9em;");
//  f_fn_prtlin( "      font-weight: bold;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .bgy { background-color:#f7ebd1;");
//  f_fn_prtlin( "   white-space: pre  ; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    P { ");
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      width: auto;");
//  f_fn_prtlin( "      font-size:   80%;");
//  f_fn_prtlin( "      margin-top: 0;");
//  f_fn_prtlin( "      margin-bottom: 0;");
//  f_fn_prtlin( "      margin-left: auto;");
//  f_fn_prtlin( "      margin-right:auto;");
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table {");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      font-size: 120%;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.center {");
//  f_fn_prtlin( "      margin-left:auto;");
//  f_fn_prtlin( "      margin-right:auto;");
//  f_fn_prtlin( "      font-size: 1.1em;");
//  f_fn_prtlin( "      line-height: 1.4em");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    TD {");
//  f_fn_prtlin( "      white-space: nowrap;");
//  f_fn_prtlin( "      padding: 0;");
//  f_fn_prtlin( "    }");
////  f_fn_prtlin( "    .cGr2        { background-color:#66ff33; font-weight: bold; ");
//  f_fn_prtlin( "    .cGr2        { background-color:#80ff40; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin( "    }");
////  f_fn_prtlin( "    .cGre        { background-color:#a8ff98; font-weight: bold; ");
//  f_fn_prtlin( "    .cGre        { background-color:#c0ffc0; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ;font-weight: bold; ");
//  f_fn_prtlin( "    }");
////  f_fn_prtlin( "    .cRed        { background-color:#ff98a8; font-weight: bold; ");
//  f_fn_prtlin( "    .cRed        { background-color:#ffb5c9; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin( "    }");
////  f_fn_prtlin( "    .cRe2        { background-color:#ff4477; font-weight: bold; ");
//  f_fn_prtlin( "    .cRe2        { background-color:#ff7ba3; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ; font-weight: bold; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .row4        { background-color:#f8f0c0; }");
////  f_fn_prtlin( "    .cNeu        { background-color:#e5e2c7; font-weight: bold; ");
//  f_fn_prtlin( "    .cNeu        { background-color:#edebd8; font-weight: bold; ");
////  f_fn_prtlin( "    .cNeu        { background-color:#f5f4ea; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    .cSky        { background-color:#3f3ffa; font-weight: bold; ");
//  f_fn_prtlin( "   white-space: pre  ; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "   .star        { color:#f7ebd1; font-weight: bold; }");
//  f_fn_prtlin( "    .cNam        {               ");
//  f_fn_prtlin( "                   background-color: #F7ebd1;");
//  f_fn_prtlin( "                   font-size: 133%;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait {");
//  f_fn_prtlin( "      margin-left:auto;");
//  f_fn_prtlin( "      margin-right:auto;");
//  f_fn_prtlin( "      margin-top: 0.1em;");
///*   f_fn_prtlin( "      font-size: 1.4em;"); */
//  f_fn_prtlin( "      font-size: 1.2em;");
//  f_fn_prtlin( "      white-space: pre;");
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait td {");
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      white-space: pre;");
//  f_fn_prtlin( "      font-size: 90%;");
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      padding-left: 10px; ");
//  f_fn_prtlin( "      padding-right: 10px; ");
//  f_fn_prtlin( "      padding-top: 2px; ");
//  f_fn_prtlin( "      padding-bottom: 2px; ");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait th{");
//  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "      font-size: 90%;");
//  f_fn_prtlin( "      padding: 10px; ");
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      text-align: center;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "}    "); // END of   @media screen and (min-device-width: 501px)CSS for BIG SREEN  tablet,iPad,PC,Mac
//
//
//
//
//  f_fn_prtlin( "  </style>");
//
///* from p */
///*   f_fn_prtlin( "      margin-left: 20%;"); */
///*   f_fn_prtlin( "      margin-right:20%;"); */
///*   f_fn_prtlin( "      text-align: left;"); */
//
///*   f_fn_prtlin( "    <!-- "); */
///*   f_fn_prtlin( "    PRE {line-height: 68%}; "); */
///*   f_fn_prtlin( "    P {margin-left:10%; margin-right:10%}"); */
///*   f_fn_prtlin( "    --> "); */
//
///* put in favicon */
//f_fn_prtlin("<link href=\"data:image/x-icon;base64,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\" rel=\"icon\" type=\"image/x-icon\" />");
//
//  f_fn_prtlin( "</head>");
//  f_fn_prtlin( " ");
//  f_fn_prtlin("\n<body>");
//
///*   f_fn_prtlin( "<body background=\"file:///mkgif1g.gif\">"); */
///*   f_fn_prtlin( "<body background=\"file:///C/USR/RK/html/mkgif1g.gif\">"); */
//
//  /* a year in the life header output here */
//
//#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
////   sprintf(writebuf, "\n  <h1>%s</h1>", f_arr(0));
////   f_fn_prtlin(writebuf);
//// 
//// b(2);
//// 
//// /*  <h1><center>A Year in the Life</center></h1>
//// *   <h2><center>of Fred&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<em style="font-size:137%;">2013</em></center></h2>
//// */
//// /*   sprintf(writebuf, "\n  <h2><center>of %s</center></h2>", arr(1)); * Fred * */
////  
//// /*   GOOD-|<span style="background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>| */
//// 
////   sprintf(writebuf, "\n <h2>of %s&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<span style=\"font-size:115%%;\">%s</span><br></h2>", arr(1), arr(2) ); /* of Fred     2013 * */
////   f_fn_prtlin(writebuf);
//#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/
//
///*   n = sprintf(p,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp %s &nbsp&nbsp<span style=\"font-size: 80%%;\">of %s</span> &nbsp&nbsp <span style=\"font-size:115%%;\"> %s </span><br></h1>",
//*       arr(0), arr(1), arr(2)
//*   );
//*/
///*   n = sprintf(p,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp %s of %s &nbsp&nbsp&nbsp %s <br></h1>",
//*       arr(0), arr(1), arr(2)
//*   );
//*/
//
///*   n = sprintf(writebuf,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp Calendar Year &nbsp %s <br></h1>",
//*     arr(2)
//*   );
//*   f_fn_prtlin(writebuf);
//*   n = sprintf(writebuf,
//*     "<h2>&nbsp&nbsp&nbsp&nbsp in the life of %s<br></h2>",
//*     arr(1)
//*   );
//*   f_fn_prtlin(writebuf);
//*/
//
///*     "<h1>&nbsp&nbsp&nbsp&nbsp Calendar Year %s for %s<br></h1>", */
//
//
//  strcpy(gbl_name_for_fut, f_arr(1));  /* for stress num table at bottom */
//  strcpy(gbl_year_for_fut, f_arr(2));  /* for stress num table at bottom */
///*   strcpy(gbl_person_name, arr(1)); */
//
///*   f_fn_prtlin("<div><br></div>"); */
//
////  n = sprintf(writebuf,
////    "<h1>Calendar Year %s for <span class=\"cNam\">%s&nbsp&nbsp </span><br></h1>",
////    arr(2), arr(1)
////  );
////  f_fn_prtlin(writebuf);
//
//
//// 20160126   no more title in webview
////
/////*   f_fn_prtlin("<div class=\"spacer\"></div>"); */
/////*   f_fn_prtlin("<pre class=\"spacer\" class=\"myTitle\">"); */
////  f_fn_prtlin("<pre class=\"myTitle\">");
////  gblWeAreInPREblockContent = 1; /* 1 = yes, 0 = no */
////
/////*   sprintf(writebuf, "Calendar Year %s",  arr(2) ); */
/////*   f_fn_prtlin(writebuf); */
////
////  // want 5 sp left margin
////  // then max 15 char name centred in 15 char field
////  // extra sp on left
////  long namelen1 = strlen(gbl_name_for_fut);
////  char mynam[32];
////  strcpy(mynam, gbl_name_for_fut);
////  char char15toprint[32];
////       if (namelen1 ==  1) sprintf(char15toprint, "       %s       ", mynam); 
////  else if (namelen1 ==  2) sprintf(char15toprint, "       %s      ", mynam); 
////  else if (namelen1 ==  3) sprintf(char15toprint, "      %s      ", mynam);
////  else if (namelen1 ==  4) sprintf(char15toprint, "      %s     ", mynam); 
////  else if (namelen1 ==  5) sprintf(char15toprint, "     %s     ", mynam); 
////  else if (namelen1 ==  6) sprintf(char15toprint, "     %s    ", mynam); 
////  else if (namelen1 ==  7) sprintf(char15toprint, "    %s    ", mynam); 
////  else if (namelen1 ==  8) sprintf(char15toprint, "    %s   ", mynam); 
////  else if (namelen1 ==  9) sprintf(char15toprint, "   %s   ", mynam); 
////  else if (namelen1 == 10) sprintf(char15toprint, "   %s  ", mynam); 
////  else if (namelen1 == 11) sprintf(char15toprint, "  %s  ", mynam); 
////  else if (namelen1 == 12) sprintf(char15toprint, "  %s ", mynam); 
////  else if (namelen1 == 13) sprintf(char15toprint, " %s ", mynam); 
////  else if (namelen1 == 14) sprintf(char15toprint, " %s", mynam); 
////  else if (namelen1 == 15) sprintf(char15toprint, "%s", mynam); 
////  else                    sprintf(char15toprint,"%s", mynam);
////
////  //  sprintf(writebuf, "     %s", arr(1) );     // just name
////  //sprintf(writebuf, "     %s", char15toprint );  // just name
////  sprintf(writebuf, "%s %s", gbl_year_for_fut, char15toprint );  // year todo  AND  name
////
////  f_fn_prtlin(writebuf);
////  gblWeAreInPREblockContent = 0; 
////  f_fn_prtlin("</pre>");
/////*   f_fn_prtlin("<div class=\"spacer\"></div>"); */
/////*   f_fn_prtlin("</pre></div>"); */
////
////
//// 20160126   no more title in webview
//
//
//
//
///*   f_fn_prtlin(" "); */
//
///*   sprintf(writebuf, "\n  <h3><center>%s</center></h1>", arr(2)); * 2013 *
//*   f_fn_prtlin(writebuf);
//*/
//
//}  /* end of f_fnOutPutTopOfHtmlFile();   comment= weview version */
//








//
//void fn_outputGrhAndAspects(void)  // webview
//{
//  int i;
//  int have_printed_STRESS_line_already;
//  int have_printed_OMG_line_already;
///*   char myLastLine[8192]; */
//  int num_OMG_printed;
//
///* trn(" in fn_outputGrhAndAspects() "); */
//
//  /* put white space before  graph start
//   */
//  if (gblIsThis1stGrhToOutput == 1) {  /* 0 false, 1 true */
//    gblIsThis1stGrhToOutput = 0; 
///*     f_fn_prtlin("  <pre><br>");          */
//    f_fn_prtlin("  <pre>");         
//    gblWeAreInPREblockContent = 1;  /* true */
////    f_fn_prtlin("<br>");         
//  } else {
//    /* second graph start needs some more white space before it */
///*     f_fn_prtlin("  <pre><br><br><br><br><br><br><br>");  */
//    f_fn_prtlin("  <pre>"); 
//    gblWeAreInPREblockContent = 1;  /* true */
//    f_fn_prtlin("<br><br><br><br><br><br><br>"); 
//  }
//
//  // init gbl 
//  gbl_we_are_printing_graph = 1;
//  gblWeAreInPREblockContent = 1;  /* true */
//  gbl_do_second_line = 0;        // for benchmark label insert
//  strcpy(gbl_benchmark_label, "no label yet");   // GREAT, OMG, etc.
//
//
//  /* experiment bg color on left-side column containing label names
//  *  This is the 7-char filler (max size "STRESS-" = 7)
//  */
///*    char current_leftside[1024]; */
///*    int just_printed_stress_label; */
//
//   /* initialize */
///*    sprintf(current_leftside, "<span class=\"cRe2\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cRe2\"> </span>      "); */
///*    just_printed_stress_label = 0;                                                */
//
//
//  /* now read and print graph until we hit [end_graph] 
//  */
//  have_printed_STRESS_line_already = 0;
//  have_printed_OMG_line_already    = 0;
//  num_OMG_printed = 0;
//
//  gbl_do_readahead           = 1; /* do readahead until "OMG" label is printed */
//  gbl_just_started_readahead = 1;
//  gbl_have_hit_OMG = 0;
//  gbl_have_hit_stress = 0;
//
//
//  for (i=0; ; i++) {
//
//    f_docin_get(doclin);  // read doclin read doclin read doclin read doclin read doclin read doclin 
///* ksn(doclin); */
//    if (strstr(doclin, "[end_graph]") != NULL) break;
//
//
//    /*   EXAMPLE color a  thing
//    * <body style="background-color:yellow;">
//    * <h2 style="background-color:red;">This is a heading</h2>
//    * <p style="background-color:green;">This is a paragraph.</p>
//    * </body>
//    */
//
//
//    /* for GOOD line, make background colour palegreen
//* GOOD-|<span style="background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>|
//    */
//
///* tn();b(330);ks(doclin); */
//
//
//    /* Here we check if we are on the exact stress-level label lines
//    *  GREAT, GOOD, STRESS, OMG
//    */
//
//    if (strstr(doclin, "GREAT") != NULL) {
//      /* EXPERIMENT   left side to right */
//      /* replace " GREAT|" with "-GREAT " and put on right side */
//      strcpy(s1, " GREAT ");
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
//
//      /* replace " GREAT|" with "-GREAT " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cGr2\">%s</span>", s2, s1); 
//
////tn();b(333);ks(writebuf);
//      bracket_string_of("X", writebuf, "<span class=\"cGr2\">", "</span>");
////tn();b(334);ks(writebuf);
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
////tn();b(335);ks(writebuf);
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
////tn();b(336);ks(writebuf);
//
//      f_fn_prtlin(writebuf);
//      /* lines below are all light green */
///*    sprintf(current_leftside, "<span class=\"cGre\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cGre\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//    if (strstr(doclin, "GOOD") != NULL) {
//
//      /* replace "  GOOD|" with "-GOOD  " and put on right side */
///*       strcpy(s1, "-GOOD  "); */
//      strcpy(s1, " GOOD  ");
//
//      /* sfromto(s1, doclin,  1,  7); */  /* "  GOOD-" from "  GOOD-|" */
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
//      /* note "|" is at end */
///*         "%s<span style=\"background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%%;\">%s</span>|", s1, s2);  */
///*         "%s<span class=\"cLineGood\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cGre\">%s</span>|<span class=\"cGre\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cGre\">%s</span>|%s|", s1, s2);  */
//
//
//      /* replace "  GOOD|" with "-GOOD  " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cGre\">%s</span>", s2, s1); 
//
///*       sprintf(writebuf, "<span class=\"cGre\">%s</span>%s", s1, s2);  */
//
//      bracket_string_of("X", writebuf, "<span class=\"cGre\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//
//      f_fn_prtlin(writebuf);
//
//      /* lines below are all neutral color */
///*    sprintf(current_leftside, "<span class=\"cNeu\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cNeu\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//
//      continue;
//    }
//    /* for STRESS line, make background colour deeppink
//STRESS-|<span style="background-color:#FFBAC7; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>|
//    */
//    if (strstr(doclin, "STRESS") != NULL 
//    &&  strstr(doclin, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
//    && have_printed_STRESS_line_already == 0) {
//      ;
//      gbl_have_hit_stress = 1;
//
//      /* replace "STRESS|" with "-STRESS" and put on right side */
//      strcpy(s1, " STRESS");
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      /* note "|" is at end */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
///*         "%s<span style=\"background-color:#FFBAC7; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%%;\">%s</span>|", */
///*         "%s<span class=\"cLineStress\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cRed\">%s</span>|<span class=\"cRed\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cRed\">%s</span>|%s|", s1, s2);  */
//      sprintf(writebuf, "<span class=\"cRed\">%s</span>%s", s1, s2); 
//
//      /* replace "STRESS|" with "-STRESS" and put on right side */
//      sprintf(writebuf, " %s<span class=\"cRed\">%s</span>", s2, s1); 
//
//
////tn();
////ksn("702");
////ksn(writebuf);
//      bracket_string_of("X", writebuf, "<span class=\"cRed\">", "</span>");
////ksn(writebuf);
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
////ksn(writebuf);
//
//
//
//      // here writebuf is like this example:
//      //
////_writebuf=[ <span class="cRed">XXXXXXXXXXXXXXXXXXXXX</span><span class="star">^</span><span class="cRed">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</span><span class="cRed"> STRESS</span>]__
//      //
//
//      // fix bug where no "Stress" when bottom star on the graph is on the stress line
//      //
//      // if writebuf starts with " <span class="cRed">XXXXXXXX"
//      // change it to            " <span class="cRed"> STRESS "
//      //
//      char myprefix1[512];
//      char myprefix2[512];
//      char mybuff[2048];;
//      int  hasprefix;
//      char *myptr;
//      char *myptr2;
//      hasprefix = 1;  // default true
//      strcpy(myprefix1, " <span class=\"cRed\">XXXXXXXX");
//      strcpy(mybuff, writebuf);
//      myptr = &mybuff[0];
//      myptr2 = &myprefix1[0];
//      while(*myptr2) {
//          if(*myptr2++ != *myptr++)
//              hasprefix = 0;
//      }
//      if (hasprefix == 1) {   // replace "XXXXXXXX" with " STRESS "
////tn();
////trn(" hasprefix = YES");
////ksn(myprefix1);
////ksn(writebuf);
//         strcpy(myprefix2, " <span class=\"cRed\"> STRESS ");  
////ksn(myprefix2);
////ksn(&writebuf[strlen(myprefix1)]);
//         sprintf(mybuff, "%s%s", myprefix2, &writebuf[strlen(myprefix1)] );
////ksn(mybuff);
//         strcpy(writebuf, mybuff);
////ksn(writebuf);
////b(900);
//      }
//      
//
//
//      // make red line on STRESS line
//      //
////      scharswitch(writebuf, 'X', ' ');
////      scharswitch(writebuf, 'X', '-');   // for test, try underscore
////      scharswitch(writebuf, 'X', '^');   // for test, try
////      scharswitch(writebuf, 'X', '=');   // for test, try
////      scharswitch(writebuf, 'X', 'M');   // for test, try
////      scharswitch(writebuf, 'X', 'o');   // for test, try 
////      scharswitch(writebuf, 'X', ':');   // for test, try 
//
////      scharswitch(writebuf, 'X', 'm');   // for test, try 
////      scharswitch(writebuf, 'X', 'i');   // for test, try 
////      scharswitch(writebuf, 'X', '-');   // for test, try
////      scharswitch(writebuf, 'X', '-');   // for test, try
////      scharswitch(writebuf, 'X', 'M');   // for test, try 
//      scharswitch(writebuf, 'X', 'm');   // for test, try 
//
////      bracket_string_of("M", writebuf, "<span style=\"color:red;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: #ff0000;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: green;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: #FF0000;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: #Fuchsia;\">", "</span>");
////      bracket_string_of(":", writebuf, "<span style=\"color: #DeepPink;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: OrangeRed;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: DeepPink;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: Red;\">", "</span>");
//
////      bracket_string_of("m", writebuf, "<span style=\"color: RosyBrown;\">", "</span>");
////      bracket_string_of("m", writebuf, "<span style=\"color: hotpink;\">", "</span>");
////      bracket_string_of("m", writebuf, "<span style=\"color: red;\">", "</span>");
////      bracket_string_of("-", writebuf, "<span style=\"color: red;\">", "</span>");
////      bracket_string_of("M", writebuf, "<span style=\"color: red;\">", "</span>");
//      bracket_string_of("m", writebuf, "<span style=\"color: red;\">", "</span>");
//      //
//      // end of make red line on STRESS line
//
//
//
////ksn(writebuf);
//      scharswitch(writebuf, '#', ' ');
////ksn(writebuf);
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
////ksn(writebuf);
//
////ksn("call prtin here");
////tn();
//
//      f_fn_prtlin(writebuf);
//
//      have_printed_STRESS_line_already = 1;
//
//      /* lines below are all light red */
///*    sprintf(current_leftside, "<span class=\"cRed\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cRed\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//    /* intercept 2nd OMG line  (happens when last * is right on line)
//    */
///*     if (num_OMG_printed > 0) x */
///*  */
///*       if (num_OMG_printed == 1) x */
//        /* print blank line with color cRe2 under the 1st OMG */
///*    */
//          /* #define NUM_PTS_FOR_FUT 92 */
///*         sfill(myLastLine, NUM_PTS_FOR_FUT, ' ');  */
///*         bracket_string_of(" ", myLastLine, "<span class=\"cRe2\">", "</span>"); */
///*    */
///*         sprintf(p,"       %s\n", myLastLine );  */
///* left margin = 7 spaces */
///*         f_fn_prtlin(myLastLine); */
///*       x */
///*       continue; */
///*     x */
//
//    /* color OMG line, but
//    */
//    if (strstr(doclin, "OMG") != NULL
//    && have_printed_OMG_line_already == 0)
//    {
//
//      gbl_have_hit_OMG = 1;
//
///* tn();b(221);ki(have_printed_OMG_line_already); */
//
//       /* "   OMG-" from "   OMG-|" */
///*       sfromto(s1, doclin,  1,  7);   */
//
//      /* replace "   OMG-|" with "-OMG   " and put on right side */
///*       strcpy(s1, "-OMG   "); */
//      strcpy(s1, " OMG   ");
//
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cRe2\">%s</span>|<span class=\"cRe2\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cRe2\">%s</span>|%s|", s1, s2);  */
//      sprintf(writebuf, "<span class=\"cRe2\">%s</span>%s", s1, s2); 
//
//      /* replace "   OMG-|" with "-OMG   " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cRe2\">%s</span>", s2, s1); 
//
//      bracket_string_of("X", writebuf, "<span class=\"cRe2\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//
//      f_fn_prtlin(writebuf);
//
//      num_OMG_printed = num_OMG_printed + 1;
//
///* tn();b(222);ki(have_printed_OMG_line_already); */
//      have_printed_OMG_line_already = 1;
//
//      /* lines below are all bright red */
///*    sprintf(current_leftside, "<span class=\"cRe2\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cRe2\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//
//    /* in the bottom 4 graph lines, put different line-heights
//    */
//    if (strstr(doclin, "\'\'\'\'\'") != NULL) {
//
//      strcpy(writebuf, "");
//      f_fn_prtlin(writebuf);
//
//      /* EXPERIMENT stress level labels on right */
//      /* take 1st 7 chars margin and put them on right end */
//      sprintf(s5, "%.7s", doclin);  /* 1st 7 ch left margin */
///*       sprintf(s6, "%s%s", doclin + 7 - 1, s5); */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", doclin); */
///*       f_fn_prtlin(writebuf); */
///*       f_fn_prtlin(s6); */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", s6); */
///* ksn(s6); kin(strlen(s6)); */
///*       sprintf(writebuf, "<span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>", s6); */
///*       sprintf(writebuf, "<span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4, s5); */
//
//      /* weird   remove leadiing space from s4 and put it before yellow highlight */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 60%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 55%%;\">%s</span>%s", s4+1, s5);
//
///* ksn(writebuf); kin(strlen(writebuf)); */
//
//
//      f_fn_prtlin(writebuf);
//
//      continue;
//    }
//    if (strstr(doclin, "|    | ") != NULL) {
///* ksn(doclin); */
///* kin(strlen(doclin)); */
//      sprintf(s5, "%.7s", doclin);  /* 1st 7 ch left margin */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height:80%%;\"\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height:60%%;\">%s</span>%s", s4+1, s5);
//      f_fn_prtlin(writebuf);
//      continue;
//    }
//    if (strstr(doclin, "11   21") != NULL) {
//
//      /* EXPERIMENT stress level labels on right */
//      /* take 1st 7 chars and put them on right end */
//      sprintf(s5, "%.7s", doclin);
///*       sprintf(s6, "%s%s", doclin + 7 - 1, s5); */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 125%%;\">%s</span>", doclin); */
///*       sprintf(writebuf, "<span style=\"line-height: 125%%;\">%s</span>", s6); */
///*       sprintf(writebuf, "<span style=\"line-height: 165%%;\">%s</span>", s6); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 165%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 170%%;\">%s</span>%s", s4+1, s5);
//
//      f_fn_prtlin(writebuf);
//      continue;
//    }
//    int mth_ctr;
//    mth_ctr = 0;
//    if (strstr(doclin, "JAN") != NULL) mth_ctr++;
//    if (strstr(doclin, "FEB") != NULL) mth_ctr++;
//    if (strstr(doclin, "MAR") != NULL) mth_ctr++;
//    if (strstr(doclin, "APR") != NULL) mth_ctr++;
//    if (strstr(doclin, "MAY") != NULL) mth_ctr++;
//    if (strstr(doclin, "JUN") != NULL) mth_ctr++;
//    if (strstr(doclin, "JUL") != NULL) mth_ctr++;
//    if (strstr(doclin, "AUG") != NULL) mth_ctr++;
//    if (strstr(doclin, "SEP") != NULL) mth_ctr++;
//    if (strstr(doclin, "OCT") != NULL) mth_ctr++;
//    if (strstr(doclin, "NOV") != NULL) mth_ctr++;
//    if (strstr(doclin, "DEC") != NULL) mth_ctr++;
//
//    if (mth_ctr > 3) {
///* ksn(doclin); */
///* ksn(doclin + 7); */
//      /* remove the left margin (with year in it) and put spaces at end
//      *  we are getting rid of the year
//      */
///* ksn(doclin); */
//      /* doclin is
//       * [  2015  JULY          AUGUST          SEPTEMBER      OCTOBER        NOVEMBER       DECEMBER        ]
//       */
//
//      sprintf(s5, "%.7s", doclin);       /* grab 1st 7 ch */
//      strcpy(s5, "       "); /* 7 spaces */
//      sprintf(s4, "%s", doclin + 7 - 1); /* grab part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", doclin); */
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s       </span>", doclin + 7); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 75%%;\">%s</span>%s", s4+1, s5);
//
//
//      f_fn_prtlin(writebuf);
//      continue;
//    }
//
//
//
//  /* EXPERIMENT stress level labels on right */
//  /* take 1st 7 chars and put them on right end */
//  sprintf(s5, "%.7s", doclin);
///* ksn(s5); */
//  sprintf(s6, "%s%s", doclin + 7 - 1, s5);
///* ksn(s6); */
//  f_fn_prtlin(s6);
//
//
//  /* just output regular line */
///*   f_fn_prtlin(doclin); */
//
//
//
//  }  /* print graph until we hit [end_graph]  */
//
//
//
//  
//  gblWeAreInPREblockContent = 0;  /* false */
//
//  gbl_we_are_printing_graph = 0;
//  gbl_do_readahead          = 0; // do readahead until bottom of graph is printed
//
//  f_fn_prtlin("  </pre>\n\n");   /* end of graph */
//
//  /* 2. read until [beg_aspects]  , which look like this:
//  *    [beg_aspects]
//  *         From January 1, 2008 to March 31, 2008.  ^(sugne)
//  *         From January 1, 2008 to January 5, 2008.  ^(mogju)
//  *         From January 1, 2008 to February 12, 2008.  ^(megne)
//  *         From February 28, 2008 to March 31, 2008 and also from June 17, 2008 to July 1, 2008.  ^(vecju)
//  *    [end_aspects]
//  */
//  for (i=0; ; i++) {
//    f_docin_get(doclin);
//    if (strstr(doclin, "[beg_aspects]") != NULL) break;
//  }
//
///*   f_fn_prtlin("  <h3><br><br>Important Periods</h3>"); */
///*   f_fn_prtlin("  <h4>(they influence the graph above)<br><br><br></h4>"); */
//
//
//
//  f_fn_prtlin("<pre class=\"explain\">");
//  gblWeAreInPREblockContent = 1;  
///*   f_fn_prtlin("           Important Periods"); */
////  f_fn_prtlin("           Important Periods          ");
////  f_fn_prtlin("    (they influence the graph above)\n");
//  f_fn_prtlin("         Important Time Frames        ");
//  f_fn_prtlin("     that influence the graph above \n");
//
//
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fn_prtlin("</pre>");
//
//
//
//  /* now read and print aspects until we hit [end_aspects] 
//  */
//  for (i=0; ; i++) {
//
//    f_docin_get(doclin);
//    if (strlen(doclin) == 0) continue;
//
//    if (strstr(doclin, "[end_aspects]") != NULL) break;
//    f_fn_prtlin("\n");
//
//    /* 1 of 2
//    *    do intro lines like
//    *    "From April 30, 1933 until mumble and also from" 
//    *    From January 1, 2008 to March 31, 2008.  ^(sugne)
//    *
//    *  2 of 2  f_fn_aspect_text()
//    *    print aspect text  strings corresponding to
//    *    aspect_codes  like "^(sugne)" 
//    */
//    fn_aspect_from_to(doclin);
//
//  }  /* end of read and print aspects until we hit [end_aspects] */
//
//
//  /* now read until we get  either
//  *    1. [beg_graph]       for another grh+asp to output
//  * NO 28apr2013  no more astrobuffs  2. [beg_astrobuffs]  for report-bottom stuff
//  */
//  for (i=0; ; i++) {
//
//    f_docin_get(doclin);
//
//    if (strstr(doclin, "[beg_graph]") != NULL) {
//
//      strcpy(have_we_hit_beg_graph, "YES"); 
//      return;
//    }
//
//    if (strstr(doclin, "[beg_astrobuffs]") != NULL) break;
//  }
//
///* ksn(s1); */
//
//  /* here we have hit [beg_astrobuffs]
//  * 
//  * !! 28apr2013  we no longer display this table of planetary positions !!
//  * NOTE:    "[beg_astrobuffs]"  is stll there in docin stuff
//  *          In fact, the whole table is there, but not output anymore.
//  */
//  /* fn_output_bot_of_html_file(); */ /* for all report-bottom stuff */
//
//
//
//
//
//#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
//*   /*    else if (strstr(trait_name, "Best Calendar Year") != NULL) */
//*   /* get stress number for this year
//*   */
//*   char stringBuffForStressScore[64]; /* for instruction  "return only year stress score" */
//*   mamb_report_year_in_the_life(     /* in futdoc.o */
//*     "",                           /* html_file_name, */
//*     gbl_csv_person_string_in_htm,
//*     gbl_year_for_fut,         /* for stress num table at bottom */
//*     "return only year stress score",   /* instructions for mamb_report_year_in_the_life() */
//*     stringBuffForStressScore   );
//* tn();b(112);ks(stringBuffForStressScore);
//#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/
//
//
//
//
//
//
//
// // webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  
//
//
//
//  /* make table having stress score for the year
//  *  but only if the person was alive for the whole calendar year
//  */
//  if (gbl_is_first_year_in_life == 0) {
//
//// cannot use this since myleftmargin overrides centering on big screens
// // BUT,  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  webview  
//
//nbn(401); 
//    int sizeLongestFld;
//    char myleftmargin[32];
//    sizeLongestFld = (int)strlen(gbl_name_for_fut);
//         if (sizeLongestFld ==  1) { strcpy(myleftmargin, "8.00em;"); }
//    else if (sizeLongestFld ==  2) { strcpy(myleftmargin, "7.75em;"); }
//    else if (sizeLongestFld ==  3) { strcpy(myleftmargin, "7.50em;"); }
//    else if (sizeLongestFld ==  4) { strcpy(myleftmargin, "7.25em;"); } // s/b 7.0
//    else if (sizeLongestFld ==  5) { strcpy(myleftmargin, "7.00em;"); }
//    else if (sizeLongestFld ==  6) { strcpy(myleftmargin, "6.75em;"); }
//    else if (sizeLongestFld ==  7) { strcpy(myleftmargin, "6.50em;"); }
//    else if (sizeLongestFld ==  8) { strcpy(myleftmargin, "6.25em;"); }
//    else if (sizeLongestFld ==  9) { strcpy(myleftmargin, "6.00em;"); }
//    else if (sizeLongestFld == 10) { strcpy(myleftmargin, "5.75em;"); }
//    else if (sizeLongestFld == 11) { strcpy(myleftmargin, "5.50em;"); }
//    else if (sizeLongestFld == 12) { strcpy(myleftmargin, "5.25em;"); }
//    else if (sizeLongestFld == 13) { strcpy(myleftmargin, "5.00em;"); }
//    else if (sizeLongestFld == 14) { strcpy(myleftmargin, "4.75em;"); }
//    else if (sizeLongestFld == 15) { strcpy(myleftmargin, "4.50em;"); } //2.8
//    else                           { strcpy(myleftmargin, "4.5em;"); }
//
//    f_fn_prtlin("  <div><br></div>");
//
////
//////   f_fn_prtlin("<h4><span style=\"background-color:#FFBAC7;\">&nbspThis report is for entertainment purposes only.&nbsp</span></h4>");
////  f_fn_prtlin( "    .cSky        { background-color:#3f3ffa; font-weight: bold; ");
////
//
////    sprintf(writebuf, "  <table class=\"trait\" style=\"margin-left: %s;\"> <tr> <th colspan=\"3\"> Score For %s </tr>",
////    sprintf(writebuf, "  <table class=\"trait\" class=\"center\" style=\"margin-left: %s;\"> <tr> <th colspan=\"3\"> Score For %s </tr>",
//    sprintf(writebuf, "  <table class=\"trait\" class=\"center\"> <tr> <th colspan=\"3\"> Score For %s </tr>",
//
////      myleftmargin,
//      gbl_year_for_fut
//    );
//    f_fn_prtlin(writebuf);
//
////
////    //f_fn_prtlin("  <div><br><br><br></div>");
////    f_fn_prtlin("  <div><br></div>");
////    sprintf(writebuf,
////      "  <table class=\"trait\"> <tr> <th colspan=\"3\"> Score For %s </tr>",
////      gbl_year_for_fut
////    );
////    f_fn_prtlin(writebuf);
////
//
////    f_fn_prtlin("  <tr > <th>Person</th> <th>Score</th> <th></th></tr>");
//    f_fn_prtlin("  <tr > <th><span style=\"font-weight: normal;\"> Person</span></th> <th><span style=\"font-weight: normal;\"> Score</span></th> <th></th></tr>");
//
//
//tn();trn("COLOUR #3"); kin(gbl_YearStressScore );
//
//    /* calibrate stress score for table */
//  /*   int worknum; 
//  *     worknum = targetDayScore;
//  *     worknum = worknum * -1; 
//  *     worknum = worknum + 900;
//  *     if (worknum <= 0) worknum = 1;
//  *     worknum = mapNumStarsToBenchmarkNum(IDX_FOR_SCORE_B, worknum);
//  *     targetDayScore = worknum;
//  * 
//  *     PERCENTILE_RANK_SCORE =
//  *       mapBenchmarkNumToPctlRank(targetDayScore);
//  */
//    strcpy(gbl_name_for_fut, f_arr(1));  /* for stress num table at bottom */
//    strcpy(gbl_year_for_fut, f_arr(2));  /* for stress num table at bottom */
//
//    if (gbl_YearStressScore == 0) gbl_YearStressScore = 1; 
//
//    if (gbl_YearStressScore >= 90) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
////    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    if (gbl_YearStressScore >= 75) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
////    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//
//    if ( gbl_YearStressScore  >= 75) {
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//    if ( gbl_YearStressScore  < 75  &&  gbl_YearStressScore >= 50 ) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//      //   if ( gbl_YearStressScore  < 50  &&  gbl_YearStressScore >= 25 ) 
//      if ( gbl_YearStressScore  < 50  &&  gbl_YearStressScore >  25 ) {
//          
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
//        //  if ( gbl_YearStressScore <= 25 ) 
//            if ( gbl_YearStressScore <  25 ) {
//                
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
////      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//
//    if (gbl_YearStressScore >  25)
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
////    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");
//    if (gbl_YearStressScore >  10)
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//
//
////    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore); /* only writes if still unwritten */
//
//    f_fn_prtlin("  </table>");
//
//
//    f_fn_prtlin("<pre class=checkoutbox> ");
//    gblWeAreInPREblockContent = 1;  /* true */
//
//    f_fn_prtlin("  Check out group report \"Best Year\" which uses   ");
//    f_fn_prtlin("  this score to compare with other group members.  ");
//    f_fn_prtlin("");
//    gblWeAreInPREblockContent = 0;  /* false */
//    f_fn_prtlin("</pre> ");
//
//  } /* only when gbl_is_first_year_in_life == 0 */
//
//
//  f_fn_prtlin("<div><br><br></div>");
//  f_fn_prtlin("<pre class=willpower> ");
//  gblWeAreInPREblockContent = 1;  /* true */
///*   f_fn_prtlin( "                                                                "); */
//
//  //f_fn_prtlin( "  Your intense willpower can overcome and control your destiny  ");
//  //f_fn_prtlin( "                                                                ");
//
//  f_fn_prtlin( "  Your intense willpower can overcome  ");
//  f_fn_prtlin( "       and control your destiny        ");
//  f_fn_prtlin( "                                       ");
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fn_prtlin("</pre>");
//
//
////   sprintf(writebuf, "<h5><br><br><br>produced by iPhone app %s</h5>", APP_NAME);
////   f_fn_prtlin(writebuf);
//// /*   f_fn_prtlin("<h4><span style=\"background-color:#FFBAC7;\">&nbsp&nbsp&nbsp&nbsp&nbsp  This report is for entertainment purposes only.&nbsp&nbsp&nbsp&nbsp&nbsp  </span></h4>"); */
////   f_fn_prtlin("<h4><span style=\"background-color:#FFBAC7;\">&nbspThis report is for entertainment purposes only.&nbsp</span></h4>");
////  f_fn_prtlin("");
////  f_fn_prtlin("</pre>");
//
//  f_fn_prtlin("<pre class=\"appBy\"> ");
//  gblWeAreInPREblockContent = 1; 
//  sprintf(writebuf, "produced by iPhone app %s", APP_NAME);
//  f_fn_prtlin(writebuf);
//  gblWeAreInPREblockContent = 0; 
//  f_fn_prtlin("</pre>");
//
//  f_fn_prtlin("<pre class=\"entertainment\">");
//  gblWeAreInPREblockContent = 1; 
//  sprintf(writebuf, "&nbspThis report is for entertainment purposes only. &nbsp");
//  f_fn_prtlin(writebuf);
//  gblWeAreInPREblockContent = 0; 
//  f_fn_prtlin("</pre>");
//
////  f_fn_prtlin("");
////  f_fn_prtlin("");
//  f_fn_prtlin("<div><br><br></div>");
//
//  f_fn_prtlin("\n</body>\n");
//  f_fn_prtlin("</html>");
//
//} /* end of fn_outputGrhAndAspects() */    // webview
//


//
///* ************************************************************
//*
//* ************************************************************/
//void f_fn_aspect_text(char *aspect_code)
//{
//  int nn;
///* trn("f_fn_aspect_text(char *aspect_code)"); */
//
//  nn = binsearch_asp(aspect_code, f_asptab, NKEYS_ASP);
//  if (nn < 0) return;  /* do not print any aspect text at all  */
//
//  strcpy(my_aspect_text, f_asptab[nn].asp_text);
//
///*    put_br_every_n(my_aspect_text, 65);  */
///*    put_br_every_n(my_aspect_text, 72);  */
//   put_br_every_n(my_aspect_text, 50); 
//
//  /* example output for text paragraph:
//  * 
//  *  <table class="center"><tr><td style="white-space: nowrap"><p>You1are restless about current conditions and conventional ways of doing things. <br>There's a possibility that you can turn to unusual or even impractical projects. <br>Beware of association with eccentric or unstable people at this time.</p></td></tr></table>
//  */
//
//    //  char para_beg[133];
//    //  char para_end[133];
//
///*   strcpy(para_beg, "<table class=\"center\"><tr><td><p>"); */
///*   strcpy(para_end, "</p></td></tr></table>"); */
///*   sprintf(writebuf, "  %s%s%s\n", para_beg, my_aspect_text, para_end); */
//
//  //gblWeAreInPREblockContent = 1; /* 1 = yes, 0 = no */
//  //gblWeAreInPREblockContent = 0; /* 1 = yes, 0 = no */
//
//  //f_fn_prtlin("<div class=\"aspecttext\">");
//  f_fn_prtlin("<pre class=\"aspecttext\">");
//  gblWeAreInPREblockContent = 1;  
//  f_fn_prtlin(my_aspect_text);
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fn_prtlin("</pre>");
//
//
//  f_fn_prtlin(writebuf);
//
//}  /* end of f_fn_aspect_text(); */
//
//
///* ************************************************************
//* this is called once per aspect in docin
//* From February 28, 2008 to March 31, 2008 and also from June 17, 2008 to July 1, 2008.  ^(vecju)
//* ************************************************************/
//void fn_aspect_from_to(char *doclin)   // webview
//{
//  char fromtoline[1024];
//  char look_starting_here[1024];
//  char *p;
///* tn();trn("in fn_aspect_from_to()");  */
//
//
//  strcpy(fromtoline, doclin);
//  is_first_from_to_in_doclin = 1;
//
//  /* get return value aspect_code like "^(vecju)"
//  */
//  p = strstr(fromtoline, " ^");
//  if (p != NULL) {
//    strcpy(aspect_code, p + 1);
//  }
// 
//  /* make "^(vecju)" int "vecju"
//  */
//  scharout(aspect_code,'^');   
//  scharout(aspect_code,'(');   
//  scharout(aspect_code,')');   
//
//  *p = '\0';   /* end the fromtoline string here */
//  strcpy(look_starting_here, fromtoline);
//
// //f_fn_prtlin("<div class=\"fromtodates\">");
// f_fn_prtlin("<pre class=\"fromtodates\">");
// gblWeAreInPREblockContent = 1;  
//  do {  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
//
//    p = strstr(look_starting_here, " from");  /* look for a " from" */
//
//    if (p != NULL) {
//      strcpy(s3, p + 1);
//    }
//    if (p == NULL) {  
//      /* only one from/to in doclin
//      *  (less leading white for 2nd, 3rd)
//      */
//
//
//      if (is_first_from_to_in_doclin == 1) {
//        sprintf(writebuf, "%s", look_starting_here); 
//      } else {
//        //sprintf(writebuf, "  %s", look_starting_here); 
//        sprintf(writebuf, "%s", look_starting_here); 
//      }
//      f_fn_prtlin(writebuf);
//
//      is_first_from_to_in_doclin = 0;
//      break;  /* done */
//
//    } else {
//
//      /* found another from/to.  Now print the first from/to.
//      *  p points to sp in " from" 
//      */
//      mkstr(s2, look_starting_here, p ); /* up to space in " from" */
//      if (is_first_from_to_in_doclin == 1) {
//        sprintf(writebuf, "%s", s2); 
//      } else {
//        //sprintf(writebuf, "  %s", s2); //prepend 2 sp to align with first line
//        sprintf(writebuf, "%s", s2); //prepend 2 sp to align with first line
//      }
//      f_fn_prtlin(writebuf);
//      is_first_from_to_in_doclin = 0;
//
//      /*       strcpy(look_starting_here, p + 1); copy str into itself (nono) */
//      strcpy(s5, p + 1);
//      strcpy(look_starting_here, s5);
//    }
//  } while (p != NULL);   /* ++++++++++++++++++++++++++++++++++++ */
//
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fn_prtlin("</pre>"); // 
//  //f_fn_prtlin("</div>"); // 
//
//
//  /* here the from/to intro text has been output */
//
//    /* output the aspect text
//    */
//    f_fn_aspect_text(aspect_code);
//
//}  /* end of fn_aspect_from_to(); */
//


// c examples
//       n = sprintf(p,"%s", "\n[beg_topinfo1]\n");
//       fput(p,n,fFP_DOCIN_FILE);
// 
//       n = sprintf(p,"%s\n", scapwords(&fA_EVENT_NAME[0]));
//       fput(p,n,fFP_DOCIN_FILE);
//
//    // smup   fput(global_p, global_n, Fp_p_HTML_file);
//      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, global_p, global_n);
//      gbl_put_html_here = gbl_put_html_here + global_n;
//
//
void f_fn_prtlin(char *lin)
{
  char myEOL[8];
  //char myLastLine[8192], next_doclin[8192], current_prtlin[8192], thirdline[8192];
  char                   next_doclin[8192], current_prtlin[8192], thirdline[8192];
  char *ptr;
//tn(); tr("f_fn_prtlin         ="); ksn(lin);

//ki(gbl_do_readahead);


  if (gbl_is_first_f_fn_prtlin == 1) {  // init
    gbl_put_html_here        = 0;  // beg of js malloc'd mem
    gbl_is_first_f_fn_prtlin = 0;  // not first any more
  }



  // ignore rubbish line
  if (strstr(lin, "raph]") != NULL) return;


  // do second line of benchmark label printing, 
  // BUT not if the  benchmark label is on the last line of the graph
  // (next line has apostrophe tick marks for the dates)
  //
  if (gbl_do_second_line == 1) {

/* tn();trn("in gbl_do_second_line"); */
    strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */
    strcpy(thirdline,   global_docin_lines[global_read_idx + 2]); /* get next input line */
/* ksn(lin); */
/* ksn(next_doclin); */
/* ksn(thirdline); */

    //if (strstr(next_doclin, "||||||||||||||") == NULL) /^[bkt]

    
    if (strstr(next_doclin, "''''''''''''''") == NULL)
    {

      insert_minus_benchmark( lin);
/* trn("after insert minus");ks(lin); */
      change_last_7_chars(lin);
/* trn("after change_last7");ks(lin); */

    }


    gbl_do_second_line = 0;
  } // print second line of benchmark label
  if (gbl_do_second_line == 7) {  // print of benchmark label was nixed
    change_last_7_chars(lin);
    gbl_do_second_line = 0;
  }


  /* determine end of line method
  */
  strcpy(myEOL, "\n");
  if (GBL_HTML_HAS_NEWLINES == 1)       strcpy(myEOL, "\n");
  if (GBL_HTML_HAS_NEWLINES == 0) {
    /*    scharout(lin,'\n'); */  /* remove newlines */
    if (gblWeAreInPREblockContent == 1) strcpy(myEOL, "<br>");
    else                                strcpy(myEOL, "");
  }

  /* peek ahead to the next input line
  *  if this current line has GREAT or GO0D in it
  *    replace it with 7 spaces
  *  if the next input line has "-GREAT" or -GOOD in it
  *    on this current line, replace last 7 spaces with GREAT or GOOD 
       *   strcpy(in_line, global_docin_lines[global_read_idx] ); *
  */
  if (gbl_do_readahead == 1) {
/* b(20); */
    // not s1
    strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */

/* trn("curr=");ks(lin); */
/* trn("next=");ks(s1); */

    /* if first line of graph is GREAT or GOOD, print it as is
    */
    if (gbl_just_started_readahead == 1 ) {  // 1st line of graph
      if (((strstr(lin, "GREAT") != NULL) || strstr(lin, "GOOD") != NULL)) {


/* tn();trn("in 1st line G"); */
//tr("in 1st line G lin =");
//ksn(lin); 

        n = sprintf(p,"%s%s", lin, myEOL);

//        fput(p, n, Fp_f_HTML_file);        /* PRINT the line */
        memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
        gbl_put_html_here = gbl_put_html_here + n;

        strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
        return;
      } 
      gbl_just_started_readahead = 0;

//    } else if (strstr(s1, "GREAT") != NULL) {
    } else if (strstr(next_doclin, "GREAT") != NULL) {

/* tn();trn("in GREAT NEXT"); */

      /* replace last 7 spaces with GREAT */
      strcpy(s2, " GREAT ");
      /* into s3, get rest of string from 8th char */
      strcpy(s3, &doclin[8 - 1]);  // this is  the CURRENT  doclin, not next

/*       strcpy(s3, &lin[8 - 1]); */
/* ksn(s3); */
      /* replace " GREAT|" with "-GREAT " on CURRENT LINE and put on right side 
      */
      sprintf(writebuf, " %s<span class=\"cGr2\">%s</span>", s3, s2);   // buf for CURRENT line
      bracket_string_of("X", writebuf, "<span class=\"cGr2\">", "</span>");
/* tn();b(334);ks(writebuf); */
      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
/* tn();b(335);ks(writebuf); */
      scharswitch(writebuf, 'X', ' ');
      scharswitch(writebuf, '#', ' ');
      scharswitch(writebuf, '|', ' ');  /* sideline out */
/* ksn(writebuf); */
/* ksn(myEOL); */

      strcpy(gbl_benchmark_label, "GREAT");
      gbl_do_second_line =  insert_label_benchmark( writebuf, next_doclin);
      change_last_7_chars(writebuf);

      n = sprintf(p,"%s%s", writebuf, myEOL);

//      fput(p, n, Fp_f_HTML_file);        /* PRINT the CURRENT line */
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
      gbl_put_html_here = gbl_put_html_here + n;


      strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
      return;

      // here the NEXT doclin requires fiddling ("----" etc)

//    } else if (strstr(s1, "GOOD") != NULL) {
    } else if (strstr(next_doclin, "GOOD") != NULL) {

/* tn();trn("in GOOD NEXT"); */
      strcpy(s2, " GOOD  ");
      /* into s3, get rest of string from 8th char */
      strcpy(s3, &doclin[8 - 1]);
      sprintf(writebuf, " %s<span class=\"cGre\">%s</span>", s3, s2); 
      bracket_string_of("X", writebuf, "<span class=\"cGre\">", "</span>");
      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
      scharswitch(writebuf, 'X', ' ');
      scharswitch(writebuf, '#', ' ');
      scharswitch(writebuf, '|', ' ');  /* sideline out */

      strcpy(gbl_benchmark_label, "GOOD");
      gbl_do_second_line =  insert_label_benchmark( writebuf, next_doclin);  // ---<
      change_last_7_chars(writebuf);


      n = sprintf(p,"%s%s", writebuf, myEOL);
//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
      gbl_put_html_here = gbl_put_html_here + n;


      strcpy(gbl_prtlin_lastline, p);

      return;
      // end of GOOD is in NEXT line

    } else if ( strstr(lin, "GREAT") != NULL) {
/* tn();trn("in GREAT current"); */

      /* remove GREAT from current line and substitute 7 spaces */

      //strcpy(s1, lin);
      //ptr = strstr(s1, "<span class=\"cGr2\"> GREAT </span>");
      strcpy(current_prtlin, lin);
      ptr = strstr(current_prtlin, "<span class=\"cGr2\"> GREAT </span>");

      memcpy(ptr, "       \0", 8);
      //strcpy(lin,s1);
      strcpy(lin,current_prtlin);

      n = sprintf(p,"%s%s", writebuf, myEOL);
//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
      gbl_put_html_here = gbl_put_html_here + n;

      strcpy(gbl_prtlin_lastline, p);

      return;

    } else if ( strstr(lin, "GOOD")  != NULL) {
/* tn();trn("in GOOD current"); */
      /* remove GOOD from current line and substitute 7 spaces */
/* ksn(lin); */
      strcpy(s5, lin);
/* ksn(s5); */
      char *myptrtest;
/* char tststr[1024]; */
/* strcpy(tststr, "<span class=\"cGre\"> GOOD </span>"); */
/* ksn(tststr); */
      myptrtest = strstr(lin, "<span class=\"cGre\"> GOOD  </span>");
      memcpy(myptrtest, "       \0", 8);

      n = sprintf(p,"%s%s", writebuf, myEOL);
//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
      gbl_put_html_here = gbl_put_html_here + n;

      strcpy(gbl_prtlin_lastline, p);

      return;
    }


   else if (strstr(lin, "STRESS") != NULL 
        &&  strstr(lin, "LEVELS") == NULL ) {          // 20150325 put "STRESS LEVELS" in graph title for webview

//tn();trn("doing STRESS  LABEl !!!!!!!!!!!!!!");
     strcpy(gbl_benchmark_label, "STRESS");
     gbl_do_second_line =  insert_label_benchmark(writebuf, next_doclin);
//ksn(writebuf);
          n = sprintf(p,"%s%s", writebuf, myEOL);
          memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
          gbl_put_html_here = gbl_put_html_here + n;

//kin(gbl_do_second_line );
//tn();
   }

   else if (strstr(lin, "OMG") != NULL) {

/* tn();trn("doing OMG  LABEl !!!!!!!!!!!!!!"); */
     // check if OMG is on last line of graph
     // if yes, special output
     //

     strcpy(gbl_benchmark_label, "OMG");
     gbl_do_second_line =  insert_label_benchmark(writebuf, next_doclin);
   }


  } /* (gbl_do_readahead == 1) */



/* tn();trn("FALL THRU"); */

/*   if (   strstr(gbl_prtlin_lastline, "First Half") != NULL */
/*       && strstr(lin,                 "First Half") != NULL  */

  /* print blank line  under the first 6 months
  */
  if (   strstr(gbl_prtlin_lastline, "First 6 months") != NULL
      && strstr(lin,                 "First 6 months") != NULL 
  ) {
/*     n = sprintf(p,"%s\n", "" ); */
/*     n = sprintf(p,"%s%s", "", myEOL); */
//trn("blank under 6 mths=");ks(p);
 
     n = sprintf(p,"%s",  myEOL);
//     fput(p, n, Fp_f_HTML_file);
     memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
     gbl_put_html_here = gbl_put_html_here + n;

     strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */


    /* print blank line with color cSky */
    /* #define NUM_PTS_FOR_FUT 92 */
//   sfill(myLastLine, NUM_PTS_FOR_FUT, 'q'); 
//   bracket_string_of(" ", myLastLine, "<span class=\"cSky\">", "</span>");
//   n = sprintf(p,"       %s%s", myLastLine, myEOL); /* left margin = 7 spaces */
//   fput(p, n, Fp_f_HTML_file);
//   strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */



    /* start readahead after printing line with "6 months" in it
    */
    if(strstr(lin, "6 months") != NULL) {
      gbl_do_readahead           = 1; // do readahead until bottom of graph is printed
      gbl_just_started_readahead = 1;
    }

    return;
  }
/*   if (   strstr(gbl_prtlin_lastline, "Second Half") != NULL */
/*       && strstr(lin,                 "Second Half") != NULL  */
  if (   strstr(gbl_prtlin_lastline, "Second 6 months") != NULL
      && strstr(lin,                 "Second 6 months") != NULL 
     ) {
/*     n = sprintf(p,"%s\n", "" ); */
    n = sprintf(p,"%s%s", "", myEOL);
//trn("second 6 mths=");ks(p);

//    fput(p, n, Fp_f_HTML_file);
    memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
    gbl_put_html_here = gbl_put_html_here + n;

    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */

    /* start readahead after printing line with "6 months" in it
    */
    if(strstr(lin, "6 months") != NULL) {
      gbl_do_readahead           = 1; // do readahead until bottom of graph is printed
      gbl_just_started_readahead = 1;
    }

    return;
  }

  if (   strstr(gbl_prtlin_lastline, "|   10   20") != NULL  /* avoid double print */
      && strstr(lin,                 "|   10   20") != NULL 
     ) {
    return;
  }


  /* if last line printed has "-STRESS"  AND this line has "-STRESS"
  *  do not print this line
  *  (bug with 2 "STRESS-" lines when star is on bottom line and
  *  bottom line is stress line)
  */
/*       && strstr(lin,                 "STRESS-") != NULL  */
//      && strstr(gbl_prtlin_lastline, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
//      && strstr(lin, "LEVELS")                 == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
  if (   strstr(gbl_prtlin_lastline, "STRESS") != NULL
      && strstr(lin,                 "STRESS") != NULL 
     ) {

      if (   strstr(gbl_prtlin_lastline, "LEVELS") != NULL) {  // put blank line after grh title
        n = sprintf(p,"%s",  myEOL);
//trn("prt blank line after grh title");ks(p);

//        fput(p, n, Fp_f_HTML_file);
        memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
        gbl_put_html_here = gbl_put_html_here + n;

        strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
      }

    return;
  }

//  /* if last line printed has "-OMG"  AND this line has "-OMG"
//  *  do not print this line
//  *  (bug with 2 "OMG-" lines when star is on bottom line and
//  *  bottom line is OMG line)
//  */
//  if (   strstr(gbl_prtlin_lastline, "OMG") != NULL
//      && strstr(lin,                 "OMG") != NULL 
//     ) {
//    return;
//  }

/* if (strstr(lin, "GREAT-") != NULL) x */
/* tn();trn("f_fn_prtlin() GREAT   at TOP    "); ksn(lin); x */


  /* weird fix 
  *  if line has "STRESS-", but does NOT have "span", do not print it
  */
/*   if(strstr(lin, "STRESS-") != NULL */
/*   if(strstr(lin, "-STRESS") != NULL */
  if(strstr(lin, "STRESS") != NULL
  && strstr(lin, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
  && strstr(lin, "span")   == NULL)  return;
  
  /* weird fix  #2   long blank line at top
  */
  if (strstr(lin, " <span class=\"cSky\">                                                                                              </span>" )  != NULL) {
   /* tn();b(555);ks("HIT BAD sky!"); */
   return;
  }

  /* weird fix #3
  *  if line has "OMG-", but does NOT have "cRe2", do not print it
  *  BUT, print a line of spaces in cRe2
  */
/* tn();trn(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"); */
//tr("weird fix #3");ksn(lin); 
  if(strstr(lin, "OMG-") != NULL
  && strstr(lin, "cRe2")    == NULL) 
  {
    /* print blank line with color cRe2 under the 1st OMG
       but must have --- for OMG in it */

    // 20121229  HARD CODE THIS LINE  (it worked)
    //  strcpy(p, " <span style=\"background-color:#ff4477\"> </span><span style=\"color:#ff4477\">---</span><span style=\"background-color:#ff4477\"> </span><span class=\"cRe2\">                                                                                                                                                                                   </span> ");
  // strcpy(p, " <span style=\"background-color:#ff4477\"> </span><span style=\"color:#ff4477\">---</span><span style=\"background-color:#ff4477\"> </span><span class=\"cRe2\">                                                                                                                                                                                   </span> ");



//     strcpy(p, " <span style=\"background-color:#ff4477\"> </span><span style=\"color:#ff4477\">---</span><span style=\"background-color:#ff4477\"> </span><span class=\"cRe2\">                                                                                       </span> ");
     strcpy(p, " <span style=\"background-color:#fd0102\"> </span><span style=\"color:#fd0102\">-----</span><span style=\"background-color:#fd0102\"> </span><span class=\"cRe2\">                                                                                     </span> ");




    n = (int)strlen(p);
//tr("prt in weird fix #3");ks(p);

//    fput(p, n, Fp_f_HTML_file);
    memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
    gbl_put_html_here = gbl_put_html_here + n;

    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */


    /* print blank line with color cRe2 under the 1st OMG */
    /* #define NUM_PTS_FOR_FUT 92 */
//    sfill(myLastLine, NUM_PTS_FOR_FUT, ' '); 
//    bracket_string_of(" ", myLastLine, "<span class=\"cRe2\">", "</span>");
//    n = sprintf(p,"       %s%s", myLastLine, myEOL); /* left margin = 7 spaces */
//    fput(p, n, Fp_f_HTML_file);
//    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
    return;
  }

/* GREAT is too short here, but OK in docin array   what hpppend? */
/* if (strstr(lin, "GREAT-") != NULL) x */
/* tn();trn("f_fn_prtlin() GREAT"); ksn(lin); x */

  /* remove pipe at end of any line with a pipe in it
  */
  char *end_pipe;
  end_pipe = strstr(lin, "|<");  /* looks like "|</span>" */
  if(end_pipe != NULL) {     
    memcpy(end_pipe, " ", 1);
  }
  end_pipe = strstr(lin, "|       <");  /* looks like "|       </span>" */
  if(end_pipe != NULL) {     
    memcpy(end_pipe, " ", 1);
  }
  
  if (gbl_we_are_printing_graph == 1) change_last_7_chars(lin);
  

  // if lin does not have equal brackets "<>", do not print it
  //
  if (hasEqualBrackets(lin) == 0) {

//tn();trn("========  not printed  =================================================================================================");
//ki(n);ksn(lin);
//trn("========================================================================================================================");
    return;  // do not print this unequal bracket line
  }


  n = sprintf(p,"%s%s", lin, myEOL);

  
  // during bug bottom star is on stress line, get "-" in char postition 1 (should always be " ")
  //
  if (*p == '-') {   // global      char *p = &writebuf[0];
//ksn("hey");
      *p  = ' ';
  }



//  fput(p, n, Fp_f_HTML_file);        /* PRINT the line */
  memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
  gbl_put_html_here = gbl_put_html_here + n;


//tr("prt at bottom of prtlin");ks(p);tn();
  strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */

/* trn("end of f_fn_prtlin()"); */
} /* end of f_fn_prtlin() */


int hasEqualBrackets(char *inlin) {
  int num_L_angle; // <
  int num_R_angle; // >
  num_L_angle = 0; // <
  num_R_angle = 0; // >
  for (int i = 0; i < strlen(inlin); i++) {
    if (inlin[i] == '<') num_L_angle = num_L_angle + 1;
    if (inlin[i] == '>') num_R_angle = num_R_angle + 1;
  }

  if (num_L_angle == num_R_angle) return 1;
  else {
    // here < and > do not match, so return 0, unless there is "w3" in the line

    // problem:  these special lines should print
    //    _(========  not printed  =================================================================================================)__
    //    _n=[0]___lin=[<!doctype html public "-//w3c//dtd html 4.01 transitional//en" ]__
    //    _(========  not printed  =================================================================================================)__
    //    _n=[0]___lin=[  "http://www.w3.org/TR/html4/loose.dtd">]__
    //
    if (strstr(inlin, "w3") != NULL) return 1;

    return 0;
  }
  
}


/* arg in_docin_last_idx  is pointing at the last line written.
* Therefore, the current docin_lines written
* run from index = 0 to index = arg in_docin_last_idx.
*/
void f_docin_get(char *in_line)
{
//trn("in f_docin_get(char *in_line)");
//tn();
//ksn(in_line);  (was no great in here)

//ki(global_read_idx);
//ksn(in_line); 

//  if (strcmp(in_line, "[end_graph]") == 0) return;

/*   static int times_thru; */
/*   if (times_thru == 0) global_read_idx = 0; */
/*   else                 global_read_idx++; */
/*   times_thru++;  */

  if (is_first_f_docin_get == 1) global_read_idx = 0;
  else                           global_read_idx++;
  
  is_first_f_docin_get = 0;  /* set to false */

//  if (global_read_idx > global_max_docin_idx - 1)
  if (global_read_idx > global_max_docin_idx)
  {
     f_docin_free();
    rkabort("Error. futhtm.c walked off end of docin_lines array");
  }

  strcpy(in_line, global_docin_lines[global_read_idx] );

  scharout(in_line,'\n');   /* remove newlines */

/* trn("docin=");ks(in_line); */
} /* end of f_docin_get */


#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
* /* Take long string and wrap lines with "<br>" to a given max line length
* *
* *  Put "<br>"s in arg1 string so lines are not longer than arg2.
* */
* void put_br_every_n(char *instr,  int line_not_longer_than_this)
* {
*   char *pNewWord;
*   int len_new_word, lenbuf, num_br_added;
* 
* tn(); trn(" in put_br_every_n() ------------------------------");
* ksn(instr);
*   strcpy(writebuf, "");
*   strcpy(workbuf, "");
*   num_br_added = 0;
* 
*   pNewWord = strtok (instr," ");  /* get ptr to first word */
* 
*   while (pNewWord != NULL)  /* for all words */
*   {
*     lenbuf       = strlen(writebuf);
*     len_new_word = strlen(pNewWord);
* kin(lenbuf); tr("add this:"); ks(pNewWord);
* 
*     if (lenbuf + len_new_word >= line_not_longer_than_this) {
* 
*       if (num_br_added == 0) {
*         f_fn_right_pad_with_hidden(writebuf, line_not_longer_than_this - lenbuf);
* trn("len after pad="); ki(strlen(writebuf));
*       }
* 
*       sprintf(writebuf, "%s<br>", writebuf);   /* add break */
*       num_br_added = num_br_added + 1;
* 
*       /* add writebuf to final result in workbuf */
*       sprintf(workbuf, "%s%s", workbuf, writebuf);
* 
*       strcpy(writebuf, "");                    /* init  writebuf */
*     } /* write out since line too long */
* 
*     /* add new word to writebuf */
*     sprintf(writebuf, "%s%s%s", writebuf, pNewWord, " ");
*     pNewWord = strtok (NULL, " ");             /* get ptr to next word */
* 
*   }  /* for all words */
* 
* 
*   /* here no more words in aspect desc (writebuf has last line to add) */
* 
*   if (strlen(writebuf) != 0) {
* 
*     /* add writebuf to final result in instr but remove sp at end */
*     writebuf[ strlen(writebuf) - 1] = '\0';
* 
*     if (num_br_added == 0) {
*       lenbuf = strlen(writebuf);
*       f_fn_right_pad_with_hidden(writebuf, line_not_longer_than_this - lenbuf);
*     }
* 
*     sprintf(instr, "%s%s", workbuf, writebuf);  /* adding writebuf */
*   } else {
*     /* here writebuf is "" */
*     /* remove "<br>"  (+ sp) from the end*/
*     workbuf[ strlen(workbuf) - 5] = '\0';
* 
*     sprintf(instr, "%s", workbuf);
*   }
* 
* 
* }/* end of put_br_every_n() */
* 
* void f_fn_right_pad_with_hidden(char *s_to_pad, int num_to_pad)
* {
*   char my_right_padding_chars[80];
* /*   char *lotsachars = "_________________________________________________________"; */
* /*   char *lotsachars = "Lorem ipsum calor sit amet, consecr adipi elit. Nam cursus. Morbi ut mi. Nullam enim leo, egestas id, condimentum at,"; */
* /*   char *lotsachars = "lom  ipim  cor  sit  amet,  cosecr  adipi  elit.  nam  cirvus.  morbi  ut  mi.  nullam  enim  leo,  ege stas  id,  con dimen tum  at,"; */
* /*   char *lotsachars ="a a a a M M M M M Ma Ma Ma M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  M  "; */
*   char *lotsachars = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
* 
* tn(); trn(" in f_fn_right_pad_with_hidden() ===========================================");
* kin(num_to_pad);ks(s_to_pad);
* 
* /*   if (num_to_pad <= 0) return;  */
*   if (num_to_pad <= 0) return;
* 
*   /* make right pad chars */
*   mkstr(my_right_padding_chars, lotsachars, lotsachars + num_to_pad - 1);
*   sprintf (s_to_pad,
*     "%s<span style=\"visibility: hidden\">%s</span>",
*     s_to_pad,
*     my_right_padding_chars
*   );
* tr("padded = "); ks(s_to_pad);
* }
#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/


// make_calendar_day_html_file() not used  20210402
//
///* make short html file for best day for a person
//*/
//int make_calendar_day_html_file(   /* called from futdoc.c  */
//  char *html_f_file_name,
//  char *csv_person_string,
//  int itarget_mm,
//  int itarget_dd,
//  int itarget_yyyy,
//  int targetDayScore)
//{
//  int PERCENTILE_RANK_SCORE;
//  char person_name[32];
////  fopen_fpdb_for_debug();
//
////tn();trn("in make_calendar_day_html_file()   args are:  ");
////ksn(html_f_file_name);
////ksn(csv_person_string);
////kin(itarget_mm);
////kin(itarget_dd);
////kin(itarget_yyyy);
////kin(targetDayScore);
////
//
//
//  gblCalDayScoreIsWritten = 0;  /* init */
//
////  strcpy(gbl_ffnameHTML, html_f_file_name);
//
////  /* open output HTML file
////  */
//////trn("opening Fp_f_HTML_file this filefor write:");
//////ksn(html_f_file_name);
////  if ( (Fp_f_HTML_file = fopen(html_f_file_name, "w")) == NULL ) {
//////trn("open FAILED");
////    rkabort("Error  when  futhum.c.  fopen().");
////  }
//////trn("open SUCCESS");
////
//
///*  at end, change to STRICT  maybe */
//  f_fn_prtlin( "<!doctype html public \"-//w3c//dtd html 4.01 transitional//en\" ");
//  f_fn_prtlin( "  \"http://www.w3.org/TR/html4/loose.dtd\">");
//
//  f_fn_prtlin( "<html>");
//  f_fn_prtlin( "\n<head>");
//
//  strcpy(person_name,  csv_get_field(csv_person_string, ",", 1));
///*   strcpy(gbl_person_name, person_name); */
//
//
//  /* <TITLE> */
//
///*   sprintf(writebuf,
//*     "  <title>%s %04d%02d%02d- Calendar Day, produced by iPhone app %s.</title>",
//*     person_name,
//*     itarget_yyyy,
//*     itarget_mm,
//*     itarget_dd,
//*     APP_NAME );
//*   f_fn_prtlin(writebuf);
//*/
//  
//  /* if HTML filename, gbl_ffnameHTML, has any slashes, grab the basename
//  */
////  char myBaseName[256], *myptr;
////  if (sfind(gbl_ffnameHTML, '/')) {
////    myptr = strrchr(gbl_ffnameHTML, '/');
////    strcpy(myBaseName, myptr + 1);
////  } else {
////    strcpy(myBaseName, gbl_ffnameHTML);
////  }
////  sprintf(writebuf, "  <title>%s</title>", myBaseName);
//
//
//  f_fn_prtlin(writebuf);
//  
//
//
//
//
//  /* HEAD  META
//  */
//  sprintf(writebuf, "  <meta name=\"description\" content=\"Calendar Day report produced by iPhone app %s\"> ",  APP_NAME);
//  f_fn_prtlin(writebuf);
//
//
//  f_fn_prtlin( "  <meta http-equiv=\"Content-Type\" content=\"text/html\"; charset=\"iso-8859-1\">"); 
//  /*   f_fn_prtlin( "  <meta name=\"Author\" content=\"Author goes here\">"); */
//
//
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"group,member,astrology,personality,future,past,year in the life,compatibility,GMCR\">  */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"abym,Astromeasur,group,member,best,match,calendar,year,passionate,personality\"> "); */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"BFF,astrology,compatibility,group,best,match,calendar,year,stress,personality\"> "); */
///*   f_fn_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,compatibility,group,best,match,personality,stress,calendar,year\"> "); */ /* 86 chars */
//  f_fn_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,me,compatibility,group,best,match,personality,stress,calendar,year\"> ");  /* 89 chars */
//
//
//  /* get rid of CHROME translate "this page is in Galician" 
//  * do you want to translate?
//  */
//  f_fn_prtlin("  <meta name=\"google\" content=\"notranslate\">");
//  f_fn_prtlin("  <meta http-equiv=\"Content-Language\" content=\"en\" />");
//
//  f_fn_prtlin("  <meta name = \"format-detection\" content = \"telephone=no\">");
//
//  /* example comment out */
//  /*   f_fn_prtlin( "    <!-- "); */
//  /*   f_fn_prtlin( "      background-image: url('mkgif1g.gif');"); */
//  /*   f_fn_prtlin( "    --> "); */
//
//
//
//  /* HEAD   STYLE/CSS
//  */
//
//  f_fn_prtlin( "\n  <style type=\"text/css\">");
//
//
//
//  f_fn_prtlin( "@media screen and (max-device-width: 500px) {");   // CSS for SMALL screen device
//  f_fn_prtlin( "    BODY {");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      font-size:   2.2em;");   // <<<============================================
//  f_fn_prtlin( "      font-weight: normal;");
//  f_fn_prtlin( "      text-align:  center;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "}"); // end of  @media screen and (max-device-width: 500px)  // CSS for SMALL screen device
//
//
//  f_fn_prtlin( "@media screen and (min-device-width: 501px) {  "); // CSS for BIG SREEN  tablet, iPad, PC, Mac
//  f_fn_prtlin( "    BODY {");
//  f_fn_prtlin( "      background-color: #F7ebd1;");
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      font-size:   medium;");   // <<<============================================
//  f_fn_prtlin( "      font-weight: normal;");
//  f_fn_prtlin( "      text-align:  center;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "}    "); // END of   @media screen and (min-device-width: 501px)CSS for BIG SREEN  tablet,iPad,PC,Mac
//
//
//
//  //f_fn_prtlin( "    H1 { font-size: 137%; font-weight: bold;   line-height: 95%; text-align: center;}");
////  f_fn_prtlin( "    H1 { font-size: 2em; font-weight: bold;   line-height: 95%; text-align: center;}");
//  f_fn_prtlin( "    H1 { font-size: 1.6em; font-weight: bold;   line-height: 95%; text-align: center;}");
//
//  f_fn_prtlin( "    H2 { font-size: 125%;                      line-height: 25%; text-align: center;}");
//  f_fn_prtlin( "    H3 { font-size: 110%; font-weight: normal; line-height: 30%; text-align: center;}");
//
//  f_fn_prtlin( "    H4 { font-size:  75%; font-weight: bold;   line-height: 30%; text-align: center;}");
//  f_fn_prtlin( "    H5 { font-size:  70%; font-weight: normal; line-height: 30%; text-align: center;}");
//
//  f_fn_prtlin( "    PRE {");
//  f_fn_prtlin( "      text-align:  left;");
///*   f_fn_prtlin( "      font-size:   90%;"); */
//  f_fn_prtlin( "      display: inline-block;");
//
///*   f_fn_prtlin( "      border-style: solid;"); */
///*   f_fn_prtlin( "      border-color: #e4dfae; "); */
///*   f_fn_prtlin( "      border-width: 5px;"); */
//
//  f_fn_prtlin( "      background-color: #fcfce0;");
//  f_fn_prtlin( "      border: none;");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
///*   f_fn_prtlin( "      line-height: 90%;"); */
///*   f_fn_prtlin( "      font-size: 85%;"); */
//  f_fn_prtlin( "      font-size: 75%;");
//
//  f_fn_prtlin( "      border-spacing: 0;");
///*       border-collapse: collapse; */
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      font-weight: normal;");
///*   f_fn_prtlin( "      line-height: 100%;"); */
//  f_fn_prtlin( "      margin:0 auto;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    P { ");
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      width: auto;");
//  f_fn_prtlin( "      font-size:   93%;");
//  f_fn_prtlin( "      margin-top: 0;");
//  f_fn_prtlin( "      margin-bottom: 0;");
//  f_fn_prtlin( "      margin-left: auto;");
//  f_fn_prtlin( "      margin-right:auto;");
///*   f_fn_prtlin( "      padding-left: 5%;"); */
///*   f_fn_prtlin( "      padding-right:5%;"); */
///*   f_fn_prtlin( "      text-align: center;"); */
//  f_fn_prtlin( "      text-align: left;");
//  f_fn_prtlin( "    }");
///* for table: */
///*       border: 2px solid black; */
///*       cellspacing: 0; */
///*       border-top: 0; */
///*       border-bottom: 0; */
//  f_fn_prtlin( "    table {");
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.center {");
//  f_fn_prtlin( "      margin-left:auto;");
//  f_fn_prtlin( "      margin-right:auto;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    TD {");
//  f_fn_prtlin( "      white-space: nowrap;");
//  f_fn_prtlin( "      padding: 0;");
//  f_fn_prtlin( "    }");
//
//  f_fn_prtlin( "    .row4        { background-color:#f8f0c0; }");
//
///*   f_fn_prtlin( "    .cGr2        { background-color:#d0fda0; }");
//*   f_fn_prtlin( "    .cGre        { background-color:#e1fdc3; }");
//*   f_fn_prtlin( "    .cRed        { background-color:#ffd9d9; }");
//*   f_fn_prtlin( "    .cRe2        { background-color:#fcb9b9; }");
//*/
//
///*   p_fn_prtlin( "    .cGr2        { background-color:#d0fda0; }"); */
///*   f_fn_prtlin( "    .cGr2        { background-color:#8bfd87; }"); */
///*   f_fn_prtlin( "    .cGr2        { background-color:#66ff33; }"); */
//
///*   p_fn_prtlin( "    .cGre        { background-color:#e1fdc3; }"); */
///*   f_fn_prtlin( "    .cGre        { background-color:#ccffb9; }"); */
///*   p_fn_prtlin( "    .cRed        { background-color:#ffd9d9; }"); */
///*   f_fn_prtlin( "    .cRed        { background-color:#ffcccc; }"); */
///*   p_fn_prtlin( "    .cRe2        { background-color:#fcb9b9; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#fc8888; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#ff6094; }"); */
///*   f_fn_prtlin( "    .cRe2        { background-color:#ff3366; }"); */
//
//  // take away bold   "o" = ordinary
//  //
//  f_fn_prtlin("    .oGr2        { background-color:#80ff40; }");
//  f_fn_prtlin("    .oGre        { background-color:#c0ffc0; }");
//  f_fn_prtlin("    .oNeu        { background-color:#edebd8; }");
//  f_fn_prtlin("    .oRed        { background-color:#ffb5c9; }");
//  f_fn_prtlin("    .oRe2        { background-color:#ff7ba3; }");
//
//
////  f_fn_prtlin( "    .cGr2        { background-color:#66ff33; }");
//  f_fn_prtlin( "    .cGr2        { background-color:#80ff40; }");
///*   f_fn_prtlin( "    .cGre        { background-color:#84ff98; }"); */
////  f_fn_prtlin( "    .cGre        { background-color:#a8ff98; }");
//  f_fn_prtlin( "    .cGre        { background-color:#c0ffc0; }");
////  f_fn_prtlin( "    .cRed        { background-color:#ff98a8; }");
//  f_fn_prtlin( "    .cRed        { background-color:#ffb5c9; }");
////  f_fn_prtlin( "    .cRe2        { background-color:#ff4477; }");
//  f_fn_prtlin( "    .cRe2        { background-color:#ff7ba3; }");
//
///*   f_fn_prtlin("    .cNeu        { background-color:#e1ddc3; }"); */
////  f_fn_prtlin("    .cNeu        { background-color:#e5e2c7; }");
//  f_fn_prtlin("    .cNeu        { background-color:#edebd8; }");
////  f_fn_prtlin("    .cNeu        { background-color:#f5f4ea; }");
//
//  f_fn_prtlin( "    .cSky        { background-color:#3f3ffa; }");
//
//  f_fn_prtlin( "    .star        { color:#f7ebd1; }");
//
//  //f_fn_prtlin("     .cNam        { color:#3f3ffa;");
//  f_fn_prtlin("     .cNam        {               ");   // no blue name
//  f_fn_prtlin("                   background-color: #F7ebd1;");
//  f_fn_prtlin("                   font-size: 133%;");
//  f_fn_prtlin("    }");
//
//  f_fn_prtlin( "    table.trait {");
//  f_fn_prtlin( "      margin-left: auto;");
//  f_fn_prtlin( "      margin-right:auto;");
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      text-align: left;");
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait td {");
///*   f_fn_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//  f_fn_prtlin( "      white-space: pre;");
//
//
//  //f_fn_prtlin( "      font-size: 90%;");
//  //f_fn_prtlin( "      font-size: 150%;");
//
////  f_fn_prtlin( "      font-size: 1.2em;");
////  f_fn_prtlin( "      line-height: 1.5em;");
//  f_fn_prtlin( "      font-size: 1.2em;");
//  f_fn_prtlin( "      line-height: 1.4em;");
//
//
//  f_fn_prtlin( "      text-align: left;");
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      border-collapse: collapse;");
//  f_fn_prtlin( "      border-spacing: 0;");
//  f_fn_prtlin( "      padding-left: 10px; ");
//  f_fn_prtlin( "      padding-right: 10px; ");
//
//  f_fn_prtlin( "      padding-top: 2px; ");
//  f_fn_prtlin( "      padding-bottom: 2px; ");
////  f_fn_prtlin( "      padding-top: 5px; ");
////  f_fn_prtlin( "      padding-bottom: 5px; ");
////
//
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait th{");
///*   f_fn_prtlin( "      font-family: Trebuchet MS, Arial, Verdana, sans-serif;"); */
////  f_fn_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fn_prtlin( "  font-family: Menlo, Monaco, Consolas, \"Lucida Console\", \"Andale Mono\", Monospace, \"Courier New\" "); 
//
//  //f_fn_prtlin( "      font-size: 90%;");
////  f_fn_prtlin( "      font-size: 1.5em;");
//  f_fn_prtlin( "      font-size: 1.2em;");
//
//  f_fn_prtlin( "      padding: 10px; ");
//
///*   f_fn_prtlin( "      background-color: #e1fdc3 ;"); */
//  f_fn_prtlin( "      background-color: #fcfce0;");
//
///*   f_fn_prtlin( "      border: 1px solid black;"); */
//  f_fn_prtlin( "      border: none;");
//
//  f_fn_prtlin( "      text-align: center;");
//  f_fn_prtlin( "    }");
//  f_fn_prtlin( "    table.trait       td { text-align: left; }");
//  f_fn_prtlin( "    table.trait    td+td { text-align: right; }");
//  f_fn_prtlin( "    table.trait td+td+td { text-align: left; }");
//
//  f_fn_prtlin( "  </style>");
//
///* put in (new) favicon */
//    f_fn_prtlin("<link href=\"data:image/x-icon;base64,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\" rel=\"icon\" type=\"image/x-icon\" />");
//
//  //
//  //   old favicon   follows
//  //
////  f_fn_prtlin("<link href=\"data:image/x-icon;base64,iVBORw0KGgoAAAANSUhEUgAAAB0AAAAcCAYAAACdz7SqAAAEJGlDQ1BJQ0MgUHJvZmlsZQAAOBGFVd9v21QUPolvUqQWPyBYR4eKxa9VU1u5GxqtxgZJk6XtShal6dgqJOQ6N4mpGwfb6baqT3uBNwb8AUDZAw9IPCENBmJ72fbAtElThyqqSUh76MQPISbtBVXhu3ZiJ1PEXPX6yznfOec7517bRD1fabWaGVWIlquunc8klZOnFpSeTYrSs9RLA9Sr6U4tkcvNEi7BFffO6+EdigjL7ZHu/k72I796i9zRiSJPwG4VHX0Z+AxRzNRrtksUvwf7+Gm3BtzzHPDTNgQCqwKXfZwSeNHHJz1OIT8JjtAq6xWtCLwGPLzYZi+3YV8DGMiT4VVuG7oiZpGzrZJhcs/hL49xtzH/Dy6bdfTsXYNY+5yluWO4D4neK/ZUvok/17X0HPBLsF+vuUlhfwX4j/rSfAJ4H1H0qZJ9dN7nR19frRTeBt4Fe9FwpwtN+2p1MXscGLHR9SXrmMgjONd1ZxKzpBeA71b4tNhj6JGoyFNp4GHgwUp9qplfmnFW5oTdy7NamcwCI49kv6fN5IAHgD+0rbyoBc3SOjczohbyS1drbq6pQdqumllRC/0ymTtej8gpbbuVwpQfyw66dqEZyxZKxtHpJn+tZnpnEdrYBbueF9qQn93S7HQGGHnYP7w6L+YGHNtd1FJitqPAR+hERCNOFi1i1alKO6RQnjKUxL1GNjwlMsiEhcPLYTEiT9ISbN15OY/jx4SMshe9LaJRpTvHr3C/ybFYP1PZAfwfYrPsMBtnE6SwN9ib7AhLwTrBDgUKcm06FSrTfSj187xPdVQWOk5Q8vxAfSiIUc7Z7xr6zY/+hpqwSyv0I0/QMTRb7RMgBxNodTfSPqdraz/sDjzKBrv4zu2+a2t0/HHzjd2Lbcc2sG7GtsL42K+xLfxtUgI7YHqKlqHK8HbCCXgjHT1cAdMlDetv4FnQ2lLasaOl6vmB0CMmwT/IPszSueHQqv6i/qluqF+oF9TfO2qEGTumJH0qfSv9KH0nfS/9TIp0Wboi/SRdlb6RLgU5u++9nyXYe69fYRPdil1o1WufNSdTTsp75BfllPy8/LI8G7AUuV8ek6fkvfDsCfbNDP0dvRh0CrNqTbV7LfEEGDQPJQadBtfGVMWEq3QWWdufk6ZSNsjG2PQjp3ZcnOWWing6noonSInvi0/Ex+IzAreevPhe+CawpgP1/pMTMDo64G0sTCXIM+KdOnFWRfQKdJvQzV1+Bt8OokmrdtY2yhVX2a+qrykJfMq4Ml3VR4cVzTQVz+UoNne4vcKLoyS+gyKO6EHe+75Fdt0Mbe5bRIf/wjvrVmhbqBN97RD1vxrahvBOfOYzoosH9bq94uejSOQGkVM6sN/7HelL4t10t9F4gPdVzydEOx83Gv+uNxo7XyL/FtFl8z9ZAHF4bBsrEwAAAAlwSFlzAAALEwAACxMBAJqcGAAABTRJREFUSA21lmtsVEUUx/9zH+xu243pUvqwqfKQVhGVZwqCvBVRiRBJMIGI4QMfjFFBTEQTS4gx+EEJBtMYDDF8ABJCApIGial+kJY2LAgFAoXKo1QUSwoLLPu69x7/s63b5bGFSDnN9M7snTm/OY85dxDrPCJnj9XLKy9NldKSIgHQ761oYKHMnDZRDjfuFM3DtYthmT6lWmzb6ndYtgGWZcmE8c9J59n9YjUdaEFD0yGkUg7n9I9YFjBsmInKSgXLUjh40EV7u4MDh47h+83bgSWL5vebhfn5SubOtaS21i/NzXnS2logp08XSF1dQMrLjTSneFBI8Hz16AeG2gMgc+ZYsnlzgKB8iUQKxPOCItLdEomgzJplZjgW39y/TxVQYRgYDIVHuCrJpZEgMH+5hXlv2qioUMjL46R0Lt6qNhLpHVtK6Un3liGmiQUEjuX8Qk7Xzoqz3UgJypoA/1AP4XbgZLuHZ0YYmDjRzCgNh120trqZMUN+b3mBwJWGiRG00M/pOuUSShDnM8ZB/DcPbSc9HA8A30VdjJxkZqCJBLB+fQrXrvVy7gl9lsAvTAujDMBkS2pIer2CR7ArCqmEINEBlDFUk12Fglf/857Cli1J7NmT6iWy1yc0QFeuUCaqfQrGkwpCj5l/0KdXhUBAO0yrs9nXivx8NblQYdwimyOFpiYHa9cmcP06h1nSJ3QcY/gyFxshBTWGzaMquslmUphMFpPvup8cEyjcxdNLLVSONdF2xsOqVQm0tfHFbdIndBrjGKRi0RlziSu11xijdHL2eLD7oeC6gkEvmnhquY1kl4dvPk6gsdGFx43eLn1AFYaRlWQche7xhQX0NNwuupQkrcslXT8dRxAcb6DqS6qjyYdWpnCmTpBM3o7rHueE+pimoaBC7Iog5Sg4nTSUMBqEJGFaX7rPxAqMMzBknQW7hCXvIwftu1yY+hDnENpxpzBh8e4HNipnGIhQc4yQKDMz6rHPp87euO4T6J+uMHSDBbNU4ciHKXTsdJCK6TW55a7QhQttrHjfh9AUoxdI8A0NZ7vJghDnxoJLaOEGG8KifvS9FP780UWStIShcIHzcskd7q2uNlFTMwCPlgK/BDwWAaCYCgyeR529OjGswQqD3jERWmDi6nEPp9YmcfkAzyot5zScI+2C9n0OuQUa4tFYvdqH4cON9D43/uyggG58i5qEf74ihdBrBkreNuGrUujY5uB8rYPIGVrOzbAuIMaCUc/5Ohy55Bbo4sU2pk7l6eNivca2BeHHgBmlBkZXKxTNNlAw0kQyKjhR4+DibhexSz1JxTVxtp8IbHFoch+SgRYXKyxbZiHA+qlFgz/9xIe/l3p4otBA0UADJj8tF5mZ5zam0PU7szqqj023hX9xfj03ut91espkWs1d/2Wgo1hcKyuZHVlSVWWkXc3ChOZmF1s/d+DuFZR0CAIEOPydxxb0Lo65Hi6IR7dmKcjRzUD1tcLWJTMjLOiMZ0uLhx07Uti9m/FjaTNYKPLoBh+b1q+PkI7fDfYZ1vuSzEc8HHawaZODSfwsJXmwT/JTtW+fi4YGws4LLl/uNaGLEMXW+8t9sTKTLL/flx50suKsWRNHWRmrD/PgCiuRBmV/8TOr2Pm/wLSOb7/6TK/PtB6vZcbZ7/qjv2DebEH7iV+lorz0oUGyN6ov3frCjZv/HJZtP3wtgx8vf6jg8rJiqV1XI5qn9DXfY207evwUtm6vw976fYhGb/Kc8uA9oOibZn5+HmZOm4A3Xp+N8WNG8vJt4V9WJNqNs7nSyAAAAABJRU5ErkJggg==\" rel=\"icon\" type=\"image/x-icon\" />");
//
//  f_fn_prtlin( "</head>");
//  f_fn_prtlin( " ");
//  f_fn_prtlin("\n<body>");
//
///*   sprintf(writebuf, "\n  <h1>Calenday Day <br></h1>"); 
//*   f_fn_prtlin(writebuf);
//* 
//*   sprintf(writebuf, "\n  <h2>%s, %s %d, %d<br></h2>",
//*     fN_day_of_week[ day_of_week(itarget_mm, itarget_dd, itarget_yyyy) ],
//*     N_mth_cap[itarget_mm], 
//*     itarget_dd,
//*     itarget_yyyy  );
//*   f_fn_prtlin(writebuf);
//*/
///*   sprintf(writebuf, "\n  <h1>Calendar Day &nbsp&nbsp%s, %s %d, %d</h1>",
//*     fN_day_of_week[ day_of_week(itarget_mm, itarget_dd, itarget_yyyy) ],
//*     N_mth_cap[itarget_mm], 
//*     itarget_dd,
//*     itarget_yyyy   );
//*   f_fn_prtlin(writebuf);
//*/
///*   <h1>Calendar Day </h1>
//*   <h1>Wed &nbspMay 21 2014 </h1>
//*   <h2><br><br>for <span class="cNam">ulli</span><br></h2>
//*/
//
//
//  //f_fn_prtlin("<div><br></div>");
//
//
////  f_fn_prtlin("  <h1>Calendar Day </h1>");
////  f_fn_prtlin("  <h1>What Color is Today?</h1>");  // 20150215
//
//  sprintf(writebuf, "   <h1>%s &nbsp%s %02d,  %d</h1>",
//    fN_day_of_week[ day_of_week(itarget_mm, itarget_dd, itarget_yyyy) ],
//    N_mth_cap[itarget_mm], 
//    itarget_dd,
//    itarget_yyyy   );
//  f_fn_prtlin(writebuf);
//
//
////  sprintf(writebuf, "  <h2><br><br>for <span class=\"cNam\">%s</span><br></h2>",
////    person_name    ); 
////  f_fn_prtlin(writebuf);
////
//
///* <table> <tr> <th colspan="3"><br>The "compatibility score" of this pair<br>as a group with 2 members.<br>&nbsp</th> </tr>  */
//
//
///*   f_fn_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\"><br> \"How was your day?\"<br>&nbsp</th> </tr>"); */
//
//
////  f_fn_prtlin("  <div><br></div>");
//
//
//  //f_fn_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\"> How was your day?</th> </tr>");
//  //f_fn_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\"><span style=\"font-size:4m;\">   What Color is Today?  </span></th> </tr>");
////  f_fn_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\">&nbsp What Color is Today? &nbsp</th> </tr>");
//  f_fn_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\">&nbsp What Color is The Day? &nbsp</th> </tr>");
//
////  f_fn_prtlin("<table class=\"trait\">" );
////  f_fn_prtlin("  <div><br></div>");
//
//  //f_fn_prtlin("<div> <span style=\"font-size: 1.0em\"><br>produced by iPhone app \"Me and my BFFs\"</span><br><br><span style=\"font-size: 0.7em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div><div><br></div>");
//  //f_fn_prtlin("  <tr > <th><span style=\"font-size: 0.65em; font-weight: normal; \">Person</span></th> <th><span style=\"font-size: 0.65em; font-weight: normal; \">Score</span></th> <th></th></tr>");
////  f_fn_prtlin("  <tr > <th><span style=\"font-size: 0.7em; font-weight: normal; \">Person</span></th> <th><span style=\"font-size: 0.7em; font-weight: normal; \">Score</span></th> <th></th></tr>");
//  f_fn_prtlin("  <tr > <th><span style=\"font-size: 0.8em; font-weight: normal; \">Person</span></th> <th><span style=\"font-size: 0.8em; font-weight: normal; \">Score</span></th> <th></th></tr>");
//
//
//trn("score_B      ");
//  int worknum;  /* calibrate stress score for table */
//    worknum = targetDayScore;
//    worknum = worknum * -1; 
//    worknum = worknum + 900;
//    if (worknum <= 0) worknum = 1;
//kin(worknum);
//    worknum = mapNumStarsToBenchmarkNum(IDX_FOR_SCORE_B, worknum);
//kin(worknum);
//    targetDayScore = worknum;
//    PERCENTILE_RANK_SCORE = mapBenchmarkNumToPctlRank(targetDayScore);
//kin(PERCENTILE_RANK_SCORE);
//
//
//
////  /*  for TEST */
////static int oij;
////oij++;
////if (oij  == 2) PERCENTILE_RANK_SCORE = 10;
////if (oij  == 3) PERCENTILE_RANK_SCORE = 25;
////if (oij  == 4) PERCENTILE_RANK_SCORE = 50;
////if (oij  == 5) PERCENTILE_RANK_SCORE = 75;
////if (oij  == 6) PERCENTILE_RANK_SCORE = 90;
////
//
//
//
//
////tn();trn("COLOUR #1"); kin(PERCENTILE_RANK_SCORE );ksn(person_name);
//
//  if ( PERCENTILE_RANK_SCORE >= 90)
//  {
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                          // score is great cGr2
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td>     </td> <td></td> </tr>"); 
//
//  } else if ( PERCENTILE_RANK_SCORE >= 75  &&  PERCENTILE_RANK_SCORE  < 90 )
//  {
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                          // score is great cGr2
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td>     </td> <td></td> </tr>"); 
//  }
//  else if ( PERCENTILE_RANK_SCORE  < 75  &&  PERCENTILE_RANK_SCORE >= 50 )
//  {
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                        // score is above avg
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td>     </td> <td></td> </tr>"); 
//  }
//  else if ( PERCENTILE_RANK_SCORE  < 50  &&  PERCENTILE_RANK_SCORE >  25 ) 
//  {
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                        // score is below avg
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td>     </td> <td></td> </tr>"); 
//  }
//  else if ( PERCENTILE_RANK_SCORE  <= 25  &&  PERCENTILE_RANK_SCORE >  10 )  
//  {
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                          // score is stress cRed
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td>     </td> <td></td> </tr>"); 
//  }
//  else if ( PERCENTILE_RANK_SCORE  <= 10)  
//  {
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//    f_fn_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");  
//    f_fn_prtlin("  <tr class=\"cRed\"><td></td> <td>     </td> <td></td> </tr>"); 
//    f_fn_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    write_calendar_day_score(person_name, PERCENTILE_RANK_SCORE);                          // score is stress cRed
//  } else {
//    ;
//  }
//
//
//  f_fn_prtlin("  </table>");
///*   f_fn_prtlin("  <div><br><br></div>"); */
//  f_fn_prtlin("  <div><br></div>");
//
///*   f_fn_prtlin("<pre><br>  Check out group report Best Day.  <br>");
//*   f_fn_prtlin("     For \"How was your year?\"  ");
//*   f_fn_prtlin("  check out report Calendar Year  <br>");
//*   f_fn_prtlin("</pre>");
//*   f_fn_prtlin("  <div><br><br></div>");
//*   f_fn_prtlin("<pre><br>     This only covers short-term influences ");
//*   f_fn_prtlin("     of a few hours or a day or two.<br>");
//*   f_fn_prtlin("</pre>");
//*/
///*   f_fn_prtlin("<pre><br>  This is about shorter influences  "); */
//
//  f_fn_prtlin("  <pre>");         
//  gblWeAreInPREblockContent = 1;  /* true */
//  f_fn_prtlin("<br>  This measures short-term influences  ");
//
///*   f_fn_prtlin("  lasting a few hours or a day.<br>"); */
//  f_fn_prtlin("  lasting a few hours.<br>");
//
///*   f_fn_prtlin("  Long term influences are in the  "); */
///*   f_fn_prtlin("  graphical report \"Calendar Year\" <br>"); */
//
//  //f_fn_prtlin("  More important long term influences are  ");
//  f_fn_prtlin("  More important long term influences  ");
//  //f_fn_prtlin("  in the graphical report \"Calendar Year\" <br>");
//  f_fn_prtlin("  are in the report \"Calendar Year\" <br>");
//
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fn_prtlin("</pre>");
//
//
///*   f_fn_prtlin("<h5><br><br>produced by iPhone app Astrology by Measurement</h5>"); */
//
////  sprintf(writebuf, "<h5><br><br><br>produced by iPhone app %s</h5>", APP_NAME);
////  f_fn_prtlin(writebuf);
//  //f_fn_prtlin("<h4><span style=\"background-color:#FFBAC7;\">&nbspThis report is for entertainment purposes only.&nbsp</span></h4>");
//
//
//  //f_fn_prtlin("<div> <span style=\"font-size: 1.0em\"><br>produced by iPhone app \"Me and my BFFs\"</span><br><br><span style=\"font-size: 0.9em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div><div><br></div>");
//  //f_fn_prtlin("<div> <span style=\"font-size: 0.8em\"><br>produced by iPhone app \"Me and my BFFs\"</span><br><span style=\"font-size: 0.8em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div><div><br></div>");
//  //f_fn_prtlin("<div> <span style=\"font-size: 0.5em\"><br>produced by iPhone app \"Me and my BFFs\"</span><br><span style=\"font-size: 0.5em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div><div><br></div>");
//
//
//  char workProducedBy[256];
//  sprintf(workProducedBy,
//    "<div> <span style=\"font-size: 0.5em\"><br><br>produced by iPhone app \"%s\"</span><br><span style=\"font-size: 0.5em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div>",
//    APP_NAME
//  ); 
//
////  f_fn_prtlin("<div> <span style=\"font-size: 0.5em\"><br><br>produced by iPhone app \"Me and my BFFs\"</span><br><span style=\"font-size: 0.5em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div>");
//  f_fn_prtlin( workProducedBy );
//
//  f_fn_prtlin("</table>");
//
//  f_fn_prtlin("</body>");
//  f_fn_prtlin("</html>");
//
//
//  gblCalDayScoreIsWritten = 0;  /* re-init */
//
////  fclose_fpdb_for_debug();
//
////  /* FLUSH and CLOSE output HTML file
////  */
////  fflush(Fp_f_HTML_file);
////  if (fclose(Fp_f_HTML_file) == EOF) {
////    ;
//////trn("FCLOSE FAILED !!!   #1  ");
////  } else {
////    ;
//////trn("FCLOSE SUCCESS !!!  #1  ");
////  };
////
//
//  return(0);
//
//} /* end of make_calendar_day_html_file() */
//
//
// make_calendar_day_html_file() not used  20210402


void write_calendar_day_score(char *pname, int istress_score) {
  char rowcolor[32];

/* kin(gblCalDayScoreIsWritten); */

  if (gblCalDayScoreIsWritten == 1)  return;

//  if (istress_score >= 90) strcpy(rowcolor, " class=\"oGr2\"");
//  if (istress_score <  90 &&
//      istress_score >= 75) strcpy(rowcolor, " class=\"oGre\"");
//  if (istress_score <  75 &&
//      istress_score >= 25) strcpy(rowcolor, " class=\"oNeu\"");
//  if (istress_score <= 25 &&
//      istress_score >  10) strcpy(rowcolor, " class=\"oRed\"");
//  if (istress_score <= 10) strcpy(rowcolor, " class=\"oRe2\"");

  if (istress_score >= 90) strcpy(rowcolor, " class=\"cGr2\"");
  if (istress_score <  90 &&
      istress_score >= 75) strcpy(rowcolor, " class=\"cGre\"");
  if (istress_score <  75 &&
      istress_score >= 25) strcpy(rowcolor, " class=\"cNeu\"");
  if (istress_score <= 25 &&
      istress_score >  10) strcpy(rowcolor, " class=\"cRed\"");
  if (istress_score <= 10) strcpy(rowcolor, " class=\"cRe2\"");

/*   sprintf(writebuf, "  <tr><td> %s</td><td> %d  </td><td></td></tr>", pname, istress_score); */
  sprintf(writebuf, "  <tr %s><td> %s</td><td> %d  </td><td></td></tr>", rowcolor, pname, istress_score);

//tn();tr("calendar day score=");ksn(writebuf);tn();

  f_fn_prtlin(writebuf);  //  this does extra processing to mess up

//
//  //  f_fn_prtlin(writebuf);   this does extra processing to mess up
//  //
//  // these are globals:
//  //        FILE *Fp_f_HTML_file;
//  //        int   n;
//  //        char *p = &writebuf[0];
//  //
////  n = sprintf(p,"%s%s", writebuf, myEOL);
//  n = sprintf(p,"%s%s\n", writebuf);
//  fput(p, n, Fp_f_HTML_file);        /* PRINT the line */
//


  gblCalDayScoreIsWritten = 1;
}


// =========================  BIG versions of functions needed  =========================

//
//void f_fnBIGOutPutTopOfHtmlFile(void)
//{
//  int i;
//
///* trn("in f_fnBIGOutPutTopOfHtmlFile()");  */
//
//  /* 1. read until [beg_topinfo1]  (name)
//  */
//  for (i=0; ; i++) {
//    f_docin_get(doclin);
//    if (strstr(doclin, "[beg_topinfo1]") != NULL) break;
//  }
//
//  /* then save lines until graph until [end_topinfo1] 
//  * then put out html 
//  */
//  for (i=0; ; i++) {
//    f_docin_get(doclin);
//    if (strstr(doclin, "[end_topinfo1]") != NULL) break;
//
//    strcpy(f_arr(i), doclin);
//  }
//
///*    for (k=0; k < i; k++) ksn(arr(k)); */
//
//
//
///*   f_fnBIG_prtlin( "<!doctype html public \"-//w3c//dtd html 4.0 transitional//en\">"); */
///*   f_fnBIG_prtlin( "  \"http://www.w3.org/TR/html4/strict.dtd\">"); */
///*   f_fnBIG_prtlin( "  \"http://www.w3.org/TR/html4/loose.dtd\">"); */
//
///*   at end, change to STRICT  (maybe) */
//  f_fnBIG_prtlin( "<!doctype html public \"-//w3c//dtd html 4.01 transitional//en\" ");
//  f_fnBIG_prtlin( "  \"http://www.w3.org/TR/html4/loose.dtd\">");
//
//  f_fnBIG_prtlin( "<html>");
//  f_fnBIG_prtlin( "\n<head>");
///*   f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0\"> " ); */
//
//  /* IT TURNS OUT this <title> is used as the default filename when the html report
//  *  is emailed, you open it, and do "Save As".
//  *  Therefore, used the "real" file name with no advertising.  Rats.
//  */
//
///*   sprintf(writebuf, "  <title>%s %s Calendar Year produced by iPhone/iPad app named %s.</title>",arr(1),arr(2), APP_NAME); * lance 2013 * */
///*   sprintf(writebuf, "  <title>%s %s Calendar Year produced by iPhone app %s.</title>",arr(1),arr(2), APP_NAME);  */
//
//
//  /* if HTML filename, gbl_ffnameHTML, has any slashes, grab the basename
//  */
//  char myBaseName[256], *myptr;
//  if (sfind(gbl_ffnameHTML, '/')) {
//    myptr = strrchr(gbl_ffnameHTML, '/');
//    strcpy(myBaseName, myptr + 1);
//  } else {
//    strcpy(myBaseName, gbl_ffnameHTML);
//  }
//  sprintf(writebuf, "  <title>%s</title>", myBaseName);
//
//
//  f_fnBIG_prtlin(writebuf);
//  
//  /* HEAD  META
//  */
//  sprintf(writebuf, "  <meta name=\"description\" content=\"Calendar Year for Person produced by iPhone App %s\"> ", APP_NAME);
//  f_fnBIG_prtlin( writebuf); 
//
//
//  f_fnBIG_prtlin( "  <meta http-equiv=\"Content-Type\" content=\"text/html\"; charset=\"iso-8859-1\">"); 
///*   f_fnBIG_prtlin( "  <meta name=\"Author\" content=\"Author goes here\">"); */
//
//
///*   f_fnBIG_prtlin( "  <meta name=\"keywords\" content=\"GMCR,group,member,astrology,future,past,calendar,year,compatibility,personality\"> "); */
///*   f_fnBIG_prtlin( "  <meta name=\"keywords\" content=\"measure,group,member,best,match,calendar,year,passionate,personality\"> "); */
///*   f_fnBIG_prtlin( "  <meta name=\"keywords\" content=\"women,woman,BFF,astrology,compatibility,group,best,match,personality,calendar,year,stress\"> "); */
///*   f_fnBIG_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,astrology,compatibility,group,best,match,personality,stress,calendar,year\"> ");  * 96 chars * */
//  f_fnBIG_prtlin( "  <meta name=\"keywords\" content=\"women,woman,female,BFF,me,compatibility,group,best,match,personality,stress,calendar,year\"> ");  /* 89 chars */
//
//
//
//  /* get rid of CHROME translate "this page is in Galician" 
//  * do you want to translate?
//  */
//  f_fnBIG_prtlin("  <meta name=\"google\" content=\"notranslate\">");
//  f_fnBIG_prtlin("  <meta http-equiv=\"Content-Language\" content=\"en\">");
//
//
//  /* Using the Viewport Meta Tag  (in iOS webView)
//  * https://developer.apple.com/library/safari/documentation/AppleApplications/Reference/SafariWebContent/UsingtheViewport/UsingtheViewport.html#//apple_ref/doc/uid/TP40006509-SW25
//  *
//  * For example, TO SET THE VIEWPORT WIDTH TO THE WIDTH OF THE DEVICE, add this to your HTML file:
//  * <meta name="viewport" content="width=device-width"> 
//  * To set the initial scale to 1.0, add this to your HTML file:
//  * <meta name="viewport" content="initial-scale=1.0"> 
//  * To set the initial scale and to turn off user scaling, add this to your HTML file:
//  * <meta name="viewport" content="initial-scale=2.3, user-scalable=no">
//  */
///*   f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width\" />"); */
///*   f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0\"> "); */
//// <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
///*   f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maxium-scale=1.0 />\" " ); */
///*   f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0\"> " ); */
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0\"> "); // OK but big on iPhone  ipad change bad
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=0.5\"> "); // squiggly
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0, maximum-scale=1.0 \"> "); // OK but big on iPhone  ipad change bad
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0\"> " );//no
//
//
////f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\"> " );
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> " );
//
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0\"> "); // OK but big on iPhone  ipad change bad
//
//  // set only device-width
//  //f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0;\"> " );
//  //f_fnBIG_prtlin("  <meta name=\"viewport\"; initial-scale=1.0;\"> " );
//  // f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0;\"> " );
//  //f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0\"> "); // OK but big on iPhone  ipad change bad
//  //f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0\"> " );//no
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0, maximum-scale=1.0 \"> "); // OK but big on iPhone  ipad change bad
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> " );
//
//// OLD GOLD    f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"width=device-width, user-scalable=no\"> " ); // best graph fits device-width portrait and landscape and iPad OK!
//
////  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0\"> "); // OK but big on iPhone  ipad change bad
//  //f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=0.75\"> "); // bad
//  f_fnBIG_prtlin("  <meta name=\"viewport\" content=\"initial-scale=1.0; \"> "); // 
//  f_fnBIG_prtlin("  <meta name = \"format-detection\" content = \"telephone=no\">");
//
//  /* HEAD   STYLE/CSS
//  */
//  f_fnBIG_prtlin( "\n  <style type=\"text/css\">");
////  f_fnBIG_prtlin( "    @media print { PRE {  page-break-inside:avoid; } }");
//  f_fnBIG_prtlin( "    @media print { PRE {  page-break-inside:avoid; } }");
//
//// none of these work
////  f_fnBIG_prtlin( "     -webkit-text-size-adjust: none; ");
////  f_fnBIG_prtlin( "     -webkit-text-size-adjust: auto; ");
////  f_fnBIG_prtlin( "     -webkit-text-size-adjust: 100%; ");
//
//  f_fnBIG_prtlin( "    BODY {");
///*   f_fnBIG_prtlin( "      width:100%;"); */
///*   f_fnBIG_prtlin( "      height:100%;"); */
///* f_fnBIG_prtlin("     position:fixed;"); */
///* f_fnBIG_prtlin("     top:0;"); */
///* f_fnBIG_prtlin("     bottom:0;"); */
///* f_fnBIG_prtlin("     left:0;"); */
///* f_fnBIG_prtlin("     right:0;"); */
///* f_fnBIG_prtlin("     font-size:5vmin;"); */
///* f_fnBIG_prtlin(" onresize=onload=function(){document.body.style.fontSize=window.innerWidth}"); */
//
//
//
///*  f_fnBIG_prtlin( "      background-color: #F5EFCF;"); */
//  f_fnBIG_prtlin( "      background-color: #f7ebd1;");
//
///*   f_fnBIG_prtlin( "      font-family: Trebuchet MS, Arial, Verdana, sans-serif;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fnBIG_prtlin( "      font-size:   medium;");
//  f_fnBIG_prtlin( "      font-weight: normal;");
//  f_fnBIG_prtlin( "      text-align:  center;");
///*   f_fnBIG_prtlin( "    <!-- "); */
///*   f_fnBIG_prtlin( "      background-image: url('mkgif1g.gif');"); */
///*   f_fnBIG_prtlin( "    --> "); */
//  f_fnBIG_prtlin( "    }");
//
//  f_fnBIG_prtlin( "    H1 { font-size: 137%; font-weight: bold;   line-height: 95%; text-align: center;}");
//  f_fnBIG_prtlin( "    H2 { font-size: 137%;                      line-height: 25%; text-align: center;}");
//
//  //f_fnBIG_prtlin( "    H3 { font-size: 110%; font-weight: normal; line-height: 30%; text-align: center;}");
//  //f_fnBIG_prtlin( "    H4 { font-size:  75%; font-weight: bold;   line-height: 30%; text-align: center;}");
//  f_fnBIG_prtlin( "    H3 { font-size: 130%; font-weight: normal; line-height: 30%; text-align: center;}");
//  f_fnBIG_prtlin( "    H4 { font-size:  95%; font-weight: bold;   line-height: 30%; text-align: center;}");
//
//  f_fnBIG_prtlin( "    H5 { font-size:  70%; font-weight: normal; line-height: 30%; text-align: center;}");
//
//  f_fnBIG_prtlin( "    .bigfromto {");
//  f_fnBIG_prtlin( "      font-size:  95%; font-weight: bold;                   ; text-align: center;");
//  f_fnBIG_prtlin( "      font-size: 1.0em;");
//  f_fnBIG_prtlin( "      line-height: 1.4em");
//  f_fnBIG_prtlin( "    }");
//
///*   f_fnBIG_prtlin( "    .bigfromto {"); */
///*   f_fnBIG_prtlin( "      margin-top: 0.5em;"); */
///*   f_fnBIG_prtlin( "      margin-bottom: 0.1em;"); */
///*   f_fnBIG_prtlin( "      width: 100%;"); */
///*   f_fnBIG_prtlin( "      text-align: center;"); */
///*   f_fnBIG_prtlin( "      line-height: 145%;"); */
///*   f_fnBIG_prtlin( "      font-size: 150%;"); */
///*   f_fnBIG_prtlin( "      font-weight: bold;"); */
///*   f_fnBIG_prtlin( "      background-color: #F7ebd1;"); */
///*   f_fnBIG_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed"); */
///*   f_fnBIG_prtlin( "    }"); */
//
//
//  f_fnBIG_prtlin( "    PRE {");
///*   f_fnBIG_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fnBIG_prtlin( "      font-weight: normal;");
//  f_fnBIG_prtlin( "      font-size:   75%;");
//  f_fnBIG_prtlin( "      line-height: 70%;");
//  f_fnBIG_prtlin( "      margin:0 auto;");
//  //f_fnBIG_prtlin( "      letter-spacing: -1.2px;");
//  //f_fnBIG_prtlin( "      letter-spacing: -1.1px;");
////  f_fnBIG_prtlin( "      letter-spacing: -2px;");
////  f_fnBIG_prtlin( "      letter-spacing: -1px;"); // moved inline
//
//
//
////  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//  f_fn_prtlin( "      white-space: pre ; display: block; unicode-bidi: embed");
//
//
//
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    .prebox {");
//
///*   f_fnBIG_prtlin( "      display: inline-block;"); */
///*   f_fnBIG_prtlin( "      border-style: solid;"); */
///*   f_fnBIG_prtlin( "      border-color: #e4dfae;"); */
///*   f_fnBIG_prtlin( "      border-width: 5px;"); */
//
//  f_fnBIG_prtlin( "      display: inline-block;");
//  f_fnBIG_prtlin( "      background-color: #fcfce0;");
//  f_fnBIG_prtlin( "      border: none;");
//  f_fnBIG_prtlin( "      border-collapse: collapse;");
//  f_fnBIG_prtlin( "      border-spacing: 0;");
//  f_fnBIG_prtlin( "      line-height: 120%;");
////  f_fnBIG_prtlin( "      font-size: 75%;");
//  f_fnBIG_prtlin( "      font-size: 1.0em;");
//
//  f_fnBIG_prtlin( "    }");
///*   f_fnBIG_prtlin( "    .bgy {background-color:#ffff00;}"); */
////  f_fnBIG_prtlin( "    .bgy {background-color:#fcfc70;}"); // used to be for hdr,ftr
//  f_fn_prtlin( "    .bgy {background-color:#f7ebd1;}");  // make = body bg color
//
//
//  f_fnBIG_prtlin( "    P { ");
///*   f_fnBIG_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fnBIG_prtlin( "      width: auto;");
//  f_fnBIG_prtlin( "      font-size:   80%;");
//  f_fnBIG_prtlin( "      margin-top: 0;");
//  f_fnBIG_prtlin( "      margin-bottom: 0;");
//  f_fnBIG_prtlin( "      margin-left: auto;");
//  f_fnBIG_prtlin( "      margin-right:auto;");
///*   f_fnBIG_prtlin( "      padding-left: 5%;"); */
///*   f_fnBIG_prtlin( "      padding-right:5%;"); */
//  f_fnBIG_prtlin( "      text-align: left;");
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    table {");
//  f_fnBIG_prtlin( "      border-collapse: collapse;");
//  f_fnBIG_prtlin( "      border-spacing: 0;");
//  f_fnBIG_prtlin( "      font-size: 120%;");
//  f_fnBIG_prtlin( "    }");
///* for table: */
///*       border: 2px solid black; */
///*       cellspacing: 0; */
///*       border-top: 0; */
///*       border-bottom: 0; */
//  f_fnBIG_prtlin( "    table.center {");
//  f_fnBIG_prtlin( "      margin-left:auto;");
//  f_fnBIG_prtlin( "      margin-right:auto;");
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    TD {");
//  f_fnBIG_prtlin( "      white-space: nowrap;");
//  f_fnBIG_prtlin( "      padding: 0;");
//  f_fnBIG_prtlin( "      font-size: 1.1em;");
//  f_fnBIG_prtlin( "      line-height: 1.4em");
//  f_fnBIG_prtlin( "    }");
//
///*   f_fnBIG_prtlin("    .cGre        { background-color:#e1fdc3; }");
//*   f_fnBIG_prtlin("    .cGr2        { background-color:#d0fda0; }");
//*   f_fnBIG_prtlin("    .cRed        { background-color:#ffbac1; }");
//*   f_fnBIG_prtlin("    .cRe2        { background-color:#ff596a; }");
//*/
//
///*   p_fn_prtlin( "    .cGr2        { background-color:#d0fda0; }"); */
///*   f_fnBIG_prtlin( "    .cGr2        { background-color:#8bfd87; }"); */
///*   f_fnBIG_prtlin( "    .cGr2        { background-color:#66ff33; }"); */
//
///*   p_fn_prtlin( "    .cGre        { background-color:#e1fdc3; }"); */
///*   f_fnBIG_prtlin( "    .cGre        { background-color:#ccffb9; }"); */
///*   f_fnBIG_prtlin( "    .cGre        { background-color:#84ff98; }"); */
//
///*   p_fn_prtlin( "    .cRed        { background-color:#ffd9d9; }"); */
///*   f_fnBIG_prtlin( "    .cRed        { background-color:#ffcccc; }"); */
///*   f_fnBIG_prtlin( "    .cRed        { background-color:#ff98a8; }"); */
//
///*   p_fn_prtlin( "    .cRe2        { background-color:#fcb9b9; }"); */
///*   f_fnBIG_prtlin( "    .cRe2        { background-color:#fc8888; }"); */
///*   f_fnBIG_prtlin( "    .cRe2        { background-color:#ff6094; }"); */
///*   f_fnBIG_prtlin( "    .cRe2        { background-color:#ff3366; }"); */
//
//
////  f_fnBIG_prtlin( "    .cGr2        { background-color:#66ff33; font-weight: bold; }");
//  f_fnBIG_prtlin( "    .cGr2        { background-color:#80ff40; font-weight: bold; }");
///*   f_fnBIG_prtlin( "    .cGre        { background-color:#84ff98; }"); */
////  f_fnBIG_prtlin( "    .cGre        { background-color:#a8ff98; font-weight: bold; }");
//  f_fnBIG_prtlin( "    .cGre        { background-color:#c0ffc0; font-weight: bold; }");
////  f_fnBIG_prtlin( "    .cRed        { background-color:#ff98a8; font-weight: bold; }");
//  f_fnBIG_prtlin( "    .cRed        { background-color:#ffb5c9; font-weight: bold; }");
////  f_fnBIG_prtlin( "    .cRe2        { background-color:#ff4477; font-weight: bold; }");
//  f_fnBIG_prtlin( "    .cRe2        { background-color:#ff7ba3; font-weight: bold; }");
//
//
//  f_fnBIG_prtlin("    .row4        { background-color:#f8f0c0; }");
//
///*   f_fnBIG_prtlin("    .cNeu        { background-color:#e1ddc3; }"); */
////  f_fnBIG_prtlin("    .cNeu        { background-color:#e5e2c7; font-weight: bold; }");
//  f_fnBIG_prtlin("    .cNeu        { background-color:#edebd8; font-weight: bold; }");
////  f_fnBIG_prtlin("    .cNeu        { background-color:#f5f4ea; font-weight: bold; }");
//
//  f_fnBIG_prtlin("    .cSky        { background-color:#3f3ffa; font-weight: bold; }");
//  f_fnBIG_prtlin( "   .star        { color:#f7ebd1; font-weight: bold; }");
//
//  //f_fnBIG_prtlin("    .cNam        { color:#3f3ffa;");
//  f_fnBIG_prtlin("    .cNam        {               ");   // no blue name
//  f_fnBIG_prtlin("                   background-color: #F7ebd1;");
//  f_fnBIG_prtlin("                   font-size: 133%;");
//  f_fnBIG_prtlin("    }");
//
//
//  f_fnBIG_prtlin( "    table.trait {");
//  f_fnBIG_prtlin( "      font-size: 1.5em;");
//  f_fnBIG_prtlin( "      margin-left: auto;");
//  f_fnBIG_prtlin( "      margin-right:auto;");
///*   f_fnBIG_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fnBIG_prtlin( "      text-align: left;");
//
///*   f_fnBIG_prtlin( "      border: 1px solid black;"); */
//  f_fnBIG_prtlin( "      border: none;");
//
//  f_fnBIG_prtlin( "      border-collapse: collapse;");
//  f_fnBIG_prtlin( "      border-spacing: 0;");
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    table.trait td {");
///*   f_fnBIG_prtlin( "      font-family: Andale Mono, Monospace, Courier New;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
//  f_fnBIG_prtlin( "      white-space: pre;");
///*   f_fnBIG_prtlin( "      font-size: 75%;"); */
//  f_fnBIG_prtlin( "      font-size: 90%;");
//  f_fnBIG_prtlin( "      text-align: left;");
//
///*   f_fnBIG_prtlin( "      border: 1px solid black;"); */
//  f_fnBIG_prtlin( "      border: none;");
//
//  f_fnBIG_prtlin( "      border-collapse: collapse;");
//  f_fnBIG_prtlin( "      border-spacing: 0;");
//  f_fnBIG_prtlin( "      padding-left: 10px; ");
//  f_fnBIG_prtlin( "      padding-right: 10px; ");
//  f_fnBIG_prtlin( "      padding-top: 2px; ");
//  f_fnBIG_prtlin( "      padding-bottom: 2px; ");
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    table.trait th{");
///*   f_fnBIG_prtlin( "      font-family: Trebuchet MS, Arial, Verdana, sans-serif;"); */
//  f_fnBIG_prtlin( "      font-family: Menlo, Andale Mono, Monospace, Courier New;");
///*   f_fnBIG_prtlin( "      font-size: 75%;"); */
//  f_fnBIG_prtlin( "      font-size: 90%;");
//  f_fnBIG_prtlin( "      padding: 10px; ");
//
///*   f_fnBIG_prtlin( "      background-color: #e1fdc3 ;"); */
//  f_fnBIG_prtlin( "      background-color: #fcfce0;");
//
///*   f_fnBIG_prtlin( "      border: 1px solid black;"); */
//  f_fnBIG_prtlin( "      border: none;");
//
//  f_fnBIG_prtlin( "      text-align: center;");
//  f_fnBIG_prtlin( "    }");
//  f_fnBIG_prtlin( "    table.trait       td { text-align: left; }");
//  f_fnBIG_prtlin( "    table.trait    td+td { text-align: right; }");
//  f_fnBIG_prtlin( "    table.trait td+td+td { text-align: left; }");
//
//  f_fnBIG_prtlin( "  </style>");
//
///* from p */
///*   f_fnBIG_prtlin( "      margin-left: 20%;"); */
///*   f_fnBIG_prtlin( "      margin-right:20%;"); */
///*   f_fnBIG_prtlin( "      text-align: left;"); */
//
///*   f_fnBIG_prtlin( "    <!-- "); */
///*   f_fnBIG_prtlin( "    PRE {line-height: 68%}; "); */
///*   f_fnBIG_prtlin( "    P {margin-left:10%; margin-right:10%}"); */
///*   f_fnBIG_prtlin( "    --> "); */
//
//// put in favicon 
////  f_fnBIG_prtlin("<link href=\"data:image/x-icon;base64,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\" rel=\"icon\" type=\"image/x-icon\" />");
//// ------------------------------------------------------
//// put in favicon  (after first comma and before next \"
//f_fnBIG_prtlin("<link href=\"data:image/x-icon;base64,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\" rel=\"icon\" type=\"image/x-icon\" />");
//
//  f_fnBIG_prtlin( "</head>");
//  f_fnBIG_prtlin( " ");
//  f_fnBIG_prtlin("\n<body>");
//
///*   f_fnBIG_prtlin( "<body background=\"file:///mkgif1g.gif\">"); */
///*   f_fnBIG_prtlin( "<body background=\"file:///C/USR/RK/html/mkgif1g.gif\">"); */
//
//  /* a year in the life header output here */
//
//#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
////   sprintf(writebuf, "\n  <h1>%s</h1>", arr(0));
////   f_fnBIG_prtlin(writebuf);
//// 
//// b(2);
//// 
//// /*  <h1><center>A Year in the Life</center></h1>
//// *   <h2><center>of Fred&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<em style="font-size:137%;">2013</em></center></h2>
//// */
//// /*   sprintf(writebuf, "\n  <h2><center>of %s</center></h2>", arr(1)); * Fred * */
////  
//// /*   GOOD-|<span style="background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>| */
//// 
////   sprintf(writebuf, "\n <h2>of %s&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<span style=\"font-size:115%%;\">%s</span><br></h2>", arr(1), arr(2) ); /* of Fred     2013 * */
////   f_fnBIG_prtlin(writebuf);
//#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/
//
///*   n = sprintf(p,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp %s &nbsp&nbsp<span style=\"font-size: 80%%;\">of %s</span> &nbsp&nbsp <span style=\"font-size:115%%;\"> %s </span><br></h1>",
//*       arr(0), arr(1), arr(2)
//*   );
//*/
///*   n = sprintf(p,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp %s of %s &nbsp&nbsp&nbsp %s <br></h1>",
//*       arr(0), arr(1), arr(2)
//*   );
//*/
//
///*   n = sprintf(writebuf,
//*     "<h1>&nbsp&nbsp&nbsp&nbsp Calendar Year &nbsp %s <br></h1>",
//*     arr(2)
//*   );
//*   f_fnBIG_prtlin(writebuf);
//*   n = sprintf(writebuf,
//*     "<h2>&nbsp&nbsp&nbsp&nbsp in the life of %s<br></h2>",
//*     arr(1)
//*   );
//*   f_fnBIG_prtlin(writebuf);
//*/
//
///*     "<h1>&nbsp&nbsp&nbsp&nbsp Calendar Year %s for %s<br></h1>", */
//
//
//  strcpy(gbl_name_for_fut, f_arr(1));  /* for stress num table at bottom */
//  strcpy(gbl_year_for_fut, f_arr(2));  /* for stress num table at bottom */
///*   strcpy(gbl_person_name, arr(1)); */
//
//  f_fnBIG_prtlin("<div><br></div>");
///*   n = sprintf(writebuf, */
///*     "<h1>&nbsp&nbsp&nbsp&nbsp Calendar Year %s for <span class=\"cNam\">%s</span><br></h1>", */
///*     arr(2), arr(1) */
///*   ); */
////    "<h1>Calendar Year %s for <span class=\"cNam\">%s&nbsp&nbsp </span><br></h1>",
////    "<div>Calendar Year %s for <span class=\"cNam\">%s&nbsp&nbsp </span><br></div>",
//
////  f_fnBIG_prtlin( "    H1 { font-size: 137%; font-weight: bold;   line-height: 95%; text-align: center;}");
//  n = sprintf(writebuf,
//    "<div style=\"font-size: 137%%; font-weight: bold;\">Calendar Year %s for <span class=\"cNam\">%s&nbsp&nbsp </span><br></div>",
////    arr(2), arr(1)
//     gbl_year_for_fut, gbl_name_for_fut
//  );
//  f_fnBIG_prtlin(writebuf);
//
//
//  f_fnBIG_prtlin(" ");
//
///*   sprintf(writebuf, "\n  <h3><center>%s</center></h1>", arr(2)); * 2013 *
//*   f_fnBIG_prtlin(writebuf);
//*/
//
//} // end of  f_fnBIGOutPutTopOfHtmlFile(void) {
//


void fn_BIGoutputGrhAndAspects(void)
{
  int i;
  int have_printed_STRESS_line_already;
  int have_printed_OMG_line_already;
/*   char myLastLine[8192]; */
  int num_OMG_printed;

trn(" in fn_BIGoutputGrhAndAspects() ");
gbl_logf_fnBIG_prtlin = 1;

  /* put white space before  graph start
   */
    // NOTE: BIG only for free, so no white space

  if (gblIsThis1stGrhToOutput == 1) {  /* 0 false, 1 true */
    gblIsThis1stGrhToOutput = 0; 

    // put div around the graph which is all a PRE like this:
    //
    //    PRE {
    //      font-family: Menlo, Andale Mono, Monospace, Courier New;
    //      font-weight: normal;
    //      font-size:   75%;
    //      line-height: 70%;
    //      margin:0 auto;
    //      white-space: pre ; display: block; unicode-bidi: embed
    //    }
    //
    f_fnBIG_prtlin("\n<div id='divFUTG' class='cssFUTG' >");           // divFUTG grhFUTG preFUTG
     

/*     f_fnBIG_prtlin("  <pre><br>");          */
//    f_fnBIG_prtlin("  <pre>");         
//    f_fnBIG_prtlin("<pre style=\"letter-spacing: -1px; \">"); // moved inline
//    f_fnBIG_prtlin("<pre style=\"letter-spacing: -1px; display: inline-block; \">"); // moved inline

//    // new div grhFUTG is for thumbnail ( no dates or ticks on the bottom
//    f_fnBIG_prtlin("<div id=\"grhFUTG\"><pre style=\"letter-spacing: -1px; display: inline-block; \">"); // moved inline
//    f_fnBIG_prtlin("<div id=\"grhFUTG\"><pre id=\"preFUTG\" style=\"letter-spacing: -1px; display: inline-block; \">"); // moved inline

    // try NORMAL  letter-spacing
//    f_fnBIG_prtlin("<div id=\"grhFUTG\" class=\"cssgrhFUTG\" ><pre id=\"preFUTG\" class=\"csspreFUTG\"  style=\"                      display: inline-block; \">"); // moved inline
//
    // change pre to div
//    f_fnBIG_prtlin("<div id=\"grhFUTG\" class=\"cssgrhFUTG\" ><div id=\"preFUTG\" class=\"csspreFUTG\"  style=\"  white-space: pre; display: inline-block; \">"); // moved inline


    f_fnBIG_prtlin("<div id=\"grhFUTG\" class=\"cssgrhFUTG\" ><div id=\"preFUTG\" class=\"csspreFUTG\"  style=\"white-space: pre; display: inline-block;  line-height: 57%; font-size: 57%;\">"); // moved inline   // divFUTG grhFUTG preFUTG





    gblWeAreInPREblockContent = 1;  /* true */
    f_fnBIG_prtlin("<br>");         
  } else {
    /* second graph start needs some more white space before it */
    f_fnBIG_prtlin("  <pre><br><br><br><br><br><br><br>"); 

    //gblWeAreInPREblockContent = 1;  /* true */
    //f_fnBIG_prtlin("<br><br><br><br><br><br><br>"); 


    f_fnBIG_prtlin("  <pre>"); 
//    f_fnBIG_prtlin("  <pre style=\"white-space: pre; display: block; unicode-bidi: embed;\" ); >"); 
//    f_fnBIG_prtlin("  <pre style=\"white-space: pre; display: block; unicode-bidi: embed;\" ); >"); 
  }


  // init gbl 
  gbl_we_are_printing_graph = 1;
  gblWeAreInPREblockContent = 1;  /* true */
  gbl_do_second_line = 0;        // for benchmark label insert
  strcpy(gbl_benchmark_label, "no label yet");   // GREAT, OMG, etc.


  /* experiment bg color on left-side column containing label names
  *  This is the 7-char filler (max size "STRESS-" = 7)
  */
/*    char current_leftside[1024]; */
/*    int just_printed_stress_label; */

   /* initialize */
/*    sprintf(current_leftside, "<span class=\"cRe2\">%.7s</span>", "              "); */
/*       sprintf(current_leftside, "<span class=\"cRe2\"> </span>      "); */
/*    just_printed_stress_label = 0;                                                */


  /* now read and print graph until we hit [end_graph] 
  */
  have_printed_STRESS_line_already = 0;
  have_printed_OMG_line_already    = 0;
  num_OMG_printed = 0;
  // for big prtlin
  gbl_do_readahead           = 1; /* do readahead until "OMG" label is printed or reached bot of graph ('''''')*/
  gbl_just_started_readahead = 1;
  gbl_have_hit_OMG = 0;
  gbl_have_hit_stress = 0;

    /* print blank line with color cSky as first line in graph */
    /* #define NUM_PTS_FOR_FUT 92 */
    // NUM_PTS_WHOLE_YEAR 182
    // sfill(myLastLine, NUM_PTS_FOR_FUT, ' '); 
//   do {
// 
//     char myEOL[8];
// 
//     /* determine end of line method
//     */
// //     strcpy(myEOL, "\n");
// //     if (GBL_HTML_HAS_NEWLINES == 1)       strcpy(myEOL, "\n");
// //     if (GBL_HTML_HAS_NEWLINES == 0) {
// //       /*    scharout(lin,'\n'); */  /* remove newlines */
// //       if (gblWeAreInPREblockContent == 1) strcpy(myEOL, "<br>");
// //       else                                strcpy(myEOL, "");
// //     }
//     char myFirstLine[8192];
//     sfill(myFirstLine, NUM_PTS_WHOLE_YEAR , ' '); 
//     bracket_string_of(" ", myFirstLine, "<span class=\"cSky\">", "</span>");
// //    n = sprintf(writebuf,"%s%s", myFirstLine, myEOL); /* left margin = 7 spaces */
// //    f_fnBIG_prtlin(writebuf);
//     n = sprintf(p,"       %s%s", myFirstLine, myEOL); /* left margin = 7 spaces */
//     fput(p, n, Fp_f_HTML_file);
//     strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
//   } while(0);

  int len_doclin;
  strcpy(doclin, "init_doclin_string");
  strcpy(myprevline1, "initprev_1");
  strcpy(myprevline2, "initprev_2");
  strcpy(myprevline3, "initprev_3");
  int myapostropheCNT;

  char line184SPACES[256]; 





  // NEW:  show big grh on same page as expanded thumbnail with labels
//
//  // ==================================================================================================
//  // ==================================================================================================
//  for (i=0; ; i++)              // 400 lines print grh
//  // ==================================================================================================
//  // ==================================================================================================
//  {  // 400 lines print grh
//
//    strcpy(myprevline3, myprevline2);
//    strcpy(myprevline2, myprevline1);
//    strcpy(myprevline1, doclin);
//
//    f_docin_get(doclin);  // ------------------- read input lines --------------
//
////ksn(doclin);
//    len_doclin = (int)strlen(doclin);
//
//    if (len_doclin == 0) continue;
//
//    if(len_doclin > 12 && len_doclin < 60) {  // skip weird garbage= _doclin=[<span class="cSky">  </span>]
//      continue;
//      //trn("short short short ");ks(doclin);
//    }
// 
////
////    myapostropheCNT = scharcnt(doclin, '\'');
////    if (    myapostropheCNT > 33
////        &&  strstr(myprevline1, "STRESS") != NULL  )
////    {
////ksn(myprevline1);      
////ksn(doclin);
////trn("put blank pink lines here");
////
////      f_fnBIG_prtlin( "       <span class=\"cRe\">                                                                                                                                                                                        </span>\n" );
////      f_fnBIG_prtlin( "       <span class=\"cRe\">                                                                                                                                                                                        </span>\n" );
////      f_fnBIG_prtlin( "       <span class=\"cRe\">                                                                                                                                                                                        </span>\n" );
////    }
////
//////
//////    //  e.g.       howManyPlusSigns  = scharcnt(collect_star_lines, '+');
//////    if (strstr(doclin, "  |  ") ) {
//////int myapcnt;
//////ksn(myprevline3);      
//////myapcnt =  scharcnt(myprevline3, '\''); kin(myapcnt);
//////ksn(myprevline2);      
//////myapcnt =  scharcnt(myprevline2, '\''); kin(myapcnt);
//////ksn(myprevline1);      
//////myapcnt =  scharcnt(myprevline1, '\''); kin(myapcnt);
//////ksn(doclin);
//////myapcnt =  scharcnt(doclin, '\''); kin(myapcnt);
//////    }
//////
////
////
//
//
//    
////    if (strstr(doclin, "[end_graph]") != NULL) break;
//
//    if (strstr(doclin, "[end_graph]") != NULL) { break; }
//
//    /*   EXAMPLE color a  thing
//    * <body style="background-color:yellow;">
//    * <h2 style="background-color:red;">This is a heading</h2>
//    * <p style="background-color:green;">This is a paragraph.</p>
//    * </body>
//    */
//
//
//    /* for GOOD line, make background colour palegreen
//* GOOD-|<span style="background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>|
//    */
//
///* tn();b(330);ks(doclin); */
//
//
//    /* Here we check if we are on the exact stress-level label lines
//    *  GREAT, GOOD, STRESS, OMG
//    */
//
//    if (strstr(doclin, "GREAT") != NULL) {
//
//
//
//      /* EXPERIMENT   left side to right */
//      /* replace " GREAT|" with "-GREAT " and put on right side */
//      strcpy(s1, " GREAT ");
//      /* sfromto(s1, doclin,  1,  7);*/  /* " GREAT-" from " GREAT-|" */
//
///* tn();b(331);ks(s1); */
//
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99);  BUG to use sfromto- cause contains "class=star" inserted (not to 99)*/
///*       sfromto(s2, doclin,  8, 99); */
//
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
///* tn();b(332);ks(s2); */
//
//
///*       sprintf(writebuf, */
///*         "<span class=\"cGr2\">%s</span>|<span class=\"cGr2\">%s</span>|", s1, s2);  */
///*       sprintf(writebuf, "<span class=\"cGr2\">%s</span>|%s|", s1, s2);  */
//
//      /* replace " GREAT|" with "-GREAT " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cGr2\">%s</span>", s2, s1); 
//
///*       sprintf(writebuf, "<span class=\"cGr2\">%s</span>%s", s1, s2);  */
//
//
////tn();b(333);ks(writebuf); 
//
//      bracket_string_of("X", writebuf, "<span class=\"cGr2\">", "</span>");
////tn();b(334);ks(writebuf);
//
//
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
////      bracket_string_of("#", writebuf, "<span class=\"greenLine\">", "</span>");
//
//
////tn();b(335);ks(writebuf);
//      scharswitch(writebuf, 'X', ' ');
//
//
//      scharswitch(writebuf, '#', ' ');
////      scharswitch(writebuf, '#', '=');   // works fine for green char for green benchmark line
//
//
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
////tn();b(336);ks(writebuf);
//
//
//      f_fnBIG_prtlin(writebuf);
//      /* lines below are all light green */
///*    sprintf(current_leftside, "<span class=\"cGre\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cGre\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//    if (strstr(doclin, "GOOD") != NULL) {
//
//      /* replace "  GOOD|" with "-GOOD  " and put on right side */
///*       strcpy(s1, "-GOOD  "); */
//      strcpy(s1, " GOOD  ");
//
//      /* sfromto(s1, doclin,  1,  7); */  /* "  GOOD-" from "  GOOD-|" */
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
//      /* note "|" is at end */
///*         "%s<span style=\"background-color:#C3FDC3; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%%;\">%s</span>|", s1, s2);  */
///*         "%s<span class=\"cLineGood\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cGre\">%s</span>|<span class=\"cGre\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cGre\">%s</span>|%s|", s1, s2);  */
//
//
//      /* replace "  GOOD|" with "-GOOD  " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cGre\">%s</span>", s2, s1); 
//
///*       sprintf(writebuf, "<span class=\"cGre\">%s</span>%s", s1, s2);  */
//
//      bracket_string_of("X", writebuf, "<span class=\"cGre\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//
//      f_fnBIG_prtlin(writebuf);
//
//      /* lines below are all neutral color */
///*    sprintf(current_leftside, "<span class=\"cNeu\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cNeu\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//
//      continue;
//    }
//    /* for STRESS line, make background colour deeppink
//STRESS-|<span style="background-color:#FFBAC7; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%;">XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-XXXXX-</span>|
//    */
//    if (strstr(doclin, "STRESS") != NULL 
//    &&  strstr(doclin, "LEVELS") == NULL            
//    && have_printed_STRESS_line_already == 0)
//    {
//      ;
//      gbl_have_hit_stress = 1;
//
//      /* replace "STRESS|" with "-STRESS" and put on right side */
//      strcpy(s1, " STRESS");
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      /* note "|" is at end */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
///*         "%s<span style=\"background-color:#FFBAC7; font-family: Andale Mono, Courier New, Monospace; font-weight: normal; font-size: 100%%;\">%s</span>|", */
///*         "%s<span class=\"cLineStress\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cRed\">%s</span>|<span class=\"cRed\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cRed\">%s</span>|%s|", s1, s2);  */
//      sprintf(writebuf, "<span class=\"cRed\">%s</span>%s", s1, s2); 
//
//      /* replace "STRESS|" with "-STRESS" and put on right side */
//      sprintf(writebuf, " %s<span class=\"cRed\">%s</span>", s2, s1); 
//
//
////      // make red line on STRESS line
////      //
////      scharswitch(writebuf, 'X', 'm');   // for test, try 
////      bracket_string_of("m", writebuf, "<span style=\"color: red;\">", "</span>");
////      //
////      // end of make red line on STRESS line
//
//      // make red line on STRESS line
//      //
////      scharswitch(writebuf, 'X', 'W');   // for test, try 
////      bracket_string_of("m", writebuf, "<span style=\"color: red;\">", "</span>");
////      bracket_string_of("W", writebuf, "<span style=\"color: red;\">", "</span>");
//      //
//      // end of make red line on STRESS line
//
////    bracket_string_of("m", writebuf, "<span style=\"color: red;\">", "</span>");
////      bracket_string_of("X",
////        writebuf, "<span style=\"color: #ff0000; background-color: #ff0000; > \"", "</span>");
////        writebuf, "<span 00; > ", "</span>");
////        writebuf, "<span style=\"color: #ff0000; background-color: #ff0000; > \"", "</span>");
//
//
//
//
//
//
//      bracket_string_of("X", writebuf, "<span class=\"cRed\">", "</span>");
////      bracket_string_of("X", writebu
//
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//
////
////trn(" print stress word");
////      // find 10 consec sp, replace with "  STRESS  "
////
//
//
//
//      // writebuf = " STRESS "; 
////      writebuf[23] = 'S';
////      writebuf[24] = 'T';
////      writebuf[25] = 'R';
////      writebuf[26] = 'E';
////      writebuf[27] = 'S';
////      writebuf[28] = 'S';
//
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//
//
//      f_fnBIG_prtlin(writebuf);
//
//      have_printed_STRESS_line_already = 1;
//
//      /* lines below are all light red */
///*    sprintf(current_leftside, "<span class=\"cRed\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cRed\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//
//
//
//    /* intercept 2nd OMG line  (happens when last * is right on line)
//    */
///*     if (num_OMG_printed > 0) x */
///*  */
///*       if (num_OMG_printed == 1) x */
//        /* print blank line with color cRe2 under the 1st OMG */
///*    */
//          /* #define NUM_PTS_FOR_FUT 92 */
///*         sfill(myLastLine, NUM_PTS_FOR_FUT, ' ');  */
///*         bracket_string_of(" ", myLastLine, "<span class=\"cRe2\">", "</span>"); */
///*    */
///*         sprintf(p,"       %s\n", myLastLine );  */
///* left margin = 7 spaces */
///*         f_fnBIG_prtlin(myLastLine); */
///*       x */
///*       continue; */
///*     x */
//
//    // intercept 2nd OMG line  (happens when last * is right on line)
//    //
//
//    /* color OMG line, but
//    */
//    if (strstr(doclin, "OMG") != NULL
//    && have_printed_OMG_line_already == 0) {
//
//      gbl_have_hit_OMG = 1;
//
///* tn();b(221);ki(have_printed_OMG_line_already); */
//
//       /* "   OMG-" from "   OMG-|" */
///*       sfromto(s1, doclin,  1,  7);   */
//
//      /* replace "   OMG-|" with "-OMG   " and put on right side */
///*       strcpy(s1, "-OMG   "); */
//      strcpy(s1, " OMG   ");
//
//
///*       sfromto(s2, doclin,  9, 98); */
///*       sfromto(s2, doclin,  8, 99); */
//      strcpy(s2, &doclin[8 - 1]); /* into s2, get rest of string from 8th char */
//
///*       sprintf(writebuf, */
///*         "<span class=\"cRe2\">%s</span>|<span class=\"cRe2\">%s</span>|", s1, s2);  */
//
///*       sprintf(writebuf, "<span class=\"cRe2\">%s</span>|%s|", s1, s2);  */
//      sprintf(writebuf, "<span class=\"cRe2\">%s</span>%s", s1, s2); 
//
//      /* replace "   OMG-|" with "-OMG   " and put on right side */
//      sprintf(writebuf, " %s<span class=\"cRe2\">%s</span>", s2, s1); 
//
//      bracket_string_of("X", writebuf, "<span class=\"cRe2\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//
//      f_fnBIG_prtlin(writebuf);
//
//      num_OMG_printed = num_OMG_printed + 1;
//
///* tn();b(222);ki(have_printed_OMG_line_already); */
//      have_printed_OMG_line_already = 1;
//
//      /* lines below are all bright red */
///*    sprintf(current_leftside, "<span class=\"cRe2\">%.7s</span>", "              "); */
///*       sprintf(current_leftside, "<span class=\"cRe2\"> </span>      "); */
///*       just_printed_stress_label = 1; */
//      continue;
//    }
//
//    
////    f_fnBIG_prtlin("</pre></div><pre>"); // new div grhFUTG is for thumbnail ( no dates or ticks on the bottom
//
//    /* in the bottom 4 graph lines, put different line-heights
//    */
//    if (strstr(doclin, "\'\'\'\'\'") != NULL) {
//      
//      // before printing this line, print a number of pink blanks below STRESS
//      // if STRESS is lastline 
//
//      //
//      //[1]___linebuf=[       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX]__
//      //[0]___linebuf=[STRESS-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX]__
//      //
//
////trn("bottom 4 graph");
////ksn(myprevline3);      
////ksn(myprevline2);      
////ksn(myprevline1);      
////ksn(doclin);
//
//      if (strstr(myprevline1, "STRESS") != NULL) {
//        sfill(line184SPACES, 184, ' '); 
//
//        sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
//        f_fnBIG_prtlin(writebuf);
////        sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
////        f_fnBIG_prtlin(writebuf);
////      sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
////      f_fnBIG_prtlin(writebuf);
////      sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
////      f_fnBIG_prtlin(writebuf);
////      sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
////      f_fnBIG_prtlin(writebuf);
////      sprintf(writebuf, " <span class=\"cRed\">%s</span>",  line184SPACES); 
////      f_fnBIG_prtlin(writebuf);
////
//      }
//
//
//      strcpy(writebuf, "");
//      f_fnBIG_prtlin(writebuf);
//
//      /* EXPERIMENT stress level labels on right */
//      /* take 1st 7 chars margin and put them on right end */
//      sprintf(s5, "%.7s", doclin);  /* 1st 7 ch left margin */
///*       sprintf(s6, "%s%s", doclin + 7 - 1, s5); */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", doclin); */
///*       f_fnBIG_prtlin(writebuf); */
///*       f_fnBIG_prtlin(s6); */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", s6); */
///* ksn(s6); kin(strlen(s6)); */
///*       sprintf(writebuf, "<span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>", s6); */
///*       sprintf(writebuf, "<span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4, s5); */
//
//      /* weird   remove leadiing space from s4 and put it before yellow highlight */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 60%%;\">%s</span>%s", s4+1, s5); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 155%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 55%%;\">%s</span>%s", s4+1, s5);
//
///* ksn(writebuf); kin(strlen(writebuf)); */
//
//
//      f_fnBIG_prtlin(writebuf);
//
//      continue;
//    }
//    if (strstr(doclin, "|    | ") != NULL) {
///* ksn(doclin); */
///* kin(strlen(doclin)); */
//      sprintf(s5, "%.7s", doclin);  /* 1st 7 ch left margin */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height:80%%;\"\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height:60%%;\">%s</span>%s", s4+1, s5);
//      f_fnBIG_prtlin(writebuf);
//      continue;
//    }
//    if (strstr(doclin, "11   21") != NULL) {
//
//      /* EXPERIMENT stress level labels on right */
//      /* take 1st 7 chars and put them on right end */
//      sprintf(s5, "%.7s", doclin);
///*       sprintf(s6, "%s%s", doclin + 7 - 1, s5); */
//      sprintf(s4, "%s", doclin + 7 - 1); /* part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 125%%;\">%s</span>", doclin); */
///*       sprintf(writebuf, "<span style=\"line-height: 125%%;\">%s</span>", s6); */
///*       sprintf(writebuf, "<span style=\"line-height: 165%%;\">%s</span>", s6); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 165%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 170%%;\">%s</span>%s", s4+1, s5);
//
//      f_fnBIG_prtlin(writebuf);
//      continue;
//    }
//    int mth_ctr;
//    mth_ctr = 0;
//    if (strstr(doclin, "JAN") != NULL) mth_ctr++;
//    if (strstr(doclin, "FEB") != NULL) mth_ctr++;
//    if (strstr(doclin, "MAR") != NULL) mth_ctr++;
//    if (strstr(doclin, "APR") != NULL) mth_ctr++;
//    if (strstr(doclin, "MAY") != NULL) mth_ctr++;
//    if (strstr(doclin, "JUN") != NULL) mth_ctr++;
//    if (strstr(doclin, "JUL") != NULL) mth_ctr++;
//    if (strstr(doclin, "AUG") != NULL) mth_ctr++;
//    if (strstr(doclin, "SEP") != NULL) mth_ctr++;
//    if (strstr(doclin, "OCT") != NULL) mth_ctr++;
//    if (strstr(doclin, "NOV") != NULL) mth_ctr++;
//    if (strstr(doclin, "DEC") != NULL) mth_ctr++;
//
//    if (mth_ctr > 3) {
///* ksn(doclin); */
///* ksn(doclin + 7); */
//      /* remove the left margin (with year in it) and put spaces at end
//      *  we are getting rid of the year
//      */
///* ksn(doclin); */
//      /* doclin is
//       * [  2015  JULY          AUGUST          SEPTEMBER      OCTOBER        NOVEMBER       DECEMBER        ]
//       */
//
//      sprintf(s5, "%.7s", doclin);       /* grab 1st 7 ch */
//      strcpy(s5, "       "); /* 7 spaces */
//      sprintf(s4, "%s", doclin + 7 - 1); /* grab part after left mar of 7 */
//
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s</span>", doclin); */
///*       sprintf(writebuf, "<span style=\"line-height: 90%%;\">%s       </span>", doclin + 7); */
///*       sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 90%%;\">%s</span>%s", s4+1, s5); */
//      sprintf(writebuf, " <span class=\"bgy\" style=\"line-height: 75%%;\">%s</span>%s", s4+1, s5);
//
//
//      f_fnBIG_prtlin(writebuf);
//      continue;
//    }
//
//#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
//*     /* Here, before printing, we want to replace the first 7 chars (always blanks with bg color)
//*     *  with current_leftside which is like
//*     *       sprintf(current_leftside, "<span class=\"cRe2\">%.7s</span>", "              ");
//*     */
//*     /* grab line after 1st 7 chars */
//* 
//* trn("line1=");ks(doclin);
//* 
//* /* for TEST, grab 1st 7 ch */
//* /* mkstr(my_right_padding_chars, lotsachars, lotsachars + num_to_pad - 1); */
//* mkstr(s3, doclin, doclin + 7 - 1);
//* /*     if (strcmp("[beg_graph]", s1) == 0) break; */
//* if (strcmp(s3, "       ") != 0) xtrn("HEY!leftpad=");ks(s3);x
//* 
//*    /* grab print line after 1st 7 chars */
//*    sprintf(s3, "%s", doclin + 7);
//* trn("HEY!restofline=");ks(s3);
//* 
//*    /* build new line with new left column bg colors */
//*    sprintf(s5, "%s%s", current_leftside, s3) ;
//* trn("HEY!newline=");ks(s5);
//* 
//#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/
//
//
//  /* EXPERIMENT stress level labels on right */
//  /* take 1st 7 chars and put them on right end */
//  sprintf(s5, "%.7s", doclin);
///* ksn(s5); */
//  sprintf(s6, "%s%s", doclin + 7 - 1, s5);
///* ksn(s6); */
//  f_fnBIG_prtlin(s6);
//
//
//  /* just output regular line */
///*   f_fnBIG_prtlin(doclin); */
//
//
//
//  }  /* print graph until we hit [end_graph]  */
//  // ==================================================================================================
//  // ==================================================================================================
//
//





  
  gblWeAreInPREblockContent = 0;  /* false */
  gbl_we_are_printing_graph = 0;
  gbl_do_readahead          = 0; // do readahead until bottom of graph is printed


//  f_fnBIG_prtlin("  </pre>\n\n");   // end of graph 
//  f_fnBIG_prtlin("  </pre></div>");   // end of graph + end of new div grhFUTG is for thumbnail  no dates or ticks on the bottom
  f_fnBIG_prtlin("  </div></div>"); // divFUTG grhFUTG preFUTG  // end of graph + end of new div grhFUTG is for thumbnail  no dates or ticks on the bottom

  f_fnBIG_prtlin("</div>");          // end of div holding graph  ( id='divFUTG' )   // divFUTG grhFUTG preFUTG




gbl_logf_fnBIG_prtlin = 0;




  // set up SPACE for a SECOND graph  before the time frame text
  //
  f_fnBIG_prtlin( "<div id=\"divNAIL2\" class=\"cssNAIL2\">");   
    f_fnBIG_prtlin( "<canvas id=\"biggerGrhCanvas\" class=\"cssTHUcanvas\" >");
    f_fnBIG_prtlin( " Your browser does not support the HTML5 canvas tag 1.</canvas>");
//  f_fnBIG_prtlin( "</div>");   

  // 20200514  set up SPACE for a THIRD the graph  for drawing the sinewaves in and doing show/hide with above
  //
//  f_fnBIG_prtlin( "<div id=\"divNAIL2\" class=\"cssNAIL2\">");   
    f_fnBIG_prtlin( "<canvas id=\"biggerGrhNO_SWs\" class=\"cssTHUcanvas\" >");
    f_fnBIG_prtlin( " Your browser does not support the HTML5 canvas tag 2.</canvas>");
  f_fnBIG_prtlin( "</div>");   



  f_fnBIG_prtlin("<div id=\"divTIMEF\" class=\"cssTIMEF\">");


//<.>
  f_fnBIG_prtlin("<div id=\"divCLEAR_SW\" class=\"cssCLEAR_SW\">");
  f_fnBIG_prtlin("Clear");
  f_fnBIG_prtlin("</div>");
//<.>


  /* 2. read until [beg_aspects]  , which look like this:
  *    [beg_aspects]
  *         From January 1, 2008 to March 31, 2008.  ^(sugne)
  *         From January 1, 2008 to January 5, 2008.  ^(mogju)
  *         From January 1, 2008 to February 12, 2008.  ^(megne)
  *         From February 28, 2008 to March 31, 2008 and also from June 17, 2008 to July 1, 2008.  ^(vecju)
  *    [end_aspects]
  */
  for (i=0; ; i++) {
//tr("QDG_4");
    f_docin_get(doclin);
    if (strstr(doclin, "[beg_aspects]") != NULL) break;
  }

/*   f_fnBIG_prtlin("  <h4><span style=\"font-size: 85%; font-weight: normal\">"); */
/*   f_fnBIG_prtlin("      (they influence the graph above)   </span><br><br><br></h4>"); */

//  f_fnBIG_prtlin("  <h3>Important Periods</h3>");
//  f_fnBIG_prtlin("  <h4>(they influence the graph above)<br><br><br></h4>");
//  f_fnBIG_prtlin("  <h3>Important Time Frames</h3>");
//  f_fnBIG_prtlin("  <h4>that influence the graph above<br><br><br></h4>");

//  f_fnBIG_prtlin("<div class='cssTIMEFhdr'>Important Time Frames<br>that influence the graph above</div>");
//f_fnBIG_prtlin("<div class='cssTIMEFhdr'>Important Time Frames<br>that influence the graph</div>");
//  f_fnBIG_prtlin("<div class='cssTIMEFhdr'>Important Influences<br>that make up the graph</div>");
  f_fnBIG_prtlin("<div class='cssTIMEFhdr'>Main Influences<br>that make up the graph</div>");



trn("futhtm.c BEG -->  now read and print aspects until we hit [end_aspects]");



  /* now read and print aspects until we hit [end_aspects]  ====================================
  */
  for (i=0; ; i++) {

//tr("QDG_5");
    f_docin_get(doclin);
//ksn(doclin);
    if (strlen(doclin) == 0) continue;

    if (strstr(doclin, "[end_aspects]") != NULL) break;
    f_fnBIG_prtlin("\n");


    /* 1 of 2
    *    do intro lines like
    *    "From April 30, 1933 until mumble and also from" 
    *    From January 1, 2008 to March 31, 2008.  ^(sugne)
    *
    *  2 of 2  f_fnBIG_aspect_text()
    *    print aspect text  strings corresponding to
    *    aspect_codes  like "^(sugne)" 
    */
    fn_BIGaspect_from_to(doclin);

  }  /* end of read and print aspects until we hit [end_aspects] */

trn("futhtm.c END -->  now read and print aspects until we hit [end_aspects]");



  /* now read until we get  either
  *    1. [beg_graph]       for another grh+asp to output
  * NO 28apr2013  no more astrobuffs  2. [beg_astrobuffs]  for report-bottom stuff
  */
  for (i=0; ; i++) {

//tr("QDG_6");
    f_docin_get(doclin);

    if (strstr(doclin, "[beg_graph]") != NULL) {

      strcpy(have_we_hit_beg_graph, "YES"); 
      return;
    }

    if (strstr(doclin, "[beg_astrobuffs]") != NULL) break;
  }

  f_fnBIG_prtlin("</div>");   //  id=\"divTIMEF\" class=\"cssTIMEF\">");

/* ksn(s1); */

  /* here we have hit [beg_astrobuffs]
  * 
  * !! 28apr2013  we no longer display this table of planetary positions !!
  * NOTE:    "[beg_astrobuffs]"  is stll there in docin stuff
  *          In fact, the whole table is there, but not output anymore.
  */
  /* fn_output_bot_of_html_file(); */ /* for all report-bottom stuff */





#ifdef PUT_BACK_COMMENTED_OUT_STUFF /****************************************/
*   /*    else if (strstr(trait_name, "Best Calendar Year") != NULL) */
*   /* get stress number for this year
*   */
*   char stringBuffForStressScore[64]; /* for instruction  "return only year stress score" */
*   mamb_report_year_in_the_life(     /* in futdoc.o */
*     "",                           /* html_file_name, */
*     gbl_csv_person_string_in_htm,
*     gbl_year_for_fut,         /* for stress num table at bottom */
*     "return only year stress score",   /* instructions for mamb_report_year_in_the_life() */
*     stringBuffForStressScore   );
* tn();b(112);ks(stringBuffForStressScore);
#endif /* ifdef PUT_BACK_COMMENTED_OUT_STUFF ********************************/






  /* make table having stress score for the year
  *  but only if the person was alive for the whole calendar year
  */
//  if (gbl_is_first_year_in_life == 0) {
//
//  /*   f_fnBIG_prtlin("  <table class=\"trait\"> <tr> <th colspan=\"3\"> Single Stress Score For the Whole Year </th> </tr>"); */
//
//    f_fnBIG_prtlin("  <div><br><br><br></div>");
//  /*     "  <table class=\"trait\"> <tr> <th colspan=\"3\"> Single Score For %s </tr>", */
//    sprintf(writebuf,
//      "  <table class=\"trait\"> <tr> <th colspan=\"3\"> Score For %s </tr>",
//      gbl_year_for_fut
//    );
//    f_fnBIG_prtlin(writebuf);
//
//  /*   f_fnBIG_prtlin("</table>"); */
//  /*   f_fnBIG_prtlin("<table class=\"trait\">" ); */
//
//    f_fnBIG_prtlin("  <tr > <th>Person</th> <th>Score</th> <th></th></tr>");
//
//
///* calibrate stress score for table */
///*   int worknum; 
//*     worknum = targetDayScore;
//*     worknum = worknum * -1; 
//*     worknum = worknum + 900;
//*     if (worknum <= 0) worknum = 1;
//*     worknum = mapNumStarsToBenchmarkNum(IDX_FOR_SCORE_B, worknum);
//*     targetDayScore = worknum;
//* 
//*     PERCENTILE_RANK_SCORE =
//*       mapBenchmarkNumToPctlRank(targetDayScore);
//*/
///* ks(gbl_person_name); */
//    strcpy(gbl_name_for_fut, f_arr(1));  /* for stress num table at bottom */
//    strcpy(gbl_year_for_fut, f_arr(2));  /* for stress num table at bottom */
///*   strcpy(gbl_person_name, f_arr(1)); */
//
//    if (gbl_YearStressScore == 0) gbl_YearStressScore = 1; 
////gbl_YearStressScore = 9;  test
//
//tn();trn("COLOUR #2"); kin(gbl_YearStressScore );
//
//
//    if (gbl_YearStressScore >= 90) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
//    f_fnBIG_prtlin("  <tr class=\"cGr2\"><td></td> <td> 90  </td> <td>Great</td> </tr>");
//    if (gbl_YearStressScore >= 75) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
//    f_fnBIG_prtlin("  <tr class=\"cGre\"><td></td> <td> 75  </td> <td>Good</td> </tr>");
//
//    if ( gbl_YearStressScore  >= 75) {
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//    if ( gbl_YearStressScore  < 75  &&  gbl_YearStressScore >= 50 ) {
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//  /*   if ( gbl_YearStressScore  < 50  &&  gbl_YearStressScore >= 25 ) x */
//    if ( gbl_YearStressScore  < 50  &&  gbl_YearStressScore >  25 ) {
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    }
//  /*   if ( gbl_YearStressScore <= 25 ) x */
//    if ( gbl_YearStressScore <  25 ) {
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td> 50  </td> <td>Average</td> </tr>");
//      f_fnBIG_prtlin("  <tr class=\"cNeu\"><td></td> <td>     </td> <td></td> </tr>"); /* empty line */
//    }
//
//    if (gbl_YearStressScore >  25)
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//    f_fnBIG_prtlin("  <tr class=\"cRed\"><td></td> <td> 25  </td> <td>Stress</td> </tr>");
//    if (gbl_YearStressScore >  10)
//      write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore);
//
//
//    f_fnBIG_prtlin("  <tr class=\"cRe2\"><td></td> <td> 10  </td> <td>OMG</td> </tr>");
//    write_calendar_day_score(gbl_name_for_fut, gbl_YearStressScore); /* only writes if still unwritten */
//
//    f_fnBIG_prtlin("  </table>");
//
//
///*   f_fnBIG_prtlin("<div><br></div>"); */
//    f_fnBIG_prtlin("<pre class=prebox> ");
//    gblWeAreInPREblockContent = 1;  /* true */
///*   f_fnBIG_prtlin(" Check out Group reports \"Best Year\" and \"Best Day\". "); */
///*   f_fnBIG_prtlin("   Check out Group report \"Best Year\".   "); */
//
///*   f_fnBIG_prtlin(""); */
///*   f_fnBIG_prtlin("   Check out group report Best Year which uses   "); */
//
//    f_fnBIG_prtlin("  Check out group report \"Best Year\" which uses   ");
//    f_fnBIG_prtlin("  this score to compare with other group members.  ");
//    f_fnBIG_prtlin("");
//    gblWeAreInPREblockContent = 0;  /* false */
//    f_fnBIG_prtlin("</pre> ");
//
//  } /* only when gbl_is_first_year_in_life == 0 */
//




  //   BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE   
  //   BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE   
  //   BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE      BEGIN SCORE TABLE   


    f_fnBIG_prtlin("<div id=\"RPCY_scoreBOX\" class=\"cssCYscoreBOX\" >\n");   //    id=RPCY_scoreBOX class=cssCYscoreBOX




//
//    sprintf(writebuf, " <div id=\"RPCY_tblHdr\" class=\"RPCY_th\" > <div id=\"CYhdr1\" class=\"cssCYhdr1\">%s</div> <div id=\"SCOREstarSpace\" class=\"RPCY_th\"></div> <div id=\"CYhdr3\" class=\"cssCYhdr3\" >%02d</div> </div>\n", gbl_year_for_fut, gbl_YearStressScore ); 
//    f_fnBIG_prtlin(writebuf);

    char bufForTblHdr[1024];

//    sprintf(bufForTblHdr,
//      "<div id='tblHdrDIV' style='display: inline-block; height: 64px; font-size: 14px; ' >"
//      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; '>Compatibility<br>Potential</div>"
//      "  <div id='SCOREco_starSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; '>"
//      "    <div style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; bottom: 20px; '>"
//      "       %02d"
//      "    </div>"
//      "  </div>"
//      "</div>"
//      , gbl_RPCO_score
//    );
//

//    sprintf(bufForTblHdr,
//      "<div id='tblHdrDIVcy' style='display: inline-block; height: 64px; font-size: 14px; width; auto; ' >"
//      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; color: white; font-weight: bold; font-size: 1.8em; bottom: 0.9em; '>%s</div>"
//      "  <div id='SCOREstarSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; '>"
//      "    <div style='position: relative; display: inline-block; height: 64px; line-height: 64px; color: white; font-weight: bold; font-size: 1.4em; bottom: 0.88em; '>"
//      "       %02d"
//      "    </div>"
//      "  </div>"
//      "</div>"
//      , gbl_year_for_fut
//      , gbl_YearStressScore
//    );
//
//      "  <div id='SCOREcy_scoreSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; color: white; font-weight: bold; font-size: 1.4em; bottom: 0.88em; '>"
//      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; color: white; font-weight: bold; font-size: 1.8em; bottom: 0.9em; '>%s</div>"

    sprintf(bufForTblHdr,
      "<div id='tblHdrDIVcy' style='display: inline-block; height: 64px; font-size: 14px; width; auto; ' >"
      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; color: white; font-weight: bold; font-size: 1.8em; bottom: 0.7em; '>%s</div>"
      "  <div id='SCOREcy_starSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; '>"
      "  </div>  <!-- id=SCOREcy_starSpace -->"
      "  <div id='SCOREcy_scoreSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; color: white; font-weight: bold; font-size: 1.7em; bottom: 0.7em; '>"
      "     %02d"
      "  </div>  <!-- id=SCOREcy_scoreSpace-->"
      "</div>  <!-- id=tblHdrDIVcy-->"
      , gbl_year_for_fut
      , gbl_YearStressScore
    );
    f_fnBIG_prtlin(bufForTblHdr);
//ksn(bufForTblHdr);



    // return   gbl_YearStressScore in the some line of the return string of HTML
    sprintf(writebuf,"gbl_YearStressScore=%d\n", gbl_YearStressScore );
    f_fnBIG_prtlin( writebuf );
    // return   gbl_YearStressScore in the some line of the return string of HTML



// 20200127  rest of scoretable OUT  (build new one in JS using gbl_YearStressScore
// 20200127  rest of scoretable OUT  (build new one in JS using gbl_YearStressScore

//
//
////<.>
////
//////    sprintf(bufForTblHdr,
//////      "<div id='tblHdrDIV' style='display: inline-block; height: 64px; font-size: 14px; ' >"
//////      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; '>Compatibility<br>Potential</div>"
//////      "  <div id='SCOREco_starSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; '>"
//////      "    <div style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; bottom: 20px; '>"
//////      "       %02d"
//////      "    </div>"
//////      "  </div>"
//////      "</div>"
//////      , gbl_RPCO_score
//////    );
//////
////
////    sprintf(bufForTblHdr,
////      "<div id='tblHdrDIV' style='display: inline-block; height: 64px; font-size: 14px; ' >"
////      "  <div style='position: relative; bottom: 12px;  display: inline-block; height: 64px; font-size: 14px; '>Compatibility<br>Potential</div>"
////      "  <div id='SCOREco_starSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; '>"
////      "  </div>  <!-- id=SCOREco_starSpace -->"
////      "  <div id='SCOREco_scoreSpace' style='position: relative; display: inline-block; height: 64px; line-height: 64px; font-size: 18px; bottom: 20px; '>"
////      "     %02d"
////      "  </div>  <!-- id=SCOREco_scoreSpace-->"
////      "</div>  <!-- id=tblHdrDIV-->"
////      , gbl_RPCO_score
////    );
////<.>
////
//
//
//
////      " <div> </div> <table class=\"RPCO_tblTrait\" style=\"background-color: black;  margin-left: auto; margin-right: auto;\">\n");
//    f_fnBIG_prtlin(
//      "<table id=\"RPCY_tbl\" class=\"RPCO_tblTrait\" style=\"background-color: black;  margin-left: auto; margin-right: auto;\">\n");
//
//    f_fnBIG_prtlin(
//      " <tbody>");
//
////      " <tr><th id='SCOREstarSpace' ></th><th class=\"RPCO_th\" colspan=\"3\">Compatibility<br>Potential</th></tr>\n");
////      " <tr><th></th><th id='SCOREstarSpace' ></th><th class=\"RPCO_th\" colspan=\"2\">Compatibility<br>Potential</th></tr>\n");
//
//
//
////    sprintf(writebuf, " <tr><th></th><th id='SCOREstarSpace' ></th><th class=\"RPCY_th\" colspan=\"2\">%02d</th></tr>\n", gbl_YearStressScore ); 
////    f_fnBIG_prtlin(writebuf);
//
//
//
////<.>
//
//    char blank_cGr2_0[512] = "  <tr class=\"cGr2\" style=\"line-height: 0.5em; \" ><td id='tdIMG00'></td> <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td></tr>"; 
//
//    char blank_cGr2[512]  = "  <tr class=\"cGr2\"><td></td>  <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>"; 
//    char blank_cGre[512]  = "  <tr class=\"cGre\"><td id='tdIMG03'></td>  <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td> </tr>"; 
//
//    char blank_cNeuA[512] = "  <tr class=\"cNeu\"><td id='tdIMG05A'></td> <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td> </tr>"; 
//    char blank_cNeuB[512] = "  <tr class=\"cNeu\"><td id='tdIMG05B'></td> <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td> </tr>"; 
//
//    char blank_cRed[512]  = "  <tr class=\"cRed\"><td id='tdIMG09'></td>  <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td> </tr>"; 
//    char blank_cRe2[512]  = "  <tr class=\"cRe2\"><td id='tdIMG11'></td>  <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td> </tr>"; 
//
//    char blank_cRe2_12[512] = "  <tr class=\"cRe2\" style=\"line-height: 0.5em; \" ><td id='tdIMG12'></td> <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td> <td></td></tr>"; 
//
//
//
//
//
//    if ( gbl_YearStressScore >= 90)                                     // score is great cGr2   
//    {
////      sprintf(writebuf,
////        "<tr class=\"cGr2 subjectcss\" ><td id='tdIMG01'></td> <td>%s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td> </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is great cGr2   
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'> </td><td></td> <td> 90  </td> <td>Great</td> <td id='tdIMG02z'> </td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td> 75  </td> <td>Good</td>  <td id='tdIMG04z'> </td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td> 50  </td> <td>Average</td>  <td id='tdIMG06z'> </td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td> 25  </td> <td>Stress</td>  <td id='tdIMG08z'> </td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td> 10  </td> <td>OMG</td>  <td id='tdIMG10z'> </td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
////
//
////      f_fnBIG_prtlin( blank_cGr2_0);
////      sprintf(writebuf, "<tr class=\"cGr2 subjectcss\" ><td></td> <td>%s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td><td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is great cGr2   
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'> </td><td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
////
//
//
//      // new scorebox
//      f_fnBIG_prtlin( blank_cGr2_0);
//
//      CY_SCORELINE_cGr2 
//      CY_BENCHLINE_cGr2 
//      CY_BENCHLINE_cGre 
//
//      f_fnBIG_prtlin( blank_cNeuA);
//      CY_BENCHLINE_cNeu 
//      f_fnBIG_prtlin( blank_cNeuB);
//
//      CY_BENCHLINE_cRed 
//      CY_BENCHLINE_cRe2 
//    } else if ( gbl_YearStressScore >= 75  &&  gbl_YearStressScore  < 90 )   // score is good cGre
//    {
////      f_fnBIG_prtlin( blank_cGr2);
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'></td> <td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      sprintf(writebuf, "<tr class=\"cGre subjectcss \" ><td id='tdIMG03'></td> <td>%s</td><td id='scoreelt'> %d  </td><td>&nbsp;</td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is good cGre
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
////
//      // new scorebox
//      CY_BENCHLINE_cGr2 
//      CY_SCORELINE_cGre 
//      CY_BENCHLINE_cGre 
//
//      f_fnBIG_prtlin( blank_cNeuA);
//      CY_BENCHLINE_cNeu 
//      f_fnBIG_prtlin( blank_cNeuB);
//
//      CY_BENCHLINE_cRed 
//      CY_BENCHLINE_cRe2 
//    }
//    else if ( gbl_YearStressScore  < 75  &&  gbl_YearStressScore >= 50 )     // score is above avg cNeu
//    {
////      f_fnBIG_prtlin( blank_cGr2);
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'></td> <td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      sprintf(writebuf, "<tr class=\"cNeu subjectcss \" '  ><td id='tdIMG05A'></td> <td> %s</td><td id='scoreelt'> %d  </td><td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </td></tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is above avg
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
////
//
//      // new scorebox
//      CY_BENCHLINE_cGr2 
//      CY_BENCHLINE_cGre 
//
//      CY_SCORELINE_cNeu 
//      CY_BENCHLINE_cNeu 
//      f_fnBIG_prtlin( blank_cNeuB);
//
//      CY_BENCHLINE_cRed 
//      CY_BENCHLINE_cRe2 
//    }
//    else if ( gbl_YearStressScore  < 50  &&  gbl_YearStressScore >  25 )     // score is below avg cNeu
//    {
////      f_fnBIG_prtlin( blank_cGr2);
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'></td> <td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      sprintf(writebuf, "<tr class=\"cNeu subjectcss \" ><td></td> <td> %s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is below avg
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
////
//
//      // new scorebox
//      CY_BENCHLINE_cGr2 
//      CY_BENCHLINE_cGre 
//
//      f_fnBIG_prtlin( blank_cNeuA);
//      CY_BENCHLINE_cNeu 
//      CY_SCORELINE_cNeu 
//
//      CY_BENCHLINE_cRed 
//      CY_BENCHLINE_cRe2 
//    }
//    else if ( gbl_YearStressScore  <= 25  &&  gbl_YearStressScore >  10 )    // score is stress cRed
//    {
////      f_fnBIG_prtlin( blank_cGr2);
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'></td> <td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      sprintf(writebuf, "<tr class=\"cRed subjectcss \" ><td id='tdIMG09'></td> <td> %s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is stress cRed
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cRe2);
//
//      // new scorebox
//      CY_BENCHLINE_cGr2 
//      CY_BENCHLINE_cGre 
//
//      f_fnBIG_prtlin( blank_cNeuA);
//      CY_BENCHLINE_cNeu 
//      f_fnBIG_prtlin( blank_cNeuB);
//
//      CY_BENCHLINE_cRed 
//      CY_SCORELINE_cRed 
//      CY_BENCHLINE_cRe2 
//    }
//    else if ( gbl_YearStressScore  <= 10)                               // score is omg cRe2
//    {
//
////      f_fnBIG_prtlin( blank_cGr2);
////      f_fnBIG_prtlin( "  <tr class=\"cGr2 benchline \"><td id='tdIMG02'> </td><td></td> <td class=\"cssBenchmarkText\"> 90  </td> <td id='tdIMG02z'></td>  <td class=\"cssBenchmarkText\">Great</td>   <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cGre);
////      f_fnBIG_prtlin( "  <tr class=\"cGre benchline \"><td id='tdIMG04'></td> <td></td> <td class=\"cssBenchmarkText\"> 75  </td> <td id='tdIMG04z'></td>  <td class=\"cssBenchmarkText\">Good</td>    <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuA);
////      f_fnBIG_prtlin( "  <tr class=\"cNeu benchline \"><td id='tdIMG06'></td> <td></td> <td class=\"cssBenchmarkText\"> 50  </td> <td id='tdIMG06z'></td>  <td class=\"cssBenchmarkText\">Average</td> <td></td> </tr>");
////      f_fnBIG_prtlin( blank_cNeuB);
////      f_fnBIG_prtlin( "  <tr class=\"cRed benchline \"><td id='tdIMG08'></td> <td></td> <td class=\"cssBenchmarkText\"> 25  </td> <td id='tdIMG08z'></td>  <td class=\"cssBenchmarkText\">Stress</td>  <td></td> </tr>");  
////      f_fnBIG_prtlin( blank_cRed);
////      f_fnBIG_prtlin( "  <tr class=\"cRe2 benchline \"><td id='tdIMG10'></td> <td></td> <td class=\"cssBenchmarkText\"> 10  </td> <td id='tdIMG10z'></td>  <td class=\"cssBenchmarkText\">OMG</td>     <td></td> </tr>");
////      //  writebuf2        is   names  of person_A  and  person_B 
////      //  gbl_YearStressScore   is   in_rank_lines[i]->score;  // save for NEW "real" string_for_table_only   below
////      sprintf(writebuf, "<tr class=\"cRe2 subjectcss \" ><td id='tdIMG11'></td> <td> %s</td><td id='scoreelt'> %d  </td><td></td> <td><span style=\"visibility:hidden;\">X</span></td> <td><span style=\"visibility:hidden;\">X</span></td>  </tr>",
////        gbl_name_for_fut, gbl_YearStressScore );   
////      f_fnBIG_prtlin( writebuf);   // score is omg cRe2
////
////      f_fnBIG_prtlin( blank_cRe2_12 );
////
//      // new scorebox
//      CY_BENCHLINE_cGr2 
//      CY_BENCHLINE_cGre 
//
//      f_fnBIG_prtlin( blank_cNeuA);
//      CY_BENCHLINE_cNeu 
//      f_fnBIG_prtlin( blank_cNeuB);
//
//      CY_BENCHLINE_cRed 
//      CY_BENCHLINE_cRe2 
//      CY_SCORELINE_cRe2 
//
//      f_fnBIG_prtlin( blank_cRe2_12 ); // extra green spacing for bottom stress scores
//
//
//    } else {
//      ;
//    }
////<.>
//
//
//
////<.>
////<.>
//
//
//
////  f_fnBIG_prtlin( "<div style='background-color: cyan;'><br><br></div></tbody></table>");
//  f_fnBIG_prtlin( "</tbody></table>");
//
//

// 20200127  rest of scoretable OUT  (build new one in JS using gbl_YearStressScore
// 20200127  rest of scoretable OUT  (build new one in JS using gbl_YearStressScore




    f_fnBIG_prtlin("</div>");   //    id=RPCY_scoreBOX class=cssCYscoreBOX



  //     END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE   
  //     END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE   
  //     END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE        END SCORE TABLE   


//
//  // new div for future report bottom part
//  f_fnBIG_prtlin("<div id=\"futBOTT\"  class=\"cssfutBOTT\" >");
//
//  f_fnBIG_prtlin("<div><br><br></div>");
//
//  f_fnBIG_prtlin("<pre> ");
//  gblWeAreInPREblockContent = 1;  /* true */
//  f_fnBIG_prtlin( "  Your intense willpower can overcome and control your destiny  ");
//  f_fnBIG_prtlin( "                                                                ");
//  gblWeAreInPREblockContent = 0;  /* false */
//  f_fnBIG_prtlin("</pre>");
//
//  f_fnBIG_prtlin("<pre>");
//  char workProducedBy[256];
//  sprintf(workProducedBy,
//    "<div> <span style=\"font-size: 0.5em\"><br><br>produced by iPhone app \"%s\"</span><br><span style=\"font-size: 0.5em; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only.</span></div>" ,
//    APP_NAME
//  ); 
//  f_fnBIG_prtlin( workProducedBy );
//  f_fnBIG_prtlin("</pre>");
//
//  f_fnBIG_prtlin("</div>");   // id=futBOTT
//



  // new div for future report bottom part

  // add DATA to div  futBOTT  for all SW data  (gbl_PSV_of_SW_CSVs)
  //
  //  f_fnBIG_prtlin("<div id=\"futBOTT\"  class=\"cssfutBOTT\" >");
  sprintf(s1, "<div id=\"futBOTT\"  class=\"cssfutBOTT\" data-swcsvall=\"%s\" >", gbl_PSV_of_SW_DATA_CSVs);
  f_fnBIG_prtlin(s1);




//  f_fnBIG_prtlin("<div style=\"padding: 3vh; position: relative;  margin-left: auto;  margin-right: auto; margin-bottom: 5vh; border-style: solid; border-width: 0.33vw; border-color: rgb(42,32,8); text-align: left; background-color: rgb(255,255,255); font-size: 75%; font-weight: normal; width: 80%; \" >");
  f_fnBIG_prtlin("<div class=\"cssDIVnugget BGimageNUGGETs\" >");

//  f_fnBIG_prtlin( "Your <span style=' text-shadow: 2px 2px 0 rgb(255,255,2), -2px -2px 0 rgb(255,255,2), -2px  2px 0 rgb(255,255,2),  2px -2px 0 rgb(255,255,2) ; '>intense willpower</span> can overcome and control your destiny </div>");
//  f_fnBIG_prtlin( "Your <span class='yellowShine'>intense willpower</span> can overcome and control your destiny </div>");
  f_fnBIG_prtlin( "Your <span class='yellowShine'>intense willpower</span> can<br>overcome and control your destiny </div>");

//  f_fnBIG_prtlin( "<div style=\"text-align: center; font-size: 66%; margin-top: 2vh; \" >produced by free app igotostars.org</div>");
  f_fnBIG_prtlin( "<div class=\"iHaveAPP_DESC\" style=\"text-align: center; font-size: 66%; margin-top: 2vh; \" >produced by appDESCgoesHERE</div>");


  f_fnBIG_prtlin( "<div style=\"text-align: center; font-size: 66%; font-weight: bold; color:#FF0000;\">This report is for entertainment purposes only</div><div><br></div>" );

  f_fnBIG_prtlin("</div>");   // id=futBOTT





  f_fnBIG_prtlin("\n</body>\n");
  f_fnBIG_prtlin("</html>");

} // end of fn_BIGoutputGrhAndAspects(void) 


//void f_fnBIG_aspect_text(char *aspect_code) {
//  int nn;
///* trn("f_fnBIG_aspect_text(char *aspect_code)"); */
//
//  nn = binsearch_asp(aspect_code, f_asptab, NKEYS_ASP);
//  if (nn < 0) return;  /* do not print any aspect text at all  */
//
//  strcpy(my_aspect_text, f_asptab[nn].asp_text);
//
///*    put_br_every_n(my_aspect_text, 65);  */
//   put_br_every_n(my_aspect_text, 72); 
//
//  /* example output for text paragraph:
//  * 
//  *  <table class="center"><tr><td style="white-space: nowrap"><p>You1are restless about current conditions and conventional ways of doing things. <br>There's a possibility that you can turn to unusual or even impractical projects. <br>Beware of association with eccentric or unstable people at this time.</p></td></tr></table>
//  */
//
//  char para_beg[133];
//  char para_end[133];
//
//  strcpy(para_beg, "<table class=\"center\"><tr><td><p>");
//
//  strcpy(para_end, "</p></td></tr></table>");
//
//  sprintf(writebuf, "  %s%s%s\n", para_beg, my_aspect_text, para_end);
//
//  f_fnBIG_prtlin(writebuf);
//
//} // end of void f_fnBIG_aspect_text(char *);

// new version
void f_fnBIG_aspect_text(char *aspect_code) {
  int nn;
/* trn("f_fnBIG_aspect_text(char *aspect_code)"); */

  nn = binsearch_asp(aspect_code, f_asptab, NKEYS_ASP);
  if (nn < 0) return;  /* do not print any aspect text at all  */

  strcpy(my_aspect_text, f_asptab[nn].asp_text);

  char para_beg[133];
  char para_end[133];
  strcpy(para_beg, "<div class=\"fromtotext\">");

  strcpy(para_end, "</div>");

  sprintf(writebuf, "  %s%s%s\n", para_beg, my_aspect_text, para_end);

  f_fnBIG_prtlin(writebuf);

} // end of void f_fnBIG_aspect_text(char *);



/* ************************************************************
* this is called once per aspect in docin
* From February 28, 2008 to March 31, 2008 and also from June 17, 2008 to July 1, 2008.  ^(vecju)
* ************************************************************/
void fn_BIGaspect_from_to(char *doclin)
{
  char fromtoline[1024];
  char look_starting_here[1024];
  char *p;
//tn();trn("in fn_BIGaspect_from_to()"); 
//ksn(doclin);


  strcpy(fromtoline, doclin);
  is_first_from_to_in_doclin = 1;

  /* get return value aspect_code like "^(vecju)"
  */
  p = strstr(fromtoline, " ^");
  if (p != NULL) {
    strcpy(aspect_code, p + 1);
  }
 
  /* make "^(vecju)" into "vecju"
  */
  scharout(aspect_code,'^');   
  scharout(aspect_code,'(');   
  scharout(aspect_code,')');   

  *p = '\0';   /* end the fromtoline string here */
  strcpy(look_starting_here, fromtoline);



  // fyi  SW = Sine Wave   
  SW_put_aspect_HTML_TOP(aspect_code); // put END   of aspect_container here with DATA to allow JS to draw the impact sinewaves on a tap/click


  /* here the from/to HEADER text is going to be output
  */
  SW_put_aspect_HDR_TOP();
//trn("\n\nstart loop");
  do {  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

//tr("look_starting_here top=");ksn(p);
    p = strstr(look_starting_here, " from");  /* look for a " from" */
//ksn(p);
    if (p != NULL) {
      strcpy(s3, p + 1);
    }
    if (p == NULL) {  
      /* only one from/to in doclin
      *  (less leading white for 2nd, 3rd)
      */
//tr("printing this");ksn(look_starting_here);

      // look_starting_here DOES NOT contain "and also" 
      // SO, add 10 spaces (white-space = pre) at the end of look_starting_here 
      // to make all time frame HDR lines fixed length
      //

      if (is_first_from_to_in_doclin == 1) {
//        sprintf(s1, "%s%s%s", "  <div class=\"fromtohdr\"><br>", look_starting_here, "</div>");
        sprintf(s1, "%s%s%s%s", "  <div class=\"fromtohdr\">", look_starting_here, "          ", "</div>");  // 10spaces = fixed len fromtoHDR
      } else {
        sprintf(s1, "%s%s%s%s", "  <div class=\"fromtohdr\">", look_starting_here, "          ", "</div>");
      }
      f_fnBIG_prtlin(s1); 
      is_first_from_to_in_doclin = 0;
      break;  /* done */

    } else {

      /* found another from/to.  Now print the first from/to.
      *  p points to sp in " from" 
      */
      mkstr(s2, look_starting_here, p ); /* up to space in " from" */   // s2 DOES contain "and also" 
//tr("printing this");ksn(s2);
      if (is_first_from_to_in_doclin == 1) {
//        sprintf(s3, "%s%s%s", "  <div class=\"fromtohdr\"><br>", s2, "</div>");
        sprintf(s3, "%s%s%s", "  <div class=\"fromtohdr\">", s2, "</div>");
      } else {
//        sprintf(s3, "%s%s%s", "  <div class=\"fromtohdr\"><br>", s2, "</div>");
        sprintf(s3, "%s%s%s", "  <div class=\"fromtohdr\">", s2, "</div>");
      }

      f_fnBIG_prtlin(s3);
      is_first_from_to_in_doclin = 0;

      /*       strcpy(look_starting_here, p + 1); copy str into itself (nono) */
      strcpy(s5, p + 1);
      strcpy(look_starting_here, s5);
//tr("look_starting_here bot=");ksn(p);
    }
  } while (p != NULL);   /* ++++++++++++++++++++++++++++++++++++ */


  /* here the from/to HEADER text has been output
  */
  SW_put_aspect_HDR_BOT();



  f_fnBIG_aspect_text(aspect_code);    /* output the aspect text */


  SW_put_aspect_HTML_BOT(aspect_code); // put END   of aspect_container here with DATA to allow JS to draw the impact sinewaves on a tap/click


} // end of  void fn_BIGaspect_from_to(char *);





// this is updated after each aspect in this current calendar year is "finished"

// FYI -  - gbl_PSV_of_SW_CSVs
//
  //  _(futhtm.c BEG -->  now read and print aspects until we hit [end_aspects])__
  //  _doclin=[from Jan  1 to Jan  5 ^(subju)]__
  //  _(fn_BIGaspect_from_to() in futhtm.c  --  this is updated after the end of each aspect is reached )__
  //  _gbl_PSV_of_SW_CSVs=[sun_opp_jup,001,005,negative,042,042,015,003,done|ven_opp_jup,081,193,negative,011,068,000,097,done|ven_opp_jup,317,341,negative,003,067,012,171,done|mar_opp_jup,361,365,negative,011,055,055,183,done|ven_opp_sat,013,055,negative,005,152,000,028,done|mar_opp_sat,107,157,negative,002,036,001,079,done|ven_opp_sat,217,325,negative,005,152,010,163,done|moo_sxt_ura,001,039,positive,015,017,001,020,done|mar_squ_ura,001,107,negative,082,106,002,054,done|sun_sxt_ura,033,145,positive,000,076,000,073,done|sun_sxt_ura,319,365,positive,003,055,055,183,done|ven_opp_plu,015,237,negative,001,134,000,119,done|ven_opp_plu,317,365,negative,000,101,101,183,done||]__
  //
  //  sun_opp_jup,001,005,negative,042,042,015,003,done
  //  ven_opp_jup,081,193,negative,011,068,000,097,done
  //  ven_opp_jup,317,341,negative,003,067,012,171,done
  //  mar_opp_jup,361,365,negative,011,055,055,183,done
  //  ven_opp_sat,013,055,negative,005,152,000,028,done
  //  mar_opp_sat,107,157,negative,002,036,001,079,done
  //  ven_opp_sat,217,325,negative,005,152,010,163,done
  //  moo_sxt_ura,001,039,positive,015,017,001,020,done
  //  mar_squ_ura,001,107,negative,082,106,002,054,done
  //  sun_sxt_ura,033,145,positive,000,076,000,073,done
  //  sun_sxt_ura,319,365,positive,003,055,055,183,done
  //  ven_opp_plu,015,237,negative,001,134,000,119,done
  //  ven_opp_plu,317,365,negative,000,101,101,183,done
//
void SW_put_aspect_HTML_TOP(char *aspect_code) // put TOP   of aspect_container here with DATA to allow JS to draw the impact sinewaves on a tap/click
{
//tr("in SW_put_aspect_HTML_TOP"); ksn(aspect_code);   // fyi output 
//ksn(gbl_fromDoc_PSV_of_SW_CSVs);
            // append oneSineWaveDATA to gbl_PSV_of_SW_DATA_CSVs
  char aspcode_SW_DATA_PSV[2048];  // could be 3
  char plt2char_nat[16];
  char plt2char_trn[16];
  char asp_g_or_b  [16];
  char asp_sign    [16];  // "positive" or "negative"
  char inCSV_pltnat[16];
  char inCSV_plttrn[16];
  char inCSV_aspect[16];
  char inCSV_pos_or_neg[16];
  char inCSV_g_or_b[16];
  char aspect_code_from_SW_CSV[16];
  // need to associate this aspect_code with the corresponding SW_CSV above
  //   
  char *N_planet_2chars[] = {"   ","su" ,"mo" ,"me" ,"ve" ,"ma" ,"ju" ,"sa" ,"ur" ,"ne" ,"pl" };
  char *N_planet[]        = {"   ","sun","moo","mer","ven","mar","jup","sat","ura","nep","plu", "nod","asc","mc_"};

        //
        //  /*************** more on sfromto(dest,src,beg,end)  below
        //  Reads chars from src string (from begth char to endth char inclusive) 
        //  and writes them to dest string starting with the [0] (first) char in dest. 
        //  Adds \0 marker to dest.    Returns pointer to dest. 
        //  e.g.  s2 = "abcdefghijk";  sfromto(s1,s2,3,6);  now  s1 = "cdef" 
        //  NOTE that beg and end arguments have the intuitive values where the 
        //  first char in the string is called 1, second is called 2 etc. 
        //  BE CAREFUL.  this fn puts chars on top of and beyond dest \0.
        //  dest str should be long enough to hold all the chars.
        //  ***************/
        //  char *sfromto(char *dest,char *src, int beg, int end)
        //
        // E.G. _aspect_code=[vebpl]__
        //
  // aspect_code PARTS  aspect_code PARTS  aspect_code PARTS  
  sfromto(plt2char_nat, aspect_code, 1, 2);
  sfromto(asp_g_or_b  , aspect_code, 3, 3);
  sfromto(plt2char_trn, aspect_code, 4, 5);
  if (strcmp(asp_g_or_b, "b") == 0)   strcpy(asp_sign, "negative") ;
  else                                strcpy(asp_sign, "positive") ;
  // aspect_code PARTS  aspect_code PARTS  aspect_code PARTS  


  // loop thru thefrom Doc_PSV_of_SW_CSVs looking for an SW_CSV having all the aspect_code PARTS
  // then put its SineWave DATA into the HTML TOP code
  //
  char SW_CSV_current[128];
  strcpy(SW_CSV_current, "something so its not zero length at the start");
  //

//tr("");trn("in futhtm.c   for each csv in gbl_fromDoc_PSV_of_SW_CSVs");
//ksn(gbl_fromDoc_PSV_of_SW_CSVs);
  //
  for (int ifld = 1; strlen(SW_CSV_current) != 0; ifld++)   // FOR EACH   SW_CSV in gbl_PSV_of_SW_CSVs
  {
    strcpy(SW_CSV_current, csv_get_field( gbl_fromDoc_PSV_of_SW_CSVs, "|", ifld));  // one-based fldnum

//    if (strlen(SW_CSV_current) == 0) return; // last SW_CSV is empty =-->  "... ,000,050,done|sun_sxt_plu,141,365,positive,000,075,036,183,done||" 

    // last SW_CSV is empty =-->  "... ,000,050,done|sun_sxt_plu,141,365,positive,000,075,036,183,done||" 
    if (strlen(SW_CSV_current) == 0) break;  // go to bottom to print html for top

//trn("next SW_CSV_current");
//ki(strlen(SW_CSV_current));
//ksn(SW_CSV_current);

    // if the "aspect_code PARTS" above are in this SW_CSV, 
    // then send the sinewave data to JS as  "DATA-"
    //
        //  FYI  what an SW_CSV looks like
        //       from   void create_a_new_SW_CSV(int addval, int nat_plt, int aspect_num, int trn_plt, int day_num) 
        //
        //    sprintf(SW_CSV_current,                   // create a NEW SW_CSV
        //      "%3s_%3s_%3s,%03d,%03d,%8s,%03d,%03d,%03d,%03d,%4s",
        //      N_planet[nat_plt], N_aspect[aspect_num], N_trn_planet[trn_plt],   // fld #1   // looks like "sun_opp_jup"
        //      int_SW_BEG_DayOfYear     ,
        //      int_SW_END_DayOfYear     ,
        //      str_SW_amplitude_sign    ,                                        // fld #4   // "positive" or "negative"
        //      int_SW_amplitude_at_BEG  ,
        //      int_SW_amplitude_at_MAX  ,
        //      int_SW_amplitude_at_END  ,                                        // fld #7
        //      int_SW_day_num_updated   ,
        //      str_SW_open_or_done                                               // fld #9   // "open" or "done"
        //    );
        //    // SW_CSV_current has 49 chars
        //
        //  looks like "sun_opp_jup,001,005,negative,042,042,015,003,done"
        //             "1234567890123456789012345678901234567890123456789"
        //             "         1         2         3         4         "
        //
        sfromto(inCSV_pltnat, SW_CSV_current,  1,  2);
        sfromto(inCSV_aspect, SW_CSV_current,  5,  7);
        sfromto(inCSV_plttrn, SW_CSV_current,  9, 10);

        if (strcmp(inCSV_aspect, "tri") == 0)  strcpy(inCSV_g_or_b, "g" );
        if (strcmp(inCSV_aspect, "sxt") == 0)  strcpy(inCSV_g_or_b, "g" );
        if (strcmp(inCSV_aspect, "opp") == 0)  strcpy(inCSV_g_or_b, "b" );
        if (strcmp(inCSV_aspect, "squ") == 0)  strcpy(inCSV_g_or_b, "b" );
        if (strcmp(inCSV_aspect, "cnj") == 0)  strcpy(inCSV_g_or_b, "c" );
//ksn(inCSV_g_or_b);
//ks(inCSV_pltnat); ks(inCSV_plttrn); ksn(inCSV_g_or_b);


        // build the aspect_code for this SW_CSV
        sprintf(aspect_code_from_SW_CSV, "%s%s%s", inCSV_pltnat, inCSV_g_or_b, inCSV_plttrn);
//ksn(aspect_code_from_SW_CSV);
//tn();

        if ( strcmp(aspect_code_from_SW_CSV, aspect_code) == 0) 
        {
//tr("aspcodeFOUND->");ks(aspect_code);ksn(aspect_code_from_SW_CSV);ks(SW_CSV_current);tn();

          // here we have the 6 pieces of SineWave information from SW_CSV_current
          // needed to draw the SineWave for this screen-displayed aspect -  arg=aspect_code
            char oneSineWaveDATA[32];
            char f1[8], f2[8], f3[8], f4[8], f5[8], f6[8];

            sfromto(f1, SW_CSV_current, 13, 15),  //      int_SW_BEG_DayOfYear     ,
            sfromto(f2, SW_CSV_current, 17, 19),  //      int_SW_END_DayOfYear     ,
            sfromto(f3, SW_CSV_current, 21, 23),  //      str_SW_amplitude_sign    ,    //  "pos" or "neg"
            sfromto(f4, SW_CSV_current, 30, 32),  //      int_SW_amplitude_at_BEG  ,
            sfromto(f5, SW_CSV_current, 34, 36),  //      int_SW_amplitude_at_MAX  ,
            sfromto(f6, SW_CSV_current, 38, 40),  //      int_SW_amplitude_at_END  ,   

            sprintf( oneSineWaveDATA, "%5s,%3s,%3s,%3s,%3s,%3s,%3s",  // len = 29
              aspect_code,
              f1,f2,f3,f4,f5,f6
            );
            // aspect_code looks like "subpl"     _doclin=[from Jan  1 to Jan  5 ^(subju)]__

//tr("add this SW");ksn(oneSineWaveDATA);
            // collect all oneSineWaveDATAs   FOR ALL aspect_codes   into gbl_PSV_of_SW_DATA_CSVs
            //
            // append oneSineWaveDATA to gbl_PSV_of_SW_DATA_CSVs
            if (strlen(gbl_PSV_of_SW_DATA_CSVs) == 0 ) {
              sprintf(gbl_PSV_of_SW_DATA_CSVs, "%s|",                            oneSineWaveDATA); // this gbl used in futhtm.c
            } else {
              sprintf(gbl_PSV_of_SW_DATA_CSVs, "%s%s|", gbl_PSV_of_SW_DATA_CSVs, oneSineWaveDATA); // this gbl used in futhtm.c
            } 
//ksn(gbl_PSV_of_SW_DATA_CSVs);

//  sprintf(s1, "<div id='box_for_asp_%s' class='box_for_aspect'  data-swspecs='%s'>", aspect_code, aspcode_SW_DATA_PSV);
//  sprintf(s1, "<div id=\"futBOTT\"  class=\"cssfutBOTT\" data-swcsvall=\"%s\" >", gbl_PSV_of_SW_DATA_CSVs);


            // collect all oneSineWaveDATAs   FOR THIS aspect_code   (could be max 3)  into aspcode_SW_DATA_PSV
            //
            // append oneSineWaveDATA to aspcode_SW_DATA_PSV
            if (strlen(aspcode_SW_DATA_PSV) == 0 ) {
              sprintf(aspcode_SW_DATA_PSV, "%s|",                        oneSineWaveDATA);
            } else {
              sprintf(aspcode_SW_DATA_PSV, "%s%s|", aspcode_SW_DATA_PSV, oneSineWaveDATA);
            } 
//ksn(aspcode_SW_DATA_PSV);
//tr("");
        }

  }  // for each csv in gbl_fromDoc_PSV_of_SW_CSVs


//trn(" HTML (top) for the aspect_box");
  // HTML (top) for the aspect_box
  //
  // div id='box_for_asp_%s' ENCLOSES
  //   1. the aspect fromto HDR  lines
  //   2. the aspect fromto TEXT lines
  //
  sprintf(s1, "<div id='box_for_asp_%s' class='box_for_aspect'  data-swspecs='%s'>", aspect_code, aspcode_SW_DATA_PSV);
  f_fnBIG_prtlin(s1);


  // set up SPACE for  the canvas of the graph image
  //
  sprintf(s1, "<canvas id=\"canvas_SW_%s\" class=\"cssSWcanvas\" width=\"182\"  height=\"77\"  >", aspect_code );
  f_fnBIG_prtlin(s1);

  f_fnBIG_prtlin( " Your browser does not support the HTML5 canvas tag.</canvas>");






// todo 
//  swspecs_for_this_aspect_code = get from some global  
//  //
//  sprintf(s1, "%s%s%s", "  <div class=\"DIV_ASPECT_%s\"  data-swspecs=\"%s\">", aspect_code, swspecs_for_aspect_code
//  // later ... </div>
//  );
//  // then in JS, something like this:
//   // first on click   sinewave_specs = $this.data('swspecs')
//   // then use sinewave_specs string to buil graph for this influence IMPACT 
//   //
//  // fyi
//    $('#PICKyr' +  iidx + "") ).text(pickyr_btnlabel).addClass('pickyrPickable').data('yyyy', pickyr_todoS );  // always make data = year
//    gbls_TG_yearSTART =  $('#' + gbls_pickyr_ID_a).data('yyyy');
//


//  sprintf(s1, "<div class=\"DIV_ASPECT_%s\"  data-swspecs=\"%s\">", aspect_code, swspecs_for_aspect_code


} // SW_put_aspect_HTML_TOP()



void SW_put_aspect_HDR_TOP(void)
{
    // When there are > 1 fromto HDR lines we want them left aligned.
    // But we want to CENTER THE HDR for the whole group of fromto lines
    // inside div id "box_for_asp_%s"

    // create an enclosing div for all (or 1) of the from to HDR lines
    // div id='box_fromto_lines' ENCLOSES
    //   1. the aspect fromto HDR  lines
    //
    f_fnBIG_prtlin( "<div id='box_fromto_HDR' class='all_fromto_HDR' >" );  // fyi class does all_fromto_line swidth:fit-content and margin:auto
}
//
void SW_put_aspect_HDR_BOT(void)
{
  f_fnBIG_prtlin("</div>");  // end of div id "box_fromto_HDR"
} 




void SW_put_aspect_HTML_BOT(char *aspect_code)
{
//trn("\nin SW_put_aspect_HTML_BOT");

  f_fnBIG_prtlin("</div>");  // end of div id "box_for_asp_%s"
} 






/* c examples
*       n = sprintf(p,"%s", "\n[beg_topinfo1]\n");
*       fput(p,n,fFP_DOCIN_FILE);
* 
*       n = sprintf(p,"%s\n", scapwords(&fA_EVENT_NAME[0]));
*       fput(p,n,fFP_DOCIN_FILE);
*/
void f_fnBIG_prtlin(char *lin)
{
  char myEOL[8];
  char saveOMGline[8192];
  //char myLastLine[8192], next_doclin[8192], current_prtlin[8192];
  char                   next_doclin[8192], current_prtlin[8192];
  char *ptr;


//if (gbl_logf_fnBIG_prtlin == 1) {
//}
//ksn(lin);



if (gbl_have_hit_stress == 1) {
//tr("f_fnBIG_prtlin() 1 ");ksn(p);
}


  if (gbl_is_first_f_fnBIG_prtlin == 1) {  // init
    gbl_put_html_here        = 0;  // beg of js malloc'd mem
    gbl_is_first_f_fnBIG_prtlin = 0;  // not first any more
  }


  /* determine end of line method
  */
  strcpy(myEOL, "\n");
  if (GBL_HTML_HAS_NEWLINES == 1)       strcpy(myEOL, "\n");
  if (GBL_HTML_HAS_NEWLINES == 0) {
    /*    scharout(lin,'\n'); */  /* remove newlines */
    if (gblWeAreInPREblockContent == 1) strcpy(myEOL, "<br>");
    else                                strcpy(myEOL, "");
  }






static int flagGotOMG = 0;;

if (flagGotOMG == 1) {
  ++flagGotOMG;
//tn();trn("f_fnBIG_prtlin  AFTER  - got line with OMG");ksn(lin);tn();
//kin(flagGotOMG);
}

if (strstr(lin, " OMG  ") != NULL) {
  flagGotOMG = 1;
//tn();trn("f_fnBIG_prtlin  - got line with OMG");ksn(lin);tn();
//kin(flagGotOMG);
}




//static int countlin;
//countlin++;
//if (countlin <= 33) {
//tn();tn();trn("in f_fnBIG_prtlin() HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
// ksn(lin);
//tn();
//}
//

//kin(gbl_do_readahead ); ks( gbl_ffnameHTML);

  // ignore rubbish line
  if (strstr(lin, "raph]") != NULL) return;


  // do second line of benchmark label printing, 
  // BUT not if the  benchmark label is on the last line of the graph
  // (next line has apostrophe tick marks for the dates)
  //
  if (gbl_do_second_line == 1) {

    strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */

    if (strstr(next_doclin, "''''''''''''''") == NULL) {
      insert_minus_benchmark( lin);
//trn("after insert minus                  ");ks(lin); 
      change_last_7_chars(lin);
//trn("after insert change_last_7_chars  1 ");ks(lin); 
    }
    gbl_do_second_line = 0;
  } // print second line of benchmark label
  if (gbl_do_second_line == 7) {  // print of benchmark label was nixed
/* trn("on account of 7 ");ks(lin); */
    change_last_7_chars(lin);
//trn("after insert change_last_7_chars  2 ");ks(lin); 
    gbl_do_second_line = 0;
  }
  /* peek ahead to the next input line
  *  if this current line has GREAT or GO0D in it
  *    replace it with 7 spaces
  *  if the next input line has "-GREAT" or -GOOD in it
  *    on this current line, replace last 7 spaces with GREAT or GOOD 
       *   strcpy(in_line, global_docin_lines[global_read_idx] ); *
  */
  if (gbl_do_readahead == 1)
  {

    strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */


/* tn();trn("curr=");ks(lin); */
/* trn("next=");ks(next_doclin); */

    /* if first line of graph is GREAT or GOOD, print it as is
    */
    if (gbl_just_started_readahead == 1 ) {  // first line of graph

      if (((strstr(lin, "GREAT") != NULL) || strstr(lin, "GOOD") != NULL)) {
/* tn();trn("in 1st line G"); */
        n = sprintf(p,"%s%s", lin, myEOL);
//tr("lbl01");ksn(p);

//        fput(p, n, Fp_f_HTML_file);        /* PRINT the line */
        memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 01");ksn(p);tn();
        gbl_put_html_here = gbl_put_html_here + n;


        strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
        return;
      } 
      gbl_just_started_readahead = 0;
      // end of first line of graph

    } else if (strstr(next_doclin, "GREAT") != NULL) {


/* tn();trn("in GREAT is on NEXT line"); */
/* ksn(lin); */
/* trn("nextline=");ks(next_doclin); */

      /* replace last 7 spaces with GREAT */
/*       next_doclin[strlen(gbl_prtlin_lastline) - 7] = '\0'; */
      /* lastline,  append GREAT */
/*       sprintf(lin, "%s<span class=\"cGr2\">-GREAT </span>%s", next_doclin, myEOL); */

/*       strcpy(s2, "-GREAT "); */
      strcpy(s2, " GREAT ");
      /* into s3, get rest of string from 8th char */
      strcpy(s3, &doclin[8 - 1]);  // this is  the CURRENT  doclin, not next
/*       strcpy(s3, &lin[8 - 1]); */
/* ksn(s3); */

      /* replace " GREAT|" with "-GREAT " on CURRENT LINE and put on right side */
//      sprintf(writebuf, " %s<span class=\"cGr2\">%s</span>", s3, s2);   // buf for CURRENT LINE
//      bracket_string_of("X", writebuf, "<span class=\"cGr2\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      scharswitch(writebuf, 'X', ' ');
//      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '|', ' ');  /* sideline out */
//

      sprintf(writebuf, " %s<span class=\"cGr2\">%s</span>", s3, s2);   // buf for CURRENT LINE
      bracket_string_of("X", writebuf, "<span class=\"cGr2\">", "</span>");
      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
//      bracket_string_of("#", writebuf, "<span class=\"greenLine\">", "</span>");
      scharswitch(writebuf, 'X', ' ');
      scharswitch(writebuf, '#', ' ');
//      scharswitch(writebuf, '#', '=');   // works fine for green char for green benchmark line
      scharswitch(writebuf, '|', ' ');  /* sideline out */

      // before printing this GREAT line, 
      // possibly insert GREAT on this line and "---" on next line
      // if there is room
/* tn();trn("insert_benchmar_label(\"GREAT\", writebuf, next_doclin);"); */
/* ksn(writebuf); */

      strcpy(gbl_benchmark_label, "GREAT");
      gbl_do_second_line =  insert_label_benchmark( writebuf, next_doclin);
/* trn("on account of next_doclin = GREAT ");ks(lin); */
      change_last_7_chars(writebuf);


      // add white top text shadow on "GREAT"
      if (strstr(writebuf, "GREAT") != NULL ) {
//trn("doing great shadow");
//        strsubg(writebuf, "background-color:#80ff40", "background-color:#80ff40; color: black; text-shadow: -1px -1px 0 white, 1px 1px 0 white; ");   //  ?



        // greenLine=#33ff33
        //
//        strsubg(writebuf, "background-color:#80ff40", "background-color:#33ff33; color: black; text-shadow: -1px -1px 0 white, 1px 1px 0 white; ");   //  ?  // greenLine=#33ff33 

//per_emcc_my2.html:5395 _(memcpy p 02)__
//per_emcc_my2.html:5395 _p=[ <span class="cSky"><span style="background-color:#33ff33"> GREAT </span>                                                                                                                                       </span><span class="cGr2">  </span><span class="cSky">                                        </span> 
//per_emcc_my2.html:5395 ]__



//        strsubg(writebuf, "background-color:#33ff33", "background-color:#33ff33; color: black; text-shadow:  1px  1px 0 white, -1px 1px 0 white; ");   //  ?  // greenLine=#33ff33 




        // put greenLine color (#33ff33) in body chars on GREAT line
        bracket_string_of("X", writebuf, "<span class=\"greenLine\">", "</span>"); // put greenLine color (#33ff33) in body chars on GREAT line

      }



     // put black text-shadow on GREAT
//     strsubg(writebuf, "background-color:#33ff33", "background-color:#33ff33; color: white; text-shadow: -1px -1px 0 black, 1px 1px 0 black; ");   



      n = sprintf(p,"%s%s", writebuf, myEOL);
//tr("lbl02");ksn(p);

      //
      // NOTE: the line with the word GREAT is printed here
      //       replace it with spaces
      //void strsubg(char *s, char *replace_me, char *with_me) // on str s (max 2048) does  :s/replace_me/with_me/g
      //
      strsubg(p, "> GREAT <" , ">       <");    // on str s (max 2048) does  :s/replace_me/with_me/g
//tr("lbl02");ksn(p);




//tn();trn(" in big prtlin   GREAT   after change_last_7_chars ");
//ksn(p);tn();

/*       n = sprintf(p,"%s", writebuf); */
/* trn("GREAT next printed=");ks(p); */




//      fput(p, n, Fp_f_HTML_file);        /* PRINT the CURRENT line */
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 02");ksn(p);tn();
      gbl_put_html_here = gbl_put_html_here + n;

      gbl_dGREATlineOnePrinted = 1;  // = 1 after 1st GREAT line printed 
      // HERE,  gbl_dGREATlineTwoPrinted is = 0

      strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */

      // here the NEXT doclin requires fiddling ("----" etc)

      return;

    } else if (strstr(next_doclin, "GOOD") != NULL)
    {

/* tn();trn("in GOOD in NEXT line"); */
/* ksn(lin); */
/* trn("nextline=");ks(next_doclin); */

/* tn();trn("in GOOD NEXT"); */
/* ksn(global_docin_lines[global_read_idx - 1]); */
/* ksn(global_docin_lines[global_read_idx ]); */
/* ksn(global_docin_lines[global_read_idx + 1]); */
      /* replace last 7 spaces with GREAT */
/*       next_doclin[strlen(gbl_prtlin_lastline) - 7] = '\0';  */
      /* lastline,  append GREAT */
/*       sprintf(lin, "%s<span class=\"cGre\">-GOOD </span>%s", next_doclin, myEOL); */
/* ksn(doclin); */
/*       strcpy(s2, "-GOOD  "); */
      strcpy(s2, " GOOD  ");
      /* into s3, get rest of string from 8th char */
      strcpy(s3, &doclin[8 - 1]);
/*       strcpy(s3, &lin[8 - 1]); */
      sprintf(writebuf, " %s<span class=\"cGre\">%s</span>", s3, s2); 
      bracket_string_of("X", writebuf, "<span class=\"cGre\">", "</span>");
      bracket_string_of("#", writebuf, "<span class=\"cSky\">", "</span>");
      scharswitch(writebuf, 'X', ' ');
      scharswitch(writebuf, '#', ' ');
      scharswitch(writebuf, '|', ' ');  /* sideline out */


      strcpy(gbl_benchmark_label, "GOOD");
      gbl_do_second_line =  insert_label_benchmark( writebuf, next_doclin);
/* trn("on account of next_doclin = GOOD ");ks(lin); */
      change_last_7_chars(writebuf);


      // add white top/bot text shadow on "GOOD"
//      if (strstr(writebuf, "GOOD") != NULL ) {
////trn("doing good shadow");
//        strsubg(writebuf, "background-color:#c0ffc0", "background-color:#c0ffc0; color: black; text-shadow: -1px -1px 0 white, 1px 1px 0 white; ");   //  ?
//      }
//


      n = sprintf(p,"%s%s", writebuf, myEOL);
/* trn("GOOD next printed=");ks(p); */
//tr("lbl03");ksn(p);
      strsubg(p, "> GOOD <" , ">      <");    // on str s (max 2048) does  :s/replace_me/with_me/g
//tr("lbl03");ksn(p);

      // NOTE: the line with the word GOOD   is printed here

//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 03");ksn(p);tn();
      gbl_put_html_here = gbl_put_html_here + n;

      strcpy(gbl_prtlin_lastline, p);

      return;
      // end of GOOD is in NEXT line

    } else if ( strstr(lin, "GREAT") != NULL)
    {
//tn();trn("in GREAT current"); 
//ksn(lin);tn();
      /* remove GREAT from current line and substitute 7 spaces */
      strcpy(current_prtlin, lin);
/* ksn(current_prtlin); */
/*       ptr = strstr(current_prtlin, "<span class=\"cGr2\">-GREAT </span>"); */
      ptr = strstr(current_prtlin, "<span class=\"cGr2\"> GREAT </span>");
/* ksn(ptr); */
/*       memcpy(ptr, "       \n\0", 9); */
      memcpy(ptr, "       \0", 8);
/* ksn(ptr); */
/* ksn(current_prtlin); */
      strcpy(lin,current_prtlin);
/* ksn(lin); */
/* exit(320); */



//trn("doing great shadow");
//        strsubg(writebuf, "background-color:#33ff33", "background-color:#33ff33; color: black; text-shadow: -1px -1px 0 black, 1px 1px 0 black; ");   //  ?
//



      n = sprintf(p,"%s%s", writebuf, myEOL);
/* trn("GREAT curr printed=");ks(p); */
//tr("lbl04");ksn(p);


//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 04");ksn(p);tn();
      gbl_put_html_here = gbl_put_html_here + n;

      strcpy(gbl_prtlin_lastline, p);

      return;

    } else if ( strstr(lin, "GOOD")  != NULL)
    {
/* tn();trn("in GOOD current"); */
      /* remove GOOD from current line and substitute 7 spaces */
/* ksn(lin); */
      strcpy(s5, lin);
/* ksn(s5); */
      char *myptrtest;
/* char tststr[1024]; */
/* strcpy(tststr, "<span class=\"cGre\"> GOOD </span>"); */
/* ksn(tststr); */
      myptrtest = strstr(lin, "<span class=\"cGre\"> GOOD  </span>");
/* ksn(myptrtest); */
/*       memcpy(ptr, "       \n\0", 9); */
      memcpy(myptrtest, "       \0", 8);
/*       current_prtlin[strlen(gbl_prtlin_lastline) - 7] = '\0'; */
/* ksn(myptrtest); */
/* ksn(s5); */
/*       strcpy(lin,s5); */
/* ksn(lin); */

      n = sprintf(p,"%s%s", writebuf, myEOL);
//tr("lbl05");ksn(p);
/* trn("GOOD curr printed=");ks(p); */

//      fput(p, n, Fp_f_HTML_file);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 05");ksn(p);tn();
      gbl_put_html_here = gbl_put_html_here + n;

      strcpy(gbl_prtlin_lastline, p);

      return;

//    rb else if (strstr(next_doclin, "STRESS") != NULL)  // put red line before line with word STRESS on it
//    rb else if (strstr(next_doclin, "STRESS-  ") != NULL)  // put red line before line with word STRESS on it
//    rb else if (strstr(next_doclin, "STRESS-XX") != NULL)  // put red line before line with word STRESS on it
    } else if (strstr(next_doclin, "STRESS") != NULL)  // put red line before line with word STRESS on it
    {
       // set FLAG to put red line before line with word STRESS on it");
       // but NOT if next line is apostrophes
       //
//trn("set FLAG to put red line before line with word STRESS on it");
       sfill(gbl_redlinebuf, NUM_PTS_WHOLE_YEAR + 2, ' '); // #define NUM_PTS_WHOLE_YEAR 182
       bracket_string_of(" ", gbl_redlinebuf, "<span class=\"redLine\">", "</span>");

       gbl_flagPrintRedline = 1;  // after printing next line

    }
    else if (strstr(lin, "STRESS") != NULL
         &&  strstr(lin, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
    )
    {
/* tn();trn("doing STRESS  LABEl !!!!!!!!!!!!!!"); */
      strcpy(gbl_benchmark_label, "STRESS");
      gbl_do_second_line =  insert_label_benchmark(writebuf, next_doclin);
    }

   else if (strstr(lin, "OMG") != NULL) {

//tn();trn("doing OMG  LABEl !!!!!!!!!!!!!!"); 
     strcpy(gbl_benchmark_label, "OMG");
     gbl_do_second_line =  insert_label_benchmark(writebuf, next_doclin);
//ksn(lin);
//ksn(writebuf);
   }

  } /* (gbl_do_readahead == 1) */


/* tn();trn("FALL THRU"); */


/*   if (   strstr(gbl_prtlin_lastline, "First Half") != NULL */
/*       && strstr(lin,                 "First Half") != NULL  */

  /* print blank line  under the first 6 months
  */
  if (   strstr(gbl_prtlin_lastline, "First 6 months") != NULL
      && strstr(lin,                 "First 6 months") != NULL 
     ) {
/*     n = sprintf(p,"%s\n", "" ); */
/*     n = sprintf(p,"%s%s", "", myEOL); */
    n = sprintf(p,"%s",  myEOL);
//tr("lbl06");ksn(p);

//    fput(p, n, Fp_f_HTML_file);
    memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 06");ksn(p);tn();
    gbl_put_html_here = gbl_put_html_here + n;

    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */

    /* start readahead after printing line with "6 months" in it
    */
    if(strstr(lin, "6 months") != NULL  ) {
      gbl_do_readahead           = 1; // do readahead until bottom of graph is printed
      gbl_just_started_readahead = 1;
    }

    return;
  }
/*   if (   strstr(gbl_prtlin_lastline, "Second Half") != NULL */
/*       && strstr(lin,                 "Second Half") != NULL  */
  if (   strstr(gbl_prtlin_lastline, "Second 6 months") != NULL
      && strstr(lin,                 "Second 6 months") != NULL 
     ) {
/*     n = sprintf(p,"%s\n", "" ); */
    n = sprintf(p,"%s%s", "", myEOL);
//tr("lbl07");ksn(p);

//    fput(p, n, Fp_f_HTML_file);
    memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 07");ksn(p);tn();
    gbl_put_html_here = gbl_put_html_here + n;

    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */

    /* start readahead after printing line with "6 months" in it
    */
    if(strstr(lin, "6 months") != NULL) {
      gbl_do_readahead           = 1; // do readahead until bottom of graph is printed
      gbl_just_started_readahead = 1;
    }

    return;
  }

  if (   strstr(gbl_prtlin_lastline, "|   10   20") != NULL  /* avoid double print */
      && strstr(lin,                 "|   10   20") != NULL 
     ) {
    return;
  }


  /* if last line printed has "-STRESS"  AND this line has "-STRESS"
  *  do not print this line
  *  (bug with 2 "STRESS-" lines when star is on bottom line and
  *  bottom line is stress line)
  */
/*       && strstr(lin,                 "STRESS-") != NULL  */
  if (   strstr(gbl_prtlin_lastline, "STRESS") != NULL
      && strstr(gbl_prtlin_lastline, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
      && strstr(lin,                 "STRESS") != NULL 
      && strstr(lin,                 "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
     ) {
    return;
  }


/* if (strstr(lin, "GREAT-") != NULL) { */
/* tn();trn("f_fnBIG_prtlin() GREAT   at TOP    "); ksn(lin); } */


  /* weird fix 
  *  if line has "STRESS-", but does NOT have "span", do not print it
  */
/*   if(strstr(lin, "STRESS-") != NULL */
/*   if(strstr(lin, "-STRESS") != NULL */
  if(strstr(lin, "STRESS") != NULL
  && strstr(lin, "LEVELS") == NULL            // 20150325 put "STRESS LEVELS" in graph title for webview
  && strstr(lin, "span")   == NULL)  return;
  
  /* weird fix  #2   long blank line at top
  */
  if (strstr(lin, " <span class=\"cSky\">                                                                                              </span>" )  != NULL) {
   /* tn();b(555);ks("HIT BAD sky!"); */
   return;
  }

  /* weird fix #3
  *  if line has "OMG-", but does NOT have "cRe2", do not print it
  *  BUT, print a line of spaces in cRe2
  */
/* tn();trn(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;"); */
/* ksn(lin); */


//  if(strstr(lin, "OMG-") != NULL
//  && strstr(lin, "cRe2")    == NULL)  lb

//
//  if (flagGotOMG == 2) {
//    flagGotOMG = flagGotOMG + 1;
//nbn(400); 
//kin(flagGotOMG);
//
////
////    /* print blank line with color cRe2 under the 1st OMG
////       but must have --- for OMG in it */
////
////    // 20121229  HARD CODE THIS LINE  (it worked)
//////     strcpy(p, " <span style=\"background-color:#ff4477\"> </span><span style=\"color:#ff4477\">---</span><span style=\"background-color:#ff4477\"> </span><span class=\"cRe2\">                                                                                                                                                                                   </span> ");
//////    n = (int)strlen(p);
////
////    char my179SPACES[256]; sfill(my179SPACES, 179, ' '); 
//////    n = sprintf(p, " <span style=\"background-color:#fd0102\"> </span><span style=\"color:#fd0102\">-----</span><span style=\"background-color:#fd0102\"> </span><span class=\"cRe2\">%s</span>       ", my179SPACES);
//////    n = sprintf(p, " <span style=\"background-color:#fd0102\"> </span><span style=\"color:#fd0102\">-----</span><span class=\"cRe2\">%s</span>       <br>", my179SPACES);
//////    n = sprintf(p, " <span style=\"background-color:#fd0102\"> </span><span style=\"color:#fd0102\">-----</span><span class=\"cRe2\">%s</span>       \n", my179SPACES);
////    n = sprintf(p, " <span style=\"background-color:#fd0102\"> </span><span style=\"color:#fd0102\">----</span><span class=\"cRe2\">%s</span>       \n", my179SPACES);
////
//
////
////   // print previous line again only with colors in benchmark label area (5 chars for OMG)");
////   //
////tn();trn(" print previous line again only with colors in benchmark label area (5 chars for OMG)");
////ksn(saveOMGline);
////
////  //e.g.  saveOMGline=[ <span class="cSky"><span style="background-color:#fd0102; color:yellow; text-shadow: -1px -1px 0 black, 1px 1px 0 black, -1px 1px 0 black, 1px -1px 0 black; "> OMG </span>        </span><span class="cRe2">                                                                                           </span><span class="star">^</span><span class="cSky"> </span><span class="cRe2">                       </span><span class="cSky">             </span><span class="cRe2">  </span><span class="cSky">   </span><span class="cRe2">                                     </span> ]__
////
////  //  replace this
////  //  "<span style=\"background-color:#fd0102; color:yellow; text-shadow: -1px -1px 0 black, 1px 1px 0 black, -1px 1px 0 black, 1px -1px 0 black; \"> OMG </span>"
////  //  with  this
////  //  "<span style=\"background-color:#fd0102\">     </span>"
////  //
////  strcpy(p, lin);
////ksn(p);
////kin(n);
////
////  strsubg(p, 
////    "<span style=\"background-color:#ff7ba3\"> </span><span style=\"color:#ff7ba3\">---</span><span style=\"background-color:#ff7ba3\"> </span>",
////
////    "<span style=\"background-color:#fd0102\">     </span>"
//////    "<span style=\"background-color: cyan\">     </span>"
////  );
////  n = (int)strlen(p);
////ksn(p);
////kin(n);
////
//
//
////    fput(p, n, Fp_f_HTML_file);
//    memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 08");ksn(p);tn();
//    gbl_put_html_here = gbl_put_html_here + n;
//
//    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
//
////     /* #define NUM_PTS_FOR_FUT 92 */
//// 
////   // NUM_PTS_WHOLE_YEAR 182
////     // sfill(myLastLine, NUM_PTS_FOR_FUT, ' '); 
////     sfill(myLastLine, NUM_PTS_WHOLE_YEAR , ' '); 
//// 
////     bracket_string_of(" ", myLastLine, "<span class=\"cRe2\">", "</span>");
//// 
////     n = sprintf(p,"       %s%s", myLastLine, myEOL); /* left margin = 7 spaces */
//// 
//// tn();trn("UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU");
//// ksn(p);
////     insert_minus_benchmark( p);
//// ksn(p);
//// 
//// //    n = sprintf(p," %s%s", myLastLine, myEOL); /* left margin = 7 spaces */
//// 
//// 
//// //    fput(p, n, Fp_f_HTML_file);
//// //    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
////   
//// // b(100);
//// //     if (gbl_do_second_line == 1) {
//// // 
//// // b(101);
//// //       strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */
//// // 
//// //       if (strstr(next_doclin, "''''''''''''''") == NULL) {
//// // b(102);
//// //         insert_minus_benchmark( p);
//// // b(103);
//// // /* trn("after insert minus");ks(lin); */
//// //         change_last_7_chars(p);
//// // b(104);
//// //       }
//// // b(105);
//// //       gbl_do_second_line = 0;
//// //     } // print second line of benchmark label
//// 
//// b(106);
////     n = (int)strlen(p);
////    fput(p, n, Fp_f_HTML_file);
////    strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */
//
//    return;
//  }
//

/* GREAT is too short here, but OK in docin array   what hpppend? */
/* if (strstr(lin, "GREAT-") != NULL) { */
/* tn();trn("f_fnBIG_prtlin() GREAT"); ksn(lin); } */

  /* remove pipe at end of any line with a pipe in it
  */
  char *end_pipe;
  end_pipe = strstr(lin, "|<");  /* looks like "|</span>" */
  if(end_pipe != NULL) {     
//trn("remove pipe  1  at end of any line with a pipe in it");
//ksn(lin);
    memcpy(end_pipe, " ", 1);
  }
  end_pipe = strstr(lin, "|       <");  /* looks like "|       </span>" */
  if(end_pipe != NULL) {     
//trn("remove pipe  2  at end of any line with a pipe in it");
//ksn(lin);
    memcpy(end_pipe, " ", 1);
  }
  
  if (gbl_we_are_printing_graph == 1) {
/* trn("on account of gbl_we_are_printing_graph == 1"); */
    change_last_7_chars(lin);
  }

if (gbl_dGREATlineTwoPrinted == 1)
{
//tn();trn(" at cpy p 09 1  gbl_dGREATlineTwoPrinted == 1");
//ksn(lin);
  gbl_dGREATlineOnePrinted    = 0;
  gbl_dGREATlineTwoPrinted    = 0;
  //
  // for GREEN LINE,  change  class=cSky  to class=greenLine
  //
  // mambutil.c  void strsubg(char *s, char *replace_me, char *with_me) // on str s (max 2048) does  :s/replace_me/with_me/g
  strsubg(lin, "cSky", "greenLine");

  strsubg(lin, "cGre", "greenLine");

//tn();trn(" at cpy p 09 1A  gbl_dGREATlineTwoPrinted == 1");
//ksn(lin);

    // here change every space in span greenline to greenline_char  (first try '=')

  char *myp;  
  char *myp2;  
  char *searchStartingHere;  
  searchStartingHere = lin;
  char greenLine_char;
//  greenLine_char = 'm';
//  greenLine_char = '=';
//  greenLine_char = '"';
//  greenLine_char = '#';
  greenLine_char = ' ';
  while (1)
  {
    myp = strstr(searchStartingHere, "greenLine");
//tn();tr("strstr LOOP");ksn(myp);
    if (myp == NULL) break;
    if (myp != NULL) {
//      searchStartingHere = myp + 8;  // NEXT search,  look further down the string
      //
      // read down the string from myp until you get a space
      // replace all consecutive from there spaces with greenLine_char
      // stop when you hit a non-space
      //
      for (myp2 = myp; *myp2 != ' '; myp2++) { };
//ksn(myp2);
      // here myp2 points at a space
//      *myp2 = greenLine_char;
//ksn(myp2);
      for ( ; *myp2 == ' '; myp2++) {
        *myp2 = greenLine_char;
      }
//ksn(myp2);
      searchStartingHere = myp2;  // NEXT search,  look further down the string
    }
  }

//tn();trn(" at cpy p 09 1B  gbl_dGREATlineTwoPrinted == 1");
//ksn(lin);
    
}


// for test
if (gbl_dGREATlineOnePrinted == 1) {
//tn();trn(" at cpy p 09 2  gbl_dGREATlineOnePrinted == 1");
//ksn(lin);
  gbl_dGREATlineOnePrinted    = 0;
  gbl_dGREATlineTwoPrinted    = 1;
}
// for test



//
////      bracket_string_of("#", writebuf, "<span class=\"greenLine\">", "</span>");
////      scharswitch(writebuf, '#', '=');   // works fine for green char for green benchmark line
//
//


  // strange fix for "stress" label background  (had 1 white char on each end ) ?
  if (strstr(lin, "#ffffff") != NULL ) {
    strsubg(lin, "#ffffff", "#ff0103");
  }


  // strange fix for "stress" label foreground  (had black on red ) ?
  // make it white on red
//  if (strstr(lin, "#fd0102") != NULL ) {  // this odd color ( 1 and 2 )  is a FLAG
//
//    strsubg(lin, "background-color:#fd0102", "background-color:#fd0102; color:yellow; text-shadow: -1px -1px 0 black, 1px 1px 0 black, -1px 1px 0 black, 1px -1px 0 black; ");   //  ?
//  }


  // yellow text plus black text shadow for OMG
  //

  if (strstr(lin, " OMG ") != NULL ) {

//
//    strsubg(lin, "background-color:#ff7ba3", "background-color:#ff7ba3; color:yellow; text-shadow: -1px -1px 0 black, 1px 1px 0 black, -1px 1px 0 red, 1px -1px 0 red; ");   //  ?
////trn(" yellow text plus black text shadow for OMG");
//

    strcpy(saveOMGline, lin);  // for printing line after OMG
//ksn(lin);
//ksn(saveOMGline);
  }

  // FIX for line under OMG 
  if (strstr(lin, ">---<") != NULL )   // yellow text plus black text shadow for OMG
  {
    strsubg(lin, "#ff7ba3", "#ff0101");
//trn(" FIX for line under OMG ");
//ksn(lin);
    // e.g. <span style="background-color:#ff7ba3"> </span><span style="color:#ff7ba3">---</span><span style="background-color:#ff7ba3"> </span><span class="cSky">        </span><span class="cRe2">                                                                                            </span><span class="star">^</span><span class="cRe2">                       </span><span class="cSky">            </span><span class="star">^</span><span class="cRe2">  </span><span class="star">^</span><span class="cSky">  </span><span class="cRe2">                                     </span> 

  } // FIX for line under OMG 

//trn(" before * PRINT the line * ");
//ksn(lin);
//ksn(myEOL);

  n = sprintf(p,"%s%s", lin, myEOL);

  // NOTE: both of the lines with the words STRESS and OMG are printed here
  //


//tr("lbl08");ksn(p);

  if (strstr(lin, " OMG ") != NULL ) {
//tr("lbl08");ksn(p);
    strsubg(p, "> OMG <" , ">     <");    // on str s (max 2048) does  :s/replace_me/with_me/g
//tr("lbl08");ksn(p);
  }
  if (strstr(lin, " STRESS ") != NULL ) {
//tr("lbl08b");ksn(p);
    strsubg(p, "> STRESS <" , ">        <");    // on str s (max 2048) does  :s/replace_me/with_me/g
//tr("lbl08b");ksn(p);
  }



if (gbl_have_hit_stress == 1) {
//trn(" after  * PRINT the line * ");
//ksn(lin);
//tr("f_fnBIG_prtlin() 2 ");ksn(p);
}




  memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n);
//tn();trn("memcpy p 09");ksn(p);tn();


  gbl_put_html_here = gbl_put_html_here + n;

  strcpy(gbl_prtlin_lastline, p); /* save last line printed in gbl */


//  if (gbl_flagPrintRedline == 1) lb  // print redlline

  // print redline

//    strcpy(next_doclin, global_docin_lines[global_read_idx + 1]); /* get next input line */
//    rb else if (strstr(next_doclin, "STRESS") != NULL)  // put red line before line with word STRESS on it


//<.>
  if (    gbl_flagPrintRedline == 1)
  {  // print redlline
    char mynextlin[8196];
    char mynextnextlin[8196];
    int  myapostropheCNT;

    strcpy(mynextlin,     global_docin_lines[global_read_idx + 1]); /* get next input line */
    strcpy(mynextnextlin, global_docin_lines[global_read_idx + 2]); /* get line AFTER next input line */

//tn();trn(" if gbl_flagPrintRedline == 1");
//ksn(myprevline3);      
//ksn(myprevline2);      
//ksn(myprevline1);      
//ksn(doclin);
//ksn(mynextlin);
//ksn(mynextnextlin);
//tn();
//

    myapostropheCNT = scharcnt(mynextnextlin, '\'');

//    if (    strstr(doclin,    "STRESS-XX") != NULL 
//        &&  strstr(mynextlin, "STRESS-  ") != NULL
//        &&  myapostropheCNT > 33                     )
//      ;   // do not print redline in above conditions


    if (    strstr(mynextlin, "STRESS") != NULL
        &&  gbl_flagMEMCPY_P_11_is_done == 0      )
    {
      // this is "memcpy p 11" line
      n = sprintf(p," %s%s", gbl_redlinebuf, myEOL);
//tr("lbl09");ksn(p);
      memcpy(gbl_space_for_HTML_fut + gbl_put_html_here, p, n); // this is "memcpy p 11" line
//tn();trn("memcpy p 11");ksn(p);tn();
      gbl_put_html_here = gbl_put_html_here + n;

      gbl_flagPrintRedline = 0;
      gbl_flagMEMCPY_P_11_is_done = 1;

    }
  } // print redlline


/* trn("end of f_fnBIG_prtlin()"); */
} // end of  void f_fnBIG_prtlin(char *lin);


// ====== END OF ===========  BIG versions of functions needed  =========================



// e.g.    gbl_do_second_line =  insert_label_benchmark("GREAT", writebuf, next_doclin);
//  return 1 if OK to put second line ("---")
// arg 2 + 3  e.g. (first few, last few chars)
// curr=[ <span class="cGr2">         </span><span class="cSky">      </span> ... <span class="cGr2"> GREAT </span>]
//                           |
//       012345678901234567890123456789
//
// next_doclin=[ GREAT-XXXXXXXXX######XXXXXXXXXXXXXXXXXXXXXXXXXXX<span class="star">^</span> ...
//                     |  
//              01234567890123456789
//
// (uses gbl_benchmark_label)
//
int insert_label_benchmark(char *line_curr, char * line_next)
{
//tn();trn("insert_label_benchmark() llllllllllllllllllllllllllllllllllllllllllllllllllllllll"); 
//ksn(gbl_benchmark_label); 
//ksn(line_curr);
//ksn(line_next); 

  int len_label, line_curr_is_good, line_next_is_good, linethird_is_good;
  char area_line_curr[16], area_line_next[16], area_linethird[16];
  char myspaces[16], my_Xs[16], my_SHARPs[16], my_ticks[16];
  char changed_line[8192], part_before[8192], part_after[8192], part_middle[8192], my_bg_color[32];
  int retval_goodtogo;
  char linethird[8192]; //spans_removed[8192];


  retval_goodtogo = 0;    // try - no benchmark labels at all on grh 
  return(retval_goodtogo);


  len_label = (int)strlen(gbl_benchmark_label); // is there room on both curr line and next line  for label
/* kin(len_label); */

  // line after next line cannot have stars, '^',  in the first len_label + 2 chars
  strcpy(linethird, global_docin_lines[global_read_idx + 2]); /* get input line after next */
/* ksn(linethird); */

  remove_spans(linethird);
/* ksn(linethird); */
  mkstr(area_linethird, linethird + 7, linethird + 7  + (len_label + 2) -1);  // ignore leading 7 chars (margin)
  
  
/* ki(len_label); */
  sfill(myspaces,  len_label + 2, ' '); 
  sfill(my_Xs,     len_label + 2, 'X'); 
  sfill(my_SHARPs, len_label + 2, '#'); 
  sfill(my_ticks,  len_label + 2, '\''); 

  mkstr(area_line_curr, line_curr + 20, line_curr + 20 + (len_label + 2 - 1)); // chk for sp+len+sp   (+2)

  if (strcmp(gbl_benchmark_label, "GREAT")  == 0  || 
      strcmp(gbl_benchmark_label, "GOOD")   == 0) {
    mkstr(area_line_next, line_next +  7, line_next +  7 + (len_label + 2 - 1));
  }
  if (strcmp(gbl_benchmark_label, "STRESS")  == 0  || 
      strcmp(gbl_benchmark_label, "OMG")     == 0) {
    mkstr(area_line_next, line_next +  27, line_next + 27 + (len_label + 2 - 1));
  }

//ksn(myspaces); 
/* ksn(my_Xs); */
/* ksn(my_SHARPs); */
//ksn(area_line_curr); 
/* ksn(area_line_next); */
/* ksn(area_linethird); */
/* tn(); */

  if (   strcmp(area_line_curr, myspaces  )  == 0
      || strcmp(area_line_curr, " STRESS ")  == 0   // special case result of bug fix -bottom star on stress line
     )
  {
    line_curr_is_good = 1;
  }
  else {
    line_curr_is_good = 0;
  }

  if (strcmp(area_line_next, my_Xs)     == 0 ||
      strcmp(area_line_next, myspaces)  == 0 || 
      strcmp(area_line_next, "    <") == 0 ||    // for webview omg is on last line
      strcmp(area_line_next, my_SHARPs) == 0 ) line_next_is_good = 1;
  else                                         line_next_is_good = 0;

  if (strcmp(area_linethird, myspaces)  == 0 ||
      strcmp(area_linethird, my_Xs)     == 0 ||
      strcmp(area_linethird, my_ticks)  == 0 ||
      strcmp(area_linethird, my_SHARPs) == 0 ) linethird_is_good= 1;
  else                                         linethird_is_good= 0;

//kin(line_curr_is_good); ki(line_next_is_good ); ki(linethird_is_good ); 

  retval_goodtogo = 0;  // default
  if (line_curr_is_good == 1 && line_next_is_good == 1 && linethird_is_good) {
    retval_goodtogo = 1;
//  retval_goodtogo = 0;    // try - no benchmark labels at all on grh 

//    if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_bg_color, "#66ff33");


//    if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_bg_color, "#80ff40");
    // greenLine=#33ff33
    if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_bg_color, "#33ff33"); // greenline=#33ff33



//    if (strcmp(gbl_benchmark_label, "GOOD")   == 0) strcpy(my_bg_color, "#a8ff98");
    if (strcmp(gbl_benchmark_label, "GOOD")   == 0) strcpy(my_bg_color, "#c0ffc0");


//    if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_bg_color, "#ff98a8");
//    if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_bg_color, "#ffb5c9");


    if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_bg_color, "#fd0102");



//    if (strcmp(gbl_benchmark_label, "OMG")    == 0) strcpy(my_bg_color, "#ff4477");
    if (strcmp(gbl_benchmark_label, "OMG")    == 0) strcpy(my_bg_color, "#ff7ba3");
    
    // replace area_line_curr with the benchmark label and color

    mkstr(part_before, line_curr, line_curr + 20 -1);

    strcpy(part_after, line_curr + 20 + (len_label + 2 -1 + 1));

    sprintf(part_middle, "<span style=\"background-color:%s\"> %s </span>",
      my_bg_color, 
      gbl_benchmark_label); 
     
     if (strstr(gbl_benchmark_label, "OMG") != NULL) {
       sprintf(part_middle, "<span style=\"background-color:%s\"> %s </span>",
         "#fd0102", 
         gbl_benchmark_label); 
     }

      sprintf(changed_line, "%s%s%s", part_before, part_middle, part_after);
//tn();
//ksn(part_before);
//ksn(part_middle);
//ksn(part_after);
//ksn(changed_line);ki(retval_goodtogo);tn();


       strcpy(line_curr, changed_line);  // return changed line (by changing it in place)
  } else {
    retval_goodtogo = 7;  // flag to run   void  change_last_7_chars()
  }
//kin(retval_goodtogo); tr("7 means  flag to run   void  change_last_7_chars()  1=good  0=bad");
//tn();
  return retval_goodtogo;

} // end of insert_label_benchmark()


// e.g. for GREAT  =>    <span style="color:#66ff33;">-------</span
// algorithm
//   1. remove the len + 2 spaces altogether from line_to_change
//   2. remove first char (is a sp)
//   3. prepend this:  " <span style="color:#000000"> ----- </span>"
void insert_minus_benchmark(char *line_to_change) {

//tn();trn("in insert_minus_benchmark() ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"); 
//ksn(line_to_change); 
  char changed_line[8192], part_before[8192], part_after[8192], part_new_front[8192], mywork[8192], my_text_color[32];
  char my_minuses[1024];
    //  char part_removed[1024];
  int  len_label;
  len_label = (int)strlen(gbl_benchmark_label);
  sfill(my_minuses,  len_label, '-'); 

//  if (strstr(gbl_benchmark_label, "OMG") != NULL) {
//     len_label = 5;                                  // fix display glitch
//     sfill(my_minuses,  len_label, '-'); 
//  }

  //my_minuses[0]             = ' ';    // put sp instead of '-' on first and last char
  //my_minuses[len_label - 1] = ' ';    // put sp instead of '-' on first and last char


//  if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_text_color, "#66ff33");
//  if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_text_color, "#80ff40");
  if (strcmp(gbl_benchmark_label, "GREAT")  == 0) strcpy(my_text_color, "#33ff33"); // redline=#33ff33


//    if (strcmp(gbl_benchmark_label, "GOOD")   == 0) strcpy(my_text_color, "#a8ff98");
  if (strcmp(gbl_benchmark_label, "GOOD")   == 0) strcpy(my_text_color, "#c0ffc0");


//    if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_text_color, "#ff98a8");
//  if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_text_color, "#ffb5c9");
  if (strcmp(gbl_benchmark_label, "STRESS") == 0) strcpy(my_text_color, "#ffffff");


//    if (strcmp(gbl_benchmark_label, "OMG")    == 0) strcpy(my_text_color, "#ff4477");
  if (strcmp(gbl_benchmark_label, "OMG")    == 0) strcpy(my_text_color, "#ff7ba3");
    

  
//strcpy(my_text_color, "#000000"); // for TEST to see  


  //   1. remove the len + 2 spaces altogether from line_to_change
  //   2. remove first char (is a sp)   (see ange + 1)
  mkstr(part_before, line_to_change + 1, line_to_change + 20 -1); // +1 removes 1st char (sp)
  strcpy(part_after, line_to_change + 20 + (len_label + 2 - 1 + 1)); 




//tn();b(300);ks(part_after);
  // there are trailing 7 spaces.  remove  6 of them, leaving the standard 1 sp at end
//  part_after[(int)strlen(part_after) - 1 - 7] = '\0';
//tn();b(301);ks(part_after);

  sprintf(mywork, "%s%s", part_before, part_after);



//tn();trn("---------------------------------------------------------------------------");
//ksn(part_before);
//ksn(part_after);
//trn("with spaces removed=");ks(mywork);
//kin(strlen(line_to_change));
//trn("strlen of 1sp at beg= [1]");
//kin(strlen(part_before));
//mkstr(part_removed, line_to_change + 20 -1 +1, line_to_change  + 20 + (len_label + 2 - 1 + 1 -1));
//kin(strlen(part_removed));
//kin(strlen(part_after));
//ksn(line_to_change);
//trn("is 1 sp at beg (not in graph)");
//ksn(part_before);
//ksn(part_removed);
//ksn(part_after);
//trn("---------------------------------------------------------------------------");tn();
//


//<span style="background-color:#66ff33"> </span>

//   3. prepend this:  " <span style="color:#000000"> ----- </span>"
  sprintf(part_new_front,
    "%s<span style=\"background-color:%s\"> </span><span style=\"color:%s\">%s</span><span style=\"background-color:%s\"> </span>",
    " ",           // put back 1 sp removed with +1 in 2. above
    my_text_color, 
    my_text_color, 
    my_minuses, 
    my_text_color); 

  sprintf(changed_line, "%s%s", part_new_front, mywork);
//ksn(part_new_front);
//ksn(changed_line);tn(); 

  strcpy(line_to_change, changed_line);  // return changed line

} // end of insert_minus_benchmark()


void  change_last_7_chars(char *line_to_print) {
  //
  // remove the 7 chars and replace them with one space
  // unless it is benchmark line, then remove from the beginning of the last <span>
  // to the end of the line
  //    <span class="cGr2"> GREAT </span>
  //    123456789012345678901234567890123
  //    <span class="cGre"> GOOD  </span>
  //    <span class="cRed"> STRESS</span>
  //  and replace *them* with one space

  char workline[8192], mywk[8192];

// tn();trn("in change_last_7_chars(char *line_to_print) 7777777777777777777777777777777777777777777777777777777777777777"); 
// ksn(line_to_print);tn(); 

  if ((int)strlen(line_to_print) == 0) return;

  strcpy(workline, line_to_print);

  if (strstr(line_to_print, "GREAT")  != NULL  ||
      strstr(line_to_print, "GOOD")   != NULL  ||
      strstr(line_to_print, "STRESS") != NULL  ||
      strstr(line_to_print, "OMG")    != NULL     ) {
    mkstr(workline, line_to_print, line_to_print + (int)strlen(workline) - 1 - 33);
//ksn(workline);
  } else {
    // remove trailing 7  spaces only if they are there
    strcpy(mywk, line_to_print + (int)strlen(line_to_print) - 7);
//ksn(mywk);
    if (strcmp(mywk, "       ") == 0) {
//trn("in mywk == spaces");
      mkstr(workline, line_to_print, line_to_print + (int)strlen(line_to_print) - 1 -  7);
//ksn(line_to_print);
//ksn(workline);
    } else {
//trn("in mywk != spaces");
      strcpy(line_to_print, workline); // do not append one space
//ksn(line_to_print);
      return;
    }
  }
//ksn(line_to_print);

  // here trailing chars are removed, now append one sp
  sprintf(line_to_print, "%s ", workline);
//ksn(line_to_print);

  return;

} // end of  change_last_7_chars(char *line_to_print) {


// should be left with raw chars no html
//
void  remove_spans(char *linethird) {
  char workstr[8192], mychar;
  int  mylen, are_in_a_span, write_idx;

  mylen = (int)strlen(linethird);
  are_in_a_span = 0;
  write_idx     = -1;

  for (int i=0; i < mylen; i++) {
    mychar =  linethird[i];
    if (mychar == '<') {
      are_in_a_span = 1;
      continue;
    } 
    if (mychar == '>') {
      are_in_a_span = 0;
      continue;
    }
    if (are_in_a_span == 1) {
      continue;
    } else {
      write_idx = write_idx + 1;
      workstr[write_idx] = mychar;
    }
  }
  write_idx = write_idx + 1;
  workstr[write_idx] = '\0';

  strcpy (linethird, workstr);

} // end of  remove_spans()


/* end of futhtm.c */
