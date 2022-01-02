#include "network/broker.hpp"
namespace quick_pack {

// recv
//
// - create a large buffer
// - call recvfrom()
// - resize the buffer with realloc (test to see if this is expensive)
// - fb::VerifyPacket() to check validity (check if expensive, if yes, see if we can avoid)
// - fb::GetPacket() into pointers
// - load or new address_detail
// - do transmission level things ( like check seq )
// - update address table
// - return: Message-table-pointer, sender id, pointer-filled-with-buffer(to be freed)



/*
    return value:
    -1 recvfrom() error
    -2 VerifyPacketBuffer failed
    -3 m_temp_sock_storage holds unknown ss_family
*/

int32_t Broker::recv(
  uint32_t p_dest_id,
  const void*& pr_message_fb_table_class,
  uint32_t & pr_sender,
  void* pr_binary_buffer,
  size_t & pr_buffer_len
)
{
  // create a large buffer if one isn't supplied
  if(pr_binary_buffer == nullptr){
    pr_binary_buffer = malloc(this->kBufferCreateSize);
    pr_buffer_len = this->kBufferCreateSize;
  }

  // call recvfrom()
  socklen_t addrlen = this->kSockAddrStorageSize;
  ssize_t ret = ::recvfrom(
    this->m_internal_socket_detail_manager.m_id_to_sockdetail[p_dest_id]->m_socket, // recving socket
    pr_binary_buffer,
    pr_buffer_len,
    0, // flags
    (sockaddr *)this->m_tmp_sockaddr_in6,
    &addrlen
  );

  if (ret < 0){
    return ret;
  }

  // resize the buffer with realloc (TODO: test to see if this is expensive)
  void * newbuff = realloc(pr_binary_buffer, ret);
  if (newbuff != nullptr){ // TODO what do we do if ret is 0? realloc will return NULL
    pr_binary_buffer = newbuff;
  }

  // - fb::VerifyPacket() to check validity (check if expensive, if yes, see if we can avoid)
  flatbuffers::Verifier vf((const uint8_t*)pr_binary_buffer, ret);
  if (!transmission::VerifyPacketBuffer(vf)){
    return -2; // or other return code
  }

  // - fb::GetPacket() into pointers
  auto fb_packet_obj = transmission::GetPacket(pr_binary_buffer);

  // - load or new address_detail
  AddressDetail* sender_detail = this->load_existing_or_create_new_addrdetail();
  pr_sender = sender_detail->m_id;

  // - do transmission level things ( like check seq )
  if (fb_packet_obj->seq() != ++(sender_detail->m_in_seq)){
    // if seq is not matching...?
  }

  // update m_last_recv
  sender_detail->update_last_recv();

  // - return: Message-table-pointer, sender id, pointer-filled-with-buffer(to be freed)
  pr_message_fb_table_class  = fb_packet_obj->data();

  return ret;
}





} // namespace quick_pack
