#include "union_find.hpp"

void Union_Find::onion (const Vertex &p, const Vertex &q)
{
    Component a = find(p);
    Component b = find(q);
    if (a == b) return;
    ncomponents--;
    if (s[a] > s[b]) {
        s[b] += s[a];
        s[a] = b; //or q
    }
    else {
        s[a] += s[b];
        s[b] = a;
    }
}

Component Union_Find::find (const Vertex &p)
{
    if (s[p] < 0 ) return p;
    else return s[ p ] = find( s[ p ] );
}