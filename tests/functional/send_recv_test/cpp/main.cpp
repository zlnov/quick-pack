#include "network/broker.hpp"

#include <iostream>
int main(){




  // create a broker

  // create a internal address
  // create an external address_detail_manager/


  quick_pack::Broker broker1;

  quick_pack::Broker broker2;

  auto loco = std::string("127.0.0.1");
  auto port1 = std::string("5555");
  auto port2 = std::string("6666");

  auto from1 = broker1.add_internal_socket(loco , port1, false);
  auto from2 = broker2.add_internal_socket(loco, port2, false);

  auto to1 = broker1.add_external_address(loco, 6666, false);
  // auto to2 = broker2.add_external_address(loco, 5555, false);

  std::cout<<from1<<std::endl;
  std::cout<<from2<<std::endl;
  std::cout<<to1<<std::endl;
  // std::cout<<to2<<std::endl;

  auto builder1 = broker1.get_fb_builder();

  auto tb1 = quick_pack::message::Createexample_message_1(*builder1, 3, 6123);



  broker1.send(1, builder1, 1, quick_pack::transmission::AnyMessageTable_quick_pack_message_example_message_1, tb1.Union());


  const void * message_table;
  void * buff = nullptr;
  uint32_t sender;
  size_t len;
  broker2.recv(1, message_table, sender, buff, len);

  std::cout<<"sender: " << sender << std::endl;
  auto p1 = static_cast<const quick_pack::message::example_message_1 *> (message_table);
  std::cout<<p1->field0()<<std::endl;
  std::cout<<p1->field1()<<std::endl;

  assert (p1->field0() == 3);
  assert (p1->field1() == 6123);









}
