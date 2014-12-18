// This program was written by Franciszek Jemioło and Piotr Szulc
// index numbers fj346919 and ps347277 respectively.

#include "quaternion_sequence.h"
unsigned long QuaternionSequence::sequencer_count = 0;

unsigned long QuaternionSequence::count ()
{
	return sequencer_count;
}

QuaternionSequence::QuaternionSequence ()
{
	sequencer_count++;
}

QuaternionSequence::~QuaternionSequence ()
{
	sequencer_count++;
}


QuaternionSequence::QuaternionSequence 
    (const std::map<QuaternionSequence::size_type, Quaternion> &m) 
    : sequence (m)
{
	sequencer_count++;
	removeZeroQuaternions ();
}

QuaternionSequence::QuaternionSequence (const std::vector<Quaternion> &v)
{
	sequencer_count++;

	for (unsigned long i = 0; i < v.size (); i++)
	{
	    if (v[i])
		    sequence[i] = v[i];
	}
}

QuaternionSequence::QuaternionSequence (const QuaternionSequence &s) 
    : sequence (s.sequence)
{
	sequencer_count++;
	sequence = s.sequence;
}

QuaternionSequence & QuaternionSequence::operator+=
    (const QuaternionSequence &q)
{
	for (const auto &seq : q.sequence)
	{
		sequence[seq.first] += seq.second;
	}
    removeZeroQuaternions ();
	return (*this);
}

QuaternionSequence & QuaternionSequence::operator-=
    (const QuaternionSequence &q)
{
	for (const auto &seq : q.sequence)
	{
		sequence[seq.first] -= seq.second;
	}
    removeZeroQuaternions ();
	return (*this);
}

QuaternionSequence & QuaternionSequence::operator*=
    (const QuaternionSequence &q)
{
	for (auto &i : sequence)
	{
		auto it = q.sequence.find (i.first);
		if (it != q.sequence.end ())
			i.second *= it->second;
		else
			i.second = 0.0;
	}
    removeZeroQuaternions ();
	return (*this);
}

QuaternionSequence & QuaternionSequence::operator*= (const Quaternion &q)
{
	for (auto &i : sequence)
	{
		i.second *= q;
	}

	return *this;
}

const QuaternionSequence QuaternionSequence::operator+
    (const QuaternionSequence &q) const
{
	return QuaternionSequence (*this) += q;
}

const QuaternionSequence QuaternionSequence::operator-
    (const QuaternionSequence &q) const
{
	return QuaternionSequence (*this) -= q;
}

const QuaternionSequence QuaternionSequence::operator*
    (const QuaternionSequence &q) const
{
	return QuaternionSequence (*this) *= q;
}

bool QuaternionSequence::operator== (const QuaternionSequence& q) const
{
	return sequence == q.sequence;
}

bool QuaternionSequence::operator!= (const QuaternionSequence& q) const
{
	return sequence != q.sequence;
}

void QuaternionSequence::insert (unsigned long i, const Quaternion &q)
{
	if (sequence.find (i) != sequence.end ())
		sequence.erase (i);
	else
		sequence[i] = q;
}

const Quaternion QuaternionSequence::operator[] (unsigned long i) const
{
	auto it = sequence.find (i);

	if (it !=sequence.end ())
		return it->second;
	else
	{
		return Quaternion ();
	};
}

QuaternionSequence::operator bool () const
{
	return !sequence.empty ();
}

void QuaternionSequence::removeZeroQuaternions() {
    auto it = sequence.begin();
   
    while (it != sequence.end()) {
        if (!(it->second)) {
            it = sequence.erase(it);
        } else {
            ++it;
        }
    }
}
std::ostream & operator<< (std::ostream& out, const QuaternionSequence &s)
{
    out << "(";
	for (const auto &it : s.sequence)
	{
		out << it.first << "->" << it.second << ",";
	}
	out << ")";
	return out;
}

const QuaternionSequence operator* (QuaternionSequence s, const Quaternion &q)
{
	return s *= q;
}

const QuaternionSequence operator* (const Quaternion &q, QuaternionSequence s)
{
	for (auto &it : s.sequence) 
	{
		it.second = q * it.second;
	}

	return s;
}
