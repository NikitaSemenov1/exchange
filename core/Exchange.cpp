#include "Exchange.hpp"


namespace exchange {

namespace {

void MakeDeal(OrderBuy &buy_order, OrderSell &sell_order) {
  auto dealPrice = sell_order.created_at < buy_order.created_at
                       ? sell_order.ask
                       : buy_order.bid;
  auto dealAmount = std::min(sell_order.amount, buy_order.amount);

  sell_order.amount -= dealAmount;
  buy_order.amount -= dealAmount;

  sell_order.asset_account->Withdraw(dealAmount);
  sell_order.cur_account->Deposit(dealAmount * dealPrice);

  buy_order.asset_account->Deposit(dealAmount);
  buy_order.cur_account->Withdraw(dealAmount * dealPrice);
}

}


void Exchange::Bid(OrderBuy &&order) {
  for (MoneyType price_it = kMinQueuePrice; price_it <= order.bid; ++price_it) {
    auto &queue = sell_queue_[PriceToQueueIndex(price_it)];
    OrderSell matched_order;

    while(queue.try_dequeue(matched_order)) {

      MakeDeal(order, matched_order);

      if (matched_order.amount != 0) {
        queue.enqueue(std::move(matched_order));
        return;
      }
    }
  }

  buy_queue_[PriceToQueueIndex(order.bid)].enqueue(std::move(order));
}

void Exchange::Ask(OrderSell &&order) {
  for (MoneyType price_it = kMaxSellPrice; price_it >= order.ask; --price_it) {
    auto &queue = buy_queue_[PriceToQueueIndex(price_it)];
    OrderBuy matched_order;

    while(queue.try_dequeue(matched_order)) {

      MakeDeal(matched_order, order);

      if (matched_order.amount != 0) {
        queue.enqueue(std::move(matched_order));
        return;
      }
    }
  }
  sell_queue_[PriceToQueueIndex(order.ask)].enqueue(std::move(order));

}

std::size_t Exchange::PriceToQueueIndex(MoneyType price) {
  price = std::max(price, kMinQueuePrice);
  price = std::min(price, kMaxSellPrice);

  return price - kMinQueuePrice;
}

}  // namespace exchange
