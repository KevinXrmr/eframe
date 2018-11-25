#ifndef __TEFRAME_H__
#define  __TEFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
// typedef u16 EVENTTYPE;
typedef u8 PROC;

/*EN
 *
 */
 
/*CH
 * �������ÿ���¼�����Ӧ�����ķ���ֵ��������PROC(u8)���͡���
 * �պ������Ҫ������Ӧ�����������Ļ��ƣ�ͬ�����ƣ���ʱ���Ҫ�з���ֵ��
 */
typedef PROC (*PROCTYPE)(void);   
#define MAX_PROC_AMOUNT 10

/* �¼����� */
/* 
#define EVENT_0  0
#define EVENT_1	 1 
#define EVENT_2	 2 
#define EVENT_3	 3 
#define EVENT_4	 4 
#define EVENT_5  5
#define EVENT_6	 6 
#define EVENT_7	 7 
#define EVENT_8	 8 
#define EVENT_9	 9 
*/

// Ԥ�����¼�����, �����¼�������Ҫʹ��event_bind(e, n)��Ԥ�����¼���
// ��Ϊ����ڲ���ʹ��Ԥ�����¼�����,
typedef enum EVENT_NUM {
  EVENT_0 = 0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4,
  EVENT_5,
  EVENT_6,  
} EVENTTYPE;
// #define EVENT_MOUNT  5   //�¼�����
extern u8 EVENT_MOUNT;
#define setProcNum(n) EVENT_MOUNT = n
  
// ����󶨽�����һ����ֵ����,����¼�������Ҫ��ȫ�ַ�Χ��
// ���Ӧ��֧���¼���̬ע���ɾ�� 
#define event_bind(e, n)  e = EVENT_##n

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
 * �����¼���ö�Ӧ�¼�������
 */
#define get_proc(event) (proc_queue[event] ? proc_queue[event] : proc_null)
#endif // __TEFRAME_H__
