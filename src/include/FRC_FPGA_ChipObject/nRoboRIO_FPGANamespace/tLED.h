// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __nFRC_2020_20_1_0_LED_h__
#define __nFRC_2020_20_1_0_LED_h__

#include "../tSystem.h"
#include "../tSystemInterface.h"

namespace nFPGA
{
namespace nFRC_2020_20_1_0
{

class tLED
{
public:
   tLED(){}
   virtual ~tLED(){}

   virtual tSystemInterface* getSystemInterface() = 0;
   static tLED* create(tRioStatusCode *status);

   typedef enum
   {
      kNumSystems = 1,
   } tIfaceConstants;




   typedef enum
   {
   } tResetLoad_IfaceConstants;

   virtual void strobeResetLoad(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tStringLength_IfaceConstants;

   virtual void writeStringLength(unsigned short value, tRioStatusCode *status) = 0;
   virtual unsigned short readStringLength(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tPixelOutputIndex_IfaceConstants;

   virtual unsigned short readPixelOutputIndex(tRioStatusCode *status) = 0;


   typedef enum
   {
      kNumLowBitTickTimingElements = 2,
   } tLowBitTickTiming_IfaceConstants;

   virtual void writeLowBitTickTiming(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status) = 0;
   virtual unsigned char readLowBitTickTiming(unsigned char bitfield_index, tRioStatusCode *status) = 0;


   typedef enum
   {
   } tPixelWriteIndex_IfaceConstants;

   virtual signed short readPixelWriteIndex(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tStart_IfaceConstants;

   virtual void strobeStart(tRioStatusCode *status) = 0;


   typedef enum
   {
      kNumHighBitTickTimingElements = 2,
   } tHighBitTickTiming_IfaceConstants;

   virtual void writeHighBitTickTiming(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status) = 0;
   virtual unsigned char readHighBitTickTiming(unsigned char bitfield_index, tRioStatusCode *status) = 0;


   typedef enum
   {
   } tLoad_IfaceConstants;

   virtual void strobeLoad(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tSyncTiming_IfaceConstants;

   virtual void writeSyncTiming(unsigned int value, tRioStatusCode *status) = 0;
   virtual unsigned int readSyncTiming(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tAbort_IfaceConstants;

   virtual void strobeAbort(tRioStatusCode *status) = 0;


   typedef enum
   {
   } tOutputSelect_IfaceConstants;

   virtual void writeOutputSelect(unsigned char value, tRioStatusCode *status) = 0;
   virtual unsigned char readOutputSelect(tRioStatusCode *status) = 0;




private:
   tLED(const tLED&);
   void operator=(const tLED&);
};

}
}

#endif // __nFRC_2020_20_1_0_LED_h__
