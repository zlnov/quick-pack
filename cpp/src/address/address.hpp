#ifndef QUICK_PACK_ADDRESS_HPP
#define QUICK_PACK_ADDRESS_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace quick_pack{
enum ipv { v4, v6};
struct Address{
  ipv m_ip_type;
  sockaddr_in * m_ipv4_addr = nullptr;
  sockaddr_in6 * m_ipv6_addr = nullptr;
  sockaddr * m_common_addr = nullptr;
  socklen_t m_common_addr_len = 0;    // can be longer that sizeof(sockaddr)

  Address(sockaddr_in6*);
  Address(const std::string &p_host, const uint32_t &p_port, bool p_is_ipv6);
  ~Address();
};
} // namespace quick_pack
#endif
