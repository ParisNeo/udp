# udp
Simple Linux C udp library to help using udp communication on Linux platforms in a very simple way.
![logo](logo.png)

udp is a very simple connectionless transportation protocol. Basically, one process opens a port ans listens, and the other one sends data to that port. We don't have acknowledgement mechanism, so you send and don't know if the receiver received what we've sent. But it is a very lightweight and fast communication protocol suited for realtime data transfer and inter processes communication.
# Build
To build and install the library on your system, just use:
```console
foo@bar:~$ make clean;make; sudo make install
```
You can skip the make install part and copy the .a output file as well as the header file to your project to link it statically with your code.
# Usage
Once the library is installed on your system or after adding the header file and the .a file to your project, you can use it like this.

First import the header files
```c
#include<udp.h>
```
if you are using c++, make sure you add extern "C" protection
```c
#ifdef __cplusplus
extern "C"
{
#endif
    // udp library
    #include <udp.h>
#ifdef __cplusplus
}
#endif
```
Now you need to declare your uart configuration object:
```c
// UART configuration
udp_cfg_list udp_configurations;
```

In your main, initialize the uart configuration with whatever you need. First call the init_uart_cfg_list function to initialize the structure with default values 

```c
// Initialize every thing to default
init_udp_cfg(&udp_configuration);
```
Now you can setup custom port number and address.

```c
// Set port and baudrate
udp_configuration.port = 9600;
strcpy(udp_configuration.str_address, "192.168.1.1");
```
You can use any char* instead of the "192.168.1.1" or put any other address or port.


We are quite there. Now we configure the udp port. There are two functions. One to create a udp port that sends data (the port and adress are those of the destination), or a udp port that accepts data (the port and adress are those of the current process).

Here we assume you created and setup udp_in_configuration as mentioned above.
```c
    // Connecting UART 
    printf("Configuring udp %s:%d ...", udp_in_configuration.str_address, udp_in_configuration.port);
    if(configure_udp_in(&udp_in_configuration))
    {
        printf("OK\n"); //Success
    }
    else
    {
        printf("NOK\n");  // Failure
        exit(1);
    }
```
To build a udp out connection use:
```c
    // Connecting UART 
    printf("Configuring udp %s:%d ...", udp_out_configuration.str_address, udp_out_configuration.port);
    if(configure_udp_out(&udp_out_configuration))
    {
        printf("OK\n"); //Success
    }
    else
    {
        printf("NOK\n");  // Failure
        exit(1);
    }
```

Now you can talk to your device.

To read and write you need to declare input and output buffers:
```c
    char read_buf [256];
    char write_buf [256];
```
And now you can read into the input buffer
```c
    udp_receive(&udp_in_configuration, (void *)read_buf, 256);
```
here 256 is the size of the buffer, MSG_WAITALL to force waiting the entire message. len is the length of the 

To send data to your device you can use:
```c
    udp_send(&udp_out_configuration, (void *)write_buf, 256);
```
here len is the length of the data to send. If write_buf contains caracters, you may use strlen(write_buf) instead.

# Complete example
Let's write a sender receiver application.

Here is a listener
```c
#include<stdio.h>
#include<udp.h>

udp_cfg udp_in_configuration;
char read_buf[256];

int main(int argc, char ** argv)
{
    // Initialize every thing to default
    init_udp_cfg(&udp_in_configuration);    
    // Set port and baudrate
    udp_in_configuration.port = 9600;
    strcpy(udp_in_configuration.str_address, "192.168.1.1");
    // Configure as sender
    if(configure_udp_in(&udp_in_configuration))
    {
        printf("OK\n"); //Success
    }
    else
    {
        printf("NOK\n");  // Failure
        exit(1);
    }
    // Now we are ready to listen
    udp_receive(&udp_in_configuration, (void *)read_buf, 256);
    // That's it!
    printf("Received : %s", read_buf)
}
```


Here is a sender
```c
#include<stdio.h>
#include<udp.h>

udp_cfg udp_out_configuration;
char write_buf[256];

int main(int argc, char ** argv)
{
    // Initialize every thing to default
    init_udp_cfg(&udp_out_configuration);    
    // Set port and baudrate
    udp_out_configuration.port = 9600;
    strcpy(udp_out_configuration.str_address, "192.168.1.1");
    // Configure as sender
    if(configure_udp_out(&udp_out_configuration))
    {
        printf("OK\n"); //Success
    }
    else
    {
        printf("NOK\n");  // Failure
        exit(1);
    }
    // Now we are ready to send
    strcpy(write_buf, "Hello world");
    udp_send(&udp_out_configuration, (void *)write_buf, 256);
    // That's it!
}
```
# Information
This is one of multiple libraries I have developed to simplify some tasks we do with C on linux. The objective is for it to be open source, eazy to use and compatible with both c and cpp. The build system is make and is compatible with gcc building system. It is very eazy to use this with cmake or other build systems. All these libraries have been tested on raspberry pi with raspbian. They help starting a new application that requires configuration, communication with arduino tools and spreading information between multiple services on the raspberry pi.

The licence is MIT, so you can use this code in your projects without worrying about licence contamination that could happen when using GPL licences. So you still can use it for free in commercial applications.

Tests and bugfixes are welcome. Just clone it, repare it and send a pull request. I want to keep this code as clean and simple as possible so please avoid feature creaping.

# Useful links
Check out my [cfg library](https://github.com/ParisNeo/cfg) built in the same spirit as this library.
Check out my [uart library](https://github.com/ParisNeo/uart) built in the same spirit as this library.





