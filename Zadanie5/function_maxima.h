// This program was written by Franciszek Jemioło and Joanna Wiszowata
// identified by index numbers 346919 and 332659 respectively.

#ifndef FUNCTION_MAXIMA_H_
#define FUNCTION_MAXIMA_H_

#include <set>
#include <memory>

// Thrown when function is given argument out of domain.
class InvalidArg : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "InvalidArg";
        }
};



template<typename A, typename V>
class FunctionMaxima {

    public :
    
        // Definition of point_type which is simply a point on a function graph.
        class point_type
        {
            friend class FunctionMaxima<A, V>;
            private:
                
                std::shared_ptr<const A> pArg;
                std::shared_ptr<const V> pVal;
                point_type (std::shared_ptr<const A> arg, std::shared_ptr<const V> val = std::shared_ptr<const V> ()) 
                    : pArg(arg), pVal(val) {};
            public:
            
                point_type (point_type const& p) = default;
                point_type& operator= (point_type const& p) = default;
                A const& arg () const
                {
                    return *pArg;
                }
                V const& value () const
                {
                    return *pVal;
                }
        };
        
        // Constructors
        FunctionMaxima () = default;
        FunctionMaxima (const FunctionMaxima& f) = default;
        FunctionMaxima& operator = (FunctionMaxima& f) = default;  
        
        // Main functions
        /*V const& value_at(A const& a) const;
        void set_value(A const& a, V const& v);
        void erase(A const& a);*/
        
    private :
        
        // Only arguments of function compared
        class functionComparator
        {
            public :
                bool operator() (const point_type& p1, const point_type& p2) const
                {
                    return p1.arg () < p2.arg ();
                }
        };
        
        // For maximas we want to sort them by values (biggest first) and with
        // lowest arguments (if the same maximas).
        class maximumComparator
        {
            public :
                bool operator() (const point_type& p1, const point_type& p2) const
                {
                    if(!(p1.value () < p2.value ()) && !(p2.value () < p1.value ()))
                        return p1.arg () < p2.arg ();
                    return !(p1.value () < p2.value ());
                }
        };        

        // This set will represent our function.
        std::multiset<point_type, functionComparator> functionSet;
        
        // This set will hold all the maximas.
        std::set<point_type, maximumComparator> maximumSet;
                
        struct emptyDeleter {
            void operator() (const A*) const {}
        };
    
    public :
        
        // Iterator definitions
        using iterator = typename std::multiset<point_type, functionComparator>::const_iterator;
        using mx_iterator = typename std::set<point_type, maximumComparator>::const_iterator;
       
        // For functionSet
        iterator find (A const& a) const
        {
            auto ptr = std::shared_ptr<const A> (&a, emptyDeleter ());
            point_type point (ptr);
            return functionSet.find (point);
        }

        iterator begin () const noexcept
        {
            return functionSet.begin ();
        }

        iterator end () const noexcept
        {
            return functionSet.end ();
        }

        // For maximumSet
        mx_iterator mx_begin () const noexcept
        {
            return maximumSet.begin ();
        }

        mx_iterator mx_end() const noexcept 
        {
            return maximumSet.end ();
        };               
        
        // size_type definition
        using size_type = typename std::multiset<point_type, functionComparator>::size_type;
        size_type size() const
        {
            return functionSet.size ();
        }
        
    private :
    
        // Struct used to mark success of creating or removing and object safely
        struct safety
        {
            safety () : success (false) {}
            bool success;
            void markSuccess () {success = true;}
        };
        
        // Builder of a type, does nothing if fails (no change to set).
        
        struct argBuilder : safety
        {
            typename std::multiset<point_type,functionComparator>::iterator it;
            std::multiset<point_type,functionComparator>& set;
            
            argBuilder (point_type const& point, std::multiset<point_type,functionComparator>& set)
            : safety (), it (set.insert (point)), set (set) {}
            
            ~argBuilder () {if (!safety::success) set.erase (it);}
        };
        
        
        // Used to remove unwanted objects safely, restores if not constructed 
        // properly.
        struct argRemover : safety
        {
            typename std::multiset<point_type,functionComparator>::iterator it;
            std::multiset<point_type,functionComparator>& set;
            
            argRemover (point_type const& point, std::multiset<point_type,functionComparator>& set)
            : safety (), it ( set.find (point)), set (set) {}
            
            argRemover (typename std::multiset<point_type,functionComparator>::iterator it, std::multiset<point_type,functionComparator>& set)
            : safety (), it (it), set (set) {}
            
            ~argRemover () {if (safety::success) set.erase (it);}
        };
        
        struct maxRemover : safety
        {
            typename std::set<point_type,maximumComparator>::iterator it;
            std::set<point_type,maximumComparator>& set;
            
            maxRemover (point_type const& point, std::set<point_type,maximumComparator>& set)
            : safety (), it ( set.insert (point).first), set (set) {}
            
            maxRemover (typename std::set<point_type,maximumComparator>::iterator it,
                std::set<point_type,maximumComparator>& set)
            : safety (), it (it), set (set) {}
            
            ~maxRemover () {if (safety::success) set.erase (it);}
        };
        
        
        static bool isLocalMax (std::multiset<point_type, functionComparator> const& fMax,
            const iterator act, const iterator prev, V const& val)
        {
            auto it = act;
            auto actVal = ((act == prev) ? val : act->value ());
            
            if (act != fMax.begin ())
            {
                it--;
                auto compared = ((it == prev) ? val : it->value ());
                if (actVal < compared)
                    return false;
                it++;
            }
            it++;
            if (it != fMax.end ())
            {
                auto compared = ((it == prev) ? val : it->value ());
                if (actVal < compared)
                    return false;
            }
            return true;
        }
        
        
        // Updates maximas in maximumSet.
        struct updater : safety
        {
            enum operations {nothing, build, remove};
            operations op;
            std::set<point_type, maximumComparator>& set;
            mx_iterator it;
            
            updater (std::multiset<point_type, functionComparator> const& fMax,
                std::set<point_type, maximumComparator>& maxSet,
                iterator act, const iterator prev, point_type const& newPt,
                const int direction ) : set (maxSet)
            {
                // Checking if we are on the border of our domain.
                if (direction == 1)
                {
                    if (act == fMax.begin ())
                    {
                        op = nothing;
                        return;
                    }
                    act--; 
                }
                if (direction == -1)
                {
                    act++;
                    if (act == fMax.end ())
                    {
                        op = nothing;
                        return;
                    }
                }
                
                point_type actValue = ((act == prev) ? newPt : *act);
                
                if (isLocalMax (fMax, act, prev, newPt.value ()))
                {
        
                    auto res = maxSet.insert (actValue);
                    if (res.second)
                    // It already is.
                    {
                        op = build;
                        it = res.first;
                    }
                    else
                    {
                        op = nothing;
                    }
                }
                else 
                {
                    it = maxSet.find (actValue);
                    op = ((it == maxSet.end ()) ? nothing : remove);
                }
            }
            
            // Have to remove if updater marked with success or not insert
            // when failed to insert.
            ~updater ()
            {
                if (((safety::success) && (op == remove)) ||
                    ((!safety::success) && (op == build))) 
                        set.erase (it);
            }
            
        };
    
    public :
    // Main functions
    
        // Definition for value_at, throws InvalidArg if a not in domain.
        V const& value_at (A const& a) const
        {
            auto it = this->find (a);
            if (it == this->end ())
                throw InvalidArg ();
            return it->value ();
        }
        
        // Sets argument a value to V, adds a and v if a not in domain.
        // Using safe builder, removers and updaters so that destructors
        // will handle our exception safety (if not marked they will undo
        // all changes).
        void set_value (A const& a, V const& v)
        {
            auto argPtr = std::make_shared<A> (a);
            auto valPtr = std::make_shared<V> (v);
            point_type pt (argPtr, valPtr);
            auto it = functionSet.find (pt);
            
            if (it == functionSet.end ())
            {
                // Have to insert
                argBuilder ptBuilder (pt, functionSet);
                it = ptBuilder.it;
                
                updater leftUpdater (functionSet, maximumSet, it, it, pt, -1);
                updater midUpdater (functionSet, maximumSet, it, it, pt, 0);
                updater rightUpdater (functionSet, maximumSet, it, it, pt, 1);
                // Marking changes
                leftUpdater.markSuccess ();
                midUpdater.markSuccess ();
                rightUpdater.markSuccess ();
                ptBuilder.markSuccess ();
                return;
            }
            // Already in set, have to update change.
            
            updater leftUpdater (functionSet, maximumSet, it, it, pt, -1);
            updater midUpdater (functionSet, maximumSet, it, it, pt, 0);
            updater rightUpdater (functionSet, maximumSet, it, it, pt, 1);
            
            argBuilder ptBuilder (pt, functionSet);
            maxRemover mxRemover (*it, maximumSet);
            argRemover itRemover (it, functionSet);
            // Marking changes
            leftUpdater.markSuccess ();
            midUpdater.markSuccess ();
            rightUpdater.markSuccess ();
            itRemover.markSuccess ();
            mxRemover.markSuccess ();
            ptBuilder.markSuccess ();
            
            
        }
        
        // Erases a from domain. If a not in domain, does nothing.
        void erase (A const& a)
        {
            auto argPtr = std::make_shared<A> (a);
            point_type pt (argPtr);
            auto it = functionSet.find (pt);
            if (it == functionSet.end ())
                return; // Does nothing, not in set.
            
            // Now have to safely remove.
            argRemover ptRemover (pt, functionSet);
            maxRemover mxRemover (*it, maximumSet);
            auto left = it;
            auto right = it;
            right++;
            
            if (right == functionSet.end ())
            {
                // Ok now we are removing last one from domain. So our left will
                // be last now.
                if (left == functionSet.begin ())
                {
                    mxRemover.markSuccess ();
                    ptRemover.markSuccess ();
                    return;
                }
                
                left--;
                updater leftUpdater (functionSet, maximumSet, left, it, *left, 0);
                // Marking changes
                leftUpdater.markSuccess ();
                mxRemover.markSuccess ();
                ptRemover.markSuccess ();
                return;
            }
            
            if (left == functionSet.begin ())
            {
                // So our left neighbour is the first argument in the domain.
                updater rightUpdater (functionSet, maximumSet, right, it, *right, 0);
                // Marking changes.
                rightUpdater.markSuccess ();
                mxRemover.markSuccess ();
                ptRemover.markSuccess ();
                
            }
            
            // We are in the middle of the function and so are our left and 
            // right neighbours.
            left--;
            updater leftUpdater (functionSet, maximumSet, it, it, *left, -1);
            updater rightUpdater (functionSet, maximumSet, it, it, *right, 1);
            // Marking changes.
            leftUpdater.markSuccess ();
            rightUpdater.markSuccess ();
            mxRemover.markSuccess ();
            ptRemover.markSuccess ();
            
        }
    };

#endif
