/*
//�ļ����ƣ�HealthFtvExt.cpp
//�ļ���ʶ��
//ժ    Ҫ������ָ��������ȡ
//����ƽ̨��linux/winxp
//
//��    ����1.00
//��    �ߣ��ܺ�
//��    �ڣ�2016��8��15��
//˵    ����
//
//��    ����1.10
//��    �ߣ��˳���
//��    �ڣ�2016��9��13��
//˵    �������ӣ�1��������������ȡ
//                2������������ȡ
//                3������ָ������
*/

//win7 64λϵͳ��6G�ڴ棬���꽡��ָ��Լ81.78��

/*    20160918���ɲ����޸ģ�
��1��Ԥ���룺����#include "stdafx.h"��ע��//#include <stdio.h>��
��2��ͷ�ļ�������extern int HealIdexTest()�Ⱥ���������
��3��·���ָ����޸ģ����ж��Ƿ�linux������#define DIR_SEPARATOR '\\'��
��4���ļ�·���޸ģ�HEALTHPATH��
��5������int HealIdexTest()�������ݣ����в��ԣ�
��6������int ReadGFile_Feed(FILE* pfile)�޸ģ�����G������Լ����
��7������int ReadGFile_Spd(FILE* pfile)�޸ģ�����G������Լ����
��8������int ReadGFile_Feed(FILE* pfile)��������ģʽ�������кŴ���˳��ߵ���posLowNum++;
��9������int ReadGFile_Spd(FILE* pfile)��������ģʽ�������кŴ���˳��ߵ���
��10������int ParseR116()�������Ĵ�����λ�ļ��򿪷�ʽ"rb" -> "wb"->"wb+"
��11���ṹ��HealthFtvPar���ӻ�׼�ļ���stdfilename
��12������int read_std_file()�������йش��ļ���
��13������void initparam(char* fname, int chnnum)���ӣ���׼�ļ�����ʼ��
��14���궨�壬����SAMPDATA_OFFSET���������ݵĳ�ʼƫ����
��15��(����Ļ�)���к����ж������ļ�s_hfp.pdatafile����fseek()������SEEK_SET -> SAMPDATA_OFFSET (error)
��16�����к����ж������ļ�s_hfp.pdatafile����fseek()�������ڶ�����offset���ӳ�ʼƫ����SAMPDATA_OFFSET 
��17������int ParseR116()����, �������м��ļ�ͳһ����float������ int ->float
��18������int ParseR116()���ӣ��ļ�д�����ļ��������Ĵ���fflush()
��19���궨�����ӣ��жϸ�������ȵľ�����ֵ 
��20������void initparam(char* fname, int chnnum)�����������������㿼�ǵ�һ������ͨ��������Ӱ��
��21������int find_emtoid�����������βι��ھ��ȵ�Ĭ��ֵ���½��ش����ļ���������жϡ�������һ��
��22������int ToolFtvExt()�������м��ļ��򿪷�ʽ ��wb��->"wb+"
��23������int ToolFtvExt()������ѡ����ʼ��������������forѭ�� -> ���ú���
��24������compute_statis_file()�������󷽲�ʱ���ָ�������������������£�float -> double
��25������compute_statis_array()��������߼��㾫�ȣ�float -> double
��26������int ToolFtvExt()������Z������м��ļ���fopen()��������sfname->zfname
��27������Dece_Segmt_Idx()������Ѱ�Ҽ��ٶ��յ㣬Ӧ�ӿ�ʼ��������
��28���궨�壬����ߵ���������� HIGHSPDERR��LOWSPDERR�� 10,30-> 20,40
��29������SigSpd_AcDc_Ext()��������ȡ���ٶ�����ʱ���������� dece_idx ->consSped_idx
��30������SigSpd_AcDc_Ext()���ӣ�������������ת���жϣ���תת��Ϊ��
��31����������������malloc()���������жϣ�ʧ�ܷ���-5��
��32������int ReadGFile_Spd(FILE* pfile)���ӣ���ȡ����ߵ���ת�٣�
��33������ReadGFile_MO6()�����������������ж� M06 -> T
��34������ReadGFile_Feed()����������G�������G����궨���Լ������߿���ֲ��
��35������ReadGFile_Spd()����������G�������G����궨���Լ������߿���ֲ��
��36������������һ�������㽡��ָ������
��37������ToolFtvExt()���ӣ��رղ�ɾ���м��ļ�
��38�����Ӻ���HealthTestCalExit()��������ϼ���ģ���˳�����
��39������ExtrPoint()��������ֵ����idx+1 ->idx-1
��40������ToolFtvExt()���ӣ����ӳ�ϴ�м��ļ�������fflush()
��41������ExtrPoint()�޸ģ��β��������ڷ��صļ���ֵ��������Сֵ���������ú�������Ӧ�޸�
��42������ToolFtvExt()�޸ģ�����ѡ��ʱ��ʱ+1
��43������ToolFtvExt()�޸ģ���������������ֵ������std_tmp[3] -> std_tmp[1]
��44�������쳣������ƣ�����תsetjmp()-longjmp()ʵ��
��45�����Ӻ궨�壬�Գ����������쳣���errNO
-------------------------------[����hnc8��]--------------------------------------------
��46������CalHealthIndex()���ӣ����Ӽ����������ָ��
��47������HealIdexTestCal()�޸ģ��β����� ���������ļ���������ָ��
��48������vector_normal()�޸ģ����ӳ����ж�
��49���ṹ��HealthFtvPar���ӣ����ӻ�׼�ļ����ļ�ָ��pstdfile����ʷ��ϴ���historyTestNum
��50������read_std_file()�޸ģ���׼�������ļ�ָ���Ϊs_hfp�еĻ�׼�ļ�ָ�롢ɾ���رջ�׼�ļ�
��51������read_std_file()���ӣ����Ӷ�ȡ��ʷ��ϴ���historyTestNum
*/

/*//���޸�
(1)(���)����int ReadGFile_Spd(FILE* pfile)���ӣ���ȡ����ߵ���ת�٣�
(2)(��ʱ���Ķ�)����ת�ٸ�Ϊfloat��
(3)(���)��G�����޸�Ϊ�궨����ʽ
(4)(���)��׼�ļ�"standard_file.bin"����������
(5)(���)���������ļ�.SV ��һ������Ϊͨ��������δ����  =�����ӳ�ʼƫ����
(6)(���)���������ļ�.SV ��������1000�ı�����ϵ��mA -> A��;��Ƹ������޸�
(7)(��ʱ��Ϊ27000)�궨��IIP_NUM����̫�٣�����17000�������ң����ٽ���27000���� ����޸�  
(8)(���)�����õ��м��ļ�δ�ر�ʱ�������в������ļ�����������Ҫ�ر��ļ���������ļ�������
(9)(���)R116�ļĴ����м��ļ�int�ͣ���Ԫ��ʱfloat�ͣ����ͳһ
(10)(���)�����������Ĺ�һ���������㽡��ָ��
(11)(���)����ֵ���롢��׼�Զ����ɸ���
(12)(�������)�쳣�����������
(13)(���)����������ֵ�����Բ���ֵӰ��ϴ�
--->(14)������������ȡʱδ���ǼӼ��ٹ��̣��Ժ��ٶ���Ӱ��
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


// ·���ָ���
//#define DIR_SEPARATOR '\\'
#ifdef _LINUX
#define DIR_SEPARATOR '/'
// #define HEALTHPATH	"../tmp"	//��������ʱ�������м��ļ�(ֱ��д·����һ��\��Ϊ�����ַ�������)
// #define GFILEPATH   "../prog"              //G����·��
#else
#define DIR_SEPARATOR '\\'
// #define HEALTHPATH			"..\\tmp"	//��������ʱ�������м��ļ�(ֱ��д·����һ��\��Ϊ�����ַ�������)
// #define GFILEPATH           "..\\prog"              //G����·��
#endif

//G����궨���Լ��
#define X_NEG_LIMIT   "#101"      //X�Ḻ��λ
#define X_POS_LIMIT   "#102"       
#define Y_NEG_LIMIT   "#103"      
#define Y_POS_LIMIT   "#104"
#define Z_NEG_LIMIT   "#105"
#define Z_POS_LIMIT   "#106"
#define SPD_LOW_SPED  "#107"      //������ٶ�
#define SPD_HIGH_SPED "#108"  
#define FED_LOW_SPED  "#109"      //��������ֱ�߲岹 ��������ٶȣ��ϳ��ٶȣ�
#define FED_HIGH_SPED "#110"
#define XOY_FED_LOW_SPED  "#111"    //XOYƽ�滭Բ ��������ٶȣ��ϳ��ٶȣ�
#define XOY_FED_HIGH_SPED  "#112"

#define HEALTHGCOD			"OHealthTest.txt"		//��������G�����ļ���		
#define STD_VET_FNAME		"standard_file.SV"		//��׼�ļ� 
#define R1161				"R116_1.bin"			//R116�����ļ�
#define R1164				"R116_4.bin"
#define R1166				"R116_6.bin"
#define R1167				"R116_7.bin"
#define TOOLTIME			50						//��󻻵�����
#define FEEDTIME            3                       //ĳ��������������򣩵��������������ߵ��١�������*4��
#define SPDTIME             5                       //ĳ�������������ת�������������ͣ�������ߵ��١�����ת*4��
#define HIGHSPDERR          40                      //�����������ת�����
#define LOWSPDERR           20                      //�����������ת�����
#define FLOAT_EQUAL         0.01                //�жϸ�������ȵľ�����ֵ
#define RESET_STD_TIMES     30                  //����30�κ��������û�׼

#define	EUNIT				sizeof(float)			//�������ļ������ڴ浥Ԫ
#define IIP_NUM				27000 //10000					//�����岹����?? @@@@@@@@@@�ܻ����ʦ

#define SAMPDATA_OFFSET     (1*sizeof(long int))    //�����ļ������з�ͨ�����ݣ�ͨ���������µ�ƫ����

#define max(a,b)    (((a) > (b)) ? (a) : (b))       //���ֵ����
#define min(a,b)    (((a) < (b)) ? (a) : (b))       //��Сֵ����

#define TRY      if(!(s_ErrNo = setjmp(s_SetJmp)))              //�ó���ת�����쳣����         
#define CATCH    else                               //�ó���ת�����쳣����

//�����쳣
#define MALLOCERR      -5          //malloc�����ڴ����
#define OPENFILEERR    -6          //�ļ���ʧ��
#define NULL_POINTER   -7          //��ָ��


////////////////////////////////////////////////////////////////////////////////
//            
//
//    ��ע: ��ǲ���˳�����ͨ������˳�����仯��ֻ��Ҫ�޸�ö�ٱ�����Ӧ��ֵ
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
	SIG,		//ĳ��Ԫ��
	EUP,		//������
	EDN,		//�½���
}EDGE;

typedef struct _HealthFtvPar
{
	int TotalData;			//��ͨ��������������
	int  chn_num;			//����ͨ����Ŀ
	int historyTestNum;     //��ʷ��ϴ���  correct:add

	//�ļ�
	char filename[128];			//���������ļ���
	FILE* pdatafile;           //���������ļ�ָ��
	char stdfilename[128];		 //��׼�ļ���  //correct
	FILE* pstdfile;              //��׼�����ļ�ָ��
	char gcodefile[128];		//G�����ļ���

	//Gcoderow
	char GcoderowFilename[128];
	FILE* pGcoderow; //int��
	
	//tool feature 
	char toolfile[4][128];		//R116_1;R116_4;R116_6;R116_7;
	FILE* ptoolfile[4];
	int toolchgnum;				//��������
	int toolrow[TOOLTIME];		//�����кţ���󻻵�����100

	//feed feature
    int feednum;                 //�岹����feednum=�������=�������=�������=������ٴ�����G���뱣֤һ�£�
	int feedrow[4][FEEDTIME];    //�岹�кţ�[0][]:��������[1][]:���ٷ���[2][]:��������[3][]:���ٷ���

    //Spindle feature
	int spd_highSped;            //�������ת��
	int spd_lowSped;             //�������ת��
	int spdnum;                  //��ͣ���� = ��ת����=��ת����=��ת����=��ת���ٴ�������һ��ʱȡ���Ĵ�����
	int spdrow[4][SPDTIME][2];   //������ͣ�кţ���һά��[0]:��������[1]:���ٷ���[2]:��������[3]:���ٷ���
	                             //              �ڶ�ά������һάģʽ����ͣ����
	                             //              ����ά��[0]:��ʼ��ת�кţ�M03��M04��,[1]:ֹͣ�кţ�M05��һ�е�G04��
    //�����׼����
	FeatVec feat_base;
	FeatVec feat_min;
	FeatVec feat_max;
} HealthFtvPar;

static HealthFtvPar s_hfp;							//������ȡ����
static FeatVec		s_ftv;							//��������
static float  s_samplFreq = 1000.0;                 //����Ƶ��
static jmp_buf s_SetJmp;                            //����תbuff
static int  s_ErrNo;                                //�쳣�����󣩱�� 

//���㲽���ţ�����Ϊ�������裬����Ϊ�쳣���裩
static int s_CalThreadStep_No = 0; 
static int s_CalThreadErr_No = 0; 
//�Ƿ��¼���������Ϣ��־
static bool s_Print_CalStep_Flag = true;     //��¼���㲽��
static bool s_Print_CalDataInlo_Flag = true; //��¼�������������Ϣ

static FILE* s_debug_pfile = NULL; //��¼�������������Ϣ�ļ�ָ��

//----------------------------------------------//

/////////////////////////////////////////////////////////////////////////
//
//    int HealIdexTestCal(float* healthIndex)
//
//    ���ܣ�
//           ������ϼ���ģ��
//
//    ������
//           healthIndex: ����ָ��������������Ϊ��X�ᡢY�ᡢZ�ᡢ���ᡢ���⡢����  
//           sampDatFile: �����ļ���������·����
//           chunNum:     ����ͨ����
//    ������
//                     
//
//    ���أ�
//           MALLOCERR(-5)    :malloc()�쳣
//           OPENFILEERR(-6)  :�ļ��򿪳���
//           NULL_POINTER(-7) :��ָ��
//           -1               :��������    
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
		//(1)������ʼ��
		ret = initparam(sampDatFile,chunNum);
		if (ret == 0)
		{
			CalThread_Step_Set(1);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-1
		}
		
		 //(2)��������G�����ļ�
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
			fprintf(s_debug_pfile,"����������%d\r\n",s_hfp.toolchgnum);
			fprintf(s_debug_pfile,"��һ�������кţ�%d\r\n",s_hfp.toolrow[0]);
			fprintf(s_debug_pfile,"���һ�������кţ�%d\r\n",s_hfp.toolrow[s_hfp.toolchgnum -1]);
		}

		//(3)�����������ļ�
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
		
		//(4)����R116�Ĵ����ź�
   		ret = ParseR116();                     
		if (ret == 0)
		{
			CalThread_Step_Set(4);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-7~-9
		}

		//(5)����������׼�ļ�
   		ret = read_std_file();                 
		if (ret == 0)
		{
			CalThread_Step_Set(5);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-10~-11
		}
        
		//(6)����������ȡ
		ret = ToolFtvExt();
		if (ret == 0)
		{
			CalThread_Step_Set(6);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-12~-13
		}

		//(7)����������ȡ
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

		//(8)�����ᣨX/Y/Z��������ȡ
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
			fprintf(s_debug_pfile," ��������:(1)����ʱ�䣺%f (2)����ʱ�䣺%f (3)������ֵ��%f (4)����������%f \r\n",s_ftv.s_health[0],s_ftv.s_health[1],s_ftv.s_health[2],s_ftv.s_health[3]);
			fprintf(s_debug_pfile," X������:(1)���پ�ֵ��%f (2)���ٲ���%f (3)���پ�ֵ%f (4)���ٲ�����%f (5)������%f (6)�س���%f \r\n",s_ftv.x_health[0],s_ftv.x_health[1],s_ftv.x_health[2],s_ftv.x_health[3],s_ftv.x_health[4],s_ftv.x_health[5]);
			fprintf(s_debug_pfile," Y������:(1)���پ�ֵ��%f (2)���ٲ���%f (3)���پ�ֵ%f (4)���ٲ�����%f (5)������%f (6)�س���%f \r\n",s_ftv.y_health[0],s_ftv.y_health[1],s_ftv.y_health[2],s_ftv.y_health[3],s_ftv.y_health[4],s_ftv.y_health[5]);
			fprintf(s_debug_pfile," Z������:(1)���پ�ֵ��%f (2)���ٲ���%f (3)���پ�ֵ%f (4)���ٲ�����%f (5)������%f (6)�س���%f \r\n",s_ftv.z_health[0],s_ftv.z_health[1],s_ftv.z_health[2],s_ftv.z_health[3],s_ftv.z_health[4],s_ftv.z_health[5]);
			fprintf(s_debug_pfile," ��������:(1)�ض��������%f (2)�ܻ���ʱ��%f (3)�����ᶨ��ʱ��%f (4)��ѡ��ʱ�䣺%f (5)���������ֵ��%f (6)Z�������ֵ��%f \r\n",s_ftv.t_health[0],s_ftv.t_health[1],s_ftv.t_health[3],s_ftv.t_health[5],s_ftv.t_health[7],s_ftv.t_health[11]);
		}
		//(9)���汾����������
        ret = SaveFeaVec();
		if (ret == 0)
		{
			CalThread_Step_Set(9);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-18~-20
		} 

		//(10)����ָ������                           
		ret = CalHealthIndex(healthIndex);
		if (ret == 0)
		{
			CalThread_Step_Set(10);
		}
		else
		{
			CalThread_Step_Set(s_CalThreadErr_No);   //-21
		}

		//(11)��������˳�����
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
		case MALLOCERR: //malloc()�쳣
			memset(healthIndex,0,5*sizeof(float));
			printf("malloc() error !!!");
			CalThread_StepPrint_Refresh();
			return MALLOCERR;
			break;
		case OPENFILEERR: //�ļ���ʧ��
			memset(healthIndex,0,5*sizeof(float));
			printf("open file error !!!");
			CalThread_StepPrint_Refresh();
			return OPENFILEERR;
			break;
		case NULL_POINTER: //ʹ�ÿ�ָ��
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
//    ���ܣ�
//            ��ȡG�����ļ�: ��ȡ���������ͻ������ڵ��к�
//
//    ������
//            pfile�� G�����ļ�ָ��
//    ������
//            �������s_hfp.toolrow��           
//
//    ���أ�
//            -1����ǰ�޻�����0��������������
//
//////////////////////////////////////////////////////////////////////////
int ReadGFile_MO6(FILE* pfile)
{
	char line[1024] = {0};
    int gCodeRowNum = 0; //G�����к� 

	fseek(pfile,0,SEEK_SET);
	while(!feof(pfile))
	{
		gCodeRowNum++;
		memset(line,0,sizeof(line));
		fgets(line,sizeof(line),pfile);

		if((strstr(line,"T")!=NULL) || (strstr(line,"t")!=NULL) ) //����������  �ӹ����Ļ���ָ��M06T()  //correct: M06 -> T
        {
			if(s_hfp.toolchgnum>=0) //����¼��һ�λ������ų���ʼ��λ���� 
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
//    ���ܣ�
//            ��ȡG�����ļ�: ��ȡ�岹�����кͲ岹��������
//
//    ������
//            pfile�� G�����ļ�ָ��
//    ������
//            �������s_hfp.feedrow��      
//
//    ���أ�
//            -1������������ƥ�䣻
//             0��������������
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
    int gCodeRowNum = 0;     //G�����к� 
    bool isG01 = false;      //�Ƿ�G01
	bool isFeedPos = false;  //�Ƿ��������
	bool isFeedNeg = false;  //�Ƿ������
	bool isFeedHigh = false; //�Ƿ���ٽ���
	bool isFeedLow = false;  //�Ƿ���ٽ���
    int  posHighNum  =0;     //������������ĸ���
	int  posLowNum  =0;
	int  negHighNum  =0;
	int  neglowNum  =0;

	//����G����궨��Լ����G��������õ��ַ���   //correct: add
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
		if (isG01) //�岹���������н�һ���ж�
		{
			isFeedNeg=(strstr(line,strFedNeg_1)!=NULL)||(strstr(line,strFedNeg_2));   //#101Լ��ΪX������λ����X�Ḻ���˶��жϽ�������
			isFeedPos=(strstr(line,strFedPos_1)!=NULL)||(strstr(line,strFedPos_2));   //�ж��Ƿ�����

			isFeedHigh=(strstr(line,strFeedHig_1)!=NULL)||(strstr(line,strFeedHig_2));  //�ж��Ƿ����//F[#115]
			isFeedLow=(strstr(line,strFeedLow_1)!=NULL)||(strstr(line,strFeedLow_2));   //             F[#116]
			if (isFeedLow)
			{
				if (isFeedPos)
				{//�����������
					s_hfp.feedrow[0][posLowNum] = gCodeRowNum;  //correct
					posLowNum++;
				}
				else if (isFeedNeg)
				{//���ٸ������
					s_hfp.feedrow[1][neglowNum] = gCodeRowNum;  //correct
					neglowNum++;
				}
			}
			else if (isFeedHigh)
			{
				if (isFeedPos)
				{//�����������
					s_hfp.feedrow[2][posHighNum] = gCodeRowNum;  //correct
					posHighNum++;
				}
				else if (isFeedNeg)
				{//���ٸ������
                    s_hfp.feedrow[3][negHighNum] = gCodeRowNum;  //correct
					negHighNum++;
				}
			}
		}

	}

	if(posLowNum == neglowNum == posHighNum == negHighNum)
	{//�ߵ��������������
		s_hfp.feednum = posLowNum;
	}
	else
	{
		return -1;   //���������������
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int ReadGFile_Spd(FILE* pfile)
//
//    ���ܣ�
//            ��ȡG�����ļ�: ��ȡ���Ὺʼ��ת�ͽ�����ת�������кš�������ͣ����
//
//    ������
//            pfile�� G�����ļ�ָ��
//    ������
//            �������s_hfp.spdrow��           
//             
//    ���أ�
//             0���ɹ���
//            -1��ָֹͣ�������ָͣ�
//            -2�������𶯡�ֹͣ������ƥ��
//////////////////////////////////////////////////////////////////////////
int ReadGFile_Spd(FILE* pfile)
{
    char line[1024] = {0};            //G����ÿ�е�����
	char* tmp = NULL;
	int i=0;
    int gCodeRowNum = 0;		      //G�����к� 
	int startNum = 0;			      //���Ὺʼת��ָ�������M03��M04��
	int endNum = 0;			          //����ֹͣת��ָ�������M05��
	int startRow[4*SPDTIME][3] = {0}; //��һ�д����Ὺʼ��ת�кţ��ڶ��б������ת��1����ת��-1����ת����������ά��Ǹߵ��٣�1�����٣�-1�����٣�
	int endRow[4*SPDTIME] = {0};      //����ֹͣת�������к�
	bool isPosRot = false;			  //������ת ��M03��
	bool isNegRot = false;			  //������ת ��M04��
	//bool isRotStart = false;		  //�Ƿ����Ὺʼ��ת
	bool isRotEnd = false;			  //�Ƿ�����ֹͣת����M05��
	bool isRotPause = false;		  //�Ƿ���ͣ��רָM05����һ����ͣ��  ��G04��
	bool isHighSped = false;		  //�Ƿ��������
	bool isLowSped = false;			  //�Ƿ��������
	bool isLowSpedSet = false;        //�Ƿ�������������ú궨��
	bool isHighSpedSet = false;       //�Ƿ�������������ú궨��
	fpos_t  origPos;				  //��¼�ļ�ָ���λ��
	int lowPosNum = 0;                //���������ת����
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
	
	//����G����궨��Լ����G��������õ��ַ���   //correct: add
	sprintf(strLowSpedSet_1, "%s%s", SPD_LOW_SPED, "="); // ��������ת�ٵĺ궨��
	sprintf(strLowSpedSet_2, "%s%s", SPD_LOW_SPED, " ="); 
	sprintf(strHigSpedSet_1, "%s%s", SPD_HIGH_SPED, "="); // 
	sprintf(strHigSpedSet_2, "%s%s", SPD_HIGH_SPED, " ="); 
	sprintf(strLowSped_1, "%s%s%s", "S[",SPD_LOW_SPED, "]"); //��ȡ����ת���к�
	sprintf(strLowSped_2, "%s%s%s", "s[",SPD_LOW_SPED, "]"); 
	sprintf(strHigSped_1, "%s%s%s", "S[",SPD_HIGH_SPED, "]"); 
	sprintf(strHigSped_2, "%s%s%s", "s[",SPD_HIGH_SPED, "]"); 

	fseek(pfile,0,SEEK_SET);
	while(!feof(pfile))
	{
		gCodeRowNum++;
		memset(line,0,sizeof(line));
		fgets(line,sizeof(line),pfile);
		
		//��ȡ����ߵ�ת��
		isLowSpedSet = (strstr(line,strLowSpedSet_1)!=NULL)||(strstr(line,strLowSpedSet_2)!=NULL);   //correct: add
		isHighSpedSet = (strstr(line,strHigSpedSet_1)!=NULL)||(strstr(line,strHigSpedSet_2)!=NULL);

		if (isLowSpedSet)//�����ת�ٺ궨��
		{
			tmp = strtok(line,"=");
			if(tmp !=NULL) tmp = strtok(NULL,";");
			if(tmp !=NULL) s_hfp.spd_lowSped = atoi(tmp);
		}

		if (isHighSpedSet)//�����ת�ٺ궨��
		{
			tmp = strtok(line,"=");
			if(tmp !=NULL) tmp = strtok(NULL,";");
			if(tmp !=NULL) s_hfp.spd_highSped = atoi(tmp);
		}

		//��ȡ����ת���к�
		isPosRot = (strstr(line,"M03")!=NULL)||(strstr(line,"M3")!=NULL);
		isNegRot = (strstr(line,"M04")!=NULL)||(strstr(line,"M4")!=NULL);
        isRotEnd = (strstr(line,"M05")!=NULL)||(strstr(line,"M5")!=NULL);
		//isRotPause = (strstr(line,"G04")!=NULL)||(strstr(line,"g04")!=NULL);
		isLowSped = (strstr(line,strLowSped_1)!=NULL)||(strstr(line,strLowSped_2)!=NULL);   //#110
		isHighSped = (strstr(line,strHigSped_1)!=NULL)||(strstr(line,strHigSped_2)!=NULL);  //#111

		//��ȡ���Ὺʼת���кţ�����Ǹߵ��١�����ת
		if (isPosRot || isNegRot)
		{//���Ὺʼת���к�
			if (isPosRot)
			{
				if (isLowSped)
				{//��ת������
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = 1;
					startRow[startNum][2] = -1;
					startNum++; //correct
				} 
				else if(isHighSped)
				{//��ת������
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = 1;
					startRow[startNum][2] = 1;
					startNum++; //correct
				}
			}
			else
			{
				if (isLowSped)
				{//��ת������
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = -1;
					startRow[startNum][2] = -1;
					startNum++; //correct
				} 
				else if(isHighSped)
				{//��ת������
                    startRow[startNum][0] = gCodeRowNum;
					startRow[startNum][1] = -1;
					startRow[startNum][2] = 1;
					startNum++; //correct
				}
			}
		}

		//��ȡ����ֹͣ�к�
		if (isRotEnd)
		{
			fgetpos(pfile,&origPos); //��¼ָ�뵱ǰλ��
			memset(line,0,sizeof(line));
		    fgets(line,sizeof(line),pfile);//��ȡ��һ�е�����
			isRotPause = (strstr(line,"G04")!=NULL)||(strstr(line,"G4")!=NULL);
			if (isRotPause)//M05��һ�н�G04
			{
				endRow[endNum] = gCodeRowNum;  //+1;  //����������ȡ��ʹ�ö�̬�����ڴ���޸�
				endNum++;  //correct
			}
			else
			{
				return -1;  //ָֹͣ�������ָͣ��
			}
            fsetpos(pfile,&origPos); //��ԭ�ļ�ָ��λ��
		}
	}
    /*-----------------[while end]------------------------*/
	
	//������ͣ�кŴ���
    if (endNum == startNum)
    {
		for (i=0;i<startNum;i++)
		{
			if (startRow[i][2] == -1)//����
			{
				if (startRow[i][1] == 1)
				{//������ת
                    s_hfp.spdrow[0][lowPosNum][0] = startRow[i][0];
					s_hfp.spdrow[0][lowPosNum][1] = endRow[i];
					lowPosNum++; //correct
				} 
				else if(startRow[i][1] == -1)
				{//���ٷ�ת
                    s_hfp.spdrow[1][lowNegNum][0] = startRow[i][0];
					s_hfp.spdrow[1][lowNegNum][1] = endRow[i];
					lowNegNum++; //correct
				}
			}
			else if (startRow[i][2] == 1)//����
			{
				if (startRow[i][1] == 1)
				{//������ת
                    s_hfp.spdrow[2][HighPosNum][0] = startRow[i][0];
                    s_hfp.spdrow[2][HighPosNum][1] = endRow[i];
					HighPosNum++; //correct
				} 
				else if(startRow[i][1] == -1)
				{//���ٷ�ת
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
		return -2; //������ͣ������ƥ��
    }
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    void ReadGFile()
//
//    ���ܣ�
//            ��ȡG�����ļ�: 1.���������ȡ��
//                           2.����ֱ���˶�������ȡ
//							 3.����Բ���в�����ȡ
//
//    ������
//
//    ������
//            G�����ļ�ֻ��Ҫ�ڳ�ʼ����һ�Σ���ȡ��ɾͿ��Թر�
//
//    ���أ�
//           0:  �ɹ�
//          -1:  G�����ļ���ʧ��
//          -2:  ��ز�����ȡʧ��
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
	
	//���������ȡ
	if(ReadGFile_MO6(pgfile) < 0) 
	{
		s_CalThreadErr_No = -3;
		return -2;
	}
    //����
	if(ReadGFile_Feed(pgfile) < 0)
	{
		s_CalThreadErr_No = -4;; 
		return -2;
	}
		
	//����
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
//    ���ܣ�
//            ��������������ʼ��
//							 
//
//    ������1�����������ļ���, G�����ļ��� (�̶�)
//			2��ͨ����Ŀ     3��ͨ������(ö�ٱ���)
//
//    ������
//            
//
//    ���أ�
//			0:�ɹ�    
//			-1:��ȡ�����ļ���Ϣʧ��
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

	//��ʼ���ļ���
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, dataPath);
	sprintf(s_hfp.filename,"%s%c%s",dataPath,DIR_SEPARATOR,filename);			//�����ļ�
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, gCodePath);
	sprintf(s_hfp.gcodefile,"%s%c%s",gCodePath,DIR_SEPARATOR,HEALTHGCOD);		//G�����ļ�
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, stdPath);
	sprintf(s_hfp.stdfilename,"%s%c%s",stdPath,DIR_SEPARATOR,STD_VET_FNAME); //��׼�ļ� //correct
	//Gcoderow
	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, gCodePath);
	sprintf(s_hfp.GcoderowFilename,"%s%c%s",gCodePath,DIR_SEPARATOR,"Gcoderow.SV");		//G�����ļ�

	//��������
	if(stat(s_hfp.filename, &finfo) <0)
	{
		s_CalThreadErr_No = -1;
		return -1;
	}
	s_hfp.TotalData = (finfo.st_size-SAMPDATA_OFFSET)/s_hfp.chn_num/EUNIT;     //correct
	//tool��R116���������ļ� 
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
//    ���ܣ�
//            ��ȡ���������ļ� 
//							 
//
//    ������
//			
//
//    ������
//            
//
//    ���أ� 
//           
//
/////////////////////////////////////////////////////////////////////////
int ReadSampFile()
{

	// �򿪲�������������ļ�
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
//    ���ܣ�
//            �Ӹ������ļ���ָ����ʼ��ͳ��ȵ�����������˳����� ��һ��Ŀ��Ԫ�ض���� ����
//		         				 
//
//    ������    out_first_index     :����������ҵ���һ��Ŀ��Ԫ�ص�����
//              obj_element			:Ҫ���ҵ�Ԫ�ض���
//				find_len			:��������ĳ���
//				find_start			:���������������ֵ
//             	fp			 :ָ���м��ļ��в���     1.NULL ��ʾ�Ӳ��������ļ��в���
//				idx_chn=0~15 : ���������ļ�ָ��ͨ������; 
//						16   :   �м��ļ���������
//              arrow_err    : �������Ĭ��ΪFLOAT_EQUAL
//
//    ������
//            
//    ���أ� 
//            0: �ɹ�
//			 -1: δ�ҵ�����,out_first_index����-1
/////////////////////////////////////////////////////////////////////////
int find_first_element_float_file(int* out_first_index,int obj_element,int find_len,int find_start = 0,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT,float arrow_err=FLOAT_EQUAL)
{

	int		i=0;
	float	tmp=0.0;
	int		idx=0;
	int filelen = 0;
	
	*(out_first_index)= -1;

	if(idx_chn < CHN_COUNT)		//�����ļ�
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
	else						//�����������м��ļ�
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

	if(*(out_first_index) < 0) return -1; //δ�ҵ�Ŀ��Ԫ��
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int find_first_element_int_file(int* out_first_index,int obj_element,int find_len,
//                            int find_start = 0,FILE* fp=NULL)									
//    ���ܣ�
//            �����������ļ���ָ����ʼ��ͳ��ȵ�����������˳����� ��һ��Ŀ��Ԫ�ض���� ����
//		         				 
//
//    ������    out_first_index     :����������ҵ���һ��Ŀ��Ԫ�ص�����
//              obj_element			:Ҫ���ҵ�Ԫ�ض���
//				find_len			:��������ĳ���
//				find_start			:���������������ֵ
//             	fp			 :ָ���м��ļ��в���     1.NULL ��ʾ�Ӳ��������ļ��в���
//
//    ������
//            
//    ���أ� 
//            0: �ɹ�
//			 -1: δ�ҵ�����,out_first_index����-1
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
	
	if(*(out_first_index) < 0) return -1; //δ�ҵ�Ŀ��Ԫ��
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int compute_statis_file(float* out_value, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    ���ܣ�
//            �����ļ����������ݼ���ָ����ʼ��ͳ��ȵ����������ͳ�Ʒ���ֵ��1.��Сֵ; 2.���ֵ; 3.��ֵ; 4.����
//							 (��������ϴ󣬲�����������������)	
//
//    ������  out_value	:ͳ�Ʒ���ֵ����ָ��(����==4)
//			  fp		:�ļ�ָ��
//			  section_len	:ָ������
//			  start_idx		:ָ��������ʼ��    NULL:��ʾ���ļ�ͷ��ʼ			  
//			  idx_chn=0~15  : ���������ļ�ָ��ͨ������; 
//						16  :   �м��ļ���������
//    ������
//            ����std=sqrt(E(X^2)-E^2(X)) ,ֻ��һ��forѭ�� 
//
//    ���أ� 1
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
		
	if(idx_chn < CHN_COUNT)		//�����ļ�
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
					fmin=(double)tmp;						//��Сֵ
				
				if(fmax<tmp)
					fmax=(double)tmp;						//���ֵ
			}
		}
		
		fmean = fsum/section_len;							//��ֵ  warning:δ���г����жϣ�ilen ==0���벻��forѭ����
		fstd=sqrt(fsum2/section_len - fmean*fmean);		//������  warning:���ָ������������(������ʧ���£���Ϊdouble������)

	}else						//�����������м��ļ���һ�������ļ���
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
					fmin= (double)tmp;					//��Сֵ
				
				if(fmax<tmp)
					fmax= (double)tmp;					//���ֵ 
			}
		}
		
		fmean = fsum/section_len;								//��ֵ
		fstd=sqrt(fsum2/section_len - fmean*fmean);			//������
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
//    ���ܣ�
//            �Ӹ����ļ���ָ���������ĳ��Ԫ�ض�Ӧ������(���������غ��½���)
//							 
//
//    ������    idex     :�������
//              element  :Ҫ���ҵ�Ԫ�ض���
//				len		 :��������ĳ���
//				pos		 :���������Ӧ������ 1.NULL ��ָ������
//             	fp		 :ָ���ļ��в���     1.NULL ��ʾ�Ӳ��������ļ��в���
//				idx_chn=0~15: ���������ļ�ָ��ͨ������; 
//						16:   �м��ļ���������
//				eg:  SIG:����Ԫ��, DN:�½���, UP:������
//              arrow_err: �������Ĭ��Ϊ0
//
//    ������
//            
//
//    ���أ�  count:ʵ�ʲ��ҵ��ĸ���
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


	if(idx_chn < CHN_COUNT)		//��ά�����ļ�
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
	else						//һ�������ļ�
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
				
				if(eg==SIG)			//��Ԫ��
				{
					if(fabs(tmp-element) <= arrow_err)//(tmp==element)
					{
						*(idex+count)=idx;
						count++;
					}
				}
				else if(eg==EDN)	//���½���
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
//    ���ܣ�
//            �������ļ���ָ���������ĳ��Ԫ�ض�Ӧ������(���������غ��½���)
//							 
//
//    ������    idex     :�������
//              element  :Ҫ���ҵ�Ԫ�ض���
//				len		 :��������ĳ���
//				pos		 :���������Ӧ������ 1.NULL ��ָ������
//             	fp		 :ָ���ļ��в���     1.NULL ��ʾ�Ӳ��������ļ��в���
//				eg:  SIG:����Ԫ��, DN:�½���, UP:������
//
//    ������
//            
//
//    ���أ�  count:ʵ�ʲ��ҵ��ĸ���
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
			
			if(eg==SIG)			//��Ԫ��
			{
				if(tmp==element)
				{
					*(idex+count)=idx;
					count++;
				}
			}
			else if(eg==EDN)	//���½���
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
//    ���ܣ�
//            �����ļ����������ݼ���ָ�����е�ͳ�Ʒ���ֵ��1.��Сֵ; 2.���ֵ; 3.��ֵ; 4.����
//							 
//
//    ������  out_value��ͳ�Ʒ���ֵ����ָ��(����==4)
//			  fp		:�ļ�ָ��
//			  pos		:ָ������  NULL:��ʾһά�ļ�������Ҫָ������
//			  len		:ָ������
//			  idx_chn	:ָ��ͨ�� (��ά)
//    ������
//            ����std=sqrt(E(X^2)-E^2(X)) ,ֻ��һ��forѭ�� 
//
//    ���أ� 1
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
	
	if(idx_chn < CHN_COUNT)		//��ά�����ļ�
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
					fmin=(double)tmp;						//��Сֵ
				
				if(fmax<tmp)
					fmax=(double)tmp;						//���ֵ
			}
		}
		
		fmean = fsum/ilen;							//��ֵ  warning:δ���г����жϣ�ilen ==0���벻��forѭ����
		fstd=sqrt(fsum2/ilen - fmean*fmean);		//������  warning:���ָ������������(������ʧ���£���Ϊdouble������)

	}else						//һ�������ļ�
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
					fmin= (double)tmp;					//��Сֵ
				
				if(fmax<tmp)
					fmax= (double)tmp;					//���ֵ 
			}
		}
		
		fmean = fsum/ilen;								//��ֵ
		fstd=sqrt(fsum2/ilen - fmean*fmean);			//������
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
//    ���ܣ�
//            �����������ݼ���ָ�����е�ͳ�Ʒ���ֵ��1.��Сֵ; 2.���ֵ; 3.��ֵ; 4.����
//							 
//
//    ������  out_array��ͳ�Ʒ���ֵ����ָ��(����==4)
//			  farry		:����ָ��
//			  flen		:���鳤��
//			  pos		:ָ������  NULL:����Ҫָ������
//			  len		:ָ������
//    ������
//            
//
//    ���أ� 1
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

	fmean = fsum/ilen;								//��ֵ
	fstd=sqrt(fsum2/ilen - fmean*fmean);				//������


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
//    ���ܣ�
//            �����ļ������ݺϲ�
//							 
//
//    ������  outfile	:����ļ� 
//			  infile	:�����ļ�
//			  pos		:ָ������  NULL:����Ҫָ������
//			  len		:ָ������
//			  idx_chn	:ָ��ͨ�� (��ά)
//    ������
//            
//
//    ���أ� 1
//           
//
/////////////////////////////////////////////////////////////////////////
int merge_new_file(FILE* outfile,FILE* infile,int *pos,int len,HealSpTy idx_chn=CHN_COUNT)
{
	int i=0,idx=0;
	float tmp=0;

	if(idx_chn<CHN_COUNT) //���������ԴΪ�����ļ�����
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
	}else   //���������ԴΪ�����ļ�����
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
//    ���ܣ�	����������ȡ
//
//    ������  
//			  
//			  
//    ������
//            
//
//    ���أ� 
//           0:�ɹ�   
//			 -1:δ�ҵ�G�����Ӧ����
/////////////////////////////////////////////////////////////////////////
int ToolFtvExt()
{
	int i = 0;
	int toolrow=0;
	int sigtoollen=0;						//���λ�����Ӧ�岹�еĳ���
	int iip_grow[IIP_NUM]={0};				//���λ�����Ӧ�Ĳ岹������

	int chg_time[IIP_NUM]={0}, spd_ortime[IIP_NUM]={0}, chs_beg[10]={0},chs_end[10]={0};
	float tlChgTime[TOOLTIME] = {0};		//���λ���ʱ�� 
	float spdleOrTime[TOOLTIME] = {0};		//�������ᶨ��ʱ�� 
	float chsTolTime[TOOLTIME] = {0};		//����ѡ��ʱ��
	int   chsTolIdx_tmp[IIP_NUM]={0};       //����ѡ������      
	float spdcur_std[TOOLTIME] ={0};		//���ζ����������	
	float zCur_std[TOOLTIME] = {0};			//����ѡ��ʱ Z���������
	float   reOrtNum[TOOLTIME] = {0};		//���ᶨ����� 
	float std_tmp[4]={0};
	FILE *fspdcur=NULL, *fzcur=NULL;
	char sfname[128]={0};				//���л������ض����������
	char zfname[128]={0};				//ѡ������Z�����
	char tmpPath[128] = {0};


	HNC_SysCtrlGetConfig(HNC_SYS_CFG_TEMP_PATH, tmpPath);
	sprintf(sfname,"%s%c%s",tmpPath,DIR_SEPARATOR,"or_spdcur.bin");  //���ᶨ��ʱ����
	sprintf(zfname,"%s%c%s",tmpPath,DIR_SEPARATOR,"ct_zcur.bin");    //����ѡ��ʱZ�����

	fspdcur = fopen(sfname,"wb+");  //correct  "wb" -> "wb+"
	fzcur = fopen(zfname,"wb+");    //correct  "wb" -> "wb+"   "sfname" ->"zfname"
	if(fzcur == NULL || fspdcur == NULL) 
	{
		s_CalThreadErr_No = -12;
		longjmp(s_SetJmp,OPENFILEERR);
	}

	for(i=0;i<s_hfp.toolchgnum;i++)
	{
		//��ʼ��
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
			fprintf(s_debug_pfile,"�����к�Ϊ%d�ĳ��ȣ�%d\r\n",toolrow,sigtoollen);

		if(sigtoollen>0)
		{
			tlChgTime[i] = (float)find_emtoid_float(chg_time,1,sigtoollen,iip_grow,s_hfp.ptoolfile[0],CHN_COUNT,SIG)/s_samplFreq;			//116.1 :����ʱ��
			//debug
			if(s_Print_CalDataInlo_Flag)
				fprintf(s_debug_pfile,"�����к�Ϊ%d�Ļ���ʱ�䣺%f\r\n",toolrow,tlChgTime[i]);

			spdleOrTime[i] = (float)find_emtoid_float(spd_ortime,1,sigtoollen,iip_grow,s_hfp.ptoolfile[2],CHN_COUNT,SIG)/s_samplFreq;		//116.6 :���ᶨ��ʱ��
			compute_statis_file(std_tmp,NULL,spd_ortime,(int)(spdleOrTime[i]*s_samplFreq),CUR_SPIND);		//����ʱ���������min\max\mean\std
			spdcur_std[i] = std_tmp[3];
			merge_new_file(fspdcur,NULL,spd_ortime,(int)(spdleOrTime[i]*s_samplFreq),CUR_SPIND);

			find_emtoid_float(chs_beg,1,sigtoollen,iip_grow,s_hfp.ptoolfile[1],CHN_COUNT,EDN);			//116.4:�½���
			find_emtoid_float(chs_end,1,sigtoollen,iip_grow,s_hfp.ptoolfile[3],CHN_COUNT,EDN);			//116.7:�½���
			chsTolTime[i]=((float)chs_end[0]-(float)chs_beg[0]+1)/s_samplFreq;						//ѡ��ʱ��   correct: add:+1

			create_linspace(chsTolIdx_tmp,IIP_NUM,chs_beg[0],1,(int)(chsTolTime[i]*s_samplFreq));  //correct 
// 			for(i=0;i< (int)(chsTolTime[i]*s_samplFreq);i++)
// 			{
// 				chsTolIdx_tmp[i]=chs_beg[0]+i;
// 			}
			compute_statis_file(std_tmp,NULL,chsTolIdx_tmp,(int)(chsTolTime[i]*s_samplFreq),CUR_ACT_Z);			//����ѡ�����̶�Ӧ��Z�����ͳ��ֵ								
			zCur_std[i] = std_tmp[3];
			merge_new_file(fzcur,NULL,chsTolIdx_tmp,(int)(chsTolTime[i]*s_samplFreq),CUR_ACT_Z);

			reOrtNum[i] = (float)find_emtoid_float(chsTolIdx_tmp,1,(int)(tlChgTime[i]*s_samplFreq),chg_time,s_hfp.ptoolfile[2],CHN_COUNT,EDN);	//�����ض������
		}
		else
		{
			s_CalThreadErr_No = -13;
			return -1;		//δ�ҵ�����G�����Ӧ����
		}
	}
	//��ϴ�ļ�������
	fflush(fspdcur);   //correct: add
	fflush(fzcur);

	//������������
	compute_statis_array(std_tmp,reOrtNum, s_hfp.toolchgnum);						//�ض������
		s_ftv.t_health[0] = std_tmp[2]* s_hfp.toolchgnum;
	compute_statis_array(std_tmp,tlChgTime, s_hfp.toolchgnum);						//�ܻ���ʱ��
		s_ftv.t_health[1] = std_tmp[2]* s_hfp.toolchgnum;
		s_ftv.t_health[2] = std_tmp[1];												//���λ������ֵ
	compute_statis_array(std_tmp,spdleOrTime, s_hfp.toolchgnum);	
		s_ftv.t_health[3] = std_tmp[2]* s_hfp.toolchgnum;							//�ܶ���ʱ��
		s_ftv.t_health[4] = std_tmp[1];												//�����ʱ��
	compute_statis_array(std_tmp,chsTolTime, s_hfp.toolchgnum);	
		s_ftv.t_health[5] = std_tmp[2]* s_hfp.toolchgnum;							//��ѡ��ʱ��
		s_ftv.t_health[6] = std_tmp[1];												//���ѡ��ʱ��

	compute_statis_file(std_tmp,fspdcur);											//�������	
		s_ftv.t_health[7] = std_tmp[2];												//��ֵ
		s_ftv.t_health[8] = std_tmp[1];												//���ֵ
		s_ftv.t_health[9] = std_tmp[0];												//��Сֵ
	compute_statis_array(std_tmp,spdcur_std, s_hfp.toolchgnum);	
		s_ftv.t_health[10] = std_tmp[1];											//�������ֵ

	compute_statis_file(std_tmp,fzcur);												//Z�����	
		s_ftv.t_health[11] = std_tmp[2];											//��ֵ
		s_ftv.t_health[12] = std_tmp[1];											//���ֵ
		s_ftv.t_health[13] = std_tmp[0];											//��Сֵ
	compute_statis_array(std_tmp,zCur_std, s_hfp.toolchgnum);	
		s_ftv.t_health[14] = std_tmp[1];											//�������ֵ

	//���ⲿ���˳������ر��ļ�����ɾ���м��ļ�
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
//    ���ܣ�
//            ����׼���ļ� (��ʱ����matlab���ݹ̶�д��)
//    ������
//          
//    ������
//            ��׼���ļ�������
//            ��1������������׼��
//            ��2������������һ����׼��
//    ����:
//            0:�ɹ�
//            -2 �����ݶ�ȡʧ��   
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
		longjmp(s_SetJmp,OPENFILEERR);//�ļ���ʧ��
	} 
	else
	{
		if (fread(&s_hfp.historyTestNum,sizeof(int),1,s_hfp.pstdfile) != 1)  //������ʷ�Լ����
        {
			s_CalThreadErr_No = -11;
			return -2;//���ݶ�ȡʧ��
        }
        if (fread(&s_hfp.feat_base,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //���������������׼
        {
			s_CalThreadErr_No = -11;
			return -2;//���ݶ�ȡʧ��
        }
        if (fread(&s_hfp.feat_min,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //�����һ����׼--��Сֵ
        {
			s_CalThreadErr_No = -11;
			return -2;//
        }
		if (fread(&s_hfp.feat_max,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) //�����һ����׼--���ֵ
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
//    ���ܣ�
//            ����R116�Ĵ������ݣ��õ�R116.1��R116.4��R116.6��R116.7��λ�ź�
//    ������
//            ��
//    ������
//            �Ӳ��������ļ��е�
//                      
//    ����:
//            0:�ɹ�
//            -1: δ�ҵ����һ�λ�����һ��G����
//            -2 �����ݶ�ȡʧ��   
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

	//��ȡ�������̵�����
	for(i=0;i<10;i++)
	{
		//���뱣֤����������������һ��G����'
		if(find_first_element_int_file(&toolChgLen,s_hfp.toolrow[s_hfp.toolchgnum-1]+1,s_hfp.TotalData,0,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		
		//�ж������¸�Ԫ���Ƿ�Ҳ�Ǵ���Ԫ��,�����,�жϴ�����Ϊ��Ч
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
		fprintf(s_debug_pfile," R116.1��1������%d\r\n R116.4��1������%d\r\nR116.6��1������%d\r\n R116.7��1������%d\r\n",sum1,sum4,sum6,sum7);


    //���ļ�����������д���ļ�                  //correct
    for(i=0;i<4;i++)
	{
		fflush(s_hfp.ptoolfile[i]);
	}

	return 0;
}

////////////////////////////
//�����˳�������
//
//20160906
//
/////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    int ExtrPoint(int* out_sigmax,int* out_sigmin, FILE* fp,int * pos=NULL,int len=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    ���ܣ�  �����ļ����ݵõ�ָ�����еļ���ֵ����Сֵ����
//            
//    ������  out_sigmax:����ֵ��������ָ��
//            out_maxNum:����ֵ����
//            out_sigmin:��Сֵ��������ָ��
//            out_minNum:��Сֵ����
//			  fp		:�ļ�ָ��
//			  pos		:ָ������  NULL:��ʾһά�ļ�������Ҫָ������
//			  len		:ָ������
//			  idx_chn	:ָ��ͨ�� (��ά)
//   
//    ������
//            ����Դ������fpָ����ļ������������ļ���HealSpTy��Ӧ��
//    ����:
//            ����ֵ�뼫Сֵ�������ٵ� (max_count<min_count)?max_count:min_count
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
	
	if(idx_chn < CHN_COUNT)		//��ά�����ļ�
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
					//���ͺ���Diff(X), for a vector X, is [X(2)-X(1),  X(3)-X(2), ..., X(n)-X(n-1)].
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
						if (lag_diff*data_diff<0 && lag_diff<0)//��Сֵ  
						{
                             *(out_sigmin + min_count) = idx-1; //correct: idx+1  ->idx-1
							 min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//����ֵ  
						{
							*(out_sigmax + max_count) = idx-1;  //correct: idx+1  ->idx-1
							 max_count++;
						}
					}
				}
			}
		}
	}
	else						//һ�������ļ�
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
					//���ͺ���
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
						if (lag_diff*data_diff<0 && lag_diff<0)//��Сֵ  
						{
							*(out_sigmin + min_count) = idx-1;  //correct: idx+1  ->idx-1
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//����ֵ  
						{
							*(out_sigmax + max_count) = idx-1;  //correct: idx+1  ->idx-1
							max_count++;
						}
					}
				}
			}
		}
	}

	*(out_maxNum) = max_count; //����ֵ����
	*(out_minNum) = min_count; //��Сֵ����

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    int CalVib_continuous_infile(int* out_vib,int section_len,int start_idx=NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT)
//
//    ���ܣ�  �����ļ����������ݼ���ָ����ʼ��ͳ��ȵ���������� ����ֵ
//            
//    ������  out_vib		:���ݲ���ֵ(���)
//            section_len	:���䳤��
//            start_idx		:�����������
//			  fp			:�м��ļ�ָ��  
//			  idx_chn=0~15  : ���������ļ�ָ��ͨ������; 
//						16  :   �м��ļ���������
//   
//    ������
//            ����Դ������fpָ����ļ������������ļ���HealSpTy��Ӧ��
//    ����:
//            
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CalVib_continuous_infile(float* out_vib,int section_len,int start_idx=NULL,FILE* fp=NULL,HealSpTy idx_chn=CHN_COUNT)
{
	int		i=0;
	int     min_count = 0, max_count = 0;  //��ֵ����
	double  min_mean = 0.0, max_mean = 0.0;  //��ֵ�Ļ���ƽ��
	float	tmp=0;
	float   data = 0.0, lag_data = 0.0;
	float   data_diff = 0.0, lag_diff = 0.0;
	int	idx=0;
	int filelen = 0;
	
	if(idx_chn < CHN_COUNT)		//���������ļ�
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
					//���ͺ���Diff(X), for a vector X, is [X(2)-X(1),  X(3)-X(2), ..., X(n)-X(n-1)].
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
						if (lag_diff*data_diff<0 && lag_diff<0)//��Сֵ  
						{
							min_mean = (min_mean*min_count+lag_data)/(min_count+1); //��Сֵ����ƽ��
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//����ֵ  
						{
							max_mean = (max_mean*max_count+lag_data)/(max_count+1); //����ֵ����ƽ��
							max_count++;
						}
					}
				}
			}
		}
	}
	else						//һ�������ļ�
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
					//���ͺ���
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
						if (lag_diff*data_diff<0 && lag_diff<0)//��Сֵ  
						{
							min_mean = (min_mean*min_count+lag_data)/(min_count+1); //��Сֵ����ƽ��
							min_count++;
						}
						if (lag_diff*data_diff<0 && lag_diff>0)//����ֵ  
						{
							max_mean = (max_mean*max_count+lag_data)/(max_count+1); //����ֵ����ƽ��
							max_count++;
						}
					}
				}
			}
		}
	}

	*(out_vib) = (float)(max_mean - min_mean);  //�������ֵ

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
//    float caltrackerr(int* subscript=NULL,int sub_length=NULL ,HealSpTy act_chn,HealSpTy cmd_chn)
//
//    ���ܣ�  ����ִ��ĳ��G01ָ���ڼ䵥������������������
//
//    ������  
//			  subscript�� ָ���±����������飬NULL��ʾ��ָ��,�������ݲ������
//			  sub_length��ָ���±������ĳ���
//            act_chn:    ʵ��λ�ò���ͨ����
//            cmd_chn:    ָ��λ�ò���ͨ����
//    ������
//            �Ӳ��������ļ��м���
//
//    ���أ� trackerr �����������
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
//    ���ܣ�	ִ��ĳ��G01ָ���ڼ䵥���������������ȡ��������ֵ��������������������
//
//    ������  
//			    outftv:   �������������ֵ��������ֵ��������������������
//              subscript: ����G01�кŶ�Ӧ�������±�
//              sub_length: ��������
//              cur_chn:  �������������ͨ����
//              act_chn:  ʵ��λ�ò���ͨ����
//	            cmd_chn:  ָ��λ�ò���ͨ����		  
//    ������
//              �Ӳ��������ļ��м���
//
//    ���أ�    0�� �ɹ�
//           
//
/////////////////////////////////////////////////////////////////////////
int SigFeed(float* outft,int* subscript,int sub_length,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
{
	int maxindex[IIP_NUM] = {0};     //����ֵ����
	int maxNum = 0;                  //����ֵ����
    int minindex[IIP_NUM] = {0};     //��Сֵ����
	int minNum = 0;                  //��Сֵ����
	float statis_temp[4] = {0.0};
	float maxmean = 0.0;             //����ֵ��ֵ
	float minmean = 0.0;             //��Сֵ��ֵ

	compute_statis_file(statis_temp,NULL,subscript,sub_length,cur_chn);
	*(outft) = statis_temp[2];//������ֵ //correct:   statis_temp[3] -> statis_temp[2]
	ExtrPoint(maxindex,&maxNum,minindex,&minNum,NULL,subscript,sub_length,cur_chn);
    compute_statis_file(statis_temp,NULL,maxindex,maxNum,cur_chn);
    maxmean = statis_temp[2];            //correct:   statis_temp[3] -> statis_temp[2]
	compute_statis_file(statis_temp,NULL,minindex,minNum,cur_chn);
	minmean = statis_temp[2];            //correct:   statis_temp[3] -> statis_temp[2]
    *(outft+1) = maxmean - minmean;//��������
    *(outft+2) = caltrackerr(subscript,sub_length,act_chn,cmd_chn);//���������

	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
//    int SigFeedFtvExt(float* outftv,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
//
//    ���ܣ�	���������ᣨX/Y/Z�ᣩ����������ȡ
//
//    ������  
//			    outftv:   �����������������
//              cur_chn:  �������������ͨ����
//              act_chn:  ʵ��λ�ò���ͨ����
//	            cmd_chn:  ָ��λ�ò���ͨ����	  
//    ������
//              ���ݲ������ݼ���
//
//    ���أ�    0 ���ɹ�
//              -1��ʧ��
//
/////////////////////////////////////////////////////////////////////////
int SigFeedFtvExt(float* outftv,HealSpTy cur_chn,HealSpTy act_chn,HealSpTy cmd_chn)
{
	int i = 0;
	int row_temp = 0;
	int sigfeedlen = 0;                     //���ν�����Ӧ�岹�еĳ���
	int iip_grow[IIP_NUM]={0};			//���ν�����Ӧ�Ĳ岹������ (�ɽ�����ͳһ��Ϊint��)
	float curft[4][FEEDTIME][3] = {0.0}; //��������������[4]�ߵ������������;[FEEDTIME]����ϴ���;[3]��������ֵ����������������  
	float lcurmean =0.0; //������ٵ�����ֵ֮��
    float lcurvirb =0.0; //������ٵ�������֮��
	float hcurmean =0.0; //������ٵ�����ֵ֮��
    float hcurvirb =0.0; //������ٵ�������֮��
	float trackerr =0.0; //���������
    float diffcur = 0.0; //�����س����֮��
	float ftmp = 0.0; //�м����

	//����G01�岹��������ȡ
	for(i=0;i<s_hfp.feednum;i++)
	{
		//��������岹������ȡ
		row_temp= s_hfp.feedrow[0][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"���ٽ����岹��%d���������ȣ�%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"���ٽ����岹��%d����ʼ������%d\r\n",row_temp,*(iip_grow));
		}
		
		if (sigfeedlen>0)
		{
            SigFeed(&curft[0][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//���ٸ���岹������ȡ
		row_temp= s_hfp.feedrow[1][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"���ٽ����岹��%d���������ȣ�%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"���ٽ����岹��%d����ʼ������%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[1][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//��������岹������ȡ
		row_temp= s_hfp.feedrow[2][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"���ٽ����岹��%d���������ȣ�%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"���ٽ����岹��%d����ʼ������%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[2][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		//���ٸ���岹������ȡ
		row_temp= s_hfp.feedrow[3][i];
		//sigfeedlen = find_emtoid_float(iip_grow,row_temp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
		//Gcoderow
		sigfeedlen = find_emtoid_int(iip_grow,row_temp,s_hfp.TotalData,NULL,s_hfp.pGcoderow,SIG);
		//debug
		if(s_Print_CalDataInlo_Flag)
		{
			fprintf(s_debug_pfile,"���ٽ����岹��%d���������ȣ�%d\r\n",row_temp,sigfeedlen);
			fprintf(s_debug_pfile,"���ٽ����岹��%d����ʼ������%d\r\n",row_temp,*(iip_grow));
		}
        if (sigfeedlen>0)
		{
            SigFeed(&curft[3][i][0],iip_grow,sigfeedlen,cur_chn,act_chn,cmd_chn);
		} 
		else
		{
			return -1;
		}
		
        //---------------������ȡ-------------------------------//
		//���ٵ�����ֵ֮��
        lcurmean = lcurmean+ fabsf(curft[0][i][0])+ fabsf(curft[1][i][0]); //xcurft[0][][] Ϊ��������������xcurft[1][][]Ϊ���ٷ�������
		//���ٵ�������֮��
		lcurvirb = lcurvirb+ curft[0][i][1]+ curft[1][i][1];
		//���ٵ�����ֵ֮��
        hcurmean = hcurmean+ fabsf(curft[2][i][0])+ fabsf(curft[3][i][0]);
		//���ٵ�������֮��
		hcurvirb = hcurvirb+ curft[2][i][1]+ curft[3][i][1];
		//���������
		ftmp = max(max(curft[0][i][2],curft[1][i][2]),max(curft[2][i][2],curft[3][i][2])); //һ���Ĵ��е�������
		trackerr = max(trackerr,ftmp);
		//�����س����
        diffcur = diffcur+(fabsf(curft[0][i][0])-fabsf(curft[1][i][0]))+(fabsf(curft[2][i][0])-fabsf(curft[3][i][0]));
	}
	
	//����������������ֵ
    *(outftv) = lcurmean/s_hfp.feednum/2;   //���ٵ�����ֵ
	*(outftv+1) = lcurvirb/s_hfp.feednum/2; //���ٵ�������
	*(outftv+2) = hcurmean/s_hfp.feednum/2; //���ٵ�����ֵ
	*(outftv+3) = hcurvirb/s_hfp.feednum/2; //���ٵ�������
	*(outftv+4) = trackerr;                 //���������
	*(outftv+5) = diffcur/s_hfp.feednum/2;  //�����س����

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int FeedFtvExt()
//
//    ���ܣ�	�����ᣨX��Y��Z�ᣩ����������ȡ
//
//    ������  
//			    ��
//			  
//    ������
//            
//
//    ���أ�    0���ɹ�
//				-1:������ȡʧ��        
//
/////////////////////////////////////////////////////////////////////////
int FeedFtvExt()
{

	if(SigFeedFtvExt(&s_ftv.x_health[0],CUR_ACT_X,AXIS_ACT_X,AXIS_CMD_X) < 0) //X��
	{
		s_CalThreadErr_No = -15;
		return -1;
	}
    if(SigFeedFtvExt(&s_ftv.y_health[0],CUR_ACT_Y,AXIS_ACT_Y,AXIS_CMD_Y) < 0) //Y��
	{
		s_CalThreadErr_No = -16;
		return -1;
	}
	if(SigFeedFtvExt(&s_ftv.z_health[0],CUR_ACT_Z,AXIS_ACT_Z,AXIS_CMD_Z) < 0) //Z��
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
//    ���ܣ�	��������G�����кŶ�Ӧ���±�����
//
//    ������  
//			    out_idx��   �����к�����Ӧ�Ĳ�����������
//              out_len��   ����������󳤶�
//              start_row�� ��ʼ�к�
//			    end_row��   ��ֹ�к�
//    ������
//              ����ʼ�к�����ֹ�кŵ�����G�����кŶ�Ӧ�����������������     
//
//    ���أ� 
//             total_len�� �����ܸ�����>=0��     
//             -1       :  ����Խ��
/////////////////////////////////////////////////////////////////////////
int Connect_GRow_Idx(int* out_idx,int arr_len,int start_row,int end_row)
{
	int row_tmp = 0;
	int len_tmp = 0;
	int total_len = 0; //��������

	for (row_tmp=start_row; row_tmp<=end_row; row_tmp++)
	{
		len_tmp = find_emtoid_float(out_idx+total_len,row_tmp,s_hfp.TotalData,NULL,NULL,GODE_ROW,SIG);
        total_len += len_tmp;
		if(total_len > arr_len) return -1; //����Խ��
	}

	return total_len;
}

///////////////////////////////////////////////////////////////////////////////
//
//    create_linspace(int* obj_arr,int start_num,int scale_val,int data_num)
//
//    ���ܣ�
//            ���� ���������Ȳ����飩 ���� ��INT�ͣ� 
//    ������
//            int* obj_arr: Ŀ������ 
//            int arr_length:������󳤶� 
//            int start_num: ��������ʼ���� 
//            int scale_val�� ������ǰ���ֵ 
//            int data_num��  ����������      
//    ������
//            ��ӦMATLAB   a:i:b ���� ��
//    ����:
//            0���ɹ�
//            -1:ʧ�� 
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
//    ���ܣ�	
//              ��ȡ���ٶ�����(��0��ʼ����)
//    ������  
//			    out_idex��������ٶ���������
//              in_idex:  �޶��������飬�ڴ�������Χ����ȡ���ٶ�
//              in_len:   �޶��������鳤��
//              cmdSped:  ���ٺ������ٶ�
//              err:      ������ʵ���ٶ��������ٶȣ�
//	            sped_chn: �ٶ����ڲ���ͨ����	VEL_SPIND�������ٶ�	  
//    ������
//              ��ָ����������Χ����ȡ ���ٶε�����          
//
//    ���أ� 
//             out_len�����ٶ��������ȣ�>=0��     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int Acce_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
	int out_len =0;            //���ٶγ��ȣ����ڷ��أ�
	int consSped_len = 0;      //���ٶγ��ȣ�ָ�ٶȴﵽ����ֵ��
	int* consSped_idx = NULL;  //���ٶ���������ָ��
	int react_len = 0;		   //��Ӧ�γ��ȣ�ָ�����˶�ָ���ʼ��ת�ĶΣ�
	int* react_idx = NULL;	   //��Ӧ����������ָ��
	int acce_start = 0;        //���ٶ��������ֵ
	int acce_end = 0;          //
	int* tmp_idx = NULL;
    int tmp_start = 0;
    int tmp_datanum = 0;
	
	
    consSped_idx = (int *)malloc(in_len*sizeof(int));
	if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);           //correct
	react_idx = (int *)malloc(in_len*sizeof(int));
	if(react_idx == NULL) longjmp(s_SetJmp,MALLOCERR);             //correct
	//�Ҽ��ٶ��յ㣨������Ծ�壬���ٶ���㣩
    consSped_len =  find_emtoid_float(consSped_idx,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	acce_end = *(consSped_idx);
    //�Ҽ��ٶ���㣨��Ӧ���յ㣩
	tmp_start = *(in_idex);
	tmp_datanum = acce_end -tmp_start +1;
	tmp_idx = (int *)malloc(tmp_datanum*sizeof(int));
	if(tmp_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
    create_linspace(tmp_idx,tmp_datanum,tmp_start,1,tmp_datanum);
	react_len = find_emtoid_float(react_idx,0,tmp_datanum,tmp_idx,NULL,sped_chn,SIG,err);
	acce_start = *(react_idx+react_len-1);
    //�õ����ٶ������ͼ��ٶγ���
    out_len = acce_end -acce_start+1;
    create_linspace(out_idex,out_len,acce_start,1,out_len);
    //�˳�����
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
//    ���ܣ�	
//              ��ȡ���ٶ�����(���ٵ�0)
//    ������  
//			    out_idex��������ٶ���������
//              in_idex:  �޶��������飬�ڴ�������Χ����ȡ���ٶ�
//              in_len:   �޶��������鳤��
//              cmdSped:  ����ǰ�������ٶ�
//	            sped_chn: �ٶ����ڲ���ͨ����	VEL_SPIND�������ٶ�	
//              err:      ������ʵ���ٶ��������ٶȣ�  
//    ������
//              ��ָ����������Χ����ȡ ���ٶε�����          
//
//    ���أ� 
//             out_len�����ٶ��������ȣ�>=0��     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int Dece_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
	int out_len =0;            //���ٶγ��ȣ����ڷ��أ�
	int consSped_len = 0;      //���ٶγ��ȣ�ָ�ٶȴﵽ����ֵ��
	int* consSped_idx = NULL;  //���ٶ���������ָ��
	int zero_len = 0;		   //����γ��ȣ�ָ�����˶�ָ���ʼ��ת�ĶΣ�
	int* zero_idx = NULL;	   //�������������ָ��
	int dece_start = 0;        //���ٶ��������ֵ
	int dece_end = 0;          //���ٶ��յ�����ֵ
	int* tmp_idx = NULL;
    int tmp_start = 0;
    int tmp_datanum = 0;
	
    consSped_idx = (int *)malloc(in_len*sizeof(int));
    if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	zero_idx = (int *)malloc(in_len*sizeof(int));
	if(zero_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	//�Ҽ��ٶ���㣨���ٶ��յ㣩
    consSped_len =  find_emtoid_float(consSped_idx,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	dece_start = *(consSped_idx+consSped_len-1);
    //�Ҽ��ٶ��յ㣨������Ծ�壬������յ㣩
    tmp_start = *(in_idex);                            //�����������     //correct
	tmp_datanum = in_len -(dece_start-tmp_start);   //��ʼ����ʣ�೤��  //correct��ȥ��β��+1
	tmp_idx = (int *)malloc(tmp_datanum*sizeof(int));
	if(tmp_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
    create_linspace(tmp_idx,tmp_datanum,dece_start,1,tmp_datanum);
	zero_len = find_emtoid_float(zero_idx,0,tmp_datanum,tmp_idx,NULL,sped_chn,SIG,err);
	dece_end = *(zero_idx);
    //�õ����ٶ������ͼ��ٶγ���
    out_len = dece_end -dece_start+1;
    create_linspace(out_idex,out_len,dece_start,1,out_len);
    //�˳�����
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
//    ���ܣ�	
//              ��ȡ���ٶ�����(���ٵ�0)
//    ������  
//			    out_idex��������ٶ���������
//              in_idex:  �޶��������飬�ڴ�������Χ����ȡ���ٶ�
//              in_len:   �޶��������鳤��
//              cmdSped:  ���ٶε������ٶ�
//	            sped_chn: �ٶ����ڲ���ͨ����	VEL_SPIND�������ٶ�	
//              err:      ������ʵ���ٶ��������ٶȣ�  
//    ������
//              ��ָ����������Χ����ȡ ���ٶε�����          
//
//    ���أ� 
//             out_len�����ٶ��������ȣ�>=0��     
//             -1     :
/////////////////////////////////////////////////////////////////////////
/*
int consSped_Segmt_Idx(int* out_idex,int* in_idex, int in_len, int cmdSped, float err,HealSpTy sped_chn = VEL_SPIND)
{
    int out_len =0;            //���ٶγ��ȣ����ڷ��أ�

	//δ���Ǽ���Ծ��ĺ��ٶ�
    out_len =  find_emtoid_float(out_idex,cmdSped,in_len,in_idex,NULL,sped_chn,SIG,err);
	
	return out_len;
}
*/

/////////////////////////////////////////////////////////////////////////
//
//    int SigSpd_AcDc_Ext(float* outftv,int start_row, int end_row,bool isHighSpd = true)
//
//    ���ܣ�	�������� ������-����-���٣����̵�������ȡ
//
//    ������  
//			    outftv:     �������������1.����ʱ�䡢2.����ʱ�䡢3.������ֵ��4.����������
//              start_row:  ������תָ���кţ�M03��M04��
//              end_row:    ����ָֹͣ���кţ�M05��һ��ָ���G04��
//			    isHighSpd:  �Ƿ��������  1��Ĭ�ϣ�true
//              isPos:      �Ƿ���ת   1��Ĭ�ϣ�true
//    ������
//              ��һ��������١����١����ٹ��̵�������ȡ  
//
//    ���أ� 
//             0���ɹ�     
//
/////////////////////////////////////////////////////////////////////////
/*
int SigSpd_AcDc_Ext(float* outftv,int start_row, int end_row,bool isHighSpd = true,bool isPos = true)
{
	int* acDc_idx = NULL;     //�������-����-����ȫ��������
	int acDc_len = 0;         //ȫ������������
	int maxlen = 0;           //ȫ����������󳤶�
	int acce_len = 0;       //���ٶ���������
	int* acce_idx = NULL;   //��������
	int dece_len = 0;       //���ٶ���������
	int* dece_idx = NULL;   //��������
	int consSped_len = 0;   //���ٶ���������
	int* consSped_idx=NULL; //��������

	int cmdSped = 0;          //���۴ﵽ���ٶ�
	float allow_err = 0;      //�ٶ��������

	float statis_temp[4] = {0.0};
	int* maxindex = NULL;            //����ֵ����
	int* minindex = NULL;            //��Сֵ����
    int maxNum = 0;                  //����ֵ����
	int minNum = 0;                  //��Сֵ����
	float maxmean = 0.0;             //����ֵ��ֵ
	float minmean = 0.0;             //��Сֵ��ֵ
    
	//
	maxlen = (end_row-start_row+1)*IIP_NUM;
    acDc_idx = (int*)malloc(maxlen*sizeof(int));
	if(acDc_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	acDc_len =  Connect_GRow_Idx(acDc_idx,maxlen,start_row,end_row);  //ȫ��������
	if (isHighSpd)
	{
        cmdSped = isPos?s_hfp.spd_highSped:-s_hfp.spd_highSped;  //correcr:��������ת�ж�
		allow_err = HIGHSPDERR;
	} 
	else
	{
        cmdSped = isPos?s_hfp.spd_lowSped:-s_hfp.spd_lowSped;  //correcr:��������ת�ж�
        allow_err = LOWSPDERR;
	}
	//���ٹ���������ȡ������ʱ�䣩
	acce_idx = (int*)malloc(maxlen*sizeof(int));
	if(acce_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
    acce_len = Acce_Segmt_Idx(acce_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND);
	*(outftv) = acce_len/s_samplFreq;  //����ʱ��
	free(acce_idx);
	//���ٹ���������ȡ������ʱ�䣩
    dece_idx = (int*)malloc(maxlen*sizeof(int));
	if(dece_idx == NULL) longjmp(s_SetJmp,MALLOCERR);              //correct
	dece_len = Dece_Segmt_Idx(dece_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND);
	*(outftv+1) = dece_len/s_samplFreq;  //����ʱ��
	free(dece_idx);
	//���ٶ�������ȡ�����������ֵ���������������
    consSped_idx = (int*)malloc(maxlen*sizeof(int));
	if(consSped_idx == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	consSped_len = consSped_Segmt_Idx(consSped_idx,acDc_idx,acDc_len,cmdSped,allow_err,VEL_SPIND); //correct:  dece_idx ->consSped_idx
	compute_statis_file(statis_temp,NULL,consSped_idx,consSped_len,CUR_SPIND);
	*(outftv+2) = statis_temp[2];//������ֵ  //correct: statis_temp[3] ->statis_temp[2]
	  //�󲨶�
	maxindex = (int*)malloc(consSped_len*sizeof(int));
    if(maxindex == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	minindex = (int*)malloc(consSped_len*sizeof(int));
	if(minindex == NULL) longjmp(s_SetJmp,MALLOCERR);               //correct
	ExtrPoint(maxindex,&maxNum,minindex,&minNum,NULL,consSped_idx,consSped_len,CUR_SPIND);
	compute_statis_file(statis_temp,NULL,maxindex,maxNum,CUR_SPIND);
    maxmean = statis_temp[2];                //correct: statis_temp[3] ->statis_temp[2]
	compute_statis_file(statis_temp,NULL,minindex,minNum,CUR_SPIND);
	minmean = statis_temp[2];                //correct: statis_temp[3] ->statis_temp[2]
    *(outftv+3) = maxmean - minmean;//��������
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
//    ���ܣ�	����������ȡ
//
//    ������  
//			    ��
//			  
//    ������
//            
//
//    ���أ� 
//             0���ɹ�     
//
/////////////////////////////////////////////////////////////////////////
/*
int SpdFtvExt()
{
	int i = 0;
	int start_row = 0;
	int end_row = 0;
	int lowpos_times = 0;                   //����������ͣ����
	float lowpos_ftv[SPDTIME][4] = {0.0};   //���ε�������ʱ������ֵ
	int lowneg_times = 0;
	float lowneg_ftv[SPDTIME][4] = {0.0};   //���ٷ���
	int highpos_times = 0;
	float highpos_ftv[SPDTIME][4] = {0.0};  //��������
	int highneg_times = 0;
	float highneg_ftv[SPDTIME][4] = {0.0};  //���ٷ���

	float accetime = 0.0;   //����ʱ���ܺ�
	float decetime = 0.0;   //����ʱ���ܺ�
	float curmean = 0.0;    //������ֵ�ܺͣ�����ֵ֮�ͣ�
	float curvrib = 0.0;    //���������ܺ�

	for (i=0;i<s_hfp.spdnum;i++)
	{
		//������ת
		start_row = s_hfp.spdrow[0][i][0];
		end_row = s_hfp.spdrow[0][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&lowpos_ftv[i][0],start_row,end_row,false,true);
			lowpos_times++;
			//����ֵ�ۼ�
            accetime = accetime+lowpos_ftv[i][0];
			decetime = decetime+lowpos_ftv[i][1];
			curmean = curmean+fabsf(lowpos_ftv[i][2]);
			curvrib = curvrib+lowpos_ftv[i][3];
		}
		//���ٷ�ת
		start_row = s_hfp.spdrow[1][i][0];
		end_row = s_hfp.spdrow[1][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&lowneg_ftv[i][0],start_row,end_row,false,false);
			lowneg_times++;
			//����ֵ�ۼ�
			accetime = accetime+lowneg_ftv[i][0];
			decetime = decetime+lowneg_ftv[i][1];
			curmean = curmean+fabsf(lowneg_ftv[i][2]);
			curvrib = curvrib+lowneg_ftv[i][3];
		}  
		//������ת
		start_row = s_hfp.spdrow[2][i][0];
		end_row = s_hfp.spdrow[2][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&highpos_ftv[i][0],start_row,end_row,true,true);
			highpos_times++;
			//����ֵ�ۼ�
			accetime = accetime+highpos_ftv[i][0];
			decetime = decetime+highpos_ftv[i][1];
			curmean = curmean+fabsf(highpos_ftv[i][2]);
			curvrib = curvrib+highpos_ftv[i][3];
		}
		//���ٷ�ת
		start_row = s_hfp.spdrow[3][i][0];
		end_row = s_hfp.spdrow[3][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext(&highneg_ftv[i][0],start_row,end_row,true,false);
			highneg_times++;
			//����ֵ�ۼ�
			accetime = accetime+highneg_ftv[i][0];
			decetime = decetime+highneg_ftv[i][1];
			curmean = curmean+fabsf(highneg_ftv[i][2]);
			curvrib = curvrib+highneg_ftv[i][3];
		}
	}

	//����������������
	s_ftv.s_health[0] = accetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //����ʱ��
	s_ftv.s_health[1] = decetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //����ʱ��
	s_ftv.s_health[2] = curmean/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //������ֵ
	s_ftv.s_health[3] = curvrib/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //��������

	return 0;
}
*/
/////////////////////////////////////////////////////////////////////////
//
//    int SigSpd_AcDc_Ext_02(float* outftv,int start_row, int end_row,bool isHighSpd = true)
//
//    ���ܣ�	�������� ������-����-���٣����̵�������ȡ
//					(v2.0 -- ��ʹ�ö�̬�����ڴ�)				
//    ������  
//			    outftv:     �������������1.����ʱ�䡢2.����ʱ�䡢3.������ֵ��4.����������
//              start_row:  ������תָ���кţ�M03��M04��
//              end_row:    ����ָֹͣ���кţ�M05��һ��ָ���G04��
//			    isHighSpd:  �Ƿ��������  1��Ĭ�ϣ�true
//              isPos:      �Ƿ���ת   1��Ĭ�ϣ�true
//    ������
//              ��һ��������١����١����ٹ��̵�������ȡ  
//
//    ���أ� 
//             0���ɹ�     
//
/////////////////////////////////////////////////////////////////////////
int SigSpd_AcDc_Ext_02(float* outftv,int start_row, int end_row,bool isHighSpd = true,bool isPos = true)
{
	int acce_row_start = 0;     //�������������������ϵͳ��Ӧ�Σ�
	int dece_row_start = 0;		//�������������������ϵͳ��Ӧ�Σ�
	int acce_start = 0;			//���ٶ���㣨������ϵͳ��Ӧ�Σ�
	int acce_end = 0;			//���ٶ��յ�
	int dece_start = 0;			//���ٶ���㣨������ϵͳ��Ӧ�Σ�
	int dece_end = 0;			//���ٶ��յ�
	int cmdSped = 0;            //���۴ﵽ���ٶ�
	float allow_err = 0;        //�ٶ��������
	int acce_start_sped = 0;		//�жϼ��ٶ������ٶ�
	int dece_start_sped = 0;		//�жϼ��ٶ������ٶ�
	float current_vib = 0.0;
	float statis_temp[4] = {0.0};   //

	int i = 0;
	int temp = 0;

	if (isHighSpd)
	{
        cmdSped = isPos?s_hfp.spd_highSped:-s_hfp.spd_highSped;  //correcr:��������ת�ж�
		allow_err = HIGHSPDERR;
	} 
	else
	{
        cmdSped = isPos?s_hfp.spd_lowSped:-s_hfp.spd_lowSped;  //correcr:��������ת�ж�
        allow_err = LOWSPDERR;
	}
	acce_start_sped = (int)(isPos?(2*allow_err):(-2*allow_err));
	dece_start_sped = (int)(isPos?(cmdSped - 2*allow_err):(cmdSped + 2*allow_err));
	//���ٹ���������ȡ������ʱ�䣩
	//find_first_element_float_file(&acce_row_start,start_row,s_hfp.TotalData,0,NULL,GODE_ROW);
	//Gcoderow
	for(i=0;i<10;i++)
	{
		//�����е�һ��
		if(find_first_element_int_file(&acce_row_start,start_row,s_hfp.TotalData,0,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		//�ж������¸�Ԫ���Ƿ�Ҳ�Ǵ���Ԫ��,�����,�жϴ�����Ϊ��Ч
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
		fprintf(s_debug_pfile,"���������%d���к���ʼ������%d\r\n",start_row,acce_row_start);

	find_first_element_float_file(&acce_end,cmdSped,10000,acce_row_start,NULL,VEL_SPIND,allow_err); //���ٶ��յ�
	//debug
	if(s_Print_CalDataInlo_Flag)
		fprintf(s_debug_pfile,"���������%d���кż��ٶ��յ�������%d\r\n",start_row,acce_end);

	find_first_element_float_file(&acce_start,acce_start_sped,acce_end-acce_row_start+1,acce_row_start,NULL,VEL_SPIND,allow_err); //���ٶ���㣨ϵͳ��Ӧ���յ㣩
	*(outftv) = (acce_end - acce_start+1)/s_samplFreq;  //����ʱ��
	//���ٹ���������ȡ������ʱ�䣩
	//find_first_element_float_file(&dece_row_start,end_row,s_hfp.TotalData-acce_start+1,acce_start,NULL,GODE_ROW);
	//Gcoderow
	for(i=0;i<10;i++)
	{
		//�����е�һ��
		if(find_first_element_int_file(&dece_row_start,end_row,s_hfp.TotalData-acce_start+1,acce_start,s_hfp.pGcoderow)< 0)
		{
			s_CalThreadErr_No = -8;
			return -1;
		}
		//�ж������¸�Ԫ���Ƿ�Ҳ�Ǵ���Ԫ��,�����,�жϴ�����Ϊ��Ч
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

	find_first_element_float_file(&dece_end,0,10000,dece_row_start,NULL,VEL_SPIND,allow_err); //���ٶ��յ�
	find_first_element_float_file(&dece_start,dece_start_sped,dece_end-dece_row_start+1,dece_row_start,NULL,VEL_SPIND,allow_err); //���ٶ���㣨ϵͳ��Ӧ���յ㣩
	*(outftv+1) = (dece_end - dece_start+1)/s_samplFreq;  //����ʱ��
	//���ٶ�������ȡ�����������ֵ���������������
    compute_statis_continuous_infile(statis_temp,dece_start-acce_end+1,acce_end,NULL,CUR_SPIND);
	*(outftv+2) = statis_temp[2];//������ֵ
	//�󲨶�
	CalVib_continuous_infile(&current_vib,dece_start-acce_end+1,acce_end,NULL,CUR_SPIND);
	*(outftv+3) = current_vib;//��������

	return 0;
}

/////////////////////////////////////////////////////////////////////////
//
//    int SpdFtvExt_02()
//
//    ���ܣ�	����������ȡ -> �޸ģ�����malloc()
//
//    ������  
//			    ��
//			  
//    ������
//            
//
//    ���أ� 
//             0���ɹ�     
//
/////////////////////////////////////////////////////////////////////////
int SpdFtvExt_02()
{
	int i = 0;
	int start_row = 0;
	int end_row = 0;
	int lowpos_times = 0;                   //����������ͣ����
	float lowpos_ftv[SPDTIME][4] = {0.0};   //���ε�������ʱ������ֵ
	int lowneg_times = 0;
	float lowneg_ftv[SPDTIME][4] = {0.0};   //���ٷ���
	int highpos_times = 0;
	float highpos_ftv[SPDTIME][4] = {0.0};  //��������
	int highneg_times = 0;
	float highneg_ftv[SPDTIME][4] = {0.0};  //���ٷ���
	
	float accetime = 0.0;   //����ʱ���ܺ�
	float decetime = 0.0;   //����ʱ���ܺ�
	float curmean = 0.0;    //������ֵ�ܺͣ�����ֵ֮�ͣ�
	float curvrib = 0.0;    //���������ܺ�
	
	for (i=0;i<s_hfp.spdnum;i++)
	{
		//������ת
		start_row = s_hfp.spdrow[0][i][0];
		end_row = s_hfp.spdrow[0][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&lowpos_ftv[i][0],start_row,end_row,false,true);
			lowpos_times++;
			//����ֵ�ۼ�
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
		//���ٷ�ת
		start_row = s_hfp.spdrow[1][i][0];
		end_row = s_hfp.spdrow[1][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&lowneg_ftv[i][0],start_row,end_row,false,false);
			lowneg_times++;
			//����ֵ�ۼ�
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
		//������ת
		start_row = s_hfp.spdrow[2][i][0];
		end_row = s_hfp.spdrow[2][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&highpos_ftv[i][0],start_row,end_row,true,true);
			highpos_times++;
			//����ֵ�ۼ�
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
		//���ٷ�ת
		start_row = s_hfp.spdrow[3][i][0];
		end_row = s_hfp.spdrow[3][i][1];
		if (start_row >0 && end_row>0)
		{
			SigSpd_AcDc_Ext_02(&highneg_ftv[i][0],start_row,end_row,true,false);
			highneg_times++;
			//����ֵ�ۼ�
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
	
	//����������������
	s_ftv.s_health[0] = accetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //����ʱ��
	s_ftv.s_health[1] = decetime/(lowpos_times+lowneg_times+highpos_times+highneg_times);  //����ʱ��
	s_ftv.s_health[2] = curmean/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //������ֵ
	s_ftv.s_health[3] = curvrib/(lowpos_times+lowneg_times+highpos_times+highneg_times);   //��������
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//    int vector_normal(float* obj_vector, float* min_Arr, float* max_Arr, int vector_length)
//
//    ���ܣ�
//            ��������ÿһ��ֵ���ն�Ӧ��׼�ֱ���й�һ��
//    ������
//            float* obj_vector :Ҫ��һ��������
//            float* min_Arr :��һ����׼--��Сֵ   -> 0
//            float* max_Arr :��һ����׼--���ֵ   -> 1
//            int vector_length :��������
//    ������
//            
//    ����:
//            0:�ɹ�
//            -1: ��ָ��
//            -2 ����������<=0   
//////////////////////////////////////////////////////////////////////////
int vector_normal(float* obj_vector, float* min_Arr, float* max_Arr, int vector_length)
{
    int i = 0;

	if(obj_vector==NULL || min_Arr==NULL || max_Arr==NULL)return -1;
	if(vector_length <= 0)return -2;

	for (i = 0;i < vector_length;i++)
	{
		if(*(max_Arr+i) == *(min_Arr+i))  //correct:���ӳ����ж�
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
//    ���ܣ�
//            ����FeatureVec�ṹ�����������������һ��
//    ������
//            FeatureVec *obj_feature :Ҫ��һ�������������ṹ��
//            FeatureVec *min_normalStd :��һ����׼--��Сֵ   -> 0
//            FeatureVec *max_normalStd :��һ����׼--���ֵ   -> 1
//   
//    ������
//            
//    ����:
//            0:�ɹ�
//            -1: ��ָ��
//            -2 ��������һ��ʧ�� 
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
//    ���ܣ�
//            ���������������ŷʽ���루��������ͬ���ȣ�
//    ������
//            float *vector_1 :����1
//            float *vector_2 :����2
//            int vector_length :��������
//   
//    ������
//            d = (v1 - v2)(v1 -v2)'
//    ����:
//            euclid_dis:ŷʽ���� ��>=0��
//            -1: ��ָ��
//            -2 ����������<=0 
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
//    ���ܣ�
//            logsigӳ�亯��
//    ������
//            float number: ��ӳ�����
//   
//    ������
//            logsig(n) = 1 / (1 + exp(-n))
//    ����:
//            transfer_num: logsigӳ���Ľ��
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
//    ���ܣ�
//            ������ȡ�ĸ���������ֵ�������׼����������������Ľ���ָ��
//    ������
//            healthIndex: ����ָ��������������Ϊ��X�ᡢY�ᡢZ�ᡢ���ᡢ���⡢����
//   
//    ������
//            
//    ����:
//            0������ɹ�
//////////////////////////////////////////////////////////////////////////
int CalHealthIndex(float* healthIndex)
{
	FeatVec standard_vec = {0}; //�����׼
    FeatVec cal_vec = {0};      //������ȡ�������������޸�s_ftv

	//���������������ͻ�׼������һ��
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
	//�������ὡ��ָ��
	*(healthIndex) = cal_Euclidean_distance(cal_vec.s_health, standard_vec.s_health, S_VEC_LENGTH)/S_VEC_LENGTH; 
	*(healthIndex) = 2*logsig(-(*(healthIndex)));
	//����X�ὡ��ָ��
	*(healthIndex+1) = cal_Euclidean_distance(cal_vec.x_health, standard_vec.x_health, X_VEC_LENGTH)/X_VEC_LENGTH; 
	*(healthIndex+1) = 2*logsig(-(*(healthIndex+1)));
	//����Y�ὡ��ָ��
	*(healthIndex+2) = cal_Euclidean_distance(cal_vec.y_health, standard_vec.y_health, Y_VEC_LENGTH)/Y_VEC_LENGTH; 
	*(healthIndex+2) = 2*logsig(-(*(healthIndex+2)));
	//����Z�ὡ��ָ��
	*(healthIndex+3) = cal_Euclidean_distance(cal_vec.z_health, standard_vec.z_health, Z_VEC_LENGTH)/Z_VEC_LENGTH; 
	*(healthIndex+3) = 2*logsig(-(*(healthIndex+3)));
	//���㵶�⽡��ָ��
	*(healthIndex+4) = cal_Euclidean_distance(cal_vec.t_health, standard_vec.t_health, T_VEC_LENGTH)/T_VEC_LENGTH; 
	*(healthIndex+4) = 2*logsig(-(*(healthIndex+4)));
	//�����������ָ��
    *(healthIndex+5) = (*(healthIndex) + *(healthIndex+1) + *(healthIndex+2) + *(healthIndex+3) + *(healthIndex+4))/5;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int resetHistoryFile()
//
//    ���ܣ�
//            �������»�׼ʱ�����¼�����ʷ�Ľ���ָ��
//    ������
//            
//   
//    ������
//            ���������ɵĻ�׼���һ����׼�����¼�����ʷ�Ľ���ָ��
//    ����:
//            0���ɹ�
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

	//����ȡ����ǰ���������������㲢���潡��ָ��
	fseek(s_hfp.pstdfile,sizeof(int)+3*FEATURE_STRUCT_SIZE,SEEK_SET);
	for (i=0;i<RESET_STD_TIMES - 1; i++)//������ǰ����д�����β���д
	{
		//����ǰ�������¼��㽡��ָ��
		fread(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
		CalHealthIndex(healthIndex_buf);
		//������ʷ����ָ��
		fseek(p_historyFile,6*i*sizeof(fBit32),SEEK_SET);
		fwrite(healthIndex_buf,sizeof(fBit32),6,p_historyFile);
	}

	//���¶���������������������δ�����»�׼�����󽡿�ָ��
	fread(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fclose(p_historyFile);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//
//    int resetStdFile()
//
//    ���ܣ�
//            �����ɻ�׼�ļ�
//    ������
//            
//   
//    ������
//            ���Լ�ģ���ڻ�������30��ʱ�����¸��ݱ������������ɻ�׼
//    ����:
//            0���ɹ�
//            -1:
//            -2:
//////////////////////////////////////////////////////////////////////////
int resetStdFile()
{
	Bit32 i = 0, j = 0;
	Bit32 data_off = 0;
	struct stat finfo;
	fBit32 ftv_buf[RESET_STD_TIMES][VEC_TOTAL_LENGTH] = {0.0}; //������������ֵ����
	fBit32 ftv_base[VEC_TOTAL_LENGTH] = {0.0};  //�»�׼-�Ƚ�ֵ
	fBit32 ftv_max[VEC_TOTAL_LENGTH] = {0.0};   //��һ��-���ֵ
	fBit32 ftv_min[VEC_TOTAL_LENGTH] = {0.0};   //��һ��-��Сֵ
	fBit32 scale_cof = 0.2; //����ϵ��

	//��ȡ��׼�ļ���Ϣ
	if(stat(s_hfp.stdfilename, &finfo) <0)
	{
		//s_CalThreadErr_No = -1;
		return -1;
	}

	data_off = (Bit32)(sizeof(int)+3*FEATURE_STRUCT_SIZE);//��׼�ļ�ͷƫ��������ʷ����+1����׼����+2����һ��������
	//�ļ�ʵ�ʴ�С��Ԥ��һ�������¼�������»�׼
	if (finfo.st_size == (data_off+s_hfp.historyTestNum*FEATURE_STRUCT_SIZE) )
	{
		fseek(s_hfp.pstdfile,data_off,SEEK_SET);

		for (i =0;i<RESET_STD_TIMES;i++)
		{
			fread(&ftv_buf[i][0],FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
			//�ؼ����»�׼���һ����׼
			if (i == 0)
			{
				memcpy(ftv_max,&ftv_buf[0][0],FEATURE_STRUCT_SIZE);
				memcpy(ftv_min,&ftv_buf[0][0],FEATURE_STRUCT_SIZE);
			}

			for (j=0;j<VEC_TOTAL_LENGTH;j++)
			{
				//�»�׼
				ftv_base[j] += ftv_buf[i][j];
				//��һ��->���ֵ
				if(ftv_buf[i][j] > ftv_max[j]) 
					ftv_max[j] = ftv_buf[i][j];
				//��һ��->��Сֵ
				if(ftv_buf[i][j] < ftv_min[j]) 
					ftv_min[j] = ftv_buf[i][j];
			}
		}

		//���������»�׼���һ����׼
		for (j=0;j<VEC_TOTAL_LENGTH;j++)
		{
			ftv_base[j] = ftv_base[j]/RESET_STD_TIMES;
			ftv_max[j] = ftv_max[j]*(1+scale_cof);
			ftv_min[j] = ftv_min[j]*(1-scale_cof);
		}	
	} 
	else
	{
		return -2; //��׼�ļ���С�����ݸ�����һ��
	}

	//�»�׼���һ����׼д���׼�ļ�
	fseek(s_hfp.pstdfile,sizeof(int),SEEK_SET);
	fwrite(ftv_base,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fwrite(ftv_max,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);
	fwrite(ftv_min,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile);

	//���²����ṹ���е�����
	memcpy(&s_hfp.feat_base,ftv_base,FEATURE_STRUCT_SIZE);
	memcpy(&s_hfp.feat_max,ftv_max,FEATURE_STRUCT_SIZE);
	memcpy(&s_hfp.feat_min,ftv_min,FEATURE_STRUCT_SIZE);

	//�����»�׼���¼������ν���ָ��
	resetHistoryFile();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//    int SaveFeaVec()
//
//    ���ܣ�
//            ���μ���������������浽��׼�ļ���
//    ������
//            
//   
//    ������
//            
//    ����:
//            0���ɹ�
//            -1:д��ʧ��
//////////////////////////////////////////////////////////////////////////
int SaveFeaVec()
{
	if(s_hfp.pstdfile == NULL)
	{
		s_CalThreadErr_No = -18;
		longjmp(s_SetJmp,NULL_POINTER);//�ļ�ָ��Ϊ��
	}
	//�Լ������1
	s_hfp.historyTestNum++;
    fseek(s_hfp.pstdfile,0,SEEK_SET);
	if(fwrite(&s_hfp.historyTestNum,sizeof(int),1,s_hfp.pstdfile) != 1) 
	{
		s_CalThreadErr_No = -19;
		return -1;
	}
	//д�뱾���Լ����������
    fseek(s_hfp.pstdfile,0,SEEK_END);
	if(fwrite(&s_ftv,FEATURE_STRUCT_SIZE,1,s_hfp.pstdfile) != 1) 
	{
		s_CalThreadErr_No = -20;
		return -1;
	}
	//�ж��Ƿ���Ҫ��д��׼
	if (s_hfp.historyTestNum == RESET_STD_TIMES)
	{
		fflush(s_hfp.pstdfile);
		resetStdFile();
	}

	//�رջ�׼�ļ�
	fclose(s_hfp.pstdfile);
	s_hfp.pstdfile = NULL;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//
//    int HealthTestCalExit()
//
//    ���ܣ�
//            ������ϼ���ģ���˳�����
//    ������
//            
//   
//    ������
//            
//    ����:
//            0���ɹ�
//            -1:���������ļ��ر�ʧ��
//////////////////////////////////////////////////////////////////////////
int HealthTestCalExit()
{
	//�رղ��������ļ���ָ���ÿ�
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
	sprintf(filename_tmp,"%s%c%s",gCodePath,DIR_SEPARATOR,simpleFileName_1);		//G�����ļ�
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
	sprintf(filename_tmp,"%s%c%s",gCodePath,DIR_SEPARATOR,simpleFileName_2);		//G�����ļ�
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
//    ���ܣ�
//            �����̵߳ļ������ˢ�´�ӡ
//    ������
//            reset_tmp_No���Ƿ������ڲ��ֲ���̬����  Ĭ��fault:������
//   
//    ������
//            
//    ����:
//            ��
//////////////////////////////////////////////////////////////////////////
void CalThread_StepPrint_Refresh(bool reset_tmp_No) 
{
	static int tmp_No;  //�ֲ���̬��������->��¼ˢ�µ��Ĳ���

	Bit32 height = 0;
	Bit32 width = 0;
	Bit32 left = 0;
	Bit32 top = 0;
	Bit8 info_tmp[256] = {0};
	FILE *fp = NULL;

	Bit8 dataPath[128] = {'\0'};
	Bit8 fullname[128] = {'\0'};
	Bit8 filename[128]  = "CalStep_Print.txt";

	//�����ڲ��ֲ���̬����Ϊ0
	if (reset_tmp_No)   
	{
		tmp_No = 0;  
		return;
	}
	//�Ѿ���ӡ���µļ��㲽�裬��ˢ��
	if (tmp_No == s_CalThreadStep_No)
	{
		return;     
	}

	height = (USER_BOTTOM-USER_TOP)/20;
	width = (USER_RIGHT - USER_LEFT);
	//���ݲ���Ŵ�ӡ��Ϣ
	if (s_CalThreadStep_No > 0)     //���쳣����
	{
		left = USER_LEFT;
		switch (s_CalThreadStep_No)
		{
		case 1:
			sprintf(info_tmp,"���� 1: %s\r\n","������ʼ�� ����");
			top = USER_TOP+0*height;
			break;
		case 2:
			sprintf(info_tmp,"���� 2: %s\r\n","����G���� ����");
			top = USER_TOP+1*height;
			break;
		case 3:
			sprintf(info_tmp,"���� 3: %s\r\n","�����������ļ� ����");
			top = USER_TOP+2*height;
			break;
		case 4:
			sprintf(info_tmp,"���� 4: %s\r\n","����R116�Ĵ����ź� ����");
			top = USER_TOP+3*height;
			break;
		case 5:
			sprintf(info_tmp,"���� 5: %s\r\n","������׼�ļ� ����");
			top = USER_TOP+4*height;
			break;
		case 6:
			sprintf(info_tmp,"���� 6: %s\r\n","����������ȡ ����");
			top = USER_TOP+5*height;
			break;
		case 7:
			sprintf(info_tmp,"���� 7: %s\r\n","����������ȡ ����");
			top = USER_TOP+6*height;
			break;
		case 8:
			sprintf(info_tmp,"���� 8: %s\r\n","�����ᣨX/Y/Z��������ȡ ����");
			top = USER_TOP+7*height;
			break;
		case 9:
			sprintf(info_tmp,"���� 9: %s\r\n","���汾���������� ����");
			top = USER_TOP+8*height;
			break;
		case 10:
			sprintf(info_tmp,"���� 10: %s\r\n","����ָ������ ����");
			top = USER_TOP+9*height;
			break;
		case 11:
			sprintf(info_tmp,"���� 11: %s\r\n","��������˳����� ����");
			top = USER_TOP+10*height;
			break;
		default:
			sprintf(info_tmp,"default: %s\r\n","ȱʡֵ");
			top = USER_TOP+11*height;
			break;
		}
	}
	else    // �쳣����
	{
		left = USER_LEFT;
		switch (s_CalThreadStep_No)
		{
		case -1:
			sprintf(info_tmp,"���� 1: %s\r\n","������ʼ�� �쳣:��ȡ�����ļ���Ϣʧ��!");
			top = USER_TOP+0*height;
			break;

		case -2:
			sprintf(info_tmp,"���� 2: %s\r\n","����G���� �쳣:G�����ʧ��!");
			top = USER_TOP+1*height;
			break;
		case -3:
			sprintf(info_tmp,"���� 2: %s\r\n","����G���� �쳣:G������ȡ������ز���ʧ��!");
			top = USER_TOP+1*height;
			break;
		case -4:
			sprintf(info_tmp,"���� 2: %s\r\n","����G���� �쳣:G������ȡ��������ز���ʧ��!");
			top = USER_TOP+1*height;
			break;
		case -5:
			sprintf(info_tmp,"���� 2: %s\r\n","����G���� �쳣:G������ȡ������ز���ʧ��!");
			top = USER_TOP+1*height;
			break;

		case -6:
			sprintf(info_tmp,"���� 3: %s\r\n","�����������ļ� �쳣:�򿪲��������ļ�ʧ��!");
			top = USER_TOP+2*height;
			break;

		case -7:
			sprintf(info_tmp,"���� 4: %s\r\n","����R116�Ĵ����ź� �쳣:R116�м��λ�ļ���ʧ��!");
			top = USER_TOP+3*height;
			break;
		case -8:
			sprintf(info_tmp,"���� 4: %s\r\n","����R116�Ĵ����ź� �쳣:δ�ҵ���������������!");
			top = USER_TOP+3*height;
			break;
		case -9:
			sprintf(info_tmp,"���� 4: %s\r\n","����R116�Ĵ����ź� �쳣:ĳ��λ�ź�ȫΪ0 !");
			top = USER_TOP+3*height;
			break;

		case -10:
			sprintf(info_tmp,"���� 5: %s\r\n","������׼�ļ� �쳣:��׼�ļ���ʧ��!");
			top = USER_TOP+4*height;
			break;
		case -11:
			sprintf(info_tmp,"���� 5: %s\r\n","������׼�ļ� �쳣:���ݶ�ȡʧ��!");
			top = USER_TOP+4*height;
			break;

		case -12:
			sprintf(info_tmp,"���� 6: %s\r\n","����������ȡ �쳣:�м��ļ���ʧ��!");
			top = USER_TOP+5*height;
			break;
		case -13:
			sprintf(info_tmp,"���� 6: %s\r\n","����������ȡ �쳣:δ�ҵ������ж�Ӧ���ݵ�!");
			top = USER_TOP+5*height;
			break;

		case -14:
			sprintf(info_tmp,"���� 7: %s\r\n","����������ȡ �쳣:�кŲ�����0 !");
			top = USER_TOP+6*height;
			break;

		case -15:
			sprintf(info_tmp,"���� 8: %s\r\n","�����ᣨX/Y/Z��������ȡ �쳣:X��������ȡʧ��!");
			top = USER_TOP+7*height;
			break;
		case -16:
			sprintf(info_tmp,"���� 8: %s\r\n","�����ᣨX/Y/Z��������ȡ �쳣:Y��������ȡʧ��!");
			top = USER_TOP+7*height;
			break;
		case -17:
			sprintf(info_tmp,"���� 8: %s\r\n","�����ᣨX/Y/Z��������ȡ �쳣:Z��������ȡʧ��!");
			top = USER_TOP+7*height;
			break;

		case -18:
			sprintf(info_tmp,"���� 9: %s\r\n","���汾���������� �쳣:��׼�ļ�ָ��Ϊ��!");
			top = USER_TOP+9*height;
			break;
		case -19:
			sprintf(info_tmp,"���� 9: %s\r\n","���汾���������� �쳣:д����ʷ�Լ����ʧ��!");
			top = USER_TOP+9*height;
			break;
		case -20:
			sprintf(info_tmp,"���� 9: %s\r\n","���汾���������� �쳣:д�뱾����������ʧ��!");
			top = USER_TOP+9*height;
			break;

		case -21:
			sprintf(info_tmp,"���� 10: %s\r\n","����ָ������ �쳣:��һ��ʧ��!");
			top = USER_TOP+8*height;
			break;

		case -22:
			sprintf(info_tmp,"���� 11: %s\r\n","��������˳����� �쳣:�رղ��������ļ�ʧ��!");
			top = USER_TOP+10*height;
			break;

		default:
			sprintf(info_tmp,"default: %s\r\n","ȱʡֵ");
			top = USER_TOP+11*height;
			break;
		}
	}
	//
	cstr_out_mul_line(left,top,width,height,info_tmp,COLOR_TEXT,COLOR_BACK,textLEFT,IS12);

	tmp_No = s_CalThreadStep_No;

	//������Ҫ��ѡ���Ƿ��¼���㲽�赽�ļ�
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
//    ���ܣ�
//            �����̵߳ļ���������ã����ڽ�����ʾ
//    ������
//            step_No�� ������̱��
//   
//    ������
//            
//    ����:
//            ��
//////////////////////////////////////////////////////////////////////////
void CalThread_Step_Set(int step_No) 
{
	// ������̱������
	s_CalThreadStep_No = step_No;
	//���������ʾ����ˢ��
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