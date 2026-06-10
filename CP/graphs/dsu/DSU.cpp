// ════════════════════════════════════════════════════════════════════════════
// UNION-FIND (DISJOINT SET UNION) — Path Compression + Union by Size/Rank
// ────────────────────────────────────────────────────────────────────────────
// Disjoint sets ko efficiently handle karta hai
// FIND = element ka representative dhundho  |  UNION = do sets merge karo
// Applications: cycle detection, Kruskal MST, connected components
// Time: O(α(n)) per op  |  Space: O(n)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <vector>
using namespace std;

class Union_find
{
    vector<int> parent; // Parent array - har element ka representative/root store karta hai
    vector<int> size;   // Size array - har set ka size store karta hai (optimization ke liye)
    vector<int> rank;   // Rank array - tree ki height track karta hai (union by rank ke liye)

public:
    // Step 1: parent, size, rank arrays ko n size ka resize karo.
    // Step 2: size[i] = 1 — har node apne aap ek set; rank[i] = 0.
    // Step 3: parent[i] = i for all i — shuru mein n alag disjoint sets.
    // Step 4: Ab UNION operations se sets merge honge.
    Union_find(int n)
    {
        parent.resize(n);  // Parent array ko n size ka banao
        size.resize(n, 1); // Initially har element ka apna set hai, size = 1
        rank.resize(n, 0); // Initially sabka rank 0 hai (single node tree)

        // Initially har element apne aap ko point karta hai (apna khud ka representative)
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Har node ka parent apne aap ko banate hain
        }
    }

    // Step 1: Agar x == parent[x] hai to x khud root hai — return x.
    // Step 2: Warna recursively parent chain follow karo find(parent[x]) se.
    // Step 3: PATH COMPRESSION: return parent[x] = find(parent[x]) — saare nodes direct root ko point.
    // Step 4: Future find calls O(α(n)) ≈ constant time ho jayenge.
    // Step 5: Root return karo — ye element ke set ka representative hai.
    int find(int x)
    {
        // Base case: agar x khud apna parent hai, matlab ye root/representative hai
        if (x == parent[x])
            return x;

        // PATH COMPRESSION MAGIC:
        // Recursively parent dhundkte time, direct root ko point karte jao
        // Ye future find operations ko O(1) bana deta hai
        return parent[x] = find(parent[x]);

        /*
        PATH COMPRESSION EXAMPLE:
        Before: 1->2->3->4 (to find root of 1, we traverse 1->2->3->4)
        After:  1->4, 2->4, 3->4 (ab sabko direct root point karta hai)
        */
    }

    // Step 1: find(x) aur find(y) se dono ke roots nikalo — x_parent, y_parent.
    // Step 2: Same root ho to already same set — return, kuch nahi karna.
    // Step 3: Bada size wale root ke neeche chhota attach karo — tree flat rehti hai.
    // Step 4: Merge ke baad size[root] += size[other] — total set size update.
    // Step 5: Equal size ho to koi ek root banao, size add karo, rank++ optional.
    void UNION_BY_SIZE(int x, int y)
    {
        int x_parent = find(x); // x ka ultimate representative dhundo
        int y_parent = find(y); // y ka ultimate representative dhundo

        // Agar dono elements already same set mein hain, kuch nahi karna
        if (x_parent == y_parent)
            return;

        // SIZE-BASED MERGING: Chota set ko bade set mein attach karo
        // Ye tree ki height kam rakhta hai

        if (size[x_parent] > size[y_parent])
        {
            // x_parent ka set bada hai, y_parent ko x_parent mein merge karo
            parent[y_parent] = x_parent;
            size[x_parent] += size[y_parent]; // Total size update karo
        }
        else if (size[x_parent] < size[y_parent])
        {
            // y_parent ka set bada hai, x_parent ko y_parent mein merge karo
            parent[x_parent] = y_parent;
            size[y_parent] += size[x_parent]; // Total size update karo
        }
        else
        {
            // Dono sets ka size same hai, koi bhi ko root bana sakte hain
            parent[x_parent] = y_parent;
            size[y_parent] += size[x_parent]; // Total size update karo
            rank[y_parent]++;                 // Rank increase karo (height badh gaya)
        }
    }

    // Step 1: x aur y ke roots find() se nikalo.
    // Step 2: Same root → already connected, return.
    // Step 3: Chhoti rank wale tree ko badi rank wale ke parent banao — height control.
    // Step 4: Equal rank ho to ek ko root banao aur rank[root]++ — height ek level badhi.
    // Step 5: Union by rank se tree height O(log n) bound rehti hai.
    void UNION_BY_RANK(int x, int y)
    {
        int x_parent = find(x); // x ka ultimate representative dhundo
        int y_parent = find(y); // y ka ultimate representative dhundo

        // Agar dono elements already same set mein hain, kuch nahi karna
        if (x_parent == y_parent)
            return;

        // RANK-BASED MERGING: Chhoti height wale tree ko badi height wale mein attach karo
        // Ye overall tree height minimize karta hai

        if (rank[x_parent] < rank[y_parent])
        {
            // y_parent ki rank zyada hai, x_parent ko uske neeche attach karo
            parent[x_parent] = y_parent;
            // Note: Rank change nahi hoga kyunki chhoti height badi mein merge hui
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            // x_parent ki rank zyada hai, y_parent ko uske neeche attach karo
            parent[y_parent] = x_parent;
            // Note: Rank change nahi hoga kyunki chhoti height badi mein merge hui
        }
        else
        {
            // Dono ki rank same hai, koi bhi ko root banao aur rank increase karo
            parent[x_parent] = y_parent;
            rank[y_parent]++; // Rank increase karo (height ek level badh gaya)
        }
    }

    // Step 1: components = 0 initialize karo.
    // Step 2: Har index i par check — parent[i] == i matlab i ek root/set leader hai.
    // Step 3: Har root ke liye components++ — ek alag connected group count hua.
    // Step 4: Poori parent array scan karke total disjoint sets return karo.
    int countComponents()
    {
        int components = 0; // Components counter initialize karo

        // Har element check karo
        for (int i = 0; i < parent.size(); ++i)
        {
            // Agar koi element apne aap ko point karta hai, matlab wo root/representative hai
            if (parent[i] == i)
                components++; // Ek nayi component mili
        }
        return components;
    }
};

int main()
{
    // 6 elements (0 to 5) ke saath Union_find object create karo
    Union_find Union_find(6);

    /*
    INITIAL STATE:
    Sets: {0}, {1}, {2}, {3}, {4}, {5}
    Total components: 6
    */

    // STEP-BY-STEP UNION OPERATIONS:

    // Operation 1: 0 aur 1 ko merge karo using UNION_BY_SIZE
    Union_find.UNION_BY_SIZE(0, 1);
    /* After: Sets become {0,1}, {2}, {3}, {4}, {5} */

    // Operation 2: 0 aur 2 ko merge karo (actually {0,1} aur {2} merge hoga)
    Union_find.UNION_BY_SIZE(0, 2);
    /* After: Sets become {0,1,2}, {3}, {4}, {5} */

    // Operation 3: 3 aur 4 ko merge karo using UNION_BY_RANK
    Union_find.UNION_BY_RANK(3, 4);
    /* After: Sets become {0,1,2}, {3,4}, {5} */

    // Operation 4: 1 aur 3 ko merge karo (actually {0,1,2} aur {3,4} merge hoga)
    Union_find.UNION_BY_SIZE(1, 3);
    /* After: Sets become {0,1,2,3,4}, {5} */

    // CONNECTIVITY CHECKS:

    // Check 1: Kya 0 aur 3 same set mein hain?
    cout << "Are 0 and 3 in the same set? "
         << (Union_find.find(0) == Union_find.find(3) ? "Yes" : "No") << endl;
    // Output: Yes (kyunki dono {0,1,2,3,4} set mein hain)

    // Check 2: Kya 0 aur 5 same set mein hain?
    cout << "Are 0 and 5 in the same set? "
         << (Union_find.find(0) == Union_find.find(5) ? "Yes" : "No") << endl;
    // Output: No (5 alag set mein hai)

    // Check 3: Kya 3 aur 4 same set mein hain?
    cout << "Are 3 and 4 in the same set? "
         << (Union_find.find(3) == Union_find.find(4) ? "Yes" : "No") << endl;
    // Output: Yes (dono {0,1,2,3,4} set mein hain)

    // FINAL COMPONENT COUNT:
    cout << "Number of connected components: " << Union_find.countComponents() << endl;
    // Output: 2 (sets: {0,1,2,3,4} aur {5})

    return 0;
}

/*
DETAILED ALGORITHM ANALYSIS:

1. TIME COMPLEXITY:
   - Find operation: O(α(n)) where α is inverse Ackermann function
   - Union operation: O(α(n))
   - α(n) is practically constant (≤ 4 for all practical values)
   - Without optimizations: O(n) per operation in worst case

2. SPACE COMPLEXITY: O(n)
   - Parent array: O(n)
   - Size array: O(n)
   - Rank array: O(n)

3. KEY OPTIMIZATIONS:
   a) PATH COMPRESSION in find():
      - Makes all nodes in path point directly to root
      - Future finds become O(1)

   b) UNION BY SIZE:
      - Smaller set always attached to larger set
      - Prevents deep trees

   c) UNION BY RANK:
      - Tree with smaller height attached to tree with larger height
      - Keeps overall tree height minimum

4. APPLICATIONS:
   - Kruskal's Minimum Spanning Tree Algorithm
   - Cycle detection in undirected graphs
   - Connected components in graphs
   - Dynamic connectivity problems
   - Percolation problems

5. REAL-WORLD ANALOGY:
   - Think of it like merging companies
   - Find = "Which parent company does this subsidiary belong to?"
   - Union = "Merge two companies under one parent"
   - Path compression = "Update all records to point directly to ultimate parent"

6. COMMON INTERVIEW QUESTIONS:
   - Number of islands
   - Friend circles / Connected components
   - Redundant connections
   - Union of intervals
   - Accounts merge

REMEMBER: Union-Find is one of the most important data structures in competitive programming aur graph problems mein bahut use hota hai!
*/