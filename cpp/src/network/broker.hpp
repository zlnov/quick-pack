#ifndef QUICK_PACK_BROKER_HPP
#define QUICK_PACK_BROKER_HPP
#include "address/address_detail_manager.hpp"
#include "socket/socket_detail_manager.hpp"
#include "transmission_generated.h"
#include <sys/types.h>

namespace quick_pack{

class Broker{

private:
  AddressDetailManager m_external_address_detail_manager;
  SocketDetailManager m_internal_socket_detail_manager;
  const size_t kBufferCreateSize = 256;
  sockaddr_in6* m_tmp_sockaddr_in6;    // potentially rotate from a pool
  const socklen_t kSockAddrStorageSize = sizeof(sockaddr_in6);
  flatbuffers::FlatBufferBuilder* m_fb_builder; // potentially have a system to rotate multiple builder?


public:
  int32_t send(
    uint32_t p_from_id, // id of m_internal_socket_detail_manager;
    flatbuffers::FlatBufferBuilder* p_builder,
    uint32_t p_dest,
    quick_pack::transmission::AnyMessageTable p_type,
    flatbuffers::Offset<void> p_message   // return from Create*() then .Union()
  );

  int32_t recv(
    uint32_t p_dest_id, // id of m_internal_socket_detail_manager
    const void*& p_message_fb_table_class,
    uint32_t & p_sender,
    void* p_binary_buffer,
    size_t & pr_buffer_len
  );

  Broker();
  ~Broker();

  uint32_t add_internal_socket(const std::string &p_host, const std::string &p_port, bool p_is_ipv6);
  uint32_t add_external_address(const std::string &p_host, const uint32_t p_port, bool p_is_ipv6);

  AddressDetail* add_new_ipv46_address(sockaddr_in6* addr); // both ipv4 and ipv6


  flatbuffers::FlatBufferBuilder* get_fb_builder();

  AddressDetail* load_existing_or_create_new_addrdetail();

};
} // namespace quick_pack
#endif
