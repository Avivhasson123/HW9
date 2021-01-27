#include <iostream>
#include <cstring>
#include "string.h"
using namespace std;
//string works perfectly//
#define IP_PARTS 4
#define ERROR -1

/*
 * @brief initializes String
 */
String::String(){

	data = NULL;
	length = 0;

}

/*
 * @brief creates new String from existing one
 * @param reference to String "str"
 */
String::String(const String &str){
	if (str.data == NULL){
		String();
		return;
	}
	length = str.length;
	if(length == 0) { // check if this is necessary
		data = NULL;
	}
	data = new char [str.length+1];
	strcpy(data, str.data);
}

/*
 * @brief creates new String with data copied from string
 * @param pointer to string(char*)
 */
String::String(const char *str){
	if (str == NULL){
		String();
		return;
	}
	length = strlen(str);
	data = new char[length+1];
	strcpy(data, str);
}
/*
 * @brief frees memory
 */
String::~String(){
	if (data != NULL){
		delete[] data;
	}
}

/*
 * @brief overwrites String with information of String rhs
 * @param reference to String "rhs"
 * @returns reference to modified String
 */
String& String::operator=(const String &rhs){
	if(rhs.data == NULL){
		String();
		return *this;
	}
	if (data != NULL){
		delete[] data;
	}
	if(rhs.length != 0) {
		data = new char [rhs.length+1];
		strcpy(data, rhs.data);
	}
	else{
		data = NULL;
	}
	length = rhs.length;
	return *this;
}

/*
 * @brief overwrites String with data copied from string "str"
 * @param pointer to string(char*)
 * @returns reference to modified String
 */
String& String::operator=(const char *str){
	if (str == NULL){
		String();
		return *this;
	}
	if (data != NULL){
		delete[] data;
	}
	length = strlen(str);
	data = new char[length+1];
	strcpy(data, str);

	return *this;
}
/*
 * @brief determined whether two Strings are identical
 * @param reference to String "rhs"
 * @returns "true" if identical (size&data), else "false"
 */
bool String::equals(const String &rhs) const{

	bool flag = false;
	if (length == rhs.length){
		flag = true;
	}
	if ((strcmp(data, rhs.data) == 0) && flag == true){
		return true;
	}else {
		return false;
	}
}
/*
 * @brief determined whether String & string are identical
 * @param reference to string "rhs"(char*)
 * @returns "true" if identical (size&content), else "false"
 */
bool String::equals(const char *rhs) const{
	bool flag = false;
	if (rhs == NULL){
		return false;
	}
	if (length == strlen(rhs)){
		flag = true;
	}
	if ((strcmp(data, rhs) == 0) && flag == true){
		return true;
	} else {
		return false;
	}
}

/*
 * @brief splits String data according to delimiters
 * @param delimiters string, String array, pointer to size
 * @note saves substrings in "output" array
 * @note saves number of substrings in "size"
 */
void String::split(const char *delimiters,
				   String **output,
				   size_t *size) const{

	int sub_string_cnt=0, string_top =0, num_deli =0, sub_string_num = 0;
	char end_of_string = '\0';

	if ((output == NULL || data == NULL) && size!= NULL){
		*size = 0;
		return;
	}
	num_deli = strlen(delimiters);
	char *string_copy = new char[length+1];
	strcpy(string_copy, data);
	string_copy[length] = end_of_string;

	for(unsigned int i=0; i<length; i++){
		for(int j=0; j<num_deli; j++){
			if(string_copy[i] == delimiters[j]){
				sub_string_num++;
			}
		}
	}
	sub_string_num++;

	*output = new String[sub_string_num];
	*size = sub_string_num;

	for(unsigned int i=0; i<length; i++){
		for(int j=0; j<num_deli; j++){
			if(string_copy[i] == delimiters[j]){
				string_copy[i] = end_of_string;
				(*output)[sub_string_cnt] = String(&string_copy[string_top]);
				sub_string_cnt++;
				string_top = i + 1;
			}
		}
	}
	(*output)[sub_string_cnt] = String(&string_copy[string_top]);
	delete[] string_copy;
	return;
}


/*
 * @brief cuts out spaces in start&end of String data
 * @returns modified String
 */
String String::trim() const{

	int start=0, end = length-1, cnt = 0;
	unsigned int i=0, j=0;
	if(data == NULL){
		return String();
	}
	while (data[start] == ' '){
		cnt++;
		start++;
	}
	while (data[end] == ' '){
		cnt++;
		end--;
	}
	int new_size = length-cnt;
	char new_string[new_size+1];

	for (i=0; i<length; i++) {
		if(data[i] != ' '){
			new_string[j] = data[i];
			j++;
		}
	}
	new_string[new_size] = '\0';
	String str(new_string);
	return str;
}
/*
 * @brief convert String to numbers
 * @return the converted number
 */
int String::to_integer() const{

	String *string = NULL;
	size_t substring_num = 0;
	int string_to_int = 0, temp=0;

	split(".", &string, &substring_num);
	if(substring_num == IP_PARTS){
		for(unsigned int i=0; i<substring_num; i++){
			temp = atoi(string[i].trim().data);
			if(temp > 255 || temp < 0) {
				delete[] string;
				return ERROR;
			}

			string_to_int = string_to_int | (temp << (24 - 8*i));

		}
	}
	else {
		string_to_int = atoi(data);
	}
	delete[] string;
	return string_to_int;
}
