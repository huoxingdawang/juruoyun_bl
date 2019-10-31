/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_MALLOC_H
#define __JRY_BL_MALLOC_H
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
void* jry_bl_malloc(size_t size);
void* jry_bl_realloc(void* ptr,size_t size);
void* jry_bl_free(void * p);
size_t jry_bl_malloc_size(void* ptr);
#endif