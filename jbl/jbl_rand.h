/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_RAND_H
#define __JBL_RAND_H
#include "jbl_rand_config.h"
#if JBL_RAND_ENABLE==1
void			jbl_rand_srand			(jbl_uint32 seed);
jbl_uint32		jbl_rand				();
jbl_uint32 		jbl_rand_between		(jbl_uint32 a,jbl_uint32 b);

#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
jbl_string *	jbl_rand_string			(jbl_string *this,jbl_string_size_type len,char* s);
#define			jbl_rand_dict_small		"abcdefghijklmnopqrstuvwxyz"
#define			jbl_rand_dict_big		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define			jbl_rand_dict_number	"0123456789"
#define			jbl_rand_dict_symbol	"~!@#$%^&*()_+=-`{}|[]\\:\";'<>?,./"
#endif

#endif
#endif
