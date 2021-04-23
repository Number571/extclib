#ifndef EXTCLIB_CRYPTO_H_
#define EXTCLIB_CRYPTO_H_

#define CRYPTO_MODE_ENCRYPT  1
#define CRYPTO_MODE_DECRYPT -1

/*
@todo
-rand [xtea-ofb]
-hash [xtea-mdc2]
*/

extern int crypto_entropy(unsigned char *output, int size);

extern void crypto_srand(const unsigned char *key, int ksize);
extern void crypto_rand(unsigned char *output, int size);

extern unsigned long long crypto_xtea(
	int mode, 
	unsigned long long data, 
	const unsigned long key[4]
);

extern int crypto_hex(
	int mode,
	unsigned char *output,
	const unsigned char *input,
	int size
);

#endif /* EXTCLIB_CRYPTO_H_ */
