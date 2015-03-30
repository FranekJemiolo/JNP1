#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <vector>
#include <memory>

#include "schedulingAlgorithms.h"
#include "os.h"
#include "hardware.h"


class Computer
{
    private :
        std::shared_ptr<Hardware> hardware;
        std::shared_ptr<SchedulingAlgorithm> scheduler;
        std::shared_ptr<OS> os;
        
    public :
        Computer ();
        Computer (Computer const& other) = default;
        Computer& operator=(Computer const& other) = default;
    
        void setCPU (register_type numOfRegisters);
        void setRAM (memory_type size);
        std::shared_ptr<OS> installOS (std::shared_ptr<SchedulingAlgorithm> alg);
        

};

std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling ();

std::shared_ptr<SchedulingAlgorithm> createRRScheduling (time_type quantum);

std::shared_ptr<SchedulingAlgorithm> createSJFScheduling ();

#endif
