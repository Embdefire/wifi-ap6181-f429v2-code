#include "wifi_base_config.h"
#include "appliance.h"
#include "stm32f4xx.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "client.h"

/**
 * @brief app_main
 *
 */
void app_main( void )
{
		/*����wifi lwip��Ϣ*/
		Config_WIFI_LwIP_Info();
		client_init();
    while (1)
    {
    }

}


