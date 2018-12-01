/**************************************************
 * 嵌入式事件驱动框架
 *			 4.增加一个运行时监测调试方案
 * 			 5. ...
 *
 */

#include "eframe.h"

/* handler函数都注册到此数组  */
handler_t ef_handler_list[MAX_HANDLER_AMOUNT] = {0}; //事件处理函数数组
event_t event_cnt = 10; // 1-10为框架内置事件,用户事件从11开始

// 事件没有对应的响应程序的时候执行该函数
efPROC(ef_handle_null)
{

	// do something to handle the event without handler
	printf("null process function\n");	// For PC
}

/* 
 * 事件队列部分
 * ef_queue_size() 队列元素长度
 * ef_queue_add(event)  队尾追加
 * ef_queue_poll()  取队头
 */
event_t ef_eventqueue[REAL_LEN] = { 0 };	// 待处理事件队列

static event_t _tail = 0;
static event_t _head = 0;

#define ef_queue_size() (_tail >= _head ? _tail - _head: REAL_LEN - _head + _tail)
err_t ef_queue_add(const event_t e)
{
	u8 temp_tail = _tail + 1 == REAL_LEN ? 0 : _tail + 1;
	if (ef_queue_size() == REAL_LEN - 1) {
		return FAIL;
	}
	ef_eventqueue[_tail = temp_tail] = e;
	return SUCCESS;
}

event_t ef_queue_poll()
{
	u8 temp_head = _head + 1 == REAL_LEN ? 0 : _head + 1;
	if (!ef_queue_size()) {
		return EFNONE_EVENT;
	}
	return ef_eventqueue[_head = temp_head];
}

// 事件触发部分
err_t ef_post(const event_t e)
{
	err_t err = SUCCESS;
	atomic(
		err = ef_queue_add(e);
	      );
	return err;
}

void ef_idle(void)
{
// while(ef_queue_size() == 0) {
    // halt()
    printf("waked, but no event. continue sleep\n");
// }
}

void ef_scheduler_run(void)
{
	event_t e = EFNONE_EVENT;
	while ((e = ef_queue_poll()) != EFNONE_EVENT) {
		ef_handle_event(e);
	}
	ef_idle();
}

