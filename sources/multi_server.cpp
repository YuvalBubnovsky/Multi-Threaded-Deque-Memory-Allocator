#define NUM_OF_FUNC 5
#define _POSIX_C_SOURCE 199309
#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "deque.hpp"

#define PORT "3490" // the port users will be connecting to

// Delimiter definition needed for parsing, this will be passed to strtok()
#define DELIM " \t\r\n\a"
#define TOKEN_SIZE 256

#define BACKLOG 10 // how many pending connections queue will hold

pdeq deq = (pdeq)malloc(sizeof(pdeq)); // singleton

// Function handlers

char const *func_names[] = {"POP", "TOP", "PUSH", "ENQUEUE", "DEQUEUE"};

int POP(char **args)
{
    _POP(deq);
    printf("Got POP Request\n");
    return 1;
} // TODO: better return the just return 1;
int TOP(char **args)
{
    pnode top = _TOP(deq);
    printf("Got TOP Request\n");
    if (top != NULL)
    {
        printf("%s\n", top->value);
    }

    return 1;
}

int PUSH(char **args)
{
    pnode node = (pnode)malloc(sizeof(pnode));
    node->value = args[1];
    printf("Got PUSH Request\n");
    printf("%s\n", args[1]);
    _PUSH(deq, node);
    return 1;
}

int ENQUEUE(char **args)
{
    pnode node = (pnode)malloc(sizeof(pnode));
    node->value = args[1];
    printf("Got ENQUEUE Request\n");
    printf("%s\n", args[1]);

    _ENQUEUE(deq, node);
    return 1;
}
int DEQUEUE(char **args)
{
    _DEQUEUE(deq);
    printf("Got DEQUEUE Request\n");

    return 1;
}

int (*func_implements[])(char **) = {
    &POP,
    &TOP,
    &PUSH,
    &ENQUEUE,
    &DEQUEUE};

char **parse_args(char *input)
{
    int buff_size = TOKEN_SIZE;
    int pos = 0;

    char *token;
    char **tokens = (char **)malloc(sizeof(char *) * buff_size);
    if (tokens == NULL)
    {
        fprintf(stderr, "Couldn't Allocate For Tokens!\n");
        exit(1);
    }

    token = strtok(input, DELIM);
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;

        token = strtok(NULL, DELIM); // searching for more tokens in the string
    }
    tokens[pos] = NULL;
    return tokens;
}

int execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1; // Empty command
    }

    for (int i = 0; i < NUM_OF_FUNC; i++)
    {
        if (strcmp(args[0], func_names[i]) == 0)
        {
            return (*func_implements[i])(args);
        }
    }

    return 1;
}

void *sock_thread(void *arg) /* ***************** THREAD HANDLER ***************** */
{
    int n;
    char buffer[2048];
    char **args;
    int new_sock = *((int *)arg);
    bzero(buffer, 2048);
    printf("New connection from %d\n", new_sock); // DEBUG ONLY
    sleep(1);

    while ((n = recv(new_sock, &buffer, sizeof(buffer), 0)) > 0)
    {
        if (n == -1)
        {
            perror("recv");
        }
        args = parse_args(buffer);
        execute(args);
    }

    close(new_sock);
    pthread_exit(NULL);
}

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    pthread_t new_thread[10]; // We need to be able to server 10 connections at the same time
    int i = 0;
    while (1)
    { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        // create a new thread, assign it to our thread array and send the thread_id and socket FD to out thread handler
        if (pthread_create(&new_thread[i++], NULL, sock_thread, &new_fd) != 0)
        {
            printf("ERROR: Failed To Create Thread!\n");
        }

        // Loop over our threads array and join all completed threads, freeing up resources
        if (i >= 10)
        {
            i = 0;
            while (i < 10)
            {
                pthread_join(new_thread[i++], NULL);
            }
            i = 0;
        }
    }

    return 0;
}