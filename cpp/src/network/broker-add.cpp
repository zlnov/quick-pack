#include "broker.hpp"

namespace quick_pack{
uint32_t Broker::add_internal_socket(const std::string &p_host, const std::string &p_port, bool p_is_ipv6){
  auto sock = new SocketDetail();
  sock->bind(p_host, p_port, p_is_ipv6);
  return this->m_internal_socket_detail_manager.add_socket(sock);
}

uint32_t Broker::add_external_address(const std::string &p_host, const uint32_t p_port, bool p_is_ipv6){
  auto addr = new Address(p_host, p_port, p_is_ipv6);
  auto addrdetail = new AddressDetail();
  addrdetail->m_address = addr;
  return this->m_external_address_detail_manager.add_addressdetail(addrdetail);
}

AddressDetail* Broker::add_new_ipv46_address(sockaddr_in6* addr){
  auto addrdetail = new AddressDetail();
  auto address = new Address(addr);
  addrdetail->m_address=address;
  this->m_external_address_detail_manager.add_addressdetail(addrdetail);
  return addrdetail;
}

} // namespace quick_pack
