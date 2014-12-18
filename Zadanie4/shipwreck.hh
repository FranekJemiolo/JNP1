// This program was written by Franciszek Jemioło and Hubert Marciniak.
// Index numbers respectively 346919 and 347154.
#ifndef SHIPWRECK_HH
#define SHIPWRECK_HH

#include <iostream>
#include <cassert>
#include <algorithm>
#include <typeinfo>

const static unsigned long int maxUnits = (unsigned long int) 1e9;

template <unsigned long int c, unsigned long int m, unsigned long int o>
struct ShipGear
{   
    static constexpr unsigned long int cannons = c;
    static constexpr unsigned long int masts = m;
    static constexpr unsigned long int oars = o;
};

typedef ShipGear<1, 0, 0> Cannon;
typedef ShipGear<0, 1, 0> Mast;
typedef ShipGear<0, 0, 1> Oar;

template <class G1, class G2> 
struct add_gear
{
    typedef ShipGear<G1::cannons+G2::cannons, G1::masts+G2::masts,
        G1::oars+G2::oars> type;
};

template<class G1, class G2> 
struct remove_gear
{
    typedef ShipGear<(G1::cannons > G2::cannons ? G1::cannons-G2::cannons : 0), 
        (G1::masts > G2::masts ? G1::masts-G2::masts : 0), 
        (G1::oars > G2::oars ? G1::oars-G2::oars : 0)> type;
};

template<class G1, unsigned long int N> 
struct multiply_gear
{
    typedef ShipGear<G1::cannons * N, G1::masts * N, G1::oars * N> type;
};

template<class G1, unsigned long int N> 
struct split_gear
{
    typedef ShipGear<G1::cannons / N, G1::masts / N, G1::oars / N> type;
};

template <class G>
class Squad
{
    private :
        unsigned long int count;

    public :
        constexpr Squad () : count (1) {}
        constexpr Squad (const unsigned int x) : count (x) {}
        constexpr Squad (Squad<G> const & s) : count (s.get_count ()){}
        ~Squad () = default;
        constexpr unsigned long int get_count () const
        {
            return count;
        }
        typedef G gear_type;
        static const gear_type gear;
        
        // Squad count altering operators.
        
        Squad<G>& operator += (Squad<G> const& other)
        {
            count += other.get_count();
            return *this;
        }
        
        Squad<G>& operator -= (Squad<G> const& other)
        {
            (count > other.get_count ()) ? 
                count -= other.get_count () : count = 0;
            return *this;
        }
        
        constexpr Squad<G> operator + (Squad<G> const& other) const
        {
            return Squad<G> (count + other.get_count ());
        }
        constexpr Squad<G> operator - (Squad<G> const& other) const
        {
            return Squad<G> (count > other.get_count ()  ? 
                (count - other.get_count ()) : 0);
        }
        
        Squad<G>& operator *= (long long x)
        {
            (x > 0) ? count *= x : count = 0;
            return *this;
        }
        
        Squad<G>& operator /= (long long x)
        {
            (x > 0) ? count /= x : count = 0;
            return *this;
        }
        
        constexpr Squad<G> operator * (long long x) const
        {
            return Squad<G> ((x > 0) ? count * x : 0);
        }

        constexpr Squad<G> operator / (long long x) const
        {
            return Squad<G> ((x > 0) ? count / x : 0);
        }

        // Boolean operators for comparing Squads with different gear.
            
        template <class G2>
        constexpr bool operator == (Squad<G2> const& other) const 
        {
            return (G::cannons == G2::cannons);
        }
        
        template <class G2>
        constexpr bool operator != (Squad<G2> const& other) const
        {
            return (G::cannons != G2::cannons);
        }
        
        template <class G2>
        constexpr bool operator > (Squad<G2> const& other) const
        {
            return (G::cannons > G2::cannons);
        }
        
        template <class G2>
        constexpr bool operator < (Squad<G2> const& other) const
        {
            return (G::cannons < G2::cannons);
        }
        
        template <class G2>
        constexpr bool operator >= (Squad<G2> const& other) const
        {
            return (G::cannons >= G2::cannons);
        }
        
        template <class G2>
        constexpr bool operator <= (Squad<G2> const& other) const
        {
            return (G::cannons <= G2::cannons);
        }
        
        // Boolean operators for comparing Squads with the same gear.
        
        constexpr bool operator == (Squad<G> const& other) const 
        {
            return (count == other.get_count ());
        }
        
        constexpr bool operator != (Squad<G> const& other) const
        {
            return (count != other.get_count ());
        }
        
        constexpr bool operator > (Squad<G> const& other) const
        {
            return (count > other.get_count ());
        }
        
        constexpr bool operator < (Squad<G> const& other) const
        {
            return (count < other.get_count ());
        }
        
        constexpr bool operator >= (Squad<G> const& other) const
        {
            return (count >= other.get_count ());
        }
        
        constexpr bool operator <= (Squad<G> const& other) const
        {
            return (count <= other.get_count ());
        }
        

       
};

template <class G>
constexpr Squad<G> operator * (long long x, const Squad<G>& s)
{
    return Squad<G> ((x > 0) ? s.get_count () * x : 0);
}

template <class G>
std::ostream& operator<< (std::ostream& out, const Squad<G>& s)
{
    out << "Ships: " << s.get_count () << "; Ship gear: Cannons: "
        << G::cannons << ", Masts: " << G::masts  << ", Oars: " << G::oars ;
    return out;
}

// This struct creates a type of smaller gear which is G1 if G1 < G2 or G2 else.
// We are comparing G1 and G2 by cannons then by masts and in the end by oars.
template <class G1, class G2> 
struct smaller_gear
{
    typedef ShipGear<(G1::cannons > G2::cannons ? G2::cannons : G1::cannons), 
        ((((G1::cannons == G2::cannons) && (G1::masts > G2::masts)) || 
            (G1::cannons > G2::cannons)) ? G2::masts : G1::masts), 
        (((((G1::cannons == G2::cannons) && (G1::masts == G2::masts) && 
            (G1::oars > G2::oars))) || (G1::cannons > G2::cannons) 
            || ((G1::cannons == G2::cannons) && (G1::masts > G2::masts))) ?
            G2::oars : G1::oars)> type;
};

// Returning minimal number from three numbers.
constexpr unsigned long int min3 
    (unsigned long int a, unsigned long int b, unsigned long int c)
{
    return ((((a > b) && (b > 0) ? b : a) > c) && (c > 0) ? c : 
        (((a > b) ? b : a) == 0 ? 0 : ((a > b) ? b : a)));
}


// We have to check if both Squads gear is <0,0,0>, because then we have to
// return their added count. If it is not equal to <0,0,0> then we have to
// decide how many ships a squad with new gear will hold.
template <class G1, class G2> 
constexpr Squad <typename add_gear<G1, G2>::type> join_ships 
    (Squad<G1> const& s1, Squad<G2> const& s2)
    
{
    return Squad <typename add_gear<G1, G2>::type> (
    min3 (
        (G1::cannons + G2::cannons > 0 ? 
        (((G1::cannons * s1.get_count ()) + (G2::cannons * s2.get_count ()))
            / (G1::cannons + G2::cannons)) 
        : 0),
        (G1::masts + G2::masts > 0 ? 
        (((G1::masts * s1.get_count ()) + (G2::masts * s2.get_count ())) 
            / (G1::masts + G2::masts)) 
        : 0),
        (G1::oars + G2::oars > 0 ? 
        (((G1::oars * s1.get_count ()) + (G2::oars * s2.get_count ())) 
            / (G1::oars + G2::oars)) 
        : 0)
        ) 
    == 0 ?
    (s1.get_count () + s2.get_count ()) :
    min3 (
        (G1::cannons + G2::cannons > 0 ? 
        (((G1::cannons * s1.get_count ()) + (G2::cannons * s2.get_count ()))
            / (G1::cannons + G2::cannons)) 
        : 0),
        (G1::masts + G2::masts > 0 ? 
        (((G1::masts * s1.get_count ()) + (G2::masts * s2.get_count ())) 
            / (G1::masts + G2::masts)) 
        : 0),
        (G1::oars + G2::oars > 0 ? 
        (((G1::oars * s1.get_count ()) + (G2::oars * s2.get_count ())) 
            / (G1::oars + G2::oars)) 
        : 0)
        )
    );     
  
}



template <class G1> 
constexpr Squad <typename split_gear<G1,2>::type> split_ships 
    (Squad<G1> const& s)
{
    return Squad <typename split_gear<G1,2>::type> (s.get_count ());
}


// Expected_booty for comparing squads of different gear.
template <class G1, class G2> 
constexpr Squad <typename smaller_gear<G1, G2>::type> expected_booty 
    (Squad<G1> const& s1, Squad<G2> const& s2)
    
{
    return Squad <typename smaller_gear<G1, G2>::type> (
        ((G1::cannons > G2::cannons)||
            ((G1::cannons == G2::cannons) && (G1::masts > G2::masts)) ||
            ((G1::cannons == G2::cannons) && (G1::masts == G2::masts) &&
                (G1::oars > G2::oars))
        ) ? s2.get_count () : s1.get_count ()
    );
}


// Expected_booty if comparing squads ships of same gear. The result is always 
// second ship.
template <class G> 
constexpr Squad <typename smaller_gear<G, G>::type> expected_booty 
    (Squad<G> const& s1, Squad<G> const& s2)  
{
    return Squad <typename smaller_gear<G, G>::type> (s2.get_count ());
}

#endif
