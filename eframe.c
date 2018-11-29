/**************************************************
 * Ƕ��ʽ�¼��������
 *			 4.����һ������ʱ�����Է���
 * 			 5. ...
 *
 */
 
 /*
  * @API List��
    *                       efPROC(eventname) �����¼�����handler
	*		                ef_setevent(event_t event, num) //�����û��¼����
    *                       ef_bindhandler(event, handler)		//���¼�������Ӧ����
	*						handle_event(event_t event) //�����¼�ִ��handler����(��eframe.h�к궨��)
	*
	*/
#include "eframe.h"	


/* handler������ע�ᵽ������  */
handler_t  ef_handler_list[MAX_HANDLER_AMOUNT] = {0};//�¼�����������

// �¼�û�ж�Ӧ����Ӧ�����ʱ��ִ�иú���
efPROC(ef_handle_null)
{
  // do something to handle the event without handler
    printf("null process function\n"); // For PC
}


/* 
 * �¼����в���
 * ef_queue_size() ����Ԫ�س���
 * ef_queue_add(event)  ��β׷��
 * ef_queue_poll()  ȡ��ͷ
 */
event_t ef_eventqueue[REAL_LEN] = {0}; // �������¼�����

static event_t _tail = 0;
static event_t _head = 0;

#define ef_queue_size() (_tail >= _head ? _tail - _head: REAL_LEN - _head + _tail)

err_t ef_queue_add(event_t e)
{
  u8 temp_tail = _tail + 1 == REAL_LEN ? 0 : _tail + 1;
  if(ef_queue_size() == REAL_LEN - 1) {
    return FAIL;
  }    
  ef_eventqueue[_tail = temp_tail] = e;
  return SUCCESS;
}

event_t ef_queue_poll()
{
  u8 temp_head = _head + 1 == REAL_LEN ? 0 : _head + 1;
  if(!ef_queue_size()){
    return EFNONE_EVENT;
  }
  return ef_eventqueue[_head = temp_head];  
}

// �¼���������
err_t ef_post(event_t e)
{
  err_t err = SUCCESS;
  atomic(
         err = ef_queue_add(e);
  );
  return err;
}

void ef_scheduler_run(void)
{
  event_t e = EFNONE_EVENT;
  while((e = ef_queue_poll()) != EFNONE_EVENT) {
    ef_handle_event(e);
  }
  ef_idle();
}

