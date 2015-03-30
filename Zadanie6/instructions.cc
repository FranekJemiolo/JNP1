#include "instructions.h"


SetInstruction::SetInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg (a), val (b) {}

void SetInstruction::execute ()
{
    if ((reg < 1) || (reg > hardware->get_reg()))
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->registers))[reg-1] = val;
}


LoadInstruction::LoadInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg (a), mem (b) {}

void LoadInstruction::execute ()
{
    if (((reg < 1) || (reg > hardware->get_reg())) ||
        ((mem < 0) || (mem > hardware->get_mem()-1)))
    {
        throw IllegalArgumentException ();
    }
    (*(this->hardware->registers))[reg-1] = (*(hardware->memory))[mem];
}


StoreInstruction::StoreInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), mem (a), reg (b) {}

void StoreInstruction::execute ()
{
    if (((reg < 1) || (reg > hardware->get_reg())) ||
        ((mem < 0) || (mem > hardware->get_mem()-1)))
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->memory))[mem] = (*(hardware->registers))[reg-1];
}


AddInstruction::AddInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg1 (a), reg2 (b) {}

void AddInstruction::execute ()
{
    if (((reg1 < 1) || (reg1 > hardware->get_reg())) ||
        ((reg2 < 1) || (reg2 > hardware->get_reg())))    
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->registers))[reg1-1] += (*(hardware->registers))[reg2-1]; 
}


SubInstruction::SubInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg1 (a), reg2 (b) {}

void SubInstruction::execute ()
{
    if (((reg1 < 1) || (reg1 > hardware->get_reg())) ||
        ((reg2 < 1) || (reg2 > hardware->get_reg())))    
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->registers))[reg1-1] -= (*(hardware->registers))[reg2-1]; 
}


MulInstruction::MulInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg1 (a), reg2 (b) {}

void MulInstruction::execute ()
{
    if (((reg1 < 1) || (reg1 > hardware->get_reg())) ||
        ((reg2 < 1) || (reg2 > hardware->get_reg())))    
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->registers))[reg1-1] *= (*(hardware->registers))[reg2-1]; 
}


DivInstruction::DivInstruction (std::shared_ptr<Hardware> hw, long long a, 
    long long b) : Instruction(hw), reg1 (a), reg2 (b) {}

void DivInstruction::execute ()
{
    if (((reg1 < 1) || (reg1 > hardware->get_reg())) ||
        ((reg2 < 1) || (reg2 > hardware->get_reg())))    
    {
        throw IllegalArgumentException ();
    }
    (*(hardware->registers))[reg1-1] /= (*(hardware->registers))[reg2-1]; 
}



PrintlnInstruction::PrintlnInstruction (std::shared_ptr<Hardware> hw, 
    long long a) : Instruction(hw), reg (a) {}

void PrintlnInstruction::execute ()
{
    if ((reg < 1) || (reg > hardware->get_reg()))
    {
        throw IllegalArgumentException ();
    }
    std::cout << (*(hardware->registers))[reg-1] << std::endl;
}
