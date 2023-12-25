#include "handler.hpp"

#include <algorithm>

namespace exchange {

std::string io::Handle(std::string request) {
  std::ranges::reverse(request);

  return request;
}

} // namespace exchange
