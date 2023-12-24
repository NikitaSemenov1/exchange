#ifndef CLIENSERVERECN_ACCOUNT_HPP
#define CLIENSERVERECN_ACCOUNT_HPP

#include <atomic>
#include <map>
#include <memory>

#include <boost/uuid/uuid_generators.hpp>

#include "Common.hpp"

namespace exchange {;

class Account {
public:
  Account(Currency currency, MoneyType initial_balance) : currency_{currency}, balance_{initial_balance} {}
  Account(const boost::uuids::uuid id, Currency currency, MoneyType initial_balance) : id_{id}, currency_{currency}, balance_{initial_balance} {}

  [[nodiscard]] MoneyType Balance() const;

  void Deposit(MoneyType amount);

  void Withdraw(MoneyType amount);

private:
  boost::uuids::uuid id_ = boost::uuids::random_generator()();
  const Currency currency_;
  std::atomic<MoneyType> balance_;
};

class User {
public:

  std::string CreateAccount(Currency currency) {
    auto id = boost::uuids::random_generator()();
    accounts_[id] = std::make_unique<Account>(id, currency, 0);
  }

private:
  std::map<boost::uuids::uuid, std::unique_ptr<Account>> accounts_;
};

}  // namespace exchange

#endif // CLIENSERVERECN_ACCOUNT_HPP
