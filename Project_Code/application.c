/* 
 * File:   application.c
 * Author: AyaAli
 * Created on September 22, 2023, 10:24 AM
 */
#include "application.h"

timer2_config_t timer2;
ccp1_t ccp1_obj;

int main() {
   
Std_ReturnType ret = E_NOT_OK;

ccp1_obj.CCP1_Interrupt_Hundeler = NULL;
ccp1_obj.ccp1_mode = CCP1_PWM_MODE_SELECTED;
ccp1_obj.PWM_Freq = 20000;
ccp1_obj.ccp1_pin.port = PORTC_INDEX;
ccp1_obj.ccp1_pin.pin = PIN2;
ccp1_obj.ccp1_pin.direction = Output;
ccp1_obj.timer2_prescaler_value = TIMER2_POSTSCALLER_DIV_BY_1;
ccp1_obj.timer2_postscaler_value= TIMER2_PRESCALLER_DIV_BY_1;
ret = CCP1_PWM_Init(&ccp1_obj);

timer2.TMR2_Interrupt_Hundeler = NULL;
timer2.timer2_prescaller_value = TIMER2_POSTSCALLER_DIV_BY_1;
timer2.timer2_post_scaller_value = TIMER2_PRESCALLER_DIV_BY_1;
timer2.timer2_preloaded_value = 0;

ret = Timer2_Init(&timer2);



while(1){
ret = CCP1_PWM1_Set_Duty(25);
ret = CCP1_PWM1_Start();
__delay_ms(2000);
ret = CCP1_PWM1_Set_Duty(50);
ret = CCP1_PWM1_Start();
__delay_ms(2000);
ret = CCP1_PWM1_Set_Duty(75);
ret = CCP1_PWM1_Start();
}
 return (EXIT_SUCCESS);
}
void application_initialize(void){
   Std_ReturnType ret = E_NOT_OK;

}
