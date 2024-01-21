#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATE_BUFFER 10
#define BUFFER_MAX_SIZE 500

char date[DATE_BUFFER];
char time[DATE_BUFFER];

int main()
{   
    fileinitialization();
    startprogram();    
    return 0;
}

int startprogram()
{
 int choice, category;
    FILE *dateptr;
    dateptr = popen("date +%d-%m-%y","r");
    if (dateptr == NULL)
        printf("\nFailed to get date\n");
    else
        fgets(date, sizeof(dateptr)+1, dateptr);
    pclose(dateptr);
    printf("\n Current Date is => %s",date);
    do{
        printf("\n *************************WELCOME TO DAILY EXPENSE TRACKER********************** \n Please select the operation you wish to perform");
        printf("\n 1. ENTER EXPENSE \n 2. DISPLAY EXPENSE \n 3. CHANGE DATE \n 0. EXIT \n Your Choice: ");
        scanf("%d",&choice);
        if(!(choice >= 0 && choice <= 3)){
            invalidinput();
            return 0;}
        else{
        switch(choice)
        {
            case 1: 
                    enterexpense();
                    return 0;
                    break;
            
            case 2: 
                    display();
                    return 0;
                    break;
            
            case 3: 
                    printf("\nEnter date and time in the format explained in dd-mm-yy: ");
                    scanf("%s",date);
                    printf("\nEntered date is: %s",date);
                    break;

            case 0:
                    return 0;
                    break;

            case 5:
                    return 0;
                    break;

            default:
                    main();
        }
    }}while(choice!=0);
    return 0;
}

int enterexpense()
{
    char description[50];
    int amount, choice;
    printf("\n *********************************** SELECT CATEGORY ****************************************\n 1. Transport \n 2. Education \n 3. Food \n 4. Miscellaneous \n 5. EXIT \n Your Choice: ");
    scanf("%d",&choice);
    if(!(choice >= 0 && choice <= 4)){
        invalidinput();
        return 0;
    }else{
        printf("\n ENTER AMOUNT: ");
        scanf("%d",&amount);
        if(!(amount >= 0 && amount<= 999999999999))
        {
            invalidinput();
            return 0;
        }else{
        printf("\n ENTER short description [maximum 50 characters only]: ");
        getchar();
        gets(description);
        printf("entered input : %s",description);
        writerecordinfile(choice, amount, description);
        printf("\n Response recorded successfully !!!!!!!!\n");
        startprogram();
        return 0;  
        } 
    }
}

int writerecordinfile(int title, int money, char *details)
{
        FILE *fptrtrans;
        FILE *fptredu; 
        FILE *fptrfood; 
        FILE *fptrmisc;

    findtime();
    switch (title)
    {
        case 1:
                printf("opening file");
                fptrtrans = fopen("./transport","a+");
                if (fptrtrans == NULL){
                    printf("\nNot able to open file\n");
                    } 
                fprintf(fptrtrans,"TRANS%s\t\t%d\t\t%s\t\t%s\n",time,money,date,details);
                fclose(fptrtrans);
                break;
    
        case 2:
                fptredu = fopen("./education","a+");
                if (fptredu == NULL){
                     printf("\nNot able to open file\n");
                    } 
                fprintf(fptredu,"EDUC%s\t\t%d\t\t%s\t\t%s\n",time,money,date,details);
                fclose(fptredu);
                break;

        case 3:
                fptrfood = fopen("./food","a+");
                if (fptrfood == NULL){
                    printf("\nNot able to open file\n");
                    } 
                fprintf(fptrfood,"FOOD%s\t\t%d\t\t%s\t\t%s\n",time,money,date,details);
                fclose(fptrfood);
                break;
        case 4:
                fptrmisc = fopen("./misc","a+");
                if (fptrmisc == NULL){
                     printf("\nNot able to open file\n");
                    } 
                fprintf(fptrmisc,"MISC%s\t\t%d\t\t%s\t\t%s\n",time,money,date,details);
                fclose(fptrmisc);
                break;
    }
    return 0;
}

int display()
{
    int choice,ch;
    FILE *displayptr;
    char data[BUFFER_MAX_SIZE];
    printf("\n *********************************** SELECT CATEGORY ****************************************\n 1. Transport \n 2. Education \n 3. Food \n 4. Miscellaneous \n 5. EXIT \n Your Choice: ");
    scanf("%d",&choice);
    if(!(choice>=1 && choice <=5)){
        invalidinput();
        return 0;
    }
    else{
    switch(choice)
    {
        case 1:
                displayptr = fopen("./transport","r");
                if (displayptr == NULL)
                    printf("\nFailed to read file\n");
                else{
                    do {
                        ch = fgetc(displayptr);
                        printf("%c",ch);
                        } while (ch != EOF);
                    }
                    fclose(displayptr);
                break;

        case 2:
                displayptr = fopen("./education","r");
                if (displayptr == NULL)
                    printf("\nFailed to read file\n");
                else{
                    do {
                        ch = fgetc(displayptr);
                        printf("%c", ch);
                        } while (ch != EOF);
                    }
                    fclose(displayptr);
                break;
        case 3:
                displayptr = fopen("./food","r");
                if (displayptr == NULL)
                    printf("\nFailed to read file\n");
                else{
                    do {
                        ch = fgetc(displayptr);
                        printf("%c",ch);
                        } while (ch != EOF);
                    }
                    fclose(displayptr);
                break;
        
        case 4:
                displayptr = fopen("./misc","r");
                if (displayptr == NULL)
                    printf("\nFailed to read file\n");
                else{
                    do {
                        ch = fgetc(displayptr);
                        printf("%c",ch);
                        } while(ch != EOF);
                    }
                    fclose(displayptr);
                break;
        
        case 5:
                return 0;
                break;

        default:
                printf("\nWrong input\n");
                display();
                break;
    }
    startprogram();
    return 0;
    }
}

int findtime()
{
    FILE *timeptr;
    timeptr = popen("date +%H1%M2%S","r");
    if(timeptr == NULL)
        printf("Unable to get time");
    else
        fgets(time, sizeof(timeptr)+1, timeptr);
    pclose(timeptr);
    return 0;
}

int fileinitialization()
{
        FILE *fptrtrans;
        FILE *fptredu; 
        FILE *fptrfood; 
        FILE *fptrmisc;

        fptrtrans = fopen("./transport","r");
        if (fptrtrans == NULL){
            printf("fileptrtrans doesnt exist");
            system("touch ./transport");
            fptrtrans = fopen("./transport","a+"); 
            fprintf(fptrtrans,"--------------------------------------------------------------------------------------------\nID\t\t\tAmount\t\tDate\t\t\tDetails\n--------------------------------------------------------------------------------------------\n");
            fclose(fptrtrans);}

        fptredu = fopen("./education","r");
        if (fptredu == NULL){
            printf("fileptredu doesnt exist");
            system("touch ./education");
            fptredu = fopen("./education","a+");
            fprintf(fptredu,"--------------------------------------------------------------------------------------------\nID\t\t\tAmount\t\tDate\t\t\tDetails\n--------------------------------------------------------------------------------------------\n");
            fclose(fptredu);}

        fptrfood = fopen("./food","r");
        if (fptrfood == NULL){
            printf("fileptrfood doesnt exist");        
            system("touch ./food");
            fptrfood = fopen("./food","a+");
            fprintf(fptrfood,"--------------------------------------------------------------------------------------------\nID\t\t\tAmount\t\tDate\t\t\tDetails\n--------------------------------------------------------------------------------------------\n");
            fclose(fptrfood);}

        fptrmisc = fopen("./misc","r");
        if (fptrmisc == NULL){
            printf("fileptrmisc doesnt exist");
            system("touch ./misc");
            fptrmisc = fopen("./misc","a+");
            fprintf(fptrmisc,"--------------------------------------------------------------------------------------------\nID\t\t\tAmount\t\tDate\t\t\tDetails\n--------------------------------------------------------------------------------------------\n");
            fclose(fptrmisc);}
        
        return 0;
}

int invalidinput()
{
    printf("\n Invalid input please try again!! \n");
    return 0;
}
