#include "main.h"
//TODO
int main()
{
#if JBL_BASE64_ENABLE==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	
	jbl_string *s1=jbl_string_new(),*s2=NULL,*s3=NULL;
	s1=jbl_string_add_chars(s1,UC"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	s2=jbl_base64_encode(s1,NULL);
	s3=jbl_base64_decode(s2,NULL);
	
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_string_view(s3);
#if JBL_STREAM_ENABLE==1
    jbl_string_free(jbl_refer(&s1));
    jbl_string_free(jbl_refer(&s2));
	jbl_stream *ss1=jbl_string_stream_new(s1);
	jbl_stream *ss2=jbl_string_stream_new(s2);
	jbl_stream *b64en=jbl_stream_base64_encode_new();
	jbl_stream *b64de=jbl_stream_base64_decode_new();
		
	jbl_stream_connect(ss1,b64en);
	jbl_stream_connect(b64en,(jbl_stream_stdout));
	jbl_stream_do(ss1,true);
	pn();
	jbl_stream_connect(ss2,b64de);
	jbl_stream_connect(b64de,(jbl_stream_stdout));
	jbl_stream_do(ss2,true);
	pn();

	ss1=jbl_stream_free(ss1);	
	ss2=jbl_stream_free(ss2);	
	b64en=jbl_stream_free(b64en);	
	b64de=jbl_stream_free(b64de);
#endif	
	s1=jbl_string_free(s1);s2=jbl_string_free(s2);s3=jbl_string_free(s3);

	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
#endif
}