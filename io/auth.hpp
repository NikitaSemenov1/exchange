#pragma once

#include <string>

namespace exchange::io {

struct RegisterRequest {
  std::string login;
  std::string password;
  std::string name;
};

struct LoginRequest {
  std::string login;
  std::string password;
};

struct LoginResponse {
  std::string auth_token;
};

}  // namespace exchange::io