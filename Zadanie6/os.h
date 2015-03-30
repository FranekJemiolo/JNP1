#ifndef _OS_H_
#define _OS_H_

#include <list>
#include "exceptions.h"
#include "schedulingAlgorithms.h"
#include "hardware.h"

class OS
{
    private :
        std::shared_ptr<Hardware> hardware;
        std::shared_ptr<SchedulingAlgorithm> scheduler;
        
        std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> parseInput 
            (std::string s);
        
    public :
        OS (std::shared_ptr<Hardware> hw, std::shared_ptr<SchedulingAlgorithm> sched) :
            hardware (hw), scheduler (sched) {}

        void executePrograms (std::list<std::string> const& programs);
};


#endif
