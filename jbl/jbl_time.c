/* Generated by re2c 1.3 on Mon Aug 10 21:25:32 2020 */
#line 1 "jbl/jbl_time.l"
/* Generated by re2c 1.3 on Fri Jul 24 11:31:45 2020 */
/* Generated by re2c 1.3 on Fri Jul 24 11:25:13 2020 */
/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_time.h"
#if JBL_TIME_ENABLE==1
/*******************************************************************************************/
/*                            依赖jbl_gc jbl_malloc jbl_ying jbl_exception                */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_gc.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#include <sys/time.h>
/*******************************************************************************************/
/*                            联动jbl_string jbl_var                                       */
/*******************************************************************************************/
#include "jbl_string.h"
#include "jbl_var.h"
/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
jbl_int8		jbl_time_time_zone=JBL_TIME_DEFAULT_TIME_ZONE;
/*******************************************************************************************/
/*                            以下函实现时间基本操作                                     */
/*******************************************************************************************/
inline jbl_time * jbl_time_new()
{
	return jbl_time_init(jbl_malloc(sizeof(jbl_time)));
}
inline jbl_time * jbl_time_init(jbl_time *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);
	this->t=0;
	return this;
}
inline jbl_time * jbl_time_free(jbl_time *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_time_free((jbl_time*)(((jbl_reference*)this)->ptr)):0);
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif
			jbl_free(this);
	}
	return NULL;
}
inline jbl_time * jbl_time_set(jbl_time * this,jbl_uint64 time)
{
	if(!this)this=jbl_time_new();
	((jbl_time *)(jbl_refer_pull(this)))->t=time;
	return this;
}
inline jbl_time * jbl_time_copy(jbl_time * that)
{
	if(that==NULL)return NULL;
#if JBL_VAR_ENABLE==1
	if(jbl_gc_is_var(that))
		return jbl_time_set(jbl_Vtime(jbl_Vtime_new()),((jbl_time*)jbl_refer_pull(that))->t);
	else
#endif
	return jbl_time_set(NULL,((jbl_time*)jbl_refer_pull(that))->t);
}
inline jbl_time * jbl_time_add_second(jbl_time * this,jbl_uint64 second)
{
	if(!this)this=jbl_time_new();
	((jbl_time *)(jbl_refer_pull(this)))->t+=second*1000;
	return this;
}
/*******************************************************************************************/
/*                            以下函实现时间获取操作                                     */
/*******************************************************************************************/
inline jbl_time * jbl_time_now(jbl_time *this)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return jbl_time_set(this,(((jbl_int64)tv.tv_sec)*1000)+(tv.tv_usec/1000));
}
void jbl_time_decode(jbl_time *this,jbl_time_decoded *tt)
{
	if(this==NULL)return;
	jbl_int64 ts=jbl_time_to_unix(this);
	int days=0,dayTmp=0,secs=0;
	if(jbl_time_time_zone==JBL_TIME_ZONE_ASIA_SHANGHAI)
		ts+=8*3600000;
	if(ts>0)
	{
		tt->ms=ts%1000,ts/=1000,days=ts/86400,secs=ts%86400;
		for(tt->year=1970;days>0;++tt->year)
			if(days>=(dayTmp=(365+(tt->isleap=jbl_time_if_leap_year(tt->year)))))
				days-=dayTmp;
			else
				break;
		for(tt->month=1;tt->month<12;++tt->month)
			if(days>=(dayTmp=jbl_time_get_day_of_month(tt->month,tt->year)))
				days-=dayTmp;
			else
				break;
		tt->month=tt->month,tt->day=days+1,tt->dom=dayTmp;
	}
	else
	{
		tt->ms=(1000-(-ts)%1000),ts=((ts-(1000-tt->ms))/1000),((tt->ms==1000)?(tt->ms=0):0),secs=-(ts%86400),secs=(secs==0)?0:(86400-secs),days=(ts-secs)/86400;
		for(tt->year=1969;days<0;--tt->year)
			if((-days)>=(dayTmp=(365+(tt->isleap=jbl_time_if_leap_year(tt->year)))))
				days+=dayTmp;
			else
				break;
		for(tt->month=12;tt->month>0;--tt->month)
			if(days<(dayTmp=jbl_time_get_day_of_month(tt->month,tt->year)))
				days+=dayTmp;
			else
				break;
		tt->dom=dayTmp;
		if(days>jbl_time_get_day_of_month(tt->month+1,tt->year))
			++tt->month,days-=(tt->dom=jbl_time_get_day_of_month(tt->month,tt->year));
		tt->month=tt->month+1,tt->day=days+1;
	}
	tt->hour=secs/3600,secs%=3600,tt->minute=secs/60,tt->second=secs%60;
	tt->week=jbl_time_get_weekday(tt->day,tt->month,tt->year);
}
/*******************************************************************************************/
/*                            以下函实现时间比较操作                                      */
/*******************************************************************************************/
inline char jbl_time_space_ship(jbl_time *this,jbl_time *that)
{
	jbl_int64 t=jbl_time_minus(this,that);
	return (t>0)?1:((t<0)?(-1):0);
}
/*******************************************************************************************/
/*                            以下函实现特殊时间判断操作                                 */
/*******************************************************************************************/
inline jbl_uint8	jbl_time_if_leap_year		(jbl_uint32 year){return (((year%400)==0)?1:(((year%100)==0)?0:(((year%4)==0)?1:0)));}
inline jbl_uint8	jbl_time_get_day_of_month	(jbl_uint8 month,jbl_uint32 year){static const jbl_uint8 dpm[12]={31,28,31,30,31,30,31,31,30,31,30,31};return (month==2||(month==0)||(month>12))?(dpm[1]+jbl_time_if_leap_year(year)):(dpm[month-1]);}
inline jbl_uint8	jbl_time_get_weekday		(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year){if((month==1)||(month==2))month+=12,year--;return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7+1;}
jbl_uint8 jbl_time_if_dst(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year)
{
	if(jbl_time_time_zone==JBL_TIME_ZONE_ASIA_SHANGHAI)
	{
		
		
		
	}
	return false;
}
jbl_time_key __jbl_time_key_scaner(const unsigned char * YYCURSOR,const unsigned char * YYLIMIT,const unsigned char **addr)
{
	#define YYCTYPE		unsigned char
	#define YYFILL(n)	return JBL_TIME_KEY_END;
    
#line 167 "jbl/jbl_time.c"
{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '%':	goto yy4;
	case 'A':	goto yy6;
	case 'B':	goto yy8;
	case 'D':	goto yy10;
	case 'F':	goto yy12;
	case 'G':	goto yy14;
	case 'H':	goto yy16;
	case 'I':	goto yy18;
	case 'L':	goto yy20;
	case 'M':	goto yy22;
	case 'N':	goto yy24;
	case 'O':	goto yy26;
	case 'P':	goto yy28;
	case 'S':	goto yy30;
	case 'T':	goto yy32;
	case 'U':	goto yy34;
	case 'W':	goto yy36;
	case 'Y':	goto yy38;
	case 'Z':	goto yy40;
	case 'a':	goto yy42;
	case 'd':	goto yy44;
	case 'e':	goto yy46;
	case 'g':	goto yy48;
	case 'h':	goto yy50;
	case 'i':	goto yy52;
	case 'j':	goto yy54;
	case 'l':	goto yy56;
	case 'm':	goto yy58;
	case 'n':	goto yy60;
	case 'o':	goto yy62;
	case 's':	goto yy64;
	case 't':	goto yy66;
	case 'u':	goto yy68;
	case 'w':	goto yy70;
	case 'y':	goto yy72;
	case 'z':	goto yy74;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
#line 163 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_UNDEFINED;}
#line 215 "jbl/jbl_time.c"
yy4:
	++YYCURSOR;
#line 164 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_ESCAPE;}
#line 220 "jbl/jbl_time.c"
yy6:
	++YYCURSOR;
#line 189 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_A;}
#line 225 "jbl/jbl_time.c"
yy8:
	++YYCURSOR;
#line 190 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SWATCH;}
#line 230 "jbl/jbl_time.c"
yy10:
	++YYCURSOR;
#line 168 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOW3;}
#line 235 "jbl/jbl_time.c"
yy12:
	++YYCURSOR;
#line 177 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_M;}
#line 240 "jbl/jbl_time.c"
yy14:
	++YYCURSOR;
#line 192 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H12WZ;}
#line 245 "jbl/jbl_time.c"
yy16:
	++YYCURSOR;
#line 194 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H24WZ;}
#line 250 "jbl/jbl_time.c"
yy18:
	++YYCURSOR;
#line 200 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_IDST;}
#line 255 "jbl/jbl_time.c"
yy20:
	++YYCURSOR;
#line 183 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_YILY;}
#line 260 "jbl/jbl_time.c"
yy22:
	++YYCURSOR;
#line 179 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_M3;}
#line 265 "jbl/jbl_time.c"
yy24:
	++YYCURSOR;
#line 170 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWN;}
#line 270 "jbl/jbl_time.c"
yy26:
	++YYCURSOR;
#line 201 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_HTG;}
#line 275 "jbl/jbl_time.c"
yy28:
	++YYCURSOR;
#line 202 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DWG;}
#line 280 "jbl/jbl_time.c"
yy30:
	++YYCURSOR;
#line 171 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOMS;}
#line 285 "jbl/jbl_time.c"
yy32:
	++YYCURSOR;
#line 203 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TZ;}
#line 290 "jbl/jbl_time.c"
yy34:
	++YYCURSOR;
#line 205 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_S;}
#line 295 "jbl/jbl_time.c"
yy36:
	++YYCURSOR;
#line 175 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_WOY;}
#line 300 "jbl/jbl_time.c"
yy38:
	++YYCURSOR;
#line 185 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_Y;}
#line 305 "jbl/jbl_time.c"
yy40:
	++YYCURSOR;
#line 204 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_STG;}
#line 310 "jbl/jbl_time.c"
yy42:
	++YYCURSOR;
#line 188 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SA;}
#line 315 "jbl/jbl_time.c"
yy44:
	++YYCURSOR;
#line 167 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOMWZ;}
#line 320 "jbl/jbl_time.c"
yy46:
	++YYCURSOR;
#line 199 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TZT;}
#line 325 "jbl/jbl_time.c"
yy48:
	++YYCURSOR;
#line 191 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H12;}
#line 330 "jbl/jbl_time.c"
yy50:
	++YYCURSOR;
#line 193 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H24;}
#line 335 "jbl/jbl_time.c"
yy52:
	++YYCURSOR;
#line 195 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MWZ;}
#line 340 "jbl/jbl_time.c"
yy54:
	++YYCURSOR;
#line 166 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOM;}
#line 345 "jbl/jbl_time.c"
yy56:
	++YYCURSOR;
#line 169 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWA;}
#line 350 "jbl/jbl_time.c"
yy58:
	++YYCURSOR;
#line 178 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MNWZ;}
#line 355 "jbl/jbl_time.c"
yy60:
	++YYCURSOR;
#line 180 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MN;}
#line 360 "jbl/jbl_time.c"
yy62:
	++YYCURSOR;
#line 184 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_YISO;}
#line 365 "jbl/jbl_time.c"
yy64:
	++YYCURSOR;
#line 196 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SWZ;}
#line 370 "jbl/jbl_time.c"
yy66:
	++YYCURSOR;
#line 181 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TDOM;}
#line 375 "jbl/jbl_time.c"
yy68:
	++YYCURSOR;
#line 197 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MSWZ;}
#line 380 "jbl/jbl_time.c"
yy70:
	++YYCURSOR;
#line 172 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWNF0;}
#line 385 "jbl/jbl_time.c"
yy72:
	++YYCURSOR;
#line 186 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_Y2;}
#line 390 "jbl/jbl_time.c"
yy74:
	++YYCURSOR;
#line 173 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOY;}
#line 395 "jbl/jbl_time.c"
}
#line 207 "jbl/jbl_time.c"

	#undef YYCTYPE
	#undef YYFILL
}
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函实现时间对字符串操作                                */
/*******************************************************************************************/
jbl_string * jbl_time_to_string_format(jbl_time *this,jbl_string *result,const unsigned char * format)
{
	jbl_time_decoded tt;
	jbl_time_decode(this,&tt);
	jbl_string_size_type n=jbl_strlen(format),i=0;
	const unsigned char * addr;
	jbl_time_key key;
	const char * doms[]	={"th","st","nd","rd","th","th","th","th","th","th"};
	const char * dowa[]	={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	const char * dow3[]	={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
	const char * m[]	={"January","February","March","April","May","June","July","August","September","October","November","December"};
	const char * m3[]	={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	const char * sa[]	={"am","pm"};
	const char * a[]	={"AM","PM"};
	while((key=__jbl_time_key_scaner(format+i,format+n,&addr))!=JBL_TIME_KEY_END)
	{
		i=addr-format;
		switch(key)
		{
			case JBL_TIME_KEY_UNDEFINED	:result=jbl_string_add_char(result,format[i-1])					;break;			
			case JBL_TIME_KEY_ESCAPE	:if(format[i])result=jbl_string_add_char(result,format[i]),++i	;break;			
			case JBL_TIME_KEY_END		:return result;break;
			
			case JBL_TIME_KEY_DOM		:result=jbl_string_add_uint(result,tt.day)					;break;
			case JBL_TIME_KEY_DOMWZ		:result=jbl_string_add_uint_length(result,tt.day,2,'0')		;break;
			case JBL_TIME_KEY_DOMS		:result=jbl_string_add_chars(result,UC doms[tt.day%10])			;break;
			case JBL_TIME_KEY_DOW3		:result=jbl_string_add_chars(result,UC dow3[tt.week-1])			;break;
			case JBL_TIME_KEY_DOWA		:result=jbl_string_add_chars(result,UC dowa[tt.week-1])			;break;
			case JBL_TIME_KEY_DOWN		:result=jbl_string_add_uint(result,tt.week)					;break;
			case JBL_TIME_KEY_DOWNF0	:result=jbl_string_add_uint(result,tt.week-1)					;break;
			case JBL_TIME_KEY_DOY		:break;
			
			case JBL_TIME_KEY_WOY		:break;
			
			case JBL_TIME_KEY_M			:result=jbl_string_add_chars(result,UC m[tt.month-1])			;break;	
			case JBL_TIME_KEY_MNWZ		:result=jbl_string_add_uint_length(result,tt.month,2,'0')		;break;
			case JBL_TIME_KEY_M3		:result=jbl_string_add_chars(result,UC m3[tt.month-1])			;break;	
			case JBL_TIME_KEY_MN		:result=jbl_string_add_uint(result,tt.month)					;break;	
			case JBL_TIME_KEY_TDOM		:result=jbl_string_add_uint(result,tt.dom)					;break;			

			case JBL_TIME_KEY_YILY		:result=jbl_string_add_uint(result,tt.isleap)					;break;
			case JBL_TIME_KEY_Y			:result=jbl_string_add_uint_length(result,tt.year,4,'0')		;break;
			case JBL_TIME_KEY_YISO		:break;
			case JBL_TIME_KEY_Y2		:result=jbl_string_add_uint_length(result,tt.year%100,2,'0')	;break;	
			
			
			
			case JBL_TIME_KEY_SA		:result=jbl_string_add_chars(result,UC sa[tt.hour/12])			;break;
			case JBL_TIME_KEY_A			:result=jbl_string_add_chars(result,UC a[tt.hour/12])			;break;
			case JBL_TIME_KEY_SWATCH	:break;
			case JBL_TIME_KEY_H12		:result=jbl_string_add_uint(result,tt.hour%12)				;break;
			case JBL_TIME_KEY_H12WZ		:result=jbl_string_add_uint_length(result,tt.hour%12,2,'0')	;break;
			case JBL_TIME_KEY_H24		:result=jbl_string_add_uint(result,tt.hour)					;break;
			case JBL_TIME_KEY_H24WZ		:result=jbl_string_add_uint_length(result,tt.hour,2,'0')		;break;
			case JBL_TIME_KEY_MWZ		:result=jbl_string_add_uint_length(result,tt.minute,2,'0')	;break;
			case JBL_TIME_KEY_SWZ		:result=jbl_string_add_uint_length(result,tt.second,2,'0')	;break;
			case JBL_TIME_KEY_MSWZ		:result=jbl_string_add_uint_length(result,tt.ms,2,'0')		;break;
			
			
			case JBL_TIME_KEY_TZT		:result=jbl_string_add_chars(result,UC "GMT")					;break;
			case JBL_TIME_KEY_IDST		:break;
			case JBL_TIME_KEY_HTG		:break;
			case JBL_TIME_KEY_DWG		:break;
			case JBL_TIME_KEY_TZ		:break;
			case JBL_TIME_KEY_STG		:break;
			case JBL_TIME_KEY_S			:result=jbl_string_add_uint(result,this->t/1000)				;break;

			
		}
	}
	return result;
}
jbl_string * jbl_time_to_string(jbl_time *this,jbl_string *result)
{
	return jbl_time_to_string_format(this,result,UC "Y-m-d H:i:s D");
}
#endif
#if JBL_JSON_ENABLE==1
/*******************************************************************************************/
/*                            以下函实现时间JSON操作                                      */
/*******************************************************************************************/
#if JBL_STRING_ENABLE==1
inline jbl_string* jbl_time_json_encode(jbl_time* this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
	jbl_string *s1=jbl_time_to_string_format(this,NULL,UC "Y-m-d H:i:s D");
	out=jbl_string_json_encode(s1,out,format,tabs);
	jbl_string_free(s1);
	return out;
}
#endif
#if JBL_STREAM_ENABLE==1
void jbl_time_json_put(jbl_time* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs)
{
#if JBL_STRING_ENABLE==1
	jbl_string *s1=jbl_time_to_string_format(this,NULL,UC "Y-m-d H:i:s D");
	jbl_string_json_put(s1,out,format,tabs);
	jbl_string_free(s1);	
#else
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),out,format,tabs))return;
	jbl_stream_push_int(out,this->t);
	if(format&2){jbl_stream_push_char(out,',');}if((format&1)||(format&4)){jbl_stream_push_char(out,'\n');}
#endif
}
#endif
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现时间的浏览操作                                 */
/*******************************************************************************************/
jbl_time* jbl_time_view_put(jbl_time* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	jbl_time * thi;if(jbl_stream_view_put_format(thi=jbl_refer_pull(this),out,format,tabs,UC"jbl_time",line,varname,func,file)){jbl_stream_push_char(out,'\n');return this;}
	jbl_stream_push_chars(out,UC"\ttime stamp:");
	jbl_stream_push_int(out,thi->t);
#if JBL_STRING_ENABLE==1
	jbl_stream_push_chars(out,UC"\tdate:");
	jbl_string *s1=jbl_time_to_string(thi,NULL);
	jbl_stream_push_string(out,s1);
	jbl_string_free(s1);	
#endif
	jbl_stream_push_char(out,'\n');
	return this;
}
#endif

#if JBL_VAR_ENABLE==1
/*******************************************************************************************/
/*                            以下函实现时间的var操作                                    */
/*******************************************************************************************/
jbl_var_operators_new(jbl_time_operators,jbl_time_free,jbl_time_copy,jbl_time_space_ship,jbl_time_json_encode,jbl_time_view_put,jbl_time_json_put);
inline jbl_time* jbl_Vtime(jbl_var * this){if(this&&!Vis_jbl_time(this))jbl_exception("VAR TYPE ERROR");return((jbl_time*)this);}
jbl_var * jbl_Vtime_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_time))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_time_init((jbl_time*)this);
	jbl_gc_set_var((jbl_time*)this);
	jbl_var_set_operators(this,&jbl_time_operators);
	return this;
}
jbl_var * jbl_time_copy_as_var(jbl_time *that)
{
	if(that==NULL)return NULL;
	if(jbl_gc_is_var(that))
		return jbl_V(jbl_time_copy(that));
	if(jbl_gc_is_ref(that))
	{
		void *data=that;
		jbl_gc_plus((jbl_reference*)that);//出来的data ref_cnt一定是2
		jbl_refer_as_var(&data,&jbl_time_operators);
		jbl_gc_minus((jbl_reference*)data);//出来的data ref_cnt一定是2
		return jbl_V(data);
	}	
	return jbl_V(jbl_time_set(jbl_Vtime(jbl_Vtime_new()),((jbl_time*)jbl_refer_pull(that))->t));
}
#endif
#endif
