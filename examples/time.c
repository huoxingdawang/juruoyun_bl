#include "main.h"
//TODO
#include <time.h>
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_time * t1=jbl_time_now(NULL);
	jbl_var  * v1=jbl_V(jbl_time_now(jbl_Vtime(jbl_Vtime_new())));
	
	jbl_string *s1=jbl_time_to_string_format(t1,NULL,UC 
		"%Y\t:Y\n"
		"%y\t:y\n"
		"%o\t:o\n"
		"%L\t:L\n"
		"\n"
		"%F\t:F\n"
		"%f\t:f\n"
		"%M\t:M\n"
		"%n\t:n\n"
		"%t\t:t\n"
		"\n"
		"%j\t:j\n"
		"%d\t:d\n"
		"%D\t:D\n"
		"%l\t:l\n"
		"%L\t:L\n"
		"%N\t:N\n"
		"%S\t:S\n"
		"%w\t:w\n"
		"%z\t:z\n"
		"\n"	
		"%a\t:a\n"
		"%A\t:A\n"
		"%B\t:B\n"
		"%g\t:g\n"
		"%G\t:G\n"
		"%h\t:h\n"
		"%H\t:H\n"
		"%i\t:i\n"
		"%s\t:s\n"
		"%u\t:u\n"
		"\n"
		"%e\t:e\n"
		"%I\t:I\n"
		"%O\t:O\n"
		"%P\t:P\n"
		"%T\t:T\n"
		"%Z\t:Z\n"
		"%c\t:c\n"
		"%r\t:r\n"
		"%U\t:U\n"
		"\n"	
	);
	
	jbl_string_view(s1);s1=jbl_string_free(s1);
	s1=jbl_time_to_string_format(t1,NULL,UC"%i%t %i%s %t%h%e jS %d%a%y.");
	jbl_string_view(s1);s1=jbl_string_free(s1);
	s1=jbl_time_to_string_format(t1,NULL,UC JBL_TIME_FORMAT_RFC1123);
	jbl_string_view(s1);s1=jbl_string_free(s1);
	
	
	jbl_time_view(t1);
	jbl_var_view(v1);
	
	jbl_time_json_put(t1,jbl_stream_stdout,1,1);pn();
		
	t1=jbl_time_free(t1);
	v1=jbl_var_free(v1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
