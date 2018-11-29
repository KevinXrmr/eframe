/**************************************************
 * Ƕ��ʽ�¼��������
 * Ŀ��: 1.���֧��һ�׽�Ϊ������ϵͳdebug����
 *			 4.����һ������ʱ�����Է���
 * 			 5. ...
 *
 */
#include <stdio.h> // For PC
  
 
 /*
  * @API List��
    *                       efPROC(eventname) �����¼�����handler
	*		                ef_setevent(EVENTTYPE event, num) //�����û��¼����
    *                       ef_bindhandler(event, handler)		//���¼�������Ӧ����
	*						handle_event(EVENTTYPE event) //�����¼�ִ��handler����(��eframe.h�к궨��)
	*
	* @breif: 
	*						Ϊ��֤����Ч�ʣ���Ӧ�������¼�֮��ֱ��ͨ�������Ӧ
	*	@todo 		�Ľ�Ŀ�꣺�ù�ϣ��ɢ�к���������һά���顣
	*/
#include "eframe.h"	


/* handler������ע�ᵽ������  */
PROCTYPE  ef_handler_list[MAX_HANDLER_AMOUNT] = {0};//�¼�����������
EVENTTYPE ef_eventqueue[MAX_EVENT_QUEUELEN] = {0}; // �������¼�����

// �¼�û�ж�Ӧ����Ӧ�����ʱ��ִ�иú���
efPROC(ef_handle_null)
{
  // do something to handle the event without handler
    printf("null process function\n"); // For PC
}

static u8 ef_eventqueue_idx = 0;

/* 
 * ����һ���¼�����β,����ʧ�ܷ���1,���򷵻�1
 */
u8 ef_event_add(EVENTTYPE e)
{ 
  if(ef_eventqueue_idx >= MAX_EVENT_QUEUELEN)
    return 1;
  
  atomic(
         ef_eventqueue[ef_eventqueue_idx++] = e;
         );
  return 0;
}

// ��Ʋ��Ҳ��븴�Ӷȶ�Ϊ1�Ķ���
EVENTTYPE ef_event_poll()
{
  if(ef_eventqueue_idx == 0)
    return EFNONE_EVENT;
  return ef_eventqueue[ef_eventqueue_idx];
}
