#include "socket/socket_detail_manager.hpp"


namespace quick_pack{

uint32_t SocketDetailManager::add_socket(SocketDetail* d){ // not thread safe
  this->m_id_to_sockdetail[++m_last_id_count]=d;
  d->m_id = this->m_last_id_count;
  return this->m_last_id_count;
}


SocketDetailManager::SocketDetailManager(){
  this->m_last_id_count = 0;
}

SocketDetailManager::~SocketDetailManager(){
  for (auto & a : m_id_to_sockdetail){
    delete(a.second);
  }
}

} // namespace quick_pack
