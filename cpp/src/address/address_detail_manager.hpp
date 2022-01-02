#ifndef QUICK_PACK_ADDRESS_DETAIL_MANAGER_HPP
#define QUICK_PACK_ADDRESS_DETAIL_MANAGER_HPP
#include "address/address_detail.hpp"
#include "utility/hash/sockaddr_in.hpp"
#include <unordered_map>
#include <stdint.h>
namespace quick_pack{


class AddressDetailManager{
private:
  uint32_t m_last_id_count = 0;
public:
  AddressDetailManager();
  ~AddressDetailManager();
  std::unordered_map<uint32_t, AddressDetail*> m_id_to_addrdetail;
  std::unordered_map<sockaddr_in*, AddressDetail*, util::psockaddr_in_Hash, util::psockaddr_in_Equal> m_sockaddr_to_addrdetail;
  std::unordered_map<sockaddr_in6*, AddressDetail*, util::psockaddr_in6_Hash, util::psockaddr_in6_Equal> m_sockaddr6_to_addrdetail;
  uint32_t add_addressdetail(AddressDetail* const addrd); // not thread safe

};
}// namespace quick_pack
#endif
