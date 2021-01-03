/*
http_reqs.h - A minimal implementation for HTTP requests.
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>

#define REC_BUFSIZE 0x1000
#define MSG_BUFSIZE 0x1000

static void fail_check(int test, const char *format, ...)
{
	if (test) {
		va_list args;
		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
		// exit ok
		exit(EXIT_FAILURE);
	}
}

static char* http_get(const char *host, const char *page) {
	static char msg[MSG_BUFSIZE];
	const char *format = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: http_reqs.c\r\n\r\n";
	int status;

	status = snprintf(msg, MSG_BUFSIZE, format, page, host);
	fail_check(status == -1 || !msg || status >= MSG_BUFSIZE, "snprintf failed.\n");
	
	return msg;
}

static void make_request(int sd, char *req_type, const char *host, const char *page){
	int status;
	char *msg;
	
	if (strcmp(req_type, "GET") == 0) {
		msg = http_get(host, page);
	}
	
	status = send(sd, msg, strlen(msg), 0);
	fail_check(status == -1, "send failed: %s\n", strerror(errno));
	
	while (1) {
		int bytes;
		char buf[REC_BUFSIZE+10];
		bytes = recv(sd, buf, REC_BUFSIZE, 0);
		if (bytes == 0) {
			break;
		}
		fail_check(bytes == -1, "%s\n", strerror(errno));
		buf[bytes] = '\0';
		/* Print to stdout. */
		printf("%s", buf);
		printf("\n");
	}
}

int make_connection(char *req_type, const char *host, const char *page) {
	struct addrinfo hints, *res, *res_init;
	int error;
	int status;
	int sd;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	error = getaddrinfo(host, "http", &hints, &res_init);
	fail_check(error, gai_strerror(error));
	sd = -1;
	
	for (res = res_init; res; res = res->ai_next) {
		sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		fail_check(sd < 0, "socket: %s\n", strerror(errno));
		
		status = connect(sd, res->ai_addr, res->ai_addrlen);
		if (status < 0) {
			close(sd);
			fail_check(status < 0, "connect: %s\n", strerror(errno));
		}
		break;
	}
	if (sd != -1) {
		make_request(sd, req_type, host, page);
	}
	freeaddrinfo(res_init);
	return 0;
}

int main() {
	const char *host = "api.crossref.org";
	const char *page = "works/doi:10.1098/rsif.2011.0403/transform/application/x-bibtex";
	char *req_type = "GET";
	int status;
	status = make_connection(req_type, host, page);
	return status;
}

/*
http://api.crossref.org/works/${1}/transform/application/x-bibtex
*/

/*
// first connect to the remote as usual, but use the port 443 instead of 80

// initialize OpenSSL - do this once and stash ssl_ctx in a global var
SSL_load_error_strings ();
SSL_library_init ();
SSL_CTX *ssl_ctx = SSL_CTX_new (SSLv23_client_method ());

// create an SSL connection and attach it to the socket
SSL *conn = SSL_new(ssl_ctx);
SSL_set_fd(conn, sock);

// perform the SSL/TLS handshake with the server - when on the
// server side, this would use SSL_accept()
int err = SSL_connect(conn);
if (err != 1)
   abort(); // handle error

// now proceed with HTTP traffic, using SSL_read instead of recv() and
// SSL_write instead of send(), and SSL_shutdown/SSL_free before close()
*/
