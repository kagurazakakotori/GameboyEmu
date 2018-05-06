#pragma once
#include "DataType.h"

namespace Gameboy
{

class CPU
{
public:
    void init();
private:
    struct Reg
    {
        byte a = 0;
        byte f = 0;
        byte b = 0;
        byte c = 0;
        byte d = 0;
        byte e = 0;
        byte h = 0;
        byte l = 0;
        word sp = 0;
        word pc = 0;
    } reg;
};

}