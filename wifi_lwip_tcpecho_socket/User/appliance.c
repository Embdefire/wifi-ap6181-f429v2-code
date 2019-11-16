#include "wifi_base_config.h"
#include "appliance.h"
#include "stm32f4xx.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "tcpecho.h"

#define PRINTF printf

/**
 * @brief ����ʵ��˵��
 *
 */
void ExperimentalDescription()
{
	PRINTF("��������ʾ���Կͻ��˷������ݵ���������������\n\n");
	
	PRINTF("������Ϊ������������Ϊ�ͻ���\n\n");

	PRINTF("�ȴ򿪷�����ٴ򿪿ͻ��ˣ�Network ready IP: ��Ӧ�ľ���IP��ַ\n\n");	
}
/**
 * @brief app_main
 *
 */
void app_main( void )
{
	
		/*����wifi lwip��Ϣ*/
		Config_WIFI_LwIP_Info();
	
		ExperimentalDescription();
		tcpecho_init();
}
