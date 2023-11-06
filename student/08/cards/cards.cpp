#include "cards.hh"

// Constructor initializes top_ to nullptr.
Cards::Cards() : top_(nullptr) {}

// Returns a pointer to the topmost card for testing.
Card_data* Cards::get_topmost() {
    return top_;
}

// Adds a new card with the given id as the topmost element.
void Cards::add(int id) {
    Card_data* newCard = new Card_data;
    newCard->data = id;
    newCard->next = top_;
    top_ = newCard;
}

// Prints the content of the data structure from top to bottom.
void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* current = top_;
    int ordinal = 1;

    while (current != nullptr) {
        s << "Card " << ordinal << ": " << current->data << std::endl;
        current = current->next;
        ordinal++;
    }
}

// Removes the topmost card and passes its id value in the reference parameter id to the caller.
// Returns false if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false; // Empty deck
    }

    Card_data* temp = top_;
    id = temp->data;
    top_ = top_->next;
    delete temp;
    return true;
}

// Moves the last element of the data structure as the first one.
// Returns false if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false; // Empty deck
    }

    Card_data* current = top_;
    Card_data* prev = nullptr;

    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }

    current->next = top_;
    top_ = current;
    prev->next = nullptr;

    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom() {
    if (top_ == nullptr || top_->next == nullptr) {
        return false; // Empty deck or only one card
    }

    Card_data* current = top_;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    Card_data* first = top_;
    top_ = top_->next;
    current->next->next = first;
    first->next = nullptr;

    return true;
}

// Helper function for recursive printing from bottom to top.
int Cards::recursive_print(Card_data* top, std::ostream& s) {
    if (top == nullptr) {
        return 0;
    } else {
        int count = recursive_print(top->next, s);
        s << "Card " << count + 1 << ": " << top->data << std::endl;
        return count + 1;
    }
}

// Prints the content of the data structure from bottom to top using recursive_print.
void Cards::print_from_bottom_to_top(std::ostream& s) {
    recursive_print(top_, s);
}

// Destructor deallocates memory when the data structure is no longer needed.
Cards::~Cards() {
    while (top_ != nullptr) {
        Card_data* temp = top_;
        top_ = top_->next;
        delete temp;
    }
}
