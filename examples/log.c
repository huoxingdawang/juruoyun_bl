#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_string * s1=jbl_string_add_const(NULL,UC "jbl_string test");
	jbl_log(UC "test %d%d%d %s %X %c juruoyun %v",1,123,456,"123123123121",0XFE,'a',jbl_gc_minus(jbl_string_copy_as_var(s1)));
	s1=jbl_string_free(s1);
	
	jbl_log_save();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}