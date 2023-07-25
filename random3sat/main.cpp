#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

typedef vector<bool> Assignment;

/***
RANDOM 3-SAT
- using the idea of random walk


f = (p v q v r) & (q v r v l) & (r v q v p)
=> n := number of variables = 4
=> m := number of clauses = 3

*/


vector<bool> vars(4);


class Clause
{
public:
    Clause(vector<bool>& literas) : m_literas(literas), m_value(false) {}

    vector<bool>& m_literas;
    bool m_value;
};

class Function
{
public:
    Function(const vector<Clause>& clauses) : m_clauses(clauses) {}

    bool evaluate()
    {
        bool result = true;

        // evaluate each clause and function
        for (size_t index = 0; index < m_clauses.size(); ++index)
        {
            // go through each clause
            for (size_t cl_index = 0; cl_index < m_clauses[index].m_literas.size(); ++cl_index)
            {
                m_clauses[index].m_value |= m_clauses[index].m_literas[cl_index];
            }
            result &= m_clauses[index].m_value;
        }
        return result;
    }

    void display_interpretation()
    {
        for (size_t index = 0; index < m_clauses.size(); ++index)
        {
            // go through each clause
            for (size_t cl_index = 0; cl_index < m_clauses[index].m_literas.size(); ++cl_index)
            {
                cout << m_clauses[index].m_literas[cl_index] << " ";
            }
            cout << endl;
        }
    }

    size_t un_idx()
    {
        for (size_t index = 0; index < m_clauses.size(); ++index)
        {
            // go through each clause
            if (!m_clauses[index].m_value)
            {
                return index;
            }
        }
        cout << "should not reach this" << endl;
        return 0;
    }

    vector<Clause> m_clauses;
};


bool random_walk(Assignment a, Function& func)
{
    //  a' = a;
    vars = a;

    size_t n = vars.size();
    size_t times = 3 * n;

    for (size_t index = 0; index < times; ++index)
    {
        if (func.evaluate())
        {
            // accept and halt
            cout << "HALT" << endl;
            func.display_interpretation();

            return true;
        }
        // C - clause that is not satisfied by temp_a
        size_t unsatisfied = func.un_idx();
        size_t urandom = (rand() % 3) + 1;
        // flip
        func.m_clauses[unsatisfied].m_literas[urandom] = !func.m_clauses[unsatisfied].m_literas[urandom];

    }
}



int main()
{
    srand(time(0));

    Clause c1(vars);
    c1.m_literas = vector<bool>{vars[0], vars[1], vars[2]};
    Clause c2(vars);
    c2.m_literas = vector<bool>{vars[0], vars[3], vars[1]};


    vector<Clause> clauses {c1, c2};

    /**
    f = (x1 v x2 v x3) & (x1 v x4 v x2)
    */

    Function func1(clauses);
    // cout << func1.evaluate() << endl;


    Assignment a1 {
    {
        // should satisfy
        false, false, false, false,
    }
    };


    for (;;)
    {
        if (random_walk(a1, func1))
        {
            break;
        }
    }


    return 0;
}
