#ifndef __EFRAME_H__
#define  __EFRAME_H__
#include <stdio.h>		// For PC

typedef unsigned int u16;
typedef unsigned char u8;
typedef u8 event_t;
typedef enum {
  SUCCESS = 0,
  FAIL 
} err_t;
 
/*CH
 * �¼�handler����Ϊvoid xx(void)
 */ 
#define efPROC(event) void event(void)	// �����¼��������ķ�ʽ
typedef void (*handler_t) (void);
 
#define MAX_HANDLER_AMOUNT 10	// ������¼���������
    
#define MAX_QUEUE 10
// ����ͷ���Ϊ�ڱ�,���ʵ�ʶ��г���Ϊ��Ч���ݳ���+1
#define REAL_LEN MAX_QUEUE + 1	// �������¼����г���
    
// 0��Ϊ���¼�
#define EFNONE_EVENT 0
static event_t event_cnt = EFNONE_EVENT;
 
// ��ʼ���¼�����, ÿ�λ��һ���¼�ID
#define ef_event_init() ++event_cnt
    
/* ��Ӧ�������ص�״̬�� */ 
#define DEFAULT 0		//Ĭ��״̬�루�����壩
#define NO_PROC 1		//û����Ӧ����
    
/* ��Ӧ������� */ 
extern handler_t ef_handler_list[MAX_HANDLER_AMOUNT];
  
/* ��Ӧ�������¼��� */ 
#define ef_bindhandler(event, handler) \
do {\
 ef_handler_list[event] = handler;\
} while (0)
 
/**
 * ��ȡ�¼���Ӧ�Ĵ������
 */ 
extern efPROC(ef_handle_null);	// �մ�����

/* �����¼�,���ô����¼��Ĺ��̻ص����� */ 
#define ef_handle_event(event)\
do {\
 (ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null) ();\
} while (0)
 

// ��Ҫ��ֲ
#define ef_idle()\
do {\
 printf("idle handler, MCU enter the halt()\n");\
} while (0)
 
// ��Ҫ��ֲ
// ����ԭ�Ӳ���,�ڽ���ʱӦ����������жϴ���,�˳�ʱ�ָ�
#define atomic(s) \
do {\
 printf("enter atomic regeion\n");\
 s \
 printf("exit atomic regeion\n");\
} while (0)

extern err_t ef_post(event_t e);
extern void ef_scheduler_run(void);

#endif // __TFRAME_H__


