#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):owner_(owner), has_credit_(has_credit), balance_(0.0), credit_limit_(0.0){
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(double limit) {
    if (has_credit_) {
        credit_limit_ = limit;
    }
    else {
        std::cout << "Cannot set credit limit: the account has no credit card"<<std::endl;
    }
}

bool Account::save_money(double amount) {
    if (amount > 0.0) {
        balance_ += amount;
        return true;
    }
    return false;
}

bool Account::take_money(double amount) {
    if (amount > 0.0 && (balance_ - amount) >= -credit_limit_) {
        balance_ -= amount;
         std::cout<< amount <<" euros taken: new balance of "<< iban_<<" is "<<balance_ <<" euros"<<std::endl;
        return true;
    }
    else if((balance_ - amount)< -credit_limit_){
        std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
        return false;
    }
    std::cout<<"Cannot take money: balance underflow"<<std::endl;
    return false;
}

bool Account::transfer_to(Account& target, double amount) {
    if (amount > 0.0 && (balance_ - amount) >= -credit_limit_) {
        if (target.save_money(amount)) {
            balance_ -= amount;
            std::cout<<amount<<" euros taken: "<<"new balance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
            return true;
        }
    }
    std::cout<<"Cannot take money: balance underflow"<<std::endl;
    std::cout<<"Transfer from "<< iban_ <<" failed"<<std::endl;

    return false;
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}
