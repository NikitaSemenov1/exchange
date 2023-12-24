#include "Account.hpp"

namespace exchange {

MoneyType Account::Balance() const {
  return balance_;
}
void Account::Deposit(MoneyType amount) {
  balance_ += amount;
}
void Account::Withdraw(MoneyType amount) {
  balance_ -= amount;
}

}  // namespace exchange
