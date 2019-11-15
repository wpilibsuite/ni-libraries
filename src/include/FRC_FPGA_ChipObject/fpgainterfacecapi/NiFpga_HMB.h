#ifndef __NiFpga_HMB_h__
#define __NiFpga_HMB_h__

#include "fpgainterfacecapi/NiFpga.h"

#if NiFpga_Cpp
extern "C"
{
#endif

/**
 * Open a host memory buffer.
 *
 * @param session [in] handle to a currently open session
 * @param memoryName [in] name of the HMB memory configured in the project
 * @param virtualAddress [out] virtual address that the host will use to access the memory
 * @param size [out] size in bytes of the memory area
 * @return result of the call
 */
NiFpga_Status NiFpga_OpenHostMemoryBuffer(NiFpga_Session session,
                                          const char* memoryName,
                                          void** virtualAddress,
                                          size_t* size);

#if NiFpga_Cpp
}
#endif

#endif
