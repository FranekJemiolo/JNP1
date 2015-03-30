#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <vector>
#include <memory>

#include "instructions.h"

typedef long long process_size;

class Process
{
    private :
    	
    	process_size p_size;
        std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> instructions;
        std::shared_ptr<Hardware> hardware;
               
    public :
        Process (std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> ins,
            std::shared_ptr<Hardware> hw);
        
        void run ();
        
        process_size get_size();
        
    	bool operator < (Process& p) {
			return p_size < p.p_size;
		}
};

#endif
