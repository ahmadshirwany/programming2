#include "queue.hh"
#include <iostream>

Queue::Queue(unsigned int cycle) : cycle_(cycle) {
    // Other attributes are initialized automatically
}

Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* temp = first_;
        first_ = first_->next;
        delete temp;
    }
}

void Queue::enqueue(string const& reg) {
    if (!is_green_) {
        Vehicle* newVehicle = new Vehicle{reg, nullptr};
        if (first_ == nullptr) {
            first_ = newVehicle;
            last_ = newVehicle;
        } else {
            last_->next = newVehicle;
            last_ = newVehicle;
        }
    }
    else{
        cout<<"GREEN: The vehicle "<< reg <<" need not stop to wait"<<endl;
    }
}

void Queue::switch_light() {
    is_green_ = !is_green_;
    if (is_green_) {
        if (first_ == nullptr) {
                   cout << "GREEN: No vehicles waiting in traffic lights" << endl;
               }
        else {

        unsigned int vehicles_to_release = cycle_;
        cout << "GREEN: Vehicle(s) ";
        while (vehicles_to_release > 0  && first_  != nullptr) {
            Vehicle* temp = first_;
            first_ = first_->next;
            cout <<  temp->reg_num<<" ";
            delete temp;
            vehicles_to_release--;
        }
        if (vehicles_to_release == 0){
             is_green_ = !is_green_;
        }
        cout <<" can go on" << endl;
        }

    } else {
        cout << "RED: No vehicles waiting in traffic lights" << endl;
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const {
    cout <<  "RED" << ": Vehicle(s) ";
    if (first_ != nullptr) {
        Vehicle* current = first_;
        while (current != nullptr) {
            cout << current->reg_num;
            if (current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        cout << " waiting in traffic lights" << endl;
    } else {
        cout << "No vehicles waiting in traffic lights" << endl;
    }
}
