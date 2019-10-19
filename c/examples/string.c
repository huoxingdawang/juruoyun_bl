#include "main.h"

int main()
{
//jry_bl_string	
	printf("-------------------字符串部分-----------------------\n");
//三种初始化方式
	printf("-------------------三种初始化方式-------------------\n");
	jry_bl_string s1,s2;jry_bl_string_inits(2,&s1,&s2);jry_bl_string_views(stderr,2,&s1,&s2);
	jry_bl_string_add_char_pointer(&s1,"juruoyun");	jry_bl_string_view(&s1,stderr);
	jry_bl_string_add_char_pointer(&s2,"12345678");	jry_bl_string_view(&s2,stderr);
	jry_bl_string_add_string(&s1,&s2);				jry_bl_string_view(&s1,stderr);jry_bl_string_clears(2,&s1,&s2);
//	jry_bl_string_add_char(&s1,'a');				jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
//	jry_bl_string_add_unsigned_long_long(&s1,12356);jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
//	jry_bl_string_add_long_long(&s1,-12356);		jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
//	jry_bl_string_add_long_double(&s1,1.123);j		jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
//	jry_bl_string_add_long_double_len(&s1,1.12,100);jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_add_long_double_len(&s1,1.123,3);	jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_add_long_double_len(&s2,1.123,4);	jry_bl_string_view(&s2,stderr);jry_bl_string_clear(&s2);


	
	
	jry_bl_string_frees(2,&s1,&s2);
//输出、动态扩容、字符串拼接
/*	printf("-------------------输出、动态扩容、字符串拼接------\n");
	printf("-------------------逐个输出--------------------------\n");
	std::cout<<s3[1];
	std::cout<<s3[2];
	std::cout<<s3[3]<<std::endl;
	printf("-------------------一起输出--------------------------\n");
	std::cout<<s3<<std::endl;
	s2=s3;
	s1=(s3+=s3);
	printf("-------------------动态扩容--------------------------\n");
	s2.view();
	for(int i=0;i<10;i++,(s2+=s2));
	s2.view();
	s3.view();
	for(int i=0;i<1000;i++,(s3+="kuorong"));
	s3.view();
	s1.view();
	s1.free();s2.free();s3.free();
	s1.view();s2.view();s3.view();
*/
//数字拼接、字符串转数字
/*	printf("-------------------数字拼接、字符串转数字-----------\n");
	printf("-------------------拼接整数--------------------------\n");
	s1+=(123);std::cout<<s1<<std::endl;s1.free();
	printf("-------------------拼接小数--------------------------\n");
	s1+=(-123.4567891234);std::cout<<s1<<std::endl;
	printf("-------------------强转int---------------------------\n");
	std::cout<<s1.get_int()<<std::endl;
	printf("-------------------第二位开始强转int----------------\n");
	std::cout<<s1.get_int(2)<<std::endl;
	printf("-------------------强转float-------------------------\n");
	std::cout<<s1.get_float()<<std::endl;
	printf("-------------------第二位开始强转float--------------\n");
	std::cout<<s1.get_float(2)<<std::endl;
	s1.free();s2.free();s3.free();
*/
//浅拷贝
/*	printf("-------------------浅拷贝----------------------------\n");
	printf("-------------------原串s1----------------------------\n");
	s1="qiankaobei";
	s1.view();
	printf("-------------------s2<<s1----------------------------\n");s2<<s1;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();
	printf("-------------------s3<<s1----------------------------\n");s3<<s1;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();	
	printf("-------------------s3<<s2----------------------------\n");s3<<s2;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();	
	s1.free();s2.free();s3.free();	
	s1="qiankaobei";	
	printf("-------------------s1>>s2----------------------------\n");s1>>s2;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();	
	printf("-------------------s1>>s3----------------------------\n");s1>>s3;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();	
	printf("-------------------s2>>s3----------------------------\n");s2>>s3;
	printf("-------------------s1--------------------------------\n");s1.view();	
	printf("-------------------s2--------------------------------\n");s2.view();	
	printf("-------------------s3--------------------------------\n");s3.view();
	s1.free();s2.free();s3.free();
*/
//JSON
/*	s1="qiankaobei\"345435";
	s2<<s1.to_json();
	std::cout<<s2<<std::endl;
	s1.free();s2.free();s3.free();
	s1="\"qiankaobei345\\\"435\"";
	std::cout<<s1<<std::endl;
	s2.from_json(s1,0);
	std::cout<<s2<<std::endl;
	s1.free();s2.free();s3.free();	
*/
//比较
/*	printf("-------------------比较----------------------------\n");
	s1=123123;
	s2=123123;	
	std::cout<<s1<<"=="<<s2<<":"<<(s1==s2)<<std::endl;
	std::cout<<s1<<"< "<<s2<<":"<<(s1< s2)<<std::endl;
	std::cout<<s1<<"> "<<s2<<":"<<(s1> s2)<<std::endl;
	std::cout<<s1<<"!="<<s2<<":"<<(s1!=s2)<<std::endl;
	std::cout<<s1<<"<="<<s2<<":"<<(s1<=s2)<<std::endl;
	std::cout<<s1<<">="<<s2<<":"<<(s1>=s2)<<std::endl;
	std::cout<<std::endl;
	s1=123124;
	s2=123123;
	std::cout<<s1<<"=="<<s2<<":"<<(s1==s2)<<std::endl;
	std::cout<<s1<<"< "<<s2<<":"<<(s1< s2)<<std::endl;
	std::cout<<s1<<"> "<<s2<<":"<<(s1> s2)<<std::endl;
	std::cout<<s1<<"!="<<s2<<":"<<(s1!=s2)<<std::endl;
	std::cout<<s1<<"<="<<s2<<":"<<(s1<=s2)<<std::endl;
	std::cout<<s1<<">="<<s2<<":"<<(s1>=s2)<<std::endl;
	std::cout<<std::endl;
	s1=123123;
	s2=123124;
	std::cout<<s1<<"=="<<s2<<":"<<(s1==s2)<<std::endl;
	std::cout<<s1<<"< "<<s2<<":"<<(s1< s2)<<std::endl;
	std::cout<<s1<<"> "<<s2<<":"<<(s1> s2)<<std::endl;
	std::cout<<s1<<"!="<<s2<<":"<<(s1!=s2)<<std::endl;
	std::cout<<s1<<"<="<<s2<<":"<<(s1<=s2)<<std::endl;
	std::cout<<s1<<">="<<s2<<":"<<(s1>=s2)<<std::endl;
	std::cout<<std::endl;
	s1=123123;
	s2<<s1;
	std::cout<<s1<<"=="<<s2<<":"<<(s1==s2)<<std::endl;
	std::cout<<s1<<"< "<<s2<<":"<<(s1< s2)<<std::endl;
	std::cout<<s1<<"> "<<s2<<":"<<(s1> s2)<<std::endl;
	std::cout<<s1<<"!="<<s2<<":"<<(s1!=s2)<<std::endl;
	std::cout<<s1<<"<="<<s2<<":"<<(s1<=s2)<<std::endl;
	std::cout<<s1<<">="<<s2<<":"<<(s1>=s2)<<std::endl;
*/
			
	return 0;
}