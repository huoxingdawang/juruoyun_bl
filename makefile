#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
CC = gcc
EX = -m64
EXLIB = $(JRY_BL_EXLIB)
ifeq ($(shell uname),Linux)
	H = /
	rm = rm -f
else
	H = \\
	rm = del
endif
all:jry_bl aes array base64 bitset cmd file json hash_table link_list malloc md5 rand stream string time sha1 test var
clean:
	$(rm) tmp$(H)*.o /s
	$(rm) tmp$(H)*.a /s
	$(rm) exes$(H)* /s /Q
	$(rm) testfiles$(H)*.out /s
	$(rm) testfiles$(H)*.ans /s
	$(rm) testfiles$(H)*.html /s
init:
	mkdir tmp
	mkdir exes
run:
	exes$(H)string
	exes$(H)aes
#	exes$(H)array
	exes$(H)base64
	exes$(H)bitset
	exes$(H)cmd
	exes$(H)file
	exes$(H)json
	exes$(H)hash_table
	exes$(H)link_list
	exes$(H)malloc
	exes$(H)rand
	exes$(H)md5
	exes$(H)stream
	exes$(H)sha1
	exes$(H)time
	exes$(H)test
	exes$(H)var
#examples
aes:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)aes.o examples$(H)aes.c $(EXLIB)
	$(CC) -o exes$(H)aes tmp$(H)aes.o tmp$(H)jry_bl.a
array:jry_bl
#	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)array.o examples$(H)array.c $(EXLIB)
#	$(CC) -o exes$(H)array tmp$(H)array.o tmp$(H)jry_bl.a
base64:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)base64.o examples$(H)base64.c $(EXLIB)
	$(CC) -o exes$(H)base64 tmp$(H)base64.o tmp$(H)jry_bl.a
bitset:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)bitset.o examples$(H)bitset.c $(EXLIB)
	$(CC) -o exes$(H)bitset tmp$(H)bitset.o tmp$(H)jry_bl.a
cmd:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)cmd.o examples$(H)cmd.c $(EXLIB)
	$(CC) -o exes$(H)cmd tmp$(H)cmd.o tmp$(H)jry_bl.a	
file:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)file.o examples$(H)file.c $(EXLIB)
	$(CC) -o exes$(H)file tmp$(H)file.o tmp$(H)jry_bl.a
json:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)json.o examples$(H)json.c	$(EXLIB)
	$(CC) -o exes$(H)json tmp$(H)json.o tmp$(H)jry_bl.a
hash_table:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)hash_table.o examples$(H)hash_table.c $(EXLIB)
	$(CC) -o exes$(H)hash_table tmp$(H)hash_table.o tmp$(H)jry_bl.a	
link_list:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)link_list.o examples$(H)link_list.c $(EXLIB)
	$(CC) -o exes$(H)link_list tmp$(H)link_list.o tmp$(H)jry_bl.a
malloc:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)malloc.o examples$(H)malloc.c $(EXLIB)
	$(CC) -o exes$(H)malloc tmp$(H)malloc.o tmp$(H)jry_bl.a
md5:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)md5.o examples$(H)md5.c $(EXLIB)
	$(CC) -o exes$(H)md5 tmp$(H)md5.o tmp$(H)jry_bl.a
rand:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)rand.o examples$(H)rand.c $(EXLIB)
	$(CC) -o exes$(H)rand tmp$(H)rand.o tmp$(H)jry_bl.a	
stream:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)stream.o examples$(H)stream.c $(EXLIB)
	$(CC) -o exes$(H)stream tmp$(H)stream.o tmp$(H)jry_bl.a
string:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)string.o examples$(H)string.c $(EXLIB)
	$(CC) -o exes$(H)string tmp$(H)string.o tmp$(H)jry_bl.a
sha1:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)sha1.o examples$(H)sha1.c $(EXLIB)
	$(CC) -o exes$(H)sha1 tmp$(H)sha1.o tmp$(H)jry_bl.a
time:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)time.o examples$(H)time.c $(EXLIB)
	$(CC) -o exes$(H)time tmp$(H)time.o tmp$(H)jry_bl.a
test:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)test.o examples$(H)test.c $(EXLIB)
	$(CC) -o exes$(H)test tmp$(H)test.o tmp$(H)jry_bl.a
var:jry_bl
	$(CC) $(EX) -c -std=gnu99 -o tmp$(H)var.o examples$(H)var.c $(EXLIB)
	$(CC) -o exes$(H)var tmp$(H)var.o tmp$(H)jry_bl.a
#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
#jry_bl
ifeq ($(shell uname),Linux)
JRY_BL_EXLIB = 
else
JRY_BL_EXLIB = 
endif
jry_bl                       :jry_bl/jry_bl_aes jry_bl/jry_bl_array jry_bl/jry_bl_base64 jry_bl/jry_bl_bitset jry_bl/jry_bl_cmd jry_bl/jry_bl_exception jry_bl/jry_bl_file jry_bl/jry_bl_gc jry_bl/jry_bl_hash_table jry_bl/jry_bl_link_list jry_bl/jry_bl_malloc jry_bl/jry_bl_md5 jry_bl/jry_bl_rand jry_bl/jry_bl_sha1 jry_bl/jry_bl_stream jry_bl/jry_bl_string jry_bl/jry_bl_time jry_bl/jry_bl_var jry_bl/jry_bl_ying 
	ar rc tmp$(H)jry_bl.a tmp$(H)jry_bl_*.o
jry_bl/jry_bl_aes            :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_aes.o        jry_bl$(H)jry_bl_aes.c        $(JRY_BL_EXLIB)
jry_bl/jry_bl_array          :
	$(CC) $(EX) -c       -std=gnu99 -o tmp$(H)jry_bl_array.o      jry_bl$(H)jry_bl_array.c      $(JRY_BL_EXLIB)
jry_bl/jry_bl_base64         :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_base64.o     jry_bl$(H)jry_bl_base64.c     $(JRY_BL_EXLIB)
jry_bl/jry_bl_bitset         :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_bitset.o     jry_bl$(H)jry_bl_bitset.c     $(JRY_BL_EXLIB)
jry_bl/jry_bl_cmd            :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_cmd.o        jry_bl$(H)jry_bl_cmd.c        $(JRY_BL_EXLIB)
jry_bl/jry_bl_exception      :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_exception.o  jry_bl$(H)jry_bl_exception.c  $(JRY_BL_EXLIB)
jry_bl/jry_bl_file           :
	$(CC) $(EX) -c       -std=gnu99 -o tmp$(H)jry_bl_file.o       jry_bl$(H)jry_bl_file.c       $(JRY_BL_EXLIB)
jry_bl/jry_bl_gc             :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_gc.o         jry_bl$(H)jry_bl_gc.c         $(JRY_BL_EXLIB)
jry_bl/jry_bl_hash_table     :
	$(CC) $(EX) -c       -std=gnu99 -o tmp$(H)jry_bl_hash_table.o jry_bl$(H)jry_bl_hash_table.c $(JRY_BL_EXLIB)
jry_bl/jry_bl_link_list      :
	$(CC) $(EX) -c       -std=gnu99 -o tmp$(H)jry_bl_link_list.o  jry_bl$(H)jry_bl_link_list.c  $(JRY_BL_EXLIB)
jry_bl/jry_bl_malloc         :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_malloc.o     jry_bl$(H)jry_bl_malloc.c     $(JRY_BL_EXLIB)
jry_bl/jry_bl_md5            :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_md5.o        jry_bl$(H)jry_bl_md5.c        $(JRY_BL_EXLIB)
jry_bl/jry_bl_rand           :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_rand.o       jry_bl$(H)jry_bl_rand.c       $(JRY_BL_EXLIB)
jry_bl/jry_bl_sha1           :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_sha1.o       jry_bl$(H)jry_bl_sha1.c       $(JRY_BL_EXLIB)    
jry_bl/jry_bl_stream         :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_stream.o     jry_bl$(H)jry_bl_stream.c     $(JRY_BL_EXLIB)
jry_bl/jry_bl_string         :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_string.o     jry_bl$(H)jry_bl_string.c     $(JRY_BL_EXLIB)
jry_bl/jry_bl_time           :
	$(CC) $(EX) -c       -std=gnu99 -o tmp$(H)jry_bl_time.o       jry_bl$(H)jry_bl_time.c       $(JRY_BL_EXLIB)
jry_bl/jry_bl_var            :
	$(CC) $(EX) -c -w    -std=gnu99 -o tmp$(H)jry_bl_var.o        jry_bl$(H)jry_bl_var.c        $(JRY_BL_EXLIB)
jry_bl/jry_bl_ying           :
	$(CC) $(EX) -c -Wall -std=gnu99 -o tmp$(H)jry_bl_ying.o       jry_bl$(H)jry_bl_ying.c       $(JRY_BL_EXLIB)