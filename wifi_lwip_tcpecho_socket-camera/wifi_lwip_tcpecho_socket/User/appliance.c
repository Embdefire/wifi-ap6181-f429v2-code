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
 * @brief app_main
 *
 */
void app_main( void )
{
		SAMPLE_PRT("�����Ѿ���ʼִ��");
		/*����wifi lwip��Ϣ*/
		Config_WIFI_LwIP_Info();

		tcpecho_init();
}
