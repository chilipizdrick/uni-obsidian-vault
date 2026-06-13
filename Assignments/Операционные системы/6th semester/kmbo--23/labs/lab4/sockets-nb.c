#define _GNU_SOURCE

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* number of lines to generate on client side */
static const unsigned int nlines = 10;

static void proceed_client(FILE *f, const char *name);
static void server_loop(int servsock);
static void client_loop(int csock, unsigned int lines);
static void usage(const char *msg);

struct client_state {
    int csock;
    char *buf;
    size_t bufsize, bufused;
} *clients;

/*
 * Processes data sent by client until end-of-stream or error.
 */
void proceed_client(FILE *f, const char *name) {
    char *line = NULL;
    size_t linesize = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &linesize, f)) != -1) {
        printf("from %s: ", name);
        fwrite(line, linelen, 1, stdout);
    }
    free(line);
    /* don't care if there was any error, or just EOF */
}

/*
 * Accepts clients and proceeds them in protocol-agnostic way.
 */
void server_loop(int servsock) {
    struct sockaddr_storage sas;
    FILE *f;
    socklen_t len;
    int csock, cnum = 0;
    char numbuf[20];

    for (;;) {
        len = sizeof(struct sockaddr_storage);
        if ((csock = accept(servsock, (struct sockaddr *)&sas, &len)) == -1) {
            if (errno == EINTR)
                continue;
            err(1, "accept");
            break;
        }
        if ((f = fdopen(csock, "r+")) == NULL)
            err(1, "fdopen");
        cnum++;
        snprintf(numbuf, sizeof(numbuf), "client %d", cnum);
        printf("===> %s connected\n", numbuf);
        proceed_client(f, numbuf);
        printf("===> %s disconnected\n", numbuf);
        fclose(f);
        close(csock);
    }
}

#define countof(x) (sizeof(x) / sizeof(x[0]))

void client_loop(int csock, unsigned int lines) {
    static const char *nouns[] = {"danger", "security", "table", "picture",
                                  "rainbow"};
    static const char *verbs[] = {"eats", "sleeps", "invites", "sends", "sees"};
    static const char *adjectives[] = {"beautifully", "exclusively", "blue",
                                       "funny", "last"};

    FILE *f;
    int i, j, msgsize;
    const char *noun, *verb, *adjective;
    char *msg = NULL;
    ssize_t sent = 0, nwritten;
    struct pollfd pfd;

    memset(&pfd, 0, sizeof(pfd));
    pfd.fd = csock;
    pfd.events = POLLOUT;
    for (i = 0; i < lines; i++) {
        /*
         * CAUTION in non-fun code you should care about uniform
         * distribution; see, e.g., arc4random(3).
         */
        noun = nouns[rand() % countof(nouns)];
        verb = verbs[rand() % countof(verbs)];
        adjective = adjectives[rand() % countof(adjectives)];
        free(msg);
        msgsize = asprintf(&msg, "%s %s %s\n", noun, verb, adjective);
        if (msgsize == -1)
            err(1, "asprintf");
        sent = 0;

        while (sent < msgsize) {
            switch (poll(&pfd, 1, -1)) {
                case -1:
                    err(1, "poll");
                    break;

                case 1:
                    nwritten = write(csock, msg + sent, msgsize - sent);
                    if (nwritten == -1)
                        err(1, "write");
                    else
                        sent += nwritten;
                    break;
            }
        }
        sleep(1);
    }
    free(msg);
}

#undef countof

void usage(const char *msg) {
    const char *name;
    if (msg != NULL)
        fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "usage: %s {server|client} unix path\n",
            program_invocation_short_name);
    fprintf(stderr, "       %s {server|client} {inet|inet6} port [address]\n",
            program_invocation_short_name);
    exit(2);
}

int main(int argc, char **argv) {
    struct sockaddr_storage ss;
    socklen_t slen;
    int s, servermode;

    if (argc < 4 || argc > 5)
        usage(NULL);

    if (strcmp(argv[1], "server") == 0)
        servermode = 1;
    else if (strcmp(argv[1], "client") == 0)
        servermode = 0;
    else
        usage("invalid mode, should be either server or client");

    memset(&ss, 0, sizeof(struct sockaddr_storage));
    if (strcmp(argv[2], "unix") == 0) {
        struct sockaddr_un *sun = (struct sockaddr_un *)&ss;

        if (argc > 4)
            usage(NULL);
        sun->sun_family = AF_UNIX;
        if (strlcpy(sun->sun_path, argv[3], sizeof(sun->sun_path)) >=
            sizeof(sun->sun_path))
            usage("UNIX socket path is too long");
        slen = sizeof(struct sockaddr_un);
        if (servermode)
            unlink(argv[3]);
    } else if (strcmp(argv[2], "inet") == 0 || strcmp(argv[2], "inet6") == 0) {
        int port, rv;

        ss.ss_family = ((argv[2][4] == '\0') ? AF_INET : AF_INET6);
        port = atoi(argv[3]);
        if (port <= 0 || port > 65535)
            errx(1, "invalid port: %s", argv[3]);
        if (ss.ss_family == AF_INET) {
            struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
            sin->sin_port = htons((uint16_t)port);
            slen = sizeof(struct sockaddr_in);
        } else {
            struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&ss;
            sin6->sin6_port = htons((uint16_t)port);
            slen = sizeof(struct sockaddr_in6);
        }

        if (argc > 4) {
            if (ss.ss_family == AF_INET) {
                struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
                rv = inet_pton(AF_INET, argv[4], &sin->sin_addr);
            } else {
                struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&ss;
                rv = inet_pton(AF_INET6, argv[4], &sin6->sin6_addr);
            }
            if (!rv)
                errx(1, "invalid network address: %s", argv[4]);
        } else if (servermode) {
            /*
             * Binding to "any" address is done by zeroing address,
             * which was already done by memset(3).
             */
        } else {
            /* connect to local address by default */
            if (ss.ss_family == AF_INET) {
                inet_pton(ss.ss_family, "127.0.0.1",
                          &((struct sockaddr_in *)&ss)->sin_addr);
            } else {
                inet_pton(ss.ss_family, "::1",
                          // inet_pton(ss.ss_family,
                          // "0000:0000:0000:0000:0000:0000:0000:0001",
                          &((struct sockaddr_in6 *)&ss)->sin6_addr);
            }
        }
    } else {
        usage("invalid protocol family");
    }

    if ((s = socket(ss.ss_family, SOCK_STREAM, 0)) == -1)
        err(1, "socket");
    if (servermode) {
        if (bind(s, (const struct sockaddr *)&ss, slen) == -1)
            err(1, "bind");
        if (listen(s, 10) == -1)
            err(1, "listen");
        server_loop(s);
    } else {
        int flags = fcntl(s, F_GETFL);
        fcntl(s, F_SETFL, flags | O_NONBLOCK);
        if (connect(s, (const struct sockaddr *)&ss, slen) == -1 &&
            errno != EINPROGRESS)
            err(1, "connect");
        client_loop(s, nlines);
    }
    close(s);

    return 0;
}
