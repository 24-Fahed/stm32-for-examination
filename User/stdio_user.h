#ifndef __STDIO_USER_H__
#define __STDIO_USER_H__

// define
//
#define MAX_FLOW_BUFFER 30

// struct of data_buffer
struct DataFlow {
	char data[MAX_FLOW_BUFFER];
	int header;
	int tail;
    unsigned char lock;                 // 访问锁，0：没有占用 1：正在占用
};

typedef struct DataFlow DataFlow;
typedef struct DataFlow * DataFlow_Ptr;


static DataFlow stdio_buffer_list = {
	'\0', 0, 0, 0
};

void Stdio_Buffer_Init(void);

// 字符流操作方法
//
int Load_Data(char ch, DataFlow_Ptr DFP);
int Load_String(char *str, DataFlow_Ptr DFP);
char *Read_Data(DataFlow_Ptr DFP);
int Clear_DataFlow(DataFlow_Ptr DFP);

int unget_Char(DataFlow_Ptr DFP);

int IsNull(DataFlow_Ptr DFP);

/*
static int inline IsLocked(DataFlow_Ptr DFP) {
    return (DFP->tail == 1);                        // 是否上锁，是返回1，否返回非1
}
*/

static int inline IsEmpty(DataFlow_Ptr DFP) {
    return (DFP->header) == (DFP->tail);
}

// 编写模式说明：将原数据指定字符从结构中复制出来，放置到指定的target位置上
char get_char(DataFlow_Ptr DFP);
char *get_String_Data(DataFlow_Ptr DFP);
char get_Word(DataFlow_Ptr DFsource, char *target);
DataFlow_Ptr get_StdioBuffer(void);

// 依赖工具: 操作方式为由指针到指针
//
// 复制字符串到指定位置
char *ustrcpy(char *source, char *target);  // 字符串拷贝
int   ustrcmp(char *csOne, char *csTwo);    // 字符串对比
int   ustrlen(char *source);                // 返回字符串长度

int char_to_int(char *source);              // char转换int


#endif // __STDIO_USER_H__
