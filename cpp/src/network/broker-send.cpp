#include "network/broker.hpp"


namespace quick_pack {

  //   send
  //
  // - parameter: builder(that was used to build data field), reference to field that was built, field type, destination
  // - do transmission level stuff (like adding seq or encoding)
  // - serialize and finalize builder into binary buffer
  // - send
  // - reset builder and release it
  // - returns sent size or return negative error number
  //     - if return is -1, then it should be sentto() function error, one should check errno
  //     - if return is < -1 then it is other error specific to send()

int32_t Broker::send(
  uint32_t p_from_id, // id of m_internal_address_manager;
  flatbuffers::FlatBufferBuilder* p_builder,
  uint32_t p_dest,
  quick_pack::transmission::AnyMessageTable p_type = quick_pack::transmission::AnyMessageTable_NONE,
  flatbuffers::Offset<void> p_message = 0   // return from Create*() then .Union()
){

  AddressDetail* addrdetail_to = this->m_external_address_detail_manager.m_id_to_addrdetail[p_dest];
// do transmission layer stuff?
  auto fb_packet = quick_pack::transmission::CreatePacket(
    *p_builder,
    p_type,
    p_message,
    ++(addrdetail_to->m_out_seq)
  );
  p_builder->Finish(fb_packet);
  ssize_t ret = ::sendto(
    this->m_internal_socket_detail_manager.m_id_to_sockdetail[p_from_id]->m_socket,
    p_builder->GetBufferPointer(),
    p_builder->GetSize(),
    0, // flags
    addrdetail_to->m_address->m_common_addr,
    addrdetail_to->m_address->m_common_addr_len
  );
  p_builder->Reset();
  // TODO:: release p_builder
  return ret;
}









} // namespace quick_pack
