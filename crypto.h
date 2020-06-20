#ifndef EXTCLIB_CRYPTO_H_
#define EXTCLIB_CRYPTO_H_

#include <stdint.h>

#include "context.h"

// extern int8_t genkeys_crypto(size_t size, Context ctx);
// extern int8_t rsa_crypto(option_t option, Context ctx);

extern int8_t aes_crypto(option_t option, Context ctx);
extern int8_t rand_crypto(Context ctx);

extern void sha256_crypto(Context ctx);
extern void hmac256_crypto(Context ctx);

#endif /* EXTCLIB_CRYPTO_H_ */
