#include <SDL.h>

#include "core/psxemulator.h"
#include "core/r3000a.h"
#include "gui/gui.h"

class SystemImpl : public PCSX::System {
    virtual void SysPrintf(const char *fmt, ...) final {
        // print message to debugging console
        va_list a;
        va_start(a, fmt);
        vprintf(fmt, a);
        va_end(a);
    }

    virtual void SysBiosPrintf(const char *fmt, ...) final {
        // print message to debugging console
        va_list a;
        va_start(a, fmt);
        vprintf(fmt, a);
        va_end(a);
    }

    virtual void SysBiosPrintf(const char *fmt, va_list a) final {
        // print message to debugging console
        vprintf(fmt, a);
    }

    virtual void SysMessage(const char *fmt, ...) final {
        // display message to user as a pop-up
        va_list a;
        va_start(a, fmt);
        vprintf(fmt, a);
        va_end(a);
    }

    virtual void SysLog(const char *facility, const char *fmt, va_list a) final {
        vprintf(fmt, a);
    }

    virtual void SysUpdate() final {
        // called on vblank to update states
        GUI_flip();
    }

    virtual void SysRunGui() final {
        // called when the UI needs to show up
    }

    virtual void SysReset() final {
        // debugger is requesting a reset
    }

    virtual void SysClose() final {
        // emulator is requesting a shutdown of the emulation
    }
};

int main(int argc, char *argv[]) {
    unsigned int texture = GUI_init();
    PCSX::Emulator emulator;

    PCSX::system = new SystemImpl;

    emulator.config().PsxAuto = true;
    emulator.config().HLE = false;
    emulator.config().SlowBoot = false;
    emulator.config().BiosDir = ".";
    emulator.config().Bios = "bios.bin";
    emulator.config().Cpu = PCSX::Emulator::CPU_DYNAREC;

    SetIsoFile("test.img");
    LoadPlugins();

    emulator.EmuInit();
    emulator.EmuReset();

    GPU_open(texture);
    CDR_open();
    CheckCdrom();
    LoadCdrom();

    PCSX::g_emulator->m_psxCpu->Execute();

    return 0;
}
