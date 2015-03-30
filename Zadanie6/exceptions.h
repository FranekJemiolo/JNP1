#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

// Thrown when computer is given wrong registers or memory.
class IllegalArgumentException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "IllegalArgumentException";
        }
};

// Thrown when installing OS without CPU.
class NoCPUException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "NoCPUException";
        }
};

// Thrown when installing OS without RAM.
class NoRAMException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "NoRAMException";
        }
};

// Thrown when unknown instruction is given in program.
class UnknownInstructionException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "UnknownInstructionException";
        }
};

// Thrown when invalid register was given in instruction.
class InvalidRegisterException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "InvalidRegisterException";
        }
};

// Thrown when invalid addres was given in instruction.
class InvalidAddressException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "InvalidAddressException";
        }
};

// Thrown when instruction in program want to divide by zero.
class DivisionByZeroException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "DivisionByZeroException";
        }
};

// Thrown when program without lines runs.
class NULLException : public std::exception 
{
    public:
        virtual const char* what() const throw() 
        {
            return "NULLException";
        }
};


#endif
