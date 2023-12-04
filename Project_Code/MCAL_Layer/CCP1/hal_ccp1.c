/* 
 * File:   hal_ccp1.c
 * Author: Aya Ali
 *
 * Created on December 2, 2023, 9:18 PM
 */

#include "hal_ccp1.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*CCPI_Interrupt_Hundeler)(void);
#endif


#ifdef CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED 
Std_ReturnType CCP1_CAPTURE_Init(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
     CCP1_SET_MODE(CCP1_MODULE_DISABLE);
    if(ccp1_obj->ccp1_mode == CCP1_CAPTURE_MODE_SELECTED){
      switch(ccp1_obj->ccp1_mode_variant){
           case CCP1_CAPTURE_MODE_1_FALLING_EDGE: 
           CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_FALLING_EDGE);
           break;
           case CCP1_CAPTURE_MODE_1_RISING_EDGE: 
           CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_RISING_EDGE);
           break;
           case CCP1_CAPTURE_MODE_4_RISING_EDGE: 
           CCP1_SET_MODE(CCP1_CAPTURE_MODE_4_RISING_EDGE);
           break;
           case CCP1_CAPTURE_MODE_16_RISING_EDGE: 
           CCP1_SET_MODE(CCP1_CAPTURE_MODE_16_RISING_EDGE);
           break;
          default: ret = E_NOT_OK;
      }  
      ret = gpio_pin_intialize(&(ccp1_obj->ccp1_pin));
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCPI_Interrupt_Hundeler = ccp1_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp1_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp1_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif      
  
    }
}
    return ret;
}

Std_ReturnType CCP1_CAPTURE_Deinit(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
CCP1_SET_MODE(CCP1_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP1_INTERRUPT_DISABLE();
#endif 

}
return ret;
}

Std_ReturnType CCP1_IsCapturedData_Ready(uint_8 *captured_status){
Std_ReturnType ret = E_OK;
if(captured_status == NULL){
ret = E_NOT_OK;
}
else{
    if(PIR1bits.CCP1IF == CCP1_CAPTURE_READY){
    *captured_status = CCP1_CAPTURE_READY;
    CCP1_CLEAR_FLAG();
    }
    else{
     *captured_status = CCP1_CAPTURE_NOT_READY;
    }

}
return ret;
}
Std_ReturnType CCP1_Captured_Mode_Read_Value(uint_16 *captured_value){
Std_ReturnType ret = E_OK;
CCP1_PERIOD_REG_T capure_temp_value = {.ccp1_low = 0,.ccp1_high = 0 };
if(captured_value == NULL){
ret = E_NOT_OK;
}
else{
capure_temp_value.ccp1_low = CCPR1L;
capure_temp_value.ccp1_high = CCPR1H;
*captured_value = capure_temp_value.ccp1_16bit;
}
 return ret;
}
#endif 


#ifdef CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED 
Std_ReturnType CCP1_COMPARE_Init(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
      CCP1_SET_MODE(CCP1_MODULE_DISABLE);
     if(ccp1_obj->ccp1_mode == CCP1_COMPARE_MODE_SELECTED)
    {
        switch(ccp1_obj->ccp1_mode_variant){
           case CCP1_COMPARE_MODE_SET_PIN_LOW: 
           CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW);
           break;
           case CCP1_COMPARE_MODE_SET_PIN_HIGH: 
           CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH);
           break;
           case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH: 
           CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH);
           break;
           case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT: 
           CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT);
           break;
           case CCP1_COMPARE_MODE_GEN_EVENT: 
           CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_EVENT);
           break;
           default: ret = E_NOT_OK;
      } 
         ret = gpio_pin_intialize(&(ccp1_obj->ccp1_pin)); 
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCPI_Interrupt_Hundeler = ccp1_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp1_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp1_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif 
     }
}
return ret;
}

Std_ReturnType CCP1_COMPARE_Deinit(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
CCP1_SET_MODE(CCP1_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP1_INTERRUPT_DISABLE();
#endif 
}
return ret;
}

Std_ReturnType CCP1_IsCompare_Completed(uint_8 *compare_status){
Std_ReturnType ret = E_OK;
if(compare_status == NULL){
ret = E_NOT_OK;
}
else{
    if(PIR1bits.CCP1IF == CCP1_COMPARE_READY){
    *compare_status = CCP1_COMPARE_READY;
    CCP1_CLEAR_FLAG();
    }
    else{
        *compare_status = CCP1_COMPARE_NOT_READY;
    }


}
return ret;
}

Std_ReturnType CCP1_Compare_Mode_Set_Value(uint_16 compare_value){
Std_ReturnType ret = E_NOT_OK;
CCP1_PERIOD_REG_T compare_temp_value = {.ccp1_low = 0,.ccp1_high = 0 };
compare_temp_value.ccp1_16bit = compare_value;
CCPR1L = compare_temp_value.ccp1_low;
CCPR1H = compare_temp_value.ccp1_high;
ret = E_OK;
return ret;
}
#endif


//#ifdef CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED 

Std_ReturnType CCP1_PWM_Init(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
    CCP1_SET_MODE(CCP1_PWM_MODE);
#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)            
if(ccp1_obj->ccp1_mode == CCP1_PWM_MODE_SELECTED){
         if(ccp1_obj->ccp1_mode_variant == CCP1_PWM_MODE){
         CCP1_SET_MODE(CCP1_PWM_MODE);
 PR2 = (uint_8)((_XTAL_FREQ/(ccp1_obj->PWM_Freq * 4.0 * ccp1_obj->timer2_prescaler_value * ccp1_obj->timer2_postscaler_value))-1);
         }
         else{}
         ret = gpio_pin_intialize(&(ccp1_obj->ccp1_pin));
        
}
     else{} 
#endif      

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCPI_Interrupt_Hundeler = ccp1_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp1_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp1_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif 
    CCP1_SET_MODE(CCP1_MODULE_DISABLE);
}
return ret;
}

Std_ReturnType CCP1_PWM_Deinit(const ccp1_t *ccp1_obj){
Std_ReturnType ret = E_OK;
if(ccp1_obj == NULL){
ret = E_NOT_OK;
}
else{
    CCP1_SET_MODE(CCP1_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP1_INTERRUPT_DISABLE();
#endif 
}
return ret;
}

Std_ReturnType CCP1_PWM1_Set_Duty(const uint_8 duty){
Std_ReturnType ret = E_NOT_OK;
uint_16 l_duty_temp = 0;
l_duty_temp = (uint_16)(((PR2 + 1) *(duty / 100.0)) * 4);
CCP1CONbits.DC1B = (uint_8)(l_duty_temp & 0x0003);
CCPR1L = (uint_8)(l_duty_temp >> 2);
ret = E_OK;
 return ret;
}

Std_ReturnType CCP1_PWM1_Start(void){
Std_ReturnType ret = E_NOT_OK;
CCP1CONbits.CCP1M = CCP1_PWM_MODE;
ret = E_OK;
return ret;

}

Std_ReturnType CCP1_PWM1_Stop(void){
Std_ReturnType ret = E_NOT_OK;
CCP1CONbits.CCP1M = CCP1_MODULE_DISABLE;
ret = E_OK;
 return ret;

}

//#endif