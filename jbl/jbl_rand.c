/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
	  http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_rand.h"
#if JBL_RAND_ENABLE==1
/*******************************************************************************************/
/*                            依赖jbl_ying jbl_exception                                   */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_ying.h"
#include "jbl_pthread.h"
/*******************************************************************************************/
/*                            联动jbl_string                                               */
/*******************************************************************************************/
#include "jbl_string.h"
#if JBL_RAND_USE_MERSENN==1
/*******************************************************************************************/
/*                            以下函数完成梅森旋转树伪随机                               */
/*******************************************************************************************/
static struct
{
	jbl_pthread_lock_define;
	jbl_uint32 index;
	jbl_uint32 buf[624];
}__jbl_rand_data;
/*
·(w, n, m, r) = (32, 624, 397, 31)
·a = 9908B0DF（16）
·f = 1812433253
·(u, d) = (11, FFFFFFFF16)
·(s, b) = (7, 9D2C568016)
·(t, c) = (15, EFC6000016)
·l = 18
MT19937-64的参数列表如下：
·(w, n, m, r) = (64, 312, 156, 31)
·a = B5026F5AA96619E9（16）
·f = 6364136223846793005
·(u, d) = (29, 555555555555555516)
·(s, b) = (17, 71D67FFFEDA6000016)
·(t, c) = (37, FFF7EEE00000000016)
·l = 43
*/


/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
void jbl_rand_start()
{
	jbl_pthread_lock_init(&__jbl_rand_data);
	jbl_rand_srand(1);
}
void jbl_rand_stop()
{
	jbl_pthread_lock_free(&__jbl_rand_data);
}
void jbl_rand_srand(jbl_uint32 seed)
{
	jbl_pthread_lock_wrlock(&__jbl_rand_data);
	__jbl_rand_data.buf[__jbl_rand_data.index=0]=seed;
	for(jbl_uint16 i=1;i<624;++i)
		__jbl_rand_data.buf[i]=(0X6C078965*(__jbl_rand_data.buf[i-1]^(__jbl_rand_data.buf[i-1]>>30))+i)&0xffffffff;
	jbl_pthread_lock_unwrlock(&__jbl_rand_data);
}
void __jbl_rand_generate()
{
	jbl_pthread_lock_wrlock(&__jbl_rand_data);
	for(jbl_uint16 i=0;i<624;i++)
	{
		jbl_uint32 y=(__jbl_rand_data.buf[i]&0x80000000)+(__jbl_rand_data.buf[(i+1)%624]&0x7fffffff);
		__jbl_rand_data.buf[i]=__jbl_rand_data.buf[(i+397)%624]^(y>>1);
		if(y&1)__jbl_rand_data.buf[i]^=0x9908B0DF;
	}
	jbl_pthread_lock_unwrlock(&__jbl_rand_data);
}
jbl_uint32 jbl_rand()
{
	if(!__jbl_rand_data.index)__jbl_rand_generate();
	jbl_pthread_lock_wrlock(&__jbl_rand_data);
	jbl_uint32 y=__jbl_rand_data.buf[__jbl_rand_data.index];
	__jbl_rand_data.index=(__jbl_rand_data.index+1)%624;
	jbl_pthread_lock_unwrlock(&__jbl_rand_data);
	y=y^(y>>11);
	y=y^((y<<7)&0x9D2C5680);
	y=y^((y<<15)&0xEFC60000);
	y=y^(y>>18);
	return y;
}
#elif JBL_RAND_USE_STDLIB==1
/*******************************************************************************************/
/*                            以下函数完成对stdlib随机函数封装                           */
/*******************************************************************************************/
#include <stdlib.h>
JBL_INLINE void jbl_rand_srand(jbl_uint32 seed){srand(seed);}
JBL_INLINE jbl_uint32 jbl_rand(){return (jbl_uint32)rand();}
#else
/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
static struct
{
	jbl_pthread_lock_define;
	jbl_uint32 next;
}__jbl_rand_data;
/*******************************************************************************************/
/*                            以下函数完成我也不知道叫啥的伪随机                        */
/*******************************************************************************************/
JBL_INLINE void jbl_rand_srand(jbl_uint32 seed){jbl_pthread_lock_wrlock(&__jbl_rand_data);__jbl_rand_data.next=seed;jbl_pthread_lock_unwrlock(&__jbl_rand_data);}
JBL_INLINE jbl_uint32 jbl_rand()
{
	jbl_pthread_lock_wrlock(&__jbl_rand_data);
	jbl_uint32 i=__jbl_rand_data.next=__jbl_rand_data.next*1103515245+12345;
	jbl_pthread_lock_unwrlock(&__jbl_rand_data);
	return((jbl_uint32)(i/65536)%32768);

}
#endif
JBL_INLINE jbl_uint32 jbl_rand_between(jbl_uint32 a,jbl_uint32 b)
{
	return jbl_rand()%(b-a+1)+a;
}
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现随机字符串                                     */
/*******************************************************************************************/
jbl_string * jbl_rand_string(jbl_string *this,jbl_string_size_type len,unsigned char* s)
{
	this=jbl_string_extend(this,len);
	jbl_string * thi=jbl_refer_pull(this);
	for(jbl_string_size_type i=0,n=jbl_strlen(s);i<len;jbl_string_add_char_force(thi,s[jbl_rand_between(0,(jbl_uint32)(n-1))]),++i);
	return this;
}
#endif 

#endif
