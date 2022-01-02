#ifndef QUICK_PACK_SOCKET_DETAIL_HPP
#define QUICK_PACK_SOCKET_DETAIL_HPP

#include "address/address.hpp"
#include <string>
namespace quick_pack{
class SocketDetail{
public:
  int m_socket;
  int m_id;
  void bind(const std::string &p_host, const std::string &p_port, bool &p_is_ipv6);
  void bind(Address* address);
  ~SocketDetail();
};

}// namespace quick_pack
#endif
