#include "socket/socket_detail.hpp"
#include "address/address.hpp"
#include <netdb.h>
#include <cstring>
#include <system_error>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

namespace quick_pack{

void SocketDetail::bind(const std::string &p_host, const std::string &p_port, bool &p_is_ipv6){
  int sockfd;
  int rv;
  addrinfo hints, *my_info;
  memset(&hints, 0, sizeof hints);
  if (p_is_ipv6) {
    hints.ai_family = AF_INET6;
  }
  else{
    hints.ai_family = AF_INET;
  }

  hints.ai_socktype = SOCK_DGRAM;

  if ((rv = getaddrinfo(p_host.c_str(), p_port.c_str(), &hints, &my_info)) != 0) {
    throw std::system_error(errno, std::generic_category(), std::string("getaddrinfo() failed") + gai_strerror(rv));
  }
  auto p = my_info;
  for(; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("listener: socket");
      continue;
    }

    if (::bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("listener: bind");
      continue;
    }
    break;
  }
  freeaddrinfo(my_info);
  if (p == NULL) {
    throw std::system_error(errno, std::generic_category(), "failed to create/bind socket");
  }

  if (rv =fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0){
    throw std::system_error(errno, std::generic_category(), std::string("fcntl() failed") + gai_strerror(rv));
  }
  this->m_socket = sockfd;
}

void SocketDetail::bind(Address* address){
  if (address == nullptr){
    throw std::runtime_error("attempt to call quick_pack::socket_detail::bind(Address* address) with a NULL address");
  }
  int sockfd;
  int ai_family;
  int ai_socktype = SOCK_DGRAM;
  int ai_protocol = IPPROTO_UDP;
  socklen_t ai_addrlen = address->m_common_addr_len;
  sockaddr * ai_addr = address->m_common_addr;
  switch (address->m_ip_type){
    case v4:
      ai_family = AF_INET;
      break;
    case v6:
      ai_family = AF_INET6;
      break;
    default:
      throw std::runtime_error("quick_pack::socket_detail::bind(Address* address) encounters an unknown address->m_ip_type");
      break;
  }
  if (ai_addr == nullptr){
    throw std::runtime_error("quick_pack::socket_detail::bind(Address* address) underlaying sockaddr_in/sockaddr_in6 pointer is NULL");
  }
  if ((sockfd = socket(ai_family, ai_socktype, ai_protocol)) == -1) {
    throw std::runtime_error("quick_pack::socket_detail::bind(Address* address) socket() failed");
  }
  if (::bind(sockfd, ai_addr, ai_addrlen) == -1) {
    close(sockfd);
    throw std::runtime_error("quick_pack::socket_detail::bind(Address* address) bind() failed");
  }
  if (int rv =fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0){
    throw std::system_error(errno, std::generic_category(), std::string("fcntl() failed") + gai_strerror(rv));
  }
  this->m_socket = sockfd;
}

SocketDetail::~SocketDetail(){
  close(this->m_socket);
}
} // namespace quick_pack
