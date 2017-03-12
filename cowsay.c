/*
    2017-03-13  1.1 support more pic,and small fix
    


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pic.h"


// 使用说明：
// ./cowsay "the message we want so say"

void print_tux(void)
{
    int i;
    for(i = 0; i < 7; i++) {
        printf("%s\n", tux[i]);
    }
}

void print_koala(void)
{
    int i;
    for(i = 0; i < 5; i++) {
        printf("%s\n", koala[i]);
    }
}


void print_cow(void);
void print_message(char*, int);
void print_message_multilines(char*, int);
void clean_stdin(void);

int main(int argc, char* argv[])
{
    int length = 0;
    char message[1000] = { 0 };
    
    if(argc >= 2) {
        // 目前只支持一个字符串作为输入参数，因此只判断argv[1]
        if((length = strlen(argv[1])) < 42) { // 如果argv[1]长度超过42,就多行显示
            print_message(argv[1], length);
        } else {
            print_message_multilines(argv[1], length);
        }
    } else {
        printf("please enter the message you want to display : \n");
        scanf("%[^\n]", message); //scanf的%[]格式控制符，表明当输入\n时才结束

        if (strlen(message) > 255) {
          printf("Usage: max 255 character limit\n");
          exit(EXIT_FAILURE);
        }	 

        printf("\n\n");
        
        if((length = strlen(message)) < 42) {
            print_message(message, length);
        } else {
            print_message_multilines(message, length);
        }
    }
   
    //print_cow();
    //print_tux();
    print_koala();
    //clean_stdin();
    printf("\n");
    exit(EXIT_SUCCESS);
    return 0;
}

void clean_stdin(void)
{
    int c;
 
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

    exit(EXIT_SUCCESS);
}

void print_cow(void)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("%s\n", cow[i]);
    }
}

void print_message_multilines(char* message, int length)
{
    int nb_chunk = (length/42)+1;
    char** strings = calloc(nb_chunk, sizeof(char*));
    
    int i;
    int j;
    for(i = 0; i < nb_chunk; i++)
    {
        strings[i] = calloc(43, sizeof(char));
    }
    
    for(i = 0; i < nb_chunk; i++)
    {
        for(j = 0; j < 42; j++)
        {
            strings[i][j] = message[i*42+j];
        }
    }
    
    for(i =(length%42); i < 42; i++)
    {
        strings[nb_chunk-1][i] = ' ';
    }
    
    
    putc(' ', stdout);
    putc('/', stdout);
    
    for(i = 0; i < strlen(strings[0]); i++)
    {
        putc('-', stdout);
    }
    putc('\\', stdout);
    putc('\n', stdout);
    
    for(i = 0; i < nb_chunk; i++)
    {
        printf("| %s |\n", strings[i]);
    }
    
    putc(' ', stdout);
    putc('\\', stdout);
    
    for(i = 0; i < strlen(strings[0]); i++)
    {
        putc('-', stdout);
    }
    putc('/', stdout);
    putc('\n', stdout);
    
    for(i = 0; i < nb_chunk-1; i++)
    {
        free(strings[i]);
    }
    
    free(strings);
}

void print_message(char* message, int length)
{
    int message_length = length;
    
    putc(' ', stdout);
    
    int i;
    for(i = 0; i < message_length+1; i++) {
        putc('_', stdout);
    }
    putc('\n', stdout);
    putc('<', stdout);
    putc(' ', stdout);
    
    printf("%s>\n", message);
    putc(' ', stdout);
    for(i = 0; i < message_length+1; i++)
    {
        putc('-', stdout);
    }
    putc('\n', stdout);
}
