// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __nFRC_2023_23_0_0_HMB_h__
#define __nFRC_2023_23_0_0_HMB_h__

#include "../tSystem.h"
#include "../tSystemInterface.h"

namespace nFPGA
{
namespace nFRC_2023_23_0_0
{

class tHMB
{
public:
   tHMB(){}
   virtual ~tHMB(){}

   virtual tSystemInterface* getSystemInterface() = 0;
   static tHMB* create(tRioStatusCode *status);

   typedef enum
   {
      kNumSystems = 1,
   } tIfaceConstants;

   typedef
   union{
      struct{
#ifdef __vxworks
         unsigned Enables_AI0_Low : 1;
         unsigned Enables_AI0_High : 1;
         unsigned Enables_AIAveraged0_Low : 1;
         unsigned Enables_AIAveraged0_High : 1;
         unsigned Enables_AI1_Low : 1;
         unsigned Enables_AI1_High : 1;
         unsigned Enables_AIAveraged1_Low : 1;
         unsigned Enables_AIAveraged1_High : 1;
         unsigned Enables_Accumulator0 : 1;
         unsigned Enables_Accumulator1 : 1;
         unsigned Enables_DI : 1;
         unsigned Enables_AnalogTriggers : 1;
         unsigned Enables_Counters_Low : 1;
         unsigned Enables_Counters_High : 1;
         unsigned Enables_CounterTimers_Low : 1;
         unsigned Enables_CounterTimers_High : 1;
         unsigned Enables_Encoders_Low : 1;
         unsigned Enables_Encoders_High : 1;
         unsigned Enables_EncoderTimers_Low : 1;
         unsigned Enables_EncoderTimers_High : 1;
         unsigned Enables_DutyCycle_Low : 1;
         unsigned Enables_DutyCycle_High : 1;
         unsigned Enables_Interrupts : 1;
         unsigned Enables_PWM : 1;
         unsigned Enables_PWM_MXP : 1;
         unsigned Enables_Relay_DO_AO : 1;
         unsigned Enables_Timestamp : 1;
#else
         unsigned Enables_Timestamp : 1;
         unsigned Enables_Relay_DO_AO : 1;
         unsigned Enables_PWM_MXP : 1;
         unsigned Enables_PWM : 1;
         unsigned Enables_Interrupts : 1;
         unsigned Enables_DutyCycle_High : 1;
         unsigned Enables_DutyCycle_Low : 1;
         unsigned Enables_EncoderTimers_High : 1;
         unsigned Enables_EncoderTimers_Low : 1;
         unsigned Enables_Encoders_High : 1;
         unsigned Enables_Encoders_Low : 1;
         unsigned Enables_CounterTimers_High : 1;
         unsigned Enables_CounterTimers_Low : 1;
         unsigned Enables_Counters_High : 1;
         unsigned Enables_Counters_Low : 1;
         unsigned Enables_AnalogTriggers : 1;
         unsigned Enables_DI : 1;
         unsigned Enables_Accumulator1 : 1;
         unsigned Enables_Accumulator0 : 1;
         unsigned Enables_AIAveraged1_High : 1;
         unsigned Enables_AIAveraged1_Low : 1;
         unsigned Enables_AI1_High : 1;
         unsigned Enables_AI1_Low : 1;
         unsigned Enables_AIAveraged0_High : 1;
         unsigned Enables_AIAveraged0_Low : 1;
         unsigned Enables_AI0_High : 1;
         unsigned Enables_AI0_Low : 1;
#endif
      };
      struct{
         unsigned value : 27;
      };
   } tConfig;



   typedef enum
   {
   } tLoopCount_IfaceConstants;

   virtual signed int readLoopCount(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tWriteData_IfaceConstants;

   virtual unsigned int readWriteData(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tReadData_IfaceConstants;

   virtual unsigned int readReadData(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tWriteAddress_IfaceConstants;

   virtual unsigned short readWriteAddress(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tForceOnce_IfaceConstants;

   virtual void writeForceOnce(bool value, tRioStatusCode *status) = 0;
   virtual bool readForceOnce(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tConfig_IfaceConstants;

   virtual void writeConfig(tConfig value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AI0_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AI0_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AIAveraged0_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AIAveraged0_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AI1_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AI1_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AIAveraged1_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AIAveraged1_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Accumulator0(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Accumulator1(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_DI(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_AnalogTriggers(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Counters_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Counters_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_CounterTimers_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_CounterTimers_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Encoders_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Encoders_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_EncoderTimers_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_EncoderTimers_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_DutyCycle_Low(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_DutyCycle_High(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Interrupts(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_PWM(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_PWM_MXP(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Relay_DO_AO(bool value, tRioStatusCode *status) = 0;
   virtual void writeConfig_Enables_Timestamp(bool value, tRioStatusCode *status) = 0;
   virtual tConfig readConfig(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AI0_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AI0_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AIAveraged0_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AIAveraged0_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AI1_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AI1_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AIAveraged1_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AIAveraged1_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Accumulator0(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Accumulator1(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_DI(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_AnalogTriggers(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Counters_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Counters_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_CounterTimers_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_CounterTimers_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Encoders_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Encoders_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_EncoderTimers_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_EncoderTimers_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_DutyCycle_Low(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_DutyCycle_High(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Interrupts(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_PWM(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_PWM_MXP(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Relay_DO_AO(tRioStatusCode *status) = 0;
   virtual bool readConfig_Enables_Timestamp(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tWriteCount_IfaceConstants;

   virtual unsigned int readWriteCount(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tReqReadyForInput_IfaceConstants;

   virtual bool readReqReadyForInput(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tWriteReadyForInput_IfaceConstants;

   virtual bool readWriteReadyForInput(tRioStatusCode *status) = 0;




private:
   tHMB(const tHMB&);
   void operator=(const tHMB&);
};

}
}

#endif // __nFRC_2023_23_0_0_HMB_h__
