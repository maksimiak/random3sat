# random3sat

Randomized 3 SAT algorithm based on random walk

# Usage

Create clauses with Clause class, which accepts two parameters in constructor. First parameter describes the indexes of variables the clause holds, second parameter describes which of the literas should be negated (from initially provided list). Second parameter is optional.

## Example

```
/* create clauses */
Clause c0({2, 1, 0}); 
Clause c01({2, 0, 3}, {0}); // first literal will be negated
Clause c02({1, 1, 0});
 
 /* f = (x3 v x2 v x1) & (!x3 v x1 v x4) & (x2 v x2 v x1) */
vector<Clause> clauses {c0, c01, c02};
Function func1(clauses);

/* create any initial assignment for available literals */
Assignment a {false, false, false, false};


/* apply random walk */
for (;;)
{
    if (random_walk(a, func1)) break;
}

/* to display final interpretation */
func1.display_interpretation();
```

# References
A Probabilistic 3—SAT Algorithm Further Improved: https://doi.org/10.1007/3-540-45841-7_15
