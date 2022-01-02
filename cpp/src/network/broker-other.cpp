#include "broker.hpp"
namespace quick_pack{
flatbuffers::FlatBufferBuilder* Broker::get_fb_builder(){
  return m_fb_builder;
}

AddressDetail* Broker::load_existing_or_create_new_addrdetail(){
  // from this->m_tmp_sockaddr_in6;
  if ( this->m_tmp_sockaddr_in6->sin6_family == AF_INET){ // if it's ipv4
    // search for it in ipv4 list, if found then
    auto it = this->m_external_address_detail_manager.m_sockaddr_to_addrdetail.find(\
    (sockaddr_in*)this->m_tmp_sockaddr_in6);
    if (it == this->m_external_address_detail_manager.m_sockaddr_to_addrdetail.end()){
      // ipv4 new
      AddressDetail* out = this->add_new_ipv46_address(this->m_tmp_sockaddr_in6);
      this->m_tmp_sockaddr_in6 = new sockaddr_in6;
      return out;
    }{
      return it->second;
    }
  }
  else{ // else if ipv6
    auto it = this->m_external_address_detail_manager.m_sockaddr6_to_addrdetail.find(\
    this->m_tmp_sockaddr_in6);
    if( it == this->m_external_address_detail_manager.m_sockaddr6_to_addrdetail.end()){
      // ipv6 new
      AddressDetail* out = this->add_new_ipv46_address(this->m_tmp_sockaddr_in6);
      this->m_tmp_sockaddr_in6 = new sockaddr_in6;
      return out;
    }{
      return it->second;
    }
  }
}

} // namespace quick_pack
