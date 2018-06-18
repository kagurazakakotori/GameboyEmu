#pragma once
#include <array>
#include <functional>
#include <ios>
#include <iostream>
#include "Common.h"
#include "Memory.h"

namespace gb
{

class CPU
{
public:
    int cycle;

    CPU(Memory& _memory);

    void init();
    void exec();

    void handleInterrupt();

private:
    static const int FLAG_Z = 7;  // Zero Flag
    static const int FLAG_N = 6;  // Add/Sub-Flag
    static const int FLAG_H = 5;  // Half Carry Flag
    static const int FLAG_C = 4;  // Carry

    Memory& memory;

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

    bool interruptMasterEnable = false;
    bool halt                  = false;

    void serviceInterrupt(const int& interruptType);

    // Flag register operations
    inline bool getFlag(int bit);
    inline void setFlag(int bit, bool value);

    // Opcode interpreter assist functions
    // using _ prefix to avoid misusing
    void _add(const byte& value);
    void _adc(const byte& value);
    void _sub(const byte& value);
    void _sbc(const byte& value);
    void _and(const byte& value);
    void _or(const byte& value);
    void _xor(const byte& value);
    void _cp(const byte& value);
    void _inc(byte& target);
    void _dec(byte& target);
    void _addhl(const word& value);
    void _rlc(byte& target);
    void _rl(byte& target);
    void _rrc(byte& target);
    void _rr(byte& target);
    void _sla(byte& target);
    void _sra(byte& target);
    void _srl(byte& target);
    void _swap(byte& target);
    void _bit(const int& bit, const byte& target);
    void _daa();

    std::array<std::function<int()>, 0x100> opcode;  // Instructions set
    std::array<std::function<int()>, 0x100> cbcode;  // CB-prefix instructions set

    void loadOpcode();
    void loadCbcode();
};

}  // namespace gb