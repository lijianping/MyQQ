#include "encrypt.h"
#include "md5.h"
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

static char *hexchar2bin(const std::string &data, int &length);

static std::string qq_md5(const unsigned char *data, int length);

std::string encrypt_passwd(const std::string &password,
	                       const std::string &verify_code,
	                       const std::string &uin)
{
	/* NOTICE: free uin_ptr */
	char *uin_ptr = strdup(uin.c_str());
	char *ptr = uin_ptr;

	/* DEBUG: show uin_ptr */
	printf("uin_ptr before call strtok: %s\n", uin_ptr);
	char *tok = strtok(uin_ptr, "\\x");
	std::vector<std::string> parts;
	while (tok != NULL) {
		parts.push_back(tok);
		tok = strtok(NULL, "\\x");
		printf("uin_ptr after call strtok: %s\n", uin_ptr);
	}

	/* DEBUG: show uin_ptr */
	printf("uin_ptr after call strtok: %s\n", uin_ptr);
	printf("ptr after call strtok: %s\n", ptr);

	std::string uin_str;

	for (std::vector<std::string>::iterator it = parts.begin();
		it != parts.end(); ++it) {
		char ints[3] = {0};
		memset(ints, 0, sizeof(ints));
		memcpy(ints, it->c_str(), 2);

		char *end_ptr;
		long int iv = strtol(ints, &end_ptr, 16);
		if (ints == end_ptr) {
			break;
		} else if (*end_ptr != '\0') {
			break;
		} else {
			uin_str += (unsigned char)iv;
		}
	}

	free(uin_ptr);
	uin_ptr = NULL;

	std::string verify(verify_code);
	std::transform(verify.begin(), 
		           verify.end(),
		           verify.begin(),
		           ::toupper);

	std::string en_password;
	int len1, len2;
	char *temp1 = hexchar2bin(qq_md5((unsigned char *)password.c_str(), password.length()),
		                      len1);

	len2 = len1 + uin_str.size();

	char *temp2 = new char[len2];
	if (!temp2) {
		return "error";
	}

	memcpy(temp2, temp1, len1);
	memcpy(temp2 + len1, uin_str.c_str(), uin_str.size());
	delete [] temp1;
	temp1 = NULL;

	std::string result;
	result = qq_md5((unsigned char *)temp2, len2);
	result += verify;
	result = qq_md5((unsigned char *)result.c_str(), result.length());
	delete [] temp2;
	temp2 = NULL;

	return result;
}	             

static char *hexchar2bin(const std::string &data, int &length)          
{
	char *buf;
	const char *data_str;
	int i, j = 0;

	length = data.size() / 2;

	buf = new char[length];
	if (!buf) {
		return NULL;
	}
	memset(buf, 0, length);

	data_str = data.c_str();

	for (i = 0; i < data.size(); i += 2) {
		char ints[3] = {0};
		memset(ints, 0, sizeof(ints));
		memcpy(ints, data_str + i, 2);

		char *end_ptr;

		long int iv = strtol(ints, &end_ptr, 16);

		if (ints == end_ptr) {
			break;
		} else if (*end_ptr != '\0') {
			break;
		} else {
			buf[j++] = (unsigned char)iv;
		}
	}

	return buf;
}

static std::string qq_md5(const unsigned char *data, int length)
{
	unsigned char p[128] = {0};

	MD5((unsigned char *)data, length, p);

	std::string result(reinterpret_cast<char *>(p));

	std::transform(result.begin(), 
		           result.end(),
		           result.begin(),
		           ::toupper);

	return result;
}