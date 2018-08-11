#ifndef __SUFFIX_TREE_H_INCLUDES__
#define __SUFFIX_TREE_H_INCLUDES__

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cassert>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::setw;
using std::flush;
using std::endl;

const int MAX_LENGTH = 1000;
const int HASH_TABLE_SIZE = 2179;

class Suffix {
    public :
        int origin_node;
        int first_char_index;
        int last_char_index;
        Suffix( int node, int start, int stop )
            : origin_node( node ),
              first_char_index( start ),
              last_char_index( stop ){};
        int Explicit(){ return first_char_index > last_char_index; }
        int Implicit(){ return last_char_index >= first_char_index; }
        void Canonize();
};

class Edge {
    public :
        int first_char_index;
        int last_char_index;
        int end_node;
        int start_node;
        void Insert();
        void Remove();
        Edge();
        Edge( int init_first_char_index,
              int init_last_char_index,
              int parent_node );
        int SplitEdge( Suffix &s );
        static Edge Find( int node, int c );
        static int Hash( int node, int c );
};

class Node {
    public :
        int suffix_node;
        Node() { suffix_node = -1; }
        static int Count;
};

Edge Edges[ HASH_TABLE_SIZE ];
int Node::Count = 1;
Node Nodes[ MAX_LENGTH * 2 ];
char T[ MAX_LENGTH ];
int N;

Edge::Edge()
{
    start_node = -1;
}


Edge::Edge( int init_first, int init_last, int parent_node )
{
    first_char_index = init_first;
    last_char_index = init_last;
    start_node = parent_node;
    end_node = Node::Count++;
}

int Edge::Hash( int node, int c )
{
    return ( ( node << 8 ) + c ) % HASH_TABLE_SIZE;
}

void Edge::Insert()
{
    int i = Hash( start_node, T[ first_char_index ] );
    while ( Edges[ i ].start_node != -1 )
        i = ++i % HASH_TABLE_SIZE;
    Edges[ i ] = *this;
}

void Edge::Remove()
{
    int i = Hash( start_node, T[ first_char_index ] );
    while ( Edges[ i ].start_node != start_node ||
            Edges[ i ].first_char_index != first_char_index )
        i = ++i % HASH_TABLE_SIZE;
    for ( ; ; ) {
        Edges[ i ].start_node = -1;
        int j = i;
        for ( ; ; ) {
            i = ++i % HASH_TABLE_SIZE;
            if ( Edges[ i ].start_node == -1 )
                return;
            int r = Hash( Edges[ i ].start_node, T[ Edges[ i ].first_char_index ] );
            if ( i >= r && r > j )
                continue;
            if ( r > j && j > i )
                continue;
            if ( j > i && i >= r )
                continue;
            break;
        }
        Edges[ j ] = Edges[ i ];
    }
}

Edge Edge::Find( int node, int c )
{
    int i = Hash( node, c );
    for ( ; ; ) {
        if ( Edges[ i ].start_node == node )
            if ( c == T[ Edges[ i ].first_char_index ] )
                return Edges[ i ];
        if ( Edges[ i ].start_node == -1 )
            return Edges[ i ];
        i = ++i % HASH_TABLE_SIZE;
    }
}

int Edge::SplitEdge( Suffix &s )
{
    Remove();
    Edge *new_edge =
      new Edge( first_char_index,
                first_char_index + s.last_char_index - s.first_char_index,
                s.origin_node );
    new_edge->Insert();
    Nodes[ new_edge->end_node ].suffix_node = s.origin_node;
    first_char_index += s.last_char_index - s.first_char_index + 1;
    start_node = new_edge->end_node;
    Insert();
    return new_edge->end_node;
}

void dump_edges( int current_n )
{
    cout << " Start  End  Suf  First Last  String\n";
    for ( int j = 0 ; j < HASH_TABLE_SIZE ; j++ ) {
        Edge *s = Edges + j;
        if ( s->start_node == -1 )
            continue;
        cout << setw( 5 ) << s->start_node << " "
             << setw( 5 ) << s->end_node << " "
             << setw( 3 ) << Nodes[ s->end_node ].suffix_node << " "
             << setw( 5 ) << s->first_char_index << " "
             << setw( 6 ) << s->last_char_index << "  ";
        int top;
        if ( current_n > s->last_char_index )
            top = s->last_char_index;
        else
            top = current_n;
        for ( int l = s->first_char_index ;
                  l <= top;
                  l++ )
            cout << T[ l ];
        cout << "\n";
    }
}

void Suffix::Canonize()
{
    if ( !Explicit() ) {
        Edge edge = Edge::Find( origin_node, T[ first_char_index ] );
        int edge_span = edge.last_char_index - edge.first_char_index;
        while ( edge_span <= ( last_char_index - first_char_index ) ) {
            first_char_index = first_char_index + edge_span + 1;
            origin_node = edge.end_node;
            if ( first_char_index <= last_char_index ) {
               edge = Edge::Find( edge.end_node, T[ first_char_index ] );
                edge_span = edge.last_char_index - edge.first_char_index;
            };
        }
    }
}

void AddPrefix( Suffix &active, int last_char_index )
{
    int parent_node;
    int last_parent_node = -1;

    for ( ; ; ) {
        Edge edge;
        parent_node = active.origin_node;
//
// Step 1 is to try and find a matching edge for the given node.
// If a matching edge exists, we are done adding edges, so we break
// out of this big loop.
//
        if ( active.Explicit() ) {
            edge = Edge::Find( active.origin_node, T[ last_char_index ] );
            if ( edge.start_node != -1 )
                break;
        } else { //implicit node, a little more complicated
            edge = Edge::Find( active.origin_node, T[ active.first_char_index ] );
            int span = active.last_char_index - active.first_char_index;
            if ( T[ edge.first_char_index + span + 1 ] == T[ last_char_index ] )
                break;
            parent_node = edge.SplitEdge( active );
        }

        Edge *new_edge = new Edge( last_char_index, N, parent_node );
        new_edge->Insert();
        if ( last_parent_node > 0 )
            Nodes[ last_parent_node ].suffix_node = parent_node;
        last_parent_node = parent_node;

        if ( active.origin_node == 0 )
            active.first_char_index++;
        else
            active.origin_node = Nodes[ active.origin_node ].suffix_node;
        active.Canonize();
    }
    if ( last_parent_node > 0 )
        Nodes[ last_parent_node ].suffix_node = parent_node;
    active.last_char_index++;  //Now the endpoint is the next active point
    active.Canonize();
};

char CurrentString[ MAX_LENGTH ];
char GoodSuffixes[ MAX_LENGTH ];
char BranchCount[ MAX_LENGTH * 2 ] = { 0 };

int walk_tree( int start_node, int last_char_so_far )
{
    int edges = 0;
    for ( int i = 0 ; i < 256 ; i++ ) {
        Edge edge = Edge::Find( start_node, i );
        if ( edge.start_node != -1 ) {
            if ( BranchCount[ edge.start_node ] < 0 )
                cerr << "Logic error on node "
                     << edge.start_node
                     << '\n';
            BranchCount[ edge.start_node ]++;
            edges++;
            int l = last_char_so_far;
            for ( int j = edge.first_char_index ; j <= edge.last_char_index ; j++ )
                CurrentString[ l++ ] = T[ j ];
            CurrentString[ l ] = '\0';
            if ( walk_tree( edge.end_node, l ) ) {
                if ( BranchCount[ edge.end_node ] > 0 )
                        cerr << "Logic error on node "
                             << edge.end_node
                             << "\n";
                BranchCount[ edge.end_node ]--;
            }
        }
    }

    if ( edges == 0 ) {
        cout << "Suffix : ";
        for ( int m = 0 ; m < last_char_so_far ; m++ )
            cout << CurrentString[ m ];
        cout << "\n";
        GoodSuffixes[ strlen( CurrentString ) - 1 ]++;
        cout << "comparing: " << ( T + N - strlen( CurrentString ) + 1 )
             << " to " << CurrentString << endl;
        if ( strcmp(T + N - strlen(CurrentString) + 1, CurrentString ) != 0 )
            cout << "Comparison failure!\n";
        return 1;
    } else
        return 0;
}

void validate()
{
    for ( int i = 0 ; i < N ; i++ )
        GoodSuffixes[ i ] = 0;
    walk_tree( 0, 0 );
    int error = 0;
    for ( int i = 0 ; i < N ; i++ )
        if ( GoodSuffixes[ i ] != 1 ) {
            cout << "Suffix " << i << " count wrong!\n";
            error++;
        }
    if ( error == 0 )
        cout << "All Suffixes present!\n";
    int leaf_count = 0;
    int branch_count = 0;
    for ( int i = 0 ; i < Node::Count ; i++ ) {
        if ( BranchCount[ i ] == 0 )
            cout << "Logic error on node "
                 << i
                 << ", not a leaf or internal node!\n";
        else if ( BranchCount[ i ] == -1 )
            leaf_count++;
        else
            branch_count += BranchCount[ i ];
    }
    cout << "Leaf count : "
         << leaf_count
         << ( leaf_count == ( N + 1 ) ? " OK" : " Error!" )
         << "\n";
    cout << "Branch count : "
         << branch_count
         << ( branch_count == (Node::Count - 1) ? " OK" : " Error!" )
         << endl;
}

#endif
