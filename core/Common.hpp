#ifndef CLIENSERVERECN_COMMON_HPP
#define CLIENSERVERECN_COMMON_HPP

#include <string>
#include <chrono>

static short port = 5555;

namespace Requests
{
    static std::string Registration = "Reg";
    static std::string Hello = "Hel";
}

namespace exchange {

using MoneyType = long long;  // cents or kopecks
using QuantityType = long long;
using Time = std::chrono::time_point<std::chrono::system_clock>;

enum class Currency {
  RUB, USD
};

}  // namespace exchange

#endif //CLIENSERVERECN_COMMON_HPP
