#pragma once
#include "DataType.h"

namespace Gameboy
{

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
};
}