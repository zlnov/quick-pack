#include "address/address_detail.hpp"
namespace quick_pack {

AddressDetail::AddressDetail(){
}

AddressDetail::~AddressDetail(){
  delete(m_address);
}




} // namespace quick_pack
