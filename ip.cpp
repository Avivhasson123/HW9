#include <iostream>
#include <cstring>
#include "ip.h"
using namespace std;

#define BITS 32
/*
 * @brief initializes IP according to pattern.
 * @param String pattern, "dst-ip"/"src-ip"
 */
Ip::Ip(String pattern):Field(pattern, IP){
}
/*
 * @brief splits Ip to address&mask and converts strings to num
 * @param String Val containing "ip-address/mask"
 * @note sets lowest, highest legal ips according to mask
 * @returns "true" if Val is legal ip input, else false
 */
bool Ip::set_value(String val){

	bool err_flag = true;
	String *split_ip;
	size_t size, i;
	int ip[MASK_SEGMENT] = {0};
	int bits_ignored;
	unsigned int bit_calc;

	val.split("/", &split_ip, &size);
	if(size != MASK_SEGMENT){
		err_flag = false;
	}
	for(i=0; i<MASK_SEGMENT; i++){
		ip[i] = split_ip[i].trim().to_integer();
	}
	bits_ignored = BITS - ip[1];
	if(bits_ignored >= 0 && bits_ignored < BITS){
		bit_calc = ~(((unsigned int)1 << bits_ignored) -1);
	} else if (bits_ignored == BITS){
		bit_calc = 0xFFFFFFFF;
		low = ~bit_calc;
		high = bit_calc;
		delete[] split_ip;
		return err_flag;
	} else {
		err_flag = false;
	}
	low = ip[0] & bit_calc;
	high = ip[0] | ~bit_calc;
	delete[] split_ip;
	return err_flag;
}

/*
 * @brief determined whether Ip given is legal
 * according to info given in set_value
 * @param String Val containing some ip address
 * @returns "true" if Val is legal ip input, else false
 */
bool Ip::match_value(String val) const{
	unsigned int ip;
	ip = (unsigned int)val.trim().to_integer();
	if((low <= ip) && (high >= ip)){
		return true;
	}
	return false;
}
