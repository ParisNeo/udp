/**
 * \file        udp.h
 * \brief       A c library to manage udp 
 * \author      Saifeddine ALOUI
 * \version     0.1
 * \date        12 juin 2022
 * 
 *	Provides helper tools to build audp connection .
 *
 */
#ifndef __UDP__
#define __UDP__
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

// Defines -----------------------------------------------
#define UDP_MAXADDR_SIZE 		16
#define UDP_MAXPORT_SIZE 		8

// Maximum number of UDP connections
#define UDP_MAX_CFG			2

// Default UDP configuration
#define DEFAULT_UDP_ADDRESS	"172.0.0.1"
#define DEFAULT_UDP_PORT	9601
// Structs -----------------------------------------------

typedef struct{
	int     			port;
	char    			str_address[UDP_MAXADDR_SIZE];
	struct  sockaddr_in sockaddr;
	int					fd;
} udp_cfg;


typedef struct{
	int     	nb_cfg;
	udp_cfg    	udp[UDP_MAX_CFG];
} udp_cfg_list;

typedef struct{
	int		  			received_len;
	struct  sockaddr_in sender_address;
	socklen_t 			socket_len;
}udp_receive_infos;

// Prototypes --------------------------------------------
/**
 * \fn void init_udp_cfg(udp_cfg * udp)
 * \brief Initializes the udp_cfg structure
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
void init_udp_cfg(udp_cfg * udp);

/**
 * \fn void init_udp_cfg_list(udp_cfg_list * udp_list)
 * \brief Initializes the udp_cfg_list structure with default values
 *
 * \param udp_list      The struct containing the udp list configuration
 * 
 * \return true if succeeded.
 */
void init_udp_cfg_list(udp_cfg_list * udp_list);

/**
 * \fn configure_udp_out(udp_cfg * udp)
 * \brief Configures udp connection to send data to the socket
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
bool configure_udp_out(udp_cfg * udp);

/**
 * \fn configure_udp_in(udp_cfg * udp)
 * \brief Configures udp connection to receive data from the socket
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
bool configure_udp_in(udp_cfg * udp);

/**
 * \fn int send(udp_cfg *udp_out_configuration, void *data)
 * \brief Sends data to the output udp port
 *
 * \param udp_out_configuration      The struct containing the udp configuration
 * \param data      The data to be sent
 * \param data_len      The length of the data to be sent
 * 
 * \return the number of sent bytes.
 */
int udp_send(udp_cfg *udp_out_configuration, void *data, int data_len);

/**
 * \fn int udp_receive(udp_cfg *udp_out_configuration, void *data, int data_len)
 * \brief Receives data from udp port until data_len bytes received or timeout
 * UDP packets have a fixed size. So you need to provide a buffer at least as big as the sent data or else you may loose all the data
 *
 * \param udp_in_configuration  The struct containing the udp configuration
 * \param data                  The data buffer to be filled
 * \param data_len              The maximum length of the data to be received
 * 
 * \return a structure containing the size of the received data as well as the sender address and its size.
 */
udp_receive_infos udp_receive(udp_cfg *udp_in_configuration, void *data, int data_len);

#endif