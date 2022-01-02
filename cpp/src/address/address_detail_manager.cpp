#include "address/address_detail_manager.hpp"
namespace quick_pack{

AddressDetailManager::AddressDetailManager(){
}

AddressDetailManager::~AddressDetailManager(){
  for (auto &a : this->m_id_to_addrdetail){
    delete(a.second);
  }
}

uint32_t AddressDetailManager::add_addressdetail(AddressDetail* const addrd){ // pointer is const, data is not
  addrd->m_id = ++this->m_last_id_count;
  this->m_id_to_addrdetail[addrd->m_id] = addrd;
  if(addrd->m_address->m_ip_type == v4){   // ipv4
    this->m_sockaddr_to_addrdetail[addrd->m_address->m_ipv4_addr] = addrd;
  }
  else{            // ipv6
    this->m_sockaddr6_to_addrdetail[addrd->m_address->m_ipv6_addr] = addrd;
  }
  return addrd->m_id;
}


}// namespace quick_pack
