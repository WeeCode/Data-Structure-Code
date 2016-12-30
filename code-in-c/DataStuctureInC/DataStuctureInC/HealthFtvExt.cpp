/*
//文件名称：HealthFtvExt.cpp
//文件标识：
//摘    要：健康指数特征提取
//运行平台：linux/winxp
//
//版    本：1.00
//作    者：周浩
//日    期：2016年8月15日
//说    明：
//
//版    本：1.10
//作    者：潘成龙
//日    期：2016年9月13日
//说    明：增加：1、进给轴特征提取
//                2、主轴特征提取
//                3、健康指数计算
*/

//win7 64位系统、6G内存，跑完健康指数约81.78秒

/*    20160918集成测试修改：
（1）预编译：增加#include "stdafx.h"，注释//#include <stdio.h>；
（2）头文件：增加extern int HealIdexTest()等函数声明；
（3）路径分隔符修改，不判断是否linux环境，#define DIR_SEPARATOR '\\'；
（4）文件路径修改，HEALTHPATH；
（5）函数int HealIdexTest()增加内容，进行测试；
（6）函数int ReadGFile_Feed(FILE* pfile)修改，关于G代码宏的约定；
（7）函数int ReadGFile_Spd(FILE* pfile)修改，关于G代码宏的约定；
（8）函数int ReadGFile_Feed(FILE* pfile)修正，各模式计数与行号存入顺序颠倒；posLowNum++;
（9）函数int ReadGFile_Spd(FILE* pfile)修正，各模式计数与行号存入顺序颠倒；
（10）函数int ParseR116()修正，寄存器点位文件打开方式"rb" -> "wb"->"wb+"
（11）结构体HealthFtvPar增加基准文件名stdfilename
（12）函数int read_std_file()修正，有关打开文件名
（13）函数void initparam(char* fname, int chnnum)增加，基准文件名初始化
（14）宏定义，增加SAMPDATA_OFFSET，采样数据的初始偏移量
（15）(错误改回)所有函数中读采样文件s_hfp.pdatafile数据fseek()修正，SEEK_SET -> SAMPDATA_OFFSET (error)
（16）所有函数中读采样文件s_hfp.pdatafile数据fseek()修正，第二参数offset增加初始偏移量SAMPDATA_OFFSET 
（17）函数int ParseR116()修正, 解析的中间文件统一存入float型数据 int ->float
（18）函数int ParseR116()增加，文件写入后对文件缓冲区的处理fflush()
（19）宏定义增加，判断浮点数相等的精度阈值 
（20）函数void initparam(char* fname, int chnnum)修正，采样点数计算考虑第一个数存通道个数的影响
（21）函数int find_emtoid（）修正，形参关于精度的默认值；下降沿处的文件流、相等判断、索引加一；
（22）函数int ToolFtvExt()修正，中间文件打开方式 “wb”->"wb+"
（23）函数int ToolFtvExt()修正，选刀开始到结束的索引，for循环 -> 调用函数
（24）函数compute_statis_file()修正，求方差时出现负数开方情况，精度误差导致，float -> double
（25）函数compute_statis_array()修正，提高计算精度，float -> double
（26）函数int ToolFtvExt()修正，Z轴电流中间文件，fopen()参数错误，sfname->zfname
（27）函数Dece_Segmt_Idx()修正，寻找减速段终点，应从开始减速算起
（28）宏定义，主轴高低速允许误差 HIGHSPDERR，LOWSPDERR： 10,30-> 20,40
（29）函数SigSpd_AcDc_Ext()修正，提取恒速段索引时，参数错误： dece_idx ->consSped_idx
（30）函数SigSpd_AcDc_Ext()增加，增加主轴正反转的判断，反转转速为负
（31）函数修正，所有malloc()函数增加判断，失败返回-5；
（32）函数int ReadGFile_Spd(FILE* pfile)增加，提取主轴高低速转速；
（33）函数ReadGFile_MO6()修正，换到所在行判断 M06 -> T
（34）函数ReadGFile_Feed()修正，解析G代码根据G代码宏定义的约定，提高可移植性
（35）函数ReadGFile_Spd()修正，解析G代码根据G代码宏定义的约定，提高可移植性
（36）增加向量归一化、计算健康指数功能
（37）函数ToolFtvExt()增加，关闭并删除中间文件
（38）增加函数HealthTestCalExit()，健康诊断计算模块退出处理
（39）函数ExtrPoint()修正，极值索引idx+1 ->idx-1
（40）函数ToolFtvExt()增加，增加冲洗中间文件缓冲区fflush()
（41）函数ExtrPoint()修改，形参增加用于返回的极大值个数、极小值个数，调用函数处对应修改
（42）函数ToolFtvExt()修改，计算选刀时间时+1
（43）函数ToolFtvExt()修改，计算电流方差最大值修正，std_tmp[3] -> std_tmp[1]
（44）增加异常处理机制，长跳转setjmp()-longjmp()实现
（45）增加宏定义，对常见错误与异常编号errNO
-------------------------------[加入hnc8后]--------------------------------------------
（46）函数CalHealthIndex()增加，增加计算机床健康指数
（47）函数HealIdexTestCal()修改，形参增加 采样数据文件名、健康指数
（48）函数vector_normal()修改，增加除零判断
（49）结构体HealthFtvPar增加，增加基准文件的文件指针pstdfile、历史诊断次数historyTestNum
（50）函数read_std_file()修改，基准向量的文件指针改为s_hfp中的基准文件指针、删除关闭基准文件
（51）函数read_std_file()增加，增加读取历史诊断次数historyTestNum
*/

/*//待修改
(1)(完成)函数int ReadGFile_Spd(FILE* pfile)增加，提取主轴高低速转速；
(2)(暂时不改动)主轴转速改为float型
(3)(完成)读G代码修改为宏定义形式
(4)(完成)基准文件"standard_file.bin"更新重做；
(5)(完成)采样数据文件.SV 第一个数据为通道个数，未考虑  =》增加初始偏移量
(6)(完成)采样数据文件.SV 电流存在1000的倍数关系（mA -> A）;与浩哥商量修改
(7)(暂时改为27000)宏定义IIP_NUM个数太少，换刀17000索引左右，低速进给27000左右 如何修改  
(8)(完成)计算用的中间文件未关闭时，数据有部分在文件缓冲区，需要关闭文件或者清除文件缓冲区
(9)(完成)R116的寄存器中间文件int型，找元素时float型，如何统一
(10)(完成)对特征向量的归一化处理、计算健康指数
(11)(完成)特征值存入、基准自动生成更新
(12)(初步完成)异常处理机制完善
(13)(完成)电流波动极值计数对波动值影响较大
--->(14)进给轴特征提取时未考虑加减速过程，对恒速段有影响
 */
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include <setjmp.h>
//#include "hncdatatype.h"
#include "HealthFtvExt.h"
#include "hncsysctrl.h"
#include "ncsize808.h"  //debug
#include "ncstring.h"


// 路径分隔符
//#define DIR_SEPARATOR '\\'
#ifdef _LINUX
#define DIR_SEPARATOR '/'
// #define HEALTHPATH	"../tmp"	//特征分析时产生的中间文件(直接写路径第一个\作为特殊字符处理了)
// #define GFILEPATH   "../prog"              //G代码路径
#else
#define DIR_SEPARATOR '\\'
// #define HEALTHPATH			"..\\tmp"	//特征分析时产生的中间文件(直接写路径第一个\作为特殊字符处理了)
// #define GFILEPATH           "..\\prog"              //G代码路径
#endif

//G代码宏定义的约定
#define X_NEG_LIMIT   "#101"      //X轴负限位
#define X_POS_LIMIT   "#102"       
#define Y_NEG_LIMIT   "#103"      
#define Y_POS_LIMIT   "#104"
#define Z_NEG_LIMIT   "#105"
#define Z_POS_LIMIT   "#106"
#define SPD_LOW_SPED  "#107"      //主轴低速度
#define SPD_HIGH_SPED "#108"  
#define FED_LOW_SPED  "#109"      //三轴联动直线插补 进给轴低速度（合成速度）
#define FED_HIGH_SPED "#110"
#define XOY_FED_LOW_SPED  "#111"    //XOY平面画圆 进给轴低速度（合成速度）
#define XOY_FED_HIGH_SPED  "#112"

#define HEALTHGCOD			"OHealthTest.txt"		//铁人三项G代码文件名		
#define STD_VET_FNAME		"standard_file.SV"		//基准文件 
#define R1161				"R116_1.bin"			//R116解析文件
#define R1164				"R116_4.bin"
#define R1166				"R116_6.bin"
#define R1167				"R116_7.bin"
#define TOOLTIME			50						//最大换刀次数
#define FEEDTIME            3                       //某特征（如高速正向）的最大进给次数（高低速、正反向*4）
#define SPDTIME             5                       //某特征（如高速正转）的最大主轴起停次数（高低速、正反转*4）
#define HIGHSPDERR          40                      //主轴高速允许转速误差
#define LOWSPDERR           20                      //主轴低速允许转速误差
#define FLOAT_EQUAL         0.01                //判断浮点数相等的精度阈值
#define RESET_STD_TIMES     30                  //运行30次后重新设置基准

#define	EUNIT				sizeof(float)			//二进制文件基本内存单元
#define IIP_NUM				27000 //10000					//行最大插补点数?? @@@@@@@@@@周会成老师

#define SAMPDATA_OFFSET     (1*sizeof(long int))    //采样文件数据中非通道数据（通道数）导致的偏移量

#define max(a,b)    (((a) > (b)) ? (a) : (b))       //最大值函数
#define min(a,b)    (((a) < (b)) ? (a) : (b))       //最小值函数

#define TRY      if(!(s_ErrNo = setjmp(s_SetJmp)))              //用长跳转进行异常处理         
#define CATCH    else                               //用长跳转进行异常处理

//常见异常
#define MALLOCERR      -5          //malloc分配内存出错
#define OPENFILEERR    -6          //文件打开失败
#define NULL_POINTER   -7          //空指针


////////////////////////////////////////////////////////////////////////////////
//            
//
//    备注: 标记采样顺序，如果通道采样顺序发生变化，只需要修改枚举变量对应的值
//               
//
////////////////////////////////////////////////////////////////////////////////
typedef enum _healthsmptype
{
// 	AXIS_CMD_X=0,
// 	AXIS_ACT_X=1,
// 	CUR_ACT_X=2,
// 	AXIS_CMD_Y=3,
// 	AXIS_ACT_Y=4,
// 	CUR_ACT_Y=5,
// 	AXIS_CMD_Z=6,
// 	AXIS_ACT_Z=7,
// 	CUR_ACT_Z=8,
// 	VEL_SPIND=9,
// 	CUR_SPIND=10,
// 	GODE_ROW=11,
// 	R116=12,
// 	CHN_COUNT = 16
	GODE_ROW = 0,
	R116 = 1,
	CUR_SPIND = 2,
	VEL_SPIND = 3,
	AXIS_CMD_X = 4,
	AXIS_CMD_Y = 5,
	AXIS_CMD_Z = 6,
	AXIS_ACT_X = 7,
	AXIS_ACT_Y = 8,
	AXIS_ACT_Z = 9,
	CUR_ACT_X = 10,
	CUR_ACT_Y = 11,
	CUR_ACT_Z = 12,
	CHN_COUNT = 16,
}HealSpTy;

typedef enum _edge
{
	SIG,		//某个元素
	EUP,		//上升沿
	EDN,		//下降沿
}EDGE;

typedef struct _HealthFtvPar
{
	int TotalData;			//单通道采样数据总数
	int  chn_num;			//采样通道数目
	int historyTestNum;     //历史诊断次数  correct:add

	//文件
	char filename[128];			//采样数据文件名
	FILE* pdatafile;           //采样数据文件指针
	char stdfilename[128];		 //基准文件名  //correct
	FILE* pstdfile;              //基准数据文件指针
	char gcodefile[128];		//G代码文件名

	//Gcoderow
	char GcoderowFilename[128];
	FILE* pGcoderow; //int型
	
	//tool feature 
	char toolfile[4][128];		//R116_1;R116_4;R116_6;R116_7;
	FILE* ptoolfile[4];
	int toolchgnum;				//换刀数行
	int toolrow[TOOLTIME];		//换刀行号：最大换刀次数100

	//feed feature
    int feednum;                 //插补次数feednum=正向低速=反向低速=正向高速=反向高速次数（G代码保证一致）
	int feedrow[4][FEEDTIME];    //插补行号，[0][]:低速正向，[1][]:低速反向，[2][]:高速正向，[3][]:高速反向

    //Spindle feature
	int spd_highSped;            //主轴高速转速
	int spd_lowSped;             //主轴低速转速
	int spdnum;                  //起停次数 = 正转低速=反转低速=正转高速=反转高速次数（不一致时取最多的次数）
	int spdrow[4][SPDTIME][2];   //主轴起停行号，第一维：[0]:低速正向，[1]:低速反向，[2]:高速正向，[3]:高速反向
	                             //              第二维：各第一维模式的起停次数
	                             //              第三维：[0]:开始旋转行号（M03、M04）,[1]:停止行号（M05下一行的G04）
    //计算基准向量
	FeatVec feat_base;
	FeatVec feat_min;
	FeatVec feat_max;
} HealthFtvPar;

static HealthFtvPar s_hfp;							//特征提取参数
static FeatVec		s_ftv;							//特征向量
static float  s_samplFreq = 1000.0;                 //采样频率
static jmp_buf s_SetJmp;                            //长跳转buff
static int  s_ErrNo;                                //异常（错误）编号 

//计算步骤编号（正数为正常步骤，负数为异常步骤）
static int s_CalThreadStep_No = 0; 
static int s_CalThreadErr_No = 0; 
//是否记录计算过程信息标志
static bool s_Print_CalStep_Flag = true;     //记录计算步骤
static bool s_Print_CalDataInlo_Flag = true; //记录计算过程数据信息

static FILE* s_debug_pfile = NULL; //记录计算过程数据信息文件指针

//----------------------------------------------//

/////////////////////////////////////////////////////////////////////////
//
//    int HealIdexTestCal(float* healthIndex)
//
//    功能：
//           健康诊断计算模块
//
//    参数：
//           healthIndex: 健康指数计算结果，依次为：X轴、Y轴、Z轴、主轴、刀库、机床  
//           sampDatFile: 采样文件名（不带路径）
//           chunNum:     采样通道数
//    描述：
//                     
//
//    返回：
//           MALLOCERR(-5)    :malloc()异常
//           OPENFILEERR(-6)  :文件打开出错
//           NULL_POINTER(-7) :空指针
//           -1               :其它错误    
//
//////////////////////////////////////////////////////////////////////////
int HealIdexTestCal(float* healthIndex,char* sampDatFile,int chunNum)
{
	int ret = 0;

	CalThread_StepPrint_Refresh(true);
	if(s_Print_CalDataInlo_Flag) 
		CalThread_debug_init();
//	debug_open_simpleFile();
	TRY{
		//(1)参数初始化
		ret = initparam(sampDatFile,chunNum);
		if (ret == 0)
		{
			CalThread_Step_Set(1);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-1
		}
		
		 //(2)读、解析G代码文件
  		ret = ReadGFile();                    
		if (ret == 0)
		{
			CalThread_Step_Set(2);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-2~-5
		}

		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"换刀次数：%d\r\n",s_hfp.toolchgnum);
			fprintf(s_debug_pfile,"第一个换刀行号：%d\r\n",s_hfp.toolrow[0]);
			fprintf(s_debug_pfile,"最后一个换刀行号：%d\r\n",s_hfp.toolrow[s_hfp.toolchgnum -1]);
		}

		//(3)读采样数据文件
   		ret = ReadSampFile();                  
		if (ret == 0)
		{
			CalThread_Step_Set(3);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-6
		}

		//Gcoderow
		ParseGcodeRow();
		
		//(4)解析R116寄存器信号
   		ret = ParseR116();                     
		if (ret == 0)
		{
			CalThread_Step_Set(4);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-7~-9
		}

		//(5)读、解析基准文件
   		ret = read_std_file();                 
		if (ret == 0)
		{
			CalThread_Step_Set(5);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-10~-11
		}
        
		//(6)刀库特征提取
		ret = ToolFtvExt();
		if (ret == 0)
		{
			CalThread_Step_Set(6);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-12~-13
		}

		//(7)主轴特征提取
		//SpdFtvExt();
		ret = SpdFtvExt_02();
		if (ret == 0)
		{
			CalThread_Step_Set(7);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-14
		}

		//(8)进给轴（X/Y/Z）特征提取
		ret = FeedFtvExt();
		if (ret == 0)
		{
			CalThread_Step_Set(8);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-15~-17
		}

		//Gcoderow
		GcoderowExit();
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile," 主轴特征:(1)加速时间：%f (2)减速时间：%f (3)电流均值：%f (4)电流波动：%f \r\n",s_ftv.s_health[0],s_ftv.s_health[1],s_ftv.s_health[2],s_ftv.s_health[3]);
			fprintf(s_debug_pfile," X轴特征:(1)低速均值：%f (2)低速波动%f (3)高速均值%f (4)高速波动：%f (5)跟随误差：%f (6)回程误差：%f \r\n",s_ftv.x_health[0],s_ftv.x_health[1],s_ftv.x_health[2],s_ftv.x_health[3],s_ftv.x_health[4],s_ftv.x_health[5]);
			fprintf(s_debug_pfile," Y轴特征:(1)低速均值：%f (2)低速波动%f (3)高速均值%f (4)高速波动：%f (5)跟随误差：%f (6)回程误差：%f \r\n",s_ftv.y_health[0],s_ftv.y_health[1],s_ftv.y_health[2],s_ftv.y_health[3],s_ftv.y_health[4],s_ftv.y_health[5]);
			fprintf(s_debug_pfile," Z轴特征:(1)低速均值：%f (2)低速波动%f (3)高速均值%f (4)高速波动：%f (5)跟随误差：%f (6)回程误差：%f \r\n",s_ftv.z_health[0],s_ftv.z_health[1],s_ftv.z_health[2],s_ftv.z_health[3],s_ftv.z_health[4],s_ftv.z_health[5]);
			fprintf(s_debug_pfile," 刀库特征:(1)重定向次数：%f (2)总换刀时间%f (3)总主轴定向时间%f (4)总选刀时间：%f (5)主轴电流均值：%f (6)Z轴电流均值：%f \r\n",s_ftv.t_health[0],s_ftv.t_health[1],s_ftv.t_health[3],s_ftv.t_health[5],s_ftv.t_health[7],s_ftv.t_health[11]);
		}
		//(9)保存本次特征向量
        ret = SaveFeaVec();
		if (ret == 0)
		{
			CalThread_Step_Set(9);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-18~-20
		} 

		//(10)健康指数计算                           
		ret = CalHealthIndex(healthIndex);
		if (ret == 0)
		{
			CalThread_Step_Set(10);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-21
		}

		//(11)计算过程退出处理
		ret = HealthTestCalExit();
		if (ret == 0)
		{
			CalThread_Step_Set(11);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-22
		} 
		//debug
		if(s_Print_CalDataInlo_Flag)
			CalThread_debug_exit();
	}
	CATCH{
		switch (s_ErrNo)
		{
		case MALLOCERR: //malloc()异常
			memset(healthIndex,0,5*sizeof(float));
			printf("malloc() error !!!");
			CalThread_StepPrint_Refresh();
			return MALLOCERR;
			break;
		case OPENFILEERR: //文件打开失败
			memset(healthIndex,0,5*sizeof(float));
			printf("open file error !!!");
			CalThread_StepPrint_Refresh();
			return OPENFILEERR;
			break;
		case NULL_POINTER: //使用空指针
			memset(healthIndex,0,5*sizeof(float));
			printf("null pointer !!!"); 
			CalThread_StepPrint_Refresh();
			return NULL_POINTER;
			break;
		default:
			memset(healthIndex,0,5*sizeof(float));
			CalThread_StepPrint_Refresh();
			return -1;
			break;
		}
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
//    int ReadGFile_MO6(FILE* pfile)
//
//    功能：
//            读取G代码文件: 获取换刀次数和换刀所在的行号
//
//    参数：
//            pfile： G代码文件指针
//    描述：
//            结果存入s_hfp.toolrow中           
//
//    返回：
//            -1：当前无换刀；0：换刀程序正常
//
//////////////////////////////////////////////////////////////////////////
int ReadGFile_MO6(FILE* pfile)
{
	char line[1024] = {0};
    int gCodeRowNum = 0; //G代码行号 

	fseek(pfile,0,SEEK_SET);
	while(!feof(pfile))
	{
		gCodeRowNum++;
		memset(line,0,sizeof(line));
		fgets(line,sizeof(line),pfile);

		if((strstr(line,"T")!=NULL) || (strstr(line,"t")!=NULL) ) //换刀所在行  加工中心换刀指令M06T()  //correct: M06 -> T
        {
			if(s_hfp.toolchgnum>=0) //不记录第一次换刀，排除初始刀位干扰 
			{
				s_hfp.toolrow[s_hfp.toolchgnum] = gCodeRowNum;
			}
			s_hfp.toolchgnum++;	
		}

	}

	if(	s_hfp.toolchgnum<=0) return -1;

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int ReadGFile_Feed(FILE* pfile)
//
//    功能：
//            读取G代码文件: 获取插补所在行和插补进给次数
//
//    参数：
//            pfile： G代码文件指针
//    描述：
//            结果存入s_hfp.feedrow中      
//
//    返回：
//            -1：进给次数不匹配；
//             0：进给程序正常
//
//////////////////////////////////////////////////////////////////////////
int ReadGFile_Feed(FILE* pfile)
{
    char line[1024] = {0};
	char strFedNeg_1[128] = {0};
	char strFedNeg_2[128] = {0};
	char strFedPos_1[128] = {0};
	char strFedPos_2[128] = {0};
    char strFeedHig_1[128] = {0};
	char strFeedHig_2[128] = {0};
	char strFeedLow_1[128] = {0};
	char strFeedLow_2[128] = {0};
    int gCodeRowNum = 0;     //G代码行号 
    bool isG01 = false;      //是否含G01
	bool isFeedPos = false;  //是否正向进给
	bool isFeedNeg = false;  //是否负向进给
	bool isFeedHigh = false; //是否高速进给
	bool isFeedLow = false;  //是否低速进给
    int  posHighNum  =0;     //高速正向进给的个数
	int  posLowNum  =0;
	int  negHighNum  =0;
	int  neglowNum  =0;

	//根据G代码宏定义约定对G代码分析用的字符串   //correct: add
	sprintf(strFedNeg_1, "%s%s%s", "X[", X_NEG_LIMIT, "]"); // "X[#101]"
	sprintf(strFedNeg_2, "%s%s%s", "x[", X_NEG_LIMIT, "]"); // "x[#101]"
	sprintf(strFedPos_1, "%s%s%s", "X[", X_POS_LIMIT, "]"); 
	sprintf(strFedPos_2, "%s%s%s", "x[", X_POS_LIMIT, "]"); 
	sprintf(strFeedHig_1, "%s%s%s", "F[", FED_HIGH_SPED, "]"); 
	sprintf(strFeedHig_2, "%s%s%s", "f[", FED_HIGH_SPED, "]"); 
	sprintf(strFeedLow_1, "%s%s%s", "F[", FED_LOW_SPED, "]"); 
	sprintf(strFeedLow_2, "%s%s%s", "f[", FED_LOW_SPED, "]"); 

	fseek(pfile,0,SEEK_SET);
	while(!feof(pfile))
	{
		gCodeRowNum++;
		memset(line,0,sizeof(line));
		fgets(line,sizeof(line),pfile);

		isG01 = ((strstr(line,"G01")!=NULL) || (strstr(line,"G1")!=NULL));
		if (isG01) //插补进给所在行进一步判断
		{
			isFeedNeg=(strstr(line,strFedNeg_1)!=NULL)||(strstr(line,strFedNeg_2));   //#101约定为X轴软负限位，以X轴负向运动判断进给负向
			isFeedPos=(strstr(line,strFedPos_1)!=NULL)||(strstr(line,strFedPos_2));   //判断是否正向

			isFeedHigh=(strstr(line,strFeedHig_1)!=NULL)||(strstr(line,strFeedHig_2));  //判断是否高速//F[#115]
			isFeedLow=(strstr(line,strFeedLow_1)!=NULL)||(strstr(line,strFeedLow_2));   //             F[#116]
			if (isFeedLow)
			{
				if (isFeedPos)
				{//低速正向进给
					s_hfp.feedrow[0][posLowNum] = gCodeRowNum;  //correct
					posLowNum++;
				}
				else if (isFeedNeg)
				{//低速负向进给
					s_hfp.feedrow[1][neglowNum] = gCodeRowNum;  //correct
					neglowNum++;
				}
			}
			else if (isFeedHigh)
			{
				if (isFeedPos)
				{//高速正向进给
					s_hfp.feedrow[2][posHighNum] = gCodeRowNum;  //correct
					posHighNum++;
				}
				else if (isFeedNeg)
				{//高速负向进给
                    s_hfp.feedrow[3][negHighNum] = gCodeRowNum;  //correct
					negHighNum++;
				}
			}
		}

	}

	if(posLowNum == neglowNum == posHighNum == negHighNum)
	{//高低速往返次数相等
		s_hfp.feednum = posLowNum;
	}
	else
	{
		return -1;   //各类进给次数不等
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int ReadGFile_Spd(FILE* pfile)
//
//    功能：
//            读取G代码文件: 获取主轴开始旋转和结束旋转所在行行号、主轴起停次数
//
//    参数：
//            pfile： G代码文件指针
//    描述：
//            结果存入s_hfp.spdrow中           
//             
//    返回：
//             0：成功；
//            -1：停止指令后无暂停指令；
//            -2：主轴起动、停止个数不匹配
//////////////////////////////////////////////////////////////////////////
int ReadGFile_Spd(FILE* pfile)
{
    char line[1024] = {0};            //G代码每行的内容
	char* tmp = NULL;
	int i=0;
    int gCodeRowNum = 0;		      //G代码行号 
	int startNum = 0;			      //主轴开始转动指令个数（M03、M04）
	int endNum = 0;			          //主轴停止转动指令个数（M05）
	int startRow[4*SPDTIME][3] = {0}; //第一列存主轴开始旋转行号，第二列标记正反转（1：正转，-1：反转），第三列维标记高低速（1：高速，-1：低速）
	int endRow[4*SPDTIME] = {0};      //主轴停止转动所在行号
	bool isPosRot = false;			  //主轴正转 （M03）
	bool isNegRot = false;			  //主轴正转 （M04）
	//bool isRotStart = false;		  //是否主轴开始旋转
	bool isRotEnd = false;			  //是否主轴停止转动（M05）
	bool isRotPause = false;		  //是否暂停（专指M05的下一条暂停）  （G04）
	bool isHighSped = false;		  //是否主轴高速
	bool isLowSped = false;			  //是否主轴低速
	bool isLowSpedSet = false;        //是否是主轴低速设置宏定义
	bool isHighSpedSet = false;       //是否是主轴高速设置宏定义
	fpos_t  origPos;				  //记录文件指针的位置
	int lowPosNum = 0;                //主轴低速正转次数
	int lowNegNum = 0;
	int HighPosNum = 0;
	int HighNegNum = 0;
	char strLowSpedSet_1[128] = {0};
	char strLowSpedSet_2[128] = {0};
	char strHigSpedSet_1[128] = {0};
	char strHigSpedSet_2[128] = {0};
	char strLowSped_1[128] = {0};
	char strLowSped_2[128] = {0};
	char strHigSped_1[128] = {0};
	char strHigSped_2[128] = {0};
	
	//根据G代码宏定义约定对G代码分析用的字符串   //correct: add
	sprintf(strLowSpedSet_1, "%s%s", SPD_LOW_SPED, "="); // 设置主轴转速的宏定义
	sprintf(strLowSpedSet_2, "%s%s", SPD_LOW_SPED, " ="); 
	sprintf(strHigSpedSet_1, "%s%s", SPD_HIGH_SPED, "="); // 
	sprintf(strHigSpedSet_2, "%s%s", SPD_HIGH_SPED, " ="); 
	sprintf(strLowSped_1, "%s%s%s", "S[",SPD_LOW_SPED, "]"); //提取主轴转动行号
	sprintf(strLowSped_2, "%s%s%s", "s[",SPD_LOW_SPED, "]"); 
	sprintf(strHigSped_1, "%s%s%s", "S[",SPD_HIGH_SPED, "]"); 
	sprintf(strHigSped_2, "%s%s%s", "s[",SPD_HIGH_SPED, "]"); 

	fseek(pfile,0,SEEK_SET);
	while(!feof(pfile))
	{
		gCodeRowNum++;
		memset(line,0,sizeof(line));
		fgets(line,sizeof(line),pfile);
		
		//提取主轴高低转速
		isLowSpedSet = (strstr(line,strLowSpedSet_1)!=NULL)||(strstr(line,strLowSpedSet_2)!=NULL);   //correct: add
		isHighSpedSet = (strstr(line,strHigSpedSet_1)!=NULL)||(strstr(line,strHigSpedSet_2)!=NULL);

		if (isLowSpedSet)//主轴低转速宏定义
		{
			tmp = strtok(line,"=");
			if(tmp !=NULL) tmp = strtok(NULL,";");
			if(tmp !=NULL) s_hfp.spd_lowSped = atoi(tmp);
		}

		if (isHighSpedSet)//主轴高转速宏定义
		{
			tmp = strtok(line,"=");
			if(tmp !=NULL) tmp = strtok(NULL,";");
			if(tmp !=NULL) s_hfp.spd_highSped = atoi(tmp);
		}

		//提取主轴转动行号
		isPosRot = (strstr(line,"M03")!=NULL)||(strstr(line,"M3")!=NULL);
		isNegRot = (strstr(line,"M04")!=NULL)||(strstr(line,"M4")!=NULL);
        isRotEnd = (strstr(line,"M05")!=NULL)||(strstr(line,"M5")!=NULL);
		//isRotPause = (strstr(line,"G04")!=NULL)||(strstr(line,"g04")!=NULL);
		isLowSped = (strstr(line,strLowSped_1)!=NULL)||(strstr(line,strLowSped_2)!=NULL);   //#110
		isHighSped = (strstr(line,strHigSped_1)!=NULL)||(strstr(line,strHigSped_2)!=NULL);  //#111

		//获取主轴开始转动行号，并标记高低速、正反转
		if (isPosRot || isNegRot)
		{//主轴开始转动行号
			if (isPosRot)
			{
				if (isLowSped)
				{//正转、低速
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = 1;
					startRow[startNum][2] = -1;
					startNum++; //correct
				} 
				else if(isHighSped)
				{//正转、高速
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = 1;
					startRow[startNum][2] = 1;
					startNum++; //correct
				}
			}
			else
			{
				if (isLowSped)
				{//反转、低速
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = -1;
					startRow[startNum][2] = -1;
					startNum++; //correct
				} 
				else if(isHighSped)
				{//反转、高速
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = -1;
					startRow[startNum][2] = 1;
					startNum++; //correct
				}
			}
		}

		//获取主轴停止行号
		if (isRotEnd)
		{
			fgetpos(pfile,&origPos); //记录指针当前位置
			memset(line,0,sizeof(line));
		    fgets(line,sizeof(line),pfile);//读取下一行的内容
			isRotPause = (strstr(line,"G04")!=NULL)||(strstr(line,"G4")!=NULL);
			if (isRotPause)//M05下一行接G04
			{
				endRow[endNum] = gCodeRowNum;  //+1;  //主轴特征提取不使用动态分配内存后修改
				endNum++;  //correct
			}
			else
			{
				return -1;  //停止指令后无暂停指令
			}
            fsetpos(pfile,&origPos); //还原文件指针位置
		}
	}
    /*-----------------[while end]------------------------*/
	
	//主轴起停行号存入
    if (endNum == startNum)
    {
		for (i=0;i<startNum;i++)
		{
			if (startRow[i][2] == -1)//低速
			{
				if (startRow[i][1] == 1)
				{//低速正转
                    s_hfp.spdrow[0][lowPosNum][0] = startRow[i][0];
					s_hfp.spdrow[0][lowPosNum][1] = endRow[i];
					lowPosNum++; //correct
				} 
				else if(startRow[i][1] == -1)
				{//低速反转
                    s_hfp.spdrow[1][lowNegNum][0] = startRow[i][0];
					s_hfp.spdrow[1][lowNegNum][1] = endRow[i];
					lowNegNum++; //correct
				}
			}
			else if (startRow[i][2] == 1)//高速
			{
				if (startRow[i][1] == 1)
				{//高速正转
                    s_hfp.spdrow[2][HighPosNum][0] = startRow[i][0];
                    s_hfp.spdrow[2][HighPosNum][1] = endRow[i];
					HighPosNum++; //correct
				} 
				else if(startRow[i][1] == -1)
				{//高速反转
                    s_hfp.spdrow[3][HighNegNum][0] = startRow[i][0];
					s_hfp.spdrow[3][HighNegNum][1] = endRow[i];
					HighNegNum++; //correct
				}
			}
		}
        
		if (lowPosNum == lowNegNum == HighPosNum == HighNegNum)
		{
			s_hfp.spdnum  = lowPosNum;
		}  
    } 
    else
    {
		return -2; //主轴起停个数不匹配
    }
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    void ReadGFile()
//
//    功能：
//            读取G代码文件: 1.刀库参数提取；
//                           2.进给直接运动参数提取
//							 3.进给圆运行参数提取
//
//    参数：
//
//    描述：
//            G代码文件只需要在初始化打开一次，读取完成就可以关闭
//
//    返回：
//           0:  成功
//          -1:  G代码文件打开失败
//          -2:  相关参数提取失败
//
/////////////////////////////////////////////////////////////////////////
int ReadGFile()
{
	FILE* pgfile=NULL;

	pgfile = fopen(s_hfp.gcodefile,"r");
	printf("the Gcode file name is:%s\n",s_hfp.gcodefile);
	if(pgfile==NULL) 
	{
		printf("open Gfile err!\n");
		s_CalThreadErr_No = -2;
		longjmp(s_SetJmp,OPENFILEERR);
	}
	
	//刀库参数提取
	if(ReadGFile_MO6(pgfile) < 0) 
	{
		s_CalThreadErr_No = -3;
		return -2;
	}
    //进给
	if(ReadGFile_Feed(pgfile) < 0)
	{
		s_CalThreadErr_No = -4;; 
		return -2;
	}
		
	//主轴
    if(ReadGFile_Spd(pgfile) < 0)
	{
		s_CalThreadErr_No = -5; 
		return -2;
	}

	fclose(pgfile);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int initparam(char * fname, int chnnum)
//
//    功能：
//            健康特征参数初始化
//							 
//
//    参数：1、采样数据文件名, G代码文件名 (固定)
//			2、通道数目     3、通道类型(枚举变量)
//
//    描述：
//            
//
//    返回：
//			0:成功    
//			-1:获取采样文件信息失败
/////////////////////////////////////////////////////////////////////////
int initparam(char* fname, int chnnum)
{
	char filename[128]={'\0'};
	char dataPath[128] = {'\0'};
	char gCodePath[128] = {'\0'};
	char stdPath[128] = {'\0'};

	struct stat finfo;

	strcpy(filename,fname);
	s_hfp.chn_num = chnnum;

	//初始化文件名
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, dataPath);
	sprintf(s_hfp.filename,"%s%c%s",dataPath,DIR_SEPARATOR,filename);			//采样文件
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, gCodePath);
	sprintf(s_hfp.gcodefile,"%s%c%s",gCodePath,DIR_SEPARATOR,HEALTHGCOD);		//G代码文件
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, stdPath);
	sprintf(s_hfp.stdfilename,"%s%c%s",stdPath,DIR_SEPARATOR,STD_VET_FNAME); //基准文件 //correct
	//Gcoderow
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, gCodePath);
	sprintf(s_hfp.GcoderowFilename,"%s%c%s",gCodePath,DIR_SEPARATOR,"Gcoderow.SV");		//G代码文件

	//采样点数
	if(stat(s_hfp.filename, &finfo) <0)
	{
		s_CalThreadErr_No = -1;
		return -1;
	}
	s_hfp.TotalData = (finfo.st_size-SAMPDATA_OFFSET)/s_hfp.chn_num/EUNIT;     //correct
	//tool：R116解析数据文件 
	sprintf(s_hfp.toolfile[0],"%s%c%s",dataPath,DIR_SEPARATOR,R1161);
	sprintf(s_hfp.toolfile[1],"%s%c%s",dataPath,DIR_SEPARATOR,R1164);
	sprintf(s_hfp.toolfile[2],"%s%c%s",dataPath,DIR_SEPARATOR,R1166);
	sprintf(s_hfp.toolfile[3],"%s%c%s",dataPath,DIR_SEPARATOR,R1167);
	s_hfp.toolchgnum=-1;

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int ReadSampFile()
//
//    功能：
//            读取采样数据文件 
//							 
//
//    参数：
//			
//
//    描述：
//            
//
//    返回： 
//           
//
/////////////////////////////////////////////////////////////////////////
int ReadSampFile()
{

	// 打开采样保存的数据文件
	s_hfp.pdatafile = fopen(s_hfp.filename,"rb");

	if(s_hfp.pdatafile==NULL) 
	{
		printf("open sample file err!\n");
		s_CalThreadErr_No = -6;
		longjmp(s_SetJmp,OPENFILEERR);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int find_first_element_float_file(int* out_first_index,int obj_element,int find_len,
//                            int find_start = 0,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT,float arrow_err=FLOAT_EQUAL)									
//    功能：
//            从浮点数文件中指定起始点和长度的连续区间内顺序查找 第一个目标元素对象的 索引
//		         				 
//
//    参数：    out_first_index     :（输出）查找到第一个目标元素的索引
//              obj_element			:要查找的元素对象
//				find_len			:查找区间的长度
//				find_start			:查找区间起点索引值
//             	fp			 :指定中间文件中查找     1.NULL 表示从采样数据文件中查找
//				idx_chn=0~15 : 采样数据文件指定通道查找; 
//						16   :   中间文件连续查找
//              arrow_err    : 允许的误差，默认为FLOAT_EQUAL
//
//    描述：
//            
//    返回： 
//            0: 成功
//			 -1: 未找到索引,out_first_index返回-1
/////////////////////////////////////////////////////////////////////////
int find_first_element_float_file(int* out_first_index,int obj_element,int find_len,int find_start = 0,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT,float arrow_err=FLOAT_EQUAL)
{

	int		i=0;
	float	tmp=0.0;
	int		idx=0;
	int filelen = 0;
	
	*(out_first_index)= -1;

	if(idx_chn < CHN_COUNT)		//采样文件
	{
		for(i=0;i < find_len;i++)
		{
			idx=find_start+i;
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);
				if(fabs(tmp-obj_element) <= arrow_err)//(tmp==element)
				{
					*(out_first_index)=idx;
					break;
				}
			}
		}
	}
	else						//分析产生的中间文件
	{	
		fseek (fp,0,SEEK_END);   
		filelen = (int)(ftell(fp)/EUNIT); 

		for(i=0; i<find_len; i++)
		{
			idx=find_start+i;
			
			if(idx>=0 && idx<filelen)
			{
				fseek(fp,idx*EUNIT,SEEK_SET);
				fread(&tmp,EUNIT,1,fp);				
				if(fabs(tmp-obj_element) <= arrow_err)//(tmp==element)
				{
					*(out_first_index)=idx;
					break;
				}
				
			}
		}
	}

	if(*(out_first_index) < 0) return -1; //未找到目标元素
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int find_first_element_int_file(int* out_first_index,int obj_element,int find_len,
//                            int find_start = 0,FILE* fp=NULL)									
//    功能：
//            从整型数据文件中指定起始点和长度的连续区间内顺序查找 第一个目标元素对象的 索引
//		         				 
//
//    参数：    out_first_index     :（输出）查找到第一个目标元素的索引
//              obj_element			:要查找的元素对象
//				find_len			:查找区间的长度
//				find_start			:查找区间起点索引值
//             	fp			 :指定中间文件中查找     1.NULL 表示从采样数据文件中查找
//
//    描述：
//            
//    返回： 
//            0: 成功
//			 -1: 未找到索引,out_first_index返回-1
/////////////////////////////////////////////////////////////////////////
int find_first_element_int_file(int* out_first_index,int obj_element,int find_len,int find_start = 0,FILE* fp=NULL)
{
	
	int		i=0;
	int 	tmp=0;
	int		idx=0;
	int filelen = 0;
	
	*(out_first_index)= -1;
	
	fseek (fp,0,SEEK_END);   
	filelen = (int)(ftell(fp)/sizeof(int)); 
	
	for(i=0; i<find_len; i++)
	{
		idx=find_start+i;
		
		if(idx>=0 && idx<filelen)
		{
			fseek(fp,idx*sizeof(int),SEEK_SET);
			fread(&tmp,sizeof(int),1,fp);				
			if(tmp==obj_element)//(tmp==element)
			{
				*(out_first_index)=idx;
				break;
			}
			
		}
	}
	
	if(*(out_first_index) < 0) return -1; //未找到目标元素
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int compute_statis_file(float* out_value, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    功能：
//            根据文件二进制数据计算指定起始点和长度的连续区间的统计分析值：1.最小值; 2.最大值; 3.均值; 4.方差
//							 (用于区间较大，不便给出索引区间情况)	
//
//    参数：  out_value	:统计分析值数组指针(长度==4)
//			  fp		:文件指针
//			  section_len	:指定长度
//			  start_idx		:指定区间起始点    NULL:表示从文件头开始			  
//			  idx_chn=0~15  : 采样数据文件指定通道查找; 
//						16  :   中间文件连续查找
//    描述：
//            方差std=sqrt(E(X^2)-E^2(X)) ,只需一次for循环 
//
//    返回： 1
//           
//
/////////////////////////////////////////////////////////////////////////
int compute_statis_continuous_infile(float* out_value, int section_len,int start_idx = NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT)
{
	int		i=0;
	float	tmp=0;
	double  fsum=0,fmin=0,fmax=0,fmean=0,fsum2=0,fstd=0;   //correct: float->double
	int	idx=0;
	int filelen = 0;
		
	if(idx_chn < CHN_COUNT)		//采样文件
	{	
		for(i=0;i < section_len;i++)
		{
			idx=start_idx+i;
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);
				fsum += (double)tmp;
				fsum2 += (double)tmp*tmp;
				
				if(i==0)
				{
					fmin=fmax=(double)tmp;
				}
				
				if(fmin>tmp)
					fmin=(double)tmp;						//最小值
				
				if(fmax<tmp)
					fmax=(double)tmp;						//最大值
			}
		}
		
		fmean = fsum/section_len;							//均值  warning:未进行除零判断（ilen ==0进入不了for循环）
		fstd=sqrt(fsum2/section_len - fmean*fmean);		//均方差  warning:出现负数开方的情况(精度损失导致，改为double后正常)

	}else						//分析产生的中间文件（一组数组文件）
	{
		fseek (fp, 0, SEEK_END);   
		filelen = (int)(ftell (fp)/EUNIT);

		for(i=0;i < section_len;i++)
		{
			idx=start_idx+i;

			if(idx>=0 && idx<filelen)
			{
				fseek(fp,idx*EUNIT,SEEK_SET);
				fread(&tmp,EUNIT,1,fp);
				fsum += (double)tmp;
				fsum2 += (double)tmp*tmp;
				
				if(i==0)
				{
					fmin=fmax=(double)tmp;
				}
				
				if(fmin>tmp)
					fmin= (double)tmp;					//最小值
				
				if(fmax<tmp)
					fmax= (double)tmp;					//最大值 
			}
		}
		
		fmean = fsum/section_len;								//均值
		fstd=sqrt(fsum2/section_len - fmean*fmean);			//均方差
	}

	*out_value =(float) fmin;
	*(out_value + 1) =(float) fmax;
	*(out_value + 2) = (float)fmean;
	*(out_value + 3) = (float)fstd;

	return 0 ;
}


/////////////////////////////////////////////////////////////////////////
//
//    int find_emtoid_float(int* idex,int element,int len,int* pos=NULL,FILE* fp=NULL,
//                      HealSpTy idx_chn=CHN_COUNT,EDGE eg=SIG,float arrow_err=0.0)									
//    功能：
//            从浮点文件中指定区间查找某个元素对应的索引(包含上升沿和下降沿)
//							 
//
//    参数：    idex     :输出索引
//              element  :要查找的元素对象
//				len		 :查找区间的长度
//				pos		 :查找区间对应的数组 1.NULL 不指定区间
//             	fp		 :指定文件中查找     1.NULL 表示从采样数据文件中查找
//				idx_chn=0~15: 采样数据文件指定通道查找; 
//						16:   中间文件连续查找
//				eg:  SIG:查找元素, DN:下降沿, UP:上升沿
//              arrow_err: 允许的误差，默认为0
//
//    描述：
//            
//
//    返回：  count:实际查找到的个数
//           
//
/////////////////////////////////////////////////////////////////////////
int find_emtoid_float(int* idex,int element,int len,int* pos=NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT,EDGE eg=SIG,float arrow_err=FLOAT_EQUAL)
{
	int		i=0,filelen=0;
	float	tmp=0,tem=0;
	int		count=0;
	int		idx=0;
	//struct stat finfo;


	if(idx_chn < CHN_COUNT)		//多维数组文件
	{
		for(i=0;i < len;i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);

			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);
				if(fabs(tmp-element) <= arrow_err)//(tmp==element)
				{
					*(idex+count)=idx;
					count++;
				}
			}
		}
	}
	else						//一组数组文件
	{
		fseek (fp, 0, SEEK_END);   
		filelen = (int)(ftell(fp)/EUNIT); 
	
		for(i=0; i<len; i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);

			if(idx>=0 && idx<filelen)
			{
				fseek(fp,idx*EUNIT,SEEK_SET);
				fread(&tmp,EUNIT,1,fp);
				
				if(eg==SIG)			//找元素
				{
					if(fabs(tmp-element) <= arrow_err)//(tmp==element)
					{
						*(idex+count)=idx;
						count++;
					}
				}
				else if(eg==EDN)	//找下降沿
				{
					fread(&tem,EUNIT,1,fp);
					//fseek(fp,EUNIT,SEEK_CUR);  //correct
					
					if(fabs(tmp-1) <= arrow_err && fabs(tem-0) <= arrow_err)  //correct  //(tmp==1 && tem==0)
					{
						*(idex+count)=idx +1;  // correct idx ->idx+1
						count++;
					}
				}
			}
		}
	}
	
	return count;
}

/////////////////////////////////////////////////////////////////////////
//
//    int find_emtoid_int(int* idex,int element,int len,int* pos=NULL,FILE* fp=NULL,EDGE eg=SIG)
//									
//    功能：
//            从整型文件中指定区间查找某个元素对应的索引(包含上升沿和下降沿)
//							 
//
//    参数：    idex     :输出索引
//              element  :要查找的元素对象
//				len		 :查找区间的长度
//				pos		 :查找区间对应的数组 1.NULL 不指定区间
//             	fp		 :指定文件中查找     1.NULL 表示从采样数据文件中查找
//				eg:  SIG:查找元素, DN:下降沿, UP:上升沿
//
//    描述：
//            
//
//    返回：  count:实际查找到的个数
//           
//
/////////////////////////////////////////////////////////////////////////
int find_emtoid_int(int* idex,int element,int len,int* pos=NULL,FILE* fp=NULL,EDGE eg=SIG)
{
	int		i=0,filelen=0;
	int	tmp=0,tem=0;
	int		count=0;
	int		idx=0;

	fseek (fp, 0, SEEK_END);   
	filelen = (int)(ftell(fp)/sizeof(int)); 
	
	for(i=0; i<len; i++)
	{
		if(pos==NULL)
			idx=i;
		else
			idx=*(pos+i);
		
		if(idx>=0 && idx<filelen)
		{
			fseek(fp,idx*sizeof(int),SEEK_SET);
			fread(&tmp,sizeof(int),1,fp);
			
			if(eg==SIG)			//找元素
			{
				if(tmp==element)
				{
					*(idex+count)=idx;
					count++;
				}
			}
			else if(eg==EDN)	//找下降沿
			{
				fread(&tem,EUNIT,1,fp);			
				if(tmp==1 && tem==0)  
				{
					*(idex+count)=idx +1;  // correct idx ->idx+1
					count++;
				}
			}
		}
	}
	
	return count;
}


/////////////////////////////////////////////////////////////////////////
//
//    int compute_statis_file(float* out_value, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    功能：
//            根据文件二进制数据计算指定序列的统计分析值：1.最小值; 2.最大值; 3.均值; 4.方差
//							 
//
//    参数：  out_value：统计分析值数组指针(长度==4)
//			  fp		:文件指针
//			  pos		:指定区别  NULL:表示一维文件，不需要指定区间
//			  len		:指定长度
//			  idx_chn	:指定通道 (多维)
//    描述：
//            方差std=sqrt(E(X^2)-E^2(X)) ,只需一次for循环 
//
//    返回： 1
//           
//
/////////////////////////////////////////////////////////////////////////
int compute_statis_file(float* out_value, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
{
	int		i=0, ilen=0;
	float	tmp=0;
	double  fsum=0,fmin=0,fmax=0,fmean=0,fsum2=0,fstd=0;   //correct: float->double
	int	idx=0;
	//struct stat finfo;
	
	ilen = len;
	
	if(idx_chn < CHN_COUNT)		//多维数组文件
	{
		if(pos==NULL)
			ilen = s_hfp.TotalData;
		
		for(i=0;i < ilen;i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);
				fsum += (double)tmp;
				fsum2 += (double)tmp*tmp;
				
				if(i==0)
				{
					fmin=fmax=(double)tmp;
				}
				
				if(fmin>tmp)
					fmin=(double)tmp;						//最小值
				
				if(fmax<tmp)
					fmax=(double)tmp;						//最大值
			}
		}
		
		fmean = fsum/ilen;							//均值  warning:未进行除零判断（ilen ==0进入不了for循环）
		fstd=sqrt(fsum2/ilen - fmean*fmean);		//均方差  warning:出现负数开方的情况(精度损失导致，改为double后正常)

	}else						//一组数组文件
	{
		if(pos==NULL)
		{
			//stat(fp, &finfo);
			//ilen = finfo.st_size/EUNIT;
			fseek (fp, 0, SEEK_END);   
			ilen = (int)(ftell (fp)/EUNIT); 
		}
	
		for(i=0;i < ilen;i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(fp,idx*EUNIT,0);
				fread(&tmp,EUNIT,1,fp);
				fsum += (double)tmp;
				fsum2 += (double)tmp*tmp;
				
				if(i==0)
				{
					fmin=fmax=(double)tmp;
				}
				
				if(fmin>tmp)
					fmin= (double)tmp;					//最小值
				
				if(fmax<tmp)
					fmax= (double)tmp;					//最大值 
			}
		}
		
		fmean = fsum/ilen;								//均值
		fstd=sqrt(fsum2/ilen - fmean*fmean);			//均方差
	}

	*out_value =(float) fmin;
	*(out_value + 1) =(float) fmax;
	*(out_value + 2) = (float)fmean;
	*(out_value + 3) = (float)fstd;

	return 0 ;
}

/////////////////////////////////////////////////////////////////////////
//
//    int compute_statis_array(float* out_array,float * farry,int flen,int *pos=NULL,int len=NULL)
//
//    功能：
//            根据数组内容计算指定序列的统计分析值：1.最小值; 2.最大值; 3.均值; 4.方差
//							 
//
//    参数：  out_array：统计分析值数组指针(长度==4)
//			  farry		:数组指针
//			  flen		:数组长度
//			  pos		:指定区别  NULL:不需要指定区间
//			  len		:指定长度
//    描述：
//            
//
//    返回： 1
//           
//
/////////////////////////////////////////////////////////////////////////
int compute_statis_array(float* out_array,float * farry,int flen,int *pos=NULL,int len=NULL)
{
	double fmin=0, fmax=0, fmean=0, fstd=0, fsum=0, fsum2=0; //correct
	int i=0;
	int idx=0,ilen=0;
	
	if(farry==NULL || len> flen)
		return -1;

	if(pos==NULL)
		ilen=flen;
	else
		ilen=len;

	for(i=0; i < ilen; i++)
	{
		if(pos==NULL)
			idx=i;
		else
			idx=*(pos+i);
		
		if(i == 0)
			fmin = fmax =(double)(*(farry+idx));

		fsum += (double)(*(farry+idx));
		fsum2 += (double)(*(farry+idx)) * (*(farry+idx));

		if(fmin> (*(farry+idx)))
		{
			fmin = (double)(*(farry+idx));
		}

		if(fmax < (*(farry+idx)))
		{
			fmax = (double)(*(farry+idx));
		}
	}

	fmean = fsum/ilen;								//均值
	fstd=sqrt(fsum2/ilen - fmean*fmean);				//均方差


	*out_array = (float)fmin;
	*(out_array + 1) = (float)fmax;
	*(out_array + 2) = (float)fmean;
	*(out_array + 3) = (float)fstd;

    return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int merge_new_file(FILE* outfile,FILE* infile,int *pos,int len,HealSpTy idx_chn=CHN_COUNT)
//
//    功能：
//            两个文件夹内容合并
//							 
//
//    参数：  outfile	:输出文件 
//			  infile	:输入文件
//			  pos		:指定区别  NULL:不需要指定区间
//			  len		:指定长度
//			  idx_chn	:指定通道 (多维)
//    描述：
//            
//
//    返回： 1
//           
//
/////////////////////////////////////////////////////////////////////////
int merge_new_file(FILE* outfile,FILE* infile,int *pos,int len,HealSpTy idx_chn=CHN_COUNT)
{
	int i=0,idx=0;
	float tmp=0;

	if(idx_chn<CHN_COUNT) //输入的数据源为采样文件数据
	{
		for(i=0;i < len;i++)
		{
			idx=*(pos+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);
				fwrite(&tmp,EUNIT,1,outfile);
			}
		}
	}else   //输入的数据源为其它文件数据
	{
		if(infile==NULL)
			return -1;

		for(i=0;i < len;i++)
		{
			idx=*(pos+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(infile,idx*EUNIT,SEEK_SET);
				fread(&tmp,EUNIT,1,infile);
				fwrite(&tmp,EUNIT,1,outfile);
			}
		}
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////
//
//    int ToolFtvExt()
//
//    功能：	刀库特征提取
//
//    参数：  
//			  
//			  
//    描述：
//            
//
//    返回： 
//           0:成功   
//			 -1:未找到G代码对应索引
/////////////////////////////////////////////////////////////////////////
int ToolFtvExt()
{
	int i = 0;
	int toolrow=0;
	int sigtoollen=0;						//单次换刀对应插补行的长度
	int iip_grow[IIP_NUM]={0};				//单次换刀对应的插补行索引

	int chg_time[IIP_NUM]={0}, spd_ortime[IIP_NUM]={0}, chs_beg[10]={0},chs_end[10]={0};
	float tlChgTime[TOOLTIME] = {0};		//单次换刀时间 
	float spdleOrTime[TOOLTIME] = {0};		//单次主轴定向时间 
	float chsTolTime[TOOLTIME] = {0};		//单次选刀时间
	int   chsTolIdx_tmp[IIP_NUM]={0};       //单次选刀索引      
	float spdcur_std[TOOLTIME] ={0};		//单次定向主轴电流	
	float zCur_std[TOOLTIME] = {0};			//单次选刀时 Z轴电流方差
	float   reOrtNum[TOOLTIME] = {0};		//主轴定向次数 
	float std_tmp[4]={0};
	FILE *fspdcur=NULL, *fzcur=NULL;
	char sfname[128]={0};				//所有换刀进重定向主轴电流
	char zfname[128]={0};				//选刀过程Z轴电流
	char tmpPath[128] = {0};


	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, tmpPath);
	sprintf(sfname,"%s%c%s",tmpPath,DIR_SEPARATOR,"or_spdcur.bin");  //主轴定向时电流
	sprintf(zfname,"%s%c%s",tmpPath,DIR_SEPARATOR,"ct_zcur.bin");    //刀库选刀时Z轴电流

	fspdcur = fopen(sfname,"wb+");  //correct  "wb" -> "wb+"
	fzcur = fopen(zfname,"wb+");    //correct  "wb" -> "wb+"   "sfname" ->"zfname"
	if(fzcur == NULL || fspdcur == NULL) 
	{
		s_CalThreadErr_No = -12;
		longjmp(s_SetJmp,OPENFILEERR);
	}

	for(i=0;i<s_hfp.toolchgnum;i++)
	{
		//初始化
		memset(iip_grow,0,sizeof(int)*IIP_NUM);  //correct :float -> int
		memset(chg_time,0,sizeof(int)*IIP_NUM);  //correct :float -> int
		memset(spd_ortime,0,sizeof(int)*IIP_NUM); //correct :float -> int
		memset(chsTolIdx_tmp,0,sizeof(int)*IIP_NUM); //correct :add
		memset(std_tmp,0,sizeof(float)*4);

		toolrow = s_hfp.toolrow[i];
		//sigtoollen = find_emtoid_float(iip_grow,toolrow,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//gcoderow
		sigtoollen = find_emtoid_int(iip_grow,toolrow,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);

		//debug
		if(s_Print_CalDataInlo_Flag)
			fprintf(s_debug_pfile,"换刀行号为%d的长度：%d\r\n",toolrow,sigtoollen);

		if(sigtoollen>0)
		{
			tlChgTime[i] = (float)find_emtoid_float(chg_time,1,sigtoollen,iip_grow,s_hfp.ptoolfile[0],CHN_COUNT,SIG)/s_samplFreq;			//116.1 :换刀时间
			//debug
			if(s_Print_CalDataInlo_Flag)
				fprintf(s_debug_pfile,"换刀行号为%d的换刀时间：%f\r\n",toolrow,tlChgTime[i]);

			spdleOrTime[i] = (float)find_emtoid_float(spd_ortime,1,sigtoollen,iip_grow,s_hfp.ptoolfile[2],CHN_COUNT,SIG)/s_samplFreq;		//116.6 :主轴定向时间
			compute_statis_file(std_tmp,NULL,spd_ortime,(int)(spdleOrTime[i]*s_samplFreq),CUR_SPIND);		//定向时：主轴电流min\max\mean\std
			spdcur_std[i] = std_tmp[3];
			merge_new_file(fspdcur,NULL,spd_ortime,(int)(spdleOrTime[i]*s_samplFreq),CUR_SPIND);

			find_emtoid_float(chs_beg,1,sigtoollen,iip_grow,s_hfp.ptoolfile[1],CHN_COUNT,EDN);			//116.4:下降沿
			find_emtoid_float(chs_end,1,sigtoollen,iip_grow,s_hfp.ptoolfile[3],CHN_COUNT,EDN);			//116.7:下降沿
			chsTolTime[i]=((float)chs_end[0]-(float)chs_beg[0]+1)/s_samplFreq;						//选刀时间   correct: add:+1

			create_linspace(chsTolIdx_tmp,IIP_NUM,chs_beg[0],1,(int)(chsTolTime[i]*s_samplFreq));  //correct 
// 			for(i=0;i< (int)(chsTolTime[i]*s_samplFreq);i++)
// 			{
// 				chsTolIdx_tmp[i]=chs_beg[0]+i;
// 			}
			compute_statis_file(std_tmp,NULL,chsTolIdx_tmp,(int)(chsTolTime[i]*s_samplFreq),CUR_ACT_Z);			//计算选刀过程对应的Z轴电流统计值								
			zCur_std[i] = std_tmp[3];
			merge_new_file(fzcur,NULL,chsTolIdx_tmp,(int)(chsTolTime[i]*s_samplFreq),CUR_ACT_Z);

			reOrtNum[i] = (float)find_emtoid_float(chsTolIdx_tmp,1,(int)(tlChgTime[i]*s_samplFreq),chg_time,s_hfp.ptoolfile[2],CHN_COUNT,EDN);	//主轴重定向次数
		}
		else
		{
			s_CalThreadErr_No = -13;
			return -1;		//未找到该行G代码对应索引
		}
	}
	//清洗文件缓冲区
	fflush(fspdcur);   //correct: add
	fflush(fzcur);

	//刀具特征向量
	compute_statis_array(std_tmp,reOrtNum, s_hfp.toolchgnum);						//重定向次数
		s_ftv.t_health[0] = std_tmp[2]* s_hfp.toolchgnum;
	compute_statis_array(std_tmp,tlChgTime, s_hfp.toolchgnum);						//总换刀时间
		s_ftv.t_health[1] = std_tmp[2]* s_hfp.toolchgnum;
		s_ftv.t_health[2] = std_tmp[1];												//单次换刀最大值
	compute_statis_array(std_tmp,spdleOrTime, s_hfp.toolchgnum);	
		s_ftv.t_health[3] = std_tmp[2]* s_hfp.toolchgnum;							//总定向时间
		s_ftv.t_health[4] = std_tmp[1];												//最大定向时间
	compute_statis_array(std_tmp,chsTolTime, s_hfp.toolchgnum);	
		s_ftv.t_health[5] = std_tmp[2]* s_hfp.toolchgnum;							//总选刀时间
		s_ftv.t_health[6] = std_tmp[1];												//最大选刀时间

	compute_statis_file(std_tmp,fspdcur);											//主轴电流	
		s_ftv.t_health[7] = std_tmp[2];												//均值
		s_ftv.t_health[8] = std_tmp[1];												//最大值
		s_ftv.t_health[9] = std_tmp[0];												//最小值
	compute_statis_array(std_tmp,spdcur_std, s_hfp.toolchgnum);	
		s_ftv.t_health[10] = std_tmp[1];											//方差最大值

	compute_statis_file(std_tmp,fzcur);												//Z轴电流	
		s_ftv.t_health[11] = std_tmp[2];											//均值
		s_ftv.t_health[12] = std_tmp[1];											//最大值
		s_ftv.t_health[13] = std_tmp[0];											//最小值
	compute_statis_array(std_tmp,zCur_std, s_hfp.toolchgnum);	
		s_ftv.t_health[14] = std_tmp[1];											//方差最大值

	//刀库部分退出处理，关闭文件、并删除中间文件
	fclose(fspdcur);
	remove(sfname);
	fclose(fzcur);
	remove(zfname);
	for(i=0;i<4;i++)
	{
		fclose(s_hfp.ptoolfile[i]);
		s_hfp.ptoolfile[i] = NULL;
		remove(s_hfp.toolfile[i]);
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////
//
//    int read_std_file()
//
//    功能：
//            读标准化文件 (暂时根据matlab数据固定写入)
//    参数：
//          
//    描述：
//            标准化文件包括：
//            （1）特征向量基准；
//            （2）特征向量归一化标准；
//    返回:
//            0:成功
//            -2 ：数据读取失败   
//////////////////////////////////////////////////////////////////////////
int read_std_file()
{
    //char filename[128] = {"\0"}; //correct
	//FILE *fp = NULL;
	//	int readnum = 0;
	//sprintf(s_hfp.stdfilename,"%s%c%s",HEALTHPATH,DIR_SEPARATOR,STD_VET_FNAME); //correct
	
	if ( (s_hfp.pstdfile = fopen(s_hfp.stdfilename,"rb+")) == NULL)  //correct
	{
		printf("open std file err!\n");
		s_CalThreadErr_No = -10;
		longjmp(s_SetJmp,OPENFILEERR);//文件打开失败
	} 
	else
	{
		if (fread(&s_hfp.historyTestNum,sizeof(int),1,s_hfp.pstdfile) != 1)  //读入历史自检次数
        {
			s_CalThreadErr_No = -11;
			return -2;//数据读取失败
        }
        if (fread(&s_hfp.feat_base,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //读入各特征向量基准
        {
			s_CalThreadErr_No = -11;
			return -2;//数据读取失败
        }
        if (fread(&s_hfp.feat_min,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //读入归一化标准--最小值
        {
			s_CalThreadErr_No = -11;
			return -2;//
        }
		if (fread(&s_hfp.feat_max,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //读入归一化标准--最大值
        {
			s_CalThreadErr_No = -11;
			return -2;//
        }
	}
	
// 	fclose(s_hfp.pstdfile);
// 	s_hfp.pstdfile = NULL;
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//
//    int ParseR116()
//
//    功能：
//            解析R116寄存器数据，得到R116.1、R116.4、R116.6、R116.7点位信号
//    参数：
//            无
//    描述：
//            从采样数据文件中的
//                      
//    返回:
//            0:成功
//            -1: 未找到最后一次换刀下一行G代码
//            -2 ：数据读取失败   
//////////////////////////////////////////////////////////////////////////
int ParseR116()//(FILE* pfile)
{
	int i=0;
	int shiftmp=0,shiftmp1=0,shiftmp4=0,shiftmp6=0,shiftmp7=0;
	float ftmp=0.0;
	float ftmp_wt = 0.0;
	HealSpTy idx_r116=R116;
	int sum1=0,sum4=0,sum6=0,sum7=0;
	int toolChgLen = 0;
	int temp = 0;

	for(i=0;i<4;i++)
	{
		s_hfp.ptoolfile[i]=fopen(s_hfp.toolfile[i],"wb+"); //correct : "rb" ->"wb"->"wb+"
		if(s_hfp.ptoolfile[i] == NULL) 
		{
			s_CalThreadErr_No = -7;
			longjmp(s_SetJmp,OPENFILEERR);
		}
	}

	//提取换刀过程的索引
	for(i=0;i<10;i++)
	{
		//必须保证换刀动作结束后还有一行G代码'
		if(find_first_element_int_file(&toolChgLen,s_hfp.toolrow[s_hfp.toolchgnum-1]+1,s_hfp.TotalData,0,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		
		//判断索引下个元素是否也是待求元素,如果否,判断此索引为无效
		fseek(s_hfp.pGcoderow,toolChgLen*sizeof(int),SEEK_SET);
		fread(&temp,sizeof(int),1,s_hfp.pGcoderow);
		if (temp == (s_hfp.toolrow[s_hfp.toolchgnum-1]+1) )
		{
			break;
		}
		else
		{
			if(i == 9)
			{
				s_CalThreadErr_No = -8;
				return -1;
			}
		}
	}

	for(i=0;i<toolChgLen;i++)
	{
		fseek(s_hfp.pdatafile,(i*s_hfp.chn_num+idx_r116)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
		fread(&ftmp,sizeof(float), 1,s_hfp.pdatafile);   //correct

		shiftmp=(int)ftmp;
		shiftmp1 = (shiftmp>>1) & 1; 
		sum1+=shiftmp1;
		ftmp_wt = (float)shiftmp1;
		fwrite(&ftmp_wt,sizeof(float),1,s_hfp.ptoolfile[0]);//correct

		shiftmp4 = (shiftmp>>4) & 1; 
		sum4+=shiftmp4; 
		ftmp_wt = (float)shiftmp4;
		fwrite(&ftmp_wt,sizeof(float),1,s_hfp.ptoolfile[1]);//correct

		shiftmp6 = (shiftmp>>6) & 1; 
		sum6+=shiftmp6; 
		ftmp_wt = (float)shiftmp6;
		fwrite(&ftmp_wt,sizeof(float),1,s_hfp.ptoolfile[2]);//correct

		shiftmp7 = (shiftmp>>7) & 1; 
		sum7+=shiftmp7; 
		ftmp_wt = (float)shiftmp7;
		fwrite(&ftmp_wt,sizeof(float),1,s_hfp.ptoolfile[3]);//correct
	}

	if(sum1==0 || sum4==0 || sum6==0 || sum7==0)
	{
		printf("bit single is zero!");
		s_CalThreadErr_No = -9;
		return -2;
	}

	//debug
	if(s_Print_CalDataInlo_Flag)
		fprintf(s_debug_pfile," R116.1置1次数：%d\r\n R116.4置1次数：%d\r\nR116.6置1次数：%d\r\n R116.7置1次数：%d\r\n",sum1,sum4,sum6,sum7);


    //将文件缓冲区数据写入文件                  //correct
    for(i=0;i<4;i++)
	{
		fflush(s_hfp.ptoolfile[i]);
	}

	return 0;
}

////////////////////////////
//以下潘成龙新增
//
//20160906
//
/////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    int ExtrPoint(int* out_sigmax,int* out_sigmin, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    功能：  根据文件数据得到指定序列的极大值、极小值索引
//            
//    参数：  out_sigmax:极大值索引数组指针
//            out_maxNum:极大值个数
//            out_sigmin:极小值索引数组指针
//            out_minNum:极小值个数
//			  fp		:文件指针
//			  pos		:指定区别  NULL:表示一维文件，不需要指定区间
//			  len		:指定长度
//			  idx_chn	:指定通道 (多维)
//   
//    描述：
//            数据源可以是fp指向的文件、采样数据文件（HealSpTy对应）
//    返回:
//            极大值与极小值个数较少的 (max_count<min_count)?max_count:min_count
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExtrPoint(int* out_sigmax,int* out_maxNum,int* out_sigmin,int* out_minNum, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
{
	int		i=0, ilen=0;
	int     min_count = 0, max_count = 0;
	float	tmp=0;
	float   data = 0.0, lag_data = 0.0;
	float   data_diff = 0.0, lag_diff = 0.0;
	int	idx=0;
	//struct stat finfo;
	
	ilen = len;
	
	if(idx_chn < CHN_COUNT)		//多维数组文件
	{
		if(pos==NULL)
			ilen = s_hfp.TotalData;
		
		for(i=0;i < ilen;i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);
			
 			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);

                if (i == 0)
                {
                     data = tmp;
                } 
				else
				{
					//求滞后差分Diff(X), for a vector X, is [X(2)-X(1),  X(3)-X(2), ..., X(n)-X(n-1)].
                    lag_data = data;
					data = tmp;
					if ( i == 1)
					{
						data_diff = data - lag_data;
					}
					else
					{
                        lag_diff = data_diff;
						data_diff = data - lag_data;
						if (lag_diff*data_diff<0 && lag_diff<0)//极小值  
						{
                             *(out_sigmin + min_count) = idx-1; //correct: idx+1  ->idx-1
							 min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//极大值  
						{
							*(out_sigmax + max_count) = idx-1;  //correct: idx+1  ->idx-1
							 max_count++;
						}
					}
				}
			}
		}
	}
	else						//一组数组文件
	{
		if(pos==NULL)
		{
			//stat(fp, &finfo);
			//ilen = finfo.st_size/EUNIT;
			fseek (fp, 0, SEEK_END);   
			ilen = (int)(ftell (fp)/EUNIT); 
		}
		
		for(i=0;i < ilen;i++)
		{
			if(pos==NULL)
				idx=i;
			else
				idx=*(pos+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(fp,idx*EUNIT,0);
				fread(&tmp,EUNIT,1,fp);
				
				if (i == 0)
                {
					data = tmp;
                } 
				else
				{
					//求滞后差分
                    lag_data = data;
					data = tmp;
					if ( i == 1)
					{
						data_diff = data - lag_data;
					}
					else
					{
                        lag_diff = data_diff;
						data_diff = data - lag_data;
						if (lag_diff*data_diff<0 && lag_diff<0)//极小值  
						{
							*(out_sigmin + min_count) = idx-1;  //correct: idx+1  ->idx-1
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//极大值  
						{
							*(out_sigmax + max_count) = idx-1;  //correct: idx+1  ->idx-1
							max_count++;
						}
					}
				}
			}
		}
	}

	*(out_maxNum) = max_count; //极大值个数
	*(out_minNum) = min_count; //极小值个数

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    int CalVib_continuous_infile(int* out_vib,int section_len,int start_idx=NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    功能：  根据文件二进制数据计算指定起始点和长度的连续区间的 波动值
//            
//    参数：  out_vib		:数据波动值(输出)
//            section_len	:区间长度
//            start_idx		:区间起点索引
//			  fp			:中间文件指针  
//			  idx_chn=0~15  : 采样数据文件指定通道查找; 
//						16  :   中间文件连续查找
//   
//    描述：
//            数据源可以是fp指向的文件、采样数据文件（HealSpTy对应）
//    返回:
//            
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CalVib_continuous_infile(float* out_vib,int section_len,int start_idx=NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT)
{
	int		i=0;
	int     min_count = 0, max_count = 0;  //极值计数
	double  min_mean = 0.0, max_mean = 0.0;  //极值的滑动平均
	float	tmp=0;
	float   data = 0.0, lag_data = 0.0;
	float   data_diff = 0.0, lag_diff = 0.0;
	int	idx=0;
	int filelen = 0;
	
	if(idx_chn < CHN_COUNT)		//采样数据文件
	{		
		for(i=0;i < section_len;i++)
		{
			idx=start_idx+i;
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+idx_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&tmp,EUNIT,1,s_hfp.pdatafile);

                if (i == 0)
                {
                     data = tmp;
                } 
				else
				{
					//求滞后差分Diff(X), for a vector X, is [X(2)-X(1),  X(3)-X(2), ..., X(n)-X(n-1)].
                    lag_data = data;
					data = tmp;
					if ( i == 1)
					{
						data_diff = data - lag_data;
					}
					else
					{
                        lag_diff = data_diff;
						data_diff = data - lag_data;
						if (lag_diff*data_diff<0 && lag_diff<0)//极小值  
						{
							min_mean = (min_mean*min_count+lag_data)/(min_count+1); //极小值滑动平均
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//极大值  
						{
							max_mean = (max_mean*max_count+lag_data)/(max_count+1); //极大值滑动平均
							max_count++;
						}
					}
				}
			}
		}
	}
	else						//一组数组文件
	{
		fseek (fp, 0, SEEK_END);   
		filelen = (int)(ftell (fp)/EUNIT); 

		for(i=0;i < section_len;i++)
		{
			idx=start_idx+i;
			if(idx>=0 && idx<filelen)
			{
				fseek(fp,idx*EUNIT,0);
				fread(&tmp,EUNIT,1,fp);
				
				if (i == 0)
                {
					data = tmp;
                } 
				else
				{
					//求滞后差分
                    lag_data = data;
					data = tmp;
					if ( i == 1)
					{
						data_diff = data - lag_data;
					}
					else
					{
                        lag_diff = data_diff;
						data_diff = data - lag_data;
						if (lag_diff*data_diff<0 && lag_diff<0)//极小值  
						{
							min_mean = (min_mean*min_count+lag_data)/(min_count+1); //极小值滑动平均
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//极大值  
						{
							max_mean = (max_mean*max_count+lag_data)/(max_count+1); //极大值滑动平均
							max_count++;
						}
					}
				}
			}
		}
	}

	*(out_vib) = (float)(max_mean - min_mean);  //输出波动值

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
//    float caltrackerr(int* subscript=NULL,int sub_length=NULL ,HealSpTy act_chn,HealSpTy cmd_chn)
//
//    功能：  计算执行某条G01指令期间单根进给轴的最大跟随误差
//
//    参数：  
//			  subscript： 指定下标索引的数组，NULL表示不指定,所有数据参与计算
//			  sub_length：指定下标索引的长度
//            act_chn:    实际位置采样通道号
//            cmd_chn:    指令位置采样通道号
//    描述：
//            从采样数据文件中计算
//
//    返回： trackerr ：最大跟随误差
//           
//
/////////////////////////////////////////////////////////////////////////
float caltrackerr(int* subscript,int sub_length ,HealSpTy act_chn,HealSpTy cmd_chn)
{
	int		i=0, ilen=0;
	float	act_tmp=0.0, cmd_tmp = 0.0;
	float   err_tmp = 0.0;
	float   trackerr = 0.0;
	int	idx=0;
	
	ilen = sub_length;
	
	if(act_chn < CHN_COUNT && cmd_chn < CHN_COUNT)		
	{
		if(subscript==NULL)
			ilen = s_hfp.TotalData;
		
		for(i=0;i < ilen;i++)
		{
			if(subscript==NULL)
				idx=i;
			else
				idx=*(subscript+i);
			
			if(idx>=0 && idx<s_hfp.TotalData)
			{
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+act_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&act_tmp,EUNIT,1,s_hfp.pdatafile);
				fseek(s_hfp.pdatafile,(idx*s_hfp.chn_num+cmd_chn)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
				fread(&cmd_tmp,EUNIT,1,s_hfp.pdatafile);
				err_tmp = fabsf(act_tmp - cmd_tmp);
                if (err_tmp  > trackerr)
                {
					trackerr = err_tmp;
                }
			}
		}
	}
	return trackerr ;
}
/////////////////////////////////////////////////////////////////////////
//
//    int SigFeed(float* outft,int* subscript,int sub_length,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
//
//    功能：	执行某条G01指令期间单根进给轴的特征提取（电流均值、电流波动、最大跟随误差）
//
//    参数：  
//			    outftv:   输出进给轴特征值（电流均值、电流波动、最大跟随误差）
//              subscript: 本次G01行号对应的索引下标
//              sub_length: 索引长度
//              cur_chn:  进给轴电流采样通道号
//              act_chn:  实际位置采样通道号
//	            cmd_chn:  指令位置采样通道号		  
//    描述：
//              从采样数据文件中计算
//
//    返回：    0： 成功
//           
//
/////////////////////////////////////////////////////////////////////////
int SigFeed(float* outft,int* subscript,int sub_length,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
{
	int maxindex[IIP_NUM] = {0};     //极大值索引
	int maxNum = 0;                  //极大值个数
    int minindex[IIP_NUM] = {0};     //极小值索引
	int minNum = 0;                  //极小值个数
	float statis_temp[4] = {0.0};
	float maxmean = 0.0;             //极大值均值
	float minmean = 0.0;             //极小值均值

	compute_statis_file(statis_temp,NULL,subscript,sub_length,cur_chn);
	*(outft) = statis_temp[2];//电流均值 //correct:   statis_temp[3] -> statis_temp[2]
	ExtrPoint(maxindex,&maxNum,minindex,&minNum,NULL,subscript,sub_length,cur_chn);
    compute_statis_file(statis_temp,NULL,maxindex,maxNum,cur_chn);
    maxmean = statis_temp[2];            //correct:   statis_temp[3] -> statis_temp[2]
	compute_statis_file(statis_temp,NULL,minindex,minNum,cur_chn);
	minmean = statis_temp[2];            //correct:   statis_temp[3] -> statis_temp[2]
    *(outft+1) = maxmean - minmean;//电流波动
    *(outft+2) = caltrackerr(subscript,sub_length,act_chn,cmd_chn);//最大跟随误差

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
//    int SigFeedFtvExt(float* outftv,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
//
//    功能：	单根进给轴（X/Y/Z轴）特征向量提取
//
//    参数：  
//			    outftv:   输出进给轴特征向量
//              cur_chn:  进给轴电流采样通道号
//              act_chn:  实际位置采样通道号
//	            cmd_chn:  指令位置采样通道号	  
//    描述：
//              根据采样数据计算
//
//    返回：    0 ：成功
//              -1：失败
//
/////////////////////////////////////////////////////////////////////////
int SigFeedFtvExt(float* outftv,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
{
	int i = 0;
	int row_temp = 0;
	int sigfeedlen = 0;                     //单次进给对应插补行的长度
	int iip_grow[IIP_NUM]={0};			//单次进给对应的插补行索引 (可将索引统一改为int型)
	float curft[4][FEEDTIME][3] = {0.0}; //进给电流特征：[4]高低速正反向组合;[FEEDTIME]各组合次数;[3]（电流均值、波动、最大跟随误差）  
	float lcurmean =0.0; //各轴低速电流均值之和
    float lcurvirb =0.0; //各轴低速电流波动之和
	float hcurmean =0.0; //各轴高速电流均值之和
    float hcurvirb =0.0; //各轴高速电流波动之和
	float trackerr =0.0; //最大跟随误差
    float diffcur = 0.0; //电流回程误差之和
	float ftmp = 0.0; //中间变量

	//单个G01插补行特征提取
	for(i=0;i<s_hfp.feednum;i++)
	{
		//低速正向插补特征提取
		row_temp= s_hfp.feedrow[0][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"低速进给插补行%d的索引长度：%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"低速进给插补行%d的起始索引：%d\r\n",row_temp,*(iip_grow));
		}
		
		if (sigfeedlen>0)
		{
            SigFeed(&curft[0][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//低速负向插补特征提取
		row_temp= s_hfp.feedrow[1][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"低速进给插补行%d的索引长度：%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"低速进给插补行%d的起始索引：%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[1][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//高速正向插补特征提取
		row_temp= s_hfp.feedrow[2][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"低速进给插补行%d的索引长度：%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"低速进给插补行%d的起始索引：%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[2][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//高速负向插补特征提取
		row_temp= s_hfp.feedrow[3][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"低速进给插补行%d的索引长度：%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"低速进给插补行%d的起始索引：%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[3][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		
        //---------------特征提取-------------------------------//
		//低速电流均值之和
        lcurmean = lcurmean+ fabsf(curft[0][i][0])+ fabsf(curft[1][i][0]); //xcurft[0][][] 为低速正向特征，xcurft[1][][]为低速反向特征
		//低速电流波动之和
		lcurvirb = lcurvirb+ curft[0][i][1]+ curft[1][i][1];
		//高速电流均值之和
        hcurmean = hcurmean+ fabsf(curft[2][i][0])+ fabsf(curft[3][i][0]);
		//高速电流波动之和
		hcurvirb = hcurvirb+ curft[2][i][1]+ curft[3][i][1];
		//最大跟随误差
		ftmp = max(max(curft[0][i][2],curft[1][i][2]),max(curft[2][i][2],curft[3][i][2])); //一轮四次中的最大误差
		trackerr = max(trackerr,ftmp);
		//电流回程误差
        diffcur = diffcur+(fabsf(curft[0][i][0])-fabsf(curft[1][i][0]))+(fabsf(curft[2][i][0])-fabsf(curft[3][i][0]));
	}
	
	//进给轴特征向量赋值
    *(outftv) = lcurmean/s_hfp.feednum/2;   //低速电流均值
	*(outftv+1) = lcurvirb/s_hfp.feednum/2; //低速电流波动
	*(outftv+2) = hcurmean/s_hfp.feednum/2; //高速电流均值
	*(outftv+3) = hcurvirb/s_hfp.feednum/2; //高速电流波动
	*(outftv+4) = trackerr;                 //最大跟随误差
	*(outftv+5) = diffcur/s_hfp.feednum/2;  //电流回程误差

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int FeedFtvExt()
//
//    功能：	进给轴（X、Y、Z轴）特征向量提取
//
//    参数：  
//			    无
//			  
//    描述：
//            
//
//    返回：    0：成功
//				-1:特征提取失败        
//
/////////////////////////////////////////////////////////////////////////
int FeedFtvExt()
{

	if(SigFeedFtvExt(&s_ftv.x_health[0],CUR_ACT_X,AXIS_ACT_X,AXIS_CMD_X) < 0) //X轴
	{
		s_CalThreadErr_No = -15;
		return -1;
	}
    if(SigFeedFtvExt(&s_ftv.y_health[0],CUR_ACT_Y,AXIS_ACT_Y,AXIS_CMD_Y) < 0) //Y轴
	{
		s_CalThreadErr_No = -16;
		return -1;
	}
	if(SigFeedFtvExt(&s_ftv.z_health[0],CUR_ACT_Z,AXIS_ACT_Z,AXIS_CMD_Z) < 0) //Z轴
	{
		s_CalThreadErr_No = -17;
		return -1;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int Connect_GRow_Idx(int* out_idx,int out_len,int start_row,int end_row)
//
//    功能：	连接连续G代码行号对应的下标索引
//
//    参数：  
//			    out_idx：   连续行号所对应的采样索引数组
//              out_len：   索引数组最大长度
//              start_row： 起始行号
//			    end_row：   终止行号
//    描述：
//              将起始行号至终止行号的所有G代码行号对应的索引连接起来输出     
//
//    返回： 
//             total_len： 索引总个数（>=0）     
//             -1       :  数组越界
/////////////////////////////////////////////////////////////////////////
int Connect_GRow_Idx(int* out_idx,int arr_len,int start_row,int end_row)
{
	int row_tmp = 0;
	int len_tmp = 0;
	int total_len = 0; //索引总数

	for (row_tmp=start_row; row_tmp<=end_row; row_tmp++)
	{
		len_tmp = find_emtoid_float(out_idx+total_len,row_tmp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
        total_len += len_tmp;
		if(total_len > arr_len) return -1; //数组越界
	}

	return total_len;
}

///////////////////////////////////////////////////////////////////////////////
//
//    create_linspace(int* obj_arr,int start_num,int scale_val,int data_num)
//
//    功能：
//            创建 连续数（等差数组） 数组 （INT型） 
//    参数：
//            int* obj_arr: 目标数组 
//            int arr_length:数组最大长度 
//            int start_num: 连续数起始数字 
//            int scale_val： 连续数前后差值 
//            int data_num：  连续数个数      
//    描述：
//            对应MATLAB   a:i:b 功能 ；
//    返回:
//            0：成功
//            -1:失败 
//////////////////////////////////////////////////////////////////////////
int create_linspace(int* obj_arr,int arr_length,int start_num,int scale_val,int data_num)
{
	int i = 0;
	
	if((obj_arr == NULL) || (data_num < 0) || (data_num>arr_length))
	{
		return -1;
	}
	
	for(i=0;i<data_num;i++)
	{
		*(obj_arr+i) = start_num + i*scale_val;
	}
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int Acce_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, HealSpTy sped_chn)
//
//    功能：	
//              提取加速段索引(从0开始加速)
//    参数：  
//			    out_idex：输出加速段索引数组
//              in_idex:  限定索引数组，在此索引范围内提取加速段
//              in_len:   限定索引数组长度
//              cmdSped:  加速后理论速度
//              err:      允许误差（实际速度与理论速度）
//	            sped_chn: 速度所在采样通道号	VEL_SPIND：主轴速度	  
//    描述：
//              在指定的索引范围内提取 加速段的索引          
//
//    返回： 
//             out_len：加速段索引长度（>=0）     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int Acce_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
	int out_len =0;            //加速段长度（用于返回）
	int consSped_len = 0;      //恒速段长度（指速度达到理论值）
	int* consSped_idx = NULL;  //恒速段索引数组指针
	int react_len = 0;		   //响应段长度（指发出运动指令到开始旋转的段）
	int* react_idx = NULL;	   //响应段索引数组指针
	int acce_start = 0;        //加速段起点索引值
	int acce_end = 0;          //
	int* tmp_idx = NULL;
    int tmp_start = 0;
    int tmp_datanum = 0;
	
	
    consSped_idx = (int *)malloc(in_len*sizeof(int));
	if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);           //correct
	react_idx = (int *)malloc(in_len*sizeof(int));
	if(react_idx == NULL) longjmp(s_SetJmp,MALLOCERR);             //correct
	//找加速段终点（不考虑跃冲，恒速段起点）
    consSped_len =  find_emtoid_float(consSped_idx,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	acce_end = *(consSped_idx);
    //找加速段起点（响应段终点）
	tmp_start = *(in_idex);
	tmp_datanum = acce_end -tmp_start +1;
	tmp_idx = (int *)malloc(tmp_datanum*sizeof(int));
	if(tmp_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
    create_linspace(tmp_idx,tmp_datanum,tmp_start,1,tmp_datanum);
	react_len = find_emtoid_float(react_idx,0,tmp_datanum,tmp_idx,NULL,sped_chn,SIG,err);
	acce_start = *(react_idx+react_len-1);
    //得到加速段索引和加速段长度
    out_len = acce_end -acce_start+1;
    create_linspace(out_idex,out_len,acce_start,1,out_len);
    //退出处理
    free(consSped_idx);
	free(react_idx);
	free(tmp_idx);
	
	return out_len;
}
*/

/////////////////////////////////////////////////////////////////////////
//
//    int Dece_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, HealSpTy sped_chn)
//
//    功能：	
//              提取减速段索引(减速到0)
//    参数：  
//			    out_idex：输出减速段索引数组
//              in_idex:  限定索引数组，在此索引范围内提取减速段
//              in_len:   限定索引数组长度
//              cmdSped:  减速前的理论速度
//	            sped_chn: 速度所在采样通道号	VEL_SPIND：主轴速度	
//              err:      允许误差（实际速度与理论速度）  
//    描述：
//              在指定的索引范围内提取 减速段的索引          
//
//    返回： 
//             out_len：减速段索引长度（>=0）     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int Dece_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
	int out_len =0;            //减速段长度（用于返回）
	int consSped_len = 0;      //恒速段长度（指速度达到理论值）
	int* consSped_idx = NULL;  //恒速段索引数组指针
	int zero_len = 0;		   //回零段长度（指发出运动指令到开始旋转的段）
	int* zero_idx = NULL;	   //回零段索引数组指针
	int dece_start = 0;        //减速段起点索引值
	int dece_end = 0;          //减速段终点索引值
	int* tmp_idx = NULL;
    int tmp_start = 0;
    int tmp_datanum = 0;
	
    consSped_idx = (int *)malloc(in_len*sizeof(int));
    if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	zero_idx = (int *)malloc(in_len*sizeof(int));
	if(zero_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	//找减速段起点（恒速段终点）
    consSped_len =  find_emtoid_float(consSped_idx,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	dece_start = *(consSped_idx+consSped_len-1);
    //找减速段终点（不考虑跃冲，回零段终点）
    tmp_start = *(in_idex);                            //所有索引起点     //correct
	tmp_datanum = in_len -(dece_start-tmp_start);   //开始减速剩余长度  //correct：去掉尾部+1
	tmp_idx = (int *)malloc(tmp_datanum*sizeof(int));
	if(tmp_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
    create_linspace(tmp_idx,tmp_datanum,dece_start,1,tmp_datanum);
	zero_len = find_emtoid_float(zero_idx,0,tmp_datanum,tmp_idx,NULL,sped_chn,SIG,err);
	dece_end = *(zero_idx);
    //得到减速段索引和减速段长度
    out_len = dece_end -dece_start+1;
    create_linspace(out_idex,out_len,dece_start,1,out_len);
    //退出处理
    free(consSped_idx);
	free(zero_idx);
	free(tmp_idx);
	
	return out_len;
}
*/

/////////////////////////////////////////////////////////////////////////
//
//    int consSped_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, HealSpTy sped_chn)
//
//    功能：	
//              提取恒速段索引(减速到0)
//    参数：  
//			    out_idex：输出恒速段索引数组
//              in_idex:  限定索引数组，在此索引范围内提取恒速段
//              in_len:   限定索引数组长度
//              cmdSped:  恒速段的理论速度
//	            sped_chn: 速度所在采样通道号	VEL_SPIND：主轴速度	
//              err:      允许误差（实际速度与理论速度）  
//    描述：
//              在指定的索引范围内提取 恒速段的索引          
//
//    返回： 
//             out_len：恒速段索引长度（>=0）     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int consSped_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
    int out_len =0;            //恒速段长度（用于返回）

	//未考虑加速跃冲的恒速段
    out_len =  find_emtoid_float(out_idex,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	
	return out_len;
}
*/

/////////////////////////////////////////////////////////////////////////
//
//    int SigSpd_AcDc_Ext(float* outftv,int start_row, int end_row,bool isHighSpd = true)
//
//    功能：	单次主轴 （加速-恒速-减速）过程的特征提取
//
//    参数：  
//			    outftv:     输出主轴特征（1.加速时间、2.减速时间、3.电流均值、4.电流波动）
//              start_row:  主轴旋转指令行号（M03、M04）
//              end_row:    主轴停止指令行号（M05下一条指令的G04）
//			    isHighSpd:  是否主轴高速  1、默认：true
//              isPos:      是否正转   1、默认：true
//    描述：
//              对一次主轴加速、恒速、减速过程的特征提取  
//
//    返回： 
//             0：成功     
//
/////////////////////////////////////////////////////////////////////////
/*
int SigSpd_AcDc_Ext(float* outftv,int start_row, int end_row,bool isHighSpd = true,bool isPos = true)
{
	int* acDc_idx = NULL;     //主轴加速-恒速-减速全过程索引
	int acDc_len = 0;         //全过程索引个数
	int maxlen = 0;           //全过程索引最大长度
	int acce_len = 0;       //加速段索引长度
	int* acce_idx = NULL;   //加速索引
	int dece_len = 0;       //减速段索引长度
	int* dece_idx = NULL;   //减速索引
	int consSped_len = 0;   //恒速段索引长度
	int* consSped_idx=NULL; //恒速索引

	int cmdSped = 0;          //理论达到的速度
	float allow_err = 0;      //速度允许误差

	float statis_temp[4] = {0.0};
	int* maxindex = NULL;            //极大值索引
	int* minindex = NULL;            //极小值索引
    int maxNum = 0;                  //极大值个数
	int minNum = 0;                  //极小值个数
	float maxmean = 0.0;             //极大值均值
	float minmean = 0.0;             //极小值均值
    
	//
	maxlen = (end_row-start_row+1)*IIP_NUM;
    acDc_idx = (int*)malloc(maxlen*sizeof(int));
	if(acDc_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	acDc_len =  Connect_GRow_Idx(acDc_idx,maxlen,start_row,end_row);  //全过程索引
	if (isHighSpd)
	{
        cmdSped = isPos?s_hfp.spd_highSped:-s_hfp.spd_highSped;  //correcr:增加正反转判断
		allow_err = HIGHSPDERR;
	} 
	else
	{
        cmdSped = isPos?s_hfp.spd_lowSped:-s_hfp.spd_lowSped;  //correcr:增加正反转判断
        allow_err = LOWSPDERR;
	}
	//加速过程特征提取（加速时间）
	acce_idx = (int*)malloc(maxlen*sizeof(int));
	if(acce_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
    acce_len = Acce_Segmt_Idx(acce_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND);
	*(outftv) = acce_len/s_samplFreq;  //加速时间
	free(acce_idx);
	//减速过程特征提取（减速时间）
    dece_idx = (int*)malloc(maxlen*sizeof(int));
	if(dece_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	dece_len = Dece_Segmt_Idx(dece_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND);
	*(outftv+1) = dece_len/s_samplFreq;  //减速时间
	free(dece_idx);
	//恒速段特征提取（主轴电流均值、主轴电流波动）
    consSped_idx = (int*)malloc(maxlen*sizeof(int));
	if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	consSped_len = consSped_Segmt_Idx(consSped_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND); //correct:  dece_idx ->consSped_idx
	compute_statis_file(statis_temp,NULL,consSped_idx,consSped_len,CUR_SPIND);
	*(outftv+2) = statis_temp[2];//电流均值  //correct: statis_temp[3] ->statis_temp[2]
	  //求波动
	maxindex = (int*)malloc(consSped_len*sizeof(int));
    if(maxindex == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	minindex = (int*)malloc(consSped_len*sizeof(int));
	if(minindex == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	ExtrPoint(maxindex,&maxNum,minindex,&minNum,NULL,consSped_idx,consSped_len,CUR_SPIND);
	compute_statis_file(statis_temp,NULL,maxindex,maxNum,CUR_SPIND);
    maxmean = statis_temp[2];                //correct: statis_temp[3] ->statis_temp[2]
	compute_statis_file(statis_temp,NULL,minindex,minNum,CUR_SPIND);
	minmean = statis_temp[2];                //correct: statis_temp[3] ->statis_temp[2]
    *(outftv+3) = maxmean - minmean;//电流波动
	free(maxindex);
	free(minindex);
    free(consSped_idx);
	free(acDc_idx);

	return 0;
}
*/
/////////////////////////////////////////////////////////////////////////
//
//    int SpdFtvExt()
//
//    功能：	主轴特征提取
//
//    参数：  
//			    无
//			  
//    描述：
//            
//
//    返回： 
//             0：成功     
//
/////////////////////////////////////////////////////////////////////////
/*
int SpdFtvExt()
{
	int i = 0;
	int start_row = 0;
	int end_row = 0;
	int lowpos_times = 0;                   //低速正向起停次数
	float lowpos_ftv[SPDTIME][4] = {0.0};   //各次低速正向时的特征值
	int lowneg_times = 0;
	float lowneg_ftv[SPDTIME][4] = {0.0};   //低速反向
	int highpos_times = 0;
	float highpos_ftv[SPDTIME][4] = {0.0};  //高速正向
	int highneg_times = 0;
	float highneg_ftv[SPDTIME][4] = {0.0};  //高速反向

	float accetime = 0.0;   //加速时间总和
	float decetime = 0.0;   //减速时间总和
	float curmean = 0.0;    //电流均值总和（绝对值之和）
	float curvrib = 0.0;    //电流波动总和

	for (i=0;i<s_hfp.spdnum;i++)
	{
		//低速正转
		start_row = s_hfp.spdrow[0][i][0];
		end_row = s_hfp.spdrow[0][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&lowpos_ftv[i][0],start_row,end_row,false,true);
			lowpos_times++;
			//特征值累加
            accetime = accetime+lowpos_ftv[i][0];
			decetime = decetime+lowpos_ftv[i][1];
			curmean = curmean+fabsf(lowpos_ftv[i][2]);
			curvrib = curvrib+lowpos_ftv[i][3];
		}
		//低速反转
		start_row = s_hfp.spdrow[1][i][0];
		end_row = s_hfp.spdrow[1][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&lowneg_ftv[i][0],start_row,end_row,false,false);
			lowneg_times++;
			//特征值累加
			accetime = accetime+lowneg_ftv[i][0];
			decetime = decetime+lowneg_ftv[i][1];
			curmean = curmean+fabsf(lowneg_ftv[i][2]);
			curvrib = curvrib+lowneg_ftv[i][3];
		}  
		//高速正转
		start_row = s_hfp.spdrow[2][i][0];
		end_row = s_hfp.spdrow[2][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&highpos_ftv[i][0],start_row,end_row,true,true);
			highpos_times++;
			//特征值累加
			accetime = accetime+highpos_ftv[i][0];
			decetime = decetime+highpos_ftv[i][1];
			curmean = curmean+fabsf(highpos_ftv[i][2]);
			curvrib = curvrib+highpos_ftv[i][3];
		}
		//高速反转
		start_row = s_hfp.spdrow[3][i][0];
		end_row = s_hfp.spdrow[3][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&highneg_ftv[i][0],start_row,end_row,true,false);
			highneg_times++;
			//特征值累加
			accetime = accetime+highneg_ftv[i][0];
			decetime = decetime+highneg_ftv[i][1];
			curmean = curmean+fabsf(highneg_ftv[i][2]);
			curvrib = curvrib+highneg_ftv[i][3];
		}
	}

	//主轴特征向量计算
	s_ftv.s_health[0] = accetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //加速时间
	s_ftv.s_health[1] = decetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //减速时间
	s_ftv.s_health[2] = curmean/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //电流均值
	s_ftv.s_health[3] = curvrib/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //电流波动

	return 0;
}
*/
/////////////////////////////////////////////////////////////////////////
//
//    int SigSpd_AcDc_Ext_02(float* outftv,int start_row, int end_row,bool isHighSpd = true)
//
//    功能：	单次主轴 （加速-恒速-减速）过程的特征提取
//					(v2.0 -- 不使用动态分配内存)				
//    参数：  
//			    outftv:     输出主轴特征（1.加速时间、2.减速时间、3.电流均值、4.电流波动）
//              start_row:  主轴旋转指令行号（M03、M04）
//              end_row:    主轴停止指令行号（M05下一条指令的G04）
//			    isHighSpd:  是否主轴高速  1、默认：true
//              isPos:      是否正转   1、默认：true
//    描述：
//              对一次主轴加速、恒速、减速过程的特征提取  
//
//    返回： 
//             0：成功     
//
/////////////////////////////////////////////////////////////////////////
int SigSpd_AcDc_Ext_02(float* outftv,int start_row, int end_row,bool isHighSpd = true,bool isPos = true)
{
	int acce_row_start = 0;     //加速行起点索引（包括系统响应段）
	int dece_row_start = 0;		//减速行起点索引（包括系统响应段）
	int acce_start = 0;			//加速段起点（不包括系统响应段）
	int acce_end = 0;			//加速段终点
	int dece_start = 0;			//减速段起点（不包括系统响应段）
	int dece_end = 0;			//减速段终点
	int cmdSped = 0;            //理论达到的速度
	float allow_err = 0;        //速度允许误差
	int acce_start_sped = 0;		//判断加速段起点的速度
	int dece_start_sped = 0;		//判断减速段起点的速度
	float current_vib = 0.0;
	float statis_temp[4] = {0.0};   //

	int i = 0;
	int temp = 0;

	if (isHighSpd)
	{
        cmdSped = isPos?s_hfp.spd_highSped:-s_hfp.spd_highSped;  //correcr:增加正反转判断
		allow_err = HIGHSPDERR;
	} 
	else
	{
        cmdSped = isPos?s_hfp.spd_lowSped:-s_hfp.spd_lowSped;  //correcr:增加正反转判断
        allow_err = LOWSPDERR;
	}
	acce_start_sped = (int)(isPos?(2*allow_err):(-2*allow_err));
	dece_start_sped = (int)(isPos?(cmdSped - 2*allow_err):(cmdSped + 2*allow_err));
	//加速过程特征提取（加速时间）
	//find_first_element_float_file(&acce_row_start,start_row,s_hfp.TotalData,0,NULL,GODE_ROW);
	//Gcoderow
	for(i=0;i<10;i++)
	{
		//加速行第一点
		if(find_first_element_int_file(&acce_row_start,start_row,s_hfp.TotalData,0,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		//判断索引下个元素是否也是待求元素,如果否,判断此索引为无效
		fseek(s_hfp.pGcoderow,acce_row_start*sizeof(int),SEEK_SET);
		fread(&temp,sizeof(int),1,s_hfp.pGcoderow);
		if(temp == start_row)
		{
			break;
		}
		else
		{
			if(i == 9)
			{
				s_CalThreadErr_No = -8;
				return -1;
			}
		}
	}
	//debug
	if(s_Print_CalDataInlo_Flag)
		fprintf(s_debug_pfile,"主轴加速行%d的行号起始索引：%d\r\n",start_row,acce_row_start);

	find_first_element_float_file(&acce_end,cmdSped,10000,acce_row_start,NULL,VEL_SPIND,allow_err); //加速段终点
	//debug
	if(s_Print_CalDataInlo_Flag)
		fprintf(s_debug_pfile,"主轴加速行%d的行号加速段终点索引：%d\r\n",start_row,acce_end);

	find_first_element_float_file(&acce_start,acce_start_sped,acce_end-acce_row_start+1,acce_row_start,NULL,VEL_SPIND,allow_err); //加速段起点（系统响应段终点）
	*(outftv) = (acce_end - acce_start+1)/s_samplFreq;  //加速时间
	//减速过程特征提取（减速时间）
	//find_first_element_float_file(&dece_row_start,end_row,s_hfp.TotalData-acce_start+1,acce_start,NULL,GODE_ROW);
	//Gcoderow
	for(i=0;i<10;i++)
	{
		//减速行第一点
		if(find_first_element_int_file(&dece_row_start,end_row,s_hfp.TotalData-acce_start+1,acce_start,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		//判断索引下个元素是否也是待求元素,如果否,判断此索引为无效
		fseek(s_hfp.pGcoderow,dece_row_start*sizeof(int),SEEK_SET);
		fread(&temp,sizeof(int),1,s_hfp.pGcoderow);
		if(temp == end_row)
		{
			break;
		}
		else
		{
			if(i == 9)
			{
				s_CalThreadErr_No = -8;
				return -1;
			}
		}
	}

	find_first_element_float_file(&dece_end,0,10000,dece_row_start,NULL,VEL_SPIND,allow_err); //减速段终点
	find_first_element_float_file(&dece_start,dece_start_sped,dece_end-dece_row_start+1,dece_row_start,NULL,VEL_SPIND,allow_err); //减速段起点（系统响应段终点）
	*(outftv+1) = (dece_end - dece_start+1)/s_samplFreq;  //减速时间
	//恒速段特征提取（主轴电流均值、主轴电流波动）
    compute_statis_continuous_infile(statis_temp,dece_start-acce_end+1,acce_end,NULL,CUR_SPIND);
	*(outftv+2) = statis_temp[2];//电流均值
	//求波动
	CalVib_continuous_infile(&current_vib,dece_start-acce_end+1,acce_end,NULL,CUR_SPIND);
	*(outftv+3) = current_vib;//电流波动

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int SpdFtvExt_02()
//
//    功能：	主轴特征提取 -> 修改：无需malloc()
//
//    参数：  
//			    无
//			  
//    描述：
//            
//
//    返回： 
//             0：成功     
//
/////////////////////////////////////////////////////////////////////////
int SpdFtvExt_02()
{
	int i = 0;
	int start_row = 0;
	int end_row = 0;
	int lowpos_times = 0;                   //低速正向起停次数
	float lowpos_ftv[SPDTIME][4] = {0.0};   //各次低速正向时的特征值
	int lowneg_times = 0;
	float lowneg_ftv[SPDTIME][4] = {0.0};   //低速反向
	int highpos_times = 0;
	float highpos_ftv[SPDTIME][4] = {0.0};  //高速正向
	int highneg_times = 0;
	float highneg_ftv[SPDTIME][4] = {0.0};  //高速反向
	
	float accetime = 0.0;   //加速时间总和
	float decetime = 0.0;   //减速时间总和
	float curmean = 0.0;    //电流均值总和（绝对值之和）
	float curvrib = 0.0;    //电流波动总和
	
	for (i=0;i<s_hfp.spdnum;i++)
	{
		//低速正转
		start_row = s_hfp.spdrow[0][i][0];
		end_row = s_hfp.spdrow[0][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&lowpos_ftv[i][0],start_row,end_row,false,true);
			lowpos_times++;
			//特征值累加
            accetime = accetime+lowpos_ftv[i][0];
			decetime = decetime+lowpos_ftv[i][1];
			curmean = curmean+fabsf(lowpos_ftv[i][2]);
			curvrib = curvrib+lowpos_ftv[i][3];
		}
		else
		{
			s_CalThreadErr_No = -14;
			return -1;
		}
		//低速反转
		start_row = s_hfp.spdrow[1][i][0];
		end_row = s_hfp.spdrow[1][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&lowneg_ftv[i][0],start_row,end_row,false,false);
			lowneg_times++;
			//特征值累加
			accetime = accetime+lowneg_ftv[i][0];
			decetime = decetime+lowneg_ftv[i][1];
			curmean = curmean+fabsf(lowneg_ftv[i][2]);
			curvrib = curvrib+lowneg_ftv[i][3];
		} 
		else
		{
			s_CalThreadErr_No = -14;
			return -1;
		}
		//高速正转
		start_row = s_hfp.spdrow[2][i][0];
		end_row = s_hfp.spdrow[2][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&highpos_ftv[i][0],start_row,end_row,true,true);
			highpos_times++;
			//特征值累加
			accetime = accetime+highpos_ftv[i][0];
			decetime = decetime+highpos_ftv[i][1];
			curmean = curmean+fabsf(highpos_ftv[i][2]);
			curvrib = curvrib+highpos_ftv[i][3];
		}
		else
		{
			s_CalThreadErr_No = -14;
			return -1;
		}
		//高速反转
		start_row = s_hfp.spdrow[3][i][0];
		end_row = s_hfp.spdrow[3][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&highneg_ftv[i][0],start_row,end_row,true,false);
			highneg_times++;
			//特征值累加
			accetime = accetime+highneg_ftv[i][0];
			decetime = decetime+highneg_ftv[i][1];
			curmean = curmean+fabsf(highneg_ftv[i][2]);
			curvrib = curvrib+highneg_ftv[i][3];
		}
		else
		{
			s_CalThreadErr_No = -14;
			return -1;
		}
	}
	
	//主轴特征向量计算
	s_ftv.s_health[0] = accetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //加速时间
	s_ftv.s_health[1] = decetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //减速时间
	s_ftv.s_health[2] = curmean/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //电流均值
	s_ftv.s_health[3] = curvrib/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //电流波动
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//    int vector_normal(float* obj_vector, float* min_Arr, float* max_Arr, int vector_length)
//
//    功能：
//            对向量的每一个值按照对应标准分别进行归一化
//    参数：
//            float* obj_vector :要归一化的向量
//            float* min_Arr :归一化标准--最小值   -> 0
//            float* max_Arr :归一化标准--最大值   -> 1
//            int vector_length :向量长度
//    描述：
//            
//    返回:
//            0:成功
//            -1: 空指针
//            -2 ：向量长度<=0   
//////////////////////////////////////////////////////////////////////////
int vector_normal(float* obj_vector, float* min_Arr, float* max_Arr, int vector_length)
{
    int i = 0;

	if(obj_vector==NULL || min_Arr==NULL || max_Arr==NULL)return -1;
	if(vector_length <= 0)return -2;

	for (i = 0;i < vector_length;i++)
	{
		if(*(max_Arr+i) == *(min_Arr+i))  //correct:增加除零判断
		{
			*(obj_vector+i) = *(max_Arr+i);
		}
		else
		{
           *(obj_vector+i) = (*(obj_vector+i) - *(min_Arr+i))/(*(max_Arr+i) - *(min_Arr+i));
		}		
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int feature_normaled(FeatureVec *obj_feature,FeatureVec *min_normalStd,FeatureVec *max_normalStd)
//
//    功能：
//            按照FeatureVec结构体对所有特征向量归一化
//    参数：
//            FeatureVec *obj_feature :要归一化的特征向量结构体
//            FeatureVec *min_normalStd :归一化标准--最小值   -> 0
//            FeatureVec *max_normalStd :归一化标准--最大值   -> 1
//   
//    描述：
//            
//    返回:
//            0:成功
//            -1: 空指针
//            -2 ：向量归一化失败 
//////////////////////////////////////////////////////////////////////////
int feature_normaled(FeatVec *obj_feature,FeatVec *min_normalStd,FeatVec *max_normalStd)
{
	if(obj_feature==NULL || min_normalStd==NULL || max_normalStd==NULL)return -1;

    if(vector_normal(obj_feature->x_health, min_normalStd->x_health, max_normalStd->x_health, X_VEC_LENGTH) < 0)return -2;
    if(vector_normal(obj_feature->y_health, min_normalStd->y_health, max_normalStd->y_health, Y_VEC_LENGTH) < 0)return -2;
	if(vector_normal(obj_feature->z_health, min_normalStd->z_health, max_normalStd->z_health, Z_VEC_LENGTH) < 0)return -2;
	if(vector_normal(obj_feature->s_health, min_normalStd->s_health, max_normalStd->s_health, S_VEC_LENGTH) < 0)return -2;
	if(vector_normal(obj_feature->t_health, min_normalStd->t_health, max_normalStd->t_health, T_VEC_LENGTH) < 0)return -2;

    return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
//
//    float cal_Euclidean_distance(float *vector_1, float *vector_2, int vector_length)
//
//    功能：
//            计算两个向量间的欧式距离（向量必须同长度）
//    参数：
//            float *vector_1 :向量1
//            float *vector_2 :向量2
//            int vector_length :向量长度
//   
//    描述：
//            d = (v1 - v2)(v1 -v2)'
//    返回:
//            euclid_dis:欧式距离 （>=0）
//            -1: 空指针
//            -2 ：向量长度<=0 
/////////////////////////////////////////////////////////////////////////////////
float cal_Euclidean_distance(float *vector_1, float *vector_2, int vector_length)
{
    int i = 0;
	float quadratic_sum = 0.0;
	float euclid_dis = 0.0;
	
	if(vector_1==NULL || vector_2==NULL)return -1;
	if(vector_length <= 0)return -2;

	for (i=0;i<vector_length;i++)
	{
		quadratic_sum = quadratic_sum + (*(vector_1+i) - *(vector_2+i))*(*(vector_1+i) - *(vector_2+i));
	}

    euclid_dis = sqrtf(quadratic_sum);
    return euclid_dis;
}

///////////////////////////////////////////////////////////////////////////////
//
//    float logsig(float number)
//
//    功能：
//            logsig映射函数
//    参数：
//            float number: 待映射的数
//   
//    描述：
//            logsig(n) = 1 / (1 + exp(-n))
//    返回:
//            transfer_num: logsig映射后的结果
//////////////////////////////////////////////////////////////////////////
float logsig(float number)
{
	float cons_e = 2.7182818284;
	float transfer_num = 0.0;

	transfer_num = 1/(1+powf(cons_e,-number));

	return transfer_num;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int CalHealthIndex(float* healthIndex)
//
//    功能：
//            根据提取的各部件特征值向量与基准向量，计算各部件的健康指数
//    参数：
//            healthIndex: 健康指数计算结果，依次为：X轴、Y轴、Z轴、主轴、刀库、机床
//   
//    描述：
//            
//    返回:
//            0：计算成功
//////////////////////////////////////////////////////////////////////////
int CalHealthIndex(float* healthIndex)
{
	FeatVec standard_vec = {0}; //计算基准
    FeatVec cal_vec = {0};      //本次提取的特征，避免修改s_ftv

	//将本次特征向量和基准向量归一化
	memcpy(&standard_vec,&s_hfp.feat_base,FEATURE_STRUCT_SIZE);
	memcpy(&cal_vec,&s_ftv,FEATURE_STRUCT_SIZE);
    if(feature_normaled(&standard_vec,&s_hfp.feat_min,&s_hfp.feat_max) <0 )
	{
		s_CalThreadErr_No = -21;
		return -1;
	}
	if(feature_normaled(&cal_vec,&s_hfp.feat_min,&s_hfp.feat_max) <0 )
	{
		s_CalThreadErr_No = -21;
		return -1;
	}
	//计算主轴健康指数
	*(healthIndex) = cal_Euclidean_distance(cal_vec.s_health, standard_vec.s_health, S_VEC_LENGTH)/S_VEC_LENGTH; 
	*(healthIndex) = 2*logsig(-(*(healthIndex)));
	//计算X轴健康指数
	*(healthIndex+1) = cal_Euclidean_distance(cal_vec.x_health, standard_vec.x_health, X_VEC_LENGTH)/X_VEC_LENGTH; 
	*(healthIndex+1) = 2*logsig(-(*(healthIndex+1)));
	//计算Y轴健康指数
	*(healthIndex+2) = cal_Euclidean_distance(cal_vec.y_health, standard_vec.y_health, Y_VEC_LENGTH)/Y_VEC_LENGTH; 
	*(healthIndex+2) = 2*logsig(-(*(healthIndex+2)));
	//计算Z轴健康指数
	*(healthIndex+3) = cal_Euclidean_distance(cal_vec.z_health, standard_vec.z_health, Z_VEC_LENGTH)/Z_VEC_LENGTH; 
	*(healthIndex+3) = 2*logsig(-(*(healthIndex+3)));
	//计算刀库健康指数
	*(healthIndex+4) = cal_Euclidean_distance(cal_vec.t_health, standard_vec.t_health, T_VEC_LENGTH)/T_VEC_LENGTH; 
	*(healthIndex+4) = 2*logsig(-(*(healthIndex+4)));
	//计算机床健康指数
    *(healthIndex+5) = (*(healthIndex) + *(healthIndex+1) + *(healthIndex+2) + *(healthIndex+3) + *(healthIndex+4))/5;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int resetHistoryFile()
//
//    功能：
//            当生成新基准时，重新计算历史的健康指数
//    参数：
//            
//   
//    描述：
//            根据新生成的基准与归一化标准，重新计算历史的健康指数
//    返回:
//            0：成功
//            -1:
//            -2:
//////////////////////////////////////////////////////////////////////////
int resetHistoryFile()
{
	FILE *p_historyFile = NULL;
	Bit8 filePath[128] = {0};
	Bit8 historyfilename[128] = {0};
	fBit32 healthIndex_buf[6] = {0.0}; //pancl
	Bit32 i=0;
	
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, filePath);
	sprintf(historyfilename, "%s%c%s", filePath, DIR_SEPARATOR, "historyIndexData.SV");
	p_historyFile = fopen(historyfilename, "wb");

	//重新取出以前的特征向量，计算并保存健康指数
	fseek(s_hfp.pstdfile,sizeof(int)+3*FEATURE_STRUCT_SIZE,SEEK_SET);
	for (i=0;i<RESET_STD_TIMES - 1; i++)//仅对以前的重写，本次不重写
	{
		//对以前特征重新计算健康指数
		fread(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
		CalHealthIndex(healthIndex_buf);
		//存入历史健康指数
		fseek(p_historyFile,6*i*sizeof(fBit32),SEEK_SET);
		fwrite(healthIndex_buf,sizeof(fBit32),6,p_historyFile);
	}

	//重新读出本次特征，待后续按未生成新基准流程求健康指数
	fread(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fclose(p_historyFile);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//
//    int resetStdFile()
//
//    功能：
//            自生成基准文件
//    参数：
//            
//   
//    描述：
//            当自检模块在机床运行30次时，重新根据本机床特征生成基准
//    返回:
//            0：成功
//            -1:
//            -2:
//////////////////////////////////////////////////////////////////////////
int resetStdFile()
{
	Bit32 i = 0, j = 0;
	Bit32 data_off = 0;
	struct stat finfo;
	fBit32 ftv_buf[RESET_STD_TIMES][VEC_TOTAL_LENGTH] = {0.0}; //历次所有特征值缓存
	fBit32 ftv_base[VEC_TOTAL_LENGTH] = {0.0};  //新基准-比较值
	fBit32 ftv_max[VEC_TOTAL_LENGTH] = {0.0};   //归一化-最大值
	fBit32 ftv_min[VEC_TOTAL_LENGTH] = {0.0};   //归一化-最小值
	fBit32 scale_cof = 0.2; //缩放系数

	//获取基准文件信息
	if(stat(s_hfp.stdfilename, &finfo) <0)
	{
		//s_CalThreadErr_No = -1;
		return -1;
	}

	data_off = (Bit32)(sizeof(int)+3*FEATURE_STRUCT_SIZE);//基准文件头偏移量（历史次数+1个基准向量+2个归一化向量）
	//文件实际大小与预期一致则重新计算机床新基准
	if (finfo.st_size == (data_off+s_hfp.historyTestNum*FEATURE_STRUCT_SIZE) )
	{
		fseek(s_hfp.pstdfile,data_off,SEEK_SET);

		for (i =0;i<RESET_STD_TIMES;i++)
		{
			fread(&ftv_buf[i][0],FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
			//重计算新基准与归一化标准
			if (i == 0)
			{
				memcpy(ftv_max,&ftv_buf[0][0],FEATURE_STRUCT_SIZE);
				memcpy(ftv_min,&ftv_buf[0][0],FEATURE_STRUCT_SIZE);
			}

			for (j=0;j<VEC_TOTAL_LENGTH;j++)
			{
				//新基准
				ftv_base[j] += ftv_buf[i][j];
				//归一化->最大值
				if(ftv_buf[i][j] > ftv_max[j]) 
					ftv_max[j] = ftv_buf[i][j];
				//归一化->最小值
				if(ftv_buf[i][j] < ftv_min[j]) 
					ftv_min[j] = ftv_buf[i][j];
			}
		}

		//处理生成新基准与归一化标准
		for (j=0;j<VEC_TOTAL_LENGTH;j++)
		{
			ftv_base[j] = ftv_base[j]/RESET_STD_TIMES;
			ftv_max[j] = ftv_max[j]*(1+scale_cof);
			ftv_min[j] = ftv_min[j]*(1-scale_cof);
		}	
	} 
	else
	{
		return -2; //基准文件大小与数据个数不一致
	}

	//新基准与归一化标准写入基准文件
	fseek(s_hfp.pstdfile,sizeof(int),SEEK_SET);
	fwrite(ftv_base,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fwrite(ftv_max,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fwrite(ftv_min,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);

	//更新参数结构体中的数据
	memcpy(&s_hfp.feat_base,ftv_base,FEATURE_STRUCT_SIZE);
	memcpy(&s_hfp.feat_max,ftv_max,FEATURE_STRUCT_SIZE);
	memcpy(&s_hfp.feat_min,ftv_min,FEATURE_STRUCT_SIZE);

	//根据新基准重新计算历次健康指数
	resetHistoryFile();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int SaveFeaVec()
//
//    功能：
//            本次计算的特征向量保存到基准文件中
//    参数：
//            
//   
//    描述：
//            
//    返回:
//            0：成功
//            -1:写入失败
//////////////////////////////////////////////////////////////////////////
int SaveFeaVec()
{
	if(s_hfp.pstdfile == NULL)
	{
		s_CalThreadErr_No = -18;
		longjmp(s_SetJmp,NULL_POINTER);//文件指针为空
	}
	//自检次数加1
	s_hfp.historyTestNum++;
    fseek(s_hfp.pstdfile,0,SEEK_SET);
	if(fwrite(&s_hfp.historyTestNum,sizeof(int),1,s_hfp.pstdfile) != 1) 
	{
		s_CalThreadErr_No = -19;
		return -1;
	}
	//写入本次自检的特征向量
    fseek(s_hfp.pstdfile,0,SEEK_END);
	if(fwrite(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) 
	{
		s_CalThreadErr_No = -20;
		return -1;
	}
	//判断是否需要重写基准
	if (s_hfp.historyTestNum == RESET_STD_TIMES)
	{
		fflush(s_hfp.pstdfile);
		resetStdFile();
	}

	//关闭基准文件
	fclose(s_hfp.pstdfile);
	s_hfp.pstdfile = NULL;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//
//    int HealthTestCalExit()
//
//    功能：
//            健康诊断计算模块退出处理
//    参数：
//            
//   
//    描述：
//            
//    返回:
//            0：成功
//            -1:采样数据文件关闭失败
//////////////////////////////////////////////////////////////////////////
int HealthTestCalExit()
{
	//关闭采样数据文件，指针置空
	if( 0 != fclose(s_hfp.pdatafile))
	{
		s_CalThreadErr_No = -22;
		return -1;
	}
	s_hfp.pdatafile = NULL;
	remove(s_hfp.filename);

	return 0;
}

/*
void debug_open_simpleFile()
{
	FILE *fp = NULL;
    char simpleFileName_1[128] = "123_pan.txt";
	char simpleFileName_2[128] = "O_pan.txt";
	char filename_tmp[128] = {'\0'};
	char gCodePath[128] = {'\0'};

	HNC_SysCtrlGetConfig(HNC_SYS_CFG_PROG_PATH, gCodePath);
	sprintf(filename_tmp,"%s%c%s",gCodePath,DIR_SEPARATOR,simpleFileName_1);		//G代码文件
	fp = fopen(filename_tmp,"r");
	if (fp == NULL)
	{
		s_CalThreadStep_No = 101;
	} 
	else
	{
		s_CalThreadStep_No = 102;
	}
	
	CalThread_StepPrint_Refresh();
	fclose(fp);
	fp = NULL;

	HNC_SysCtrlGetConfig(HNC_SYS_CFG_PROG_PATH, gCodePath);
	sprintf(filename_tmp,"%s%c%s",gCodePath,DIR_SEPARATOR,simpleFileName_2);		//G代码文件
	fp = fopen(filename_tmp,"r");
	if (fp == NULL)
	{
		s_CalThreadStep_No = 103;
	} 
	else
	{
		s_CalThreadStep_No = 104;
	}
	CalThread_StepPrint_Refresh();
	fclose(fp);
}
*/

///////////////////////////////////////////////////////////////////////////////
//
//    void CalThread_StepPrint_Refresh(bool reset_tmp_No) 
//
//    功能：
//            计算线程的计算过程刷新打印
//    参数：
//            reset_tmp_No：是否重置内部局部静态变量  默认fault:不重置
//   
//    描述：
//            
//    返回:
//            无
//////////////////////////////////////////////////////////////////////////
void CalThread_StepPrint_Refresh(bool reset_tmp_No) 
{
	static int tmp_No;  //局部静态，步骤标记->记录刷新到的步骤

	Bit32 height = 0;
	Bit32 width = 0;
	Bit32 left = 0;
	Bit32 top = 0;
	Bit8 info_tmp[256] = {0};
	FILE *fp = NULL;

	Bit8 dataPath[128] = {'\0'};
	Bit8 fullname[128] = {'\0'};
	Bit8 filename[128]  = "CalStep_Print.txt";

	//重置内部局部静态变量为0
	if (reset_tmp_No)   
	{
		tmp_No = 0;  
		return;
	}
	//已经打印最新的计算步骤，不刷新
	if (tmp_No == s_CalThreadStep_No)
	{
		return;     
	}

	height = (USER_BOTTOM-USER_TOP)/20;
	width = (USER_RIGHT - USER_LEFT);
	//根据步骤号打印信息
	if (s_CalThreadStep_No > 0)     //无异常步骤
	{
		left = USER_LEFT;
		switch (s_CalThreadStep_No)
		{
		case 1:
			sprintf(info_tmp,"步骤 1: %s\r\n","参数初始化 正常");
			top = USER_TOP+0*height;
			break;
		case 2:
			sprintf(info_tmp,"步骤 2: %s\r\n","解析G代码 正常");
			top = USER_TOP+1*height;
			break;
		case 3:
			sprintf(info_tmp,"步骤 3: %s\r\n","读采样数据文件 正常");
			top = USER_TOP+2*height;
			break;
		case 4:
			sprintf(info_tmp,"步骤 4: %s\r\n","解析R116寄存器信号 正常");
			top = USER_TOP+3*height;
			break;
		case 5:
			sprintf(info_tmp,"步骤 5: %s\r\n","解析基准文件 正常");
			top = USER_TOP+4*height;
			break;
		case 6:
			sprintf(info_tmp,"步骤 6: %s\r\n","刀库特征提取 正常");
			top = USER_TOP+5*height;
			break;
		case 7:
			sprintf(info_tmp,"步骤 7: %s\r\n","主轴特征提取 正常");
			top = USER_TOP+6*height;
			break;
		case 8:
			sprintf(info_tmp,"步骤 8: %s\r\n","进给轴（X/Y/Z）特征提取 正常");
			top = USER_TOP+7*height;
			break;
		case 9:
			sprintf(info_tmp,"步骤 9: %s\r\n","保存本次特征向量 正常");
			top = USER_TOP+8*height;
			break;
		case 10:
			sprintf(info_tmp,"步骤 10: %s\r\n","健康指数计算 正常");
			top = USER_TOP+9*height;
			break;
		case 11:
			sprintf(info_tmp,"步骤 11: %s\r\n","计算过程退出处理 正常");
			top = USER_TOP+10*height;
			break;
		default:
			sprintf(info_tmp,"default: %s\r\n","缺省值");
			top = USER_TOP+11*height;
			break;
		}
	}
	else    // 异常步骤
	{
		left = USER_LEFT;
		switch (s_CalThreadStep_No)
		{
		case -1:
			sprintf(info_tmp,"步骤 1: %s\r\n","参数初始化 异常:获取采样文件信息失败!");
			top = USER_TOP+0*height;
			break;

		case -2:
			sprintf(info_tmp,"步骤 2: %s\r\n","解析G代码 异常:G代码打开失败!");
			top = USER_TOP+1*height;
			break;
		case -3:
			sprintf(info_tmp,"步骤 2: %s\r\n","解析G代码 异常:G代码提取刀库相关参数失败!");
			top = USER_TOP+1*height;
			break;
		case -4:
			sprintf(info_tmp,"步骤 2: %s\r\n","解析G代码 异常:G代码提取进给轴相关参数失败!");
			top = USER_TOP+1*height;
			break;
		case -5:
			sprintf(info_tmp,"步骤 2: %s\r\n","解析G代码 异常:G代码提取主轴相关参数失败!");
			top = USER_TOP+1*height;
			break;

		case -6:
			sprintf(info_tmp,"步骤 3: %s\r\n","读采样数据文件 异常:打开采样数据文件失败!");
			top = USER_TOP+2*height;
			break;

		case -7:
			sprintf(info_tmp,"步骤 4: %s\r\n","解析R116寄存器信号 异常:R116中间点位文件打开失败!");
			top = USER_TOP+3*height;
			break;
		case -8:
			sprintf(info_tmp,"步骤 4: %s\r\n","解析R116寄存器信号 异常:未找到换刀所在行数据!");
			top = USER_TOP+3*height;
			break;
		case -9:
			sprintf(info_tmp,"步骤 4: %s\r\n","解析R116寄存器信号 异常:某点位信号全为0 !");
			top = USER_TOP+3*height;
			break;

		case -10:
			sprintf(info_tmp,"步骤 5: %s\r\n","解析基准文件 异常:基准文件打开失败!");
			top = USER_TOP+4*height;
			break;
		case -11:
			sprintf(info_tmp,"步骤 5: %s\r\n","解析基准文件 异常:数据读取失败!");
			top = USER_TOP+4*height;
			break;

		case -12:
			sprintf(info_tmp,"步骤 6: %s\r\n","刀库特征提取 异常:中间文件打开失败!");
			top = USER_TOP+5*height;
			break;
		case -13:
			sprintf(info_tmp,"步骤 6: %s\r\n","刀库特征提取 异常:未找到换刀行对应数据点!");
			top = USER_TOP+5*height;
			break;

		case -14:
			sprintf(info_tmp,"步骤 7: %s\r\n","主轴特征提取 异常:行号不大于0 !");
			top = USER_TOP+6*height;
			break;

		case -15:
			sprintf(info_tmp,"步骤 8: %s\r\n","进给轴（X/Y/Z）特征提取 异常:X轴特征提取失败!");
			top = USER_TOP+7*height;
			break;
		case -16:
			sprintf(info_tmp,"步骤 8: %s\r\n","进给轴（X/Y/Z）特征提取 异常:Y轴特征提取失败!");
			top = USER_TOP+7*height;
			break;
		case -17:
			sprintf(info_tmp,"步骤 8: %s\r\n","进给轴（X/Y/Z）特征提取 异常:Z轴特征提取失败!");
			top = USER_TOP+7*height;
			break;

		case -18:
			sprintf(info_tmp,"步骤 9: %s\r\n","保存本次特征向量 异常:基准文件指针为空!");
			top = USER_TOP+9*height;
			break;
		case -19:
			sprintf(info_tmp,"步骤 9: %s\r\n","保存本次特征向量 异常:写入历史自检次数失败!");
			top = USER_TOP+9*height;
			break;
		case -20:
			sprintf(info_tmp,"步骤 9: %s\r\n","保存本次特征向量 异常:写入本次特征向量失败!");
			top = USER_TOP+9*height;
			break;

		case -21:
			sprintf(info_tmp,"步骤 10: %s\r\n","健康指数计算 异常:归一化失败!");
			top = USER_TOP+8*height;
			break;

		case -22:
			sprintf(info_tmp,"步骤 11: %s\r\n","计算过程退出处理 异常:关闭采样数据文件失败!");
			top = USER_TOP+10*height;
			break;

		default:
			sprintf(info_tmp,"default: %s\r\n","缺省值");
			top = USER_TOP+11*height;
			break;
		}
	}
	//
	cstr_out_mul_line(left,top,width,height,info_tmp,COLOR_TEXT,COLOR_BACK,textLEFT,IS12);

	tmp_No = s_CalThreadStep_No;

	//根据需要，选择是否记录计算步骤到文件
	if (s_Print_CalStep_Flag)
	{
		HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, dataPath);
		sprintf(fullname,"%s%c%s",dataPath,DIR_SEPARATOR,filename);
		fp = fopen(fullname,"at");
		fputs(info_tmp,fp);
		fclose(fp);
	}
	

	return;
}

///////////////////////////////////////////////////////////////////////////////
//
//    void CalThread_Step_Set(int step_No) 
//
//    功能：
//            计算线程的计算过程设置，并在界面显示
//    参数：
//            step_No： 计算过程编号
//   
//    描述：
//            
//    返回:
//            无
//////////////////////////////////////////////////////////////////////////
void CalThread_Step_Set(int step_No) 
{
	// 计算过程编号设置
	s_CalThreadStep_No = step_No;
	//计算过程显示界面刷新
	CalThread_StepPrint_Refresh();

	return;
}

//Gcoderow
int ParseGcodeRow()
{
	int i=0;
	float tmp = 0.0;
	int tem = 0;

	s_hfp.pGcoderow = fopen(s_hfp.GcoderowFilename,"wb+");
	if(s_hfp.pGcoderow == NULL)
	{
		printf("open GcodeRow file err!\n");
		s_CalThreadErr_No = -6;
		longjmp(s_SetJmp,OPENFILEERR);
	}

	for (i=0;i<s_hfp.TotalData;i++)
	{
		fseek(s_hfp.pdatafile,(i*s_hfp.chn_num+GODE_ROW)*EUNIT+SAMPDATA_OFFSET,SEEK_SET);
		if(1 != fread(&tmp,EUNIT,1,s_hfp.pdatafile))
		{
			printf(" read GcodeRow file err!\n");
			s_CalThreadErr_No = -6;
			longjmp(s_SetJmp,OPENFILEERR);
		}
		tem = (int)tmp;
		if(1 !=fwrite(&tem,sizeof(int),1,s_hfp.pGcoderow))
		{
			printf(" read GcodeRow file err!\n");
			s_CalThreadErr_No = -6;
			longjmp(s_SetJmp,OPENFILEERR);
		}
	}

	fflush(s_hfp.pGcoderow);

	return 0;
}

//Gcoderow
void GcoderowExit()
{
	fclose(s_hfp.pGcoderow);
	s_hfp.pGcoderow = NULL;
	remove(s_hfp.GcoderowFilename);
}

void CalThread_debug_init()
{

	char tmpPath[128] = {'\0'};
	char filename[128] = "Cal_DataInfo_Record.txt";
	char debugfilename[128] = {'\0'};
	
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, tmpPath);
	sprintf(debugfilename,"%s%c%s",tmpPath,DIR_SEPARATOR,filename);

	s_debug_pfile = fopen(debugfilename,"at");
}

// void CalThread_debug(FILE* fp,char format[],char info[])
// {
// 	fprintf(fp,format,info);
// }

void CalThread_debug_exit()
{
	fclose(s_debug_pfile);
	s_debug_pfile = NULL;
}