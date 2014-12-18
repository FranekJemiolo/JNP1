// This program was written by Franciszek Jemioło and Piotr Szulc
// index numbers fj346919 and ps347277 respectively.

#include <iostream>
#include <algorithm>
#include <cmath>


class Quaternion
{
    private:
        double a, b, c, d; 
    public:
        // Constructors.
        Quaternion (double e = 0, double f = 0, double g = 0, double h = 0) : 
            a(e), b(f), c(g), d(h) {}
        
        Quaternion (const Quaternion& q) : a(q.R()), b(q.I()), c(q.J()),
            d(q.K()) {}
        
        double R () const { return a; }
        
        double I () const { return b; }
        
        double J () const { return c; }
        
        double K () const { return d; }
        
        // We are returning conjugated quaternion.
        Quaternion conj ()
        {
            return Quaternion (this->a, -(this->b), -(this->c), -(this->d));
        }
        
        // We are returning normalized quaternion.
        double norm ()
        {
            return sqrt ((a*a) + (b*b) + (c*c) + (d*d));
        }        
        
        // Overloaded operators.
                
        Quaternion & operator= (const Quaternion& other)
        {
            this->a = other.R();
            this->b = other.I();
            this->c = other.J();
            this->d = other.K();
            return (*this);
        }
        
        Quaternion & operator+= (const Quaternion& other)
        {
            this->a += other.R();
            this->b += other.I();
            this->c += other.J();
            this->d += other.K();
            return (*this);
        }

        Quaternion & operator-= (const Quaternion& other)
        {
            this->a -= other.R();
            this->b -= other.I();
            this->c -= other.J();
            this->d -= other.K();
            return (*this);
        }
        
        
        Quaternion operator*= (const Quaternion& other)
        {
            return Quaternion (
            (this->a * other.R() - this->b * other.I() - this->c * other.J() - 
                this->d * other.K()),
            (this->a * other.I() + this->b * other.R() + this->c * other.K() - 
                this->d * other.J()),
            (this->a * other.J() - this->b * other.K() + this->c * other.R() + 
                this->d * other.I()),
            (this->a * other.K() + this->b * other.J() - this->c * other.I() + 
                this->d * other.R())
            );
        }
        
        Quaternion operator+ (const Quaternion& other) const
        {
            return Quaternion(*this) += other;
        }
        
        Quaternion operator+ (double a) const
        {
            return Quaternion(*this) += Quaternion(a);
        }          

        Quaternion operator- (const Quaternion& other) const
        {
            return Quaternion(*this) -= other;
        }
        
        Quaternion operator- (double a) const
        {
            return Quaternion(*this) -= Quaternion(a);
        }

        Quaternion operator* (const Quaternion& other) const
        {
            return Quaternion(*this) *= other;
        }        

        bool operator== ( const Quaternion& other) const
        {
            return ((this->a == other.R()) && (this->b == other.I()) && 
                (this->c == other.J()) && (this->d == other.K()));
        }
        
        bool operator!= (const Quaternion& other) const
        {
            return ((this->a != other.R()) || (this->b != other.I()) || 
                (this->c != other.J()) || (this->d != other.K()));
        }
                
        explicit operator bool() const {
                return (*this) != Quaternion();
        }
        
        // Friend functions
        
        friend const Quaternion operator+ (const Quaternion& q)
        {
            return Quaternion(q);
        }
 
        friend const Quaternion operator- (const Quaternion& q)
        {
            return Quaternion (-q.R(), -q.I(), -q.J(), -q.K());
        }     
        friend const Quaternion operator+ (double a, Quaternion other)
        {
            return Quaternion ((other.R() + a), (other.I()), 
                (other.J()), (other.K()));
        }
        
        friend const Quaternion operator- (double a, Quaternion other)
        {
            return Quaternion ((a-other.R()), (-other.I()), 
                (-other.J()), (-other.K()));
        }
        
        friend const Quaternion operator* (double a, Quaternion q)
        {
            return Quaternion((q.R() * a), (q.I() * a), (q.J() * a), 
                (q.K() * a));
        }    
        friend double norm (Quaternion q)
        {
            return q.norm();
        }   
        friend Quaternion conj (Quaternion q)
        {
            return q.conj();
        }
        
        
        // Overloaded operator for standard output stream.
        friend std::ostream & operator<< (std::ostream &output, 
            const Quaternion& q )
        {
            if (q.R() == 0) {
                if (q.I() == 0) {
                    if (q.J() == 0) {
                        if (q.K () == 0) {
                            output << 0;
                        }
                        else {
                            output << q.K() << "k";
                        }
                    }
                    else {
                        if (q.K() == 0) {
                            output << q.J() << "j";
                        }
                        else {
                            output << q.J() << "j " << q.K() << "k";
                        }
                    }
                }
                else {
                    if (q.J() == 0) {
                        if (q.K () == 0) {
                            output << q.I() << "i";
                        }
                        else {
                            output << q.I() << "i " << q.K() << "k";
                        }
                    }
                    else {
                        if (q.K() == 0) {
                            output << q.I() << "i " << q.J() << "j";
                        }
                        else {
                            output << q.I() << "i " << q.J() << "j " << q.K() 
                                << "k";
                        }
                    }
                }
            }
            else {
                if (q.I() == 0) {
                    if (q.J() == 0) {
                        if (q.K () == 0) {
                            output << q.R();
                        }
                        else {
                            output << q.R() << " " << q.K() << "k";
                        }
                    }
                    else {
                        if (q.K() == 0) {
                            output << q.R() << " " << q.J() << "j";
                        }
                        else {
                            output << q.R() << " " << q.J() << "j " << q.K() 
                                << "k";
                        }
                    }
                }
                else {
                    if (q.J() == 0) {
                        if (q.K () == 0) {
                            output << q.R() << " " << q.I() << "i";
                        }
                        else {
                            output << q.R() << " " << q.I() << "i " << q.K() 
                                << "k";
                        }
                    }
                    else {
                        if (q.K() == 0) {
                            output << q.R() << " " << q.I() << "i " << q.J() 
                                << "j";
                        }
                        else {
                            output << q.R() << " " << q.I() << "i " << q.J() 
                                << "j " << q.K() << "k";
                        }
                    }
                }
            }
            return output;
        }
};
static const Quaternion I (0,1,0,0);
static const Quaternion J (0,0,1,0);
static const Quaternion K (0,0,0,1);
