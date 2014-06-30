#ifndef MD5_HEADER
#define MD5_HEADER

/*
 * @brief This struct represents a MD5-hash context.
 */
typedef struct {
	///<< state (ABCD)
	unsigned int state[4];

	///<< number of bits, modulo 2^64 (lsb first)
	unsigned int count[2];

	///<< input buffer
	unsigned char buffer[64];
} MD5_CTX;

/*
 * @brief Initialization begins an operation,
 *        writing a new context.
 * @param context The MD5_CTX context to initialize.
 **/
void MD5Init(MD5_CTX *context);

/*
 * @brief Block update operation. Continues an md5 message-digest
 *        operation, processing another message block, and updating
 *        the context.
 * @param context The MD5_CTX context to update.
 * @param input The data to write into the context.
 * @param input_len The length of the input data.
 **/
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int input_len);

/*
 * @brief Finalization ends the md5 message-digest operation,
 *        writing the message digest and zeroizing the context.
 * @param context The context to finalize.
 * @param digest This is an OUT parameter which contains the
 *        created hash after the method returns.
 **/
void MD5Final(MD5_CTX *context, unsigned char digest[16]);

int MD5(unsigned char *input, unsigned int input_len, unsigned char *digest);

#endif