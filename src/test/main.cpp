#include "FRC_NetworkCommunication/FRCComm.h"
#include "FRC_NetworkCommunication/LoadOut.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#include "FRC_FPGA_ChipObject/RoboRIO_FRC_ChipObject_Aliases.h"
#include "FRC_FPGA_ChipObject/nRoboRIO_FPGANamespace/tGlobal.h"
#include "FRC_FPGA_ChipObject/nRoboRIO_FPGANamespace/nInterfaceGlobals.h"
#pragma GCC diagnostic pop
#include <stdio.h>
#include "FRC_FPGA_ChipObject/printFpgaVersion.h"
#include "visa/visa.h"

int main () {
    FRC_NetworkCommunication_Reserve(nullptr);
    nFPGA::nRoboRIO_FPGANamespace::g_currentTargetClass = FRC_NetworkCommunication_nLoadOut_getTargetClass();
    tRioStatusCode status = 0;
    auto global = nFPGA::nRoboRIO_FPGANamespace::tGlobal::create(&status);
    nFPGA::printFPGAVersion(*global);

    int32_t resourceHandle;
    viOpenDefaultRM(reinterpret_cast<ViSession*>(&resourceHandle));

    viClose(resourceHandle);
}
