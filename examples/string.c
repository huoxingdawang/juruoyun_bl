#include "main.h"
#include <time.h>

int main()
{
	printf("\n--------------------------------" __FILE__ "--------------------------------\n");
	printf("jry_bl_string size:%lld\n",(long long)(sizeof (jry_bl_string)));	
	jry_bl_start();

	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL;
	s1=jry_bl_string_add_chars(s1,"-123");
//	jry_bl_gc_view(s1);
	jry_bl_string_view(s1);
	s2=jry_bl_string_copy(s1);
//	jry_bl_gc_view(s1);
	jry_bl_string_view(s2);
	printf("Space ship test:%d\n",jry_bl_string_space_ship(s1,s2));
	s1=jry_bl_string_add_chars(s1,"456");
	printf("Space ship test:%d\n",jry_bl_string_space_ship(s1,s2));
	s3=jry_bl_string_add_double(jry_bl_string_add_string(jry_bl_string_add_chars(jry_bl_string_copy(s1)," 0000 "),s2),-89789.1234);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_unicode_as_utf8(jry_bl_string_add_unicode_as_utf8(jry_bl_string_add_unicode_as_utf8(s3,0X849f),0X84BB),0X4E91);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_hex(s3,0XEFFFFF);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_hex_8bits(s3,0XF);
	
//	jry_bl_gc_view(s1);
//	jry_bl_gc_view(s2);
	jry_bl_string_view(s1);
	jry_bl_string_view(s2);
	jry_bl_string_view(s3);
	
	jry_bl_stream_push_uint64(sout,jry_bl_string_get_uint64(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_push_int64(sout,jry_bl_string_get_int64(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_push_double(sout,jry_bl_string_get_double(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_do(sout,jry_bl_stream_force);
	
	
	
	
	
exit:	
	s1=jry_bl_string_free(s1);s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);

	jry_bl_stop();
	return 0;
}