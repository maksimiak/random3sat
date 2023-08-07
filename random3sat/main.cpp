#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>
#include <map>

using namespace std;

constexpr const size_t MAX_SAT = 3;
constexpr const size_t NO_VARS = 4;

typedef vector<bool> Assignment;

/***
RANDOM 3-SAT
- using the idea of random walk


f = (p v q v r) & (q v r v l) & (r v q v p)
=> n := number of variables = 4
=> m := number of clauses = 3

*/

vector<bool> vars(NO_VARS);

class Clause
{
public:
    Clause(vector<size_t> indexes, vector<size_t> neg_indexes = vector<size_t>())
    : m_indexes(indexes), m_neg_indexes(neg_indexes), m_value(false) {}

    vector<size_t> m_indexes;
    vector<size_t> m_neg_indexes;
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
            for (size_t cl_index = 0; cl_index < m_clauses[index].m_indexes.size(); ++cl_index)
            {

                int var_idx = m_clauses[index].m_indexes[cl_index];
                bool value = vars[var_idx];

                if (is_negated(index, cl_index))
                {
                    value = !value;
                }

                m_clauses[index].m_value |= value;

            }
            result &= m_clauses[index].m_value;
        }

        cleanup(); // set internal values to false
        return result;
    }

    void cleanup()
    {
        for (size_t index = 0; index < m_clauses.size(); ++index)
        {
            m_clauses[index].m_value = false;
        }
    }

    bool is_negated(size_t clause_idx, size_t literal_index)
    {
         if (find(m_clauses[clause_idx].m_neg_indexes.begin(),
                         m_clauses[clause_idx].m_neg_indexes.end(), literal_index) != m_clauses[clause_idx].m_neg_indexes.end())
         {

             return true;
         }
         return false;

    }

    void display_interpretation()
    {
        for (size_t index = 0; index < m_clauses.size(); ++index)
        {
            for (size_t cl_index = 0; cl_index < m_clauses[index].m_indexes.size(); ++cl_index)
            {
                cout << vars[m_clauses[index].m_indexes[cl_index]] << " ";
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
    size_t times = MAX_SAT * n;

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
        size_t urandom = rand() % MAX_SAT;


        // flip in all clauses
        size_t var_idx = func.m_clauses[unsatisfied].m_indexes[urandom];
        vars[var_idx] = !vars[var_idx];
    }
    return false;
}

int main()
{

    srand(time(0));

    Clause c0({2, 1, 0}); // initialized with index of available variables
    Clause c01({2, 0, 3}, {0});
    Clause c02({1, 1, 0});

    vector<Clause> clauses {c0, c01, c02};

    /**
    f = (x3 v x2 v x1) & (!x3 v x1 v x4) & (x2 v x2 v x1)
    */

    Function func1(clauses);
    func1.display_interpretation();

    Assignment a {false, false, false, false};

    for (;;)
    {
        if (random_walk(a, func1)) break;
    }

    return 0;
}
