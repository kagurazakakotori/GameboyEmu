#include "CPU.h"

namespace gb
{

inline bool CPU::getFlag(int bit)
{
    return getBit(reg.f, bit);
}

inline void CPU::setFlag(int bit, bool value)
{
    setBit(reg.f, bit, value);
}

void CPU::loadOpcode()
{
    // Opcode returns the clock cycles of a command
    // Initialize Opcodes
    for (auto&& i : opcode) {
        i = [&]() -> int { return 4; };
    }

    // CB code mapping
    opcode[0xcb] = [&]() -> int { uint8_t value = memory.readByte(reg.pc++); return cbcode[value](); };

    // Assign Opcode functions
    // LD nn,n
    opcode[0x06] = [&]() -> int { reg.b = memory.readByte(reg.pc); reg.pc++; return 8; };
    opcode[0x0e] = [&]() -> int { reg.c = memory.readByte(reg.pc); reg.pc++; return 8; };
    opcode[0x16] = [&]() -> int { reg.d = memory.readByte(reg.pc); reg.pc++; return 8; };
    opcode[0x1e] = [&]() -> int { reg.e = memory.readByte(reg.pc); reg.pc++; return 8; };
    opcode[0x26] = [&]() -> int { reg.h = memory.readByte(reg.pc); reg.pc++; return 8; };
    opcode[0x2e] = [&]() -> int { reg.l = memory.readByte(reg.pc); reg.pc++; return 8; };

    // LD r1,r2
    opcode[0x40] = [&]() -> int { reg.b = reg.b; return 4; };
    opcode[0x41] = [&]() -> int { reg.b = reg.c; return 4; };
    opcode[0x42] = [&]() -> int { reg.b = reg.d; return 4; };
    opcode[0x43] = [&]() -> int { reg.b = reg.e; return 4; };
    opcode[0x44] = [&]() -> int { reg.b = reg.h; return 4; };
    opcode[0x45] = [&]() -> int { reg.b = reg.l; return 4; };
    opcode[0x46] = [&]() -> int { reg.b = memory.readByte(reg.hl); return 8; };
    opcode[0x48] = [&]() -> int { reg.c = reg.b; return 4; };
    opcode[0x49] = [&]() -> int { reg.c = reg.c; return 4; };
    opcode[0x4a] = [&]() -> int { reg.c = reg.d; return 4; };
    opcode[0x4b] = [&]() -> int { reg.c = reg.e; return 4; };
    opcode[0x4c] = [&]() -> int { reg.c = reg.h; return 4; };
    opcode[0x4d] = [&]() -> int { reg.c = reg.l; return 4; };
    opcode[0x4e] = [&]() -> int { reg.c = memory.readByte(reg.hl); return 8; };
    opcode[0x50] = [&]() -> int { reg.d = reg.b; return 4; };
    opcode[0x51] = [&]() -> int { reg.d = reg.c; return 4; };
    opcode[0x52] = [&]() -> int { reg.d = reg.d; return 4; };
    opcode[0x53] = [&]() -> int { reg.d = reg.e; return 4; };
    opcode[0x54] = [&]() -> int { reg.d = reg.h; return 4; };
    opcode[0x55] = [&]() -> int { reg.d = reg.l; return 4; };
    opcode[0x56] = [&]() -> int { reg.d = memory.readByte(reg.hl); return 8; };
    opcode[0x58] = [&]() -> int { reg.e = reg.b; return 4; };
    opcode[0x59] = [&]() -> int { reg.e = reg.c; return 4; };
    opcode[0x5a] = [&]() -> int { reg.e = reg.d; return 4; };
    opcode[0x5b] = [&]() -> int { reg.e = reg.e; return 4; };
    opcode[0x5c] = [&]() -> int { reg.e = reg.h; return 4; };
    opcode[0x5d] = [&]() -> int { reg.e = reg.l; return 4; };
    opcode[0x5e] = [&]() -> int { reg.e = memory.readByte(reg.hl); return 8; };
    opcode[0x60] = [&]() -> int { reg.h = reg.b; return 4; };
    opcode[0x61] = [&]() -> int { reg.h = reg.c; return 4; };
    opcode[0x62] = [&]() -> int { reg.h = reg.d; return 4; };
    opcode[0x63] = [&]() -> int { reg.h = reg.e; return 4; };
    opcode[0x64] = [&]() -> int { reg.h = reg.h; return 4; };
    opcode[0x65] = [&]() -> int { reg.h = reg.l; return 4; };
    opcode[0x66] = [&]() -> int { reg.h = memory.readByte(reg.hl); return 8; };
    opcode[0x68] = [&]() -> int { reg.l = reg.b; return 4; };
    opcode[0x69] = [&]() -> int { reg.l = reg.c; return 4; };
    opcode[0x6a] = [&]() -> int { reg.l = reg.d; return 4; };
    opcode[0x6b] = [&]() -> int { reg.l = reg.e; return 4; };
    opcode[0x6c] = [&]() -> int { reg.l = reg.h; return 4; };
    opcode[0x6d] = [&]() -> int { reg.l = reg.l; return 4; };
    opcode[0x6e] = [&]() -> int { reg.l = memory.readByte(reg.hl); return 8; };
    opcode[0x70] = [&]() -> int { memory.writeByte(reg.hl, reg.b); return 8; };
    opcode[0x71] = [&]() -> int { memory.writeByte(reg.hl, reg.c); return 8; };
    opcode[0x72] = [&]() -> int { memory.writeByte(reg.hl, reg.d); return 8; };
    opcode[0x73] = [&]() -> int { memory.writeByte(reg.hl, reg.e); return 8; };
    opcode[0x74] = [&]() -> int { memory.writeByte(reg.hl, reg.h); return 8; };
    opcode[0x75] = [&]() -> int { memory.writeByte(reg.hl, reg.l); return 8; };
    opcode[0x36] = [&]() -> int { memory.writeByte(reg.hl, memory.readByte(reg.pc)); reg.pc++; return 12; };

    // LD A,n
    opcode[0x7f] = [&]() -> int { reg.a = reg.a; return 4; };
    opcode[0x78] = [&]() -> int { reg.a = reg.b; return 4; };
    opcode[0x79] = [&]() -> int { reg.a = reg.c; return 4; };
    opcode[0x7a] = [&]() -> int { reg.a = reg.d; return 4; };
    opcode[0x7b] = [&]() -> int { reg.a = reg.e; return 4; };
    opcode[0x7c] = [&]() -> int { reg.a = reg.h; return 4; };
    opcode[0x7d] = [&]() -> int { reg.a = reg.l; return 4; };
    opcode[0x0a] = [&]() -> int { reg.a = memory.readByte(reg.bc); return 8; };
    opcode[0x1a] = [&]() -> int { reg.a = memory.readByte(reg.de); return 8; };
    opcode[0x7e] = [&]() -> int { reg.a = memory.readByte(reg.hl); return 8; };
    opcode[0xfa] = [&]() -> int { reg.a = memory.readByte(memory.readWord(reg.pc)); reg.pc += 2; return 16; };
    opcode[0x3e] = [&]() -> int { reg.a = memory.readByte(reg.pc); reg.pc++; return 8; };

    // LD n,A
    opcode[0x47] = [&]() -> int { reg.b = reg.a; return 4; };
    opcode[0x4f] = [&]() -> int { reg.c = reg.a; return 4; };
    opcode[0x57] = [&]() -> int { reg.d = reg.a; return 4; };
    opcode[0x5f] = [&]() -> int { reg.e = reg.a; return 4; };
    opcode[0x67] = [&]() -> int { reg.h = reg.a; return 4; };
    opcode[0x6f] = [&]() -> int { reg.l = reg.a; return 4; };
    opcode[0x02] = [&]() -> int { memory.writeByte(reg.bc, reg.a); return 8; };
    opcode[0x12] = [&]() -> int { memory.writeByte(reg.de, reg.a); return 8; };
    opcode[0x77] = [&]() -> int { memory.writeByte(reg.hl, reg.a); return 8; };
    opcode[0xea] = [&]() -> int { memory.writeByte(memory.readWord(reg.pc), reg.a); reg.pc += 2; return 16; };

    // LD A,(C)
    opcode[0xf2] = [&]() -> int { reg.a = memory.readByte(0xff00 + reg.c) ; return 8; };

    // LD (C),A
    opcode[0xe2] = [&]() -> int { memory.writeByte(0xff00 + reg.c, reg.a) ; return 8; };

    // LD A,(HL-)
    opcode[0x3a] = [&]() -> int { reg.a = memory.readByte(reg.hl); reg.hl--; return 8; };

    // LD (HL-),A
    opcode[0x32] = [&]() -> int { memory.writeByte(reg.hl, reg.a); reg.hl--; return 8; };

    // LD A,(HL+)
    opcode[0x2a] = [&]() -> int { reg.a = memory.readByte(reg.hl); reg.hl++; return 8; };

    // LD (HL+),A
    opcode[0x22] = [&]() -> int { memory.writeByte(reg.hl, reg.a); reg.hl++; return 8; };

    // LDH (n),A
    opcode[0xe0] = [&]() -> int { memory.writeByte(0xff00 + memory.readByte(reg.pc), reg.a); reg.pc++; return 12; };

    // LDH A,(n)
    opcode[0xf0] = [&]() -> int { reg.a = memory.readByte(0xff00 + memory.readByte(reg.pc)); reg.pc++; return 12; };

    // LD n,nn
    opcode[0x01] = [&]() -> int { reg.bc = memory.readWord(reg.pc); reg.pc += 2; return 12; };
    opcode[0x11] = [&]() -> int { reg.de = memory.readWord(reg.pc); reg.pc += 2; return 12; };
    opcode[0x21] = [&]() -> int { reg.hl = memory.readWord(reg.pc); reg.pc += 2; return 12; };
    opcode[0x31] = [&]() -> int { reg.sp = memory.readWord(reg.pc); reg.pc += 2; return 12; };

    // LD SP,HL
    opcode[0xf9] = [&]() -> int { reg.sp = reg.hl; return 8; };

    // LD HL,SP+e(signed int8)
    opcode[0xf8] = [&]() -> int { 
        int16_t e = static_cast<int8_t>(memory.readByte(reg.pc));
        reg.pc++;
        word result = reg.sp + e;
        setFlag(FLAG_Z, 0);
        setFlag(FLAG_N, 0);
        setFlag(FLAG_H, (((reg.sp & 0xfff) + (e & 0xfff)) & 0x1000));
        setFlag(FLAG_C, (((reg.sp & 0xffff) + (e & 0xffff)) & 0x10000));
        reg.hl = result;
        return 12; };

    // LD (nn),SP
    opcode[0x08] = [&]() -> int { memory.writeWord(reg.pc, reg.sp); reg.pc += 2; return 20; };

    // PUSH nn
    opcode[0xf5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.a); reg.sp--; memory.writeByte(reg.sp, reg.f); return 16; };
    opcode[0xc5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.b); reg.sp--; memory.writeByte(reg.sp, reg.c); return 16; };
    opcode[0xd5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.d); reg.sp--; memory.writeByte(reg.sp, reg.e); return 16; };
    opcode[0xe5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.h); reg.sp--; memory.writeByte(reg.sp, reg.l); return 16; };

    // POP nn
    // The lower 4 bit of reg.f can't be written
    opcode[0xf1] = [&]() -> int { reg.f = (memory.readByte(reg.sp) & 0xf0); reg.sp++; reg.a = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xc1] = [&]() -> int { reg.c = memory.readByte(reg.sp); reg.sp++; reg.b = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xd1] = [&]() -> int { reg.e = memory.readByte(reg.sp); reg.sp++; reg.d = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xe1] = [&]() -> int { reg.l = memory.readByte(reg.sp); reg.sp++; reg.h = memory.readByte(reg.sp); reg.sp++; return 12; };

    // ADD A,n
    opcode[0x87] = [&]() -> int { _add(reg.a); return 4; };
    opcode[0x80] = [&]() -> int { _add(reg.b); return 4; };
    opcode[0x81] = [&]() -> int { _add(reg.c); return 4; };
    opcode[0x82] = [&]() -> int { _add(reg.d); return 4; };
    opcode[0x83] = [&]() -> int { _add(reg.e); return 4; };
    opcode[0x84] = [&]() -> int { _add(reg.h); return 4; };
    opcode[0x85] = [&]() -> int { _add(reg.l); return 4; };
    opcode[0x86] = [&]() -> int { _add(memory.readByte(reg.hl)); return 8; };
    opcode[0xc6] = [&]() -> int { _add(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // ADC A,n
    opcode[0x8f] = [&]() -> int { _adc(reg.a); return 4; };
    opcode[0x88] = [&]() -> int { _adc(reg.b); return 4; };
    opcode[0x89] = [&]() -> int { _adc(reg.c); return 4; };
    opcode[0x8a] = [&]() -> int { _adc(reg.d); return 4; };
    opcode[0x8b] = [&]() -> int { _adc(reg.e); return 4; };
    opcode[0x8c] = [&]() -> int { _adc(reg.h); return 4; };
    opcode[0x8d] = [&]() -> int { _adc(reg.l); return 4; };
    opcode[0x8e] = [&]() -> int { _adc(memory.readByte(reg.hl)); return 8; };
    opcode[0xce] = [&]() -> int { _adc(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // SUB A,n
    opcode[0x97] = [&]() -> int { _sub(reg.a); return 4; };
    opcode[0x90] = [&]() -> int { _sub(reg.b); return 4; };
    opcode[0x91] = [&]() -> int { _sub(reg.c); return 4; };
    opcode[0x92] = [&]() -> int { _sub(reg.d); return 4; };
    opcode[0x93] = [&]() -> int { _sub(reg.e); return 4; };
    opcode[0x94] = [&]() -> int { _sub(reg.h); return 4; };
    opcode[0x95] = [&]() -> int { _sub(reg.l); return 4; };
    opcode[0x96] = [&]() -> int { _sub(memory.readByte(reg.hl)); return 8; };
    opcode[0xd6] = [&]() -> int { _sub(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // AND n
    opcode[0xa7] = [&]() -> int { _and(reg.a); return 4; };
    opcode[0xa0] = [&]() -> int { _and(reg.b); return 4; };
    opcode[0xa1] = [&]() -> int { _and(reg.c); return 4; };
    opcode[0xa2] = [&]() -> int { _and(reg.d); return 4; };
    opcode[0xa3] = [&]() -> int { _and(reg.e); return 4; };
    opcode[0xa4] = [&]() -> int { _and(reg.h); return 4; };
    opcode[0xa5] = [&]() -> int { _and(reg.l); return 4; };
    opcode[0xa6] = [&]() -> int { _and(memory.readByte(reg.hl)); return 8; };
    opcode[0xe6] = [&]() -> int { _and(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // OR n
    opcode[0xb7] = [&]() -> int { _or(reg.a); return 4; };
    opcode[0xb0] = [&]() -> int { _or(reg.b); return 4; };
    opcode[0xb1] = [&]() -> int { _or(reg.c); return 4; };
    opcode[0xb2] = [&]() -> int { _or(reg.d); return 4; };
    opcode[0xb3] = [&]() -> int { _or(reg.e); return 4; };
    opcode[0xb4] = [&]() -> int { _or(reg.h); return 4; };
    opcode[0xb5] = [&]() -> int { _or(reg.l); return 4; };
    opcode[0xb6] = [&]() -> int { _or(memory.readByte(reg.hl)); return 8; };
    opcode[0xf6] = [&]() -> int { _or(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // XOR n
    opcode[0xaf] = [&]() -> int { _xor(reg.a); return 4; };
    opcode[0xa8] = [&]() -> int { _xor(reg.b); return 4; };
    opcode[0xa9] = [&]() -> int { _xor(reg.c); return 4; };
    opcode[0xaa] = [&]() -> int { _xor(reg.d); return 4; };
    opcode[0xab] = [&]() -> int { _xor(reg.e); return 4; };
    opcode[0xac] = [&]() -> int { _xor(reg.h); return 4; };
    opcode[0xad] = [&]() -> int { _xor(reg.l); return 4; };
    opcode[0xae] = [&]() -> int { _xor(memory.readByte(reg.hl)); return 8; };
    opcode[0xee] = [&]() -> int { _xor(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // CP n
    opcode[0xbf] = [&]() -> int { _cp(reg.a); return 4; };
    opcode[0xb8] = [&]() -> int { _cp(reg.b); return 4; };
    opcode[0xb9] = [&]() -> int { _cp(reg.c); return 4; };
    opcode[0xba] = [&]() -> int { _cp(reg.d); return 4; };
    opcode[0xbb] = [&]() -> int { _cp(reg.e); return 4; };
    opcode[0xbc] = [&]() -> int { _cp(reg.h); return 4; };
    opcode[0xbd] = [&]() -> int { _cp(reg.l); return 4; };
    opcode[0xbe] = [&]() -> int { _cp(memory.readByte(reg.hl)); return 8; };
    opcode[0xfe] = [&]() -> int { _cp(memory.readByte(reg.pc)); reg.pc++; return 8; };

    // INC n
    opcode[0x3c] = [&]() -> int { _inc(reg.a); return 4; };
    opcode[0x04] = [&]() -> int { _inc(reg.b); return 4; };
    opcode[0x0c] = [&]() -> int { _inc(reg.c); return 4; };
    opcode[0x14] = [&]() -> int { _inc(reg.d); return 4; };
    opcode[0x1c] = [&]() -> int { _inc(reg.e); return 4; };
    opcode[0x24] = [&]() -> int { _inc(reg.h); return 4; };
    opcode[0x2c] = [&]() -> int { _inc(reg.l); return 4; };
    opcode[0x34] = [&]() -> int { byte value = memory.readByte(reg.hl); _inc(value); memory.writeByte(reg.hl, value); return 12; };

    // DEC n
    opcode[0x3d] = [&]() -> int { _dec(reg.a); return 4; };
    opcode[0x05] = [&]() -> int { _dec(reg.b); return 4; };
    opcode[0x0d] = [&]() -> int { _dec(reg.c); return 4; };
    opcode[0x15] = [&]() -> int { _dec(reg.d); return 4; };
    opcode[0x1d] = [&]() -> int { _dec(reg.e); return 4; };
    opcode[0x25] = [&]() -> int { _dec(reg.h); return 4; };
    opcode[0x2d] = [&]() -> int { _dec(reg.l); return 4; };
    opcode[0x35] = [&]() -> int { byte value = memory.readByte(reg.hl); _dec(value); memory.writeByte(reg.hl, value); return 12; };

    // ADD HL,n
    opcode[0x09] = [&]() -> int { _addhl(reg.bc); return 8; };
    opcode[0x19] = [&]() -> int { _addhl(reg.de); return 8; };
    opcode[0x29] = [&]() -> int { _addhl(reg.hl); return 8; };
    opcode[0x39] = [&]() -> int { _addhl(reg.sp); return 8; };

    // ADD SP,e
    opcode[0xe8] = [&]() -> int {
        int16_t e = static_cast<int8_t>(memory.readByte(reg.pc));
        reg.pc++;
        word result = reg.sp + e;
        setFlag(FLAG_Z, 0);
        setFlag(FLAG_N, 0);
        setFlag(FLAG_H, (((reg.sp & 0xfff) + (e & 0xfff)) & 0x1000));
        setFlag(FLAG_C, (((reg.sp & 0xffff) + (e & 0xffff)) & 0x10000));
        reg.sp = result; 
        return 16; };

    // INC nn
    opcode[0x03] = [&]() -> int { reg.bc++; return 8; };
    opcode[0x13] = [&]() -> int { reg.de++; return 8; };
    opcode[0x23] = [&]() -> int { reg.hl++; return 8; };
    opcode[0x33] = [&]() -> int { reg.sp++; return 8; };

    // DEC nn
    opcode[0x0b] = [&]() -> int { reg.bc--; return 8; };
    opcode[0x1b] = [&]() -> int { reg.de--; return 8; };
    opcode[0x2b] = [&]() -> int { reg.hl--; return 8; };
    opcode[0x3b] = [&]() -> int { reg.sp--; return 8; };

    // RLCA
    opcode[0x07] = [&]() -> int { _rlc(reg.a); return 4; };

    // RLA
    opcode[0x17] = [&]() -> int { _rl(reg.a); return 4; };

    // RRCA
    opcode[0x0f] = [&]() -> int { _rrc(reg.a); return 4; };

    // RRA
    opcode[0x1f] = [&]() -> int { _rr(reg.a); return 4; };

    // JP, nn
    opcode[0xc3] = [&]() -> int { reg.pc = memory.readWord(reg.pc); return 16; };

    // JP cc,nn
    opcode[0xc2] = [&]() -> int { if (getFlag(FLAG_Z) == 0) { reg.pc = memory.readWord(reg.pc); return 16; } else { reg.pc += 2; return 12; } };
    opcode[0xca] = [&]() -> int { if (getFlag(FLAG_Z) == 1) { reg.pc = memory.readWord(reg.pc); return 16; } else { reg.pc += 2; return 12; } };
    opcode[0xd2] = [&]() -> int { if (getFlag(FLAG_C) == 0) { reg.pc = memory.readWord(reg.pc); return 16; } else { reg.pc += 2; return 12; } };
    opcode[0xda] = [&]() -> int { if (getFlag(FLAG_C) == 1) { reg.pc = memory.readWord(reg.pc); return 16; } else { reg.pc += 2; return 12; } };

    // JP (HL)
    opcode[0xe9] = [&]() -> int { reg.pc = reg.hl; return 4; };

    // JR n
    opcode[0x18] = [&]() -> int { reg.pc += (static_cast<int8_t>(memory.readByte(reg.pc)) + 1); return 12; };

    // JR CC
    opcode[0x20] = [&]() -> int { if (getFlag(FLAG_Z) == 0) { reg.pc += (static_cast<int8_t>(memory.readByte(reg.pc)) + 1); return 12; } else { reg.pc++ ; return 8; } };
    opcode[0x28] = [&]() -> int { if (getFlag(FLAG_Z) == 1) { reg.pc += (static_cast<int8_t>(memory.readByte(reg.pc)) + 1); return 12; } else { reg.pc++ ; return 8; } };
    opcode[0x30] = [&]() -> int { if (getFlag(FLAG_C) == 0) { reg.pc += (static_cast<int8_t>(memory.readByte(reg.pc)) + 1); return 12; } else { reg.pc++ ; return 8; } };
    opcode[0x38] = [&]() -> int { if (getFlag(FLAG_C) == 1) { reg.pc += (static_cast<int8_t>(memory.readByte(reg.pc)) + 1); return 12; } else { reg.pc++ ; return 8; } };

    // CALL nn
    opcode[0xcd] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, (reg.pc + 2)); reg.pc = memory.readWord(reg.pc); return 24; };

    // CALL cc,nn
    opcode[0xc4] = [&]() -> int { if (getFlag(FLAG_Z) == 0) { reg.sp -= 2; memory.writeWord(reg.sp, (reg.pc + 2)); reg.pc = memory.readWord(reg.pc); return 24; } else { reg.pc += 2; return 12; } };
    opcode[0xcc] = [&]() -> int { if (getFlag(FLAG_Z) == 1) { reg.sp -= 2; memory.writeWord(reg.sp, (reg.pc + 2)); reg.pc = memory.readWord(reg.pc); return 24; } else { reg.pc += 2; return 12; } };
    opcode[0xd4] = [&]() -> int { if (getFlag(FLAG_C) == 0) { reg.sp -= 2; memory.writeWord(reg.sp, (reg.pc + 2)); reg.pc = memory.readWord(reg.pc); return 24; } else { reg.pc += 2; return 12; } };
    opcode[0xdc] = [&]() -> int { if (getFlag(FLAG_C) == 1) { reg.sp -= 2; memory.writeWord(reg.sp, (reg.pc + 2)); reg.pc = memory.readWord(reg.pc); return 24; } else { reg.pc += 2; return 12; } };

    // RET
    opcode[0xc9] = [&]() -> int { reg.pc = memory.readWord(reg.sp); reg.sp +=2; return 16; };

    // RET cc
    opcode[0xc0] = [&]() -> int { if (getFlag(FLAG_Z) == 0) { reg.pc = memory.readWord(reg.sp); reg.sp +=2; return 20; } else { return 8; } };
    opcode[0xc8] = [&]() -> int { if (getFlag(FLAG_Z) == 1) { reg.pc = memory.readWord(reg.sp); reg.sp +=2; return 20; } else { return 8; } };
    opcode[0xd0] = [&]() -> int { if (getFlag(FLAG_C) == 0) { reg.pc = memory.readWord(reg.sp); reg.sp +=2; return 20; } else { return 8; } };
    opcode[0xd8] = [&]() -> int { if (getFlag(FLAG_C) == 1) { reg.pc = memory.readWord(reg.sp); reg.sp +=2; return 20; } else { return 8; } };

    // RETI
    opcode[0xd9] = [&]() -> int { reg.pc = memory.readWord(reg.sp); reg.sp +=2; interruptMasterEnable = true; return 16; };

    // RST n
    opcode[0xc7] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x00; return 16; };
    opcode[0xcf] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x08; return 16; };
    opcode[0xd7] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x10; return 16; };
    opcode[0xdf] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x18; return 16; };
    opcode[0xe7] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x20; return 16; };
    opcode[0xef] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x28; return 16; };
    opcode[0xf7] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x30; return 16; };
    opcode[0xff] = [&]() -> int { reg.sp -= 2; memory.writeWord(reg.sp, reg.pc); reg.pc = 0x38; return 16; };

    // DAA
    opcode[0x27] = [&]() -> int { _daa(); return 4; };

    // CPL
    opcode[0x2f] = [&]() -> int { reg.a = ~reg.a; setFlag(FLAG_N, 1); setFlag(FLAG_H, 1); return 4; };

    // NOP
    opcode[0x00] = [&]() -> int { return 4; };

    // CCF
    opcode[0x3f] = [&]() -> int { setFlag(FLAG_C, !getFlag(FLAG_C)); setFlag(FLAG_N, 0); setFlag(FLAG_H, 0); return 4; };

    // SCF
    opcode[0x37] = [&]() -> int { setFlag(FLAG_C, 1); setFlag(FLAG_N, 0); setFlag(FLAG_H, 0); return 4; };

    // DI
    opcode[0xf3] = [&]() -> int { interruptMasterEnable = false; return 4; };

    // EI
    opcode[0xfb] = [&]() -> int { interruptMasterEnable = true; return 4; };

    // HALT
    opcode[0x76] = [&]() -> int { halt = true; return 4; };

    // STOP
    opcode[0x10] = [&]() -> int { halt = true; return 4; };
}

void CPU::loadCbcode()
{
    // RLC n
    cbcode[0x07] = [&]() -> int { _rlc(reg.a); return 8; };
    cbcode[0x00] = [&]() -> int { _rlc(reg.b); return 8; };
    cbcode[0x01] = [&]() -> int { _rlc(reg.c); return 8; };
    cbcode[0x02] = [&]() -> int { _rlc(reg.d); return 8; };
    cbcode[0x03] = [&]() -> int { _rlc(reg.e); return 8; };
    cbcode[0x04] = [&]() -> int { _rlc(reg.h); return 8; };
    cbcode[0x05] = [&]() -> int { _rlc(reg.l); return 8; };
    cbcode[0x06] = [&]() -> int { byte value = memory.readByte(reg.hl); _rlc(value); memory.writeByte(reg.hl, value); return 16; };

    // RL n
    cbcode[0x17] = [&]() -> int { _rl(reg.a); return 8; };
    cbcode[0x10] = [&]() -> int { _rl(reg.b); return 8; };
    cbcode[0x11] = [&]() -> int { _rl(reg.c); return 8; };
    cbcode[0x12] = [&]() -> int { _rl(reg.d); return 8; };
    cbcode[0x13] = [&]() -> int { _rl(reg.e); return 8; };
    cbcode[0x14] = [&]() -> int { _rl(reg.h); return 8; };
    cbcode[0x15] = [&]() -> int { _rl(reg.l); return 8; };
    cbcode[0x16] = [&]() -> int { byte value = memory.readByte(reg.hl); _rl(value); memory.writeByte(reg.hl, value); return 16; };

    // RRC n
    cbcode[0x0f] = [&]() -> int { _rrc(reg.a); return 8; };
    cbcode[0x08] = [&]() -> int { _rrc(reg.b); return 8; };
    cbcode[0x09] = [&]() -> int { _rrc(reg.c); return 8; };
    cbcode[0x0a] = [&]() -> int { _rrc(reg.d); return 8; };
    cbcode[0x0b] = [&]() -> int { _rrc(reg.e); return 8; };
    cbcode[0x0c] = [&]() -> int { _rrc(reg.h); return 8; };
    cbcode[0x0d] = [&]() -> int { _rrc(reg.l); return 8; };
    cbcode[0x0e] = [&]() -> int { byte value = memory.readByte(reg.hl); _rrc(value); memory.writeByte(reg.hl, value); return 16; };

    // RR n
    cbcode[0x1f] = [&]() -> int { _rr(reg.a); return 8; };
    cbcode[0x18] = [&]() -> int { _rr(reg.b); return 8; };
    cbcode[0x19] = [&]() -> int { _rr(reg.c); return 8; };
    cbcode[0x1a] = [&]() -> int { _rr(reg.d); return 8; };
    cbcode[0x1b] = [&]() -> int { _rr(reg.e); return 8; };
    cbcode[0x1c] = [&]() -> int { _rr(reg.h); return 8; };
    cbcode[0x1d] = [&]() -> int { _rr(reg.l); return 8; };
    cbcode[0x1e] = [&]() -> int { byte value = memory.readByte(reg.hl); _rr(value); memory.writeByte(reg.hl, value); return 16; };

    // SLA n
    cbcode[0x27] = [&]() -> int { _sla(reg.a); return 8; };
    cbcode[0x20] = [&]() -> int { _sla(reg.b); return 8; };
    cbcode[0x21] = [&]() -> int { _sla(reg.c); return 8; };
    cbcode[0x22] = [&]() -> int { _sla(reg.d); return 8; };
    cbcode[0x23] = [&]() -> int { _sla(reg.e); return 8; };
    cbcode[0x24] = [&]() -> int { _sla(reg.h); return 8; };
    cbcode[0x25] = [&]() -> int { _sla(reg.l); return 8; };
    cbcode[0x26] = [&]() -> int { byte value = memory.readByte(reg.hl); _sla(value); memory.writeByte(reg.hl, value); return 16; };

    // SRA n
    cbcode[0x2f] = [&]() -> int { _sra(reg.a); return 8; };
    cbcode[0x28] = [&]() -> int { _sra(reg.b); return 8; };
    cbcode[0x29] = [&]() -> int { _sra(reg.c); return 8; };
    cbcode[0x2a] = [&]() -> int { _sra(reg.d); return 8; };
    cbcode[0x2b] = [&]() -> int { _sra(reg.e); return 8; };
    cbcode[0x2c] = [&]() -> int { _sra(reg.h); return 8; };
    cbcode[0x2d] = [&]() -> int { _sra(reg.l); return 8; };
    cbcode[0x2e] = [&]() -> int { byte value = memory.readByte(reg.hl); _sra(value); memory.writeByte(reg.hl, value); return 16; };

    // SRL n
    cbcode[0x3f] = [&]() -> int { _srl(reg.a); return 8; };
    cbcode[0x38] = [&]() -> int { _srl(reg.b); return 8; };
    cbcode[0x39] = [&]() -> int { _srl(reg.c); return 8; };
    cbcode[0x3a] = [&]() -> int { _srl(reg.d); return 8; };
    cbcode[0x3b] = [&]() -> int { _srl(reg.e); return 8; };
    cbcode[0x3c] = [&]() -> int { _srl(reg.h); return 8; };
    cbcode[0x3d] = [&]() -> int { _srl(reg.l); return 8; };
    cbcode[0x3e] = [&]() -> int { byte value = memory.readByte(reg.hl); _srl(value); memory.writeByte(reg.hl, value); return 16; };

    // SWAP n
    cbcode[0x37] = [&]() -> int { _swap(reg.a); return 8; };
    cbcode[0x30] = [&]() -> int { _swap(reg.b); return 8; };
    cbcode[0x31] = [&]() -> int { _swap(reg.c); return 8; };
    cbcode[0x32] = [&]() -> int { _swap(reg.d); return 8; };
    cbcode[0x33] = [&]() -> int { _swap(reg.e); return 8; };
    cbcode[0x34] = [&]() -> int { _swap(reg.h); return 8; };
    cbcode[0x35] = [&]() -> int { _swap(reg.l); return 8; };
    cbcode[0x36] = [&]() -> int { byte value = memory.readByte(reg.hl); _swap(value); memory.writeByte(reg.hl, value); return 16; };

    // BIT b,r
    for (int i = 0; i < 8; i++) {
        cbcode[0x47 + i * 8] = [&]() -> int { _bit(i, reg.a); return 8; };
        cbcode[0x40 + i * 8] = [&]() -> int { _bit(i, reg.b); return 8; };
        cbcode[0x41 + i * 8] = [&]() -> int { _bit(i, reg.c); return 8; };
        cbcode[0x42 + i * 8] = [&]() -> int { _bit(i, reg.d); return 8; };
        cbcode[0x43 + i * 8] = [&]() -> int { _bit(i, reg.e); return 8; };
        cbcode[0x44 + i * 8] = [&]() -> int { _bit(i, reg.h); return 8; };
        cbcode[0x45 + i * 8] = [&]() -> int { _bit(i, reg.l); return 8; };
        cbcode[0x46 + i * 8] = [&]() -> int { _bit(i, memory.readByte(reg.hl)); return 16; };
    }

    // SET b,r
    for (int i = 0; i < 8; i++) {
        cbcode[0xc7 + i * 8] = [&]() -> int { reg.a |= 1 << i; return 8; };
        cbcode[0xc0 + i * 8] = [&]() -> int { reg.b |= 1 << i; return 8; };
        cbcode[0xc1 + i * 8] = [&]() -> int { reg.c |= 1 << i; return 8; };
        cbcode[0xc2 + i * 8] = [&]() -> int { reg.d |= 1 << i; return 8; };
        cbcode[0xc3 + i * 8] = [&]() -> int { reg.e |= 1 << i; return 8; };
        cbcode[0xc4 + i * 8] = [&]() -> int { reg.h |= 1 << i; return 8; };
        cbcode[0xc5 + i * 8] = [&]() -> int { reg.l |= 1 << i; return 8; };
        cbcode[0xc6 + i * 8] = [&]() -> int { byte value = memory.readByte(reg.hl); value |= 1 << i; memory.writeByte(reg.hl, value); return 16; };
    }

    // RES b,r
    for (int i = 0; i < 8; i++) {
        cbcode[0x87 + i * 8] = [&]() -> int { reg.a &= ~(1 << i); return 8; };
        cbcode[0x80 + i * 8] = [&]() -> int { reg.b &= ~(1 << i); return 8; };
        cbcode[0x81 + i * 8] = [&]() -> int { reg.c &= ~(1 << i); return 8; };
        cbcode[0x82 + i * 8] = [&]() -> int { reg.d &= ~(1 << i); return 8; };
        cbcode[0x83 + i * 8] = [&]() -> int { reg.e &= ~(1 << i); return 8; };
        cbcode[0x84 + i * 8] = [&]() -> int { reg.h &= ~(1 << i); return 8; };
        cbcode[0x85 + i * 8] = [&]() -> int { reg.l &= ~(1 << i); return 8; };
        cbcode[0x86 + i * 8] = [&]() -> int { byte value = memory.readByte(reg.hl); value &= ~(1 << i); memory.writeByte(reg.hl, value); return 16; };
    }
}

void CPU::_add(const byte& value)
{
    int result = reg.a + value;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, (((reg.a & 0xf) + (value & 0xf)) & 0x10));
    setFlag(FLAG_C, (result > 0xff));
    reg.a = (result & 0xff);
}

void CPU::_adc(const byte& value)
{
    // _add(value + getFlag(FLAG_C));
    // Considering 1Fh + 1Fh + 1h will not activate half carry
    // Sentence above should never be used

    byte carry  = getFlag(FLAG_C);
    int  result = reg.a + value + carry;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, (((reg.a & 0xf) + (value & 0xf) + (carry & 0xf)) & 0x10));
    setFlag(FLAG_C, (result > 0xff));
    reg.a = (result & 0xff);
}

void CPU::_sub(const byte& value)
{
    int result = reg.a - value;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 1);
    setFlag(FLAG_H, (((reg.a & 0xf) - (value & 0xf)) < 0));
    setFlag(FLAG_C, (result < 0));
    reg.a = (result & 0xff);
}

void CPU::_sbc(const byte& value)
{
    byte carry  = getFlag(FLAG_C);
    int  result = reg.a - value - carry;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 1);
    setFlag(FLAG_H, (((reg.a & 0xf) - (value & 0xf) - (carry & 0xf)) < 0));
    setFlag(FLAG_C, (result < 0));
    reg.a = (result & 0xff);
}

void CPU::_and(const byte& value)
{
    byte result = reg.a & value;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 1);
    setFlag(FLAG_C, 0);
    reg.a = result;
}

void CPU::_or(const byte& value)
{
    byte result = reg.a | value;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, 0);
    reg.a = result;
}

void CPU::_xor(const byte& value)
{
    byte result = reg.a ^ value;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, 0);
    reg.a = result;
}

void CPU::_cp(const byte& value)
{
    int result = reg.a - value;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 1);
    setFlag(FLAG_H, (((reg.a & 0xf) - (value & 0xf)) < 0));
    setFlag(FLAG_C, (result < 0));
}

void CPU::_inc(byte& target)
{
    int result = target + 1;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, (((target & 0xf) + 1) & 0x10));
    target = (result & 0xff);
}

void CPU::_dec(byte& target)
{
    int result = target - 1;
    setFlag(FLAG_Z, ((result & 0xff) == 0));
    setFlag(FLAG_N, 1);
    setFlag(FLAG_H, (((target & 0xf) - 1) < 0));
    target = (result & 0xff);
}

void CPU::_addhl(const word& value)
{
    int result = reg.hl + value;
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, (((reg.hl & 0xfff) + (value & 0xfff)) & 0x1000));
    setFlag(FLAG_C, (result > 0xffff));
    reg.hl = (result & 0xffff);
}

void CPU::_rlc(byte& target)
{
    byte bit    = (target & 0x80) >> 7;
    byte result = (target << 1) | bit;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, bit);
    target = result;
}

void CPU::_rl(byte& target)
{
    byte bit    = getFlag(FLAG_C);
    byte result = (target << 1) | bit;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, ((target & 0x80) >> 7));
    target = result;
}

void CPU::_rrc(byte& target)
{
    byte bit    = (target & 0x01);
    byte result = (target >> 1) | (bit << 7);
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, bit);
    target = result;
}

void CPU::_rr(byte& target)
{
    byte bit    = getFlag(FLAG_C);
    byte result = (target >> 1) | (bit << 7);
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, (target & 0x01));
    target = result;
}

void CPU::_sla(byte& target)
{
    byte result = (target << 1);
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, (target & 0x80));
    target = result;
}

void CPU::_sra(byte& target)
{
    byte bit    = (target & 0x80);
    byte result = (target >> 1) | bit;
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, (target & 0x01));
    target = result;
}

void CPU::_srl(byte& target)
{
    byte result = (target >> 1);
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, (target & 0x01));
    target = result;
}

void CPU::_swap(byte& target)
{
    byte higher = (target & 0xf0);
    byte lower  = (target & 0x0f);
    byte result = (higher >> 4) | (lower << 4);
    setFlag(FLAG_Z, (result == 0));
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_C, 0);
    target = result;
}

void CPU::_bit(const int& bit, const byte& target)
{
    setFlag(FLAG_Z, ((target >> bit) & 0x01) == 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_H, 1);
}

void CPU::_daa()
{
    // NOTE: My original implementation is wrong
    // This inplementation is based on mehcode/wadatsumi
    // https://github.com/mehcode/wadatsumi

    unsigned int result     = reg.a;
    unsigned int correction = (getFlag(FLAG_C)) ? 0x60 : 0x00;

    if (getFlag(FLAG_H) || (!getFlag(FLAG_N)) && ((result & 0x0f) > 0x09)) {
        correction |= 0x06;
    }

    if (getFlag(FLAG_C) || (!getFlag(FLAG_N)) && (result > 0x99)) {
        correction |= 0x60;
    }

    if (getFlag(FLAG_N)) {
        result -= correction;
    }
    else {
        result += correction;
    }

    if (((correction << 2) & 0x100) != 0) {
        setFlag(FLAG_C, true);
    }

    setFlag(FLAG_H, false);
    setFlag(FLAG_Z, ((result & 0xff) == 0));

    reg.a = (result & 0xff);
}

}  // namespace gb