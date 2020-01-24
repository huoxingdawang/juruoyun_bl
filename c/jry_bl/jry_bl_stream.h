/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_STREAM_H
#define __JRY_BL_STREAM_H
#include "jry_bl_stream_config.h"
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_ying.h"
#include <stdio.h>
typedef struct __jry_bl_stream
{
	void (*op)(struct __jry_bl_stream*,jry_bl_uint8);
	struct __jry_bl_stream *nxt;
	jry_bl_uint16	en;
	jry_bl_uint16	size;
	void			*data;
	jry_bl_uint64	tmp;
	unsigned char	*buf;
}jry_bl_stream;



#define jry_bl_stream_init(z,o,d,b,s)		(z)->op=(o),(z)->data=(d),(z)->en=(0),(z)->tmp=(0),(z)->buf=(b),(z)->nxt=(NULL),(z)->size=s
#define jry_bl_stream_free(z)				(z)->op=NULL,(z)->data=NULL,(z)->en=(0),(z)->tmp=(0),(z)->buf=NULL,(z)->nxt=(NULL)
#define jry_bl_stream_do(this,flag)			(this)->op(this,flag)
#define jry_bl_stream_connect(this,that)	(this)->nxt=that
#define jry_bl_stream_reset(this)			(this)->en=0,(this)->tmp=0

#define jry_bl_stream_force					B0000_0001

void jry_bl_stream_file_operator(jry_bl_stream* this,jry_bl_uint8 flags);

extern jry_bl_stream jry_bl_stream_stdout;
extern jry_bl_stream jry_bl_stream_stdin;
#define jry_bl_stream_start()	jry_bl_stream_init(&jry_bl_stream_stdout,jry_bl_stream_file_operator,stdout,jry_bl_malloc(JRY_BL_STREAM_EXCEED_LENGTH),JRY_BL_STREAM_EXCEED_LENGTH),	\
								jry_bl_stream_init(&jry_bl_stream_stdin ,jry_bl_stream_file_operator,stdin ,NULL,0)
#define jry_bl_stream_stop()	jry_bl_free(jry_bl_stream_stdout.buf),jry_bl_stream_free(&jry_bl_stream_stdout),	\
								jry_bl_stream_free(&jry_bl_stream_stdin )

#else
#define jry_bl_stream_start
#define jry_bl_stream_stop
#endif
#endif