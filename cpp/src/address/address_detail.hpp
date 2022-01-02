#ifndef QUICK_PACK_ADDRESS_DETAIL_HPP
#define QUICK_PACK_ADDRESS_DETAIL_HPP
#include "address/address.hpp"
#include <chrono>
// #include <stdint.h>
namespace quick_pack {

struct AddressDetail{
private:

  std::chrono::time_point<std::chrono::system_clock>  m_last_recv;

public:
  uint32_t m_in_seq = 0;
  uint32_t m_out_seq = 0;
  Address *m_address = nullptr;
  uint32_t m_id = 0;
  inline void update_last_recv(){
    this->m_last_recv = std::chrono::system_clock::now();
  }
  AddressDetail();
  ~AddressDetail();
};

} // namespace quick_pack
#endif
