#include "mbedtls/config.h" // 这个地方是个坑, 一定要include这个文件先

void testRSA() {
    unsigned char input[117] = "helloworld";
    unsigned char output[1024] = { 0 };
    unsigned char outputex[128] = { 0 };
    outputex[117] = 0x0a;

    mbedtls_entropy_context entropy;
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_context ctr;
    mbedtls_ctr_drbg_init(&ctr);
    mbedtls_ctr_drbg_seed(&ctr, mbedtls_entropy_func, &entropy, NULL, 0);

    mbedtls_rsa_context ctx;
    mbedtls_rsa_init(&ctx, MBEDTLS_RSA_PKCS_V21, 0);
    int ret = mbedtls_rsa_gen_key(&ctx, mbedtls_ctr_drbg_random, &ctr, 1024, 65537);
    ret = mbedtls_rsa_public(&ctx, input, output);
    ret = mbedtls_rsa_private(&ctx, mbedtls_ctr_drbg_random, &ctr, output, outputex);

    mbedtls_rsa_free(&ctx);
    mbedtls_ctr_drbg_free(&ctr);
    mbedtls_entropy_free(&entropy);
}