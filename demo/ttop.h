#include "mbedtls/config.h" // 这个地方是个坑, 一定要include这个文件先

unsigned int gettotp(__time64_t t64) {
    unsigned char output[64] = { 0 };
    char key[] = "3132333435363738393031323334353637383930";
    char tmp[32] = { 0 };
    sprintf(tmp, "%lld", t64);

    mbedtls_hmac_drbg_context hmacCtx;
    mbedtls_hmac_drbg_init(&hmacCtx);
    mbedtls_hmac_drbg_seed_buf(&hmacCtx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA1), key, strlen(key));
    mbedtls_hmac_drbg_random_with_add(&hmacCtx, &output[0], 64, (unsigned char*)tmp, strlen(tmp));
    mbedtls_hmac_drbg_free(&hmacCtx);

    int offset = output[31] & 0xf;
    int binary = ((output[offset] & 0x7f) << 24) |
        ((output[offset + 1] & 0xff) << 16) |
        ((output[offset + 2] & 0xff) << 8) |
        (output[offset + 3] & 0xff);

    int otp = binary % 1000000;
    return otp;
}
