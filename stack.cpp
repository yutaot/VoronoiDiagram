/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack. That is, the element
 * should go at the beginning of the list.
 *
 * @note This function must be O(1)!
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T newItem)
{
    /**
     * @todo Your code here!
     */
     myStack.pushR(newItem);
}

/**
 * Removes the object on top of the Stack, and returns it. That is, remove
 * the element at the beginning of the list. You may assume this function
 * is only called when the Stack is not empty.
 *
 * @note This function must be O(1)!
 *
 * @return The element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop()
{
    /**
     * @todo Your code here!
     */
     return myStack.popR();
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Stack<T>::add(T theItem)
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to add the element to the Stack.
     */
     myStack.pushR(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Stack<T>::remove()
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to remove an element from the Stack and return it.
     */
     return myStack.popR();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. It should
 * look at the beginning of the list. You may assume this function is only
 * called when the Stack is not empty.
 *
 * @return The value of the element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek()
{
    /**
     * @todo Your code here!
     */
     return myStack.peekR();
}

/**
 * Determines if the Stack is empty.
 *
 * @note This function must be O(1)! Note that the std::list's size()
 *	function is O(n), so you should not attempt to use it here.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const
{
    /**
     * @todo Your code here!
     */
     return myStack.isEmpty();
}
