#include <iostream>
#include <cstring>
#include "port.h"
#include "field.h"
#include "ip.h"
using namespace std;

#define ARR_SIZE 2

/*
 * @brief initializes Field
 * @param String containing pattern, field type(IP/PORT)
 */
Field::Field(String pattern, field_type type){
	this->type = type;
	this->pattern = pattern;
}

/*
 * @brief initializes Field
 * @param String containing pattern
 */
Field::Field(String pattern){
	this->pattern = pattern;
	type = GENERIC;
}

/*
 * @brief returns Field type
 */
field_type Field::get_type() const{
	return (this->type);
}

/*
 * @brief according to type, picks the right value set
 * @param String Val(either port range/ip+mask)
 * @returns true if legal input
 */
bool Field::set_value(String val){
	if(type == PORT){
		if(((Port*)this)->set_value(val) == true){
			return true;
		}
	}
	if(type == IP){
		if(((Ip*)this)->set_value(val) == true){
			return true;
		}
	}
	return false;
}

/*
 * @brief according to type, checks whether Val fits rules
 * of type (defined in set_value)
 * @param String Val(certain port/ip address)
 * @returns true if Val passed match_value of type
 */
bool Field::match_value(String val) const {
	if(type == PORT){
		if(((Port*)this)->match_value(val) == true){
			return true;
		}
	}
	if(type == IP){
		if(((Ip*)this)->match_value(val) == true){
			return true;
		}
	}
	return false;
}
/*
 * @brief destructs Field
 */
Field::~Field() {
}

/*
 * @brief splits packet to sub-rules and splits each of them
 * to name&value. checks if name&value follow restrictions
 * @param String packet ("rules")
 * @returns True if packet matches Field restrictions
 */
bool Field::match(String packet){

	bool flag = false;
	String *sub_packets = NULL;
	String *split_name_num = NULL;
	size_t num_sub_packets = 0, name_num_size = 0;
	packet.split(",", &sub_packets, &num_sub_packets);
	if(num_sub_packets == 0){
		return false;
	}
	for(unsigned int i=0; i<num_sub_packets; i++){
		sub_packets[i].split("=", &split_name_num, &name_num_size);
		if(name_num_size == 0){
			continue;
		}
		if(name_num_size == ARR_SIZE){
			if(pattern.trim().equals(split_name_num[0].trim()) == true){
				flag = match_value(split_name_num[1].trim());
			}
		}
		if(split_name_num != NULL){
			delete[] split_name_num;
		}
	}

	if(sub_packets != NULL){
		delete[] sub_packets;
	}
	return flag;
}




