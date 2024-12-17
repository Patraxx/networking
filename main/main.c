#include <stdio.h>
#include "prints.h"

#define TASK_1_BIT (1 << 0)
#define TASK_2_BIT (1 << 1)

QueueHandle_t queue_task1_task2; // Task 1 -> Task 2
QueueHandle_t queue2; 


typedef struct function_data_t
{
    SemaphoreHandle_t semaphore;
    SemaphoreHandle_t countingSemaphore;
    SemaphoreHandle_t mutex;
    EventGroupHandle_t event_group;
    QueueHandle_t queue;
    MessageBufferHandle_t messageBuffer;
    StreamBufferHandle_t streamBuffer;
    char sharedString[10];
} function_data_t;

  
TaskHandle_t task_handle_1;
TaskHandle_t task_handle_2;
TaskHandle_t task_handle_3;
TaskHandle_t task_handle_4;
TaskHandle_t task_handle_5;


//  PRINTFC_TASK_2("Nu väntar vi på semaphore \n");


// void function_2(void* pvParameters){
    
//     function_data_t *param = (function_data_t*) pvParameters;
//     PRINTFC_TASK_2("Nu väntar vi på semaphore \n");

//     vTaskDelay(pdMS_TO_TICKS(100));
//     BaseType_t result = xSemaphoreTake(param->countingSemaphore, portMAX_DELAY);

//     if(result == pdTRUE){
//         PRINTFC_TASK_2("jag har counting semaphore \n");
//     }
//     vTaskDelay(pdMS_TO_TICKS(1000)); //kolla vad skillnadfen är på det jag använt tidigare
//     PRINTFC_TASK_2("Nu släpper jag countern\n");
//     xSemaphoreGive(param->countingSemaphore);

//     vTaskDelete(NULL);
// }
 

void task_1(void* pvParameters){

   bool task_boolean = false;
   int task_counter = 0;
   for(;;){

        task_counter++;
        vTaskDelay(pdMS_TO_TICKS(333));
        if(task_counter % 5 == 0){
            task_boolean = !task_boolean;
            xTaskNotifyGive(task_handle_2);
        }
        if(task_boolean){
            PRINTFC_TASK_1("Task 1: %d\n", task_counter);


        }
   } 
    vTaskDelete(NULL);
}

void task_2(void* pvParameters){

   bool task_boolean = false;
   int task_counter = 0;

   
    vTaskDelete(NULL);
}
void task_3(void* pvParameters){

   bool task_boolean = false;
   int task_counter = 0;

   
    vTaskDelete(NULL);
}
void task_4(void* pvParameters){

   bool task_boolean = false;
   int task_counter = 0;

   
    vTaskDelete(NULL);
}
void task_5(void* pvParameters){

   bool task_boolean = false;
   int task_counter = 0;

   
    vTaskDelete(NULL);
}

void app_main(void)
{   


    function_data_t functionData;
    functionData.semaphore = xSemaphoreCreateBinary();
    functionData.countingSemaphore = xSemaphoreCreateCounting(2, 2);
    functionData.event_group = xEventGroupCreate();
    functionData.queue = xQueueCreate(1, sizeof(int));
   
   
  


    xTaskCreate(task_1, "Task 1", 2048, &functionData, 1, &task_handle_1); //fråga om task handle
  // xTaskCreate(function_2, "Task 2", 2048, &functionData, 1, &task_handle_2); //fråga om task handle
   // xTaskCreate(function_2, "Task 3", 2048, &data_3, 3, &task_handle_3); //fråga om task handle

    

}



/*
Kör följande 5 tasks
Varje task ska ha en lokal räknar variabel som inte går att nå utanför tasken. Värdet ska börja på 0
Varje task ska ha en lokal booleansk variabel som inte går att nå utanför tasken. Värdet ska börja på
false.

Task_1
Räkna +1 tre gånger per sekund med jämna mellanrum
Var 5e increment ska boolean inverteras från false till true eller true till false.

Task_2
När task 1 har blivit 5 ska denna task räkna +1 på sin räknare
När task 2 tar emot new line (\n) ska den ta strängen den fått från task 5 och räkna ut hur många
vokaler texten innehåller och multiplicera det med antalet jämna siffror och dela det med antalet
udda siffor i strängen. Om resultatet av den beräkningen är udda ska boolean sättas till sant annars
falskt

Task_3
När task 1 & task 2 har en räknare som går att dela jämt dela med 10 ska task 3s räknare plussa på 1.
Obs endast +1 per kombination av tal från task 1 & 2. Alltså värdet task_1: 50 & task_2: 10 ska endast
resultera i task_3 = 1 nästa kommer vid 100 & 20.
Varje gång task 2 har tagigt emot ett medelande ska task 3 få del av längden på det medelandet och
om task 2 har satt sin boolean till true på grund av medelandet ska task 3 sätta sin boolean till true
om längden är udda. Om task 2 har satt sin boolean till false ska task 3 sätta sin boolean till false om
längden är udda.

Task_4
Task 4 ska räkna +1 på sin räknare 5 gånger per sekund så länge task 1 &2 & 3 har sin boolean satt till
true
Task 4 ska få en kopia av den sträng som task 2 tog emot 2 sekunder efter att task 2 är färdig
med den.
Task 4 ska då byta ut alla bokstäver från lower till upper och från upper till lower case.


Task_5

Task 5 ska skicka användar genererade text strängar till task 2. Du kan använda TCP, UDP,
Seriel kommunikation över usb-uart. Upp till dig.
Task 5 ska ta emot strängen som task 4 har modifierat och skicka tillbaka den till avsändar*/