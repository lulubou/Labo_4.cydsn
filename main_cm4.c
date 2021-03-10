/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "params.h"
#include "queue.h"

void inv_LED(){
    for(;;){
        Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    xTaskCreate(inv_LED, "blink_LED", 300, NULL, 1, NULL);
    vTaskStartScheduler();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
