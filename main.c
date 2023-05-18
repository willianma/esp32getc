#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "string.h" 
/*
read_input emulates the buzy wait of scanf 
ch==-1 when nothing typed 
isprint ensures the character is printable (requires to include <ctype.h>)
now upgraded to update terminal to erase when pressed backspace key

input = read_input("Type n of steps and time of each pulse: ");
printf("%s\n", input);
can read a float by: 
float tfloat = (float)strtof(input,NULL);
printf("float incr res: %4.4f\n",tfloat);
can read two ints by
int value1 = strtol(input, &input, 10);
int value2 = strtol(input, &input, 10);
so when typed "32 48" it will store 32 into value1 and 48 into value2
*/
char* read_input(const char* prompt) {
    static char input[20];
    printf("%s", prompt);
    fflush(stdout);
    fflush(stdout);
    int pos=0;

    while(1){
        int ch=getchar();
        //printf("[%d]",ch);
        if(ch=='\n'){
            input[pos]='\0';
            break;
        }else if(ch=='\b' && pos>0){
            pos--;
            printf("\b \b");  // Erase previous character
            fflush(stdout);
        }else if (ch!=-1){//(isprint(ch) && ch!=-1){ 
            input[pos]=ch;
            putchar(ch);//printf("%c",input[pos]);
            fflush(stdout);
            pos++;
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    printf("\n\n");  // Erase previous character
    fflush(stdout);
    return input;
}
void app_main(void){
    char* input;
    while(1){
        input = read_input("Type n of steps and time of each pulse: ");
        printf("%s\n", input);
        //tfloat = tfloat + (float)strtof(input,NULL);
        //printf("float incr res: %4.4f\n",tfloat);
        int value1 = strtol(input, &input, 10);
        int value2 = strtol(input, &input, 10);
        printf("int read value1: %d | int read value2: %d\n",value1,value2);
    }
}
