//////#ifndef FREERTOS_CONFIG_H
//////#define FREERTOS_CONFIG_H

//////#include "stm32f4xx.h"



//////#define configUSE_PREEMPTION 1
//////#define configUSE_TICKLESS_IDLE 0
//////#define configCPU_CLOCK_HZ     (SystemCoreClock)
//////#define configTICK_RATE_HZ ((TickType_t)1000)
//////#define configMAX_PRIORITIES (18)
//////#define configMINIMAL_STACK_SIZE ((unsigned short)90)
//////#define configMAX_TASK_NAME_LEN (10)
//////#define configUSE_16_BIT_TICKS 0
//////#define configIDLE_SHOULD_YIELD 1
//////#define configUSE_TASK_NOTIFICATIONS 1
//////#define configUSE_MUTEXES 1
//////#define configUSE_RECURSIVE_MUTEXES 1
//////#define configUSE_COUNTING_SEMAPHORES 1
//////#define configUSE_ALTERNATIVE_API 0 /* Deprecated! */
//////#define configQUEUE_REGISTRY_SIZE 8
//////#define configUSE_QUEUE_SETS 0
//////#define configUSE_TIME_SLICING 1
//////#define configUSE_NEWLIB_REENTRANT 0
//////#define configENABLE_BACKWARD_COMPATIBILITY 1
//////#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5
//////#define configUSE_APPLICATION_TASK_TAG          0

///////* Used memory allocation (heap_x.c) */
//////#define configFRTOS_MEMORY_SCHEME               3
///////* Tasks.c additions (e.g. Thread Aware Debug capability) */
//////#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1

///////* Memory allocation related definitions. */
//////#define configSUPPORT_STATIC_ALLOCATION         0
//////#define configSUPPORT_DYNAMIC_ALLOCATION        1
///////*#define configTOTAL_HEAP_SIZE                   0  not used by heap_3.c allocator */
//////#define configAPPLICATION_ALLOCATED_HEAP        0

///////* Hook function related definitions. */
//////#define configUSE_IDLE_HOOK                     0
//////#define configUSE_TICK_HOOK                     0
//////#define configCHECK_FOR_STACK_OVERFLOW          0
//////#define configUSE_MALLOC_FAILED_HOOK            0
//////#define configUSE_DAEMON_TASK_STARTUP_HOOK      0

///////* Run time and task stats gathering related definitions. */
//////#define configGENERATE_RUN_TIME_STATS           0
//////#define configUSE_TRACE_FACILITY                1
//////#define configUSE_STATS_FORMATTING_FUNCTIONS    1

///////* Co-routine related definitions. */
//////#define configUSE_CO_ROUTINES                   0
//////#define configMAX_CO_ROUTINE_PRIORITIES         2

///////* Software timer related definitions. */
//////#define configUSE_TIMERS 1
//////#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)
//////#define configTIMER_QUEUE_LENGTH 10
//////#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE * 2)

/////////* Define to trap errors during development. */
//////#define configASSERT_DEFINED 1
//////#define configASSERT(x)           \
//////    if ((x) == 0)                 \
//////    {                             \
//////        taskDISABLE_INTERRUPTS(); \
//////        for (;;)                  \
//////            ;                     \
//////    }

///////* Optional functions - most linkers will remove unused functions anyway. */
//////#define INCLUDE_vTaskPrioritySet                1
//////#define INCLUDE_uxTaskPriorityGet               1
//////#define INCLUDE_vTaskDelete                     1
//////#define INCLUDE_vTaskSuspend                    1
//////#define INCLUDE_xResumeFromISR                  1
//////#define INCLUDE_vTaskDelayUntil                 1
//////#define INCLUDE_vTaskDelay                      1
//////#define INCLUDE_xTaskGetSchedulerState          1
//////#define INCLUDE_xTaskGetCurrentTaskHandle       1
//////#define INCLUDE_uxTaskGetStackHighWaterMark     0
//////#define INCLUDE_xTaskGetIdleTaskHandle          0
//////#define INCLUDE_eTaskGetState                   1
//////#define INCLUDE_xEventGroupSetBitFromISR        1
//////#define INCLUDE_xTimerPendFunctionCall          1
//////#define INCLUDE_xTaskAbortDelay                 0
//////#define INCLUDE_xTaskGetHandle                  0
//////#define INCLUDE_xTaskResumeFromISR              1
//////#define INCLUDE_xTaskIsTaskFinished                 ( 1 )

////////

///////* Interrupt nesting behaviour configuration. Cortex-M specific. */
//////#ifdef __NVIC_PRIO_BITS
///////* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
//////#define configPRIO_BITS __NVIC_PRIO_BITS
//////#else
//////#define configPRIO_BITS 4 /* 15 priority levels */
//////#endif

///////* The lowest interrupt priority that can be used in a call to a "set priority"
//////function. */
//////#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY ((1U << (configPRIO_BITS)) - 1)

///////* The highest interrupt priority that can be used by any interrupt service
//////routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
//////INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
//////PRIORITY THAN THIS! (higher priorities are lower numeric values. */
//////#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 2

///////* Interrupt priorities used by the kernel port layer itself.  These are generic
//////to all Cortex-M ports, and do not rely on any particular library functions. */
//////#define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
///////* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
//////See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
//////#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

///////* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
//////standard names. */
//////#define vPortSVCHandler SVC_Handler
//////#define xPortPendSVHandler PendSV_Handler
//////#define xPortSysTickHandler SysTick_Handler






//////#endif /* FREERTOS_CONFIG_H */






#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"


//��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ�
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//����
#define vAssertCalled(char,int)  printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

/************************************************************************
 *               FreeRTOS������������ѡ�� 
 *********************************************************************/
/* ��1��RTOSʹ����ռʽ����������0��RTOSʹ��Э��ʽ��������ʱ��Ƭ��
 * 
 * ע���ڶ������������ϣ�����ϵͳ���Է�Ϊ��ռʽ��Э��ʽ���֡�
 * Э��ʽ����ϵͳ�����������ͷ�CPU���л�����һ������
 * �����л���ʱ����ȫȡ�����������е�����
 */
#define configUSE_PREEMPTION					  1

//1ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_TIME_SLICING					1		

/* ĳЩ����FreeRTOS��Ӳ�������ַ���ѡ����һ��Ҫִ�е�����
 * ͨ�÷������ض���Ӳ���ķ��������¼�ơ����ⷽ��������
 * 
 * ͨ�÷�����
 *      1.configUSE_PORT_OPTIMISED_TASK_SELECTION Ϊ 0 ����Ӳ����֧���������ⷽ����
 *      2.������������FreeRTOS֧�ֵ�Ӳ��
 *      3.��ȫ��Cʵ�֣�Ч���Ե������ⷽ����
 *      4.��ǿ��Ҫ���������������ȼ���Ŀ
 * ���ⷽ����
 *      1.���뽫configUSE_PORT_OPTIMISED_TASK_SELECTION����Ϊ1��
 *      2.����һ�������ض��ܹ��Ļ��ָ�һ�������Ƽ���ǰ����[CLZ]ָ���
 *      3.��ͨ�÷�������Ч
 *      4.һ��ǿ���޶����������ȼ���ĿΪ32
 * һ����Ӳ������ǰ����ָ������ʹ�õģ�MCUû����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ0��
 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	        1                       
                                                                        
/* ��1��ʹ�ܵ͹���ticklessģʽ����0������ϵͳ���ģ�tick���ж�һֱ����
 * ���迪���͹��ĵĻ����ܻᵼ�����س������⣬��Ϊ������˯����,�������°취���
 * 
 * ���ط�����
 *      1.���������������Ӻ�
 *      2.��ס��λ�������������˲���ɿ���λ����
 *     
 *      1.ͨ������ñ�� BOOT 0 �Ӹߵ�ƽ(3.3V)
 *      2.�����ϵ磬����
 *    
 * 			1.ʹ��FlyMcu����һ��оƬ��Ȼ���������
 *			STMISP -> ���оƬ(z)
 */
#define configUSE_TICKLESS_IDLE													0   

/*
 * д��ʵ�ʵ�CPU�ں�ʱ��Ƶ�ʣ�Ҳ����CPUָ��ִ��Ƶ�ʣ�ͨ����ΪFclk
 * FclkΪ����CPU�ں˵�ʱ���źţ�������˵��cpu��ƵΪ XX MHz��
 * ����ָ�����ʱ���źţ���Ӧ�ģ�1/Fclk��Ϊcpuʱ�����ڣ�
 */
#define configCPU_CLOCK_HZ						  (SystemCoreClock)

//RTOSϵͳ�����жϵ�Ƶ�ʡ���һ���жϵĴ�����ÿ���ж�RTOS��������������
#define configTICK_RATE_HZ						  (( TickType_t )1000)

//��ʹ�õ�������ȼ�
#define configMAX_PRIORITIES					  (32)

//��������ʹ�õĶ�ջ��С
#define configMINIMAL_STACK_SIZE				((unsigned short)128)
  
//���������ַ�������
#define configMAX_TASK_NAME_LEN					(16)

 //ϵͳ���ļ����������������ͣ�1��ʾΪ16λ�޷������Σ�0��ʾΪ32λ�޷�������
#define configUSE_16_BIT_TICKS					0                      

//�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
#define configIDLE_SHOULD_YIELD					1           

//���ö���
#define configUSE_QUEUE_SETS					  1   

//��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_TASK_NOTIFICATIONS    1   

//ʹ�û����ź���
#define configUSE_MUTEXES						    0    

//ʹ�õݹ黥���ź���                                            
#define configUSE_RECURSIVE_MUTEXES			0   

//Ϊ1ʱʹ�ü����ź���
#define configUSE_COUNTING_SEMAPHORES		1

/* ���ÿ���ע����ź�������Ϣ���и��� */
#define configQUEUE_REGISTRY_SIZE				10                                 
                                                                       
#define configUSE_APPLICATION_TASK_TAG		  0                       
                      

/*****************************************************************
              FreeRTOS���ڴ������й�����ѡ��                                               
*****************************************************************/
//֧�ֶ�̬�ڴ�����
#define configSUPPORT_DYNAMIC_ALLOCATION        1    
//֧�־�̬�ڴ�
#define configSUPPORT_STATIC_ALLOCATION					0					
//ϵͳ�����ܵĶѴ�С
#define configTOTAL_HEAP_SIZE					((size_t)(36*1024))    


/***************************************************************
             FreeRTOS�빳�Ӻ����йص�����ѡ��                                            
**************************************************************/
/* ��1��ʹ�ÿ��й��ӣ�Idle Hook�����ڻص�����������0�����Կ��й���
 * 
 * ������������һ������������������û���ʵ�֣�
 * FreeRTOS�涨�˺��������ֺͲ�����void vApplicationIdleHook(void )��
 * ���������ÿ�������������ڶ��ᱻ����
 * �����Ѿ�ɾ����RTOS���񣬿�����������ͷŷ�������ǵĶ�ջ�ڴ档
 * ��˱��뱣֤����������Ա�CPUִ��
 * ʹ�ÿ��й��Ӻ�������CPU����ʡ��ģʽ�Ǻܳ�����
 * �����Ե��û������������������API����
 */
#define configUSE_IDLE_HOOK						0      

/* ��1��ʹ��ʱ��Ƭ���ӣ�Tick Hook������0������ʱ��Ƭ����
 * 
 * 
 * ʱ��Ƭ������һ������������������û���ʵ�֣�
 * FreeRTOS�涨�˺��������ֺͲ�����void vApplicationTickHook(void )
 * ʱ��Ƭ�жϿ��������Եĵ���
 * ��������ǳ���С�����ܴ���ʹ�ö�ջ��
 * ���ܵ����ԡ�FromISR" �� "FROM_ISR����β��API����
 */
 /*xTaskIncrementTick��������xPortSysTickHandler�жϺ����б����õġ���ˣ�vApplicationTickHook()����ִ�е�ʱ�����̲ܶ���*/
#define configUSE_TICK_HOOK						0           

//ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_MALLOC_FAILED_HOOK			0 

/*
 * ����0ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹��� 
 * �û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
 * ��ֵ����Ϊ1����2����Ϊ������ջ�����ⷽ�� */
#define configCHECK_FOR_STACK_OVERFLOW			0   


/********************************************************************
          FreeRTOS������ʱ�������״̬�ռ��йص�����ѡ��   
**********************************************************************/
//��������ʱ��ͳ�ƹ���
#define configGENERATE_RUN_TIME_STATS	        0             
 //���ÿ��ӻ����ٵ���
#define configUSE_TRACE_FACILITY				      0    
/* ���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������
 * prvWriteNameToBuffer()
 * vTaskList(),
 * vTaskGetRunTimeStats()
*/
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       
                                                                        
                                                                        
/********************************************************************
                FreeRTOS��Э���йص�����ѡ��                                                
*********************************************************************/
//����Э�̣�����Э���Ժ��������ļ�croutine.c
#define configUSE_CO_ROUTINES 			          0                 
//Э�̵���Ч���ȼ���Ŀ
#define configMAX_CO_ROUTINE_PRIORITIES       ( 2 )                   


/***********************************************************************
                FreeRTOS�������ʱ���йص�����ѡ��      
**********************************************************************/
 //���������ʱ��
#define configUSE_TIMERS				            0                              
//�����ʱ�����ȼ�
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        
//�����ʱ�����г���
#define configTIMER_QUEUE_LENGTH		        10                               
//�����ʱ�������ջ��С
#define configTIMER_TASK_STACK_DEPTH	      (configMINIMAL_STACK_SIZE*2)    

/************************************************************
            FreeRTOS��ѡ��������ѡ��                                                     
************************************************************/
#define INCLUDE_xTaskGetSchedulerState       1                       
#define INCLUDE_vTaskPrioritySet		         1
#define INCLUDE_uxTaskPriorityGet		         1
#define INCLUDE_vTaskDelete				           1
#define INCLUDE_vTaskCleanUpResources	       1
#define INCLUDE_vTaskSuspend			           1
#define INCLUDE_vTaskDelayUntil			         1
#define INCLUDE_vTaskDelay				           1
#define INCLUDE_eTaskGetState			           1
#define INCLUDE_xTimerPendFunctionCall	     0
//#define INCLUDE_xTaskGetCurrentTaskHandle       1
//#define INCLUDE_uxTaskGetStackHighWaterMark     0
//#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_xTaskIsTaskFinished                 ( 1 )


/******************************************************************
           FreeRTOS���ж��йص�����ѡ��                                                 
******************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif
//�ж�������ȼ�
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15     

//ϵͳ�ɹ��������ж����ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	/* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )




/****************************************************************
            FreeRTOS���жϷ������йص�����ѡ��                         
****************************************************************/
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler


/* ����Ϊʹ��Percepio Tracealyzer��Ҫ�Ķ���������Ҫʱ�� configUSE_TRACE_FACILITY ����Ϊ 0 */
#if ( configUSE_TRACE_FACILITY == 1 )
#include "trcRecorder.h"
#define INCLUDE_xTaskGetCurrentTaskHandle               1   // ����һ����ѡ�������ú����� TraceԴ��ʹ�ã�Ĭ�ϸ�ֵΪ0 ��ʾ���ã�
#endif


#endif /* FREERTOS_CONFIG_H */

