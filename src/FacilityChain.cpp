#include <iostream>
#include "../include/FacilityChain.h"

void FacilityChain::appendToList(Facility* fac) {
        if (head != NULL) { // if list already has elements in it,
            tail->next = fac; // then append the element to the end of list
            tail = fac; // and make it the end of the list
        } else { // if the list is empty,
            head = fac; // then make the new element the first in the list
            tail = head; // and last
        }
}

Facility* FacilityChain::removeFromList(Facility* fac) {
    Facility* temp = head;

    if (temp == NULL) {
        // list is empty
        cout << "list is empty, cannot remove" << endl;
        return NULL;
    }
    
    if (temp->id == fac->id) { // if the element we're looking to remove is the head,
        if (temp->next != NULL) { // and if the list is not only one element long,
            head = temp->next; // then, set the head to the predecessor of the element we're looking for
            temp->next = NULL; // and exclude it from the list
            return temp; // then we can return it
        } else { // otherwise, the head (and tail) is the only element in the list
            temp->next = NULL; // se we exclude it from the list
            head = NULL; // and deinitialize the list by making the head null
            tail = NULL;  // and the tail
            return temp; // then we can return the removed element
        }

    }

    while (temp != tail) { // Otherwise, loop until the correct element is found, or we reach the end
        if (temp->next->id == fac->id) { // if the next element is the correct element,

            if (temp->next != tail) { // if the found element is not the tail,
                temp->next = temp->next->next; // then it has a predecessor, and we can repair the reference
            } 
            fac->next = NULL; // and regardless, the found element should not point into the list
            return fac; // then we can return it, so it can be pushed onto the stack
        }

        temp = temp->next; // iterate through elements
    } 

    cout << fac->id << " not found in list..." << endl;
    return NULL;
}

Facility* FacilityChain::LinearSearch(string id) {
    Facility* temp = head;

    do {
        if (temp->id == id) { // if the id matches
            return temp; // then return it
        }

    } while (temp != tail);
    return NULL; // couldn't find, so we return NULL
}