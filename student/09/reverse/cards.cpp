#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}

bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        // Deck is empty
        return false;
    }

    id = top_->data; // Retrieve the data of the top card
    std::shared_ptr<Card_data> temp = top_; // Save the current top card
    top_ = top_->next; // Move the top pointer to the next card
    temp.reset(); // Release the memory of the removed card

    return true;
}

void Cards::reverse() {
    std::shared_ptr<Card_data> current = top_;
    std::shared_ptr<Card_data> prev = nullptr;
    std::shared_ptr<Card_data> next = nullptr;

    while (current != nullptr) {
        next = current->next; // Save the next card
        current->next = prev;  // Reverse the link

        // Move one step forward in the list
        prev = current;
        current = next;
    }

    top_ = prev; // Update the top pointer to the new front of the reversed list
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
