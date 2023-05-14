// dlist_impl.h

#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

/***********************/
/* Operational methods */
/***********************/

template <class T>
bool Dlist<T>::isEmpty() const
// EFFECTS: returns true if list is empty, false otherwise
{

    return ((first == NULL) && (last == NULL)); // It is empty when both first and last is NULL

}

template <class T>
void Dlist<T>::insertFront(T *op)
// MODIFIES this
// EFFECTS inserts o at the front of the list
{

    node *np = new node; // New node to be inserted

    np->op = op;

    if(Dlist<T>::isEmpty()) { // if Dlist is empty
        np->prev = NULL;
        np->next = NULL;
        first = last = np;
    }
    else {
        first->prev = np;
        np->next = first;
        np->prev = NULL;
        first = np;
    }

}

template <class T>
void Dlist<T>::insertBack(T *op)
// MODIFIES this
// EFFECTS inserts o at the back of the list
{

    node *np = new node; // New node to be inserted

    np->op = op;

    if(Dlist<T>::isEmpty()) { // if Dlist is empty
        np->prev = NULL;
        np->next = NULL;
        first = last = np;
    }
    else {
        last->next = np;
        np->prev = last;
        np->next = NULL;
        last = np;
    }

}

template <class T>
T* Dlist<T>::removeFront()
// MODIFIES this
// EFFECTS removes and returns first object from non-empty list
//         throws an instance of emptyList if empty
{

    if(Dlist<T>::isEmpty()) { // if the list is already empty
        emptyList e;
        throw e; // throw exception
    }

    node *victim = first; // create victim to be deleted
    T* result = victim->op;
    first = victim->next;
    if(first == NULL) { // if first is NULL, then the list is empty
        last = NULL; // therefore, last also need to point NULL
    }
    else {
        first->prev = NULL;
    }

    delete victim; // free victim

    return result; // return op

}

template <class T>
T* Dlist<T>::removeBack()
// MODIFIES this
// EFFECTS removes and returns last object from non-empty list
//         throws an instance of emptyList if empty
{

    if(Dlist<T>::isEmpty()) { // if the list is already empty
        emptyList e;
        throw e; // throw exception
    }

    node *victim = last; // create victim to be deleted
    T* result = victim->op;
    last = victim->prev;
    if(last == NULL) { // if last is NULL, then the list is empty
        first = NULL; // therefore, first also need to point NULL
    }
    else {
        last->next = NULL;
    }

    delete victim; // free victim

    return result; // return op

}

/***********************/
/* Maintenance methods */
/***********************/

// constructor
template <class T>
Dlist<T>::Dlist() : first(0), last(0) {} // Initialize first and last point NULL

// copy constructor
template <class T>
Dlist<T>::Dlist(const Dlist &l) : first(0), last(0) {

    Dlist<T>::copyAll(l);

}

// assignment operator
template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {

    if(this != &l) {
        Dlist<T>::removeAll();
        Dlist<T>::copyAll(l);
    }
    return *this;

}

// destructor
template <class T>
Dlist<T>::~Dlist() {

    Dlist<T>::removeAll();

}

/***********************/
/*** Utility methods ***/
/***********************/

template <class T>
void Dlist<T>::removeAll()
// EFFECT: called by destructor/operator= to remove and destroy
//         all list elements
{

    while(!Dlist<T>::isEmpty()) {
        delete Dlist<T>::removeFront(); // free the op which Dlist<T>::removeFront() returns
    }

}

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
// EFFECT: called by copy constructor/operator= to copy elements
//         from a source instance l to this instance
{

    node *np = new node; // create a temporary node
    np = l->first;
    this->first->prev = NULL; // previous node of first node should be NULL

    while(!np) { // np is moved from first to last until it becomes NULL
        T *temp = np->op;
        Dlist<T>::insertBack(temp); // insert op to this
        np = np->next; // move to the next node
    }

    this->last->next = NULL; // next node of last node should be NULL

    delete np; // free the temporary node

}

#endif /* __DLIST_IMPL_H__ */