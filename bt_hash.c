/*
@header
    The bt_hash class allows to hash blobs.
*/

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "bt_hash.h"

//  Structure of our class


//  --------------------------------------------------------------------------
//  Constructor
//  Create new SHA object

bt_hash_t *
bt_hash_new (void)
{
    bt_hash_t *self = (bt_hash_t *) malloc (sizeof (bt_hash_t));
    SHA1_Init (&self->context);
    return self;
}

//  --------------------------------------------------------------------------
//  Destroy a SHA object

void
bt_hash_destroy (bt_hash_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        bt_hash_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Add buffer into SHA calculation

void
bt_hash_update (bt_hash_t *self, byte *buffer, size_t length)
{
    //  Buffer has to be on 64-bit boundary
    /*assert (((long) buffer & 7L) == 0);*/
    SHA1_Update (&self->context, buffer, length);
}


//  --------------------------------------------------------------------------
//  Return final SHA hash data

byte *
bt_hash_data (bt_hash_t *self)
{
    if (!self->final) {
        SHA1_Final (self->hash, &self->context);
        self->final = true;
    }
    return self->hash;
}


//  --------------------------------------------------------------------------
//  Return final SHA hash size

size_t
bt_hash_size (bt_hash_t *self)
{
    return SHA_DIGEST_LENGTH;
}


//  --------------------------------------------------------------------------
//  Self test of this class

int
bt_hash_test (bool verbose)
{
    printf (" * bt_hash: ");

    //  @selftest
    byte *buffer = malloc (1024);
    memset (buffer, 0xAA, 1024);

    bt_hash_t *hash = bt_hash_new ();
    bt_hash_update (hash, buffer, 1024);
    byte *data = bt_hash_data (hash);
    size_t size = bt_hash_size (hash);
    assert (data [0] == 0xDE);
    assert (data [1] == 0xB2);
    assert (data [2] == 0x38);
    assert (data [3] == 0x07);
    bt_hash_destroy (&hash);
    free (buffer);
    //  @end

    printf ("OK\n");
    return 0;
}
