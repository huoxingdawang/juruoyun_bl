/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_TIME_H
#define __JRY_BL_TIME_H
#include "jry_bl_time_config.h"
#if JRY_BL_TIME_ENABLE==1
#include <sys/timeb.h>
#if JRY_BL_USE_STDARG==1
#include <stdarg.h>
#endif
typedef struct __jry_bl_time
{
	jry_bl_uint64 s;
	jry_bl_uint16 ms;
}jry_bl_time;
void	jry_bl_time_init		(jry_bl_time *this);
void	jry_bl_time_free		(jry_bl_time *this);
void	jry_bl_time_clear		(jry_bl_time *this);
void	jry_bl_time_now			(jry_bl_time *this);
#define	jry_bl_time_minus(x,y)	(((x)->s-(y)->s)*1000+((x)->ms-(y)->ms))


#if JRY_BL_USE_STDARG==1
void	jry_bl_time_inits		(int n,...);
void	jry_bl_time_frees		(int n,...);
void	jry_bl_time_clears		(int n,...);
#endif

#endif
#endif
