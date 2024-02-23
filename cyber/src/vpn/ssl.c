#define _POSIX_C_SOURCE 2
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/opensslv.h>

#define COOKIE_LENGTH (11)
#define MTU (1400)
#define PORT (54345)
#define CERT_PATH "./cert_dir/cert.pem"
#define KEY_PATH "./cert_dir/key.pem"
#define AS_CLIENT YES

static int verify_cert(int ok, X509_STORE_CTX *ctx)
{
    (void)ok;
    (void)ctx;
    return 1;
}
static int generate_cookie(SSL *ssl, unsigned char *cookie, unsigned int *cookie_len)
{
    *cookie_len = COOKIE_LENGTH;
    memcpy(cookie, "TOP_SECRET", *cookie_len);
    (void)ssl;
    return 1;
}
static int verify_cookie(SSL *ssl, unsigned char *cookie, unsigned int cookie_len)
{
    (void)ssl;
    (void)cookie;
    (void)cookie_len;
    return 1;
}

void SSLInit()
{
    SSL_CTX *ctx;
    system("sudo apt-get install libssl-dev");
    SSL_load_error_strings();
    SSL_library_init();

#ifdef AS_CLIENT
    ctx = SSL_CTX_new(DTLSv1_client_method());
#else
    ctx = SSL_CTX_new(DTLSv1_server_method());
#endif
    SSL_CTX_use_certificate_chain_file(ctx, CERT_PATH);
    SSL_CTX_use_PrivateKey_file(ctx, KEY_PATH, SSL_FILETYPE_PEM);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_cert);
    SSL_CTX_set_cookie_generate_cb(ctx, generate_cookie);
    SSL_CTX_set_cookie_verify_cb(ctx, verify_cookie);
}
