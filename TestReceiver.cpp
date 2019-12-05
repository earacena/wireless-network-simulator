#include "Receiver.h"

int main() {
  Receiver receiver;
  
  receiver.read_data_from_GUI("test-file-receiver.txt");
  receiver.parse_data();

  return 0;
}
