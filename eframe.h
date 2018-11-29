#ifndef __EFRAME_H__
#define  __EFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
// typedef u8 efPROC;

/*EN
 *
 */
 
/*CH
 * �������ÿ���¼�����Ӧ�����ķ���ֵ��������PROC(u8)���͡���
 * �պ������Ҫ������Ӧ�����������Ļ��ƣ�ͬ�����ƣ���ʱ���Ҫ�з���ֵ��
 */
#define efPROC(event) void event(void) // �����¼��������ķ�ʽ
typedef void (*PROCTYPE)(void);   

#define MAX_HANDLER_AMOUNT 10 // ������¼���������
#define MAX_EVENT_QUEUELEN 5 // �������¼����г���

// Ԥ�����¼�����, �����¼�������Ҫʹ��event_bind(e, n)��Ԥ�����¼���
// ��Ϊ����ڲ���ʹ��Ԥ�����¼�����,
typedef enum EVENT_NUM {
  EFNONE_EVENT = 0,
  EFEVENT_1,
  EFEVENT_2,
  EFEVENT_3,
  EFEVENT_4,
  EFEVENT_5,
  EFEVENT_6,
  EFEVENT_7,
  EFEVENT_8,
  EFEVENT_9,    
} EVENTTYPE;
  
// ����󶨽�����һ����ֵ����,����¼�������Ҫ��ȫ�ַ�Χ��
// ���Ӧ��֧���¼���̬ע���ɾ�� 
#define ef_setevent(e, n) EVENTTYPE e = EFEVENT_##n;  // �����û������¼��󶨵�Ԥ�����¼�

/* ��Ӧ�������ص�״̬�� */
#define DEFAULT 0  //Ĭ��״̬�루�����壩
#define NO_PROC 1  //û����Ӧ����

/**
 * ��Ӧ�������
 */
extern PROCTYPE ef_handler_list[MAX_HANDLER_AMOUNT];


/**
 * ��Ӧ�������¼���
 */
#define ef_bindhandler(event, handler) \
do { \
    ef_handler_list[event] = handler; \
   } while(0)

/**
 * ��ȡ�¼���Ӧ�Ĵ������
 */
extern efPROC(ef_handle_null); // �մ�����

/** 
 * �����¼�,���ô����¼��Ĺ��̻ص�����
 */
#define ef_handle_event(event)\
do {\
    (ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null)();\
   } while(0)

// ��Ҫ��ֲ
#define ef_idle()\
  do{\
    printf("idle handler, MCU enter the halt()\n");\
  }while(0)

// ��Ҫ��ֲ
// ����ԭ�Ӳ���,�ڽ���ʱӦ����������жϴ���,�˳�ʱ�ָ�
#define atomic(s) \
  do{\
  printf("enter atomic regeion\n");\
  s \
  printf("exit atomic regeion\n");\
} while(0)


extern u8 ef_event_add(EVENTTYPE e);
#endif // __TFRAME_H__
