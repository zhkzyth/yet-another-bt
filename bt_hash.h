#ifndef __BT_HASH_H_INCLUDED__
#define __BT_HASH_H_INCLUDED__

#include <stdbool.h>

#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/sha.h>
#endif

typedef unsigned char byte;

//common header vars for project
typedef struct _bt_hash_t {
    SHA_CTX context;
    byte hash [SHA_DIGEST_LENGTH];
    bool final;
} bt_hash_t;

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create new HASH object
bt_hash_t *
    bt_hash_new (void);

//  Destroy a HASH object
void
    bt_hash_destroy (bt_hash_t **self_p);

//  Add buffer into HASH calculation
void
    bt_hash_update (bt_hash_t *self, byte *buffer, size_t length);
    
//  Return final HASH hash data
byte *
    bt_hash_data (bt_hash_t *self);

//  Return final HASH hash size
size_t
    bt_hash_size (bt_hash_t *self);

//  Self test of this class
int
    bt_hash_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
