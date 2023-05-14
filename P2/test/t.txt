#include <iostream>
#include <cassert>
#include "recursive.h"

using namespace std;

// Implementation of the list ADT 
const unsigned int  list_node_id = 0x11341134;
const unsigned int  list_empty_id = 0x22452245;

struct list_node {
    unsigned int      ln_id;    // Are we really a list_node?
    int               ln_elt;   // This element
    struct list_node *ln_rest;  // rest of this list, null for empty node
} list_node_t;


static struct list_node *
list_checkValid(list_t list)
    // MODIFIES: cerr
    // EFFECTS: assert if lnp does not appear to be a valid list.
    //          writing an appropriate error message to cerr.
{
    struct list_node *lnp = (struct list_node *)list;

    if ((lnp->ln_id != list_node_id) && (lnp->ln_id != list_empty_id)) {
        cerr << "Error: user passed invalid list\n";
        assert(0);
    }

    return lnp;
}

static void
list_checkNonEmpty(list_t list)
    // MODIFIES: cerr
    // EFFECTS: assert if lnp is an empty list, 
    //          writing an appropriate error message to cerr.
{
    if (list_isEmpty(list)) {
        cerr << "error: user passed empty list where non-empty requried\n";
        assert(0);
    }
}

static void
not_allocated()
{
    cerr << "Your test case is too large for this machine\n";
    cerr << "Try using a smaller test case\n";
    assert(0);
}

bool
list_isEmpty(list_t list)
{
    struct list_node *lnp = list_checkValid(list);
    return (lnp->ln_id == list_empty_id);
}

list_t
list_make()
{
    struct list_node *newp = 0; 

    try {
        newp = new struct list_node;
    } catch (bad_alloc &a) {
        not_allocated();
    }

    newp->ln_id = list_empty_id;
    newp->ln_rest = NULL;
    
    return (list_t)(newp);
}

list_t
list_make(int elt, list_t list) 
{
    struct list_node *newp = 0; 
    struct list_node *restp = list_checkValid(list);

    try {
        newp = new struct list_node;
    } catch (bad_alloc &a) {
        not_allocated();
    }

    newp->ln_id = list_node_id;
    newp->ln_elt = elt;
    newp->ln_rest = restp;
    
    return (list_t)(newp);
}

int
list_first(list_t list) 
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return lnp->ln_elt;
}

list_t
list_rest(list_t list) 
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return (list_t)(lnp->ln_rest);
}

static void
list_print_helper(list_t list)
    // MODIFIES: cout
    // EFFECTS: prints list contents to cout, with no parens
{
    if (list_isEmpty(list)) {
        return;
    } else {
        cout << list_first(list) << " ";
        list_print_helper(list_rest(list));
    }
}

void
list_print(list_t list)
{
    cout << "( ";
    list_print_helper(list);
    cout << ")";
}

/**************************************************/

// Implementation of the tree ADT
const unsigned int  tree_node_id = 0x45ee45ee;
const unsigned int  tree_empty_id = 0x56ff56ff;

struct tree_node {
    unsigned int       tn_id;    // Are we really a tree_node?
    int                tn_elt;   // This element
    struct tree_node  *tn_left;  // left subtree
    struct tree_node  *tn_right; // right subtree
};

static struct tree_node *
tree_checkValid(tree_t tree)
    // MODIFIES: cerr
    // EFFECTS: assert if tnp does not appear to be a valid tree, 
    //          writing an appropriate error message to cerr.
{
    struct tree_node *tnp = (struct tree_node *)tree;

    if ((tnp->tn_id != tree_node_id) && (tnp->tn_id != tree_empty_id)) {
        cerr << "Error: user passed invalid tree\n";
        assert(0);
    }
    return tnp;
}

static void
tree_checkNonEmpty(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        cerr << "Error: user passed empty tree\n";
        assert(0);
    }
}

bool
tree_isEmpty(tree_t tree)
{
    struct tree_node *tnp = tree_checkValid(tree);
    return (tnp->tn_id == tree_empty_id);
}

tree_t
tree_make()
{
    struct tree_node *tnp = 0;

    try {
        tnp = new struct tree_node;
    } catch (bad_alloc &a) {
        not_allocated();
    }

    tnp->tn_id = tree_empty_id;
    tnp->tn_left = NULL;
    tnp->tn_right = NULL;

    return (tree_t)(tnp);
}

tree_t
tree_make(int elt, tree_t left, tree_t right)
{
    struct tree_node *tnp = 0;

    try {
        tnp = new struct tree_node;
    } catch (bad_alloc &a) {
        not_allocated();
    }

    if (!tree_isEmpty(left)) {
        tree_checkValid(left);
    }
    if (!tree_isEmpty(right)) {
        tree_checkValid(right);
    }

    tnp->tn_id = tree_node_id;
    tnp->tn_elt = elt;
    tnp->tn_left = (struct tree_node *)left;
    tnp->tn_right = (struct tree_node *)right;

    return (tree_t)(tnp);
}

int
tree_elt(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return tnp->tn_elt;
}

tree_t
tree_left(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return (tree_t)(tnp->tn_left);
}

tree_t
tree_right(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return (tree_t)(tnp->tn_right);
}

static void
print_spaces(int spaces)
    // MODIFIES: cout
    // EFFECTS: prints n spaces
{
    while (spaces--) {
        cout << "  ";
    }
}

static void
tree_print_internal_old(tree_t tree, int spaces)
    // MODIFIES: cout
    // EFFECTS: prints tree contents recursively, with newlines 
    //          for each node, with each level indented
{
    print_spaces(spaces);
    if (tree_isEmpty(tree)) {
        cout << "( )\n";
    } else {
        cout << "(" << tree_elt(tree) << "\n";
        tree_print_internal_old(tree_left(tree), spaces+1);
        tree_print_internal_old(tree_right(tree), spaces+1);
        print_spaces(spaces);
        cout << " )\n";
    }
}

static void
tree_print_internal(tree_t tree, int spaces)
    // MODIFIES: cout
    // EFFECTS: prints tree contents recursively, with newlines 
    //          for each node, with each level indented
{
    if(tree_isEmpty(tree))
        return;
    else
    {
        tree_print_internal(tree_left(tree), spaces+2);
        print_spaces(spaces+1);
        cout << "/" << endl;
        print_spaces(spaces);
        cout << tree_elt(tree) << endl;
        print_spaces(spaces+1);
        cout << "\\" << endl;
        tree_print_internal(tree_right(tree), spaces+2);
    }
}

void
tree_print(tree_t tree)
{
    //tree_print_internal_old(tree, 0);
    tree_print_internal(tree, 0);
}

static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

int size(list_t list) {
	if(list_isEmpty(list)) {
		return 0;
	}
	else {
		return 1 + size(list_rest(list));
	}
} 
/* 
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/ 

int sum(list_t list) {
	if(list_isEmpty(list)) {
		return 0;
	}
	else {
		return list_first(list) + sum(list_rest(list));
	}
}
/* 
// EFFECTS: Returns the sum of each element in "list".
//          Returns zero if "list" is empty.
*/ 

int product(list_t list) {
	if(list_isEmpty(list)) {
		return 1;
	}
	else {
		return list_first(list) * product(list_rest(list));
	}
}
/* 
// EFFECTS: Returns the product of each element in "list".
//          Returns one if "list" is empty.
*/

static int sum(int a, int b) {
	return a + b;
}
static int product(int a, int b) {
	return a * b;
}

int accumulate(list_t list, int (*fn)(int, int), int base) {
	if(list_isEmpty(list)) {
		return base;
	}
	else {
		return fn(list_first(list), accumulate(list_rest(list), fn, base));
	}
}
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list), 
//                      accumulate(list_rest(list), fn, base) otherwise.
//
// For example, if you have the following function:
//
//           int add(int x, int y);
//
// Then the following invocation returns the sum of all elements:
//
//           accumulate(list, add, 0);
*/ 

static list_t reverse_helper(list_t new_list, list_t old_list) {
	if(list_isEmpty(old_list)) {
		return new_list;
	}
	else {
		return reverse_helper(list_make(list_first(old_list), new_list), list_rest(old_list));
	}
}

list_t reverse(list_t list) {
	return reverse_helper(list_make(list_first(list), list_make()), list_rest(list));
}
/*
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
*/

static list_t append_helper(list_t first, list_t second) {
	if(list_isEmpty(first)) {
		return second;
	}
	else {
		return append_helper(list_rest(first), list_make(list_first(first), second));
	}
}

list_t append(list_t first, list_t second) {
	if(list_isEmpty(first)) {
		return second;
	}
	else {
		first = reverse(first);
		return append_helper(first, second);
	}
}
/*
// EFFECTS: Returns the list (first second).
//
// For example: append(( 2 4 6 ), ( 1 3 )) gives
// the list ( 2 4 6 1 3 ).
*/ 

list_t filter_odd(list_t list) {
	if(list_isEmpty(list)) {
		return list_make();
	}
	else if((list_first(list) % 2) != 0) {
		return list_make(list_first(list), filter_odd(list_rest(list)));
	}
	else {
		return filter_odd(list_rest(list));
	}
}
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value, 
//          in the order in which they appeared in list.
//
// For example, if you apply filter_odd to the list ( 3 4 1 5 6 ),
// you would get the list ( 3 1 5 ).
*/ 

list_t filter_even(list_t list) {
	if(list_isEmpty(list)) {
		return list_make();
	}
	else if(list_first(list) % 2 == 0) {
		return list_make(list_first(list), filter_even(list_rest(list)));
	}
	else {
		return filter_even(list_rest(list));
	}
}
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are even in value, 
//          in the order in which they appeared in list.
*/
static bool odd(int a) {
	if(a % 2 != 0) {
		return true;
	}
	else{
		return false;
	}
}
static bool even(int a) {
	if(a % 2 == 0) {
		return true;
	}
	else{
		return false;
	}
}
list_t filter(list_t list, bool (*fn)(int)) {
	if(list_isEmpty(list)) {
		return list_make();
	}
	else if(fn(list_first(list))) {
		return list_make(list_first(list), filter(list_rest(list), fn));
	}
	else {
		return filter(list_rest(list), fn);
	}
}
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
// For example, if predicate bool odd(int a) returns true if a is odd,
// then the function filter(list, odd) has the same behavior as the
// function filter_odd(list).
*/

list_t insert_list(list_t first, list_t second, unsigned int n) {
	if(list_isEmpty(first) && list_isEmpty(second)) {
		return list_make();
	}
	else if(list_isEmpty(second)) {
		return list_make(list_first(first), insert_list(list_rest(first), second, n));
	}
	else if(n == 0) {
		return list_make(list_first(second), insert_list(first, list_rest(second), n)); 
	}
	else {
		return list_make(list_first(first), insert_list(list_rest(first), second, n-1));
	}
}
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
//
//     For example: insert (( 1 2 3 ), ( 4 5 6 ), 2)
//            gives ( 1 2 4 5 6 3 ).
*/

static list_t chop_helper(list_t list, unsigned int n) {
	if((list_isEmpty(list)) || (n == 0)) {
		return list_make();
	}
	else {
		return list_make(list_first(list), chop_helper(list_rest(list), n-1));
	}
}

list_t chop(list_t list, unsigned int n) {
	int nn = size(list) - n;
	return chop_helper(list, nn);
}
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree) {
	if(tree_isEmpty(tree)) {
		return 0;
	}
	else {
		return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
	}
}
/*
// EFFECTS: Returns the sum of all elements in "tree". 
//          Returns zero if "tree" is empty.
*/

static int search_helper(tree_t tree, int key) {
	if(tree_isEmpty(tree)) {
		return 0;
	}
	else if(tree_elt(tree) == key) {
		return 1;
	}
	else {
		return search_helper(tree_left(tree), key) + search_helper(tree_right(tree), key);
	}
}
bool tree_search(tree_t tree, int key) {
	if(search_helper(tree, key) > 0) {
		return true;
	}
	else {
		return false;
	}
}
/*
// EFFECTS: Returns true if there exists any element in "tree"
//          whose value is "key". Otherwise, return "false".
*/
static int max(int a, int b) {
	if(a >= b) {
		return a;
	}
	else {
		return b;
	}
}

int depth(tree_t tree) {
	if(tree_isEmpty(tree)) {
		return 0;
	}
	else {
		return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));
	}
}
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero is "tree" is empty.
//
// For example, the tree
// 
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3        8
//                        / \      / \
//                       6   7
//                      / \ / \
//
// has depth 4.
// The element 4 is on the first layer.
// The elements 2 and 5 are on the second layer.
// The elements 3 and 8 are on the third layer.
// The elements 6 and 7 are on the fourth layer.
//
*/

static int min(int a, int b) {
	if(a <= b) {
		return a;
	}
	else {
		return b;
	}
}

int tree_min(tree_t tree) {
	if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
		return tree_elt(tree);
	}
	else if(tree_isEmpty(tree_left(tree))) {
		return min(tree_elt(tree), tree_min(tree_right(tree)));
	}
	else if(tree_isEmpty(tree_right(tree))) {
		return min(tree_elt(tree), tree_min(tree_left(tree)));
	}
	else {
		return min(tree_elt(tree), min(tree_min(tree_left(tree)), tree_min(tree_right(tree))));
	}
}
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/

list_t traversal(tree_t tree) {
	if(tree_isEmpty(tree)) {
		return list_make();
	}
	else {
		return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
	}
}
/* 
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints 
//          the "left most" element first, then the second-left-most, 
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
//
// For example, the tree:
// 
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3 
//                        / \
//
// would return the list
//
//       ( 2 3 4 5 )
// 
// An empty tree would print as:
// 
//       ( )
//
*/

static int path_helper(tree_t tree, int sum) {
	if(tree_isEmpty(tree)) {
		if(sum == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return path_helper(tree_left(tree), (sum - tree_elt(tree))) + path_helper(tree_right(tree), (sum - tree_elt(tree)));
	}
}

bool tree_hasPathSum(tree_t tree, int sum) {
	if(path_helper(tree, sum) > 0) {
		return true;
	}
	else {
		return false;
	}
}
/* 
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
//          path such that adding all elements along the path equals "sum".
//          
// A root-to-leaf path is a sequence of elements in a tree starting
// with the root element and proceeding downward to a leaf (an element
// with no children).
//
// An empty tree has no root-to-leaf path.
//
// For example, the tree:
// 
//                           4
//                         /   \
//                        /     \
//                       1       5
//                      / \     / \
//                     3   6 
//                    / \ / \
//
// has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
// Given sum = 9, the path 4->5 has the sum 9, so the function
// should return true. If sum = 10, since no path has the sum 10,
// the function should return false.
// 
*/

static int cover_helper(tree_t A, tree_t B) {
	if(tree_isEmpty(A)) {
		return 0;
	}
	else if(tree_isEmpty(B)) {
		return 1;
	}
	else {
		if(tree_elt(A) == tree_elt(B)) {
			return 0 + cover_helper(tree_left(A), tree_left(B)) + cover_helper(tree_right(A), tree_right(B));
		}
		else {
			return 1 + cover_helper(tree_left(A), tree_left(B)) + cover_helper(tree_right(A), tree_right(B));
		}
	}
}

bool covered_by(tree_t A, tree_t B) {
	if(tree_isEmpty(A)) {
		return true;
	}
	else if(tree_isEmpty(B)) {
		return false;
	}
	else {
		if(cover_helper(A, B) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/
       
bool contained_by(tree_t A, tree_t B) {
	if(tree_isEmpty(A)) {
		return true;
	}
	else if(tree_isEmpty(B)) {
		return false;
	}
	else {
		if(covered_by(A, B)) {
			return true;
		}
		else {
			return (contained_by(A, tree_left(B)) || contained_by(A, tree_right(B)));
		}
	}
}

int main()
{
    /*
    int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i * (-1), listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }

    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;

    listB = append(listA, listB);
    listA = reverse(listA);
    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;

    if(list_equal(listA, listA_answer) 
        && list_equal(listB, listB_answer))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
    */
    list_t l1 = list_make();
    list_t l2 = list_make();
    list_t l3 = list_make();
    for(int i = 5; i>0; i--)
    {
        l2 = list_make(i, l2);
        l3 = list_make((i+10) * (-1), l3);
    }
    list_print(l1);
    cout<<endl;
    cout<<size(l1)<<endl;
    list_print(l2);
    cout<<endl;
    cout<<size(l2)<<endl;

    list_print(l1);
    cout<<endl;
    cout<<sum(l1)<<endl;
    list_print(l2);
    cout<<endl;
    cout<<sum(l2)<<endl;
    list_print(l3);
    cout<<endl;
    cout<<sum(l3)<<endl;

    list_print(l1);
    cout<<endl;
    cout<<product(l1)<<endl;
    list_print(l2);
    cout<<endl;
    cout<<product(l2)<<endl;
    list_print(l3);
    cout<<endl;
    cout<<product(l3)<<endl;

    list_print(l2);
    cout<<endl;
    cout<<accumulate(l2, sum, 0)<<endl;
    list_print(l3);
    cout<<endl;
    cout<<accumulate(l3, product, 1)<<endl;

    list_t l4 = reverse(l2);
    list_t l5 = reverse(l3);
    list_print(l2);
    cout<<endl;
    list_print(l4);
    cout<<endl;
    list_print(l3);
    cout<<endl;
    list_print(l5);
    cout<<endl;

    list_t l6 = append(l2, l3);
    list_print(l6);
    cout<<endl;

    l4 = filter_odd(l2);
    l5 = filter_even(l3);
    list_print(l2);
    cout<<endl;
    list_print(l4);
    cout<<endl;
    list_print(l3);
    cout<<endl;
    list_print(l5);
    cout<<endl;

    l4 = filter(l2, odd);
    l5 = filter(l3, even);
    list_print(l2);
    cout<<endl;
    list_print(l4);
    cout<<endl;
    list_print(l3);
    cout<<endl;
    list_print(l5);
    cout<<endl;

    l6 = insert_list(l2, l3, 2);
    list_print(l6);
    cout<<endl;

    list_t l7 = chop(l6, 2);
    list_print(l7);
    cout<<endl;
    cout << endl;


    tree_t e = tree_make();
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    tree_t t1 = tree_make(1, tree_make(2, tree_make(4, tree_make(), tree_make()), tree_make(5, tree_make(), tree_make())),  
	       tree_make(3, tree_make(6, tree_make(), tree_make()), tree_make(7, tree_make(), tree_make())));

    tree_t t2 = tree_make(6, tree_make(5, tree_make(2, tree_make(), tree_make()), tree_make(1, tree_make(), tree_make())),  
	       tree_make(4, tree_make(2, tree_make(), tree_make()), tree_make(7, tree_make(), tree_make())));

    tree_print(start);
    cout << endl;
    cout << endl;
    tree_print(end);
    cout << endl;
    cout << endl;
    tree_print(t1);
    cout << endl;
    cout << endl;
    tree_print(t2);
    cout << endl;
    cout << endl;


    cout<<tree_sum(t1)<<endl;
    if(tree_search(t1, 9)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }
    cout<<depth(t1)<<endl;
    cout<<tree_min(t2)<<endl;
    list_print(traversal(t1));
    cout<<endl;
    if(tree_hasPathSum(t1, 5)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }    

    cout << endl;
    cout << endl;
    cout<<tree_sum(e)<<endl;
    if(tree_search(e, 3)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }
    cout<<depth(e)<<endl;
    cout<<tree_min(end)<<endl;
    list_print(traversal(e));
    cout<<endl;
    if(tree_hasPathSum(e, 5)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }    

    cout << endl;
    cout << endl;
    tree_t t3 = tree_make(1, tree_make(2, tree_make(4, tree_make(), tree_make()), tree_make(5, tree_make(), tree_make())),  
	       tree_make(3, tree_make(6, tree_make(), tree_make()), tree_make(7, tree_make(), tree_make())));

    tree_t t4 = tree_make(1, tree_make(2, tree_make(4, tree_make(), tree_make()), tree_make(5, tree_make(), tree_make())), tree_make());
    //tree_t t4 = tree_make(2, tree_make(2, tree_make(), tree_make(5, tree_make(), tree_make())), tree_make());
    
    if(covered_by(t4, t3)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   
    if(covered_by(t2, t1)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   

    cout << endl;
    cout << endl;
    tree_t t5 = tree_make(1, tree_make(2, tree_make(4, tree_make(), tree_make()), tree_make(5, tree_make(), tree_make())),  
	       tree_make(3, tree_make(6, tree_make(), tree_make()), tree_make(7, tree_make(), tree_make())));

    //tree_t t6 = tree_make(3, tree_make(6, tree_make(), tree_make()), tree_make());
    tree_t t6 = tree_make(2, tree_make(4, tree_make(), tree_make()), tree_make(5, tree_make(), tree_make()));

    if(contained_by(t4, t3)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   
    if(contained_by(t6, t5)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   
    if(contained_by(t3, t4)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   
    if(contained_by(t5, t6)) {
    	cout<<"true"<<endl;
    }
    else {
    	cout<<"false"<<endl;
    }   
}
