#include<stdio.h>
#include<string.h>
char movie[20];
struct ticket
{
    char name[20];
    char email_id[45];
    long int p_number;
};
void Detail_reciver(struct ticket t,int a[],int n,FILE *det)
{
    int l,r;
    printf("\nEnter the following details");
    printf("\nEnter your name:\t");
    scanf("%s",t.name);
    printf("\nEnter your phone number:\t");
    scanf("%ld",&t.p_number);
    printf("\nEnter your email id:\t");
    scanf("%s",t.email_id);
    fputs("Occupied seats: ",det);
    for(int i=0;i<n;i++)
    {
        fprintf(det,"%d",a[i]);
        fputs(", ",det);
    }
    fputs("\n",det);

    fputs(t.name,det);
    fputs("\n",det);

    fputs(t.email_id,det);
    fputs("\n",det);

    fprintf(det,"%ld",t.p_number);
    fputs("\n",det);
    fputs("\n",det);

    fclose(det);
}
void admin()
{
    char admin_id[20],det[25];
    char admin_pass[10],time[10];
    int choice,size;
    FILE *movdet,*d1,*d2;
    char num[5],ch;
    L4:printf("Admin id:\t");
    scanf("%s",admin_id);
    printf("Admin password:\t");
    scanf("%s",admin_pass);
    if(strcmp(admin_id,"admin@123")==0 && strcmp(admin_pass,"123")==0)
    {
        L8 :printf("\n1]----->change movie name and timings");
        printf("\n2]----->get the show details");
        L5:printf("\nEnter your choice : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            movdet=fopen("Movie_details.txt","w+");
            for(int i=0;i<2;i++)
            {
               num[0]=(i+1)+'0';
               printf("Enter a movie name:\t");
               scanf("%s",movie);
               printf("Enter the movie timing:\t");
               scanf("%s",time);
               if(strlen(movie)>0 && strlen(time)>0)
               {
                 fputs(num,movdet);
                 fputs("] ",movdet);
                 fputs(movie,movdet);
                 fputs("\t",movdet);
                 fputs(time,movdet);
                 fputs("\n",movdet);
               }
            }
            printf("Successfully saved!!!\n\n");
        }
        else if(choice==2)
        {
            movdet=fopen("Movie_details.txt","a+");
            int i=0;
            while(i<2)
            {
                fgets(det,25,movdet);
                printf("%s",det);
                i++;
            }
            L6:printf("Enter the movie number for the user details : ");
            scanf("%d",&choice);
            if(choice==1)
            {
                d1=fopen("Details1.txt","r+");
                while((ch=fgetc(d1))!= EOF)
                    printf("%c",ch);
                printf("\n\n\n");
                fclose(d1);
            }
            else if(choice==2)
            {
                d2=fopen("Details2.txt","r+");
                while((ch=fgetc(d2))!=EOF)
                printf("%c",ch);
                printf("\n\n\n");
                fclose(d2);
            }
            else
            {
                printf("\nWrong input\n");
                goto L6;
            }
        }
        else
        {
            printf("Sorry wrong choice!!! Try again.");
            goto L5;
        }
    }
    else
    {
        printf("\nInvalid credentials!\n");
        goto L4;
    }
    fclose(movdet);
    printf("\n\n----->1] Continue as admin\n----->Press any key to leave\n\n");
    scanf("%d",&choice);
    if(choice==1)
        goto L8;

}

void book(FILE *poi,FILE *seat)
{
    int a=0,tick[80],no=0,occupied;
    struct ticket t1;
    printf("\t\t\t\t\t\t\t\tSCREEN\n\n");

    int occ[80]={0},i=0;
    while((occupied=getw(seat)) != EOF)
    {
        occ[i]=occupied;
        i++;
    }
    for(int j=0;j<8;j++)
    {
        printf("\t");
        for(int k=0;k<10;k++)
        {
            int flag=0;
            a++;
            for(int r=0;r<80;r++)
            {
                if(occ[r]==a)
                {
                    if(a<10)
                        printf("0%d-O\t",a);
                    else
                        printf("%d-O\t",a);
                    flag=0;
                    break;
                }
                else
                    flag=1;
            }

            if(flag==1)
            {
              if(a<10)
                printf("0%d-V\t",a);
              else
                printf("%d-V\t",a);
            }
        }
        printf("\n");
    }
    printf("\nPrices");
    printf("\nSeats [01 - 20]---> Rs.50--->Budget");
    printf("\nSeats [21 - 60]---> Rs.110--->Premium");
    printf("\nSeats [61 - 80]---> Rs.140--->Elite");
    L3:printf("\n\nEnter the number of tickets you want : ");
    scanf("%d",&no);
    if(no>(80-i))
    {
        printf("\nSo many number of seats not available\n");
        goto L3;
    }
    printf("\nEnter the seat number as per the seating vacancy displayed above ");
    for(int i=0;i<no;i++)
    {
        L7:printf("\nnext:");
        scanf("%d",&tick[i]);
        if(tick[i]>80)
        {
            printf("Oops!! Wrong input. Try again");
            goto L7;
        }
        else
        {
            for(int k=0;k<80;k++)
            {
                if(occ[k]==tick[i])
                {
                    printf("Oops!! Already booked. Try another seat");
                    goto L7;
                }
            }
        }
        for(int s=0;s<i;s++)
        {
            if(tick[s]==tick[i])
            {
                printf("\nAlready entered the seat number\n");
                goto L7;
            }
        }
        putw(tick[i],seat);
    }
    fclose(seat);
    a=0;
    Detail_reciver(t1,tick,no,poi);
    float sum=0,tax=0;
    for(int i=0;i<no;i++)
    {
        if(tick[i]>0 && tick[i]<=20)
            sum=sum+50;
        else if(tick[i]>=21 && tick[i]<=60)
            sum=sum+110;
        else
            sum=sum+140;
    }
    printf("\nNo. of seats booked: %d",no);
    printf("\nBooked seats:");
    for(int r=0;r<no;r++)
    printf("%d, ",tick[r]);
    printf("\nTotal amount: Rs.%.2f/-",sum);
    tax=(sum*5)/100;
    printf("\nTax amount: Rs.%.2f/-",tax);
    printf("\nNet amount: Rs.%.2f/-",sum+tax);
    printf("\nHAVE A GREAT DAY!!!\n\n\n");

    fclose(poi);

}
int main()
{
    FILE *Md,*d1,*d2,*s1,*s2;
    int choice;
    int ch=0;
    char det[25];
    printf("____________________________________________________________________\n");
    printf("____________________________________________________________________\n");
    printf("|                WELCOME TO MY CINEMAS                             |\n");
    printf("|             BOOK YOUR TICKETS RIGHT AWAY                         |\n");
    printf("____________________________________________________________________\n");
    printf("____________________________________________________________________\n");
    l1 : printf("1]-----> Book your ticket\n");
    printf("2]-----> Admin login\n");
    printf("3]----->Exit\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        Md=fopen("Movie_details.txt","a+");
        int i=0;
        while(i<2)
        {
            fgets(det,25,Md);
            printf("%s",det);
            i++;
        }
        L2:printf("ENTER YOUR MOVIE CHOICE\n");
        scanf("%d",&ch);
        if(ch==1)
        {
                d1=fopen("Details1.txt","a+");
                s1=fopen("Seats1.txt","a+");
                book(d1,s1);
                goto l1;
        }
        else if(ch==2)
        {
            d2=fopen("Details2.txt","a+");
            s2=fopen("Seats2.txt","a+");
            book(d2,s2);
            goto l1;
        }
        else
        {
            printf("\nInvalid choice. Try again");
            printf("\n");
            goto L2;
        }
    }
    else if(choice==2)
    {
        admin();
        goto l1;
    }
    else if(choice==3)
        printf("\n\n\nHAVE A GREAT DAY!!!\n");

    else
    {
        printf("Invalid choice. Please enter again\n");
        goto l1;
    }
}
