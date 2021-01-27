#include <iostream>
#include <cstring>
#include "port.h"

#define PORT_NUM 2
#define MAX_PORT 65535
#define MIN_PORT 0

/*
 * @brief splits ports range and converts string to num
 * @param String Val containing "port1-port2"
 * @note sets range[0] to low-port and range[1] to high-port
 * @returns "true" if Val is legal port input, else false
 */
bool Port::set_value(String val){


	bool err_flag = true;
	String *split_two_ports;
	size_t size, i;

	val.split("-", &split_two_ports, &size);
	if(size == PORT_NUM){
		for(i=0; i<size; i++){
			range[i] = split_two_ports[i].trim().to_integer();
			if(range[i] > MAX_PORT || range[i] < MIN_PORT){
				err_flag = false;
			}
		}
	}
	if(range[0]>range[1]){
		err_flag = false;
	}
	delete[] split_two_ports;
	return err_flag;
}
/*
 * @brief initializes Port according to pattern.
 * @param String pattern, "dst-port"/"src-port"
 */
Port::Port(String pattern):Field(pattern, PORT){
}

/*
 * @brief determined whether Port given is legal
 * according to info given in set_value
 * @param String Val containing some port number
 * @returns "true" if Val is legal port input, else false
 */
bool Port::match_value(String val) const{
	int port;
	port = val.trim().to_integer();
	if((range[0] <= port) && (range[1] >= port)){
		return true;
	}
	return false;
}
