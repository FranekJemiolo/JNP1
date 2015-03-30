#include "process.h"

Process::Process (std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> ins,
    std::shared_ptr<Hardware> hw)
{
    hardware = hw;
    instructions = ins;
    p_size = ins->size ();   
}

// Runs and removes first instruction of the program.
void Process::run ()
{
    auto ins = instructions->begin ();
    if (ins != instructions->end ())
    {
        (*ins)->execute ();
        instructions->erase (ins);
        p_size--;
    }
    else
    {
        throw NULLException ();
    }

}

process_size Process::get_size() {
	return p_size;
}
