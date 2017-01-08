#include <stdint.h>

#include "macros.h"
#include "minunit.h"
#include "buffer.h"
#include "byte-array.h"

MU_TEST(test_size_of_buffer_type) {
  mu_check(size_of_buffer_type(INT) == sizeof(int32_t));
  mu_check(size_of_buffer_type(INT8) == sizeof(int8_t));
  mu_check(size_of_buffer_type(INT16) == sizeof(int16_t));
  mu_check(size_of_buffer_type(INT32) == sizeof(int32_t));
  mu_check(size_of_buffer_type(UINT) == sizeof(uint32_t));
  mu_check(size_of_buffer_type(UINT8) == sizeof(uint8_t));
  mu_check(size_of_buffer_type(UINT16) == sizeof(uint16_t));
  mu_check(size_of_buffer_type(UINT32) == sizeof(uint32_t));
}

MU_TEST(test_new_buffer){
  buffer_t *buf = new_buffer(4, UINT8);
  mu_check(buf->size == (sizeof(uint8_t) * 4));
  mu_check(buf->length == 4);
  mu_check(buf->type == UINT8);

  uint8_t *data = (uint8_t *) buf->data;
  for(int i=0; i<buf->length;i++){
    mu_check(data[i] == 0);
  }
}

MU_TEST(test_byte_array){
  byte_array_t *bAR = new_byte_array(10);
  mu_check(bAR->length == 10);
  mu_check(bAR->buffer->length == 10);

  int i;
  uint8_t num;
  // check that data is initalized to 0
  for(i=0; i<bAR->length; i++){
    num = apply(bAR, read_uint8, i);
    mu_check(num == 0);
  }

  // testing write_uint8 with valid offset
  int check = apply(bAR, write_uint8, 2, 1);
  mu_check(check == 0);
  num = apply(bAR, read_uint8, 1);
  mu_check(num = 2);

  // testing write_uint8 with invalid offset
  check = apply(bAR, write_uint8, 2, 100);
  mu_check(check == -1);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_size_of_buffer_type);
  MU_RUN_TEST(test_new_buffer);
  MU_RUN_TEST(test_byte_array);
}

int main(int argc, char *argv[]) {
  GC_INIT();
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}