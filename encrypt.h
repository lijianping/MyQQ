#ifndef ENCRYPT_HEADER
#define ENCRYPT_HEADER

#include <string>

std::string encrypt_passwd(const std::string &password,
	                       const std::string &verify_code,
	                       const std::string &uin);

#endif