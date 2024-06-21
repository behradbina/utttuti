#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define NUMBER_OF_COMMANDS 8
#define LOGIN 2
#define LOGOUT -1
#define MINIMUM_OF_LENGTH 1
#define COM1 "signup"
#define COM2 "login"
#define COM3 "post"
#define COM4 "like"
#define COM5 "logout"
#define COM6 "delete"
#define COM7 "info"
#define COM8 "find_user"

struct user_name_liked
{
    char* user;
    struct user_name_liked * next;
};
typedef struct user_name_liked user_name_liked;

struct post_info
{
    char* user; 
    int post_id;
    int like;
    char* post;
    user_name_liked *first_user;
    struct post_info * next;
};
typedef struct post_info post_info;

struct account
{
    char* username;
    char* password;
    post_info *first_post;
    struct account* next;
};
typedef struct account account;

post_info* create_head_post();
account* create_head_account();
user_name_liked* create_head_user_name_liked();
char* get_command();
char* word(int number, char* command);
int code_command(char* command);
int number_of_command_words(char*str);
int signup(account *head,char* command);
account* login(char* command,account *head_account);
int round1_filter(char* command,account* head_account);
int post(account* your_account, char* command);
int like(account* your_account, account* head_account, char* command);
int delete_post (account* your_account, char* command);
int info(account* your_account);
int find_user(account* head_account, char* command);
int filter(char*command, account* head_account, account* your_account);
void save_accounts_data(account* head_account);
