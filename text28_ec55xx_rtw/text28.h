/*
 * Code generated for Simulink model text28.
 *
 * FILE    : text28.h
 *
 * VERSION : 1.173
 *
 * DATE    : Sat Oct 05 10:25:27 2024
 *
 * Copyright 2011-2012 ECUCoder. All Rights Reserved.
 */

#ifndef RTW_HEADER_text28_h_
#define RTW_HEADER_text28_h_
#include <math.h>
#include "etpu_util.h"
#include "etpu_ic.h"
#include "etpu_pwm.h"
#include "etpu_gpio.h"
#include "etpu_ppa.h"
#include "MPC5554.h"
#include "Std_Types.h"
#include "interrupts.h"
#include "siu.h"
#include "flash_app.h"
#ifndef text28_COMMON_INCLUDES_
# define text28_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* text28_COMMON_INCLUDES_ */

#include "text28_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#define EnableInterrupts()             asm(" wrteei 1")
#define DisableInterrupts()            asm(" wrteei 0")

/* Block signals (auto storage) */
typedef struct {
  uint32_T CANReceive_o3;              /* '<S75>/CANReceive' */
  uint32_T CANReceive1_o3;             /* '<S61>/CANReceive1' */
  uint32_T MCUSTATUS2_o3;              /* '<S4>/MCU STATUS 2' */
  uint32_T DataTypeConversion1;        /* '<S4>/Data Type Conversion1' */
  uint32_T CAN_o3;                     /* '<S3>/CAN检测' */
  uint32_T DataTypeConversion1_j;      /* '<S143>/Data Type Conversion1' */
  uint32_T u;                          /* '<S146>/左前' */
  uint32_T u_ji;                       /* '<S146>/右前' */
  uint32_T CANReceive_o3_c;            /* '<S102>/CANReceive' */
  uint32_T DataTypeConversion;         /* '<S98>/Data Type Conversion' */
  uint8_T CANReceive_o2;               /* '<S75>/CANReceive' */
  uint8_T CANReceive_o4[8];            /* '<S75>/CANReceive' */
  uint8_T CANReceive_o5;               /* '<S75>/CANReceive' */
  uint8_T CANReceive1_o2;              /* '<S61>/CANReceive1' */
  uint8_T CANReceive1_o4[8];           /* '<S61>/CANReceive1' */
  uint8_T CANReceive1_o5;              /* '<S61>/CANReceive1' */
  uint8_T CANTransmit;                 /* '<S67>/CANTransmit' */
  uint8_T MCUSTATUS2_o2;               /* '<S4>/MCU STATUS 2' */
  uint8_T MCUSTATUS2_o4[8];            /* '<S4>/MCU STATUS 2' */
  uint8_T MCUSTATUS2_o5;               /* '<S4>/MCU STATUS 2' */
  uint8_T In1[8];                      /* '<S44>/In1' */
  uint8_T or1;                         /* '<S10>/or1' */
  uint8_T or2;                         /* '<S10>/or2' */
  uint8_T or3;                         /* '<S10>/or3' */
  uint8_T or4;                         /* '<S10>/or4' */
  uint8_T or5;                         /* '<S10>/or5' */
  uint8_T or6;                         /* '<S10>/or6' */
  uint8_T or7;                         /* '<S10>/or7' */
  uint8_T or8;                         /* '<S10>/or8' */
  uint8_T CANTransmit_p;               /* '<S2>/CANTransmit' */
  uint8_T CAN_o4[8];                   /* '<S3>/CAN检测' */
  uint8_T CAN_o5;                      /* '<S3>/CAN检测' */
  uint8_T In3[8];                      /* '<S16>/In3' */
  uint8_T or1_n;                       /* '<S7>/or1' */
  uint8_T or2_b;                       /* '<S7>/or2' */
  uint8_T or3_h;                       /* '<S7>/or3' */
  uint8_T or4_k;                       /* '<S7>/or4' */
  uint8_T or5_m;                       /* '<S7>/or5' */
  uint8_T or6_n;                       /* '<S7>/or6' */
  uint8_T or7_l;                       /* '<S7>/or7' */
  uint8_T or8_b;                       /* '<S7>/or8' */
  uint8_T CANTransmit_pg;              /* '<S1>/CANTransmit' */
  uint8_T or1_a;                       /* '<S82>/or1' */
  uint8_T or2_f;                       /* '<S82>/or2' */
  uint8_T or3_k;                       /* '<S82>/or3' */
  uint8_T or4_m;                       /* '<S82>/or4' */
  uint8_T or5_c;                       /* '<S82>/or5' */
  uint8_T or6_p;                       /* '<S82>/or6' */
  uint8_T or7_a;                       /* '<S82>/or7' */
  uint8_T or8_l;                       /* '<S82>/or8' */
  uint8_T CANReceive_o2_b;             /* '<S102>/CANReceive' */
  uint8_T CANReceive_o4_m[8];          /* '<S102>/CANReceive' */
  uint8_T CANReceive_o5_i;             /* '<S102>/CANReceive' */
  uint8_T In2[8];                      /* '<S152>/In2' */
} B_text28_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S99>/Unit Delay' */
  real_T UnitDelay_DSTATE_l;           /* '<S97>/Unit Delay' */
  real_T UnitDelay_DSTATE_o;           /* '<S143>/Unit Delay' */
  real_T Motor_toque_st_DWORK1;        /* '<S8>/Motor_toque_st' */
  uint32_T UnitDelay_DSTATE_j;         /* '<S22>/Unit Delay' */
} DW_text28_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint32_T DataTypeConversion2;  /* '<S4>/Data Type Conversion2' */
  const uint32_T DataTypeConversion5;  /* '<S22>/Data Type Conversion5' */
  const uint32_T DataTypeConversion;   /* '<S143>/Data Type Conversion' */
  const boolean_T DataTypeConversion_a;/* '<S6>/Data Type Conversion' */
} ConstB_text28_T;

/* Real-time Model Data Structure */
struct tag_RTM_text28_T {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[8];
    } TaskCounters;
  } Timing;
};

/* Block signals (auto storage) */
extern B_text28_T text28_B;

/* Block states (auto storage) */
extern DW_text28_T text28_DW;
extern const ConstB_text28_T text28_ConstB;/* constant block i/o */

/* External function called from main */
extern void text28_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void text28_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void text28_initialize(void);
extern void text28_step(int_T tid);
extern uint8_T ECUCoderModelBaseCounter;
extern uint8_T AfterRunFlags[2];

/* Exported data declaration */

/* Declaration for custom storage class: Default */
extern uint8_T CAN_ok;
extern boolean_T FAN_sign;
extern real32_T McuTemp;
extern real32_T MotorTemp;
extern uint32_T anquan_out;
extern real_T app_add2;
extern real_T app_baifenbi;
extern real_T app_date1;
extern real_T app_date2;
extern real_T app_konghou;
extern real_T app_scs;
extern real_T apple;
extern real_T apps_erro;
extern real_T apps_rule;
extern boolean_T aqhl;
extern real_T baifenbi1;
extern real_T baifenbi2;
extern real_T baifenbi3;
extern real32_T baojing;
extern uint8_T bms_canok;
extern boolean_T bms_sign;
extern real_T bms_sign1;
extern real_T car_speed;
extern real_T daishi;
extern uint8_T daishi_11;
extern real_T daishi_chu;
extern real_T daishi_fanhui;
extern boolean_T daishi_out;
extern real32_T dianya;
extern real_T enable_sign;
extern real_T huazhuan;
extern real_T jiaodu1;
extern real_T jiaodu2;
extern uint16_T jiaodu_11111;
extern uint16_T jiaodu_2222;
extern uint32_T keshi;
extern real_T left_speed;
extern real_T motor_speed;
extern real_T motor_torque;
extern real_T rear_speed;
extern real_T right_speed;
extern real32_T soc;
extern uint16_T youya1;
extern real_T youya2;
extern real_T youya3;
extern real32_T zhuangtai;
extern real_T zuizhong;

/* Real-time Model object */
extern RT_MODEL_text28_T *const text28_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'text28'
 * '<S1>'   : 'text28/Function-Call Subsystem2'
 * '<S2>'   : 'text28/Function-Call Subsystem3'
 * '<S3>'   : 'text28/Function-Call Subsystem4'
 * '<S4>'   : 'text28/Function-Call Subsystem7'
 * '<S5>'   : 'text28/RapidECUSetting1'
 * '<S6>'   : 'text28/驱动系统'
 * '<S7>'   : 'text28/Function-Call Subsystem2/xieyi'
 * '<S8>'   : 'text28/Function-Call Subsystem2/xieyi/Motor_toque'
 * '<S9>'   : 'text28/Function-Call Subsystem2/xieyi/Speed'
 * '<S10>'  : 'text28/Function-Call Subsystem3/dianchi'
 * '<S11>'  : 'text28/Function-Call Subsystem3/dianchi/BatAlmLv'
 * '<S12>'  : 'text28/Function-Call Subsystem3/dianchi/BatCurrent'
 * '<S13>'  : 'text28/Function-Call Subsystem3/dianchi/BatSoc'
 * '<S14>'  : 'text28/Function-Call Subsystem3/dianchi/BatState'
 * '<S15>'  : 'text28/Function-Call Subsystem3/dianchi/BatVoltage'
 * '<S16>'  : 'text28/Function-Call Subsystem4/Function-Call Subsystem4'
 * '<S17>'  : 'text28/Function-Call Subsystem4/MeaModule2'
 * '<S18>'  : 'text28/Function-Call Subsystem4/MeaModule5'
 * '<S19>'  : 'text28/Function-Call Subsystem4/ReceiveMessages'
 * '<S20>'  : 'text28/Function-Call Subsystem4/can断线 '
 * '<S21>'  : 'text28/Function-Call Subsystem4/一级警告'
 * '<S22>'  : 'text28/Function-Call Subsystem4/可视'
 * '<S23>'  : 'text28/Function-Call Subsystem4/故障状态报警'
 * '<S24>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO'
 * '<S25>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/MeaModule'
 * '<S26>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/MeaModule1'
 * '<S27>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/MeaModule2'
 * '<S28>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/MeaModule3'
 * '<S29>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatAlmLv_Sub'
 * '<S30>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatCurrent_Sub'
 * '<S31>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatLife_Sub'
 * '<S32>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatSoc_Sub'
 * '<S33>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatState_Sub'
 * '<S34>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BatVoltage_Sub'
 * '<S35>'  : 'text28/Function-Call Subsystem4/ReceiveMessages/BMS_HCU_INFO/BtaSOH_Sub'
 * '<S36>'  : 'text28/Function-Call Subsystem4/can断线 /If Action Subsystem2'
 * '<S37>'  : 'text28/Function-Call Subsystem4/can断线 /If Action Subsystem3'
 * '<S38>'  : 'text28/Function-Call Subsystem4/can断线 /MeaModule1'
 * '<S39>'  : 'text28/Function-Call Subsystem4/一级警告/If Action Subsystem'
 * '<S40>'  : 'text28/Function-Call Subsystem4/一级警告/If Action Subsystem1'
 * '<S41>'  : 'text28/Function-Call Subsystem4/可视/MeaModule3'
 * '<S42>'  : 'text28/Function-Call Subsystem4/故障状态报警/If Action Subsystem'
 * '<S43>'  : 'text28/Function-Call Subsystem4/故障状态报警/If Action Subsystem1'
 * '<S44>'  : 'text28/Function-Call Subsystem7/Function-Call Subsystem2'
 * '<S45>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2'
 * '<S46>'  : 'text28/Function-Call Subsystem7/MeaModule'
 * '<S47>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2'
 * '<S48>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MeaModule5'
 * '<S49>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MeaModule6'
 * '<S50>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/Fail_Grade_Sub'
 * '<S51>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/Live_counter_Sub'
 * '<S52>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/MCU_temperature_Sub'
 * '<S53>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/Motor_Temperature_Sub'
 * '<S54>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/Torque_Limit_High_Sub'
 * '<S55>'  : 'text28/Function-Call Subsystem7/MCU_STATUS_2/MCU_STATUS_2/Torque_Limit_Low_Sub'
 * '<S56>'  : 'text28/RapidECUSetting1/BL'
 * '<S57>'  : 'text28/RapidECUSetting1/DAQ'
 * '<S58>'  : 'text28/RapidECUSetting1/Flash'
 * '<S59>'  : 'text28/RapidECUSetting1/PD'
 * '<S60>'  : 'text28/RapidECUSetting1/Polling'
 * '<S61>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem'
 * '<S62>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem'
 * '<S63>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem/Com0'
 * '<S64>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem/Com1'
 * '<S65>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem/Com2'
 * '<S66>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem/If Action Subsystem'
 * '<S67>'  : 'text28/RapidECUSetting1/BL/Function-Call Subsystem/Function-Call Subsystem/If Action Subsystem1'
 * '<S68>'  : 'text28/RapidECUSetting1/DAQ/daq100ms'
 * '<S69>'  : 'text28/RapidECUSetting1/DAQ/daq10ms'
 * '<S70>'  : 'text28/RapidECUSetting1/DAQ/daq50ms'
 * '<S71>'  : 'text28/RapidECUSetting1/DAQ/daq5ms'
 * '<S72>'  : 'text28/RapidECUSetting1/Flash/FlashOperation'
 * '<S73>'  : 'text28/RapidECUSetting1/PD/10mstask'
 * '<S74>'  : 'text28/RapidECUSetting1/Polling/CCPBackground'
 * '<S75>'  : 'text28/RapidECUSetting1/Polling/CCPReceive'
 * '<S76>'  : 'text28/RapidECUSetting1/Polling/CCPTransmit'
 * '<S77>'  : 'text28/RapidECUSetting1/Polling/CCPReceive/Nothing'
 * '<S78>'  : 'text28/驱动系统/ECU'
 * '<S79>'  : 'text28/驱动系统/MCU_can总线'
 * '<S80>'  : 'text28/驱动系统/Subsystem'
 * '<S81>'  : 'text28/驱动系统/Subsystem2'
 * '<S82>'  : 'text28/驱动系统/ECU/Motor'
 * '<S83>'  : 'text28/驱动系统/ECU/Motor/Control_Mode'
 * '<S84>'  : 'text28/驱动系统/ECU/Motor/Demand_Speed'
 * '<S85>'  : 'text28/驱动系统/ECU/Motor/Demand_Torquee'
 * '<S86>'  : 'text28/驱动系统/ECU/Motor/Fault_Reset'
 * '<S87>'  : 'text28/驱动系统/ECU/Motor/FootBrake'
 * '<S88>'  : 'text28/驱动系统/ECU/Motor/Gear'
 * '<S89>'  : 'text28/驱动系统/ECU/Motor/High_Value'
 * '<S90>'  : 'text28/驱动系统/ECU/Motor/Low_Value'
 * '<S91>'  : 'text28/驱动系统/ECU/Motor/MCU_Enable'
 * '<S92>'  : 'text28/驱动系统/ECU/Motor/handBrake'
 * '<S93>'  : 'text28/驱动系统/MCU_can总线/MeaModule'
 * '<S94>'  : 'text28/驱动系统/MCU_can总线/安全回路out'
 * '<S95>'  : 'text28/驱动系统/MCU_can总线/安全回路out/If Action Subsystem1'
 * '<S96>'  : 'text28/驱动系统/MCU_can总线/安全回路out/If Action Subsystem2'
 * '<S97>'  : 'text28/驱动系统/Subsystem/appsrule'
 * '<S98>'  : 'text28/驱动系统/Subsystem/制动与尾灯'
 * '<S99>'  : 'text28/驱动系统/Subsystem/制动与待驶 '
 * '<S100>' : 'text28/驱动系统/Subsystem/前轮转速'
 * '<S101>' : 'text28/驱动系统/Subsystem/滑转率计算'
 * '<S102>' : 'text28/驱动系统/Subsystem/电机测速'
 * '<S103>' : 'text28/驱动系统/Subsystem/角度传感器'
 * '<S104>' : 'text28/驱动系统/Subsystem/appsrule/MeaModule'
 * '<S105>' : 'text28/驱动系统/Subsystem/appsrule/MeaModule1'
 * '<S106>' : 'text28/驱动系统/Subsystem/appsrule/动力信号判断'
 * '<S107>' : 'text28/驱动系统/Subsystem/appsrule/同时油门刹车 '
 * '<S108>' : 'text28/驱动系统/Subsystem/appsrule/无刹车判断'
 * '<S109>' : 'text28/驱动系统/Subsystem/appsrule/油门小于5%判断'
 * '<S110>' : 'text28/驱动系统/Subsystem/appsrule/动力信号判断/动力信号'
 * '<S111>' : 'text28/驱动系统/Subsystem/appsrule/动力信号判断/故障信号'
 * '<S112>' : 'text28/驱动系统/Subsystem/appsrule/同时油门刹车 /故障'
 * '<S113>' : 'text28/驱动系统/Subsystem/appsrule/同时油门刹车 /正常  '
 * '<S114>' : 'text28/驱动系统/Subsystem/appsrule/同时油门刹车 /正常  /故障'
 * '<S115>' : 'text28/驱动系统/Subsystem/appsrule/同时油门刹车 /正常  /正常'
 * '<S116>' : 'text28/驱动系统/Subsystem/appsrule/无刹车判断/有刹车'
 * '<S117>' : 'text28/驱动系统/Subsystem/appsrule/无刹车判断/没刹车'
 * '<S118>' : 'text28/驱动系统/Subsystem/appsrule/油门小于5%判断/油门大于5%'
 * '<S119>' : 'text28/驱动系统/Subsystem/appsrule/油门小于5%判断/油门小于5%'
 * '<S120>' : 'text28/驱动系统/Subsystem/制动与尾灯/If Action Subsystem'
 * '<S121>' : 'text28/驱动系统/Subsystem/制动与尾灯/If Action Subsystem1'
 * '<S122>' : 'text28/驱动系统/Subsystem/制动与尾灯/If Action Subsystem2'
 * '<S123>' : 'text28/驱动系统/Subsystem/制动与尾灯/If Action Subsystem3'
 * '<S124>' : 'text28/驱动系统/Subsystem/制动与尾灯/MeaModule'
 * '<S125>' : 'text28/驱动系统/Subsystem/制动与尾灯/MeaModule1'
 * '<S126>' : 'text28/驱动系统/Subsystem/制动与尾灯/MeaModule2'
 * '<S127>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule'
 * '<S128>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule1'
 * '<S129>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule2'
 * '<S130>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule3'
 * '<S131>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule4'
 * '<S132>' : 'text28/驱动系统/Subsystem/制动与待驶 /MeaModule5'
 * '<S133>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶按键'
 * '<S134>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶激活'
 * '<S135>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1'
 * '<S136>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶按键/MeaModule3'
 * '<S137>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶激活/If Action Subsystem'
 * '<S138>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶激活/If Action Subsystem1'
 * '<S139>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶激活/If Action Subsystem2'
 * '<S140>' : 'text28/驱动系统/Subsystem/制动与待驶 /待驶激活/If Action Subsystem3'
 * '<S141>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1/If Action Subsystem'
 * '<S142>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1/If Action Subsystem1'
 * '<S143>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1/鸣笛'
 * '<S144>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1/鸣笛/If Action Subsystem'
 * '<S145>' : 'text28/驱动系统/Subsystem/制动与待驶 /鸣笛1/鸣笛/If Action Subsystem1'
 * '<S146>' : 'text28/驱动系统/Subsystem/前轮转速/轮速'
 * '<S147>' : 'text28/驱动系统/Subsystem/前轮转速/轮速/MeaModule'
 * '<S148>' : 'text28/驱动系统/Subsystem/前轮转速/轮速/MeaModule1'
 * '<S149>' : 'text28/驱动系统/Subsystem/前轮转速/轮速/MeaModule2'
 * '<S150>' : 'text28/驱动系统/Subsystem/滑转率计算/滑转率计算'
 * '<S151>' : 'text28/驱动系统/Subsystem/滑转率计算/滑转率计算/MeaModule'
 * '<S152>' : 'text28/驱动系统/Subsystem/电机测速/Function-Call Subsystem4'
 * '<S153>' : 'text28/驱动系统/Subsystem/电机测速/MeaModule'
 * '<S154>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages'
 * '<S155>' : 'text28/驱动系统/Subsystem/电机测速/转速转轮速'
 * '<S156>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/MeaModule'
 * '<S157>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/MeaModule1'
 * '<S158>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1'
 * '<S159>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/Active_Discharge_Enab_Sub'
 * '<S160>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/IGBT_Enable_Feedback_Sub'
 * '<S161>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/Livecounter_Sub'
 * '<S162>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/MotorACCurrent_Sub'
 * '<S163>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/MotorTorque_Sub'
 * '<S164>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/Motor_Speed_Sub'
 * '<S165>' : 'text28/驱动系统/Subsystem/电机测速/ReceiveMessages/resive1/Precharge_Allow_Sub'
 * '<S166>' : 'text28/驱动系统/Subsystem/角度传感器/MeaModule'
 * '<S167>' : 'text28/驱动系统/Subsystem/角度传感器/MeaModule1'
 * '<S168>' : 'text28/驱动系统/Subsystem/角度传感器/MeaModule2'
 * '<S169>' : 'text28/驱动系统/Subsystem/角度传感器/MeaModule4'
 * '<S170>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号'
 * '<S171>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器是否正常'
 * '<S172>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/MeaModule'
 * '<S173>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/MeaModule1'
 * '<S174>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/MeaModule3'
 * '<S175>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/不可靠信号判断'
 * '<S176>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 '
 * '<S177>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/百分比转化 '
 * '<S178>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/不可靠信号判断/If Action Subsystem8'
 * '<S179>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/不可靠信号判断/If Action Subsystem9'
 * '<S180>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule1'
 * '<S181>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule2'
 * '<S182>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule3'
 * '<S183>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule4'
 * '<S184>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule5'
 * '<S185>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /MeaModule6'
 * '<S186>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /空量程 '
 * '<S187>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值'
 * '<S188>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值2'
 * '<S189>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /空量程 /If Action Subsystem'
 * '<S190>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /空量程 /If Action Subsystem1'
 * '<S191>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值/If Action Subsystem'
 * '<S192>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值/If Action Subsystem1'
 * '<S193>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值2/If Action Subsystem'
 * '<S194>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/油门数值 /阈值2/If Action Subsystem1'
 * '<S195>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/百分比转化 /MeaModule1'
 * '<S196>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/百分比转化 /MeaModule2'
 * '<S197>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/百分比转化 /角度归零化百分比1'
 * '<S198>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器数据处理及不可靠信号/百分比转化 /角度归零化百分比2'
 * '<S199>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器是否正常/If Action Subsystem'
 * '<S200>' : 'text28/驱动系统/Subsystem/角度传感器/角度传感器是否正常/If Action Subsystem1'
 * '<S201>' : 'text28/驱动系统/Subsystem2/MeaModule1'
 */
#endif                                 /* RTW_HEADER_text28_h_ */

/* File trailer for ECUCoder generated file text28.h.
 *
 * [EOF]
 */
