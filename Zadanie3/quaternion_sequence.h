// This program was written by Franciszek Jemioło and Piotr Szulc
// index numbers fj346919 and ps347277 respectively.
#include <vector>
#include <map>
#include <iostream>
#include "quaternion.h"

class QuaternionSequence
{
	public:
	    typedef unsigned long size_type;

	    explicit QuaternionSequence ();
	    explicit QuaternionSequence 
	        (const std::map<QuaternionSequence::size_type, Quaternion> &m);
	    explicit QuaternionSequence (const std::vector<Quaternion> &v);
	    ~QuaternionSequence();

	    QuaternionSequence (const QuaternionSequence &s);
	    
        QuaternionSequence & operator=(const QuaternionSequence &s) = default;
        
	    QuaternionSequence & operator+= (const QuaternionSequence &q);
        QuaternionSequence & operator-= (const QuaternionSequence &q);
        QuaternionSequence & operator*= (const QuaternionSequence &q);
        QuaternionSequence & operator*= (const Quaternion &arg);

        const QuaternionSequence operator+ (const QuaternionSequence &q) const;
        const QuaternionSequence operator- (const QuaternionSequence &q) const;
        const QuaternionSequence operator* (const QuaternionSequence &q) const;

        bool operator== (const QuaternionSequence &q) const;
        bool operator!= (const QuaternionSequence &q) const;

        const Quaternion operator[] (size_type i) const;

        explicit operator bool () const;

        void insert (size_type i, const Quaternion &q);
        void insert (size_type i, Quaternion &&q);
        
        static unsigned long count ();
        
        friend std::ostream & operator<< (std::ostream &out, 
            const QuaternionSequence &s);
        friend const QuaternionSequence operator* (QuaternionSequence s, 
            const Quaternion &q);
        friend const QuaternionSequence operator* (const Quaternion &q, 
            QuaternionSequence s);
            
        std::map<QuaternionSequence::size_type, Quaternion> sequence;
	private:
		static unsigned long sequencer_count;
		
		void removeZeroQuaternions();
};

