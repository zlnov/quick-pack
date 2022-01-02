#ifndef QUICK_PACK_SOCKET_DETAIL_MANAGER_HPP
#define QUICK_PACK_SOCKET_DETAIL_MANAGER_HPP
#include "socket/socket_detail.hpp"
#include <unordered_map>
namespace quick_pack{
class SocketDetailManager{
  uint32_t m_last_id_count;

public:
  SocketDetailManager();
  ~SocketDetailManager();
  std::unordered_map<uint32_t, SocketDetail*> m_id_to_sockdetail;
  uint32_t add_socket(SocketDetail* d);

};
} // namespace quick_pack
#endif
