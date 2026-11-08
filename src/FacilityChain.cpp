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
    size++; // iterate size
}

void FacilityChain::removeFromList(Facility* fac) {
    Facility* temp = head;

    if (temp == NULL) {
        // list is empty
        cout << "list is empty, cannot remove" << endl;
        return;
    }
    
    if (temp->id == fac->id) { // if the element we're looking to remove is the head,
        if (temp->next != NULL) { // and if the list is not only one element long,
            head = temp->next; // then, set the head to the predecessor of the element we're looking for
            temp->next = NULL; // and exclude it from the list
            delete temp; // then we can delete it
            size--; // decrement size
        } else { // otherwise, the head (and tail) is the only element in the list
            temp->next = NULL; // se we exclude it from the list
            head = NULL; // and deinitialize the list by making the head null
            tail = NULL;  // and the tail
            delete temp; // then we can delete it
            size--; // decrement size
        }

    }

    while (temp != tail) { // Otherwise, loop until the correct element is found, or we reach the end
        if (temp->next->id == fac->id) { // if the next element is the correct element,

            if (temp->next != tail) { // if the found element is not the tail,
                temp->next = temp->next->next; // then it has a predecessor, and we can repair the reference
            } 
            fac->next = NULL; // and regardless, the found element should not point into the list
            delete fac; // then we can delete it
            size--; // decrement size
        }

        temp = temp->next; // iterate through elements
    } 

    cout << fac->id << " not found in list..." << endl;
}

Facility* FacilityChain::LinearSearch(string id) {
    if (head == NULL) return NULL; // if the list is empty, exit early

    Facility* temp = head;

    do {
        if (temp->id == id) { // if the id matches
            return temp; // then return it
        }

    } while (temp != tail);
    return NULL; // couldn't find, so we return NULL
}

void FacilityChain::ListAll() {
    if (size == 0) { // if the head is not set then this chain is empty,
        return; // so we can exit early
    }

    Facility* temp = head; // start at the head

    while (temp != tail) { // until we're at the end of the chain
        // print out the element
        cout << temp->name << ": " << temp->id << endl;
        cout << " Located at: " << temp->building << endl;
        cout << " Category: " << temp->category << endl;

        // if (temp->next != NULL) {
        //     temp = temp->next; // step to the next element
        // } else break;
    }

    // print out the tail
    cout << tail->name << ": " << tail->id << endl;
    cout << " Located at: " << tail->building << endl;
    cout << " Category: " << tail->category << endl;
}

int FacilityChain::Size() {
    return size;
}

int FacilityChain::NumCollisions() {
    if (size > 1) return size - 1;
    else return 0;
}