/* Generated by re2c 1.3 on Wed Nov 11 11:55:20 2020 */
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
jbl_var_operators_new(jbl_time_operators,jbl_time_free,jbl_time_copy,jbl_time_space_ship,jbl_time_json_encode,jbl_time_view_put,jbl_time_json_put);
/*******************************************************************************************/
/*                            以下函实现时间基本操作                                     */
/*******************************************************************************************/
jbl_time * jbl_time_new()
{
	return jbl_time_init(jbl_malloc(sizeof(jbl_time)));
}
JBL_INLINE jbl_time * jbl_time_init(jbl_time *this)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_gc_init(this);
	jbl_gc_plus(this);
	jbl_var_set_operators(this,&jbl_time_operators);
	this->t=0;
	return this;
}
JBL_INLINE jbl_time * jbl_time_free(jbl_time *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_time_free((jbl_time*)(((jbl_reference*)this)->ptr)):0);
		jbl_free(this);
	}
	return NULL;
}
JBL_INLINE jbl_time * jbl_time_set(jbl_time * this,jbl_uint64 time)
{
	if(!this)this=jbl_time_new();
	((jbl_time *)(jbl_refer_pull(this)))->t=time;
	return this;
}
JBL_INLINE jbl_time * jbl_time_copy(jbl_time * that)
{
	if(!that)return NULL;
	return jbl_time_set(NULL,((jbl_time*)jbl_refer_pull(that))->t);
}
JBL_INLINE jbl_time * jbl_time_add_second(jbl_time * this,jbl_uint64 second)
{
	if(!this)this=jbl_time_new();
	((jbl_time *)(jbl_refer_pull(this)))->t+=second*1000;
	return this;
}
/*******************************************************************************************/
/*                            以下函实现时间获取操作                                     */
/*******************************************************************************************/
JBL_INLINE jbl_time * jbl_time_now(jbl_time *this)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return jbl_time_set(this,(((jbl_int64)tv.tv_sec)*1000)+(tv.tv_usec/1000));
}
void jbl_time_decode(jbl_time *this,jbl_time_decoded *tt)
{
	if(!this)
		{tt->year=tt->ms=tt->week=tt->dom=tt->day=tt->hour=tt->month=tt->minute=tt->second=tt->isleap=0;return;}
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
JBL_INLINE char jbl_time_space_ship(jbl_time *this,jbl_time *that)
{
	jbl_int64 t=jbl_time_minus(this,that);
	return (t>0)?1:((t<0)?(-1):0);
}
/*******************************************************************************************/
/*                            以下函实现特殊时间判断操作                                 */
/*******************************************************************************************/
JBL_INLINE jbl_uint8	jbl_time_if_leap_year		(jbl_uint32 year){return (((year%400)==0)?1:(((year%100)==0)?0:(((year%4)==0)?1:0)));}
JBL_INLINE jbl_uint8	jbl_time_get_day_of_month	(jbl_uint8 month,jbl_uint32 year){static const jbl_uint8 dpm[12]={31,28,31,30,31,30,31,31,30,31,30,31};return (month==2||(month==0)||(month>12))?(dpm[1]+jbl_time_if_leap_year(year)):(dpm[month-1]);}
JBL_INLINE jbl_uint8	jbl_time_get_weekday		(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year){if((month==1)||(month==2))month+=12,year--;return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7+1;}
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
    
#line 161 "jbl/jbl_time.c"
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
#line 157 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_UNDEFINED;}
#line 209 "jbl/jbl_time.c"
yy4:
	++YYCURSOR;
#line 158 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_ESCAPE;}
#line 214 "jbl/jbl_time.c"
yy6:
	++YYCURSOR;
#line 183 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_A;}
#line 219 "jbl/jbl_time.c"
yy8:
	++YYCURSOR;
#line 184 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SWATCH;}
#line 224 "jbl/jbl_time.c"
yy10:
	++YYCURSOR;
#line 162 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOW3;}
#line 229 "jbl/jbl_time.c"
yy12:
	++YYCURSOR;
#line 171 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_M;}
#line 234 "jbl/jbl_time.c"
yy14:
	++YYCURSOR;
#line 186 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H12WZ;}
#line 239 "jbl/jbl_time.c"
yy16:
	++YYCURSOR;
#line 188 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H24WZ;}
#line 244 "jbl/jbl_time.c"
yy18:
	++YYCURSOR;
#line 194 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_IDST;}
#line 249 "jbl/jbl_time.c"
yy20:
	++YYCURSOR;
#line 177 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_YILY;}
#line 254 "jbl/jbl_time.c"
yy22:
	++YYCURSOR;
#line 173 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_M3;}
#line 259 "jbl/jbl_time.c"
yy24:
	++YYCURSOR;
#line 164 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWN;}
#line 264 "jbl/jbl_time.c"
yy26:
	++YYCURSOR;
#line 195 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_HTG;}
#line 269 "jbl/jbl_time.c"
yy28:
	++YYCURSOR;
#line 196 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DWG;}
#line 274 "jbl/jbl_time.c"
yy30:
	++YYCURSOR;
#line 165 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOMS;}
#line 279 "jbl/jbl_time.c"
yy32:
	++YYCURSOR;
#line 197 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TZ;}
#line 284 "jbl/jbl_time.c"
yy34:
	++YYCURSOR;
#line 199 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_S;}
#line 289 "jbl/jbl_time.c"
yy36:
	++YYCURSOR;
#line 169 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_WOY;}
#line 294 "jbl/jbl_time.c"
yy38:
	++YYCURSOR;
#line 179 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_Y;}
#line 299 "jbl/jbl_time.c"
yy40:
	++YYCURSOR;
#line 198 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_STG;}
#line 304 "jbl/jbl_time.c"
yy42:
	++YYCURSOR;
#line 182 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SA;}
#line 309 "jbl/jbl_time.c"
yy44:
	++YYCURSOR;
#line 161 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOMWZ;}
#line 314 "jbl/jbl_time.c"
yy46:
	++YYCURSOR;
#line 193 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TZT;}
#line 319 "jbl/jbl_time.c"
yy48:
	++YYCURSOR;
#line 185 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H12;}
#line 324 "jbl/jbl_time.c"
yy50:
	++YYCURSOR;
#line 187 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_H24;}
#line 329 "jbl/jbl_time.c"
yy52:
	++YYCURSOR;
#line 189 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MWZ;}
#line 334 "jbl/jbl_time.c"
yy54:
	++YYCURSOR;
#line 160 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOM;}
#line 339 "jbl/jbl_time.c"
yy56:
	++YYCURSOR;
#line 163 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWA;}
#line 344 "jbl/jbl_time.c"
yy58:
	++YYCURSOR;
#line 172 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MNWZ;}
#line 349 "jbl/jbl_time.c"
yy60:
	++YYCURSOR;
#line 174 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MN;}
#line 354 "jbl/jbl_time.c"
yy62:
	++YYCURSOR;
#line 178 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_YISO;}
#line 359 "jbl/jbl_time.c"
yy64:
	++YYCURSOR;
#line 190 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_SWZ;}
#line 364 "jbl/jbl_time.c"
yy66:
	++YYCURSOR;
#line 175 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_TDOM;}
#line 369 "jbl/jbl_time.c"
yy68:
	++YYCURSOR;
#line 191 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_MSWZ;}
#line 374 "jbl/jbl_time.c"
yy70:
	++YYCURSOR;
#line 166 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOWNF0;}
#line 379 "jbl/jbl_time.c"
yy72:
	++YYCURSOR;
#line 180 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_Y2;}
#line 384 "jbl/jbl_time.c"
yy74:
	++YYCURSOR;
#line 167 "jbl/jbl_time.c"
	{if(addr)*addr=YYCURSOR;return JBL_TIME_KEY_DOY;}
#line 389 "jbl/jbl_time.c"
}
#line 201 "jbl/jbl_time.c"

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
#if JBL_STREAM_ENABLE==1
void jbl_stream_push_time(jbl_stream *out,jbl_time *this,const unsigned char * format)
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
			case JBL_TIME_KEY_UNDEFINED	:jbl_stream_push_char(out,format[i-1])					;break;			
			case JBL_TIME_KEY_ESCAPE	:if(format[i])jbl_stream_push_char(out,format[i]),++i	;break;			
			case JBL_TIME_KEY_END		:return ;break;
			
			case JBL_TIME_KEY_DOM		:jbl_stream_push_uint(out,tt.day)						;break;
			case JBL_TIME_KEY_DOMWZ		:jbl_stream_push_uint_length(out,tt.day,2,'0')			;break;
			case JBL_TIME_KEY_DOMS		:jbl_stream_push_chars(out,UC doms[tt.day%10])			;break;
			case JBL_TIME_KEY_DOW3		:jbl_stream_push_chars(out,UC dow3[tt.week-1])			;break;
			case JBL_TIME_KEY_DOWA		:jbl_stream_push_chars(out,UC dowa[tt.week-1])			;break;
			case JBL_TIME_KEY_DOWN		:jbl_stream_push_uint(out,tt.week)						;break;
			case JBL_TIME_KEY_DOWNF0	:jbl_stream_push_uint(out,tt.week-1)					;break;
			case JBL_TIME_KEY_DOY		:break;
			
			case JBL_TIME_KEY_WOY		:break;
			
			case JBL_TIME_KEY_M			:jbl_stream_push_chars(out,UC m[tt.month-1])			;break;	
			case JBL_TIME_KEY_MNWZ		:jbl_stream_push_uint_length(out,tt.month,2,'0')		;break;
			case JBL_TIME_KEY_M3		:jbl_stream_push_chars(out,UC m3[tt.month-1])			;break;	
			case JBL_TIME_KEY_MN		:jbl_stream_push_uint(out,tt.month)						;break;	
			case JBL_TIME_KEY_TDOM		:jbl_stream_push_uint(out,tt.dom)						;break;			

			case JBL_TIME_KEY_YILY		:jbl_stream_push_uint(out,tt.isleap)					;break;
			case JBL_TIME_KEY_Y			:jbl_stream_push_uint_length(out,tt.year,4,'0')			;break;
			case JBL_TIME_KEY_YISO		:break;
			case JBL_TIME_KEY_Y2		:jbl_stream_push_uint_length(out,tt.year%100,2,'0')		;break;	
			
			
			
			case JBL_TIME_KEY_SA		:jbl_stream_push_chars(out,UC sa[tt.hour/12])			;break;
			case JBL_TIME_KEY_A			:jbl_stream_push_chars(out,UC a[tt.hour/12])			;break;
			case JBL_TIME_KEY_SWATCH	:break;
			case JBL_TIME_KEY_H12		:jbl_stream_push_uint(out,tt.hour%12)					;break;
			case JBL_TIME_KEY_H12WZ		:jbl_stream_push_uint_length(out,tt.hour%12,2,'0')		;break;
			case JBL_TIME_KEY_H24		:jbl_stream_push_uint(out,tt.hour)						;break;
			case JBL_TIME_KEY_H24WZ		:jbl_stream_push_uint_length(out,tt.hour,2,'0')			;break;
			case JBL_TIME_KEY_MWZ		:jbl_stream_push_uint_length(out,tt.minute,2,'0')		;break;
			case JBL_TIME_KEY_SWZ		:jbl_stream_push_uint_length(out,tt.second,2,'0')		;break;
			case JBL_TIME_KEY_MSWZ		:jbl_stream_push_uint_length(out,tt.ms,2,'0')			;break;
			
			
			case JBL_TIME_KEY_TZT		:jbl_stream_push_chars(out,UC "GMT")					;break;
			case JBL_TIME_KEY_IDST		:break;
			case JBL_TIME_KEY_HTG		:break;
			case JBL_TIME_KEY_DWG		:break;
			case JBL_TIME_KEY_TZ		:break;
			case JBL_TIME_KEY_STG		:break;
			case JBL_TIME_KEY_S			:jbl_stream_push_uint(out,this->t/1000)					;break;

			
		}
	}
}
#endif
#if JBL_JSON_ENABLE==1
/*******************************************************************************************/
/*                            以下函实现时间JSON操作                                      */
/*******************************************************************************************/
#if JBL_STRING_ENABLE==1
JBL_INLINE jbl_string* jbl_time_json_encode(jbl_time* this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,tabs);if(!this)return out;
	out=jbl_string_add_char(out,'"');
	out=jbl_time_to_string_format(this,out,UC "Y-m-d H:i:s D");
	out=jbl_string_add_char(out,'"');
	if(format&2){out=jbl_string_add_char(out,',');}if((format&1)||(format&4)){out=jbl_string_add_char(out,'\n');}
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
	jbl_stream_push_time(out,thi,UC"\tY-m-d H:i:s.u");
	jbl_stream_push_char(out,'\n');
	return this;
}
#endif

#endif
