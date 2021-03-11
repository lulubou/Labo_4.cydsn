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

SemaphoreHandle_t semaphore;
volatile uint16_t nbAppuis = 0;

void bouton_task(){
    for(;;){
        if(xSemaphoreTake(semaphore, 1) == true){
            if (nbAppuis%2 != 0){
                UART_PutString("Bouton appuye ");
                //vTaskDelay(pdMS_TO_TICKS(40));
            }
            else{
                UART_PutString("Bouton relache ");
                //vTaskDelay(pdMS_TO_TICKS(40));
            }
        }
        //if (dernier == 1){
        //    UART_PutString("Bouton relache ");
        //}
    }
}
    

void isr_bouton(void){
    nbAppuis += 1;
    CyDelay(20);
    xSemaphoreGiveFromISR(semaphore, NULL);
    Cy_GPIO_ClearInterrupt(bouton_0_PORT, bouton_0_NUM);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);
}

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
    semaphore = xSemaphoreCreateBinary();
    UART_Start();
    Cy_SysInt_Init(&bouton_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(bouton_isr_cfg.intrSrc);
    NVIC_EnableIRQ(bouton_isr_cfg.intrSrc);
    
    xTaskCreate(bouton_task, "Ecriture", 1000, NULL, 2, NULL);
    vTaskStartScheduler();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
