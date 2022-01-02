#ifndef QUICK_PACK_UINT128_HPP
#define QUICK_PACK_UINT128_HPP
#include <functional>

typedef unsigned __int128 uint128_t;

namespace std {


// template<>
// struct hash<uint128_t> {
//   const uint128_t kMod = (uint128_t)0xFFFFFFFFFFFFFFFF + 14;
//   size_t operator()(uint128_t var) const {
//     return var % kMod;
//   }
// };
//
//
// template <>
// struct hash<::sockaddr_in> {
// 		size_t operator()(::sockaddr_in a) const {
// 				return a.sin_port ^ a.sin_addr.s_addr;
// 		}
// };

} // namespace std

}
#endif
