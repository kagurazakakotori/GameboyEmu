#include "CPU.h"

namespace Gameboy
{

void CPU::init()
{
    // Initialize registers
    reg.a  = 0x01;  // Gameboy CPU Manual 2.7.1
    reg.f  = 0xb0;
    reg.bc = 0x0013;
    reg.de = 0x00d8;
    reg.hl = 0x014d;
    reg.pc = 0x0100;  // Gameboy CPU Manual 3.2.3
    reg.sp = 0xfffe;  // Gameboy CPU Manual 3.2.4
}

void CPU::loadOpcode()
{
    // Opcode returns the clock cycles of a command
    // Initialize Opcodes
    for (auto&& i : opcode) {
        i = [&]() -> int { return 4; };
    }

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
    opcode[0xf8] = [&]() -> int { return 12; };  // TODO

    // LD (nn),SP
    opcode[0x08] = [&]() -> int { memory.writeWord(reg.pc, reg.sp); reg.pc += 2; return 20; };

    // PUSH nn
    opcode[0xf5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.a); reg.sp--; memory.writeByte(reg.sp, reg.f); return 12; };
    opcode[0xc5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.b); reg.sp--; memory.writeByte(reg.sp, reg.c); return 12; };
    opcode[0xd5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.d); reg.sp--; memory.writeByte(reg.sp, reg.e); return 12; };
    opcode[0xe5] = [&]() -> int { reg.sp--; memory.writeByte(reg.sp, reg.h); reg.sp--; memory.writeByte(reg.sp, reg.l); return 12; };

    // POP nn
    opcode[0xf1] = [&]() -> int { reg.f = memory.readByte(reg.sp); reg.sp++; reg.a = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xc1] = [&]() -> int { reg.c = memory.readByte(reg.sp); reg.sp++; reg.b = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xd1] = [&]() -> int { reg.e = memory.readByte(reg.sp); reg.sp++; reg.d = memory.readByte(reg.sp); reg.sp++; return 12; };
    opcode[0xe1] = [&]() -> int { reg.l = memory.readByte(reg.sp); reg.sp++; reg.h = memory.readByte(reg.sp); reg.sp++; return 12; };
}

}  // namespace Gameboy
