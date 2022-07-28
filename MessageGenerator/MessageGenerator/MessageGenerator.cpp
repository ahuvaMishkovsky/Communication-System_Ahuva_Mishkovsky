using namespace std;
#include <iostream>
#include "MessageGeneratorDev.h"


int main()
{
    char c;

    cout << "Enter any character to start sending data messages\n";
    cin >> c;

    MessageGeneratorDev msg_dev;
  
    cout << "Enter any character to stop sending data messages\n";
    cin >> c;

    cout << "The message generator sent " 
        << msg_dev.Get_msg_counter() 
        << " messages and received " 
        << msg_dev.Get_received_msgs_counter() 
        << " messages, test duration: "
        << msg_dev.Get_msg_counter() 
        <<" seconds"<<endl;
}
