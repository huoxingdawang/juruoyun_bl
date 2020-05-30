/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_ying.h"
#if JBL_YING_ENABLE==1
inline jbl_int64 jbl_ceil(long double i)
{
	return (((jbl_int64)i)==i)?((jbl_int64)i):(((jbl_int64)i)+1);
}
/*
jbl_uint8 jbl_get_uint64_length(jbl_uint64 tmp)
{
	jbl_uint8 len=0;
	do{++len;}while((tmp=(((jbl_uint64)tmp)/10)));	
	return len;
}
jbl_uint8 jbl_get_int64_length(jbl_int64 tmp)
{
	jbl_uint8 len=0;
	if(tmp<0)
		tmp=-tmp,++len;
	do{++len;}while((tmp=(((jbl_uint64)tmp)/10)));	
	return len;
}
jbl_uint8 jbl_get_double_length(double tmp)
{
	jbl_uint8 len=1;
	len+=jbl_get_int64_length(tmp);
	if(tmp<0)
		tmp=-tmp;
	tmp-=(jbl_uint64)tmp;
	jbl_uint64 ji=10;
	for(double t=tmp*ji;t-(jbl_uint64)t<(-JBL_DOUBLE_PRECISION)||t-(jbl_uint64)t>(JBL_DOUBLE_PRECISION);ji=(ji<<3)+(ji<<1),t=tmp*ji);
	len+=jbl_get_uint64_length(tmp*ji);
	return len;
}
*/
#endif
