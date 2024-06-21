#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
    account* head_account = create_head_account();
    account* your_account;
    
    while (TRUE)
    {
        int login_status = FALSE;
        int status = FALSE;
        char * w;
        char* command = get_command();
        status = round1_filter(command,head_account);

        if (status == LOGIN)
        {            
            your_account = login(command,head_account);
            login_status = LOGIN;            
        }
        free(command);
        while (login_status == LOGIN)
        {
            char* command = get_command();
            int result_of_filter = filter(command,head_account,your_account);
            if (result_of_filter == LOGOUT){
                save_accounts_data(head_account);
                break;
            }
            free(command);
        }        
    }    
}
