#ifndef _HARDWARE_
#define _HARDWARE_
#include <memory>
#include <vector>

typedef long long register_type;
typedef long long memory_type;

class Hardware
{
    public :
        register_type registersCount;
        memory_type memorySize;
    	std::shared_ptr<std::vector<long long>> registers;
        std::shared_ptr<std::vector<long long>> memory;
        Hardware () {}
        Hardware (Hardware const& other) = default;
        Hardware& operator= (Hardware const& other) = default;
        register_type get_reg() {
			return registersCount;
		}
		memory_type get_mem() {
			return memorySize;
		}
};

#endif
