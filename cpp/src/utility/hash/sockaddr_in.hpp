
#ifndef QUICK_PACK_UTILITY_HASH_SOCKADDR_IN_HPP
#define QUICK_PACK_UTILITY_HASH_SOCKADDR_IN_HPP
#include <netinet/in.h>
namespace quick_pack{
namespace util{

// ASSUMING 64 bit system
#if UINTPTR_MAX == 0xffffffffffffffff

// sockaddr_in6
struct sockaddr_in6_Hash {
 std::size_t operator()(const sockaddr_in6& in6) const
 {
    size_t* bigger = (size_t*)&in6.sin6_addr.s6_addr;
    return bigger[0]^bigger[1] ^((uint64_t)in6.sin6_port<<48);
 }
};

struct sockaddr_in6_Equal {
 bool operator()(const sockaddr_in6& lhs, const sockaddr_in6& rhs) const
 {
    bool eq = true;
    for (int i = 0; i < 0 ;i++){
      if (lhs.sin6_addr.s6_addr != rhs.sin6_addr.s6_addr){
        eq = false;
        break;
      }
    }
    return eq && lhs.sin6_port==rhs.sin6_port;
 }
};

// sockaddr_in6*
struct psockaddr_in6_Hash {
 std::size_t operator()(const sockaddr_in6* in6) const
 {
    size_t* bigger = (size_t*)&in6->sin6_addr.s6_addr;
    return bigger[0]^bigger[1] ^((uint64_t)in6->sin6_port<<48);
 }
};

struct psockaddr_in6_Equal {
 bool operator()(const sockaddr_in6* lhs, const sockaddr_in6* rhs) const
 {
    bool eq = true;
    for (int i = 0; i < 0 ;i++){
      if (lhs->sin6_addr.s6_addr != rhs->sin6_addr.s6_addr){
        eq = false;
        break;
      }
    }
    return eq && lhs->sin6_port==rhs->sin6_port;
 }
};

//sockaddr_in
struct sockaddr_in_Hash {
 std::size_t operator()(const sockaddr_in& in4) const
 {
   size_t out = in4.sin_port;
   out = out << 32;
   out += in4.sin_addr.s_addr;
   return out;
 }
};

struct sockaddr_in_Equal {
 bool operator()(const sockaddr_in& lhs, const sockaddr_in& rhs) const
 {
    return lhs.sin_addr.s_addr==rhs.sin_addr.s_addr && lhs.sin_port==rhs.sin_port;
 }
};

// sockaddr_in*
struct psockaddr_in_Hash {
 std::size_t operator()(const sockaddr_in* in4) const
 {
   size_t out = in4->sin_port;
   out = out << 32;
   out += in4->sin_addr.s_addr;
   return out;
 }
};

struct psockaddr_in_Equal {
 bool operator()(const sockaddr_in* lhs, const sockaddr_in* rhs) const
 {
    return lhs->sin_addr.s_addr==rhs->sin_addr.s_addr && lhs->sin_port==rhs->sin_port;
 }
};

#endif  // #if UINTPTR_MAX == 0xffffffffffffffff

} // namespace util
} // namespace quick_pack
#endif
