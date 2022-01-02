#include "network/broker.hpp"

namespace quick_pack{

Broker::Broker(){
  this->m_fb_builder = new flatbuffers::FlatBufferBuilder;
  this->m_tmp_sockaddr_in6 = new sockaddr_in6;
}


Broker::~Broker(){
  delete (this->m_fb_builder);
  delete (this->m_tmp_sockaddr_in6);
}


} // namespace quick_pack
