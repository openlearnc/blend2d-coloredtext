#include "regex.h"
#define PCRE2_CODE_UNIT_WIDTH 8
#include "pcre2.h"

vector<colortext> stdd(char *str)
{
	vector<colortext> text;
   char*p ="\/\/(.*)";      //
   char*p1= "\\/\\*[\w\W]*?\\*\\/";
   char*p2 = "\\/\\*(?:\\*(?!\\/)|[^\\*])*\\*\\/";
   char*p3 = "\\/\\*(?:[^\\*]|\\*+[^\\/\\*])*\\*+\\/|\\/\\/(.*)";
   char*p4 = "\'(\\\\.|.)*?\'"; //''
   char*p5 = "\#(.*)";
PCRE2_SPTR pattern =(PCRE2_SPTR)"\\/\\*(?:[^\\*]|\\*+[^\\/\\*])*\\*+\\/|\\/\\/(.*)|\#(.*)|\"(\\\\.|.)*?\"|\'(\\\\.|.)*?\'|\\bint\\b|\\bchar\\b|\\breturn\\b|\\bif\\b|\\belse\\b";

 PCRE2_SPTR pattern1 = (PCRE2_SPTR)p1;
	// 定义输入字符串
	PCRE2_SPTR input = (PCRE2_SPTR)str;
	//" hellp hello hello world,你PCRE2!\nfffghgcgghh你hhelli gghhvvvvh\n";

	pcre2_code *re;
	pcre2_code*re1;
	int errorcode,errorcode1;
	PCRE2_SIZE erroroffset,erroroffset1;
	//PCRE2_UCHAR buffer[256];
	pcre2_match_data *match_data;
    pcre2_match_data*match_data1;
	// 编译正则表达式
	re = pcre2_compile(pattern,				  // 匹配模式(正则表达式)
					   PCRE2_ZERO_TERMINATED, // 模式长度(以'\0'结尾)
					   0,					  // 选项
					   &errorcode,			  // 错误代码
					   &erroroffset,		  // 错误偏移量
					   NULL					  // 上下文，一般取NULL
	);
	re1 = pcre2_compile(pattern1,PCRE2_ZERO_TERMINATED,0,&errorcode1,&erroroffset1,NULL);
	/*	if (re == NULL)
	{
		pcre2_get_error_message(errorcode, buffer, sizeof(buffer));
		printf("PCRE2 compilation failed at offset %d: %s\n",
			   (int)erroroffset, buffer);
		exit(EXIT_FAILURE);
	}
*/
	// 构造匹配寄存器以记录匹配结果
	match_data = pcre2_match_data_create_from_pattern(re, NULL);
    match_data1 = pcre2_match_data_create_from_pattern(re1,NULL);
	PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
   
	BLRgba32 color = BLRgba32(255, 0, 120, 255);
	int offset = 0;
	int range;
	clock_t t = clock( );
	vector<int>sortrange;
	while (input[offset] != '\0')
	{
		if (pcre2_match(re, input, PCRE2_ZERO_TERMINATED,
						offset, 0, match_data, NULL) > 0)
		{
			//input += ovector[1];
		   if(input[(int)ovector[0]]=='/'){
		  text.push_back({(int)ovector[0],(int)(ovector[1]-ovector[0]), {0,126,0,255}});
			offset = ovector[1];
	          continue;
		   
		   }
		   if(input[(int)ovector[0]]=='\"'||input[(int)ovector[0]]=='\''){
		  text.push_back({(int)ovector[0],(int)(ovector[1]-ovector[0]), {0,0,255,255}});
			offset = ovector[1];
	          continue;
		   
		   }
		   if(input[(int)ovector[0]]=='#'){
		  text.push_back({(int)ovector[0],(int)(ovector[1]-ovector[0]), {255,0,0,255}});
			offset = ovector[1];
	          continue;
		   
		   }
            range = (int)(ovector[1]-ovector[0]);
			text.push_back({(int)ovector[0],range, color});
			//offset += (ovector[1] - ovector[0]);             
			offset = ovector[1];
			printf("offset%d\n",ovector[1]);
		
		}
		else
		{
			// input ++;
			//offset ++;
           text.push_back({0,0,{0,0,0,0}});
			break;
		}
	}

 	printf("time %ld\n",clock()-t);
		
pcre2_match_data_free(match_data);
	pcre2_code_free(re);
        return text;
}
