#include <iostream>
#include <cstdlib>
#include "p2.h"
 
int size(list_t list) 
// EFFECTS: Returns the number of elements in "list".
// 	Returns zero if "list" is empty.
{
	if(list_isEmpty(list)) {
		return 0;
	}
	else {
		return 1 + size(list_rest(list));
	}
} 

int sum(list_t list) 
// EFFECTS: Returns the sum of each element in "list".
// 	Returns zero if "list" is empty.
{
	if(list_isEmpty(list)) {
		return 0;
	}
	else {
		return list_first(list) + sum(list_rest(list));
	}
}

int product(list_t list) 
// EFFECTS: Returns the product of each element in "list".
// 	Returns one if "list" is empty.
{
	if(list_isEmpty(list)) {
		return 1;
	}
	else {
		return list_first(list) * product(list_rest(list));
	}
}

int accumulate(list_t list, int (*fn)(int, int), int base) 
// REQUIRES: "fn" must be associative.
// EFFECTS: Returns "base" if "list" is empty.
// 	Returns fn(list_first(list), accumulate(list_rest(list), fn, base) otherwise.
{
	if(list_isEmpty(list)) {
		return base;
	}
	else {
		return fn(list_first(list), accumulate(list_rest(list), fn, base));
	}
}


static list_t reverse_helper(list_t new_list, list_t old_list) 
// EFFECTS: Returns new list with the elements in reverse order.
{
	if(list_isEmpty(old_list)) {
		return new_list;
	}
	else {
		return reverse_helper(list_make(list_first(old_list), new_list), list_rest(old_list));
	}
}

list_t reverse(list_t list) 
// EFFECTS: Returns the reverse of "list".
{
	if(list_isEmpty(list)) {
		return list;
	}
	else {
		return reverse_helper(list_make(list_first(list), list_make()), list_rest(list));
	}
}


static list_t append_helper(list_t first, list_t second) 
// EFFECTS: Returns the first list appended by the second list.
{
	if(list_isEmpty(first)) {
		return second;
	}
	else {
		return append_helper(list_rest(first), list_make(list_first(first), second));
	}
}

list_t append(list_t first, list_t second) 
// EFFECTS: Returns the list (first second). Appended list is the first list is followed by the second list.
{
	if(list_isEmpty(first)) {
		return second;
	}
	else {
		first = reverse(first);
		return append_helper(first, second);
	}
}

list_t filter_odd(list_t list) 
// EFFECTS: Returns a new list containing only the elements of the
// 	original "list" which are odd in value, 
// 	in the order in which they appeared in list.
{
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



list_t filter_even(list_t list) 
// EFFECTS: Returns a new list containing only the elements of the
// 	original "list" which are even in value, 
// 	in the order in which they appeared in list.
{
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

list_t filter(list_t list, bool (*fn)(int)) 
// EFFECTS: Returns a list containing precisely the elements of "list"
// 	for which the predicate fn() evaluates to true, in the
// 	order in which they appeared in list.
{
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

list_t insert_list(list_t first, list_t second, unsigned int n) 
// REQUIRES: n <= the number of elements in "first".
// EFFECTS: Returns a list comprising the first n elements of
// 	"first", followed by all elements of "second",
// 	followed by any remaining elements of "first".
{
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


static list_t chop_helper(list_t list, unsigned int n) 
// EFFECTS: Returns the list with n elements of the original list.
{
	if((list_isEmpty(list)) || (n == 0)) {
		return list_make();
	}
	else {
		return list_make(list_first(list), chop_helper(list_rest(list), n-1));
	}
}

list_t chop(list_t list, unsigned int n) 
// REQUIRES: "list" has at least n elements.
// EFFECTS: Returns the list equal to "list" without its last n
// 	elements.
{
	int nn = size(list) - n;
	return chop_helper(list, nn);
}


//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************


int tree_sum(tree_t tree) 
// EFFECTS: Returns the sum of all elements in "tree". 
// 	Returns zero if "tree" is empty.
{
	if(tree_isEmpty(tree)) {
		return 0;
	}
	else {
		return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
	}
}

static int search_helper(tree_t tree, int key) 
// EFFECTS: Returns the number of elements which value is equal to key.
{
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

bool tree_search(tree_t tree, int key) 
// EFFECTS: Returns true if there exists any element in "tree"
// 	whose value is "key". Otherwise, return "false".
{
	if(search_helper(tree, key) > 0) {
		return true;
	}
	else {
		return false;
	}
}

static int max(int a, int b) 
// EFFECTS: Returns the larger integer.
{
	if(a >= b) {
		return a;
	}
	else {
		return b;
	}
}

int depth(tree_t tree) 
// EFFECTS: Returns the depth of "tree", which equals the number of
// 	layers of nodes in the tree.
// 	Returns zero is "tree" is empty.
{
	if(tree_isEmpty(tree)) {
		return 0;
	}
	else {
		return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));
	}
}

static int min(int a, int b) 
// EFFECTS: Returns the smaller integer.
{
	if(a <= b) {
		return a;
	}
	else {
		return b;
	}
}

int tree_min(tree_t tree) 
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
{
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

list_t traversal(tree_t tree) 
// EFFECTS: Returns the elements of "tree" in a list using an
// 	in-order traversal. An in-order traversal prints 
// 	the "left most" element first, then the second-left-most, 
// 	and so on, until the right-most element is printed.
//
// 	For any node, all the elements of its left subtree
// 	are considered as on the left of that node and
// 	all the elements of its right subtree are considered as
// 	on the right of that node.
{
	if(tree_isEmpty(tree)) {
		return list_make();
	}
	else {
		return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
	}
}

static int path_helper(tree_t tree, int sum) 
// EFFECTS: Returns 1 if and only if "tree" has at least one root-to-leaf path
// 	such that adding all elements along the path equals "sum", otherwise 0.
{
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

bool tree_hasPathSum(tree_t tree, int sum) 
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
// 	path such that adding all elements along the path equals "sum".
{
	if(path_helper(tree, sum) > 0) {
		return true;
	}
	else {
		return false;
	}
}

static int cover_helper(tree_t A, tree_t B) 
// EFFECTS: Returns 0 if tree A is covered by tree B, otherwise larger than 0.
{
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

bool covered_by(tree_t A, tree_t B) 
// EFFECTS: Returns true if tree A is covered by tree B.
{
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

       
bool contained_by(tree_t A, tree_t B) 
// EFFECTS: Returns true if tree A is covered by tree B
// 	or a subtree of B.
{
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


tree_t insert_tree(int elt, tree_t tree) 
// REQUIRES: "tree" is a sorted binary tree.
// EFFECTS: Returns a new tree with elt inserted at a leaf such that 
// 	the resulting tree is also a sorted binary tree.
{
	if(tree_isEmpty(tree)) {
		return tree_make(elt, tree_make(), tree_make());
	}
	else {
		if(elt < tree_elt(tree)) {
			return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
		}
		else {
			return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
		}
	}
}
