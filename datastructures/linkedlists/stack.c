

class Stack
{
public:
    Stack();
    ~Stack();
    void push( void *data );
    void *pop();
protected:
    // Element struct needed only internally
    typedef struct Element {
        struct Element *next;
        void *data;
    } Element;

    Element *head;
};

Stack::Stack() {
    head = NULL;
    return;
}

Stack::~Stack() {
    while( head ){
        Element *next = head->next;
        delete head;
        head = next;
    }
    return;
}

void Stack::push( void *data ){
    //Allocation error will throw exception
    Element *element = new Element;
    element->data = data;
    element->next = head;
    head = element;
    return;
}

void *Stack::pop() {
    Element *popElement = head;
    void *data;

    /* Assume StackError exception class is defined elsewhere */
    if( head == NULL )
        throw StackError( E_EMPTY );

    data = head->data;
    head = head->next;
    delete popElement;
    return data;
}

