#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	printf("Pointer size:%lld\n",(long long)(sizeof (char *)));
	printf("jry_bl_var_fs size:%lld\n",(long long)(sizeof (jry_bl_var_fs)));
	printf("jry_bl_var_functions size:%lld\n",(long long)(sizeof (jry_bl_var_functions)));
	printf("jry_bl_var_tmp_functions size:%lld\n",(long long)(sizeof (jry_bl_var_tmp_functions)));
	printf("jry_bl_var_functions_struct size:%lld\n",(long long)(sizeof (jry_bl_var_functions_struct)));
//	jry_bl_var_tmp_register(0,10,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		
	jry_bl_var va,vb,vc;jry_bl_var_inits(3,&va,&vb,&vc);
	jry_bl_string sa,sb,sc,sd;jry_bl_string_inits(4,&sa,&sb,&sc,&sd);
	int a=0;

	jry_bl_string_equal_char_pointer(&sa,"juruoyun");
	jry_bl_var_equal_string(&va,&sa,copy);
	jry_bl_var_equal_string(&vb,&sa,light);
	jry_bl_var_equal_string(&vc,&sa,move);
		
	jry_bl_string_view(jry_bl_var_get_string(&va));
	jry_bl_string_view(jry_bl_var_get_string(&vb));
	jry_bl_string_view(jry_bl_var_get_string(&vc));
	jry_bl_var_views(3,&va,&vb,&vc);
	jry_bl_var_equal_int64(&va,1234234);
	jry_bl_var_equal_double(&vb,2.2222);
	jry_bl_var_equal_pointer(&vc,&a);
	jry_bl_var_views(3,&va,&vb,&vc);

	jry_bl_var_equal_double(&va,1234234.123);
	jry_bl_string_clear(&sa);
	jry_bl_var_to_json(&va,&sa);
	jry_bl_string_view(&sa);
	
	jry_bl_var_from_json(&va,&sa);
	jry_bl_var_view(&va);
	
	jry_bl_var_frees(3,&va,&vb,&vc);
	jry_bl_string_frees(4,&sa,&sb,&sc,&sd);

	jry_bl_var_equal_double(&va,234234.123);
	jry_bl_var_equal_double(&vb,4234.123);
	printf("Space ship test:%d\n",jry_bl_var_space_ship(&va,&vb));	
	
/*
*/	
exit:
	jry_bl_string_frees(4,&sa,&sb,&sc,&sd);
	jry_bl_var_frees(3,&va,&vb,&vc);
	jry_bl_stop();
	return 0;
}