/*
 * Code generated for Simulink model text28.
 *
 * FILE    : text28.c
 *
 * VERSION : 1.173
 *
 * DATE    : Sat Oct 05 10:25:27 2024
 *
 * Copyright 2011-2012 ECUCoder. All Rights Reserved.
 */

#include "text28.h"
#include "text28_private.h"

/* #include "myinclude.h" */
uint16 TLE6232DIA[12]= { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

/* Exported data definition */

/* Definition for custom storage class: Default */
uint8_T CAN_ok;
boolean_T FAN_sign;
real32_T McuTemp;
real32_T MotorTemp;
uint32_T anquan_out;
real_T app_add2;
real_T app_baifenbi;
real_T app_date1;
real_T app_date2;
real_T app_konghou;
real_T app_scs;
real_T apple;
real_T apps_erro;
real_T apps_rule;
boolean_T aqhl;
real_T baifenbi1;
real_T baifenbi2;
real_T baifenbi3;
real32_T baojing;
uint8_T bms_canok;
boolean_T bms_sign;
real_T bms_sign1;
real_T car_speed;
real_T daishi;
uint8_T daishi_11;
real_T daishi_chu;
real_T daishi_fanhui;
boolean_T daishi_out;
real32_T dianya;
real_T enable_sign;
real_T huazhuan;
real_T jiaodu1;
real_T jiaodu2;
uint16_T jiaodu_11111;
uint16_T jiaodu_2222;
uint32_T keshi;
real_T left_speed;
real_T motor_speed;
real_T motor_torque;
real_T rear_speed;
real_T right_speed;
real32_T soc;
uint16_T youya1;
real_T youya2;
real_T youya3;
real32_T zhuangtai;
real_T zuizhong;

/* Block signals (auto storage) */
B_text28_T text28_B;

/* Block states (auto storage) */
DW_text28_T text28_DW;

/* Real-time model */
RT_MODEL_text28_T text28_M_;
RT_MODEL_text28_T *const text28_M = &text28_M_;
static void rate_monotonic_scheduler(void);

/* TLE6240 control function */
void ec_tle6232_diag(void)
{
  int i;
  uint16 RD_DIAG[1] = { 0x8000 };      //Read DIAG Register

  uint16 RD_DIAG_RX1[1] = { 0x0000 };  //Read DIAG Register--returned value, chip1

  uint16 RD_DIAG_RX2[1] = { 0x0000 };  //Read DIAG Register--returned value, chip2

  ec_spi_masterwriteread(0, 1, 1, RD_DIAG, RD_DIAG_RX1);
  i= 10;
  while (i--) {
    ;
  }

  for (i=0; i<6; i++) {
    TLE6232DIA[i] = ((RD_DIAG_RX1[0] & (0x0003<<(i*2))))>>(i*2);
  }

  ec_spi_masterwriteread(0, 2, 1, RD_DIAG, RD_DIAG_RX2);
  i= 10;
  while (i--) {
    ;
  }

  for (i=0; i<6; i++) {
    TLE6232DIA[i+6] = ((RD_DIAG_RX2[0] & (0x0003<<(i*2))))>>(i*2);
  }
}

void ISR_Rti_CH23(void)
{
  EMIOS.CH[23].CSR.B.FLAG = 0x1;       /* Clear interrupt flag */
  ECUCoderModelBaseCounter++;
  rate_monotonic_scheduler();
}

void ISR_FlexCAN_2_MB1(void)
{
  /* Call the system: <S56>/Function-Call Subsystem */
  {
    /* Output and update for function-call system: '<S56>/Function-Call Subsystem' */

    /* S-Function (ec55xx_canreceiveslb): '<S61>/CANReceive1' */

    /* Receive CAN message */
    {
      uint8 CAN2BUF1RX[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint8 can2buf1looprx= 0;
      text28_B.CANReceive1_o3= 278;
      text28_B.CANReceive1_o5= 8;
      text28_B.CANReceive1_o2= ec_can_receive(2,1, CAN2BUF1RX);
      text28_B.CANReceive1_o4[0]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[1]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[2]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[3]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[4]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[5]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[6]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
      text28_B.CANReceive1_o4[7]= CAN2BUF1RX[can2buf1looprx];
      can2buf1looprx++;
    }

    /* Call the system: <S61>/Function-Call Subsystem */

    /* Output and update for function-call system: '<S61>/Function-Call Subsystem' */

    /* If: '<S62>/If' incorporates:
     *  Constant: '<S63>/Constant'
     *  Constant: '<S64>/Constant'
     *  Constant: '<S65>/Constant'
     *  Constant: '<S67>/Constant'
     *  RelationalOperator: '<S63>/Compare'
     *  RelationalOperator: '<S64>/Compare'
     *  RelationalOperator: '<S65>/Compare'
     *  Sum: '<S62>/Add'
     */
    if (((int32_T)((uint32_T)(text28_B.CANReceive1_o4[0] == 83) +
                   (text28_B.CANReceive1_o4[5] == 84)) == 2) > 0) {
      /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem' incorporates:
       *  ActionPort: '<S66>/Action Port'
       */

      /* S-Function (ec55xx_bootloaderslb): '<S66>/BootLoader' */
      {
        uint16 i= 0;
        uint8 CAN2BUF9TX[]= { 11, 12, 12, 13 };

        uint8 returnCode1= 0;
        uint8 bootflag[]= { 1, 0, 0, 0, 0, 0, 0, 0 };

        DisableInterrupts();
        returnCode1 = pFlashErase( &ssdConfig, FALSE, 0x00000000, 0x00000000,
          0x00000800, NULL_CALLBACK );
        if (returnCode1 != H7F_OK ) {
          while (1) {
            ;
          }
        }

        pFlashProgram( &ssdConfig, 0x1ffff0, 8,(uint32)bootflag, NULL_CALLBACK );
        i= 1000;
        while (i--) {
          ;
        }

        ec_can_transmit(2, 9, 0, 593, 4, CAN2BUF9TX);
        i= 10000;
        while (i--) {
          ;
        }
      }

      /* S-Function (ec55xx_cpuresetslb): '<S66>/CPUReset' */

      /* Perform a microcontroller reset */
      ec_cpu_reset();

      /* End of Outputs for SubSystem: '<S62>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S67>/Action Port'
       */

      /* S-Function (ec55xx_cantransmitslb): '<S67>/CANTransmit' */

      /*Transmit CAN message*/
      {
        uint8 CAN2BUF9TX[1];
        uint8 can2buf9looptx= 0;
        CAN2BUF9TX[can2buf9looptx]= ((uint8_T)1U);
        can2buf9looptx++;
        text28_B.CANTransmit= ec_can_transmit(2, 9, 0, 593U, 1, CAN2BUF9TX);
      }

      /* End of Outputs for SubSystem: '<S62>/If Action Subsystem1' */
    }

    /* End of If: '<S62>/If' */
  }

  FLEXCAN(2).IFRL.B.BUF01I = 1;        /* Clear CAN interrupt flag by writing it to 1 */
}

void ISR_FlexCAN_2_MB0(void)
{
  /* Call the system: <S60>/CCPReceive */
  {
    /* Output and update for function-call system: '<S60>/CCPReceive' */

    /* S-Function (ec55xx_canreceiveslb): '<S75>/CANReceive' */

    /* Receive CAN message */
    {
      uint8 CAN2BUF0RX[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint8 can2buf0looprx= 0;
      text28_B.CANReceive_o3= 256;
      text28_B.CANReceive_o5= 8;
      text28_B.CANReceive_o2= ec_can_receive(2,0, CAN2BUF0RX);
      text28_B.CANReceive_o4[0]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[1]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[2]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[3]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[4]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[5]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[6]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
      text28_B.CANReceive_o4[7]= CAN2BUF0RX[can2buf0looprx];
      can2buf0looprx++;
    }

    /* Nothing to do for system: <S75>/Nothing */
  }

  FLEXCAN(2).IFRL.B.BUF00I = 1;        /* Clear CAN interrupt flag by writing it to 1 */
}

void ISR_FlexCAN_2_MB8(void)
{
  /* Call the system: <S60>/CCPTransmit */
  {
    /* Output and update for function-call system: '<S60>/CCPTransmit' */

    /* S-Function (ec55xx_ccpslb2): '<S76>/CCPTXConfirmation' */
    ec_can_appltxconfirmation(FLEXCAN_C,8);
  }

  FLEXCAN(2).IFRL.B.BUF08I = 1;        /* Clear CAN interrupt flag by writing it to 1 */
}

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void text28_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(text28_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(text28_M, 2));
  eventFlags[3] = ((boolean_T)rtmStepTask(text28_M, 3));
  eventFlags[4] = ((boolean_T)rtmStepTask(text28_M, 4));
  eventFlags[5] = ((boolean_T)rtmStepTask(text28_M, 5));
  eventFlags[6] = ((boolean_T)rtmStepTask(text28_M, 6));
  eventFlags[7] = ((boolean_T)rtmStepTask(text28_M, 7));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (text28_M->Timing.TaskCounters.TID[1])++;
  if ((text28_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.001s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[1] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[2])++;
  if ((text28_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.005s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[2] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[3])++;
  if ((text28_M->Timing.TaskCounters.TID[3]) > 19) {/* Sample time: [0.01s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[3] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[4])++;
  if ((text28_M->Timing.TaskCounters.TID[4]) > 99) {/* Sample time: [0.05s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[4] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[5])++;
  if ((text28_M->Timing.TaskCounters.TID[5]) > 199) {/* Sample time: [0.1s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[5] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[6])++;
  if ((text28_M->Timing.TaskCounters.TID[6]) > 399) {/* Sample time: [0.2s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[6] = 0;
  }

  (text28_M->Timing.TaskCounters.TID[7])++;
  if ((text28_M->Timing.TaskCounters.TID[7]) > 999) {/* Sample time: [0.5s, 0.0s] */
    text28_M->Timing.TaskCounters.TID[7] = 0;
  }
}

/*
 * Output and update for action system:
 *    '<S94>/If Action Subsystem2'
 *    '<S106>/动力信号'
 *    '<S108>/没刹车'
 *    '<S109>/油门小于5%'
 *    '<S134>/If Action Subsystem'
 *    '<S134>/If Action Subsystem2'
 *    '<S143>/If Action Subsystem'
 *    '<S21>/If Action Subsystem1'
 *    '<S23>/If Action Subsystem1'
 */
void text28_IfActionSubsystem2(real_T *rty_Out1)
{
  /* SignalConversion: '<S96>/OutportBufferForOut1' incorporates:
   *  Constant: '<S96>/Constant'
   */
  *rty_Out1 = 1.0;
}

/*
 * Output and update for action system:
 *    '<S106>/故障信号'
 *    '<S107>/故障'
 *    '<S108>/有刹车'
 *    '<S109>/油门大于5%'
 *    '<S134>/If Action Subsystem1'
 *    '<S134>/If Action Subsystem3'
 *    '<S135>/If Action Subsystem1'
 *    '<S143>/If Action Subsystem1'
 *    '<S21>/If Action Subsystem'
 *    '<S23>/If Action Subsystem'
 */
void text28_u(real_T *rty_Out1)
{
  /* SignalConversion: '<S111>/OutportBufferForOut1' incorporates:
   *  Constant: '<S111>/Constant'
   */
  *rty_Out1 = 0.0;
}

/*
 * Output and update for action system:
 *    '<S135>/If Action Subsystem'
 *    '<S20>/If Action Subsystem3'
 */
void text28_IfActionSubsystem(real_T *rty_Out1)
{
  /* SignalConversion: '<S141>/OutportBufferForOut1' incorporates:
   *  Constant: '<S141>/Constant2'
   */
  *rty_Out1 = 1.0;
}

/*
 * Output and update for action system:
 *    '<S186>/If Action Subsystem'
 *    '<S187>/If Action Subsystem'
 *    '<S188>/If Action Subsystem'
 */
void text28_IfActionSubsystem_h(real_T rtu_In1, real_T *rty_Out1)
{
  /* Inport: '<S189>/In1' */
  *rty_Out1 = rtu_In1;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function for TID0 */
void text28_step0(void)                /* Sample time: [0.0005s, 0.0s] */
{
  {                                    /* Sample time: [0.0005s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model step function for TID1 */
void text28_step1(void)                /* Sample time: [0.001s, 0.0s] */
{
  /* S-Function (fcncallgen): '<S60>/Function-Call Generator' incorporates:
   *  SubSystem: '<S60>/CCPBackground'
   */

  /* S-Function (ec55xx_ccpslb): '<S74>/CCPBackground' */
  ccpBackground();
}

/* Model step function for TID2 */
void text28_step2(void)                /* Sample time: [0.005s, 0.0s] */
{
  /* S-Function (fcncallgen): '<S57>/5ms' incorporates:
   *  SubSystem: '<S57>/daq5ms'
   */

  /* S-Function (ec55xx_ccpslb1): '<S71>/CCPDAQ' */
  ccpDaq(0);
}

/* Model step function for TID3 */
void text28_step3(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_Merge_n;
  real_T rtb_Merge1;
  real_T rtb_Merge1_m;
  real_T rtb_Merge_l;
  real_T rtb_Merge2;
  real_T rtb_Merge_n3;
  real_T rtb_Merge_d;
  real_T rtb_Merge_n4;
  real_T rtb_Merge_f;
  real_T rtb_Gain1;
  real_T rtb_Product;
  int32_T rtb_MotorTorque_L;
  real_T rtb_Product_e;
  real_T rtb_Product_j;
  real32_T rtb_MotorTorque_sat;
  real32_T tmp;

  /* S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/驱动系统'
   */

  /* S-Function (ec55xx_swislb): '<S99>/SwitchInput' */

  /* Read the the value of the specified switch input */
  aqhl= ec_gpio_read(152);

  /* S-Function (ec55xx_pdsdslb): '<S133>/PowerDriverSwitchDiagnosis' */

  /* Read the the value of the specified channel */
  daishi_11= TLE6232DIA[7];

  /* Switch: '<S133>/Switch' incorporates:
   *  Constant: '<S133>/Constant'
   *  Constant: '<S133>/Constant1'
   */
  if (daishi_11 > 0) {
    daishi = 0.0;
  } else {
    daishi = 1.0;
  }

  /* End of Switch: '<S133>/Switch' */

  /* If: '<S134>/If' */
  if (daishi > 0.0) {
    /* Outputs for IfAction SubSystem: '<S134>/If Action Subsystem' incorporates:
     *  ActionPort: '<S137>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge_n);

    /* End of Outputs for SubSystem: '<S134>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S134>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S138>/Action Port'
     */
    text28_u(&rtb_Merge_n);

    /* End of Outputs for SubSystem: '<S134>/If Action Subsystem1' */
  }

  /* End of If: '<S134>/If' */

  /* Outputs for Atomic SubSystem: '<S80>/制动与尾灯' */

  /* S-Function (ec55xx_asislb): '<S98>/前油压' */

  /* Read the ADC conversion result of the analog signal */
  youya1= ec_adc_readresult(22);

  /* If: '<S98>/If' incorporates:
   *  Constant: '<S120>/Constant'
   *  Constant: '<S121>/Constant'
   */
  if ((youya1 > 550) && (youya1 < 4600)) {
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem' incorporates:
     *  ActionPort: '<S120>/Action Port'
     */
    youya2 = 1.0;

    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem' incorporates:
     *  ActionPort: '<S120>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S121>/Action Port'
     */
    youya2 = 0.0;

    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem1' */
    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem' */
  }

  /* End of If: '<S98>/If' */

  /* DataTypeConversion: '<S98>/Data Type Conversion' */
  text28_B.DataTypeConversion = (uint32_T)youya2;

  /* S-Function (ec55xx_pdpslb): '<S98>/尾灯' */

  /* Power driver PWM output for channel 19 */
  ec_pwm_output(19,1U,text28_B.DataTypeConversion);

  /* If: '<S98>/If1' incorporates:
   *  Constant: '<S122>/Constant'
   *  Constant: '<S123>/Constant'
   */
  if ((youya1 > 850) && (youya1 < 4600)) {
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S122>/Action Port'
     */
    youya3 = 1.0;

    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S122>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S98>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S123>/Action Port'
     */
    youya3 = 0.0;

    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem3' */
    /* End of Outputs for SubSystem: '<S98>/If Action Subsystem2' */
  }

  /* End of If: '<S98>/If1' */
  /* End of Outputs for SubSystem: '<S80>/制动与尾灯' */

  /* If: '<S134>/If1' */
  if (youya2 > 0.0) {
    /* Outputs for IfAction SubSystem: '<S134>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S139>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge1);

    /* End of Outputs for SubSystem: '<S134>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S134>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S140>/Action Port'
     */
    text28_u(&rtb_Merge1);

    /* End of Outputs for SubSystem: '<S134>/If Action Subsystem3' */
  }

  /* End of If: '<S134>/If1' */

  /* Logic: '<S134>/Logical Operator' */
  daishi_out = ((rtb_Merge_n != 0.0) && (rtb_Merge1 != 0.0));

  /* UnitDelay: '<S99>/Unit Delay' */
  daishi_fanhui = text28_DW.UnitDelay_DSTATE;

  /* Sum: '<S99>/Sum' */
  daishi_chu = (real_T)daishi_out + daishi_fanhui;

  /* Product: '<S99>/Product' */
  rtb_Product = (real_T)aqhl * daishi_chu;

  /* Saturate: '<S99>/Saturation' */
  if (rtb_Product > 1.0) {
    enable_sign = 1.0;
  } else if (rtb_Product < 0.0) {
    enable_sign = 0.0;
  } else {
    enable_sign = rtb_Product;
  }

  /* End of Saturate: '<S99>/Saturation' */

  /* Switch: '<S99>/Switch' incorporates:
   *  Constant: '<S99>/Constant'
   *  Constant: '<S99>/Constant1'
   */
  if (enable_sign > 0.0) {
    rtb_MotorTorque_L = 0;
  } else {
    rtb_MotorTorque_L = 1;
  }

  /* End of Switch: '<S99>/Switch' */

  /* Saturate: '<S91>/MCU_Enable_sat' */
  if (enable_sign > 1.0) {
    rtb_Product_e = 1.0;
  } else if (enable_sign < 0.0) {
    rtb_Product_e = 0.0;
  } else {
    rtb_Product_e = enable_sign;
  }

  /* S-Function (sfix_bitop): '<S82>/or1' incorporates:
   *  ArithShift: '<S86>/Fault_Reset_S'
   *  DataTypeConversion: '<S86>/Fault_Reset_Convert'
   *  DataTypeConversion: '<S86>/Fault_Reset_Convert1'
   *  DataTypeConversion: '<S91>/MCU_Enable_Convert'
   *  DataTypeConversion: '<S91>/MCU_Enable_Convert1'
   *  Rounding: '<S86>/Fault_ResetRon'
   *  Rounding: '<S91>/MCU_EnableRon'
   *  S-Function (sfix_bitop): '<S86>/Fault_Reset_L'
   *  S-Function (sfix_bitop): '<S91>/MCU_Enable_L'
   *  Saturate: '<S86>/Fault_Reset_1sat'
   *  Saturate: '<S86>/Fault_Reset_sat'
   *  Saturate: '<S91>/MCU_Enable_1sat'
   *  Saturate: '<S91>/MCU_Enable_sat'
   */
  text28_B.or1_a = (uint8_T)((int32_T)((uint32_T)ldexp(rt_roundd_snf((real_T)
    rtb_MotorTorque_L), 1) & 2U) | 24 | (int32_T)((uint32_T)rt_roundd_snf
    (rtb_Product_e) & 1U));

  /* S-Function (sfix_bitop): '<S82>/or2' */
  text28_B.or2_f = 202U;

  /* S-Function (sfix_bitop): '<S82>/or3' */
  text28_B.or3_k = 168U;

  /* S-Function (sfix_bitop): '<S82>/or4' */
  text28_B.or4_m = 140U;

  /* S-Function (ec55xx_asislb): '<S103>/角度1' */

  /* Read the ADC conversion result of the analog signal */
  jiaodu_11111= ec_adc_readresult(14);

  /* S-Function (ec55xx_asislb): '<S103>/角度2' */

  /* Read the ADC conversion result of the analog signal */
  jiaodu_2222= ec_adc_readresult(25);

  /* Outputs for Atomic SubSystem: '<S103>/角度传感器数据处理及不可靠信号' */
  /* Product: '<S198>/Product' incorporates:
   *  Constant: '<S198>/初始值1'
   *  Constant: '<S198>/总值1'
   *  Sum: '<S198>/Sum1'
   */
  baifenbi1 = ((real_T)jiaodu_11111 - 830.0) / 1780.0;

  /* Product: '<S197>/Product' incorporates:
   *  Constant: '<S197>/初始值1'
   *  Constant: '<S197>/总值1'
   *  Sum: '<S197>/Sum1'
   */
  baifenbi2 = ((real_T)jiaodu_2222 - 960.0) / 1800.0;

  /* Abs: '<S170>/Abs' incorporates:
   *  Sum: '<S177>/Sum2'
   */
  baifenbi3 = fabs(baifenbi1 - baifenbi2);

  /* If: '<S175>/If4' incorporates:
   *  Constant: '<S170>/Constant'
   *  Constant: '<S178>/Constant'
   *  Constant: '<S179>/Constant'
   *  Product: '<S170>/Product1'
   */
  if (baifenbi3 * 100.0 > 10.0) {
    /* Outputs for IfAction SubSystem: '<S175>/If Action Subsystem8' incorporates:
     *  ActionPort: '<S178>/Action Port'
     */
    apps_erro = 0.0;

    /* End of Outputs for SubSystem: '<S175>/If Action Subsystem8' */
  } else {
    /* Outputs for IfAction SubSystem: '<S175>/If Action Subsystem8' incorporates:
     *  ActionPort: '<S178>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S175>/If Action Subsystem9' incorporates:
     *  ActionPort: '<S179>/Action Port'
     */
    apps_erro = 1.0;

    /* End of Outputs for SubSystem: '<S175>/If Action Subsystem9' */
    /* End of Outputs for SubSystem: '<S175>/If Action Subsystem8' */
  }

  /* End of If: '<S175>/If4' */

  /* Abs: '<S176>/Abs1' incorporates:
   *  Constant: '<S176>/Constant1'
   *  Sum: '<S176>/Sum1'
   */
  jiaodu1 = fabs((real_T)jiaodu_11111 - 850.0);

  /* Abs: '<S176>/Abs' incorporates:
   *  Constant: '<S176>/Constant2'
   *  Sum: '<S176>/Sum3'
   */
  jiaodu2 = fabs((real_T)jiaodu_2222 - 970.0);

  /* Gain: '<S176>/Gain10' incorporates:
   *  Gain: '<S176>/Gain2'
   *  Gain: '<S176>/Gain3'
   *  Sum: '<S176>/Sum6'
   */
  apple = (0.011363636363636364 * jiaodu1 + 0.011204481792717087 * jiaodu2) *
    0.5;

  /* If: '<S186>/If' incorporates:
   *  Constant: '<S190>/Constant'
   */
  if (apple >= 1.0) {
    /* Outputs for IfAction SubSystem: '<S186>/If Action Subsystem' incorporates:
     *  ActionPort: '<S189>/Action Port'
     */
    text28_IfActionSubsystem_h(apple, &rtb_Merge_f);

    /* End of Outputs for SubSystem: '<S186>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S186>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S190>/Action Port'
     */
    rtb_Merge_f = 0.0;

    /* End of Outputs for SubSystem: '<S186>/If Action Subsystem1' */
  }

  /* End of If: '<S186>/If' */

  /* Product: '<S176>/Product' incorporates:
   *  Constant: '<S176>/Constant10'
   */
  app_konghou = 6.0 * rtb_Merge_f;

  /* Sum: '<S176>/Add' incorporates:
   *  Constant: '<S176>/Constant11'
   */
  app_add2 = app_konghou - 6.358E-5;

  /* If: '<S187>/If' incorporates:
   *  Constant: '<S192>/Constant'
   */
  if (app_add2 >= 1.0) {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem' incorporates:
     *  ActionPort: '<S191>/Action Port'
     */
    text28_IfActionSubsystem_h(app_add2, (&(app_date1)));

    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S187>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S192>/Action Port'
     */
    app_date1 = 0.0;

    /* End of Outputs for SubSystem: '<S187>/If Action Subsystem1' */
  }

  /* End of If: '<S187>/If' */

  /* Product: '<S170>/Product' */
  app_date2 = app_date1 * apps_erro;

  /* Gain: '<S176>/Gain1' incorporates:
   *  Constant: '<S176>/Constant3'
   *  Product: '<S176>/Divide'
   */
  rtb_Gain1 = apple / 20.0 * 100.0;

  /* If: '<S188>/If' incorporates:
   *  Constant: '<S194>/Constant'
   */
  if (rtb_Gain1 >= 0.0) {
    /* Outputs for IfAction SubSystem: '<S188>/If Action Subsystem' incorporates:
     *  ActionPort: '<S193>/Action Port'
     */
    text28_IfActionSubsystem_h(rtb_Gain1, (&(app_baifenbi)));

    /* End of Outputs for SubSystem: '<S188>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S188>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S194>/Action Port'
     */
    app_baifenbi = 0.0;

    /* End of Outputs for SubSystem: '<S188>/If Action Subsystem1' */
  }

  /* End of If: '<S188>/If' */
  /* End of Outputs for SubSystem: '<S103>/角度传感器数据处理及不可靠信号' */

  /* If: '<S108>/If2' */
  if (youya3 == 0.0) {
    /* Outputs for IfAction SubSystem: '<S108>/没刹车' incorporates:
     *  ActionPort: '<S117>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge1_m);

    /* End of Outputs for SubSystem: '<S108>/没刹车' */
  } else {
    /* Outputs for IfAction SubSystem: '<S108>/有刹车' incorporates:
     *  ActionPort: '<S116>/Action Port'
     */
    text28_u(&rtb_Merge1_m);

    /* End of Outputs for SubSystem: '<S108>/有刹车' */
  }

  /* End of If: '<S108>/If2' */

  /* If: '<S109>/If1' */
  if (app_baifenbi < 5.0) {
    /* Outputs for IfAction SubSystem: '<S109>/油门小于5%' incorporates:
     *  ActionPort: '<S119>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge_l);

    /* End of Outputs for SubSystem: '<S109>/油门小于5%' */
  } else {
    /* Outputs for IfAction SubSystem: '<S109>/油门大于5%' incorporates:
     *  ActionPort: '<S118>/Action Port'
     */
    text28_u(&rtb_Merge_l);

    /* End of Outputs for SubSystem: '<S109>/油门大于5%' */
  }

  /* End of If: '<S109>/If1' */

  /* Product: '<S97>/Product' */
  rtb_Product_e = rtb_Merge_l * rtb_Merge1_m;

  /* If: '<S107>/If' incorporates:
   *  If: '<S113>/If'
   *  UnitDelay: '<S97>/Unit Delay'
   */
  if ((app_baifenbi > 25.0) && (youya3 == 1.0)) {
    /* Outputs for IfAction SubSystem: '<S107>/故障' incorporates:
     *  ActionPort: '<S112>/Action Port'
     */
    text28_u(&rtb_Merge2);

    /* End of Outputs for SubSystem: '<S107>/故障' */
  } else {
    /* Outputs for IfAction SubSystem: '<S107>/正常  ' incorporates:
     *  ActionPort: '<S113>/Action Port'
     */
    if (text28_DW.UnitDelay_DSTATE_l >= 1.0) {
      /* Outputs for IfAction SubSystem: '<S113>/正常' incorporates:
       *  ActionPort: '<S115>/Action Port'
       */
      /* If: '<S113>/If' incorporates:
       *  Constant: '<S115>/Constant'
       *  SignalConversion: '<S115>/OutportBufferForOut1'
       */
      rtb_Merge2 = 1.0;

      /* End of Outputs for SubSystem: '<S113>/正常' */
    } else {
      /* Outputs for IfAction SubSystem: '<S113>/正常' incorporates:
       *  ActionPort: '<S115>/Action Port'
       */
      /* Outputs for IfAction SubSystem: '<S113>/故障' incorporates:
       *  ActionPort: '<S114>/Action Port'
       */
      /* If: '<S113>/If' incorporates:
       *  Constant: '<S114>/Constant'
       *  SignalConversion: '<S114>/OutportBufferForOut1'
       *  SignalConversion: '<S115>/OutportBufferForOut1'
       */
      rtb_Merge2 = 0.0;

      /* End of Outputs for SubSystem: '<S113>/故障' */
      /* End of Outputs for SubSystem: '<S113>/正常' */
    }

    /* End of Outputs for SubSystem: '<S107>/正常  ' */
  }

  /* End of If: '<S107>/If' */

  /* If: '<S106>/If3' incorporates:
   *  Sum: '<S97>/Sum'
   */
  if (rtb_Product_e + rtb_Merge2 >= 1.0) {
    /* Outputs for IfAction SubSystem: '<S106>/动力信号' incorporates:
     *  ActionPort: '<S110>/Action Port'
     */
    text28_IfActionSubsystem2((&(apps_rule)));

    /* End of Outputs for SubSystem: '<S106>/动力信号' */
  } else {
    /* Outputs for IfAction SubSystem: '<S106>/故障信号' incorporates:
     *  ActionPort: '<S111>/Action Port'
     */
    text28_u((&(apps_rule)));

    /* End of Outputs for SubSystem: '<S106>/故障信号' */
  }

  /* End of If: '<S106>/If3' */

  /* Product: '<S97>/Product1' */
  zuizhong = app_date2 * apps_rule;

  /* Saturate: '<S85>/Demand_Torquee_sat' */
  if (zuizhong > 5000.0) {
    rtb_Product_e = 5000.0;
  } else if (zuizhong < -5000.0) {
    rtb_Product_e = -5000.0;
  } else {
    rtb_Product_e = zuizhong;
  }

  /* S-Function (sfix_bitop): '<S85>/Demand_Torquee_L' incorporates:
   *  Constant: '<S85>/Demand_Torquee_O'
   *  DataTypeConversion: '<S85>/Demand_Torquee_Convert'
   *  Rounding: '<S85>/Demand_TorqueeRon'
   *  Saturate: '<S85>/Demand_Torquee_sat'
   *  Sum: '<S85>/Demand_Torquee_st'
   */
  rtb_MotorTorque_L = (int32_T)((uint32_T)rt_roundd_snf(rtb_Product_e - -5000.0)
    & 65535U);

  /* S-Function (sfix_bitop): '<S82>/or5' incorporates:
   *  Constant: '<S85>/Demand_Torquee_And_C'
   *  DataTypeConversion: '<S85>/BitCov'
   *  S-Function (sfix_bitop): '<S85>/Demand_Torquee_And'
   */
  text28_B.or5_c = (uint8_T)(rtb_MotorTorque_L & 255U);

  /* S-Function (sfix_bitop): '<S82>/or6' incorporates:
   *  Constant: '<S85>/Demand_Torqueeoutput6_C'
   *  DataTypeConversion: '<S85>/Demand_TorqueeCOV'
   *  Product: '<S85>/Demand_Torquee_D1'
   */
  text28_B.or6_p = (uint8_T)((real_T)rtb_MotorTorque_L / 256.0);

  /* S-Function (sfix_bitop): '<S82>/or7' */
  text28_B.or7_a = 152U;

  /* S-Function (sfix_bitop): '<S82>/or8' */
  text28_B.or8_l = 58U;

  /* S-Function (ec55xx_cantransmitslb): '<S79>/CANTransmit' */

  /*Transmit CAN message*/
  {
    uint8 CAN1BUF8TX[8];
    uint8 can1buf8looptx= 0;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or1_a;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or2_f;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or3_k;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or4_m;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or5_c;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or6_p;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or7_a;
    can1buf8looptx++;
    CAN1BUF8TX[can1buf8looptx]= text28_B.or8_l;
    can1buf8looptx++;
    CAN_ok= ec_can_transmit(1, 8, 1, 218040815U, 8, CAN1BUF8TX);
  }

  /* If: '<S94>/If' incorporates:
   *  DataTypeConversion: '<S94>/Data Type Conversion1'
   */
  if (CAN_ok < 2) {
    /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S96>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge_n3);

    /* End of Outputs for SubSystem: '<S94>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S94>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S95>/Action Port'
     */
    /* DataTypeConversion: '<S95>/Data Type Conversion2' incorporates:
     *  Constant: '<S95>/Constant1'
     */
    rtb_Merge_n3 = 0.0;

    /* End of Outputs for SubSystem: '<S94>/If Action Subsystem1' */
  }

  /* End of If: '<S94>/If' */

  /* If: '<S171>/If' incorporates:
   *  Constant: '<S199>/Constant'
   *  Constant: '<S200>/Constant'
   */
  if ((jiaodu_2222 > 800) && (jiaodu_11111 > 600) && (jiaodu_2222 < 2900) &&
      (jiaodu_11111 < 2700)) {
    /* Outputs for IfAction SubSystem: '<S171>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S200>/Action Port'
     */
    app_scs = 1.0;

    /* End of Outputs for SubSystem: '<S171>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S171>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S200>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S171>/If Action Subsystem' incorporates:
     *  ActionPort: '<S199>/Action Port'
     */
    app_scs = 0.0;

    /* End of Outputs for SubSystem: '<S171>/If Action Subsystem' */
    /* End of Outputs for SubSystem: '<S171>/If Action Subsystem1' */
  }

  /* End of If: '<S171>/If' */

  /* DataTypeConversion: '<S81>/Data Type Conversion2' incorporates:
   *  Logic: '<S81>/Logical Operator'
   */
  anquan_out = (uint32_T)((rtb_Merge_n3 != 0.0) && (app_scs != 0.0));

  /* S-Function (ec55xx_pdpslb): '<S81>/安全出' */

  /* Power driver PWM output for channel 16 */
  ec_pwm_output(16,1U,anquan_out);

  /* UnitDelay: '<S143>/Unit Delay' */
  rtb_Product_e = text28_DW.UnitDelay_DSTATE_o;

  /* If: '<S135>/If' */
  if (enable_sign > 0.0) {
    /* Outputs for IfAction SubSystem: '<S135>/If Action Subsystem' incorporates:
     *  ActionPort: '<S141>/Action Port'
     */
    text28_IfActionSubsystem(&rtb_Merge_d);

    /* End of Outputs for SubSystem: '<S135>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S135>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S142>/Action Port'
     */
    text28_u(&rtb_Merge_d);

    /* End of Outputs for SubSystem: '<S135>/If Action Subsystem1' */
  }

  /* End of If: '<S135>/If' */

  /* Product: '<S143>/Product' incorporates:
   *  Sum: '<S143>/Sum'
   */
  rtb_Product_j = (rtb_Merge_d + rtb_Product_e) * (real_T)aqhl;

  /* If: '<S143>/If' */
  if ((rtb_Product_j > 0.0) && (rtb_Product_j < 150.0)) {
    /* Outputs for IfAction SubSystem: '<S143>/If Action Subsystem' incorporates:
     *  ActionPort: '<S144>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge_n4);

    /* End of Outputs for SubSystem: '<S143>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S143>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S145>/Action Port'
     */
    text28_u(&rtb_Merge_n4);

    /* End of Outputs for SubSystem: '<S143>/If Action Subsystem1' */
  }

  /* End of If: '<S143>/If' */

  /* DataTypeConversion: '<S143>/Data Type Conversion1' */
  text28_B.DataTypeConversion1_j = (uint32_T)rtb_Merge_n4;

  /* S-Function (ec55xx_pdpslb): '<S143>/蜂鸣器' */

  /* Power driver PWM output for channel 14 */
  ec_pwm_output(14,text28_ConstB.DataTypeConversion,
                text28_B.DataTypeConversion1_j);

  /* S-Function (ec55xx_ffrslb): '<S146>/左前' */

  /* Read the last frequency */
  text28_B.u= ec_etpu_get_ppa_freq(84);

  /* DataTypeConversion: '<S146>/Data Type Conversion2' */
  rtb_Product_e = text28_B.u;

  /* S-Function (ec55xx_ffrslb): '<S146>/右前' */

  /* Read the last frequency */
  text28_B.u_ji= ec_etpu_get_ppa_freq(89);

  /* Gain: '<S146>/Gain1' */
  left_speed = 0.105 * rtb_Product_e;

  /* Gain: '<S146>/Gain3' incorporates:
   *  DataTypeConversion: '<S146>/Data Type Conversion3'
   */
  right_speed = 0.105 * (real_T)text28_B.u_ji;

  /* Gain: '<S146>/Gain4' incorporates:
   *  Sum: '<S146>/Sum'
   */
  car_speed = (left_speed + right_speed) * 0.5;

  /* Sum: '<S101>/Sum' incorporates:
   *  Constant: '<S101>/Constant1'
   */
  rtb_Product_e = car_speed + 1.0;

  /* S-Function (ec55xx_canreceiveslb): '<S102>/CANReceive' */

  /* Receive CAN message */
  {
    uint8 CAN1BUF7RX[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

    uint8 can1buf7looprx= 0;
    text28_B.CANReceive_o3_c= 218038281;
    text28_B.CANReceive_o5_i= 8;
    text28_B.CANReceive_o2_b= ec_can_receive(1,7, CAN1BUF7RX);
    text28_B.CANReceive_o4_m[0]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[1]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[2]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[3]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[4]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[5]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[6]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
    text28_B.CANReceive_o4_m[7]= CAN1BUF7RX[can1buf7looprx];
    can1buf7looprx++;
  }

  /* Call the system: <S102>/Function-Call Subsystem4 */

  /* Output and update for function-call system: '<S102>/Function-Call Subsystem4' */

  /* Inport: '<S152>/In2' */
  text28_B.In2[0] = text28_B.CANReceive_o4_m[0];
  text28_B.In2[1] = text28_B.CANReceive_o4_m[1];
  text28_B.In2[2] = text28_B.CANReceive_o4_m[2];
  text28_B.In2[3] = text28_B.CANReceive_o4_m[3];
  text28_B.In2[4] = text28_B.CANReceive_o4_m[4];
  text28_B.In2[5] = text28_B.CANReceive_o4_m[5];
  text28_B.In2[6] = text28_B.CANReceive_o4_m[6];
  text28_B.In2[7] = text28_B.CANReceive_o4_m[7];

  /* S-Function (sfix_bitop): '<S158>/Motor_Speed_L' incorporates:
   *  Constant: '<S158>/Motor_Speedinput2_C'
   *  Product: '<S158>/Motor_Speedinput2_P'
   *  Sum: '<S158>/Motor_Speedinput2_Ad'
   */
  rtb_MotorTorque_L = (text28_B.In2[1] << 8) + text28_B.In2[0];

  /* Switch: '<S158>/Motor_SpeedSW' incorporates:
   *  Constant: '<S158>/Motor_Speedinput2_C'
   *  DataTypeConversion: '<S158>/Motor_Speedcv'
   *  Product: '<S158>/Motor_Speedinput2_P'
   *  RelationalOperator: '<S158>/Motor_SpeedROP'
   *  Sum: '<S158>/Motor_Speedinput2_Ad'
   *  Sum: '<S158>/Motor_Speedsubcon'
   *  UnaryMinus: '<S158>/Motor_SpeedMinus'
   */
  if ((text28_B.In2[1] << 8) + text28_B.In2[0] >= 32768) {
    tmp = -(65536.0F - (real32_T)rtb_MotorTorque_L);
  } else {
    tmp = (real32_T)rtb_MotorTorque_L;
  }

  /* End of Switch: '<S158>/Motor_SpeedSW' */

  /* Sum: '<S158>/Motor_Speed_Ad' incorporates:
   *  Constant: '<S158>/Motor_Speed_O'
   */
  rtb_MotorTorque_sat = tmp + -15000.0F;

  /* Saturate: '<S158>/Motor_Speed_sat' incorporates:
   *  Constant: '<S158>/Motor_Speed_O'
   *  Sum: '<S158>/Motor_Speed_Ad'
   */
  if (tmp + -15000.0F > 15000.0F) {
    rtb_MotorTorque_sat = 15000.0F;
  } else {
    if (tmp + -15000.0F < -15000.0F) {
      rtb_MotorTorque_sat = -15000.0F;
    }
  }

  /* End of Saturate: '<S158>/Motor_Speed_sat' */

  /* Gain: '<S154>/Gain' incorporates:
   *  DataTypeConversion: '<S154>/Data Type Conversion'
   */
  motor_speed = -(real_T)rtb_MotorTorque_sat;

  /* Product: '<S155>/Divide1' incorporates:
   *  Constant: '<S155>/Constant'
   *  Constant: '<S155>/Constant1'
   *  Constant: '<S155>/Constant2'
   *  Constant: '<S155>/Constant3'
   *  Product: '<S155>/Divide'
   *  Product: '<S155>/Product'
   */
  rear_speed = -(motor_speed * 0.377 * 0.234 / 4.07 / 3.6);

  /* Product: '<S150>/Divide' incorporates:
   *  Constant: '<S101>/Constant2'
   *  Sum: '<S101>/Sum1'
   *  Sum: '<S150>/Sum'
   */
  rtb_Product_e = ((rear_speed + 1.0) - rtb_Product_e) / (rear_speed + 1.0);

  /* Saturate: '<S150>/Saturation' */
  if (rtb_Product_e > 1.0) {
    huazhuan = 1.0;
  } else if (rtb_Product_e < 0.0) {
    huazhuan = 0.0;
  } else {
    huazhuan = rtb_Product_e;
  }

  /* End of Saturate: '<S150>/Saturation' */

  /* S-Function (sfix_bitop): '<S158>/MotorTorque_L' incorporates:
   *  Constant: '<S158>/MotorTorqueinput4_C'
   *  Product: '<S158>/MotorTorqueinput4_P'
   *  Sum: '<S158>/MotorTorqueinput4_Ad'
   */
  rtb_MotorTorque_L = (text28_B.In2[3] << 8) + text28_B.In2[2];

  /* Switch: '<S158>/MotorTorqueSW' incorporates:
   *  Constant: '<S158>/MotorTorqueinput4_C'
   *  DataTypeConversion: '<S158>/MotorTorquecv'
   *  Product: '<S158>/MotorTorqueinput4_P'
   *  RelationalOperator: '<S158>/MotorTorqueROP'
   *  Sum: '<S158>/MotorTorqueinput4_Ad'
   *  Sum: '<S158>/MotorTorquesubcon'
   *  UnaryMinus: '<S158>/MotorTorqueMinus'
   */
  if ((text28_B.In2[3] << 8) + text28_B.In2[2] >= 32768) {
    tmp = -(65536.0F - (real32_T)rtb_MotorTorque_L);
  } else {
    tmp = (real32_T)rtb_MotorTorque_L;
  }

  /* End of Switch: '<S158>/MotorTorqueSW' */

  /* Sum: '<S158>/MotorTorque_Ad' incorporates:
   *  Constant: '<S158>/MotorTorque_O'
   */
  rtb_MotorTorque_sat = tmp + -5000.0F;

  /* Saturate: '<S158>/MotorTorque_sat' incorporates:
   *  Constant: '<S158>/MotorTorque_O'
   *  Sum: '<S158>/MotorTorque_Ad'
   */
  if (tmp + -5000.0F > 5000.0F) {
    rtb_MotorTorque_sat = 5000.0F;
  } else {
    if (tmp + -5000.0F < -5000.0F) {
      rtb_MotorTorque_sat = -5000.0F;
    }
  }

  /* End of Saturate: '<S158>/MotorTorque_sat' */

  /* Gain: '<S154>/Gain1' incorporates:
   *  DataTypeConversion: '<S154>/Data Type Conversion1'
   */
  motor_torque = -(real_T)rtb_MotorTorque_sat;

  /* S-Function (ec55xx_wdgfeedslb): '<S6>/WDGFeed' */
  ec_wdg_feed();

  /* Update for UnitDelay: '<S99>/Unit Delay' */
  text28_DW.UnitDelay_DSTATE = rtb_Product;

  /* Update for UnitDelay: '<S97>/Unit Delay' */
  text28_DW.UnitDelay_DSTATE_l = apps_rule;

  /* Update for UnitDelay: '<S143>/Unit Delay' */
  text28_DW.UnitDelay_DSTATE_o = rtb_Product_j;

  /* S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem2'
   */
  /* S-Function (sfix_bitop): '<S7>/or1' */
  text28_B.or1_n = 1U;

  /* S-Function (sfix_bitop): '<S7>/or2' */
  text28_B.or2_b = 1U;

  /* S-Function (sfix_bitop): '<S7>/or3' incorporates:
   *  Constant: '<S9>/Constant3'
   */
  text28_B.or3_h = 0U;

  /* S-Function (sfix_bitop): '<S7>/or4' incorporates:
   *  Constant: '<S9>/Constant4'
   */
  text28_B.or4_k = 0U;

  /* S-Function (sfix_bitop): '<S7>/or5' incorporates:
   *  Constant: '<S9>/Constant5'
   */
  text28_B.or5_m = 0U;

  /* S-Function (sfix_bitop): '<S7>/or6' incorporates:
   *  Constant: '<S9>/Constant6'
   */
  text28_B.or6_n = 0U;

  /* S-Function (sfix_bitop): '<S7>/or7' incorporates:
   *  Constant: '<S9>/Constant7'
   */
  text28_B.or7_l = 0U;

  /* S-Function (sfix_bitop): '<S7>/or8' incorporates:
   *  Constant: '<S9>/Constant8'
   */
  text28_B.or8_b = 0U;

  /* S-Function (ec55xx_cantransmitslb): '<S1>/CANTransmit' */

  /*Transmit CAN message*/
  {
    uint8 CAN0BUF8TX[8];
    uint8 can0buf8looptx= 0;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or1_n;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or2_b;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or3_h;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or4_k;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or5_m;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or6_n;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or7_l;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or8_b;
    can0buf8looptx++;
    text28_B.CANTransmit_pg= ec_can_transmit(0, 8, 0, 996U, 8, CAN0BUF8TX);
  }

  /* S-Function (fcncallgen): '<S57>/10ms' incorporates:
   *  SubSystem: '<S57>/daq10ms'
   */

  /* S-Function (ec55xx_ccpslb1): '<S69>/CCPDAQ' */
  ccpDaq(1);

  /* S-Function (fcncallgen): '<S59>/10ms' incorporates:
   *  SubSystem: '<S59>/10mstask'
   */

  /* S-Function (ec55xx_pdsdslb1): '<S73>/PDSD' */
  ec_tle6232_diag();
}

/* Model step function for TID4 */
void text28_step4(void)                /* Sample time: [0.05s, 0.0s] */
{
  int32_T rtb_MCU_temperature_Ad;

  /* S-Function (fcncallgen): '<Root>/50ms2' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem7'
   */

  /* S-Function (ec55xx_canreceiveslb): '<S4>/MCU STATUS 2' */

  /* Receive CAN message */
  {
    uint8 CAN1BUF0RX[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

    uint8 can1buf0looprx= 0;
    text28_B.MCUSTATUS2_o3= 218038537;
    text28_B.MCUSTATUS2_o5= 8;
    text28_B.MCUSTATUS2_o2= ec_can_receive(1,0, CAN1BUF0RX);
    text28_B.MCUSTATUS2_o4[0]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[1]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[2]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[3]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[4]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[5]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[6]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
    text28_B.MCUSTATUS2_o4[7]= CAN1BUF0RX[can1buf0looprx];
    can1buf0looprx++;
  }

  /* Call the system: <S4>/Function-Call Subsystem2 */

  /* Output and update for function-call system: '<S4>/Function-Call Subsystem2' */

  /* Inport: '<S44>/In1' */
  text28_B.In1[0] = text28_B.MCUSTATUS2_o4[0];
  text28_B.In1[1] = text28_B.MCUSTATUS2_o4[1];
  text28_B.In1[2] = text28_B.MCUSTATUS2_o4[2];
  text28_B.In1[3] = text28_B.MCUSTATUS2_o4[3];
  text28_B.In1[4] = text28_B.MCUSTATUS2_o4[4];
  text28_B.In1[5] = text28_B.MCUSTATUS2_o4[5];
  text28_B.In1[6] = text28_B.MCUSTATUS2_o4[6];
  text28_B.In1[7] = text28_B.MCUSTATUS2_o4[7];

  /* Switch: '<S47>/Motor_TemperatureSW' incorporates:
   *  DataTypeConversion: '<S47>/Motor_Temperature_Convert'
   *  RelationalOperator: '<S47>/Motor_TemperatureROP'
   *  Sum: '<S47>/Motor_Temperaturesubcon'
   *  UnaryMinus: '<S47>/Motor_TemperatureMinus'
   */
  if (text28_B.In1[0] >= 128) {
    rtb_MCU_temperature_Ad = text28_B.In1[0] - 256;
  } else {
    rtb_MCU_temperature_Ad = text28_B.In1[0];
  }

  /* End of Switch: '<S47>/Motor_TemperatureSW' */

  /* Sum: '<S47>/Motor_Temperature_Ad' incorporates:
   *  Constant: '<S47>/Motor_Temperature_O'
   */
  rtb_MCU_temperature_Ad += -40;

  /* Saturate: '<S47>/Motor_Temperature_sat' */
  if (rtb_MCU_temperature_Ad < -40.0F) {
    MotorTemp = -40.0F;
  } else {
    MotorTemp = (real32_T)rtb_MCU_temperature_Ad;
  }

  /* End of Saturate: '<S47>/Motor_Temperature_sat' */

  /* Switch: '<S47>/MCU_temperatureSW' incorporates:
   *  DataTypeConversion: '<S47>/MCU_temperature_Convert'
   *  RelationalOperator: '<S47>/MCU_temperatureROP'
   *  Sum: '<S47>/MCU_temperaturesubcon'
   *  UnaryMinus: '<S47>/MCU_temperatureMinus'
   */
  if (text28_B.In1[1] >= 128) {
    rtb_MCU_temperature_Ad = text28_B.In1[1] - 256;
  } else {
    rtb_MCU_temperature_Ad = text28_B.In1[1];
  }

  /* End of Switch: '<S47>/MCU_temperatureSW' */

  /* Sum: '<S47>/MCU_temperature_Ad' incorporates:
   *  Constant: '<S47>/MCU_temperature_O'
   */
  rtb_MCU_temperature_Ad += -40;

  /* Saturate: '<S47>/MCU_temperature_sat' */
  if (rtb_MCU_temperature_Ad < -40.0F) {
    McuTemp = -40.0F;
  } else {
    McuTemp = (real32_T)rtb_MCU_temperature_Ad;
  }

  /* End of Saturate: '<S47>/MCU_temperature_sat' */

  /* Logic: '<S4>/Logical Operator' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Constant: '<S4>/Constant2'
   *  RelationalOperator: '<S4>/Relational Operator'
   *  RelationalOperator: '<S4>/Relational Operator1'
   */
  FAN_sign = ((MotorTemp >= 50.0F) || (McuTemp >= 50.0F));

  /* DataTypeConversion: '<S4>/Data Type Conversion1' */
  text28_B.DataTypeConversion1 = (uint32_T)FAN_sign;

  /* S-Function (ec55xx_pdpslb): '<S4>/PowerDriverPWM' */

  /* Power driver PWM output for channel 18 */
  ec_pwm_output(18,text28_ConstB.DataTypeConversion2,
                text28_B.DataTypeConversion1);

  /* S-Function (fcncallgen): '<S57>/50ms' incorporates:
   *  SubSystem: '<S57>/daq50ms'
   */

  /* S-Function (ec55xx_ccpslb1): '<S70>/CCPDAQ' */
  ccpDaq(2);
}

/* Model step function for TID5 */
void text28_step5(void)                /* Sample time: [0.1s, 0.0s] */
{
  /* S-Function (fcncallgen): '<S57>/100ms' incorporates:
   *  SubSystem: '<S57>/daq100ms'
   */

  /* S-Function (ec55xx_ccpslb1): '<S68>/CCPDAQ' */
  ccpDaq(3);
}

/* Model step function for TID6 */
void text28_step6(void)                /* Sample time: [0.2s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_Merge;
  real_T rtb_Merge_p;
  uint32_T rtb_BatVoltage_Convert;
  real32_T rtb_BatVoltage_Ad;
  real32_T u0;

  /* S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem4'
   */

  /* S-Function (ec55xx_canreceiveslb): '<S3>/CAN检测' */

  /* Receive CAN message */
  {
    uint8 CAN0BUF0RX[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

    uint8 can0buf0looprx= 0;
    text28_B.CAN_o3= 408961267;
    text28_B.CAN_o5= 8;
    bms_canok= ec_can_receive(0,0, CAN0BUF0RX);
    text28_B.CAN_o4[0]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[1]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[2]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[3]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[4]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[5]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[6]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
    text28_B.CAN_o4[7]= CAN0BUF0RX[can0buf0looprx];
    can0buf0looprx++;
  }

  /* Call the system: <S3>/Function-Call Subsystem4 */

  /* Output and update for function-call system: '<S3>/Function-Call Subsystem4' */

  /* Inport: '<S16>/In3' */
  text28_B.In3[0] = text28_B.CAN_o4[0];
  text28_B.In3[1] = text28_B.CAN_o4[1];
  text28_B.In3[2] = text28_B.CAN_o4[2];
  text28_B.In3[3] = text28_B.CAN_o4[3];
  text28_B.In3[4] = text28_B.CAN_o4[4];
  text28_B.In3[5] = text28_B.CAN_o4[5];
  text28_B.In3[6] = text28_B.CAN_o4[6];
  text28_B.In3[7] = text28_B.CAN_o4[7];

  /* If: '<S20>/If1' */
  if (bms_canok < 1) {
    /* Outputs for IfAction SubSystem: '<S20>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S36>/Action Port'
     */
    /* SignalConversion: '<S36>/OutportBufferForOut1' incorporates:
     *  Constant: '<S36>/Constant2'
     */
    bms_sign1 = 0.0;

    /* End of Outputs for SubSystem: '<S20>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S20>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S37>/Action Port'
     */
    text28_IfActionSubsystem((&(bms_sign1)));

    /* End of Outputs for SubSystem: '<S20>/If Action Subsystem3' */
  }

  /* End of If: '<S20>/If1' */

  /* S-Function (sfix_bitop): '<S24>/BatAlmLv_L' incorporates:
   *  DataTypeConversion: '<S24>/BatAlmLv_Convert'
   */
  rtb_BatVoltage_Convert = text28_B.In3[6] & 15U;

  /* Switch: '<S24>/BatAlmLvSW' incorporates:
   *  DataTypeConversion: '<S24>/BatAlmLv_Convert'
   *  DataTypeConversion: '<S24>/BatAlmLvcv'
   *  RelationalOperator: '<S24>/BatAlmLvROP'
   *  S-Function (sfix_bitop): '<S24>/BatAlmLv_L'
   *  Sum: '<S24>/BatAlmLvsubcon'
   *  UnaryMinus: '<S24>/BatAlmLvMinus'
   */
  if ((int32_T)(text28_B.In3[6] & 15U) >= 8) {
    rtb_BatVoltage_Ad = -(16.0F - (real32_T)rtb_BatVoltage_Convert);
  } else {
    rtb_BatVoltage_Ad = (real32_T)rtb_BatVoltage_Convert;
  }

  /* End of Switch: '<S24>/BatAlmLvSW' */

  /* Saturate: '<S24>/BatAlmLv_sat' */
  if (rtb_BatVoltage_Ad > 4.0F) {
    baojing = 4.0F;
  } else if (rtb_BatVoltage_Ad < 0.0F) {
    baojing = 0.0F;
  } else {
    baojing = rtb_BatVoltage_Ad;
  }

  /* End of Saturate: '<S24>/BatAlmLv_sat' */

  /* If: '<S21>/If' */
  if (baojing == 1.0F) {
    /* Outputs for IfAction SubSystem: '<S21>/If Action Subsystem' incorporates:
     *  ActionPort: '<S39>/Action Port'
     */
    text28_u(&rtb_Merge);

    /* End of Outputs for SubSystem: '<S21>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S21>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S40>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge);

    /* End of Outputs for SubSystem: '<S21>/If Action Subsystem1' */
  }

  /* End of If: '<S21>/If' */

  /* ArithShift: '<S24>/BatState_S' incorporates:
   *  DataTypeConversion: '<S24>/BatState_Convert'
   *  S-Function (sfix_bitop): '<S24>/BatState_L'
   */
  rtb_BatVoltage_Convert = (text28_B.In3[6] & 240U) >> 4;

  /* Switch: '<S24>/BatStateSW' incorporates:
   *  ArithShift: '<S24>/BatState_S'
   *  DataTypeConversion: '<S24>/BatState_Convert'
   *  DataTypeConversion: '<S24>/BatStatecv'
   *  RelationalOperator: '<S24>/BatStateROP'
   *  S-Function (sfix_bitop): '<S24>/BatState_L'
   *  Sum: '<S24>/BatStatesubcon'
   *  UnaryMinus: '<S24>/BatStateMinus'
   */
  if ((int32_T)((text28_B.In3[6] & 240U) >> 4) >= 8) {
    rtb_BatVoltage_Ad = -(16.0F - (real32_T)rtb_BatVoltage_Convert);
  } else {
    rtb_BatVoltage_Ad = (real32_T)rtb_BatVoltage_Convert;
  }

  /* End of Switch: '<S24>/BatStateSW' */

  /* Saturate: '<S24>/BatState_sat' */
  if (rtb_BatVoltage_Ad > 7.0F) {
    zhuangtai = 7.0F;
  } else if (rtb_BatVoltage_Ad < 1.0F) {
    zhuangtai = 1.0F;
  } else {
    zhuangtai = rtb_BatVoltage_Ad;
  }

  /* End of Saturate: '<S24>/BatState_sat' */

  /* If: '<S23>/If' */
  if (zhuangtai == 7.0F) {
    /* Outputs for IfAction SubSystem: '<S23>/If Action Subsystem' incorporates:
     *  ActionPort: '<S42>/Action Port'
     */
    text28_u(&rtb_Merge_p);

    /* End of Outputs for SubSystem: '<S23>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S23>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S43>/Action Port'
     */
    text28_IfActionSubsystem2(&rtb_Merge_p);

    /* End of Outputs for SubSystem: '<S23>/If Action Subsystem1' */
  }

  /* End of If: '<S23>/If' */

  /* Logic: '<S3>/Logical Operator' */
  bms_sign = ((rtb_Merge_p != 0.0) && (rtb_Merge != 0.0) && (bms_sign1 != 0.0));

  /* S-Function (sfix_bitop): '<S24>/BatCurrent_L' incorporates:
   *  Constant: '<S24>/BatCurrentinput3_C'
   *  DataTypeConversion: '<S24>/BatCurrent_Convert'
   *  Product: '<S24>/BatCurrentinput3_P'
   *  Sum: '<S24>/BatCurrentinput3_Ad'
   */
  rtb_BatVoltage_Convert = (uint32_T)((text28_B.In3[2] << 8) + text28_B.In3[3]);

  /* Switch: '<S24>/BatCurrentSW' incorporates:
   *  Constant: '<S24>/BatCurrentinput3_C'
   *  DataTypeConversion: '<S24>/BatCurrentcv'
   *  Product: '<S24>/BatCurrentinput3_P'
   *  RelationalOperator: '<S24>/BatCurrentROP'
   *  Sum: '<S24>/BatCurrentinput3_Ad'
   *  Sum: '<S24>/BatCurrentsubcon'
   *  UnaryMinus: '<S24>/BatCurrentMinus'
   */
  if ((text28_B.In3[2] << 8) + text28_B.In3[3] >= 32768) {
    rtb_BatVoltage_Ad = -(65536.0F - (real32_T)rtb_BatVoltage_Convert);
  } else {
    rtb_BatVoltage_Ad = (real32_T)rtb_BatVoltage_Convert;
  }

  /* End of Switch: '<S24>/BatCurrentSW' */

  /* Sum: '<S24>/BatCurrent_Ad' incorporates:
   *  Constant: '<S24>/BatCurrent_O'
   *  Gain: '<S24>/BatCurrent_F'
   */
  u0 = 0.1F * rtb_BatVoltage_Ad + -1000.0F;

  /* Switch: '<S24>/BatSocSW' incorporates:
   *  DataTypeConversion: '<S24>/BatSoc_Convert'
   *  DataTypeConversion: '<S24>/BatSoccv'
   *  RelationalOperator: '<S24>/BatSocROP'
   *  Sum: '<S24>/BatSocsubcon'
   *  UnaryMinus: '<S24>/BatSocMinus'
   */
  if (text28_B.In3[4] >= 128) {
    rtb_BatVoltage_Ad = -(256.0F - (real32_T)text28_B.In3[4]);
  } else {
    rtb_BatVoltage_Ad = text28_B.In3[4];
  }

  /* End of Switch: '<S24>/BatSocSW' */

  /* Saturate: '<S24>/BatSoc_sat' */
  if (rtb_BatVoltage_Ad > 100.0F) {
    soc = 100.0F;
  } else if (rtb_BatVoltage_Ad < 0.0F) {
    soc = 0.0F;
  } else {
    soc = rtb_BatVoltage_Ad;
  }

  /* End of Saturate: '<S24>/BatSoc_sat' */

  /* S-Function (sfix_bitop): '<S24>/BatVoltage_L' incorporates:
   *  Constant: '<S24>/BatVoltageinput1_C'
   *  DataTypeConversion: '<S24>/BatVoltage_Convert'
   *  Product: '<S24>/BatVoltageinput1_P'
   *  Sum: '<S24>/BatVoltageinput1_Ad'
   */
  rtb_BatVoltage_Convert = (uint32_T)((text28_B.In3[0] << 8) + text28_B.In3[1]);

  /* Switch: '<S24>/BatVoltageSW' incorporates:
   *  Constant: '<S24>/BatVoltageinput1_C'
   *  DataTypeConversion: '<S24>/BatVoltagecv'
   *  Product: '<S24>/BatVoltageinput1_P'
   *  RelationalOperator: '<S24>/BatVoltageROP'
   *  Sum: '<S24>/BatVoltageinput1_Ad'
   *  Sum: '<S24>/BatVoltagesubcon'
   *  UnaryMinus: '<S24>/BatVoltageMinus'
   */
  if ((text28_B.In3[0] << 8) + text28_B.In3[1] >= 32768) {
    rtb_BatVoltage_Ad = -(65536.0F - (real32_T)rtb_BatVoltage_Convert);
  } else {
    rtb_BatVoltage_Ad = (real32_T)rtb_BatVoltage_Convert;
  }

  /* End of Switch: '<S24>/BatVoltageSW' */

  /* Gain: '<S24>/BatVoltage_F' */
  rtb_BatVoltage_Ad *= 0.1F;

  /* Saturate: '<S24>/BatVoltage_sat' */
  if (rtb_BatVoltage_Ad > 900.0F) {
    dianya = 900.0F;
  } else if (rtb_BatVoltage_Ad < 0.0F) {
    dianya = 0.0F;
  } else {
    dianya = rtb_BatVoltage_Ad;
  }

  /* End of Saturate: '<S24>/BatVoltage_sat' */

  /* Sum: '<S22>/Add' incorporates:
   *  Constant: '<S22>/Constant1'
   *  UnitDelay: '<S22>/Unit Delay'
   */
  rtb_BatVoltage_Convert = 1U + text28_DW.UnitDelay_DSTATE_j;

  /* Switch: '<S22>/Switch' incorporates:
   *  Constant: '<S22>/Constant4'
   *  Constant: '<S22>/Constant5'
   */
  if (rtb_BatVoltage_Convert > 5U) {
    keshi = 1U;
  } else {
    keshi = 0U;
  }

  /* End of Switch: '<S22>/Switch' */

  /* S-Function (ec55xx_pdpslb): '<S22>/断can线亮灯3' */

  /* Power driver PWM output for channel 0 */
  ec_pwm_output(0,text28_ConstB.DataTypeConversion5,keshi);

  /* Update for UnitDelay: '<S22>/Unit Delay' */
  text28_DW.UnitDelay_DSTATE_j = rtb_BatVoltage_Convert;

  /* S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem3'
   */
  /* Saturate: '<S11>/BatAlmLv_sat' */
  if (zhuangtai > 4.0F) {
    rtb_BatVoltage_Ad = 4.0F;
  } else if (zhuangtai < 0.0F) {
    rtb_BatVoltage_Ad = 0.0F;
  } else {
    rtb_BatVoltage_Ad = zhuangtai;
  }

  /* S-Function (sfix_bitop): '<S10>/or1' incorporates:
   *  DataTypeConversion: '<S11>/BatAlmLv_Convert'
   *  DataTypeConversion: '<S11>/BatAlmLv_Convert1'
   *  Rounding: '<S11>/BatAlmLvRon'
   *  S-Function (sfix_bitop): '<S11>/BatAlmLv_L'
   *  Saturate: '<S11>/BatAlmLv_sat'
   */
  text28_B.or1 = (uint8_T)((uint32_T)rt_roundf_snf(rtb_BatVoltage_Ad) & 255U);

  /* Saturate: '<S13>/BatSoc_sat' */
  if (dianya > 100.0F) {
    rtb_BatVoltage_Ad = 100.0F;
  } else if (dianya < 0.0F) {
    rtb_BatVoltage_Ad = 0.0F;
  } else {
    rtb_BatVoltage_Ad = dianya;
  }

  /* S-Function (sfix_bitop): '<S10>/or2' incorporates:
   *  DataTypeConversion: '<S13>/BatSoc_Convert'
   *  DataTypeConversion: '<S13>/BatSoc_Convert1'
   *  Rounding: '<S13>/BatSocRon'
   *  S-Function (sfix_bitop): '<S13>/BatSoc_L'
   *  Saturate: '<S13>/BatSoc_sat'
   */
  text28_B.or2 = (uint8_T)((uint32_T)rt_roundf_snf(rtb_BatVoltage_Ad) & 255U);

  /* Saturate: '<S14>/BatState_sat' */
  if (baojing > 7.0F) {
    rtb_BatVoltage_Ad = 7.0F;
  } else if (baojing < 1.0F) {
    rtb_BatVoltage_Ad = 1.0F;
  } else {
    rtb_BatVoltage_Ad = baojing;
  }

  /* S-Function (sfix_bitop): '<S10>/or3' incorporates:
   *  DataTypeConversion: '<S14>/BatState_Convert'
   *  DataTypeConversion: '<S14>/BatState_Convert1'
   *  Rounding: '<S14>/BatStateRon'
   *  S-Function (sfix_bitop): '<S14>/BatState_L'
   *  Saturate: '<S14>/BatState_sat'
   */
  text28_B.or3 = (uint8_T)((uint32_T)rt_roundf_snf(rtb_BatVoltage_Ad) & 255U);

  /* Saturate: '<S15>/BatVoltage_sat' */
  if (soc > 900.0F) {
    rtb_BatVoltage_Ad = 900.0F;
  } else if (soc < 0.0F) {
    rtb_BatVoltage_Ad = 0.0F;
  } else {
    rtb_BatVoltage_Ad = soc;
  }

  /* S-Function (sfix_bitop): '<S15>/BatVoltage_L' incorporates:
   *  Constant: '<S15>/BatVoltage_F'
   *  DataTypeConversion: '<S15>/BatVoltage_Convert'
   *  Product: '<S15>/BatVoltage_D'
   *  Rounding: '<S15>/BatVoltageRon'
   *  Saturate: '<S15>/BatVoltage_sat'
   */
  rtb_BatVoltage_Convert = (uint32_T)rt_roundf_snf(rtb_BatVoltage_Ad / 0.1F) &
    65535U;

  /* S-Function (sfix_bitop): '<S10>/or4' incorporates:
   *  Constant: '<S15>/BatVoltageoutput4_C'
   *  DataTypeConversion: '<S15>/BatVoltageCOV'
   *  Product: '<S15>/BatVoltage_D1'
   */
  text28_B.or4 = (uint8_T)((real_T)rtb_BatVoltage_Convert / 256.0);

  /* S-Function (sfix_bitop): '<S10>/or5' incorporates:
   *  Constant: '<S15>/BatVoltage_And_C'
   *  DataTypeConversion: '<S15>/BatVoltageBitCov'
   *  S-Function (sfix_bitop): '<S15>/BatVoltage_And'
   */
  text28_B.or5 = (uint8_T)(rtb_BatVoltage_Convert & 255U);

  /* S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem4'
   */
  /* Saturate: '<S24>/BatCurrent_sat' */
  if (u0 > 1000.0F) {
    u0 = 1000.0F;
  } else {
    if (u0 < -1000.0F) {
      u0 = -1000.0F;
    }
  }

  /* End of Saturate: '<S24>/BatCurrent_sat' */

  /* S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  SubSystem: '<Root>/Function-Call Subsystem3'
   */
  /* Rounding: '<S12>/BatCurrentRon' incorporates:
   *  Constant: '<S12>/BatCurrent_F'
   *  Constant: '<S12>/BatCurrent_O'
   *  Product: '<S12>/BatCurrent_D'
   *  Saturate: '<S12>/BatCurrent_sat'
   *  Sum: '<S12>/BatCurrent_st'
   */
  rtb_BatVoltage_Ad = rt_roundf_snf((u0 - 0.1F) / -1000.0F);

  /* Switch: '<S12>/BatCurrentSW' incorporates:
   *  RelationalOperator: '<S12>/BatCurrentROP'
   *  Sum: '<S12>/BatCurrentsubcon'
   */
  if (rtb_BatVoltage_Ad < 0.0F) {
    rtb_BatVoltage_Ad = 65535.0F;
  }

  /* End of Switch: '<S12>/BatCurrentSW' */

  /* S-Function (sfix_bitop): '<S10>/or6' incorporates:
   *  Constant: '<S12>/BatCurrentoutput6_C'
   *  DataTypeConversion: '<S12>/BatCurrentCOV'
   *  DataTypeConversion: '<S12>/BatCurrent_Convert'
   *  Product: '<S12>/BatCurrent_D1'
   */
  text28_B.or6 = (uint8_T)((real_T)(uint32_T)rtb_BatVoltage_Ad / 256.0);

  /* S-Function (sfix_bitop): '<S10>/or7' incorporates:
   *  Constant: '<S12>/BatCurrent_And_C'
   *  DataTypeConversion: '<S12>/BatCurrentBitCov'
   *  DataTypeConversion: '<S12>/BatCurrent_Convert'
   *  S-Function (sfix_bitop): '<S12>/BatCurrent_And'
   */
  text28_B.or7 = (uint8_T)((uint32_T)rtb_BatVoltage_Ad & 255U);

  /* S-Function (sfix_bitop): '<S10>/or8' incorporates:
   *  Constant: '<S14>/Constant8'
   */
  text28_B.or8 = 0U;

  /* S-Function (ec55xx_cantransmitslb): '<S2>/CANTransmit' */

  /*Transmit CAN message*/
  {
    uint8 CAN0BUF8TX[8];
    uint8 can0buf8looptx= 0;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or1;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or2;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or3;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or4;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or5;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or6;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or7;
    can0buf8looptx++;
    CAN0BUF8TX[can0buf8looptx]= text28_B.or8;
    can0buf8looptx++;
    text28_B.CANTransmit_p= ec_can_transmit(0, 8, 0, 21U, 8, CAN0BUF8TX);
  }
}

/* Model step function for TID7 */
void text28_step7(void)                /* Sample time: [0.5s, 0.0s] */
{
  /* S-Function (fcncallgen): '<S58>/500ms' incorporates:
   *  SubSystem: '<S58>/FlashOperation'
   */

  /* S-Function (ec55xx_flashoslb): '<S72>/FlashOperatin' */
#if defined EC_FLASH_ENABLE

  /* Operate the flash module on the MPC5554 */
  ec_flash_operation();

#endif

}

/* Model step wrapper function for compatibility with a static main program */
void text28_step(int_T tid)
{
  switch (tid) {
   case 0 :
    text28_step0();
    break;

   case 1 :
    text28_step1();
    break;

   case 2 :
    text28_step2();
    break;

   case 3 :
    text28_step3();
    break;

   case 4 :
    text28_step4();
    break;

   case 5 :
    text28_step5();
    break;

   case 6 :
    text28_step6();
    break;

   case 7 :
    text28_step7();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void text28_initialize(void)
{
  /* Start for S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  Start for SubSystem: '<Root>/驱动系统'
   */

  /* Start for Atomic SubSystem: '<S80>/制动与尾灯' */

  /* Start for S-Function (ec55xx_pdpslb): '<S98>/尾灯' */

  /* Initialize PWM output for channel 19 */
  ec_pwm_init(19);

  /* End of Start for SubSystem: '<S80>/制动与尾灯' */

  /* Start for S-Function (ec55xx_cantransmitslb): '<S79>/CANTransmit' */
  ec_buffer_init(1,8,1,218040815U);

  /* Start for S-Function (ec55xx_pdpslb): '<S81>/安全出' */

  /* Initialize PWM output for channel 16 */
  ec_pwm_init(16);

  /* Start for S-Function (ec55xx_pdpslb): '<S143>/蜂鸣器' */

  /* Initialize PWM output for channel 14 */
  ec_pwm_init(14);

  /* Start for S-Function (ec55xx_ffrslb): '<S146>/左前' */
  SIU.PCR[167].R = 0x0500;
  fs_etpu_ppa_p_init(84,FS_ETPU_PRIORITY_MIDDLE,FS_ETPU_PPA_P_INIT,
                     FS_ETPU_PPA_RISING_EDGE);

  /* Start for S-Function (ec55xx_ffrslb): '<S146>/右前' */
  SIU.PCR[172].R = 0x0500;
  fs_etpu_ppa_p_init(89,FS_ETPU_PRIORITY_MIDDLE,FS_ETPU_PPA_P_INIT,
                     FS_ETPU_PPA_RISING_EDGE);

  /* Start for S-Function (ec55xx_canreceiveslb): '<S102>/CANReceive' */
  ec_buffer_init(1,7,1,218038281);

  /* Start for S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  Start for SubSystem: '<Root>/Function-Call Subsystem2'
   */
  /* Start for S-Function (ec55xx_cantransmitslb): '<S1>/CANTransmit' */
  ec_buffer_init(0,8,0,996U);

  /* Start for S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  Start for SubSystem: '<Root>/Function-Call Subsystem4'
   */
  /* Start for S-Function (ec55xx_canreceiveslb): '<S3>/CAN检测' */
  ec_buffer_init(0,0,1,408961267);

  /* Start for S-Function (ec55xx_pdpslb): '<S22>/断can线亮灯3' */

  /* Initialize PWM output for channel 0 */
  ec_pwm_init(0);

  /* Start for S-Function (fcncallgen): '<Root>/20ms2' incorporates:
   *  Start for SubSystem: '<Root>/Function-Call Subsystem3'
   */
  /* Start for S-Function (ec55xx_cantransmitslb): '<S2>/CANTransmit' */
  ec_buffer_init(0,8,0,21U);

  /* Start for S-Function (fcncallgen): '<Root>/50ms2' incorporates:
   *  Start for SubSystem: '<Root>/Function-Call Subsystem7'
   */
  /* Start for S-Function (ec55xx_canreceiveslb): '<S4>/MCU STATUS 2' */
  ec_buffer_init(1,0,1,218038537);

  /* Start for S-Function (ec55xx_pdpslb): '<S4>/PowerDriverPWM' */

  /* Initialize PWM output for channel 18 */
  ec_pwm_init(18);

  /* Start for S-Function (ec55xx_caninterruptslb1): '<S56>/ReceiveandTransmitInterrupt' incorporates:
   *  Start for SubSystem: '<S56>/Function-Call Subsystem'
   */
  /* Start for function-call system: '<S56>/Function-Call Subsystem' */

  /* Start for S-Function (ec55xx_canreceiveslb): '<S61>/CANReceive1' incorporates:
   *  Start for SubSystem: '<S61>/Function-Call Subsystem'
   */
  /* Start for function-call system: '<S61>/Function-Call Subsystem' */

  /* Start for IfAction SubSystem: '<S62>/If Action Subsystem1' */

  /* Start for S-Function (ec55xx_cantransmitslb): '<S67>/CANTransmit' */
  ec_buffer_init(2,9,0,593U);

  /* End of Start for SubSystem: '<S62>/If Action Subsystem1' */

  /* Start for S-Function (ec55xx_canreceiveslb): '<S61>/CANReceive1' */
  ec_buffer_init(2,1,0,278);

  /* Start for S-Function (ec55xx_caninterruptslb1): '<S56>/ReceiveandTransmitInterrupt' */
  ec_bufint_init(2,1);
  INTC_InstallINTCInterruptHandler( ISR_FlexCAN_2_MB1, SW_INT_VEC_CAN2_IFRL_BUF1,
    CAN2_INTC_PRIORITY );

  /* Start for S-Function (fcncallgen): '<S60>/Function-Call Generator' incorporates:
   *  Start for SubSystem: '<S60>/CCPBackground'
   */
  /* Start for S-Function (ec55xx_ccpslb): '<S74>/CCPBackground' */
  ccpInit();

  /* Start for S-Function (ec55xx_caninterruptslb1): '<S60>/ReceiveandTransmitInterrupt' incorporates:
   *  Start for SubSystem: '<S60>/CCPReceive'
   */
  /* Start for function-call system: '<S60>/CCPReceive' */

  /* Start for S-Function (ec55xx_canreceiveslb): '<S75>/CANReceive' */
  ec_buffer_init(2,0,0,CCP_CRO_ID);

  /* Start for S-Function (ec55xx_caninterruptslb1): '<S60>/ReceiveandTransmitInterrupt' */
  ec_bufint_init(2,0);
  INTC_InstallINTCInterruptHandler( ISR_FlexCAN_2_MB0, SW_INT_VEC_CAN2_IFRL_BUF0,
    CAN2_INTC_PRIORITY );

  /* Start for S-Function (ec55xx_caninterruptslb1): '<S60>/ReceiveandTransmitInterrupt1' */
  ec_bufint_init(2,8);
  INTC_InstallINTCInterruptHandler( ISR_FlexCAN_2_MB8, SW_INT_VEC_CAN2_IFRL_BUF8,
    CAN2_INTC_PRIORITY );

  /* Start for S-Function (ec55xx_adcbsb): '<S5>/ADC' */
  ec_adc_init();

  /* Start for S-Function (ec55xx_cpubsb): '<S5>/CPU' */
  ec_wdg_init(1);

  /* Start for S-Function (ec55xx_rtibsb): '<S5>/RTI' */
  ec_rti_init(500);

  /* ConstCode for S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  ConstCode for SubSystem: '<Root>/驱动系统'
   */

  /* S-Function (ec55xx_mrsslb): '<S6>/MainRelaySwitch' */

  /* Set level text28_ConstB.DataTypeConversion_a for main relay switch */
  ec_gpio_write(205,text28_ConstB.DataTypeConversion_a);

  /* InitializeConditions for S-Function (fcncallgen): '<Root>/10ms1' incorporates:
   *  InitializeConditions for SubSystem: '<Root>/驱动系统'
   */
  /* InitializeConditions for UnitDelay: '<S97>/Unit Delay' */
  text28_DW.UnitDelay_DSTATE_l = 1.0;
}

/* File trailer for ECUCoder generated file text28.c.
 *
 * [EOF]
 */
