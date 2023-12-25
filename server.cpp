#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "io/handler.hpp"
#include "core/common.hpp"

using boost::asio::ip::tcp;

using namespace exchange;

class session {
public:
  session(boost::asio::io_service &io_service) : socket_(io_service) {}

  tcp::socket &socket() { return socket_; }

  void start() {
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  // Обработка полученного сообщения.
  void handle_read(const boost::system::error_code &error,
                   size_t bytes_transferred) {
    if (!error) {
      data_[bytes_transferred] = '\0';

      // Парсим json, который пришёл нам в сообщении.

      auto response = io::Handle(data_);

      boost::asio::async_write(socket_,
                               boost::asio::buffer(response, response.size()),
                               boost::bind(&session::handle_write, this,
                                           boost::asio::placeholders::error));
    } else {
      std::cout << "Connection closed" << std::endl;
      delete this;
    }
  }

  void handle_write(const boost::system::error_code &error) {
    if (!error) {
      socket_.async_read_some(
          boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    } else {
      delete this;
    }
  }

private:
  tcp::socket socket_;
  enum { max_length = 16 };
  char data_[max_length];
};

class server {
public:
  server(boost::asio::io_service &io_service)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    std::cout << "Server started! Listen " << port << " port" << std::endl;

    session *new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&server::handle_accept, this,
                                       new_session,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(session *new_session,
                     const boost::system::error_code &error) {
    if (!error) {
      std::cout << "Connected" << std::endl;
      new_session->start();
      new_session = new session(io_service_);
      acceptor_.async_accept(new_session->socket(),
                             boost::bind(&server::handle_accept, this,
                                         new_session,
                                         boost::asio::placeholders::error));
    } else {
      delete new_session;
    }
  }

private:
  boost::asio::io_service &io_service_;
  tcp::acceptor acceptor_;
};

int main() {

  try {
    boost::asio::io_service io_service;

    server s(io_service);

    io_service.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}