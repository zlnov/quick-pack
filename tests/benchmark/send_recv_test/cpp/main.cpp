#include "network/broker.hpp"

#include <iostream>

//
#include <chrono>
#include <thread>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

uint64_t OP_COUNT = 1000000;


void long_operation1()
{
  quick_pack::Broker broker1;

  quick_pack::Broker broker2;

  auto loco = std::string("127.0.0.1");
  auto port1 = std::string("5555");
  auto port2 = std::string("6666");

  auto from1 = broker1.add_internal_socket(loco , port1, false);
  auto from2 = broker2.add_internal_socket(loco, port2, false);

  auto to1 = broker1.add_external_address(loco, 6666, false);
  // auto to2 = broker2.add_external_address(loco, 5555, false);


  for( int i = 0; i < OP_COUNT; ++i){
    auto builder1 = broker1.get_fb_builder();

    auto tb1 = quick_pack::message::Createexample_message_1(*builder1, 3, 6123);



    broker1.send(1, builder1, 1, quick_pack::transmission::AnyMessageTable_quick_pack_message_example_message_1, tb1.Union());


    const void * message_table;
    void * buff = nullptr;
    uint32_t sender;
    size_t len;
    broker2.recv(1, message_table, sender, buff, len);

    auto p1 = static_cast<const quick_pack::message::example_message_1 *> (message_table);

    assert (p1->field0() == 3);
    assert (p1->field1() == 6123);

  }
}

void test_1(){
  auto t1 = high_resolution_clock::now();
  long_operation1();
  auto t2 = high_resolution_clock::now();

  /* Getting number of milliseconds as an integer. */
  auto ms_int = duration_cast<milliseconds>(t2 - t1);

  /* Getting number of milliseconds as a double. */
  duration<double, std::milli> ms_double = t2 - t1;

  std::cout << ms_int.count() << "ms\n";
  std::cout << ms_double.count() << "ms\n";
}


//
int main(){



  test_1();









}
