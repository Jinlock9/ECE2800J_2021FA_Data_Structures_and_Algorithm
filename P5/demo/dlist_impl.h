/* Operational methods */

template <class T>
bool Dlist<T>::isEmpty() const {

    return ((first == NULL) && (last == NULL));

}
// EFFECTS: returns true if list is empty, false otherwise

template <class T>
void Dlist<T>::insertFront(T *op) {

    node *np = new node;
    np->next = NULL;
    np->prev = NULL;
    np->op = NULL;

    np->op = op;

    if(Dlist<T>::isEmpty()) {
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
// MODIFIES this
// EFFECTS inserts o at the front of the list

template <class T>
void Dlist<T>::insertBack(T *op) {

    node *np = new node;

    np->op = op;

    if(Dlist<T>::isEmpty()) {
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
// MODIFIES this
// EFFECTS inserts o at the back of the list

template <class T>
T* Dlist<T>::removeFront() {

    if(Dlist<T>::isEmpty()) {
        emptyList e;
        throw e;
    }

    node *victim = first;
    T *result = victim->op;
    first = victim->next;
    if(first == NULL) {
        last = NULL;
    }
    delete victim;

    return result;

}
// MODIFIES this
// EFFECTS removes and returns first object from non-empty list
//         throws an instance of emptyList if empty

template <class T>
T* Dlist<T>::removeBack() {

    if(Dlist<T>::isEmpty()) {
        emptyList e;
        throw e;
    }

    node *victim = last;
    T *result = victim->op;
    last = victim->prev;
    if(last == NULL) {
        first = NULL;
    }
    delete victim;

    return result;

}
// MODIFIES this
// EFFECTS removes and returns last object from non-empty list
//         throws an instance of emptyList if empty

/* Maintenance methods */

// constructor
template <class T>
Dlist<T>::Dlist() : first(0), last(0) {}

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


/* Utility methods */

template <class T>
void Dlist<T>::removeAll() {

    while(!Dlist<T>::isEmpty()) {
        Dlist<T>::removeFront();
    }

}
// EFFECT: called by destructor/operator= to remove and destroy
//         all list elements

template <class T>
void Dlist<T>::copyAll(const Dlist &l) {

    if(*l.isEmpty()) return;

    Dlist<T> *temp = new Dlist;
    temp->first = l->first->next;
    temp->last = l->last;
    copyAll(temp);
    insertFront(l->first->op);
    delete temp;

}
// EFFECT: called by copy constructor/operator= to copy elements
//         from a source instance l to this instance