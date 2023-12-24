#ifndef CLIENSERVERECN_EXCHANGE_HPP
#define CLIENSERVERECN_EXCHANGE_HPP

#include <vector>

#include "concurrentqueue/concurrentqueue.h"

#include "Account.hpp"

namespace exchange {

struct OrderBuy {
  boost::uuids::uuid id_ = boost::uuids::random_generator()();
  Account* asset_account{};
  Account* cur_account{};
  MoneyType bid{};
  QuantityType amount{};
  Time created_at = Time::clock::now();
};

struct OrderSell {
  boost::uuids::uuid id_ = boost::uuids::random_generator()();
  Account* asset_account{};
  Account* cur_account{};
  MoneyType ask{};
  QuantityType amount{};
  Time created_at = Time::clock::now();
};


class Exchange {
public:

  static constexpr MoneyType kMinQueuePrice = 5000;  // 50 rubles
  static constexpr MoneyType kMaxSellPrice = 15000; // 150 rubles
  static constexpr std::size_t kQueueSize = kMaxSellPrice - kMinQueuePrice + 1;

  void Bid(OrderBuy&& order);

  void Ask(OrderSell&& order);

private:

  [[nodiscard]] static std::size_t PriceToQueueIndex(MoneyType price);

  std::vector<moodycamel::ConcurrentQueue<OrderSell>> sell_queue_{kQueueSize};
  std::vector<moodycamel::ConcurrentQueue<OrderBuy>> buy_queue_{kQueueSize};
};

} // namespace exchange

#endif // CLIENSERVERECN_EXCHANGE_HPP
