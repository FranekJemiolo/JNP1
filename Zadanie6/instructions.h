#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <iostream>
#include "exceptions.h"
#include "hardware.h"

class Instruction
{
    protected :
        std::shared_ptr<Hardware> hardware;
    public :
        //Instruction () = default;        
        Instruction (std::shared_ptr<Hardware> hw)
        {
            this->hardware = hw;
        }
        Instruction (Instruction const& other) = default;
        Instruction& operator= (Instruction const& other) = default;
        virtual void execute () {}
        virtual ~Instruction () {}
};

class SetInstruction : public Instruction
{
    private :
        // Register
        long long reg;
        // Value
        long long val;
    public :
        SetInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class LoadInstruction : public Instruction
{
    private :
        // Register
        long long reg;
        // Memory
        long long mem;
    public :
        LoadInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class StoreInstruction : public Instruction
{
    private :
        // Memory
        long long mem;
        // Register
        long long reg;
    public :
        StoreInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class AddInstruction : public Instruction
{
    private :
        // Register one
        long long reg1;
        // Register two
        long long reg2;
    public :
        AddInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class SubInstruction : public Instruction
{
    private :
        // Register one
        long long reg1;
        // Register two
        long long reg2;
    public :
        SubInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class MulInstruction : public Instruction
{
    private :
        // Register one
        long long reg1;
        // Register two
        long long reg2;
    public :
        MulInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class DivInstruction : public Instruction
{
    private :
        // Register one
        long long reg1;
        // Register two
        long long reg2;
    public :
        DivInstruction (std::shared_ptr<Hardware> hw, long long a, long long b);
        void execute ();
};

class PrintlnInstruction : public Instruction
{
    private :
        // Register
        long long reg;
    public :
        PrintlnInstruction (std::shared_ptr<Hardware> hw, long long a);
        void execute ();
};
#endif
