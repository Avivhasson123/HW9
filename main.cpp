#include <iostream>
#include <cstring>
#include "port.h"
#include "ip.h"
using namespace std;

extern void parse_input(Field&);
extern int check_args(int, char**);

/*
 * @brief split sub-rule name&value parts
 * match name to type, create value set according to
 * value, parse input.
 * @param argv- some rule
 */
int main(int argc, char **argv){
	String *match;
	size_t length =0;
	String rule(argv[1]);
	rule.split("=", &match, &length);
	String s1=String("dst-port");
	String s2=String("src-port");
	String s3=String("dst-ip");
	String s4=String("src-ip");
	if(check_args(argc, argv) == 0){
		return 1;
	}

	if(match[0].trim().equals(s1) ||
	   match[0].trim().equals(s2)){
		Port match_port(match[0].trim());
		match_port.set_value(match[1].trim());
		parse_input(match_port);
	}

	if(match[0].trim().equals(s3) ||
	   match[0].trim().equals(s4)){
		Ip match_ip(match[0].trim());
		match_ip.set_value(match[1].trim());
		parse_input(match_ip);
	}
	delete[] match;
}



