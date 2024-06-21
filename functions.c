#include "functions.h"

char commands [NUMBER_OF_COMMANDS][10] = {COM1,COM2,COM3,COM4,COM5,COM6,COM7,COM8};

post_info* create_head_post()
{
    post_info *head = (post_info*)malloc(sizeof(post_info));
    head->post_id = 0;
    head->next = NULL;
    return head;
}

account* create_head_account()
{
    account *head = (account*)malloc(sizeof(account));
    head->next = NULL;
    return head;
}
//linked list for users who like a certain post 
user_name_liked* create_head_user_name_liked()
{
    user_name_liked* head = (user_name_liked*)malloc(sizeof(user_name_liked));
    head->next = NULL;
    head->user = "login";
    return head;
}
//gettin command from users
char* get_command()
{
    char* str = (char*)malloc(MINIMUM_OF_LENGTH * sizeof(char*));
    if (str == NULL)
    {
        printf("Error in allocation memory!\n");
        return NULL;
    }
    
    int size = MINIMUM_OF_LENGTH;
    char c;

    //This get a string with dynamic size!
    for (int i = 0; i <= size; i++)
    {
        c = (char)getchar();
        str[i] = c;
        if (i == size && c != '\n')
        {
            size ++;
            str = (char*)realloc(str,size * sizeof(char*));
            if (str == NULL)
            {
                printf("Error in re-allocation memory in post function!\n");
                return NULL;
            }
        }

        else if (i == size && c == '\n')
        {
            str[i] = '\0'; //change the last character from \n into null!
            return str;
        }       
    }
}
//split function 
char* word(int number, char* command)
{
    char* result = (char*)malloc(MINIMUM_OF_LENGTH*sizeof(char));
    int size = MINIMUM_OF_LENGTH;
    int i = 0;
    int j = 0;

    if (number == 1)
    {
        while ( command[i] != '\0' && command[i] != ' ' )
        {
            result[i] = command[i];
            size ++;
            i++;
            result = (char*)realloc(result, size*sizeof(char));

        }
        result[i] = '\0';
    }

    else if (number == 2)
    {       
        while (command[i] != ' ')
            i++;
        
        i++;
        
        while ( command[i] != '\0' && command[i] != ' ' )
        {
            result[j] = command[i];
            size ++;
            i++;
            j++;
            result = (char*)realloc(result, size*sizeof(char));
        }
        result[j] = '\0';
    }

    else if (number == 3)
    {
        while (command[i] != ' ')
        {
            i++;
        }
        i++;
        while (command[i] != ' ')
        {
            i++;
        }
        i++;
        while ( command[i] != '\0')
        {
            result[j] = command[i];
            size ++;
            i++;
            j++;
            result = (char*)realloc(result, size*sizeof(char));
        }
        result[j] = '\0';
    }

    else if (number == 4)
    {        
        while (command[i] != ' ')
        {
            i++;
        }
        i++;
        
        while ( command[i] != '\0')
        {
            result[j] = command[i];
            size ++;
            i++;
            j++;
            result = (char*)realloc(result, size*sizeof(char));
        }
        result[j] = '\0';
    }
    
    return result;
}
//each command has a certain code this function returns it
int code_command(char* command)
{   
    char* com =word(1,command); 
    for (int i = 1; i <= NUMBER_OF_COMMANDS; i++)
    {
        if (strcmp(com,commands[i-1]) == 0)
        {
            free(com);
            return i;
        }
        
    }
    free(com);
    return FALSE;
}
//count the number of string by spaces
int number_of_command_words(char*str)
{
    int i = 0;
    int separator_count = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ' && str[i+1] != ' ' && str[i+1] != '\0') {
            separator_count++;
        }
        i++;
    }
    separator_count ++;
    return separator_count;
}

int signup(account *head,char* command)
{
    int number_of_words = number_of_command_words(command);
    account* new_account = (account*)malloc(sizeof(account));  
    char* username;
    char* password;

    if (new_account == NULL)
    {
        printf("Error in memory allocation function signup!\n Try again!\n");
        free(new_account);
        return FALSE;
    }

    if (number_of_words < 3)
    {
        printf("Number of words for signup must be 3!\n");
        free(new_account);
        return FALSE;
    }

    account* current = head;
    username = word(2,command);

    for (int i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        if (strcmp(username,commands[i]) == 0)
        {
            printf("This username is illegal!\n");
            free(username);
            free(new_account);
            return FALSE;
        }       
    }
    
    //checking for repetitive username 
    while (current != NULL)
    {
        if (strcmp(current->username,username) == 0)
        {
            printf("This username has been already taken!\n");
            free(username);
            free(new_account);
            return FALSE;
        }
        current = current->next;
    }

    current = head;

    while (current->next != NULL)
    {
        
        current = current->next;
    }

    password = word(3,command);
    new_account->first_post = create_head_post();
    new_account->username = username;
    new_account->password = password;
    new_account->next = NULL;
    current->next = new_account;
    printf("Signup Successfully!\n");
    return TRUE;
}

account* login(char* command,account *head_account)
{
    account* current = head_account;
    char* username = word(2,command);
    char* password = word(3,command);
    while (current != NULL)
    {
        if ((strcmp(current->username,username) == 0) && (strcmp(current->password,password) == 0))
        {   
            free(username);
            free(password);       
            return current;
        }
        current = current->next;           
    }
    
}
//this function is for before login and checks the situation
int round1_filter(char* command,account* head_account)
{
    int status = 0;
    int code = code_command(command);
    int number_of_words = 0;
    char* username;
    char* password;
    
    switch (code)
    {
    case 0:
        printf("Please write a command correctly!\n");
        return FALSE;
        break;
    
    case 1:
        status = signup(head_account,command);
        return status;
        break;
        
    case 2:
        number_of_words = number_of_command_words(command);

        if (number_of_words < 3)
        {
            printf("Number of words in login must be 3!\n");
            return FALSE;
        }

        username = word(2,command);
        password = word(3,command);

        account* current = head_account;
        
        while (current != NULL)
        {           
            if ((strcmp(current->username,username) == 0) && (strcmp(current->password,password) == 0))
            {
                printf("Login Successfully!\n");
                free(username);
                free(password);
                return LOGIN;
            }
            current = current->next;           
        }
        printf("Password and username is not matched!\n");
        free(username);
        free(password);
        return FALSE;
        break;

    default:
        printf("You aren't login yet!\n");
        return FALSE;
        break;
    } 
}

int post(account* your_account, char* command)
{
    char* post_text = word(4,command);
    post_info* current = your_account->first_post;
    post_info* new_post = (post_info*)malloc(sizeof(post_info));
    
    while (current->next != NULL)
    {
        current = current->next;
    }
    
    new_post->like = 0;
    new_post->next = NULL;
    new_post->post_id = (current->post_id) + 1;
    new_post->user = your_account->username;
    new_post->post = post_text;
    new_post->first_user = create_head_user_name_liked();
    current->next = new_post;
    printf("Post has been uploaded successfully!\n");
    return TRUE;

}

int like(account* your_account, account* head_account, char* command)
{
    char* username;
    char* post_id = word(3,command);
    account* current_account;
    post_info* current_post;
    user_name_liked* current_liked;
    int id = atoi(post_id);
    int flag = FALSE;

    if (id == 0)
    {
        printf("Wrong post id!\n");
        free(post_id);
        return FALSE;
    }

    username = word(2,command);
    current_account = head_account;

    // check that this post exists!
    while (current_account != NULL)
    {
        if (strcmp(current_account->username,username) == 0)
        {
            current_post = current_account->first_post;
            while (current_post != NULL)
            {
                if (current_post->post_id == id)
                {
                    flag = TRUE;
                    break;
                }
                current_post = current_post->next;
            }
        }        
        if (flag == TRUE)
        {
            break;
        }        
        current_account = current_account->next;
    }

    if (flag == FALSE)
    {
        printf("Wrong username or post_id!\n");
        free(username);
        free(post_id);
        return FALSE;
    }
    
    current_liked = current_post->first_user;
    
    while (current_liked != NULL)
    {
        if (strcmp(current_liked->user,your_account->username) == 0)
        {
            printf("You already liked this post!\n");
            free(username);
            free(post_id);
            return FALSE;
        }
        current_liked = current_liked->next;
    }

    current_post->like ++;
    
    current_liked = current_post->first_user;

    while (current_liked->next != NULL)
    {
        current_liked = current_liked->next; 
    }
    user_name_liked * newuser = (user_name_liked*)malloc(sizeof(user_name_liked));
    newuser->user = your_account->username;
    newuser->next = NULL;
    current_liked->next = newuser;
    free(username);
    free(post_id);
    printf("Like Successfully!\n");
    return TRUE;
    
}

int delete_post (account* your_account, char* command)
{
    char* post_id = word(2,command);
    int id = atoi(post_id);
    post_info* current;
    post_info* previous;

    if (id == 0)
    {
        printf("Wrong post id!\n");
        free(post_id);
        return FALSE;
    }
    
    current = your_account->first_post;
    previous = your_account->first_post;

    if (current->next == NULL && current->post_id == id)
    {
        free(current);
        free(post_id);
        printf("Delete post successfully!\n");
        return TRUE;
    }
     
    while(current != NULL)
    {
        if (current->post_id == id)
        {              
            previous->next = current->next;
            free(current);
            free(post_id);
            printf("Delete post successfully!\n");
            return TRUE;             
        }
        previous = current;
        current = current->next;
    }

    printf("Wrong post id!\n");
    free(post_id);
    return FALSE;
}

int info(account* your_account)
{
    printf("username : '%s'\n", your_account->username);
    printf("password : '%s'\n", your_account->password);
    post_info* current = your_account->first_post;

    while (current != NULL)
    {
        if (current->post_id == 0)
        {
            current = current->next;
            continue;
        }
        printf("Post Id: %d\n",current->post_id);
        printf("Post: '%s'\n", current->post);
        printf("like: %d\n\n", current->like);
        current = current->next;
    }
    printf("End!\n");
    return TRUE;
}

int find_user(account* head_account, char* command)
{
    account* current_account = head_account;
    post_info* current_post;
    char* username = word(2,command);
    
    while (current_account != NULL)
    {
        if (strcmp(current_account->username,username) == 0)
        {          
            current_post = current_account->first_post;

            while (current_post != NULL)
            {
                if (current_post->post_id == 0)
                {
                    current_post = current_post->next;
                    continue;
                }
                printf("\nPost: '%s'\n", current_post->post);
                printf("Post Id: %d\n",current_post->post_id);
                printf("like: %d\n\n", current_post->like);
                current_post = current_post->next;
            }
            printf("End!\n");
            free(username);
            return TRUE;
        }

        current_account = current_account->next;           
    }

    printf("User not found!\n");
    free(username);
    return FALSE;   
}
//this function is for after login to check the user write correct command 
int filter(char*command, account* head_account, account* your_account)
{   
    int number_of_words = number_of_command_words(command);
    int code = code_command(command);
    int status;
    
    if (code == FALSE)
    {
        printf("Please write a correct command!\n");
        return FALSE;
    }
    else if (code < 3)
    {
        printf("You must logout first!\n");
        return FALSE;
    }
    
    switch (code)
    {   
    case 3:
        if (number_of_words < 2)
        {
            printf("Can't post empty text!\n");
            return FALSE;
        }
        else
        {
            status =post(your_account,command);
            return status;
        }
                
        break;
    case 4:
        if (number_of_words != 3)
        {    
            printf("Please write a correct command!\n");
            return FALSE;
        }
        else
        {
            status = like(your_account,head_account,command);
            return status;
        }
    case 5:
        if (number_of_words != 1)
        {    
            printf("Please write a correct command!\n");
            return FALSE;
        }
        else
        {
            printf("Logout successfully!\n");
            return LOGOUT;
        } 
        break;

    case 6:
        if (number_of_words != 2)
        {    
            printf("Please write a correct command!\n");
            return FALSE;
        }
        else
        {
            status = delete_post(your_account,command);
            return status;
        }
        break;

    case 7:
        if (number_of_words != 1)
        {    
            printf("Please write a correct command!\n");
            return FALSE;
        }
        else
        {
            status = info(your_account);
            return status;
        }
        break;

    case 8:
        if (number_of_words != 2)
        {    
            printf("Please write a correct command!\n");
            return FALSE;
        }
        else
        {
            status = find_user(head_account,command);
            return status;
        }
    
    default:
        printf("Error in filter function!\n");
        printf("code = %d\n", code);        
        break;
    }  
}
//save accounts data in a file
void save_accounts_data(account* head_account)
{
    FILE * account_data = fopen("accounts.txt", "w");
    FILE * post_data = fopen("posts.txt", "w");
    account* current_account = head_account;
    post_info* current_post;
    char* username;
    char* password;
    int length_of_username = 0;
    int length_of_password = 0;
    int length_of_post = 0;
    int number_of_posts = 0;

    current_account = current_account->next; //pass the head account

    while (current_account != NULL)
    {
        number_of_posts = 0;
        username = current_account->username;
        password = current_account->password;
        length_of_username = strlen(username);
        length_of_password = strlen(password);
        fwrite(username , sizeof(char), length_of_username, account_data);
        fprintf(account_data , " ");
        fwrite(password , sizeof(char), length_of_password, account_data);
        current_post = current_account->first_post;
        current_post = current_post->next; //pass the head post
        while (current_post != NULL)
        {
            length_of_post = strlen(current_post->post);
            fwrite(current_post->post , sizeof(char), length_of_post, post_data);
            fprintf(post_data , " ");
            fwrite(username , sizeof(char), length_of_username, post_data);
            fprintf(post_data , " %d\n", current_post->like);
            number_of_posts ++;
            current_post = current_post->next;
        }
        fprintf(account_data, " %d\n", number_of_posts);
        current_account = current_account->next;
    }
    fclose(account_data);
    fclose(post_data);
}
