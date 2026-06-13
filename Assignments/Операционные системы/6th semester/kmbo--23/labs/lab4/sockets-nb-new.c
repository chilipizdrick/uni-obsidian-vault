#define _GNU_SOURCE

#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

// Number of lines to generate on client side
static const unsigned int nlines = 10;

static void server_loop(int servsock);
static void client_loop(int csock, unsigned int lines);
static void usage(const char *msg);

// Linked list of client connection contexts
struct client_ctx {
    int fd;
    FILE *f;
    char *linebuf;
    size_t linebufsz;
    struct client_ctx *next;
    struct client_ctx *prev;
};

void server_loop(int servsock) {
    // Set non-blocking mode
    int flags = fcntl(servsock, F_GETFL);
    if (flags == -1)
        err(1, "fcntl F_GETFL failed");
    if (fcntl(servsock, F_SETFL, flags | O_NONBLOCK) == -1)
        err(1, "fcntl F_SETFL failed");

    struct client_ctx *head = NULL;

    for (;;) {
        // Count server fd
        int nfds = 1;
        // And all client fds
        for (struct client_ctx *c = head; c != NULL; c = c->next)
            nfds++;

        // Prepare pollfds array
        struct pollfd pfds[nfds];

        // Populate pollfds with server's fd + expected event
        pfds[0].fd = servsock;
        pfds[0].events = POLLIN;

        // Populate pollfds with clients' fd + expected event
        int i = 1;
        for (struct client_ctx *c = head; c != NULL; c = c->next) {
            pfds[i].fd = c->fd;
            pfds[i].events = POLLIN;
            i++;
        }

        // Wait for server and client events
        if (poll(pfds, nfds, -1) == -1) {
            // Check if IO operation was interrupted, then continue
            if (errno == EINTR) {
                continue;
            }
            err(1, "poll failed");
        }

        // Handle new connections
        if (pfds[0].revents & POLLIN) {
            for (;;) {
                struct sockaddr_storage sas;
                socklen_t len = sizeof(sas);
                int csock = accept(servsock, (struct sockaddr *)&sas, &len);

                if (csock == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        break; // No more new clients
                    // Check if IO operation was interrupted, then continue
                    if (errno == EINTR)
                        continue;
                    warn("accepting connection from client failed");
                    break;
                }

                // Set non-blocking mode for client connection
                int cflags = fcntl(csock, F_GETFL);
                fcntl(csock, F_SETFL, cflags | O_NONBLOCK);

                // Open stream for client connection with read/write mode
                FILE *f = fdopen(csock, "r+");
                if (!f) {
                    warn("fdopen failed");
                    close(csock);
                    continue;
                }

                printf("=> client connected (fd %d)\n", csock);

                // Create client context and add to linked list
                struct client_ctx *new_c = malloc(sizeof(struct client_ctx));
                new_c->fd = csock;
                new_c->f = f;
                new_c->linebuf = NULL;
                new_c->linebufsz = 0;
                new_c->next = head;
                new_c->prev = NULL;

                if (head)
                    head->prev = new_c;
                head = new_c;
            }
        }

        // Read data from clients
        i = 1;
        struct client_ctx *c = head;
        // Iterate over all clients in linked list
        while (c != NULL) {
            // Prefetch next client since this one might be freed
            struct client_ctx *next = c->next;

            if (pfds[i].revents & (POLLIN | POLLERR | POLLHUP)) {
                ssize_t linelen;

                // Read all avaliable lines, until EAGAIN or EOF
                while ((linelen = getline(&c->linebuf, &c->linebufsz, c->f)) !=
                       -1) {
                    printf("from fd %d: ", c->fd);
                    fwrite(c->linebuf, linelen, 1, stdout);
                }

                // If reached EOF or error, close client connection
                if (feof(c->f) ||
                    (ferror(c->f) && errno != EAGAIN && errno != EWOULDBLOCK)) {
                    printf("=> client disconnected (fd %d)\n", c->fd);

                    // Delete client from linked list
                    if (c->prev)
                        c->prev->next = c->next;
                    else
                        head = c->next;
                    if (c->next)
                        c->next->prev = c->prev;

                    fclose(c->f);
                    free(c->linebuf);
                    free(c);
                } else if (ferror(c->f)) {
                    clearerr(c->f);
                }
            }
            // Proceed to next client
            c = next;
            i++;
        }
    }
}

#define countof(x) (sizeof(x) / sizeof(x[0]))

void client_loop(int csock, unsigned int lines) {
    static const char *nouns[] = {"danger", "security", "table", "picture",
                                  "rainbow"};
    static const char *verbs[] = {"eats", "sleeps", "invites", "sends", "sees"};
    static const char *adjectives[] = {"beautifully", "exclusively", "blue",
                                       "funny", "last"};

    int i, msgsize;
    const char *noun, *verb, *adjective;
    char *msg = NULL;
    ssize_t sent = 0, nwritten;

    // Run in blocing mode
    for (i = 0; i < lines; i++) {
        noun = nouns[rand() % countof(nouns)];
        verb = verbs[rand() % countof(verbs)];
        adjective = adjectives[rand() % countof(adjectives)];

        free(msg);
        msgsize = asprintf(&msg, "%s %s %s\n", noun, verb, adjective);
        if (msgsize == -1)
            err(1, "asprintf failed");

        sent = 0;

        // Write message to server in a loop
        while (sent < msgsize) {
            // Try to write whole message
            nwritten = write(csock, msg + sent, msgsize - sent);
            // If error occurred while writing, continue
            if (nwritten == -1) {
                if (errno == EINTR)
                    continue;
                err(1, "write failed");
            }
            sent += nwritten;
        }

        sleep(1);
    }
    free(msg);
}

#undef countof

void usage(const char *msg) {
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
            /* Binding to "any" already done via memset(0) */
        } else {
            if (ss.ss_family == AF_INET) {
                inet_pton(ss.ss_family, "127.0.0.1",
                          &((struct sockaddr_in *)&ss)->sin_addr);
            } else {
                inet_pton(ss.ss_family, "::1",
                          &((struct sockaddr_in6 *)&ss)->sin6_addr);
            }
        }
    } else {
        usage("invalid protocol family");
    }

    if ((s = socket(ss.ss_family, SOCK_STREAM, 0)) == -1)
        err(1, "socket failed");

    if (servermode) {
        if (bind(s, (const struct sockaddr *)&ss, slen) == -1)
            err(1, "bind failed");
        if (listen(s, 10) == -1)
            err(1, "listen failed");
        server_loop(s);
    } else {
        if (connect(s, (const struct sockaddr *)&ss, slen) == -1)
            err(1, "connect failed");
        client_loop(s, nlines);
    }

    close(s);
    return 0;
}
