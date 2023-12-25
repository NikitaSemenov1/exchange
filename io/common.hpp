#pragma once

#include <nlohmann/json.hpp>

namespace exchange::io {

using namespace nlohmann;

enum class RequestType {
  kRegister, kLogin, kBuy, kSell,
};

NLOHMANN_JSON_SERIALIZE_ENUM(RequestType, {
    {kRegister, "REGISTER"},
    {kLogin, "LOGIN"},
    {kBuy, "BUY"},
    {kSell, "SELL"},
})

enum class ResponseStatus {
  kOk, kBadRequest, kInternalError,
};


NLOHMANN_JSON_SERIALIZE_ENUM(RequestType, {
    {kOk, "OK"},
    {kBadRequest, "BAD_REQUEST"},
    {kInternalError, "INTERNAL_ERROR"},
})

}  // namespace exchange::io