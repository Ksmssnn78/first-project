#include "myfile.h"

#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

char vmm[10][50];

void admin_panel()
{
    int i,k;
    for(k=0; k<1;)
    {
        int n;
        printf("\tAdmin Panel :\n\n");
        printf("\t SETUP\t\t\t\t\t\t 15.logout\n\n");
        printf("\t\t  1. Add new user \n\n");
        printf("\t\t  2. Arrange new vote \n\n");
        printf("\t HISTORY:\n\n");
        printf("\t\t  #.Vote wise result :\n\n");

        FILE *file;

        file = fopen("vote's_name.txt","r");
        if(!file)
        {
            printf("\tUnable open file!\n\n");
        }
        i=0;
        while(fscanf(file, "%s", vmm[i]) == 1)
        {
            printf("\t\t\t%d.%s\n",i+3,vmm[i]);
            i++;
        }
        fclose(file);

        printf("\n\n\n\nEnter your choice: ");
        scanf("%d",&n);
        if(n == 15)
        {
            k=1;
            system("CLS");
        }
        else if(n == 1)
        {
            system("CLS");
            Add_new_user();
            k=0;
            continue;
        }
        else if(n == 2)
        {
            system("CLS");
            arrange_new_vote();
            k=0;
            continue;
        }
       // else if(n ==100)
        //{
          //  system("CLS");
            //delete_Vote();
            //k=0;
            //continue;
        //}


        n=n-3;
        if(!k && n<i)
        {
            system("CLS");
            result(n);
            k=0;

        }
        i=0;
    }
    Sleep(1000);
}


void Add_new_user()
{
    int urid;
    char q,pass[20];
    FILE *file;
    file = fopen("user_records.txt","a");
    if(!file)
        printf("couldn't open file\n\n");

    printf("New user's id: ");
    scanf("\n%c%d",&q,&urid);
    q = toupper(q);
    printf("Enter password for new user: ");
    scanf("%s",pass);

    fprintf(file, "%s\n", pass);
    fprintf(file, "%c%d\n",q,urid);

    fclose(file);
    system("CLS");

}


void arrange_new_vote()
{
    int i,n,a[5]= {0};
    char c[5][50],vt[50],fn[50]="";
    FILE *file , *file2;

    printf("Name of the Vote(use 'underscore' instead of 'space'): ");
    scanf("%s",vt);
    printf("Select Total Candidate (max 5): ");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("Name of candidate no %d:",i+1);
        scanf("%s",&c[i]);
    }

    strcat(fn,vt);
    strcat(fn,".txt");

    file = fopen("vote's_name.txt","a");
    if(!file)
    {
        printf("couldn't open file\n\n");
        return;
    }

    fprintf(file,"%s\n",vt);
    fclose(file);

    file2 = fopen(fn,"a");
    if(!file2)
    {
        printf("couldn't open file\n\n");
        return;
    }
    for(i=0; i<n; i++)
    {
        fprintf(file,"%s\n%d\n",c[i],a[i]);
    }
    fclose(file2);

    strcpy(fn,"");
    strcat(fn,vt);
    strcat(fn,"_voter-list.txt");

    file2 = fopen(fn,"a");
    if(!file2)
    {
        cout<<"file2 couldn't open";
    }

    Sleep(1000);
    system("CLS");
}

void result(int m)
{
    int i=0,id[6],k,l,tn;
    double pv[10],tv=0.0;
    char fn[50]="";
    char nm[5][50];
    FILE *file;

    printf("\t\t%s result:\n\n",vmm[m]);

    strcat(fn,vmm[m]);
    strcat(fn,".txt");

    file = fopen(fn,"r");
    if(!file)
    {
        printf("couldn't open file\n\n");
        return;
    }
    while(fscanf(file,"%s", nm[i]) == 1 )
    {
        fscanf(file, "%d",&id[i]);
        i++;

    }
    tn=i;
    fclose(file);
    i=0;
    while(i<tn)
    {
        tv=tv+id[i];
        i++;
    }
    i=0;
    while(i<tn)
    {
        pv[i]=((id[i]*100.0)/tv);
        i++;
    }
    i=0;
    while(i<tn)
    {
        printf("candidate: %s\n", nm[i]);
        printf("total vote: %d\n", id[i]);
        printf("percentage of total vote: %.2f\%\n\n", pv[i]);
        i++;

    }
    graph_ad_rslt(m);

    delay(3000);
    system("CLS");
}


void graph_ad_rslt(int n)
{
    int gd=DETECT,gm,id[50],i,tn;
    int x1,y1,x2,y2,tx,fx,fy;
    char nm[50][50],fn[50]="",t[60]="";
    FILE *file;

    strcat(fn,vmm[n]);
    strcat(fn,".txt");


    file = fopen(fn,"r");
    if(!file)
    {
        printf("couldn't open file\n\n");
        return;
    }
    i=0;
    while(fscanf(file,"%s", nm[i]) == 1 )
    {
        fscanf(file, "%d",&id[i]);
        i++;
    }
    tn=i;

    initgraph(&gd,&gm,"");

    setcolor(11);
    rectangle(150,90,450,90);
    setcolor(10);
    outtextxy(250,70,"Voting Result");

    setcolor(10);
    rectangle(500,305,50,300);
    setcolor(10);
    rectangle(57,100,50,300);
    settextstyle(BOLD_FONT,HORIZ_DIR,1);


    //1stbar
    x1=120;
    //y2=120;
    x2=100;
    y2=300;
    tx=100;
    fx=118;
    i=0;
    while(i<tn)
    {
        y1=300-(5*id[i]);
        fy=y1+5;
        setcolor(10);
        rectangle(x1,y1,x2,y2);
        floodfill(fx,fy,10);
        settextstyle(BOLD_FONT,VERT_DIR,1);
        setcolor(12);
        outtextxy(tx,400,nm[i]);

        x1+=50;
        x2+=50;
        tx+=50;
        fx+=50;
        i++;
    }


    setcolor(11);
    rectangle(40,35,600,450);
    rectangle(39,34,599,449);
    rectangle(38,33,598,448);
    Sleep(3000);
    closegraph();
}
