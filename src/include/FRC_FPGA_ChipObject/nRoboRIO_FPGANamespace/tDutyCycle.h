// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __nFRC_2022_22_0_0_DutyCycle_h__
#define __nFRC_2022_22_0_0_DutyCycle_h__

#include "../tSystem.h"
#include "../tSystemInterface.h"

namespace nFPGA
{
namespace nFRC_2022_22_0_0
{

class tDutyCycle
{
public:
   tDutyCycle(){}
   virtual ~tDutyCycle(){}

   virtual tSystemInterface* getSystemInterface() = 0;
   static tDutyCycle* create(unsigned char sys_index, tRioStatusCode *status);
   virtual unsigned char getSystemIndex() = 0;


   typedef enum
   {
      kNumSystems = 8,
   } tIfaceConstants;

   typedef
   union{
      struct{
#ifdef __vxworks
         unsigned Channel : 4;
         unsigned Module : 1;
         unsigned AnalogTrigger : 1;
#else
         unsigned AnalogTrigger : 1;
         unsigned Module : 1;
         unsigned Channel : 4;
#endif
      };
      struct{
         unsigned value : 6;
      };
   } tSource;


   typedef enum
   {
   } tOutput_IfaceConstants;

   virtual unsigned int readOutput(unsigned char *overflowStatus, tRioStatusCode *status) = 0;


   typedef enum
   {
   } tSource_IfaceConstants;

   virtual void writeSource(tSource value, tRioStatusCode *status) = 0;
   virtual void writeSource_Channel(unsigned char value, tRioStatusCode *status) = 0;
   virtual void writeSource_Module(unsigned char value, tRioStatusCode *status) = 0;
   virtual void writeSource_AnalogTrigger(bool value, tRioStatusCode *status) = 0;
   virtual tSource readSource(tRioStatusCode *status) = 0;
   virtual unsigned char readSource_Channel(tRioStatusCode *status) = 0;
   virtual unsigned char readSource_Module(tRioStatusCode *status) = 0;
   virtual bool readSource_AnalogTrigger(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tFrequency_IfaceConstants;

   virtual unsigned short readFrequency(unsigned char *overflowStatus, tRioStatusCode *status) = 0;





private:
   tDutyCycle(const tDutyCycle&);
   void operator=(const tDutyCycle&);
};

}
}

#endif // __nFRC_2022_22_0_0_DutyCycle_h__
