/**
 * \file        udp.c
 * \brief       A c library to manage udp 
 * \author      Saifeddine ALOUI
 * \version     0.1
 * \date        12 juin 2022
 * 
 *	Provides helper tools to build udp connection .
 *
 */
#include <udp.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * \fn void init_udp_cfg(udp_cfg * udp)
 * \brief Initializes the udp_cfg structure
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
void init_udp_cfg(udp_cfg * udp)
{
    strcpy(udp->str_address, DEFAULT_UDP_ADDRESS);
    udp->port=DEFAULT_UDP_PORT;
}

/**
 * \fn void init_udp_cfg_list(udp_cfg_list * udp_list)
 * \brief Initializes the udp_cfg_list structure with default values
 *
 * \param udp_list      The struct containing the udp list configuration
 * 
 * \return true if succeeded.
 */
void init_udp_cfg_list(udp_cfg_list * udp_list)
{
    udp_list->nb_cfg = 0;
    for(int i=0;i<UDP_MAX_CFG;i++)
    {
        init_udp_cfg(&udp_list->udp[i]);
    }
}


/**
 * \fn configure_udp_out(udp_cfg * udp)
 * \brief Configures udp connection to send data to the socket
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
bool configure_udp_out(udp_cfg * udp)
{        
    
    // Creating socket file descriptor 
    if ( (udp->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        return false;
    } 
        
    memset(&udp->sockaddr, 0, sizeof(udp->sockaddr)); 

    // Filling server information 
    udp->sockaddr.sin_family = AF_INET; 
    udp->sockaddr.sin_port = htons(udp->port); 
    udp->sockaddr.sin_addr.s_addr = inet_addr(udp->str_address);     
    
    return true;
}


/**
 * \fn configure_udp_in(udp_cfg * udp)
 * \brief Configures udp connection to receive data from the socket
 *
 * \param udp      The struct containing the udp configuration
 * 
 * \return true if succeeded.
 */
bool configure_udp_in(udp_cfg * udp)
{
    // Creating socket file descriptor 
    if ( (udp->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        return false;
    } 
        
    memset(&udp->sockaddr, 0, sizeof(udp->sockaddr)); 

    // Filling server information 
    udp->sockaddr.sin_family = AF_INET; 
    udp->sockaddr.sin_port = htons(udp->port); 
    udp->sockaddr.sin_addr.s_addr = inet_addr(udp->str_address);     

    // bind server address to socket descriptor
    bind(udp->fd, (struct sockaddr*)&udp->sockaddr, sizeof(udp->sockaddr));
    
    return true;
}


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
int udp_send(udp_cfg *udp_out_configuration, void *data, int data_len)
{
    int num_udp_sent_bytes = sendto(udp_out_configuration->fd, (const char *)data, data_len,  MSG_CONFIRM, (const struct sockaddr *) &udp_out_configuration->sockaddr, sizeof(udp_out_configuration->sockaddr));
}


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
udp_receive_infos udp_receive(udp_cfg *udp_in_configuration, void *data, int data_len)
{
    udp_receive_infos infos;
    infos.received_len = (int)recvfrom(
                            udp_in_configuration->fd, 
                            (void *)data, 
                            data_len,  
                            MSG_WAITALL,  
                            (struct sockaddr *) &infos.sender_address, 
                            &infos.socket_len
                            );
    return infos;
}