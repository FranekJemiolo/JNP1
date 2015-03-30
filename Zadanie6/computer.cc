#include "computer.h"

Computer::Computer ()
{
    std::shared_ptr<Hardware> p (new Hardware ());
    this->hardware = p;
}

void Computer::setCPU (register_type numOfRegisters)
{
    if (numOfRegisters < 1)
    {
        throw IllegalArgumentException ();
    }
    this->hardware->registersCount = numOfRegisters;
    std::shared_ptr<std::vector<long long>> ptr 
        (new std::vector<long long> (numOfRegisters));
    this->hardware->registers = ptr;
}

void Computer::setRAM (memory_type size)
{
    if (size < 1)
    {
        throw IllegalArgumentException ();
    }
    this->hardware->memorySize = size;
    std::shared_ptr<std::vector<long long>> ptr 
        (new std::vector<long long> (size));
    this->hardware->memory = ptr;    
}

std::shared_ptr<OS> Computer::installOS (std::shared_ptr<SchedulingAlgorithm> alg)
{
    if (hardware->memorySize < 1)
    {
        throw NoRAMException ();
    }
    if (hardware->registersCount < 1)
    {
        throw NoCPUException ();
    }
    scheduler = alg;
    std::shared_ptr<OS> os_ptr (new OS(hardware, alg));
    os = os_ptr;
    return os;

}

std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling ()
{
    std::shared_ptr<SchedulingAlgorithm> p (new FCFS ());
    return p;
}

std::shared_ptr<SchedulingAlgorithm> createRRScheduling (time_type quantum)
{
    std::shared_ptr<SchedulingAlgorithm> p (new RR (quantum));
    return p;  
}

std::shared_ptr<SchedulingAlgorithm> createSJFScheduling ()
{
    std::shared_ptr<SchedulingAlgorithm> p (new SJF ());
    return p;
}
