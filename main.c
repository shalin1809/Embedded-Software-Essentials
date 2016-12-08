/***************************************************


LEDs are Active Low in configuration. Thus setting the pin high will turn them off

*****************************************************/


#include "MKL25Z4.h"                    // Device header
#include "LED.h"
#include "uart.h"
#include "pwm.h"
#include "Circular_buffer.h"
#include "log.h"
#include "myrtc.h"
#include "Buzzer.h"
#include "adc.h"
#include "GPIO.h"
//#include "lcd_frdm.h"
#include "eeprom.h"
#include "profiler.h"
#include <stdint.h>


float time_spent = 0.0;
uint16_t temp = 0;

struct CircBuf rx_buff;
CircBuf_t *rx_buffer = &rx_buff;

struct CircBuf tx_buff;
CircBuf_t *tx_buffer = &tx_buff;


uint32_t a, b=0, alarm = 0;
int year;
uint16_t adc_value;
float adc_temp;
uint8_t PIR_state;
int i2c_data = 0;

char array[100] = {'\0'};               //Global array to read string UART0

int main () {
    int  i=0;
    initialize_Buffer(rx_buffer, 0);
    initialize_Buffer(tx_buffer, 1);
    __disable_irq();
    UART0_init();
    PWM_init();
    LED_init();
    rtc_init();
    Buzzer_init();
    ADC0_init();
    PIR_init();
    __enable_irq();    
    UART0_WriteString("Hello");
    ADC0_calibrate();
    i2c_init();
    Buzzer_ON();
    //i2c_writeByte(0x50,0x30,0x20);
    //i2c_data = i2c_readByte(0x50,0x30);
    //set_unix_time(0x58486A8D);
    //set_alarm(get_unix_time() + 10);
    while (1) {
        Control(remove_item(rx_buffer));
        a = get_unix_time();
        if(alarm == 1)
            Buzzer_ON();
        if(a>b){                                    //Print time if 1 second incremented
            b=a;
            UART0_WriteChar(get_rtc_hours()/10+48);
            UART0_WriteChar(get_rtc_hours()%10+48);
            UART0_WriteChar(':');
            UART0_WriteChar(get_rtc_minutes()/10+48);
            UART0_WriteChar(get_rtc_minutes()%10+48);
            UART0_WriteChar(':');
            UART0_WriteChar(get_rtc_seconds()/10+48);
            UART0_WriteChar(get_rtc_seconds()%10+48);
            
            UART0_WriteChar('\t');
            UART0_WriteChar((get_rtc_year()/10-152));
            UART0_WriteChar(get_rtc_year()%10+48);
            UART0_WriteChar('-');
            UART0_WriteChar(get_rtc_month()/10+48);
            UART0_WriteChar(get_rtc_month()%10+48);
            UART0_WriteChar('-');
            UART0_WriteChar(get_rtc_day()/10+48);
            UART0_WriteChar(get_rtc_day()%10+48);
            UART0_WriteChar('\n');
            UART0_WriteChar('\r');
        }
        PIR_state = PIR_read();
        if(PIR_state == 0 ){
            Buzzer_OFF();
            alarm = 2;
        }
        adc_value = ADC0_GetValue(14);
        LED_SET_BRIGHTNESS((adc_value - 0x55A0)/0x9B6);
        adc_temp = ADC0_GetValue(6);
        adc_temp *= 33;
        adc_temp/= 65535;                                
        //LOG_2("\n\rTemperature (in Celsius) is :",30,adc_temp,10);
        for( i = 0; i<1000000; i++);
    }
}

void Control(char a){
    if(a == 'i'){
        UART0_WriteString("\n\rUser Echo mode");
        UART0_ReadString(array);
        UART0_WriteString("\n\rThe string entered is:");
        UART0_WriteString(array);
    }
    else if (a == 'm'){
        UART0_WriteString("\n\rMessaging mode");
       // decode_message();
    }
    else if(a == 'p'){
        set_alarm(get_unix_time() +10);
    }
    else if(a == 'o'){
        Buzzer_OFF();
    }
    else 
        LED_Control(a);
}

void RTC_IRQHandler(void){
    
    if(alarm == 0 ){
        alarm ++;
        return;
    }
    alarm = 1;
    UART0_WriteString("Alarm Interrupt");
    UART0_WriteChar('\n');
    UART0_WriteChar('\r');
    RTC_TAR = 0xFF;
    
}

void RTC_Seconds_IRQHandler(void){
    
}
