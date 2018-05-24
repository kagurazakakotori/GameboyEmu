#pragma once
#include <array>
#include <functional>
#include "DataType.h"
#include "Memory.h"

namespace Gameboy
{
extern Memory memory;

class CPU
{
public:
    void init();

private:
    struct Register
    {
        union
        {
            struct
            {
                byte f;
                byte a;
            };
            word af;
        };

        union
        {
            struct
            {
                byte c;
                byte b;
            };
            word bc;
        };

        union
        {
            struct
            {
                byte e;
                byte d;
            };
            word de;
        };

        union
        {
            struct
            {
                byte l;
                byte h;
            };
            word hl;
        };

        word sp;
        word pc;
    } reg;

    std::array<std::function<int()>, 0x100> opcode;  // Instructions set
    std::array<std::function<int()>, 0x100> cbcode;  // CB-prefix instructions set

    void loadOpcode();
    void loadCbcode();
};

}  // namespace Gameboy