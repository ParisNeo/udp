# udp
Simple Linux C udp library to help using udp communication on Linux platforms in a very simple way.

# Build
To build and install the library on your system, just use:
```console
foo@bar:~$ make clean;make; sudo make install
```
You can skip the make install part and copy the .a output file as well as the header file to your project to link it statically with your code
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
init_udp_cfg_list(&udp_configurations);
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

# Useful links
Check out my uart library built in the same spirit as this library.





