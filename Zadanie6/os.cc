#include "os.h"
#include <boost/regex.hpp>

// Pattern used to find each line of instruction in string.
static const std::string LinePattern = "((\r\n)|(\n))";

// Pattern used to detect which instruction is given in a single line.
static const std::string BlankPattern = "((\\s)*)";
static const std::string DigitPattern = "((\\d)+)";

static const std::string PossibleEndPattern = "(((\n)|(\r)|(\r\n)|($))?)";

// The regex pattern for SET instruction.
static const std::string SetPattern = BlankPattern + "SET" + BlankPattern +
    " " + BlankPattern + "R" + DigitPattern + BlankPattern + " " + 
    BlankPattern + DigitPattern + BlankPattern + PossibleEndPattern;

// The regex pattern for LOAD instruction.    
static const std::string LoadPattern = BlankPattern +"LOAD"+ BlankPattern +
    " " + BlankPattern + "R" + DigitPattern + BlankPattern + " " + BlankPattern 
    + "M" + DigitPattern + BlankPattern + PossibleEndPattern;
// The regex pattern for STORE instruction.
static const std::string StorePattern = BlankPattern +"STORE"+ BlankPattern + 
    " " + BlankPattern + "M" + DigitPattern + BlankPattern + " " + BlankPattern 
    + "R" + DigitPattern + BlankPattern + PossibleEndPattern;
    
// The regex pattern for ADD instruction.
static const std::string AddPattern = BlankPattern +"ADD"+ BlankPattern + 
    " " + BlankPattern + "R" + DigitPattern + BlankPattern + " " + BlankPattern
    + "R" + DigitPattern + BlankPattern + PossibleEndPattern;
    
// The regex pattern for SUB instruction.
static const std::string SubPattern = BlankPattern +"SUB"+ BlankPattern + " " + 
    BlankPattern + "R" + DigitPattern + BlankPattern + " " + BlankPattern + "R" 
    + DigitPattern + BlankPattern + PossibleEndPattern;
    
// The regex pattern for MUL instruction.
static const std::string MulPattern = BlankPattern +"MUL"+ BlankPattern + " " + 
    BlankPattern + "R" + DigitPattern + BlankPattern + " " + BlankPattern + "R" 
    + DigitPattern + BlankPattern + PossibleEndPattern;

// The regex pattern for DIV instruction.
static const std::string DivPattern = BlankPattern +"DIV"+ BlankPattern + " " +
    BlankPattern + "R" + DigitPattern + BlankPattern + " " + BlankPattern + "R" 
    + DigitPattern + BlankPattern + PossibleEndPattern;

// The regex pattern for PRINTLN instruction.
static const std::string PrintlnPattern = BlankPattern + "PRINTLN" + 
    BlankPattern + " " + BlankPattern + "R" + DigitPattern + BlankPattern + 
    PossibleEndPattern;
    


// Returns a vector of lines to be changed to instructions.
std::shared_ptr<std::vector<std::string>> parseStringToLines (std::string s)
{
    std::shared_ptr<std::vector<std::string>> vec_ptr (new std::vector<std::string> ());
    
    boost::regex pattern (LinePattern);
    boost::smatch result;
    
    while (boost::regex_search (s, result, pattern))
    {
        // We are looking for the first group.
        vec_ptr->push_back (result.prefix ().str ());
        s = result.suffix ().str ();
    }
    // Adding end of line if there is any.
    if (s.size () > 0)
        vec_ptr->push_back (s);
    
    return vec_ptr;
}

// Checks if is an instruction of given pattern.
bool isInstruction (std::string s, const std::string InstructionPattern)
{
    boost::regex pattern (InstructionPattern);
    boost::smatch result;
    return boost::regex_match (s, result, pattern);
}

// Returns pair of numbers in instruction.
std::pair<long long, long long> parseTwoNumbersInstruction (std::string s,
    const std::string InstructionPattern)
{
    boost::regex pattern (InstructionPattern);
    boost::smatch result;
    long long first = -1, second = -1;
    if (boost::regex_search (s, result, pattern))
    {
        // The number of the group of first number is 7.
        first = std::stoll (result[7]);
        // The number of the group of second number is 13.
        second = std::stoll (result[13]);
    }
    else
    {
        throw UnknownInstructionException (); 
    }
    return std::make_pair (first, second);
}

// Returns the number in instruction.
long long parseOneNumberInstruction (std::string s,
    const std::string InstructionPattern)
{
    boost::regex pattern (InstructionPattern);
    boost::smatch result;
    long long first;
    if (boost::regex_search (s, result, pattern))
    {
        // The number of the group of number is 7.
        first = std::stoll (result[7]);
    }
    else
    {
        throw UnknownInstructionException (); 
    }
    return first;
}

// Parses one line of code and returns instruction.
std::shared_ptr<Instruction> parseLine (std::string s, std::shared_ptr<Hardware> hardware)
{
    // Check if given SET instruction.
    if (isInstruction (s, SetPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, SetPattern);
        std::shared_ptr<Instruction> ptr (new SetInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given LOAD instruction.
    else if (isInstruction (s, LoadPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, LoadPattern);
        std::shared_ptr<Instruction> ptr (new LoadInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given STORE instruction.
    else if (isInstruction (s, StorePattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, StorePattern);
        std::shared_ptr<Instruction> ptr (new StoreInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given ADD instruction.
    else if (isInstruction (s, AddPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, AddPattern);
        std::shared_ptr<Instruction> ptr (new AddInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given SUB instruction.
    else if (isInstruction (s, SubPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, SubPattern);
        std::shared_ptr<Instruction> ptr (new SubInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given MUL instruction.
    else if (isInstruction (s, MulPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, MulPattern);
        std::shared_ptr<Instruction> ptr (new MulInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given DIV instruction.
    else if (isInstruction (s, DivPattern))
    {
        std::pair<long long, long long> p = parseTwoNumbersInstruction 
            (s, DivPattern);
        std::shared_ptr<Instruction> ptr (new DivInstruction (hardware, p.first, p.second));
        return ptr;
    }
    // Check if given PRINTLN instruction.
    else if (isInstruction (s, PrintlnPattern))
    {
        long long f = parseOneNumberInstruction (s, PrintlnPattern);
        std::shared_ptr<Instruction> ptr (new PrintlnInstruction (hardware, f));
        return ptr;
    }
    // Unkown instruction! Throwing exception.
    else
    {
        throw UnknownInstructionException ();
    }
}

// Parses input and returns a vector of Instruction objects.
std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> OS::parseInput (std::string s)
{
    std::shared_ptr<std::vector<std::shared_ptr<Instruction>>> ins_ptr 
        (new std::vector<std::shared_ptr<Instruction>> ());
    // Parsing string to vector of lines.
    std::shared_ptr<std::vector<std::string>> str_ptr = parseStringToLines (s);
    // And now parse every line of code.
    for (auto p : *str_ptr)
    {
        
        // Check if not given empty line (only whitespaces).
        if (!isInstruction (p, BlankPattern))
        {
            // Insert instruction to the vector.
            ins_ptr->push_back (parseLine (p, hardware));
        }
        // Else ignore whitespaces.
    }
    return ins_ptr;
}

void OS::executePrograms (std::list<std::string> const& programs)
{
    // Creating list of process for scheduler.
    std::shared_ptr<std::vector<std::shared_ptr<Process>>> prog_ptr (new std::vector<std::shared_ptr<Process>> ());
    for (auto p : programs)
    {
        std::shared_ptr<Process> proc (new Process (parseInput (p), hardware));
        //std::cout << "Here" <<std::endl;
        prog_ptr->push_back (proc);
    }
    // Now the scheduler should run.
    scheduler->setTasks (prog_ptr);
    std::shared_ptr<Process> p;
    while ((p = scheduler->decide ()) != nullptr)
    {
        p->run ();
    }
}
