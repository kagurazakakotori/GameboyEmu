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
    static const int FLAG_Z = 7;  // Zero Flag
    static const int FLAG_N = 6;  // Add/Sub-Flag
    static const int FLAG_H = 5;  // Half Carry Flag
    static const int FLAG_C = 4;  // Carry

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

    // Flag register operations
    bool getFlag(int bit);
    void setFlag(int bit, bool value);

    std::array<std::function<int()>, 0x100> opcode;  // Instructions set
    std::array<std::function<int()>, 0x100> cbcode;  // CB-prefix instructions set

    void loadOpcode();
    void loadCbcode();
};

}  // namespace Gameboy