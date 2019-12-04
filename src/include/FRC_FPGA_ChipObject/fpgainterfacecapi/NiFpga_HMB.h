#pragma once
#include "fpgainterfacecapi/NiFpga.h"

#ifdef __cplusplus
extern "C" {
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

#ifdef __cplusplus
}
#endif
