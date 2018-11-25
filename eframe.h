#ifndef __EFRAME_H__
#define  __EFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
typedef u8 PROC;

/*EN
 *
 */
 
/*CH
 * �������ÿ���¼�����Ӧ�����ķ���ֵ��������PROC(u8)���͡���
 * �պ������Ҫ������Ӧ�����������Ļ��ƣ�ͬ�����ƣ���ʱ���Ҫ�з���ֵ��
 */
typedef PROC (*PROCTYPE)(void);   
#define MAX_PROC_AMOUNT 10 // ������¼���������


// Ԥ�����¼�����, �����¼�������Ҫʹ��event_bind(e, n)��Ԥ�����¼���
// ��Ϊ����ڲ���ʹ��Ԥ�����¼�����,
typedef enum EVENT_NUM {
  NULL_EVENT = 0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4,
  EVENT_5,
  EVENT_6,
  EVENT_7,
  EVENT_8,
  EVENT_9,    
} EVENTTYPE;
  
// ����󶨽�����һ����ֵ����,����¼�������Ҫ��ȫ�ַ�Χ��
// ���Ӧ��֧���¼���̬ע���ɾ�� 
#define event_bind(e, n)  e = EVENT_##n  // �����û������¼��󶨵�Ԥ�����¼�

/* ��Ӧ�������ص�״̬�� */
#define DEFAULT 0  //Ĭ��״̬�루�����壩
#define NO_PROC 1  //û����Ӧ����

/**
 * ��Ӧ�������
 */
extern PROCTYPE  proc_queue[MAX_PROC_AMOUNT];


/**
 * ��Ӧ�������¼���
 */
#define proc_bind(event, proc) \
				do{ \
					proc_queue[event] = proc; \
				}while(0)

/**
 * ��ȡ�¼���Ӧ�Ĵ������
 */
extern PROCTYPE get_proc(EVENTTYPE event);
extern PROC proc_null(void); // �մ�����

/** 
 * �����¼�,���ô����¼��Ĺ��̻ص�����
 */
#define event_proc(event) (proc_queue[event] ? proc_queue[event] : proc_null)()
#endif // __TFRAME_H__
