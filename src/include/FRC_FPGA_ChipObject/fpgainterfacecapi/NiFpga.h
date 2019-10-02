/*
 * FPGA Interface C API 19.0 header file.
 *
 * Copyright (c) 2019,
 * National Instruments Corporation.
 * All rights reserved.
 */

#ifndef __NiFpga_h__
#define __NiFpga_h__

/*
 * Determine platform details.
 */
#if defined(_M_IX86) \
 || defined(_M_X64) \
 || defined(_M_AMD64) \
 || defined(i386) \
 || defined(__i386) \
 || defined(__i386__) \
 || defined(__i486__) \
 || defined(__i586__) \
 || defined(__i686__) \
 || defined(__amd64__) \
 || defined(__amd64) \
 || defined(__x86_64__) \
 || defined(__x86_64) \
 || defined(__IA32__) \
 || defined(_X86_) \
 || defined(__THW_INTEL__) \
 || defined(__I86__) \
 || defined(__INTEL__) \
 || defined(__X86__) \
 || defined(__386__) \
 || defined(__I86__) \
 || defined(M_I386) \
 || defined(M_I86) \
 || defined(_M_I386) \
 || defined(_M_I86)
   #if defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__) \
    || defined(_WINDOWS) \
    || defined(__WINDOWS_386__) \
    || defined(__CYGWIN__)
      /* Either Windows or Phar Lap ETS. */
      #define NiFpga_Windows 1
   #elif defined(__linux__) \
      || defined(__linux) \
      || defined(linux) \
      || defined(__gnu_linux__)
      #define NiFpga_Linux 1
   #elif defined(__APPLE__) && defined(__MACH__)
      #define NiFpga_MacOsX 1
   #else
      #error Unsupported OS.
   #endif
#elif defined(__powerpc) \
   || defined(__powerpc__) \
   || defined(__POWERPC__) \
   || defined(__ppc__) \
   || defined(__PPC) \
   || defined(_M_PPC) \
   || defined(_ARCH_PPC) \
   || defined(__PPC__) \
   || defined(__ppc)
   #if defined(__vxworks)
      #define NiFpga_VxWorks 1
   #else
      #error Unsupported OS.
   #endif
#elif defined(__arm__) \
   || defined(__thumb__) \
   || defined(__TARGET_ARCH_ARM) \
   || defined(__TARGET_ARCH_THUMB) \
   || defined(_ARM) \
   || defined(_M_ARM) \
   || defined(_M_ARMT)
#if defined(__linux__) \
 || defined(__linux) \
 || defined(linux) \
 || defined(__gnu_linux__)
   #define NiFpga_Linux 1
#else
      #error Unsupported OS.
   #endif
#else
   #error Unsupported architecture.
#endif

/*
 * Determine compiler.
 */
#if defined(_MSC_VER)
   #define NiFpga_Msvc 1
#elif defined(__GNUC__)
   #define NiFpga_Gcc 1
#elif defined(_CVI_) && !defined(_TPC_)
   #define NiFpga_Cvi 1
   /* Enables CVI Library Protection Errors. */
   #pragma EnableLibraryRuntimeChecking
#else
   /* Unknown compiler. */
#endif

/*
 * Determine compliance with different C/C++ language standards.
 */
#if defined(__cplusplus)
   #define NiFpga_Cpp 1
   #if __cplusplus >= 199707L
      #define NiFpga_Cpp98 1
      #if __cplusplus >= 201103L
         #define NiFpga_Cpp11 1
      #endif
   #endif
#endif
#if defined(__STDC__)
   #define NiFpga_C89 1
   #if defined(__STDC_VERSION__)
      #define NiFpga_C90 1
      #if __STDC_VERSION__ >= 199409L
         #define NiFpga_C94 1
         #if __STDC_VERSION__ >= 199901L
            #define NiFpga_C99 1
            #if __STDC_VERSION__ >= 201112L
               #define NiFpga_C11 1
            #endif
         #endif
      #endif
   #endif
#endif

/*
 * Determine ability to inline functions.
 */
#if NiFpga_Cpp || NiFpga_C99
   /* The inline keyword exists in C++ and C99. */
   #define NiFpga_Inline inline
#elif NiFpga_Msvc
   /* Visual C++ (at least since 6.0) also supports an alternate keyword. */
   #define NiFpga_Inline __inline
#elif NiFpga_Gcc
   /* GCC (at least since 2.95.2) also supports an alternate keyword. */
   #define NiFpga_Inline __inline__
#elif !defined(NiFpga_Inline)
   /*
    * Disable inlining if inline support is unknown. To manually enable
    * inlining, #define the following macro before #including NiFpga.h:
    *
    *    #define NiFpga_Inline inline
    */
   #define NiFpga_Inline
#endif

/*
 * Define exact-width integer types, if they have not already been defined.
 */
#if NiFpga_ExactWidthIntegerTypesDefined \
 || defined(_STDINT) \
 || defined(_STDINT_H) \
 || defined(_STDINT_H_) \
 || defined(_INTTYPES_H) \
 || defined(_INTTYPES_H_) \
 || defined(_SYS_STDINT_H) \
 || defined(_SYS_STDINT_H_) \
 || defined(_SYS_INTTYPES_H) \
 || defined(_SYS_INTTYPES_H_) \
 || defined(_STDINT_H_INCLUDED) \
 || defined(_MSC_STDINT_H_) \
 || defined(_PSTDINT_H_INCLUDED)
   /* Assume that exact-width integer types have already been defined. */
#elif NiFpga_VxWorks
   /* VxWorks (at least 6.3 and earlier) did not have stdint.h. */
   #include <types/vxTypes.h>
#elif NiFpga_C99 \
   || NiFpga_Gcc /* GCC (at least since 3.0) has a stdint.h. */ \
   || defined(HAVE_STDINT_H)
   /* Assume that stdint.h can be included. */
   #include <stdint.h>
#elif NiFpga_Msvc \
   || NiFpga_Cvi
   /* Manually define exact-width integer types. */
   typedef   signed    char  int8_t;
   typedef unsigned    char uint8_t;
   typedef            short  int16_t;
   typedef unsigned   short uint16_t;
   typedef              int  int32_t;
   typedef unsigned     int uint32_t;
   typedef          __int64  int64_t;
   typedef unsigned __int64 uint64_t;
#else
   /*
    * Exact-width integer types must be defined by the user, and the following
    * macro must be #defined, before #including NiFpga.h:
    *
    *    #define NiFpga_ExactWidthIntegerTypesDefined 1
    */
   #error Exact-width integer types must be defined by the user. See comment.
#endif

/* Included for definition of size_t. */
#include <stddef.h>
/* Included for definition of FLT_MAX and DBL_MAX */
#include <float.h>

#if NiFpga_Cpp
extern "C"
{
#endif

/**
 * A boolean value; either NiFpga_False or NiFpga_True.
 */
typedef uint8_t NiFpga_Bool;

/**
 * Represents a false condition.
 */
static const NiFpga_Bool NiFpga_False = 0;

/**
 * Represents a true condition.
 */
static const NiFpga_Bool NiFpga_True = 1;

/** \addtogroup Status
 *  @{
 */

/**
 * Represents the resulting status of a function call through its return value.
 * 0 is success, negative values are errors, and positive values are warnings.
 */
typedef int32_t NiFpga_Status;

/**
 * No errors or warnings.
 */
static const NiFpga_Status NiFpga_Status_Success = 0;

/**
 * The timeout expired before the FIFO operation could complete.
 */
static const NiFpga_Status NiFpga_Status_FifoTimeout = -50400;

/**
 * No transfer is in progress because the transfer was aborted by the client.
 * The operation could not be completed as specified.
 */
static const NiFpga_Status NiFpga_Status_TransferAborted = -50405;

/**
 * A memory allocation failed. Try again after rebooting.
 */
static const NiFpga_Status NiFpga_Status_MemoryFull = -52000;

/**
 * An unexpected software error occurred.
 */
static const NiFpga_Status NiFpga_Status_SoftwareFault = -52003;

/**
 * A parameter to a function was not valid. This could be a NULL pointer, a bad
 * value, etc.
 */
static const NiFpga_Status NiFpga_Status_InvalidParameter = -52005;

/**
 * A required resource was not found. The NiFpga.* library, the RIO resource, or
 * some other resource may be missing.
 */
static const NiFpga_Status NiFpga_Status_ResourceNotFound = -52006;

/**
 * A required resource was not properly initialized. This could occur if
 * NiFpga_Initialize was not called or a required NiFpga_IrqContext was not
 * reserved.
 */
static const NiFpga_Status NiFpga_Status_ResourceNotInitialized = -52010;

/**
 * The FPGA is already running.
 */
static const NiFpga_Status NiFpga_Status_FpgaAlreadyRunning = -61003;

/**
 * An error occurred downloading the VI to the FPGA device. Verify that
 * the target is connected and powered and that the resource of the target
 * is properly configured.
 */
static const NiFpga_Status NiFpga_Status_DownloadError = -61018;

/**
 * The bitfile was not compiled for the specified resource's device type.
 */
static const NiFpga_Status NiFpga_Status_DeviceTypeMismatch = -61024;

/**
 * An error was detected in the communication between the host computer and the
 * FPGA target.
 */
static const NiFpga_Status NiFpga_Status_CommunicationTimeout = -61046;

/**
 * The timeout expired before any of the IRQs were asserted.
 */
static const NiFpga_Status NiFpga_Status_IrqTimeout = -61060;

/**
 * The specified bitfile is invalid or corrupt.
 */
static const NiFpga_Status NiFpga_Status_CorruptBitfile = -61070;

/**
 * The requested FIFO depth is invalid. It is either 0 or an amount not
 * supported by the hardware.
 */
static const NiFpga_Status NiFpga_Status_BadDepth = -61072;

/**
 * The number of FIFO elements is invalid. Either the number is greater than the
 * depth of the host memory DMA FIFO, or more elements were requested for
 * release than had been acquired.
 */
static const NiFpga_Status NiFpga_Status_BadReadWriteCount = -61073;

/**
 * A hardware clocking error occurred. A derived clock lost lock with its base
 * clock during the execution of the LabVIEW FPGA VI. If any base clocks with
 * derived clocks are referencing an external source, make sure that the
 * external source is connected and within the supported frequency, jitter,
 * accuracy, duty cycle, and voltage specifications. Also verify that the
 * characteristics of the base clock match the configuration specified in the
 * FPGA Base Clock Properties. If all base clocks with derived clocks are
 * generated from free-running, on-board sources, please contact National
 * Instruments technical support at ni.com/support.
 */
static const NiFpga_Status NiFpga_Status_ClockLostLock = -61083;

/**
 * The operation could not be performed because the FPGA is busy. Stop all
 * activities on the FPGA before requesting this operation. If the target is in
 * Scan Interface programming mode, put it in FPGA Interface programming mode.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusy = -61141;

/**
 * The operation could not be performed because the FPGA is busy operating in
 * FPGA Interface C API mode. Stop all activities on the FPGA before requesting
 * this operation.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyFpgaInterfaceCApi = -61200;

/**
 * The chassis is in Scan Interface programming mode. In order to run FPGA VIs,
 * you must go to the chassis properties page, select FPGA programming mode, and
 * deploy settings.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyScanInterface = -61201;

/**
 * The operation could not be performed because the FPGA is busy operating in
 * FPGA Interface mode. Stop all activities on the FPGA before requesting this
 * operation.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyFpgaInterface = -61202;

/**
 * The operation could not be performed because the FPGA is busy operating in
 * Interactive mode. Stop all activities on the FPGA before requesting this
 * operation.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyInteractive = -61203;

/**
 * The operation could not be performed because the FPGA is busy operating in
 * Emulation mode. Stop all activities on the FPGA before requesting this
 * operation.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyEmulation = -61204;

/**
 * LabVIEW FPGA does not support the Reset method for bitfiles that allow
 * removal of implicit enable signals in single-cycle Timed Loops.
 */
static const NiFpga_Status NiFpga_Status_ResetCalledWithImplicitEnableRemoval = -61211;

/**
 * LabVIEW FPGA does not support the Abort method for bitfiles that allow
 * removal of implicit enable signals in single-cycle Timed Loops.
 */
static const NiFpga_Status NiFpga_Status_AbortCalledWithImplicitEnableRemoval = -61212;

/**
 * LabVIEW FPGA does not support Close and Reset if Last Reference for bitfiles
 * that allow removal of implicit enable signals in single-cycle Timed Loops.
 * Pass the NiFpga_CloseAttribute_NoResetIfLastSession attribute to NiFpga_Close
 * instead of 0.
 */
static const NiFpga_Status NiFpga_Status_CloseAndResetCalledWithImplicitEnableRemoval = -61213;

/**
 * For bitfiles that allow removal of implicit enable signals in single-cycle
 * Timed Loops, LabVIEW FPGA does not support this method prior to running the
 * bitfile.
 */
static const NiFpga_Status NiFpga_Status_ImplicitEnableRemovalButNotYetRun = -61214;

/**
 * Bitfiles that allow removal of implicit enable signals in single-cycle Timed
 * Loops can run only once. Download the bitfile again before re-running the VI.
 */
static const NiFpga_Status NiFpga_Status_RunAfterStoppedCalledWithImplicitEnableRemoval = -61215;

/**
 * A gated clock has violated the handshaking protocol. If you are using
 * external gated clocks, ensure that they follow the required clock gating
 * protocol. If you are generating your clocks internally, please contact
 * National Instruments Technical Support.
 */
static const NiFpga_Status NiFpga_Status_GatedClockHandshakingViolation = -61216;

/**
 * The number of elements requested must be less than or equal to the number of
 * unacquired elements left in the host memory DMA FIFO. There are currently
 * fewer unacquired elements left in the FIFO than are being requested. Release
 * some acquired elements before acquiring more elements.
 */
static const NiFpga_Status NiFpga_Status_ElementsNotPermissibleToBeAcquired = -61219;

/**
 * The operation could not be performed because the FPGA is in configuration or
 * discovery mode. Wait for configuration or discovery to complete and retry
 * your operation.
 */
static const NiFpga_Status NiFpga_Status_FpgaBusyConfiguration = -61252;

/**
 * LabVIEW FPGA does not support Close and Reset if Last Reference for bitfiles
 * that do not support Reset. Pass the
 * NiFpga_CloseAttribute_NoResetIfLastSession attribute to NiFpga_Close instead
 * of 0.
 */
static const NiFpga_Status NiFpga_Status_CloseAndResetCalledWithResetNotSupported = -61253;

/**
 * An unexpected internal error occurred.
 */
static const NiFpga_Status NiFpga_Status_InternalError = -61499;

/**
 * The NI-RIO driver was unable to allocate memory for a FIFO. This can happen
 * when the combined depth of all DMA FIFOs exceeds the maximum depth for the
 * controller, or when the controller runs out of system memory. You may be able
 * to reconfigure the controller with a greater maximum FIFO depth. For more
 * information, refer to the NI KnowledgeBase article 65OF2ERQ.
 */
static const NiFpga_Status NiFpga_Status_TotalDmaFifoDepthExceeded = -63003;

/**
 * Access to the remote system was denied. Use MAX to check the Remote Device
 * Access settings under Software>>NI-RIO>>NI-RIO Settings on the remote system.
 */
static const NiFpga_Status NiFpga_Status_AccessDenied = -63033;

/**
 * The NI-RIO software on the host is not compatible with the software on the
 * target. Upgrade the NI-RIO software on the host in order to connect to this
 * target.
 */
static const NiFpga_Status NiFpga_Status_HostVersionMismatch = -63038;

/**
 * A connection could not be established to the specified remote device. Ensure
 * that the device is on and accessible over the network, that NI-RIO software
 * is installed, and that the RIO server is running and properly configured.
 */
static const NiFpga_Status NiFpga_Status_RpcConnectionError = -63040;

/**
 * The RPC session is invalid. The target may have reset or been rebooted. Check
 * the network connection and retry the operation.
 */
static const NiFpga_Status NiFpga_Status_RpcSessionError = -63043;

/**
 * The operation could not complete because another session is accessing the
 * FIFO. Close the other session and retry.
 */
static const NiFpga_Status NiFpga_Status_FifoReserved = -63082;

/**
 * A Configure FIFO, Stop FIFO, Read FIFO, or Write FIFO function was called
 * while the host had acquired elements of the FIFO. Release all acquired
 * elements before configuring, stopping, reading, or writing.
 */
static const NiFpga_Status NiFpga_Status_FifoElementsCurrentlyAcquired = -63083;

/**
 * A function was called using a misaligned address. The address must be a
 * multiple of the size of the datatype.
 */
static const NiFpga_Status NiFpga_Status_MisalignedAccess = -63084;

/**
 * The FPGA Read/Write Control Function is accessing a control or indicator
 * with data that exceeds the maximum size supported on the current target.
 * Refer to the hardware documentation for the limitations on data types for
 * this target.
 */
static const NiFpga_Status NiFpga_Status_ControlOrIndicatorTooLarge = -63085;

/**
 * A valid .lvbitx bitfile is required. If you are using a valid .lvbitx
 * bitfile, the bitfile may not be compatible with the software you are using.
 * Determine which version of LabVIEW was used to make the bitfile, update your
 * software to that version or later, and try again.
 */
static const NiFpga_Status NiFpga_Status_BitfileReadError = -63101;

/**
 * The specified signature does not match the signature of the bitfile. If the
 * bitfile has been recompiled, regenerate the C API and rebuild the
 * application.
 */
static const NiFpga_Status NiFpga_Status_SignatureMismatch = -63106;

/**
 * The bitfile you are trying to use is incompatible with the version
 * of NI-RIO installed on the target and/or host. Update the version
 * of NI-RIO on the target and/or host to the same version (or later)
 * used to compile the bitfile. Alternatively, recompile the bitfile
 * with the same version of NI-RIO that is currently installed on the
 * target and/or host.
 */
static const NiFpga_Status NiFpga_Status_IncompatibleBitfile = -63107;

/**
 * A hardware failure has occurred. The operation could not be completed as
 * specified.
 */
static const NiFpga_Status NiFpga_Status_HardwareFault = -63150;

/**
 * Either the supplied resource name is invalid as a RIO resource name, or the
 * device was not found. Use MAX to find the proper resource name for the
 * intended device.
 */
static const NiFpga_Status NiFpga_Status_InvalidResourceName = -63192;

/**
 * The requested feature is not supported.
 */
static const NiFpga_Status NiFpga_Status_FeatureNotSupported = -63193;

/**
 * The NI-RIO software on the target system is not compatible with this
 * software. Upgrade the NI-RIO software on the target system.
 */
static const NiFpga_Status NiFpga_Status_VersionMismatch = -63194;

/**
 * The session is invalid or has been closed.
 */
static const NiFpga_Status NiFpga_Status_InvalidSession = -63195;

/**
 * The maximum number of open FPGA sessions has been reached. Close some open
 * sessions.
 */
static const NiFpga_Status NiFpga_Status_OutOfHandles = -63198;

/**
 * Tests whether a status is an error.
 *
 * @param status status to check for an error
 * @return whether the status was an error
 */
static NiFpga_Inline NiFpga_Bool NiFpga_IsError(const NiFpga_Status status)
{
   return status < NiFpga_Status_Success ? NiFpga_True : NiFpga_False;
}

/**
 * Tests whether a status is not an error. Success and warnings are not errors.
 *
 * @param status status to check for an error
 * @return whether the status was a success or warning
 */
static NiFpga_Inline NiFpga_Bool NiFpga_IsNotError(const NiFpga_Status status)
{
   return status >= NiFpga_Status_Success ? NiFpga_True : NiFpga_False;
}

/**
 * Conditionally sets the status to a new value. The previous status is
 * preserved unless the new status is more of an error, which means that
 * warnings and errors overwrite successes, and errors overwrite warnings. New
 * errors do not overwrite older errors, and new warnings do not overwrite
 * older warnings.
 *
 * @param status status to conditionally set
 * @param newStatus new status value that may be set
 * @return the resulting status
 */
static NiFpga_Inline NiFpga_Status NiFpga_MergeStatus(
                                               NiFpga_Status* const status,
                                               const NiFpga_Status  newStatus)
{
   if (!status)
      return NiFpga_Status_InvalidParameter;
   if (NiFpga_IsNotError(*status)
   &&  (*status == NiFpga_Status_Success || NiFpga_IsError(newStatus)))
      *status = newStatus;
   return *status;
}

/**
 * This macro evaluates the expression only if the status is not an error. The
 * expression must evaluate to an NiFpga_Status, such as a call to any NiFpga_*
 * function, because the status will be set to the returned status if the
 * expression is evaluated.
 *
 * You can use this macro to mimic status chaining in LabVIEW, where the status
 * does not have to be explicitly checked after each call. Such code may look
 * like the following example.
 *
 *        NiFpga_Status status = NiFpga_Status_Success;
 *        NiFpga_IfIsNotError(status, NiFpga_WriteU32(...));
 *        NiFpga_IfIsNotError(status, NiFpga_WriteU32(...));
 *        NiFpga_IfIsNotError(status, NiFpga_WriteU32(...));
 *
 * @param status status to check for an error
 * @param expression expression to call if the incoming status is not an error
 */
#define NiFpga_IfIsNotError(status, expression) \
   if (NiFpga_IsNotError(status)) \
      NiFpga_MergeStatus(&status, (expression)); \

/**
 * @}
 */

/** \addtogroup FXP
 *  @{
 */

/**
 * This struct contains information needed to interpret an FXP Type.
 *   - `isSigned` tells if the type is signed.
 *   - `wordLength` tells us the number of bits used in the type.
 *   - `integerWordLength` is the number of bits to shift the binary point to 
 *     reach the most significant bit.
 *
 * More information can be found at the following links:
 * - http://zone.ni.com/reference/en-XX/help/371361J-01/lvconcepts/numeric_data/
 * - http://www.ni.com/newsletter/50303/en/
 * - http://digital.ni.com/public.nsf/allkb/346CC529EC1092B3862574FA0053B9B2
 */
typedef struct NiFpga_FxpTypeInfo
{
   NiFpga_Bool isSigned;
   uint8_t wordLength;
   int16_t integerWordLength;
} NiFpga_FxpTypeInfo;

/**
 * @}
 */

/**
 * Calculates the FXP delta as a float.  The delta is the smallest increment
 * that the FXP number can represent.
 *
 * @warning This function can lose precision.
 *
 * @param typeInfo the information about the FXP type
 * @return delta the delta for the specified FXP type
 */
static NiFpga_Inline float NiFpga_CalculateFxpDeltaFloat(
                                          const NiFpga_FxpTypeInfo typeInfo)
{
   const int32_t exponent =
      typeInfo.integerWordLength - typeInfo.wordLength;
   /*
      Constants taken from:
      https://en.wikipedia.org/wiki/IEEE_754#Basic_and_interchange_formats
   */
   const int32_t exponentBias = 127;
   const int32_t subNormalBias = 126;
   const int32_t maximumExponent = 127;
   const int32_t minimumExponent = -149;
   const int32_t minimumNormalExponent = -126;
   const int32_t significandStorageWidth = 23;
   const int32_t exponentStorageWidth = 8;
   uint32_t delta = 0;
   if (exponent < minimumExponent)
   {
     return 0.0;
   }
   if (exponent > maximumExponent)
   {
      return FLT_MAX;
   }
   if (exponent >= minimumNormalExponent)
   {
      const uint32_t exponentMask = (1 << exponentStorageWidth) - 1;
      delta = ((exponent + exponentBias) & exponentMask)
               << significandStorageWidth;
   }
   else
   {
      delta = 1 << (exponent + subNormalBias + significandStorageWidth);
   }
   return *((float*)(&delta));
}

/*
 * Private helper macro for converting from Fxp to float or double.
 * This is not intended for external use and may be changed or modified in
 * future versions.
 */
#define NiFpga_Private_FxpToFloatingPoint(typeInfo, delta, data) \
   const uint64_t wordLengthMask = (1ULL << typeInfo.wordLength) - 1; \
   data &= wordLengthMask; \
   if (typeInfo.isSigned) \
   { \
      const uint64_t signedMask = 1ULL << (typeInfo.wordLength - 1); \
      if (data & signedMask) \
      { \
         int64_t signedData = data ^ wordLengthMask; \
         signedData = (signedData + 1) * -1; \
         return delta * signedData; \
      } \
   } \
   return delta * data;


/**
 * @}
 */

/** \addtogroup FXP
 *  @{
 */

/**
 * Converts from a raw FXP value from the FPGA to a float.
 *
 * @warning This function can lose precision.
 * @warning This function truncates when losing precision rather than rounding.
 *
 * @param typeInfo information about the FXP data provided
 * @param data the raw FXP data from the FPGA
 * @return a float representation of the data
 */
static NiFpga_Inline float NiFpga_ConvertFromFxpToFloat(
                                          const NiFpga_FxpTypeInfo typeInfo,
                                          uint64_t data)
{
   const float delta = NiFpga_CalculateFxpDeltaFloat(typeInfo);
   NiFpga_Private_FxpToFloatingPoint(typeInfo, delta, data)
}

/**
 * @}
 */

/**
 * Calculates the FXP delta as a double.  The delta is the smallest increment
 * that the FXP number can represent.
 *
 * @warning This function can lose precision.
 *
 * @param typeInfo the information about the FXP type
 * @return delta the delta for the specified FXP type
 */
static NiFpga_Inline double NiFpga_CalculateFxpDeltaDouble(
                                          const NiFpga_FxpTypeInfo typeInfo)
{
   const int32_t exponent =
      typeInfo.integerWordLength - typeInfo.wordLength;
   /*
      Constants taken from:
      https://en.wikipedia.org/wiki/IEEE_754#Basic_and_interchange_formats
   */
   const int32_t exponentBias = 1023;
   const int32_t subNormalBias = 1022;
   const int32_t maximumExponent = 1023;
   const int32_t minimumExponent = -1074;
   const int32_t minimumNormalExponent = -1022;
   const int32_t significandStorageWidth = 52;
   const int32_t exponentStorageWidth = 11;
   uint64_t delta = 0;
   if (exponent < minimumExponent)
   {
      return 0.0;
   }
   if (exponent > maximumExponent)
   {
      return DBL_MAX;
   }
   if (exponent >= minimumNormalExponent)
   {
      const uint64_t exponentMask = (1 << exponentStorageWidth) - 1;
      delta = ((exponent + exponentBias) & exponentMask)
               << significandStorageWidth;
   }
   else
   {
      delta = 1ULL << (exponent + subNormalBias + significandStorageWidth);
   }
   return *((double*)(&delta));
}

/** \addtogroup FXP
 *  @{
 */

/**
 * Converts from a raw FXP value from the FPGA to a double.
 *
 * @warning This function can lose precision.
 * @warning This function truncates when losing precision rather than rounding.
 *
 * @param typeInfo information about the FXP data provided
 * @param data the raw FXP data from the FPGA
 * @return a double representation of the data
 */
static NiFpga_Inline double NiFpga_ConvertFromFxpToDouble(
                                          const NiFpga_FxpTypeInfo typeInfo,
                                          uint64_t data)
{
   const double delta = NiFpga_CalculateFxpDeltaDouble(typeInfo);
   NiFpga_Private_FxpToFloatingPoint(typeInfo, delta, data)
}

/**
 * @}
 */

/*
 * Private helper macro for converting from float or double to Fxp.
 * This is not intended for external use and may be changed or modified in
 * future versions.
 */
#define NiFpga_Private_FloatingPointToFxp(typeInfo, delta, data) \
   const uint64_t wordLengthMask = (1ULL << typeInfo.wordLength) - 1; \
   if (data < 0) \
   { \
      if (typeInfo.isSigned) \
      { \
         int64_t fxpRepresentation = (int64_t)(data / delta); \
         fxpRepresentation ^= wordLengthMask; \
         fxpRepresentation += 1; \
         fxpRepresentation *= -1; \
         if ((int64_t)(fxpRepresentation & wordLengthMask) == fxpRepresentation) \
         { \
            return fxpRepresentation; \
         } \
         else /* minimum */ \
         { \
            return (-1LL * (1LL << (typeInfo.wordLength - 1))) \
               & wordLengthMask; \
         } \
      } \
      else \
      { \
         return 0; \
      } \
   } \
   else \
   { \
      const uint64_t fxpRepresentation = (uint64_t)(data / delta); \
      if ((fxpRepresentation & wordLengthMask) == fxpRepresentation) \
      { \
         return fxpRepresentation; \
      } \
      else /* maxmimum */ \
      { \
         const uint64_t magnitude = typeInfo.wordLength \
                                    - (typeInfo.isSigned ? 1 : 0); \
         return (1ULL << magnitude) - 1; \
      } \
   }

/** \addtogroup FXP
 *  @{
 */

/**
 * Converts a float into a FXP representation of the specified type.
 *
 * @warning This function can lose precision.
 * @warning This function truncates when losing precision rather than rounding.
 *
 * @param typeInfo information about the FXP data provided
 * @param data the value to be converted to FXP
 * @return a value containing the FXP representation of data
 */
static NiFpga_Inline uint64_t NiFpga_ConvertFromFloatToFxp(
                                          const NiFpga_FxpTypeInfo typeInfo,
                                          float data)
{
   const float delta = NiFpga_CalculateFxpDeltaFloat(typeInfo);
   NiFpga_Private_FloatingPointToFxp(typeInfo, delta, data)
}

/**
 * Converts a double into a FXP representation of the specified type.
 *
 * @warning This function can lose precision.
 * @warning This function truncates when losing precision rather than rounding.
 *
 * @param typeInfo information about the FXP data provided
 * @param data the value to be converted to FXP
 * @return a value containing the FXP representation of data
 */
static NiFpga_Inline uint64_t NiFpga_ConvertFromDoubleToFxp(
                                          const NiFpga_FxpTypeInfo typeInfo,
                                          double data)
{
   const double delta = NiFpga_CalculateFxpDeltaDouble(typeInfo);
   NiFpga_Private_FloatingPointToFxp(typeInfo, delta, data)
}

/**
 * @}
 */

/** \addtogroup Required
 *  @{
 */

/**
 * You must call this function before all other function calls. This function
 * loads the NiFpga library so that all the other functions will work. If this
 * function succeeds, you must call NiFpga_Finalize after all other function
 * calls.
 *
 * @warning This function is not thread safe.
 *
 * @return result of the call
 */
NiFpga_Status NiFpga_Initialize(void);

/**
 * You must call this function after all other function calls if
 * NiFpga_Initialize succeeds. This function unloads the NiFpga library.
 *
 * @warning This function is not thread safe.
 *
 * @return result of the call
 */
NiFpga_Status NiFpga_Finalize(void);

/**
 * @}
 */

/** \addtogroup Session
 *  @{
 */

/**
 * A handle to an FPGA session.
 */
typedef uint32_t NiFpga_Session;

/**
 * Attributes that NiFpga_Open accepts.
 */
typedef enum
{
   NiFpga_OpenAttribute_NoRun = 1
} NiFpga_OpenAttribute;

/**
 * Opens a session to the FPGA. This call ensures that the contents of the
 * bitfile are programmed to the FPGA. The FPGA runs unless the
 * NiFpga_OpenAttribute_NoRun attribute is used.
 *
 * Because different operating systems have different default current working
 * directories for applications, you must pass an absolute path for the bitfile
 * parameter. If you pass only the filename instead of an absolute path, the
 * operating system may not be able to locate the bitfile. For example, the
 * default current working directories are C:/ni-rt/system/ for Phar Lap ETS and
 * /c/ for VxWorks. Because the generated *_Bitfile constant is a "#define" to a
 * string literal, you can use C/C++ string-literal concatenation to form an
 * absolute path. For example, if the bitfile is in the root directory of a
 * Phar Lap ETS system, pass the following for the bitfile parameter.
 *
 *    "C:\\" NiFpga_MyApplication_Bitfile
 *
 * @param bitfile path to the bitfile
 * @param signature signature of the bitfile
 * @param resource RIO resource string to open ("RIO0" or "rio://mysystem/RIO")
 * @param attribute bitwise OR of any NiFpga_OpenAttributes, or 0
 * @param session outputs the session handle, which must be closed when no
 *                longer needed
 * @return result of the call
 */
NiFpga_Status NiFpga_Open(const char*     bitfile,
                          const char*     signature,
                          const char*     resource,
                          uint32_t        attribute,
                          NiFpga_Session* session);

/**
 * Attributes that NiFpga_Close accepts.
 */
typedef enum
{
   NiFpga_CloseAttribute_NoResetIfLastSession = 1
} NiFpga_CloseAttribute;

/**
 * Closes the session to the FPGA. The FPGA resets unless either another session
 * is still open or you use the NiFpga_CloseAttribute_NoResetIfLastSession
 * attribute.
 *
 * @param session handle to a currently open session
 * @param attribute bitwise OR of any NiFpga_CloseAttributes, or 0
 * @return result of the call
 */
NiFpga_Status NiFpga_Close(NiFpga_Session session,
                           uint32_t       attribute);

/**
 * @}
 */

/** \addtogroup Method
 *  @{
 */

/**
 * Attributes that NiFpga_Run accepts.
 */
typedef enum
{
   NiFpga_RunAttribute_WaitUntilDone = 1
} NiFpga_RunAttribute;

/**
 * Runs the FPGA VI on the target. If you use NiFpga_RunAttribute_WaitUntilDone,
 * NiFpga_Run blocks the thread until the FPGA finishes running.
 *
 * @param session handle to a currently open session
 * @param attribute bitwise OR of any NiFpga_RunAttributes, or 0
 * @return result of the call
 */
NiFpga_Status NiFpga_Run(NiFpga_Session session,
                         uint32_t       attribute);

/**
 * Aborts the FPGA VI.
 *
 * @param session handle to a currently open session
 * @return result of the call
 */
NiFpga_Status NiFpga_Abort(NiFpga_Session session);

/**
 * Resets the FPGA VI.
 *
 * @param session handle to a currently open session
 * @return result of the call
 */
NiFpga_Status NiFpga_Reset(NiFpga_Session session);

/**
 * Re-downloads the FPGA bitstream to the target.
 *
 * @param session handle to a currently open session
 * @return result of the call
 */
NiFpga_Status NiFpga_Download(NiFpga_Session session);

/**
 * @}
 */

/** \addtogroup Read
 *  @{
 */

/**
 * Reads a boolean value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadBool(NiFpga_Session session,
                              uint32_t       indicator,
                              NiFpga_Bool*   value);

/**
 * Reads a signed 8-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadI8(NiFpga_Session session,
                            uint32_t       indicator,
                            int8_t*        value);

/**
 * Reads an unsigned 8-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadU8(NiFpga_Session session,
                            uint32_t       indicator,
                            uint8_t*       value);

/**
 * Reads a signed 16-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadI16(NiFpga_Session session,
                             uint32_t       indicator,
                             int16_t*       value);

/**
 * Reads an unsigned 16-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadU16(NiFpga_Session session,
                             uint32_t       indicator,
                             uint16_t*      value);

/**
 * Reads a signed 32-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadI32(NiFpga_Session session,
                             uint32_t       indicator,
                             int32_t*       value);

/**
 * Reads an unsigned 32-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadU32(NiFpga_Session session,
                             uint32_t       indicator,
                             uint32_t*      value);

/**
 * Reads a signed 64-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadI64(NiFpga_Session session,
                             uint32_t       indicator,
                             int64_t*       value);

/**
 * Reads an unsigned 64-bit integer value from a given indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadU64(NiFpga_Session session,
                             uint32_t       indicator,
                             uint64_t*      value);

/**
 * Reads a single-precision floating-point value from a given indicator or
 * control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadSgl(NiFpga_Session session,
                             uint32_t       indicator,
                             float*         value);

/**
 * Reads a double-precision floating-point value from a given indicator or
 * control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param value outputs the value that was read
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadDbl(NiFpga_Session session,
                             uint32_t       indicator,
                             double*        value);

/**
 * @}
 */

/** \addtogroup Write
 *  @{
 */

/**
 * Writes a boolean value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteBool(NiFpga_Session session,
                               uint32_t       control,
                               NiFpga_Bool    value);

/**
 * Writes a signed 8-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteI8(NiFpga_Session session,
                             uint32_t       control,
                             int8_t         value);

/**
 * Writes an unsigned 8-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteU8(NiFpga_Session session,
                             uint32_t       control,
                             uint8_t        value);

/**
 * Writes a signed 16-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteI16(NiFpga_Session session,
                              uint32_t       control,
                              int16_t        value);

/**
 * Writes an unsigned 16-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteU16(NiFpga_Session session,
                              uint32_t       control,
                              uint16_t       value);

/**
 * Writes a signed 32-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteI32(NiFpga_Session session,
                              uint32_t       control,
                              int32_t        value);

/**
 * Writes an unsigned 32-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteU32(NiFpga_Session session,
                              uint32_t       control,
                              uint32_t       value);

/**
 * Writes a signed 64-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteI64(NiFpga_Session session,
                              uint32_t       control,
                              int64_t        value);

/**
 * Writes an unsigned 64-bit integer value to a given control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteU64(NiFpga_Session session,
                              uint32_t       control,
                              uint64_t       value);

/**
 * Writes a single-precision floating-point value to a given control or
 * indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteSgl(NiFpga_Session session,
                              uint32_t       control,
                              float          value);

/**
 * Writes a double-precision floating-point value to a given control or
 * indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param value value to write
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteDbl(NiFpga_Session session,
                              uint32_t       control,
                              double         value);

/**
 * @}
 */

/** \addtogroup ReadArray
 *  @{
 */

/**
 * Reads an entire array of boolean values from a given array indicator or
 * control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayBool(NiFpga_Session session,
                                   uint32_t       indicator,
                                   NiFpga_Bool*   array,
                                   size_t         size);

/**
 * Reads an entire array of signed 8-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayI8(NiFpga_Session session,
                                 uint32_t       indicator,
                                 int8_t*        array,
                                 size_t         size);

/**
 * Reads an entire array of unsigned 8-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayU8(NiFpga_Session session,
                                 uint32_t       indicator,
                                 uint8_t*       array,
                                 size_t         size);

/**
 * Reads an entire array of signed 16-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayI16(NiFpga_Session session,
                                  uint32_t       indicator,
                                  int16_t*       array,
                                  size_t         size);

/**
 * Reads an entire array of unsigned 16-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayU16(NiFpga_Session session,
                                  uint32_t       indicator,
                                  uint16_t*      array,
                                  size_t         size);

/**
 * Reads an entire array of signed 32-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayI32(NiFpga_Session session,
                                  uint32_t       indicator,
                                  int32_t*       array,
                                  size_t         size);

/**
 * Reads an entire array of unsigned 32-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayU32(NiFpga_Session session,
                                  uint32_t       indicator,
                                  uint32_t*      array,
                                  size_t         size);

/**
 * Reads an entire array of signed 64-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayI64(NiFpga_Session session,
                                  uint32_t       indicator,
                                  int64_t*       array,
                                  size_t         size);

/**
 * Reads an entire array of unsigned 64-bit integer values from a given array
 * indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayU64(NiFpga_Session session,
                                  uint32_t       indicator,
                                  uint64_t*      array,
                                  size_t         size);

/**
 * Reads an entire array of single-precision floating-point values from a
 * given array indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArraySgl(NiFpga_Session session,
                                  uint32_t       indicator,
                                  float*         array,
                                  size_t         size);

/**
 * Reads an entire array of double-precision floating-point values from a
 * given array indicator or control.
 *
 * @warning The size passed must be the exact number of elements in the
 *          indicator or control.
 *
 * @param session handle to a currently open session
 * @param indicator indicator or control from which to read
 * @param array outputs the entire array that was read
 * @param size exact number of elements in the indicator or control
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadArrayDbl(NiFpga_Session session,
                                  uint32_t       indicator,
                                  double*        array,
                                  size_t         size);

/**
 * @}
 */

/** \addtogroup WriteArray
 *  @{
 */

/**
 * Writes an entire array of boolean values to a given array control or
 * indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayBool(NiFpga_Session     session,
                                    uint32_t           control,
                                    const NiFpga_Bool* array,
                                    size_t             size);

/**
 * Writes an entire array of signed 8-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayI8(NiFpga_Session session,
                                  uint32_t       control,
                                  const int8_t*  array,
                                  size_t         size);

/**
 * Writes an entire array of unsigned 8-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayU8(NiFpga_Session session,
                                  uint32_t       control,
                                  const uint8_t* array,
                                  size_t         size);

/**
 * Writes an entire array of signed 16-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayI16(NiFpga_Session session,
                                   uint32_t       control,
                                   const int16_t* array,
                                   size_t         size);

/**
 * Writes an entire array of unsigned 16-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayU16(NiFpga_Session  session,
                                   uint32_t        control,
                                   const uint16_t* array,
                                   size_t          size);

/**
 * Writes an entire array of signed 32-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayI32(NiFpga_Session session,
                                   uint32_t       control,
                                   const int32_t* array,
                                   size_t         size);

/**
 * Writes an entire array of unsigned 32-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayU32(NiFpga_Session  session,
                                   uint32_t        control,
                                   const uint32_t* array,
                                   size_t          size);

/**
 * Writes an entire array of signed 64-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayI64(NiFpga_Session session,
                                   uint32_t       control,
                                   const int64_t* array,
                                   size_t         size);

/**
 * Writes an entire array of unsigned 64-bit integer values to a given array
 * control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayU64(NiFpga_Session  session,
                                   uint32_t        control,
                                   const uint64_t* array,
                                   size_t          size);

/**
 * Writes an entire array of single-precision floating-point values to a given
 * array control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArraySgl(NiFpga_Session session,
                                   uint32_t       control,
                                   const float*   array,
                                   size_t         size);

/**
 * Writes an entire array of double-precision floating-point values to a given
 * array control or indicator.
 *
 * @warning The size passed must be the exact number of elements in the
 *          control or indicator.
 *
 * @param session handle to a currently open session
 * @param control control or indicator to which to write
 * @param array entire array to write
 * @param size exact number of elements in the control or indicator
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteArrayDbl(NiFpga_Session session,
                                   uint32_t       control,
                                   const double*  array,
                                   size_t         size);

/**
 * @}
 */

/**
 * Represents an infinite timeout.
 */
static const uint32_t NiFpga_InfiniteTimeout = 0xFFFFFFFF;

/** \addtogroup Interrupt
 *  @{
 */

/**
 * Enumeration of all 32 possible IRQs. Multiple IRQs can be bitwise ORed
 * together like this:
 *
 *    NiFpga_Irq_3 | NiFpga_Irq_23
 */
typedef enum
{
   NiFpga_Irq_0  = 1 << 0,
   NiFpga_Irq_1  = 1 << 1,
   NiFpga_Irq_2  = 1 << 2,
   NiFpga_Irq_3  = 1 << 3,
   NiFpga_Irq_4  = 1 << 4,
   NiFpga_Irq_5  = 1 << 5,
   NiFpga_Irq_6  = 1 << 6,
   NiFpga_Irq_7  = 1 << 7,
   NiFpga_Irq_8  = 1 << 8,
   NiFpga_Irq_9  = 1 << 9,
   NiFpga_Irq_10 = 1 << 10,
   NiFpga_Irq_11 = 1 << 11,
   NiFpga_Irq_12 = 1 << 12,
   NiFpga_Irq_13 = 1 << 13,
   NiFpga_Irq_14 = 1 << 14,
   NiFpga_Irq_15 = 1 << 15,
   NiFpga_Irq_16 = 1 << 16,
   NiFpga_Irq_17 = 1 << 17,
   NiFpga_Irq_18 = 1 << 18,
   NiFpga_Irq_19 = 1 << 19,
   NiFpga_Irq_20 = 1 << 20,
   NiFpga_Irq_21 = 1 << 21,
   NiFpga_Irq_22 = 1 << 22,
   NiFpga_Irq_23 = 1 << 23,
   NiFpga_Irq_24 = 1 << 24,
   NiFpga_Irq_25 = 1 << 25,
   NiFpga_Irq_26 = 1 << 26,
   NiFpga_Irq_27 = 1 << 27,
   NiFpga_Irq_28 = 1 << 28,
   NiFpga_Irq_29 = 1 << 29,
   NiFpga_Irq_30 = 1 << 30,
   NiFpga_Irq_31 = 1U << 31
} NiFpga_Irq;

/**
 * See NiFpga_ReserveIrqContext for more information.
 */
typedef void* NiFpga_IrqContext;

/**
 * IRQ contexts are single-threaded; only one thread can wait with a
 * particular context at any given time. To minimize jitter when first
 * waiting on IRQs, reserve as many contexts as the application
 * requires.
 *
 * If a context is successfully reserved (the returned status is not an error),
 * it must be unreserved later. Otherwise a memory leak will occur.
 *
 * @param session handle to a currently open session
 * @param context outputs the IRQ context
 * @return result of the call
 */
NiFpga_Status NiFpga_ReserveIrqContext(NiFpga_Session     session,
                                       NiFpga_IrqContext* context);

/**
 * Unreserves an IRQ context obtained from NiFpga_ReserveIrqContext.
 *
 * @param session handle to a currently open session
 * @param context IRQ context to unreserve
 * @return result of the call
 */
NiFpga_Status NiFpga_UnreserveIrqContext(NiFpga_Session    session,
                                         NiFpga_IrqContext context);

/**
 * This is a blocking function that stops the calling thread until the
 * FPGA asserts any IRQ in the irqs parameter, or until the function
 * call times out. Before calling this function, use
 * NiFpga_ReserveIrqContext to reserve an IRQ context. No other
 * threads can use the same context when this function is called.
 *
 * You can use the irqsAsserted parameter to determine which IRQs were asserted
 * for each function call.
 *
 * @param session handle to a currently open session
 * @param context IRQ context with which to wait
 * @param irqs bitwise OR of NiFpga_Irqs
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param irqsAsserted if non-NULL, outputs bitwise OR of IRQs that were
 *                     asserted
 * @param timedOut if non-NULL, outputs whether the timeout expired
 * @return result of the call
 */
NiFpga_Status NiFpga_WaitOnIrqs(NiFpga_Session    session,
                                NiFpga_IrqContext context,
                                uint32_t          irqs,
                                uint32_t          timeout,
                                uint32_t*         irqsAsserted,
                                NiFpga_Bool*      timedOut);

/**
 * Acknowledges an IRQ or set of IRQs.
 *
 * @param session handle to a currently open session
 * @param irqs bitwise OR of NiFpga_Irqs
 * @return result of the call
 */
NiFpga_Status NiFpga_AcknowledgeIrqs(NiFpga_Session session,
                                     uint32_t       irqs);

/**
 * @}
 */

/** \addtogroup FifoMethod
 *  @{
 */

/**
 * Specifies the depth of the host memory part of the DMA FIFO. This method is
 * optional. In order to see the actual depth configured, use
 * NiFpga_ConfigureFifo2.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to configure
 * @param depth requested number of elements in the host memory part of the
 *              DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ConfigureFifo(NiFpga_Session session,
                                   uint32_t       fifo,
                                   size_t         depth);

/**
 * Specifies the depth of the host memory part of the DMA FIFO. This method is
 * optional.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to configure
 * @param requestedDepth requested number of elements in the host memory part
 *                       of the DMA FIFO
 * @param actualDepth if non-NULL, outputs the actual number of elements in the
 *                    host memory part of the DMA FIFO, which may be more than
 *                    the requested number
 * @return result of the call
 */
NiFpga_Status NiFpga_ConfigureFifo2(NiFpga_Session session,
                                    uint32_t       fifo,
                                    size_t         requestedDepth,
                                    size_t*        actualDepth);

/**
 * @}
 */

/** \addtogroup AdvancedFifoConfig
 *  @{
 */

/**
 * FIFO Properties are only supported by certain RIO devices and is not
 * supported on Pharlap or VxWorks.
 */
#if NiFpga_Linux || NiFpga_Windows || NiFpga_MacOsX
typedef enum
{
   /**
    * BytesPerElement
    *
    * Type: U32
    *
    * Specifies the number of bytes in a single element of the FIFO. Other
    * FIFO Buffer related properties are specified in number of elements, so
    * this property can be used to convert that number to a number of bytes.
    *
    * This property is only Getable and cannot be Set.
    */
   NiFpga_FifoProperty_BytesPerElement = 1,
   /**
    * HostBufferAllocationGranularity
    *
    * Type: U32
    *
    * Specifies the smallest discreet allocation unit that the HostBufferSize
    * will be coerced too. By default, this value will be set to the most
    * optimized setting for your hardware and system. This usually ends up
    * being the system's page size. The only valid values for this property
    * are powers of 2.
    */
   NiFpga_FifoProperty_HostBufferAllocationGranularity = 2,
   /**
    * HostBufferSize
    *
    * Type: U64
    *
    * The number of elements in the host memory part of the DMA FIFO. This size
    * will be coerced to be a multiple of the HostBufferAllocationGranularity.
    */
   NiFpga_FifoProperty_HostBufferSize = 3,
   /**
    * HostBufferMirrorSize
    *
    * Type: U64
    *
    * Specifies the number of elements mirrored at the end of the host memory
    * part of the DMA FIFO. By mirrored, we mean that the memory is mapped in
    * such a way that these elements point to the same physical memory as the
    * elements at the beginning of the host memory part of the DMA FIFO.
    *
    * Setting up memory like this improves use with the AcquireFifoElements API.
    * When using AcquireFifoElements, you can hit the end of the buffer and
    * recieve less elements than you attempted to acquire. This requires a
    * second AcquireFifoElements call to get the remaining elements.
    * Mirroring Elements avoids that second call.
    *
    * Example:
    * ========
    * **Behavior without Mirrored Elements**:
    *
    * This is a Target to Host FIFO of 10 elements:
    *
    *        0-1-2-3-4-5-6-7-8-9
    *        ^
    *        Current FIFO pointer here.
    *
    * 1. Acquire, use and Release 7 elements.
    *
    *        0-1-2-3-4-5-6-7-8-9
    *                      ^
    *                      Current FIFO pointer here.
    *
    * 2. The device writes to those 7 elements, filling up the FIFO.
    * 3. Attempt to acquire 7 elements, get back 3 because we can only give a
    *    pointer to 3 elements.
    *
    * **Behavior with Mirrored Elements**:
    *
    * If instead we had mirrored 4 elements, it would act like this.
    *
    *        0-1-2-3-4-5-6-7-8-9{0-1-2-3}
    *        ^                   ^mirrored elements
    *        Current FIFO pointer here.
    *
    * 1. Acquire, use and Release 7 elements.
    *
    *        0-1-2-3-4-5-6-7-8-9{0-1-2-3}
    *                      ^     ^mirrored elements
    *                      Current FIFO pointer here.
    *
    * 2. The device writes to those 7 elements, filling up the FIFO.
    * 3. Acquire, use and Release 7 elements. No problems are encountered
    *    because the driver gives back a pointer to the 7 elements requested.
    */
   NiFpga_FifoProperty_HostBufferMirrorSize = 4,
   /**
    * HostBufferType
    *
    * Type: I32
    *
    * Specifies the type of memory used in the host memory part of the DMA FIFO.
    * See NiFpga_HostBufferType for the valid values of this property.
    */
   NiFpga_FifoProperty_HostBufferType = 5,
   /**
    * HostBuffer
    *
    * Type: Ptr
    *
    * Specifies a pointer to the start of the host memory part of the DMA FIFO.
    * Can only be set if the HostBufferType is set to
    * NiFpga_HostBufferType_AllocatedByUser.
    *
    * Note, if the buffer is user supplied, the buffer will be pagelocked
    * by the driver. When the user has finished with the buffer, the user must
    * do one of the following before deallocating the buffer:
    * 1. Call NiFpga_Close on the NiFpga_Session
    * 2. Set the buffer type to NiFpga_HostBufferType_AllocatedByRIO and call
    *    NiFpga_CommitFifoConfiguration.
    * 3. Set the NiFpga_FifoProperty_HostBuffer to a different buffer.
    * 4. End the process.
    */
   NiFpga_FifoProperty_HostBuffer= 6,
   /**
    * FlowControl
    *
    * Type: I32
    *
    * Specifies the flow control behavior of the DMA FIFO.
    * See NiFpga_FifoFlowControl for specifics on the behaviors.
    * Note, changing the behavior of a FIFO can make it work in a non-"first in
    * first out" manner.
    */
   NiFpga_FifoProperty_FlowControl = 7,
   /**
    * ElementsCurrentlyAcquired
    *
    * Type: U64
    *
    * Specifies the number of elements that are currently acquired by the user
    * using the NiFpga_AcquireFifoReadElements* functions that have not yet
    * been released.
    *
    * This property is only Getable and cannot be Set.
    */
   NiFpga_FifoProperty_ElementsCurrentlyAcquired = 8
} NiFpga_FifoProperty;

typedef enum
{
   /**
    * Specifies that the DMA Buffer will be allocated by the NI-RIO driver
    * according to the options specified in the other FIFO properties.
    */
   NiFpga_HostBufferType_AllocatedByRIO = 1,
   /**
    * Specifies that the user has allocated the FIFO to the options specified
    * in the other FIFO properties. After setting this property, the user
    * should set NiFpga_FifoProperty_HostBuffer to their specified buffer.
    */
   NiFpga_HostBufferType_AllocatedByUser = 2
} NiFpga_HostBufferType;

typedef enum
{
   /**
    * When this option is specified, the FPGA will fully control data transfer
    * without any action from the host. FIFOs will no longer act in a first
    * in first out manner. It is up to the user to synchronize with the FPGA
    * and ensure coherent data.
    *
    * For Target To Host FIFOs, data will being transferring on StartFifo.
    * For Host To Target FIFOs, data will begin transferring when the entire
    * host part of the DMA FIFO has been written once. This is intended to
    * prevent the FPGA from reading garbage data from an uninitialized buffer
    * on the host.
    */
   NiFpga_FifoFlowControl_Disabled = 1,
   /**
    * This is the default options for FIFOs. When this option is specified,
    * FIFOs act with First In First Out behavior and no data is ever lost.
    * Data will stop transferring if the host memory part of the FIFO becomes
    * full rather than overwriting it.
    */
   NiFpga_FifoFlowControl_Enabled = 2
} NiFpga_FifoFlowControl;
#else
typedef enum
{
   NiFpga_FifoProperty_NotSupported
} NiFpga_FifoProperty;
#endif /* NiFpga_Linux || NiFpga_Windows || NiFpga_MacOsX */

/**
 * Sets the specified U32 FIFO property to the requested value. The specified
 * value may be coerced to a different value if nessessary. The FIFO must be
 * stopped before using this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to set
 * @param value the desired value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_SetFifoPropertyU32(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        uint32_t            value);

/**
 * Sets the specified I32 FIFO property to the requested value. The specified
 * value may be coerced to a different value if nessessary. The FIFO must be
 * stopped before using this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to set
 * @param value the desired value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_SetFifoPropertyI32(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        int32_t             value);

/**
 * Sets the specified U64 FIFO property to the requested value. The specified
 * value may be coerced to a different value if nessessary. The FIFO must be
 * stopped before using this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to set
 * @param value the desired value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_SetFifoPropertyU64(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        uint64_t            value);

/**
 * Sets the specified I64 FIFO property to the requested value. The specified
 * value may be coerced to a different value if nessessary. The FIFO must be
 * stopped before using this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to set
 * @param value the desired value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_SetFifoPropertyI64(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        int64_t             value);

/**
 * Sets the specified pointer FIFO property to the requested value. The
 * specified value may be coerced to a different value if nessessary. The FIFO
 * must be stopped before using this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to set
 * @param value the desired value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_SetFifoPropertyPtr(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        void*               value);

/**
 * Gets the value of the specified U32 FIFO property. The value returned may be
 * coerced from the value set. The value returned will be used by the FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to get
 * @param value the actual value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_GetFifoPropertyU32(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        uint32_t*           value);

/**
 * Gets the value of the specified I32 FIFO property. The value returned may be
 * coerced from the value set. The value returned will be used by the FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to get
 * @param value the actual value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_GetFifoPropertyI32(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        int32_t*            value);

/**
 * Gets the value of the specified U64 FIFO property. The value returned may be
 * coerced from the value set. The value returned will be used by the FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to get
 * @param value the actual value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_GetFifoPropertyU64(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        uint64_t*           value);

/**
 * Gets the value of the specified I64 FIFO property. The value returned may be
 * coerced from the value set. The value returned will be used by the FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to get
 * @param value the actual value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_GetFifoPropertyI64(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        int64_t*            value);

/**
 * Gets the value of the specified pointer FIFO property. The value returned may
 * be coerced from the value set. The value returned will be used by the FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to use
 * @param property NiFpga_FifoProperty to get
 * @param value the actual value of the property
 * @return result of the call
 */
NiFpga_Status NiFpga_GetFifoPropertyPtr(NiFpga_Session      session,
                                        uint32_t            fifo,
                                        NiFpga_FifoProperty property,
                                        void**              value);

/**
 * Commits the configuration of the FIFO. Resolves the host memory part of the
 * DMA FIFO and commits FIFO properties to the driver. The FIFO must be stopped
 * to call this function.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to commit configuration
 * @return result of the call
 */
NiFpga_Status NiFpga_CommitFifoConfiguration(NiFpga_Session session,
                                             uint32_t       fifo);
/**
 * @}
 */

/** \addtogroup FifoMethod
 *  @{
 */

/**
 * Starts a FIFO. This method is optional.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to start
 * @return result of the call
 */
NiFpga_Status NiFpga_StartFifo(NiFpga_Session session,
                               uint32_t       fifo);

/**
 * Stops a FIFO. This method is optional.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO to stop
 * @return result of the call
 */
NiFpga_Status NiFpga_StopFifo(NiFpga_Session session,
                              uint32_t       fifo);

/**
 * @}
 */

/** \addtogroup ReadFifo
 *  @{
 */

/**
 * Reads from a target-to-host FIFO of booleans.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoBool(NiFpga_Session session,
                                  uint32_t       fifo,
                                  NiFpga_Bool*   data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of signed 8-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoI8(NiFpga_Session session,
                                uint32_t       fifo,
                                int8_t*        data,
                                size_t         numberOfElements,
                                uint32_t       timeout,
                                size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of unsigned 8-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoU8(NiFpga_Session session,
                                uint32_t       fifo,
                                uint8_t*       data,
                                size_t         numberOfElements,
                                uint32_t       timeout,
                                size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of signed 16-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoI16(NiFpga_Session session,
                                 uint32_t       fifo,
                                 int16_t*       data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of unsigned 16-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoU16(NiFpga_Session session,
                                 uint32_t       fifo,
                                 uint16_t*      data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of signed 32-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoI32(NiFpga_Session session,
                                 uint32_t       fifo,
                                 int32_t*       data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of unsigned 32-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoU32(NiFpga_Session session,
                                 uint32_t       fifo,
                                 uint32_t*      data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of signed 64-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoI64(NiFpga_Session session,
                                 uint32_t       fifo,
                                 int64_t*       data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of unsigned 64-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoU64(NiFpga_Session session,
                                 uint32_t       fifo,
                                 uint64_t*      data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of single-precision floating-point values.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoSgl(NiFpga_Session session,
                                 uint32_t       fifo,
                                 float*         data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of double-precision floating-point values.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoDbl(NiFpga_Session session,
                                 uint32_t       fifo,
                                 double*        data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        elementsRemaining);

/**
 * Reads from a target-to-host FIFO of composite types such as clusters.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param data outputs the data that was read
 * @param bytesPerElement the size in bytes of each element
 * @param numberOfElements number of elements to read
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_ReadFifoComposite(NiFpga_Session session,
                                       uint32_t       fifo,
                                       void*          data,
                                       uint32_t       bytesPerElement,
                                       size_t         numberOfElements,
                                       uint32_t       timeout,
                                       size_t*        elementsRemaining);

/**
 * @}
 */

/** \addtogroup WriteFifo
 *  @{
 */

/**
 * Writes to a host-to-target FIFO of booleans.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoBool(NiFpga_Session     session,
                                   uint32_t           fifo,
                                   const NiFpga_Bool* data,
                                   size_t             numberOfElements,
                                   uint32_t           timeout,
                                   size_t*            emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of signed 8-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoI8(NiFpga_Session session,
                                 uint32_t       fifo,
                                 const int8_t*  data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of unsigned 8-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoU8(NiFpga_Session session,
                                 uint32_t       fifo,
                                 const uint8_t* data,
                                 size_t         numberOfElements,
                                 uint32_t       timeout,
                                 size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of signed 16-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoI16(NiFpga_Session session,
                                  uint32_t       fifo,
                                  const int16_t* data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of unsigned 16-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoU16(NiFpga_Session  session,
                                  uint32_t        fifo,
                                  const uint16_t* data,
                                  size_t          numberOfElements,
                                  uint32_t        timeout,
                                  size_t*         emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of signed 32-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoI32(NiFpga_Session session,
                                  uint32_t       fifo,
                                  const int32_t* data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of unsigned 32-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoU32(NiFpga_Session  session,
                                  uint32_t        fifo,
                                  const uint32_t* data,
                                  size_t          numberOfElements,
                                  uint32_t        timeout,
                                  size_t*         emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of signed 64-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoI64(NiFpga_Session session,
                                  uint32_t       fifo,
                                  const int64_t* data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of unsigned 64-bit integers.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoU64(NiFpga_Session  session,
                                  uint32_t        fifo,
                                  const uint64_t* data,
                                  size_t          numberOfElements,
                                  uint32_t        timeout,
                                  size_t*         emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of single-precision floating-point values.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoSgl(NiFpga_Session session,
                                  uint32_t       fifo,
                                  const float*   data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of double-precision floating-point values.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoDbl(NiFpga_Session session,
                                  uint32_t       fifo,
                                  const double*  data,
                                  size_t         numberOfElements,
                                  uint32_t       timeout,
                                  size_t*        emptyElementsRemaining);

/**
 * Writes to a host-to-target FIFO of composite types such as clusters.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param data data to write
 * @param bytesPerElement the size in bytes of each element
 * @param numberOfElements number of elements to write
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param emptyElementsRemaining if non-NULL, outputs the number of empty
 *                               elements remaining in the host memory part of
 *                               the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_WriteFifoComposite(NiFpga_Session session,
                                        uint32_t       fifo,
                                        const void*    data,
                                        uint32_t       bytesPerElement,
                                        size_t         numberOfElements,
                                        uint32_t       timeout,
                                        size_t*        emptyElementsRemaining);

/**
 * @}
 */

/** \addtogroup AcquireFifoRead
 *  @{
 */

/**
 * Acquires elements for reading from a target-to-host FIFO of booleans.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsBool(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             NiFpga_Bool**  elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of signed 8-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsI8(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             int8_t**       elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of unsigned 8-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsU8(
                                            NiFpga_Session  session,
                                            uint32_t        fifo,
                                            uint8_t**       elements,
                                            size_t          elementsRequested,
                                            uint32_t        timeout,
                                            size_t*         elementsAcquired,
                                            size_t*         elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of signed 16-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsI16(
                                            NiFpga_Session  session,
                                            uint32_t        fifo,
                                            int16_t**       elements,
                                            size_t          elementsRequested,
                                            uint32_t        timeout,
                                            size_t*         elementsAcquired,
                                            size_t*         elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of unsigned 16-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsU16(
                                           NiFpga_Session   session,
                                           uint32_t         fifo,
                                           uint16_t**       elements,
                                           size_t           elementsRequested,
                                           uint32_t         timeout,
                                           size_t*          elementsAcquired,
                                           size_t*          elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of signed 32-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsI32(
                                            NiFpga_Session  session,
                                            uint32_t        fifo,
                                            int32_t**       elements,
                                            size_t          elementsRequested,
                                            uint32_t        timeout,
                                            size_t*         elementsAcquired,
                                            size_t*         elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of unsigned 32-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsU32(
                                           NiFpga_Session   session,
                                           uint32_t         fifo,
                                           uint32_t**       elements,
                                           size_t           elementsRequested,
                                           uint32_t         timeout,
                                           size_t*          elementsAcquired,
                                           size_t*          elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of signed 64-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsI64(
                                            NiFpga_Session  session,
                                            uint32_t        fifo,
                                            int64_t**       elements,
                                            size_t          elementsRequested,
                                            uint32_t        timeout,
                                            size_t*         elementsAcquired,
                                            size_t*         elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of unsigned 64-bit
 * integers.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsU64(
                                           NiFpga_Session   session,
                                           uint32_t         fifo,
                                           uint64_t**       elements,
                                           size_t           elementsRequested,
                                           uint32_t         timeout,
                                           size_t*          elementsAcquired,
                                           size_t*          elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of single-precision
 * floating-point values.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsSgl(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             float**        elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for reading from a target-to-host FIFO of double-precision
 * floating-point values.
 *
 * Acquiring, reading, and releasing FIFO elements prevents the need to copy
 * the contents of elements from the host memory buffer to a separate
 * user-allocated buffer before reading. The FPGA target cannot write to
 * elements acquired by the host. Therefore, the host must release elements
 * after reading them. The number of elements acquired may differ from the
 * number of elements requested if, for example, the number of elements
 * requested reaches the end of the host memory buffer. Always release all
 * acquired elements before closing the session. Do not attempt to access FIFO
 * elements after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo target-to-host FIFO from which to read
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoReadElementsDbl(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             double**       elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * @}
 */

/** \addtogroup AcquireFifoWrite
 *  @{
 */

/**
 * Acquires elements for writing to a host-to-target FIFO of booleans.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsBool(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             NiFpga_Bool**  elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of signed 8-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsI8(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             int8_t**       elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of unsigned 8-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsU8(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             uint8_t**      elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of signed 16-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsI16(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             int16_t**      elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of unsigned 16-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsU16(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             uint16_t**     elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of signed 32-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsI32(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             int32_t**      elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of unsigned 32-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsU32(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             uint32_t**     elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of signed 64-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsI64(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             int64_t**      elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of unsigned 64-bit
 * integers.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsU64(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             uint64_t**     elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of single-precision
 * floating-point values.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsSgl(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             float**        elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * Acquires elements for writing to a host-to-target FIFO of single-precision
 * floating-point values.
 *
 * Acquiring, writing, and releasing FIFO elements prevents the need to write
 * first into a separate user-allocated buffer and then copy the contents of
 * elements to the host memory buffer. The FPGA target cannot read elements
 * acquired by the host. Therefore, the host must release elements after
 * writing to them. The number of elements acquired may differ from the number
 * of elements requested if, for example, the number of elements requested
 * reaches the end of the host memory buffer. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo host-to-target FIFO to which to write
 * @param elements outputs a pointer to the elements acquired
 * @param elementsRequested requested number of elements
 * @param timeout timeout in milliseconds, or NiFpga_InfiniteTimeout
 * @param elementsAcquired actual number of elements acquired, which may be
 *                         less than the requested number
 * @param elementsRemaining if non-NULL, outputs the number of elements
 *                          remaining in the host memory part of the DMA FIFO
 * @return result of the call
 */
NiFpga_Status NiFpga_AcquireFifoWriteElementsDbl(
                                             NiFpga_Session session,
                                             uint32_t       fifo,
                                             double**       elements,
                                             size_t         elementsRequested,
                                             uint32_t       timeout,
                                             size_t*        elementsAcquired,
                                             size_t*        elementsRemaining);

/**
 * @}
 */

/** \addtogroup FifoMethod
 *  @{
 */

/**
 * Releases previously acquired FIFO elements.
 *
 * The FPGA target cannot read elements acquired by the host. Therefore, the
 * host must release elements after acquiring them. Always release all acquired
 * elements before closing the session. Do not attempt to access FIFO elements
 * after the elements are released or the session is closed.
 *
 * @param session handle to a currently open session
 * @param fifo FIFO from which to release elements
 * @param elements number of elements to release
 * @return result of the call
 */
NiFpga_Status NiFpga_ReleaseFifoElements(NiFpga_Session session,
                                         uint32_t       fifo,
                                         size_t         elements);

/**
 * Gets an endpoint reference to a peer-to-peer FIFO.
 *
 * @param session handle to a currently open session
 * @param fifo peer-to-peer FIFO
 * @param endpoint Outputs the endpoint reference.
 *                 The actual type is a nip2p_tEndpointHandle usable by
 *                 the NI Peer-to-Peer Streaming C/C++ API.
 * @return result of the call
 */
NiFpga_Status NiFpga_GetPeerToPeerFifoEndpoint(NiFpga_Session session,
                                               uint32_t       fifo,
                                               uint32_t*      endpoint);

/**
 * @}
 */

#if NiFpga_Cpp
}
#endif

#endif
