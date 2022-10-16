#include "stdio_user.h"
#include "stdio.h"
#include "stm32f10x.h"

extern DataFlow stdio_buffer_list;

/*=============================函数重写===========================*/
// 重定义printf输出方向
int fputc(int ch, FILE  *f) {
    // 发送ch
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    return(ch);
}

// 输入栈测试
void Stdio_Buffer_Init(void) {
    // 初始化输入输出栈
    if ((&stdio_buffer_list) == NULL) {
        while (1);
    }
    stdio_buffer_list.data[0] = '\0';
    stdio_buffer_list.header = 0;
    stdio_buffer_list.lock = 0;
    stdio_buffer_list.tail = 0;
}

// 载入字符串，如果载入成功，返回当前字符的ascii
int Load_Data(char ch, DataFlow_Ptr DFP) {
	// 检测是否已经分配空间
	if (DFP == NULL || &(DFP->data) == NULL) {
		return -1;			// 返回负值标志错误
	}
	if (DFP->tail >= MAX_FLOW_BUFFER) {
		return -2;			// 
	}
	// 将数据载入
	DFP->data[DFP->tail++] = ch;
	DFP->data[DFP->tail] = '\0';		// 最后一个字符一定是\0
	return ch;
}

int Load_String(char *str, DataFlow_Ptr DFP) {
    // 计算长度
    int len = ustrlen(str);
    // 检测是否已经分配空间
    if (DFP == NULL || &(DFP->data) == NULL)
        return -1;
    if ((DFP->tail) + len >= MAX_FLOW_BUFFER)
        return -2;
    // 将数据复制到结构中
    char *String = (DFP->data) + (DFP->tail);
    ustrcpy(str, String);
    // 更改指针位置
    DFP->tail += len;
    return DFP->tail;
}

// 返回结构中数据的字符串指针
char *Read_Data(DataFlow_Ptr DFP) {
	if (DFP != NULL) {
		return &(DFP->data[0]);
	}
	return NULL;				// 传入数据为空
}

// 清除数据
int Clear_DataFlow(DataFlow_Ptr DFP) {
	int i;
	if (DFP == NULL) {
		return -1;
	}
	for (i = 0; i < MAX_FLOW_BUFFER; i++) {
		DFP->data[i] = '\0';
	}
	DFP->header = 0;
	DFP->tail = 0;
	return 0;
}

int unget_Char(DataFlow_Ptr DFP) {
    // 将最近读取到的一个数据删除，返回这个字符
    char tmpCall;
    if (DFP->tail == DFP->header) {
        return -1;                          // 栈空，没有数据可以回退
    }
    tmpCall = DFP->data[DFP -> tail];
    DFP->data[--(DFP->tail)] = '\0';
    return tmpCall;
}

// 判断队空，返回判断结果
int IsNull(DataFlow_Ptr DFP) {
    return (DFP->header) == (DFP->tail);
}


// 从结构中去除一个字符，如果没有已经读取完毕，则返回‘\0’
char get_char(DataFlow_Ptr DFP) {
	if (DFP != NULL) {
		if ((DFP->header) < (DFP->tail)) {
			return DFP->data[DFP->header++];
		}
	}
	return '\0';
}

char *get_String_Data(DataFlow_Ptr DFP) {
    return DFP->data;
}


// 获取单词，一次返回一个单词，如果已经读取完毕，则返回‘\0’，如果没有结束，则返回非\
// 0
char get_Word(DataFlow_Ptr DFsource, char *target) {
    // 测试
    // printf("getword test printf: source: %s target: %s \n", get_String_Data(DFsource), target);
    // getchar在12 34 67  34 77下找不到任何单词（../cmd_timer.c）
    
	char c;
	while ((c = get_char(DFsource)) == ' ');			// 逻辑问题

	do {
		if (c == ' ' || c == '\0') {
			break;				// 单词结束
		}
		*target++ = c;				// 复制数据
	} while ((c = get_char(DFsource)) != '\0');
	
	*target = '\0';
	return c;					// 当句段结束的时候会返回'\0’
}


DataFlow_Ptr get_StdioBuffer(void) {
	return &stdio_buffer_list;
}


// 将一个数据复制到另一个位置（char为基本单位）.注意：该函数需要考虑target溢出的问题
// 该函数直接在原数值上做修改，也会返回复制的target
char *ustrcpy(char *source, char *target) {
	while (*source != '\0') {
		*target++ = *source++;
	}
	return target;
}

// 字符串比较
int ustrcmp(char *csOne, char *csTwo) {
	while (*csOne++ == *csTwo++) {
		if (*csOne == '\0' && *csTwo == '\0')	return 0;
	}
	return -1;
}

int ustrlen(char *source) {
    // 如果char在ascii中表示数字的位置
    // 统计数量
    char *tmp_call = source;
    int sum = 0;
    while (*(++tmp_call) != '\0');
    sum = tmp_call - source;             // 计算字符串总述
    
    return sum;                           // 字符串总数
}

int char_to_int(char *source) {
    printf("change pograms rec: %s \n", source);
    int sum = 0;
    int len = ustrlen(source);
    for (char *tempCall = source; tempCall !=  '\0'; tempCall++) {
        if (*(tempCall) >= 48 && *(tempCall) < 58) {
            sum = (sum * 10) + (*(tempCall) - '0');
        } else {
            return -1;
        }
    }
    return sum;
}


