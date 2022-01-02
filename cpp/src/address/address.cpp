#include "address/address.hpp"
#include <cstdlib>
#include <arpa/inet.h>
namespace quick_pack{
/*
because i think sockaddr_storage is too big and a waste of memory
recv into a buffer on stack then copying over is not runtime efficient
therefore i think i will do the following:

always have a sockaddr_in6 on heap to hold recved address
when we recv data from an existing address, we reuse the sockaddr_in6

when we encounter new address, we will hijack this sockaddr_in6 to make Address
  even if this is  ipv4 sockaddr_in, we will just cast it from the sockaddr_in6 space
after we hijack, we allocate a new sockaddr_in6 object to supply broker
*/

Address::Address(sockaddr_in6 * sa6){
  if (sa6->sin6_family == AF_INET){ // ipv4
    this->m_ip_type=v4;
    this->m_ipv6_addr=sa6;
    this->m_ipv4_addr=(sockaddr_in*)sa6;
    this->m_common_addr = (sockaddr *) this->m_ipv4_addr;
    this->m_common_addr_len = sizeof(sockaddr_in);

  }else{                            // ipv6
    this->m_ip_type=v6;
    this->m_ipv6_addr=sa6;
    this->m_common_addr = (sockaddr *) this->m_ipv6_addr;
    this->m_common_addr_len = sizeof(sockaddr_in6);
  }
}

Address::Address(const std::string &p_host, const uint32_t &p_port, bool p_is_ipv6){
  if(p_is_ipv6){
    this-> m_ip_type = v6;
    this->m_ipv6_addr = new sockaddr_in6;
    this->m_ipv6_addr->sin6_port = htons(p_port);
    ::inet_pton(AF_INET6, p_host.c_str(), &(this->m_ipv6_addr->sin6_addr));
    this->m_common_addr = (sockaddr *) this->m_ipv6_addr;
    this->m_common_addr_len = sizeof(sockaddr_in6);
  }else{
    this-> m_ip_type = v4;
    this->m_ipv6_addr =  new sockaddr_in6;
    this->m_ipv4_addr = (sockaddr_in*)new sockaddr_in6;
    this->m_ipv4_addr->sin_port = htons(p_port);
    ::inet_pton(AF_INET, p_host.c_str(), &(this->m_ipv4_addr->sin_addr));
    this->m_common_addr = (sockaddr *) this->m_ipv4_addr;
    this->m_common_addr_len = sizeof(sockaddr_in);
  }

}


Address::~Address(){
  free(this->m_ipv6_addr);
}

}// namespace quick_pack
