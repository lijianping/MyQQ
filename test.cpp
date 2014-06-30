#include <iostream>
#include <cstdio>
#include "encrypt.h"
using namespace std;

/*
 * test.exe 123456 !PVJ \x00\x00\x00\x00\x67\x52\xc6\x1
 * BC6213F5482AB23CD623B9B3003AD355
 */
int main(int argc, char **argv)
{
	if (argc != 4) {
		printf("%s password verify_code uin\n", argv[0]);
		return 1;
	}

	std::string password;
	password = encrypt_passwd(argv[1], argv[2], argv[3]);
	cout <<password <<endl;

	return 0;
}
