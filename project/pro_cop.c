//403110539

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>




char screen[5][30][120];

char save[5][30][120];

char trap[5][30][120];

int dagger[5][30][120];

int magic[5][30][120];

int arrow[5][30][120];

int weapon[5];

//int food[4];

int spell[3];

int health = 3000;
int max_health = 3000;
int hungry = 4000;
int max_hungry = 4000;
int gold = 0;
int score = 0;
int level = 1;
int key = 0;
int b_key = 0;
int food_power = 0;
int food_speed = 0;
int spell_health = 0;
int spell_power = 0;
int spell_speed = 0;
int color_hero = 2;
int now_weapon = 0;
int en_st = 0;
int mus = 0;

int kalam = 0;


typedef struct point{

    int X;
    int Y;

} point;

typedef struct room{
    point up_left;
    point difference;
    int floor;
} room;

typedef struct makan{
    int X;
    int Y;
    int Z;
    
} makan;

typedef struct match{
    makan door;
    makan pass_maker;
    makan pass_makertwo;
    char password[5];
    char passwordtwo[5];
    int open;
    int try;
} match;

typedef struct enemys{
    char type;
    int joon;
    makan place;
    int power;
    int movement;
    int sign;
}enemys;

typedef struct fod{
    int type;
    int time;
    int expiration;
}fod;

fod food[5];

enemys enemy[100];

int ene = 0;

makan adam;

int pdoor_pointer;

match door_pass[1000];

makan upstairs[4];

makan downstairs[4];

/////////////////////////////////////////////////////////////////////////
room *otagh[4];
room ganj;

int sec[4];
int kab[4];
int pas[4];
/////////////////////////////////////////////////////////////////////////

FILE *info;
char *acount_file,acount_user[1000] = {};
char gmail[1000],enter_pass[1000];
int total_score,game_played;
time_t now,signup_time;
char time_diff[1000];

Mix_Music *music[100];

int end = 0;
int sign = 0;
////////////////////////////////////////////////////////////////////////////

char *exprincee(time_t a){
    now = time(NULL);
    double diff = difftime(now,a);

    struct tm ex;
    ex.tm_sec = (int)diff % 60;
    ex.tm_min = ((int)diff / 60) % 60;
    ex.tm_hour = (int)diff / 3600;
    ex.tm_year = 0;
    ex.tm_mon = 0;
    ex.tm_mday = 0;
    ex.tm_wday = 0;
    ex.tm_yday = 0;
    ex.tm_isdst = 0;
    memset(time_diff,'\0',sizeof(time_diff));

    strftime(time_diff,sizeof(time_diff),"%H:%M:%S",&ex);
    return time_diff;

}

int frist_meno(){
    
    char x;
    clear();
    mvprintw(10,55,"1) signup");
    mvprintw(15,55,"2) signin");
    mvprintw(20,55,"3) geust");
    refresh();
    x = getchar();

    while(x != '1' &&  x != '2' && x !=  '3'){
        clear();
        mvprintw(10,55,"1) signup");
        mvprintw(15,55,"2) signin");
        mvprintw(20,55,"3) geust");
        mvprintw(5,55,"press correct button");
        refresh();
        x = getchar();
    }
    return x - 48;
}

int verfie_username(char *a){

    char p[10000];
    FILE *user;
    user = fopen("username.txt","r");
    while(fgets(p,10000,user) != NULL){
        p[strlen(p) - 1] = '\0';
        if(strcmp(a,p) == 0 ){
            fclose(user);
            return 0;
        }
    }
    fclose(user);
    return 1;

}


int verfie_gmail(char *a){
    
    int g = 0,h = 0;
    int i = 1;
    char p[10000];

    

    for( i = 1;i < strlen(a);i++){
        if(a[i] == '@'){
            g = 1;
            break;
        }
    }

    for(int j = i + 2 ; j < strlen(a) - 1;j++){
        if(a[j] == '.'){
            h = 1;
            break;
        }
    }


    if(g == 1 && h == 1){
        return 1 ;  
    }
    
    return 0 ;

}


int verfie_pass(char *a){
    int small = 0,big = 0,number = 0;
    if(strlen(a) < 7){
        return 0 ;
    }

    for(int i = 0;i < strlen(a);i++){
        if(a[i] <= 122 && a[i] >= 97){
            small = 1;
        }
        else if(a[i] >= 65 && a[i] <= 90){
            big = 1;
        }
        else if(a[i] >= 48 && a[i] <= 57){
            number = 1;
        }
    }
    if(small == 1 && big == 1 && number == 1){
        return 1;
    }
    return 0;
}

char *signup(char *c){

    char b[1000],a[1000],d[1000],l;
    signup_time = time(NULL);
    clear();
    mvprintw(9,10,"enter your username : ");
    scanw("%s",c);
    while(verfie_username(c) == 0){
    clear();
    memset(c,'\0',sizeof(c));
    mvprintw(12,15,"username had been taken! please enter new username");
    mvprintw(9,10,"enter your username : ");
    refresh();
    scanw("%s",c);
    }

    clear();
    mvprintw(9,10,"enter your username : %s",c);
    mvprintw(10 , 10 , "enter your email : ");
    refresh();
    scanw("%s",a);
    while(verfie_gmail(a) == 0){
    clear();
    memset(a,'\0',sizeof(a));
    mvprintw(12,15,"invalid email.please try again");
    mvprintw(9,10,"enter your username : %s",c);
    mvprintw(10 , 10 , "enter your email : ");
    refresh();
    scanw("%s",a);
    }

    clear();
    mvprintw(9,10,"enter your username : %s",c);
    mvprintw(10 , 10 , "enter yor email : %s",a);
    mvprintw(5,15,"if you want use random password press 'R' else press another botton");
    refresh();
    l = getchar();

    if(l == 'R'){
        b[0] = rand() %26 + 97;
        b[1] = rand() %26 + 97;
        b[2] = rand() %10 + 48;
        b[3] = rand() %10 + 48;
        b[4] = rand() %10 + 48;
        b[5] = rand() %26 + 65;
        b[6] = rand() %26 + 65;
        b[7] = '\0';
        clear();
        mvprintw(9,10,"enter your username : %s",c);
        mvprintw(10 , 10 , "enter yor email : %s",a);
        mvprintw(11,10,"your password : %s",b);
        refresh();
        getchar();

    }
    else{
        clear();
        mvprintw(9,10,"enter your username : %s",c);
        mvprintw(10 , 10 , "enter yor email : %s",a);
        mvprintw(11,10,"enter your password : ");
        refresh();
        scanw("%s",b);

        while(verfie_pass(b) == 0){
            clear();
            memset(b,'\0',sizeof(b));
            mvprintw(12,15,"invalid password.please try again");
            mvprintw(9,10,"enter your username : %s",c);
            mvprintw(10 , 10 , "enter yor email : %s",a);
            mvprintw(11,10,"enter your password : ");
            refresh();
            scanw("%s",b);
        }
    }

    
    
    FILE *user;
    FILE *file;
    
    user = fopen("username.txt","a");
    fprintf(user,"%s",c);
    fprintf(user,"\n");
    fclose(user);
    strcat(c,".txt");
    file = fopen (c,"w");
    fprintf(file , "%s",a);
    fprintf(file , "\n");
    fprintf(file , "%s",b);
    fprintf(file , "\n");
    fprintf(file ,"%d",0);
    fprintf(file , "\n");
    fprintf(file ,"%d",0);
    fprintf(file , "\n");
    fprintf(file ,"%ld",signup_time);
    fprintf(file , "\n");
    fprintf(file ,"%d",0);
    fprintf(file , "\n");
    fclose(file);
    return c;

}



int finduser(char *a){
    FILE *user;
    
    char p[10000];
    user = fopen("username.txt","r");
    while(fgets(p,10000,user) != NULL){
        p[strlen(p) - 1] = '\0';
        if(strcmp(a,p) == 0 ){
            return 1;
        }

    }
    return 0;

}


char *signin(char *a){

    char b[1000],q[1000],p[1000],c[1000],l;
    FILE *pass;
    clear();
    
    mvprintw(10 , 10 , "enter yor username : ");
    refresh();
    scanw("%s",c);
    
        

    while(finduser(c) == 0){
        
        memset(c,'\0',sizeof(c));
        clear();
        
        mvprintw(12,15,"wrong username");
        mvprintw(10 , 10 ,"enter yor usename : ");
        refresh();
        scanw("%s",c);

    }

    
    strcpy(a,c);
    strcat(a,".txt");
    pass = fopen(a,"r");
    fgets(p,1000,pass);
    fgets(q,1000,pass);
    q[strlen(q) - 1] = '\0';
    fclose(pass);

    mvprintw(11,10,"if you have forgotten your password press 'F' else press another botten");
    refresh();
    l = getchar();
    if(l == 'F'){
        mvprintw(5,15,"your password : %s",q);
    }

    mvprintw(11,10,"                                                                            ");
    mvprintw(11,10,"enter your password : ");
    refresh();
    scanw("%s",b);
    
    while(strcmp(b,q) != 0){
        memset(b,'\0',sizeof(b));
        clear();
        mvprintw(12,10,"wrong password");
        mvprintw(10 , 10 , "enter yor usename : %s",c);
        mvprintw(11,10,"enter your password : ");
        refresh();
        scanw("%s",b);
    }

    return a;
        

    


}

void scoreboard(char *k){
    FILE *user;
    FILE *file;
    char a[100][100],b[1000],c[1000],d[1000],kkll = 'P';
    int x[1000],y[1000],w[1000],dd;
    time_t z[1000];
    int i = 0  ;
    user = fopen("username.txt","r");
    while(fgets(a[i] , 100,user) != NULL){
        a[i][strlen(a[i]) - 1] = '\0';
        strcpy(d,a[i]);
        strcat(d,".txt");
        file = fopen(d,"r");
        fscanf(file,"%s",b);
        fscanf(file,"%s",c);
        fscanf(file,"%d",&x[i]);
        fscanf(file,"%d",&y[i]);
        fscanf(file,"%ld",&z[i]);
        fclose(file);
        memset(d,'\0',sizeof(d));
        i++;

    }

    for(int j = 0 ; j < i;j++){
        for(int h = 0 ; h < i;h++){
            if(x[j] < x[h]){
                dd++;
            }
        }
        for(int g = 0 ; g < j ; g++){
            if(x[j] == x[g]){
                dd++;
            }
        }
        w[dd] = j;
        dd = 0;

    }
    
    clear();
    mvprintw(3,10,"username");
    mvprintw(3,30,"score");
    mvprintw(3,40,"played");
    mvprintw(3,50,"exprince");
    for(int j = 0;j < i && j < 25;j++){
        if(j == 0){
            mvprintw(5,80,"\U0001F947");
            attron(COLOR_PAIR(10) | A_BOLD);
            mvprintw(5,55,"          The goat");
        }
        if(j == 1){
            mvprintw(6,80,"\U0001F948");
            attron(COLOR_PAIR(9) | A_BOLD);
            mvprintw(6,55,"          Legend");
        }
        if(j == 2){
            mvprintw(7,80,"\U0001F949");
            attron(COLOR_PAIR(8) | A_BOLD);
            mvprintw(7,55,"          Master");
        }
        if(strcmp(k,a[w[j]]) == 0){
            attron(COLOR_PAIR(11) | A_BOLD);
        }

        mvprintw(j + 5,5,"%d    ",j + 1);
        mvprintw(j + 5,10,"%s                   ",a[w[j]]);
        mvprintw(j + 5 , 30 ,"%d         ",x[w[j]]);
        mvprintw(j+ 5,40,"%d         ",y[w[j]]);
        mvprintw(j + 5 , 50,"%s",exprincee(z[w[j]]));

        if(j == 0){
            attroff(COLOR_PAIR(10) | A_BOLD);
        }
        if(j == 1){
            attroff(COLOR_PAIR(9) | A_BOLD);
        }
        if(j == 2){
            attroff(COLOR_PAIR(8) | A_BOLD);
        }
        if(strcmp(k,a[w[j]]) == 0){
            attroff(COLOR_PAIR(11) | A_BOLD);
        }
    }
    mvprintw(30,50,"press 'E' to exsit");
    mvprintw(29,50,"press '>' for next page");
    refresh();
    kkll = getchar();

    while(kkll != 'E'){
        if(kkll == '<'){
            clear();
            mvprintw(3,10,"username");
            mvprintw(3,30,"score");
            mvprintw(3,40,"played");
            mvprintw(3,50,"exprince");
            for(int j = 0;j < i && j < 25;j++){
                if(j == 0){
                    mvprintw(5,80,"\U0001F947");
                    attron(COLOR_PAIR(10) | A_BOLD);
                    mvprintw(5,55,"          The goat");
                }
                if(j == 1){
                    mvprintw(6,80,"\U0001F948");
                    attron(COLOR_PAIR(9) | A_BOLD);
                    mvprintw(6,55,"          Legend");
                }
                if(j == 2){
                    mvprintw(7,80,"\U0001F949");
                    attron(COLOR_PAIR(8) | A_BOLD);
                    mvprintw(7,55,"          Master");
                }
                if(strcmp(k,a[w[j]]) == 0){
                    attron(COLOR_PAIR(11) | A_BOLD);
                }

                mvprintw(j + 5,5,"%d    ",j + 1);
                mvprintw(j + 5,10,"%s                  ",a[w[j]]);
                mvprintw(j + 5 , 30 ,"%d         ",x[w[j]]);
                mvprintw(j+ 5,40,"%d         ",y[w[j]]);
                mvprintw(j + 5 ,50,"%s",exprincee(z[w[j]]));

                if(j == 0){
                    attroff(COLOR_PAIR(10) | A_BOLD);
                }
                if(j == 1){
                    attroff(COLOR_PAIR(9) | A_BOLD);
                }
                if(j == 2){
                    attroff(COLOR_PAIR(8) | A_BOLD);
                }
                if(strcmp(k,a[w[j]]) == 0){
                    attroff(COLOR_PAIR(11) | A_BOLD);
                }
            }
            mvprintw(30,50,"press 'E' to exsit");
            mvprintw(29,50,"press '>' for next page");
            refresh();
        }
        else if(kkll == '>'){
            clear();
            mvprintw(3,10,"username");
            mvprintw(3,30,"score");
            mvprintw(3,40,"played");
            mvprintw(3,50,"exprince");
            for(int j = 25;j < i && j < 50;j++){
                
                if(strcmp(k,a[w[j]]) == 0){
                    attron(COLOR_PAIR(11) | A_BOLD);
                }

                mvprintw(j + 5 - 25,5,"%d",j + 1);
                mvprintw(j + 5 - 25,10,"%s",a[w[j]]);
                mvprintw(j + 5 - 25, 30 ,"%d",x[w[j]]);
                mvprintw(j + 5 - 25,40,"%d",y[w[j]]);
                mvprintw(j + 5 - 25, 50,"%s",exprincee(z[w[j]]));

                
                if(strcmp(k,a[w[j]]) == 0){
                    attroff(COLOR_PAIR(11) | A_BOLD);
                }
            }
            mvprintw(30,50,"press 'E' to exsit");
            mvprintw(29,50,"press '<' for next page");
            refresh();
            
        }
       
        kkll = getchar();

    }


}


void sakhti(){
    
    char a = 'P';
    int b =  0,c =  0;
    
    clear();
    mvprintw(3,20,"down = press 'D'"); 
    mvprintw(4,20,"up = press 'U'" );
    mvprintw(5,20,"select = press 'S'");
    mvprintw(10,15,"Easy");
    attron(COLOR_PAIR(8) | A_BOLD);
    mvprintw(15,15,"Medium");
    attroff(COLOR_PAIR(8) |  A_BOLD);
    mvprintw(20,15,"Hard");
    //keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    refresh();
    while(a != 'S'){
        a = getchar();
        switch(a){
            case 'U':
                b++;
                break;
            case 'D':
                b--;
                break;
        }
        c = b %3;
        if(c < 0){
            c = c + 3;
        }
        switch(c){
            case 0:
                clear();
                mvprintw(3,20,"down = press 'D'"); 
                mvprintw(4,20,"up = press 'U'" );
                mvprintw(5,20,"select = press 'S'");
                mvprintw(10,15,"Easy");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(15,15,"Medium");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(20,15,"Hard");
                refresh();
                break;

            case 1:

                clear();
                mvprintw(3,20,"down = press 'D'"); 
                mvprintw(4,20,"up = press 'U'" );
                mvprintw(5,20,"select = press 'S'");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(10,15,"Easy");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(15,15,"Medium");
                mvprintw(20,15,"Hard");
                refresh();
                break;
            case 2:
                clear();
                mvprintw(3,20,"down = press 'D'"); 
                mvprintw(4,20,"up = press 'U'" );
                mvprintw(5,20,"select = press 'S'");
                mvprintw(10,15,"Easy");
                mvprintw(15,15,"Medium");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(20,15,"Hard");
                attroff(COLOR_PAIR(8) | A_BOLD);
                refresh();
                break;

        }
    }

    switch(c){
        case 1:
            health = 4000;
            max_health = 4000;
            hungry = 5000;
            max_hungry = 5000;
        case 2:
        health = 2000;
        max_health = 2000;
        hungry = 3000;
        max_hungry = 3000;
    }
    
}


int hero_color(){

    char a = 'P';
    int b = 0 ,c = 0;


    clear();
    mvprintw(5,22,"select hero color");
    mvprintw(10,30,"down = press 'D'"); 
    mvprintw(11,30,"up = press 'U'" );
    mvprintw(12,30,"select = press 'S'");
    attron(COLOR_PAIR(8) | A_BOLD);
    mvprintw(10,15,"red");
    attroff(COLOR_PAIR(8) | A_BOLD);
    mvprintw(15,15,"blue");
    mvprintw(20,15,"green");
    mvprintw(25,15,"yellow");
    noecho();
    curs_set(0);
    refresh();
    while(a != 'S'){
        a = getchar();
        switch(a){
            case 'U':
                b--;
                break;
            case 'D':
                b++;
                break;
        }

        c = b %4;
        if(c < 0){
            c = c + 4;
        }

        switch(c){
            case 0:
                clear();
                mvprintw(5,22,"select hero color");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(10,15,"red");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(15,15,"blue");
                mvprintw(20,15,"green");
                mvprintw(25,15,"yellow");
                refresh();
                break;

            case 1:
                clear();
                mvprintw(5,22,"select hero color");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"red");
                attron(COLOR_PAIR(7) | A_BOLD);
                mvprintw(15,15,"blue");
                attroff(COLOR_PAIR(7) | A_BOLD);
                mvprintw(20,15,"green");
                mvprintw(25,15,"yellow");
                refresh();
                break;
            case 2:
                clear();
                mvprintw(5,22,"select hero color");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"red");
                mvprintw(15,15,"blue");
                attron(COLOR_PAIR(9) | A_BOLD);
                mvprintw(20,15,"green");
                attroff(COLOR_PAIR(9) | A_BOLD);
                mvprintw(25,15,"yellow");
                refresh();
                break;
            case 3:
                clear();
                mvprintw(5,22,"select hero color");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"red");
                mvprintw(15,15,"blue");
                mvprintw(20,15,"green");
                attron(COLOR_PAIR(10) | A_BOLD);
                mvprintw(25,15,"yellow");
                attroff(COLOR_PAIR(10) | A_BOLD);
                refresh();
                break;

        }

    }

    echo();
    curs_set(1);

    return c;


}

int choose_music(){
    clear();

    char a = 'P';
    int b = 0,c = 0;
    mvprintw(5,22,"select music");
    mvprintw(10,30,"down = press 'D'"); 
    mvprintw(11,30,"up = press 'U'" );
    mvprintw(12,30,"select = press 'S'");
    attron(COLOR_PAIR(7));
    mvprintw(10,15,"mute");
    attroff(COLOR_PAIR(7));
    mvprintw(15,15,"still DRE");
    mvprintw(20,15,"mohre mar :)");
    mvprintw(25,15,"music");
    noecho();
    curs_set(0);
    refresh();
    while(a != 'S'){
        a = getchar();
        switch(a){
            case 'U':
                b--;
                break;
            case 'D':
                b++;
                break;
        }

        c = b %4;
        if(c < 0){
            c = c + 4;
        }

        switch(c){
            case 0:
                clear();
                mvprintw(5,22,"select music");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                attron(COLOR_PAIR(7));
                mvprintw(10,15,"mute");
                attroff(COLOR_PAIR(7));
                mvprintw(15,15,"still DRE");
                mvprintw(20,15,"mohre mar :)");
                mvprintw(25,15,"music");
                refresh();
                break;

            case 1:
                clear();
                mvprintw(5,22,"select music");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"mute");
                attron(COLOR_PAIR(7));
                mvprintw(15,15,"still DRE");
                attroff(COLOR_PAIR(7));
                mvprintw(20,15,"mohre mar :)");
                mvprintw(25,15,"music");
                refresh();
                break;
            case 2:
                clear();
                mvprintw(5,22,"select music");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"mute");
                mvprintw(15,15,"still DRE");
                attron(COLOR_PAIR(7));
                mvprintw(20,15,"mohre mar :)");
                attroff(COLOR_PAIR(7));
                mvprintw(25,15,"music");
                refresh();
                break;
            case 3:
                clear();
                mvprintw(5,22,"select music");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'" );
                mvprintw(12,30,"select = press 'S'");
                mvprintw(10,15,"mute");
                mvprintw(15,15,"still DRE");
                mvprintw(20,15,"mohre mar :)");
                attron(COLOR_PAIR(7));
                mvprintw(25,15,"music");
                attroff(COLOR_PAIR(7));
                refresh();
                break;

        }

    }

    echo();
    curs_set(1);

    return c;


}

void setting_meno(){
    char x;
    clear();
    mvprintw(14,55,"1) sakhti");
    mvprintw(15,55,"2) hero_color");
    mvprintw(16,55,"3) music");
    refresh();
    x = getchar();

    while(x != '1' && x != '2'&& x != '3'){
        clear();
        mvprintw(14,55,"1) sakhti");
        mvprintw(15,55,"2) hero_color");
        mvprintw(16,55,"3) music");
        mvprintw(5,55,"press correct button");
        refresh();
        x = getchar();
    }

    if(x  == '1'){
        sakhti();
    }
    else if(x == '2'){
        color_hero = hero_color();
    }
    else{
        mus = choose_music();
    }
    
}


int meno(){

    char a = 'P';
    int b = 0 , c = 0 ;
    
    clear();
    attron(COLOR_PAIR(8) | A_BOLD);
    mvprintw(5,15,"New game");
    attroff(COLOR_PAIR(8) | A_BOLD);
    mvprintw(10,15,"Resume game");
    mvprintw(15,15,"Scoreboard");
    mvprintw(20,15,"Setting");
    mvprintw(25,15,"Profile");
    mvprintw(10,30,"down = press 'D'"); 
    mvprintw(11,30,"up = press 'U'");
    mvprintw(12,30,"select = press 'S'");
    noecho();
    curs_set(0);
    refresh();

    while(a != 'S'){
        a = getchar();
        switch(a){
            case 'U':
                b--;
                break;
            case 'D':
                b++;
                break;
        }

        c = b %5;
        if (c < 0){
            c = c + 5;
        }

        switch(c){
            case 0:
                clear();
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(5,15,"New game");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(10,15,"Resume game");
                mvprintw(15,15,"Scoreboard");
                mvprintw(20,15,"Setting");
                mvprintw(25,15,"Profile");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'");
                mvprintw(12,30,"select = press 'S'");
                refresh();
                break;

            case 1:
                clear();
                mvprintw(5,15,"New game");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(10,15,"Resume game");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(15,15,"Scoreboard");
                mvprintw(20,15,"Setting");
                mvprintw(25,15,"Profile");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'");
                mvprintw(12,30,"select = press 'S'");
                refresh();
                break;

            case 2:
                clear();
                mvprintw(5,15,"New game");
                mvprintw(10,15,"Resume game");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(15,15,"Scoreboard");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(20,15,"Setting");
                mvprintw(25,15,"Profile");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'");
                mvprintw(12,30,"select = press 'S'");
                refresh();
                break;

            case 3:
                clear();
                mvprintw(5,15,"New game");
                mvprintw(10,15,"Resume game");
                mvprintw(15,15,"Scoreboard");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(20,15,"Setting");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(25,15,"Profile");
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'");
                mvprintw(12,30,"select = press 'S'");
                refresh();
                break;

            case 4:
                clear();
                mvprintw(5,15,"New game");
                mvprintw(10,15,"Resume game");
                mvprintw(15,15,"Scoreboard");
                mvprintw(20,15,"Setting");
                attron(COLOR_PAIR(8) | A_BOLD);
                mvprintw(25,15,"Profile");
                attroff(COLOR_PAIR(8) | A_BOLD);
                mvprintw(10,30,"down = press 'D'"); 
                mvprintw(11,30,"up = press 'U'");
                mvprintw(12,30,"select = press 'S'");
                refresh();
                break;

        }


    }

    echo();
    curs_set(1);
    
    return c;

}

int in_kab(makan ja){

    for(int i = 0 ; i < 4;i++){
        if(ja.Z == otagh[i][kab[i]].floor){
            if(ja.Y <= otagh[i][kab[i]].up_left.Y + otagh[i][kab[i]].difference.Y - 1 && 
            ja.Y >= otagh[i][kab[i]].up_left.Y - 1){
                if(ja.X <= otagh[i][kab[i]].up_left.X + otagh[i][kab[i]].difference.X && 
                ja.X >= otagh[i][kab[i]].up_left.X){
                    return i;
                }
            }
        }
    }
    return -1;
}

void chap(int z,int y,int x,char b[5][30][120]){
    char a;
    a = b[z][y][x];
    if(a == ' '){
        mvprintw(y,x,"%c",a);
    }
    else if(dagger[z][y][x] > 0){
        mvprintw(y,x,"2");
    }
    else if(magic[z][y][x] > 0){
        mvprintw(y,x,"3");
    }
    else if(arrow[z][y][x] > 0){
        mvprintw(y,x,"4");
    }
    else{
        switch(a){
            case '0':
                
                attron(COLOR_PAIR(4));
                mvprintw(y,x,"0");
                attroff(COLOR_PAIR(4));
                break;
            case '@':
                int w;
                for(int i = 0 ; i < pdoor_pointer;i++){
                    if(door_pass[i].door.Z == z && door_pass[i].door.Y == y && door_pass[i].door.X == x){
                        w = i;
                    }
                }

                if(door_pass[w].open == 0){
                    
                    attron(COLOR_PAIR(8));
                    mvprintw(y,x,"@");
                    attroff(COLOR_PAIR(8));

                }
                if(door_pass[w].open == 1){
                    
                    attron(COLOR_PAIR(9));
                    mvprintw(y,x,"@");
                    attroff(COLOR_PAIR(9));

                }
                break;
            case '&':
                
                attron(COLOR_PAIR(5));
                mvprintw(y,x,"&");
                attroff(COLOR_PAIR(5));
                break;
            case '$':

                attron(COLOR_PAIR(5));
                mvprintw(y,x,"$");
                attroff(COLOR_PAIR(5));
                break;
            case 'b':
                
                attron(COLOR_PAIR(2));
                mvprintw(y,x,"b");
                attroff(COLOR_PAIR(2));
                break;
            case 'f':
                
                attron(COLOR_PAIR(4));
                mvprintw(y,x,"f");
                attroff(COLOR_PAIR(4));
                break;
            case 'q':
                attron(COLOR_PAIR(1));
                mvprintw(y,x,"q");
                attroff(COLOR_PAIR(1));
                break;
            case 'a':
                attron(COLOR_PAIR(1));
                mvprintw(y,x,"a");
                attroff(COLOR_PAIR(1));
                break;
            case 'p':
                attron(COLOR_PAIR(1));
                mvprintw(y,x,"p");
                attroff(COLOR_PAIR(1));
                break;
            case '6':
                attron(COLOR_PAIR(3));
                mvprintw(y,x,"6");
                attroff(COLOR_PAIR(3));
                break;
            case '7':
                attron(COLOR_PAIR(3));
                mvprintw(y,x,"7");
                attroff(COLOR_PAIR(3));
                break;
            case '8':
                attron(COLOR_PAIR(3));
                mvprintw(y,x,"8");
                attroff(COLOR_PAIR(3));
                break;
            default:
                if(z == 4){
                    attron(COLOR_PAIR(5));
                }

                for(int i = 0 ; i < 4;i++){
                    if(z == otagh[i][kab[i]].floor){
                        if(y <= otagh[i][kab[i]].up_left.Y + otagh[i][kab[i]].difference.Y - 1 && 
                        y >= otagh[i][kab[i]].up_left.Y - 1){
                            if(x <= otagh[i][kab[i]].up_left.X + otagh[i][kab[i]].difference.X && 
                            x >= otagh[i][kab[i]].up_left.X){
                                attron(COLOR_PAIR(2));
                            }
                        }
                    }
                }
                
                for(int i = 0 ; i < 4;i++){
                    if(z == otagh[i][sec[i]].floor){
                        if(y <= otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                        y >= otagh[i][sec[i]].up_left.Y - 1){
                            if(x <= otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                            x >= otagh[i][sec[i]].up_left.X){
                                attron(COLOR_PAIR(6));
                            }
                        }
                    }
                }


                mvprintw(y,x,"%c",b[z][y][x]);

                for(int i = 0 ; i < 4;i++){
                    if(z == otagh[i][sec[i]].floor){
                        if(y <= otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                        y >= otagh[i][sec[i]].up_left.Y - 1){
                            if(x <= otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                            x >= otagh[i][sec[i]].up_left.X){
                                attroff(COLOR_PAIR(6));
                            }
                        }
                    }
                }

                for(int i = 0 ; i < 4;i++){
                    if(z == otagh[i][kab[i]].floor){
                        if(y <= otagh[i][kab[i]].up_left.Y + otagh[i][kab[i]].difference.Y - 1 && 
                        y >= otagh[i][kab[i]].up_left.Y - 1){
                            if(x <= otagh[i][kab[i]].up_left.X + otagh[i][kab[i]].difference.X && 
                            x >= otagh[i][kab[i]].up_left.X){
                                attroff(COLOR_PAIR(2));
                            }
                        }
                    }
                }

                if(z == 4){
                    attroff(COLOR_PAIR(5));
                }
                break;
            
            
        }
    }
    
}

void chap_hero(makan ja,int a){

    switch(a){
        case 0:
            attron(COLOR_PAIR(2));
            mvprintw(ja.Y,ja.X,"M");
            attroff(COLOR_PAIR(2));
            break;
        case 1:
            attron(COLOR_PAIR(1));
            mvprintw(ja.Y,ja.X,"M");
            attroff(COLOR_PAIR(1));
            break;
        case 2:
            attron(COLOR_PAIR(3));
            mvprintw(ja.Y,ja.X,"M");
            attroff(COLOR_PAIR(3));
            break;
        case 3:
            attron(COLOR_PAIR(4));
            mvprintw(ja.Y,ja.X,"M");
            attroff(COLOR_PAIR(4));
            break;

    }

}

room *make_room(room *c,int a){

    clear();

    for(int i = 0 ; i < 6;i++){
        int j =  i%3;
        int h =  i /3;
        c[i].up_left.X = (rand() %4) + j*40 + 2;
        c[i].up_left.Y = (rand() %4) + h*15 + 3;
    }

    for(int i = 0 ; i < 6;i++){
        c[i].difference.X = (rand()%6) + 10;
        c[i].difference.Y = (rand()%3) + 5;
        c[i].floor = a;
    }


    for(int i = 0 ;i < 6;i++){
        for(int j = 0 ;j <= c[i].difference.X;j++){
            screen[a][c[i].up_left.Y - 1][c[i].up_left.X + j] = '_';
            screen[a][c[i].up_left.Y + c[i].difference.Y - 1][c[i].up_left.X + j] = '_';
            mvprintw( c[i].up_left.Y - 1,c[i].up_left.X + j,"_");
            mvprintw(c[i].up_left.Y + c[i].difference.Y - 1,c[i].up_left.X + j,"_");
        }
    }

    for(int i = 0;i < 6;i++){
        for(int j = 0  ;j < c[i].difference.Y;j++){
            screen[a][c[i].up_left.Y + j][c[i].up_left.X] = '|';
            screen[a][c[i].up_left.Y + j][c[i].up_left.X + c[i].difference.X] = '|';
            mvprintw( c[i].up_left.Y + j, c[i].up_left.X,"|");
            mvprintw( c[i].up_left.Y + j, c[i].up_left.X + c[i].difference.X,"|");
        }
    }

    return c;
}


point make_door(room a,point b){

    int x,z;
    
    z = rand() %4;
    
    switch(z){
        case 0:
            x = rand() % (a.difference.X - 1);
            b.X = a.up_left.X + 1 + x;
            b.Y = a.up_left.Y - 2;
            screen[a.floor][a.up_left.Y - 2][a.up_left.X + 1 + x] = '#';
            mvprintw(a.up_left.Y - 2,a.up_left.X + 1 + x,"#");
            screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] = '+';
            mvprintw( a.up_left.Y - 1, a.up_left.X + 1 + x ,"+");
            break;
        case 1:
            x = rand() % (a.difference.X - 1);
            b.X =  a.up_left.X + 1 + x ;
            b.Y = a.up_left.Y + a.difference.Y  ;
            screen[a.floor][a.up_left.Y + a.difference.Y][a.up_left.X + 1 + x] = '#';
            mvprintw(a.up_left.Y + a.difference.Y,a.up_left.X + 1 + x,"#");
            screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] = '+';
            mvprintw( a.up_left.Y + a.difference.Y - 1, a.up_left.X + 1 + x ,"+");
            break;
        case 2:
            x = rand() % (a.difference.Y - 1);
            b.X = a.up_left.X - 1;
            b.Y = a.up_left.Y + x ;
            screen[a.floor][a.up_left.Y + x][a.up_left.X - 1] = '#';
            mvprintw(a.up_left.Y + x,a.up_left.X - 1,"#");
            screen[a.floor][a.up_left.Y + x][a.up_left.X] = '+';
            mvprintw( a.up_left.Y + x , a.up_left.X ,"+");
            break;
        case 3:
            x = rand() % (a.difference.Y - 1);
            b.X = a.up_left.X + a.difference.X + 1;
            b.Y = a.up_left.Y + x;
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X + 1] = '#';
            mvprintw(a.up_left.Y + x,a.up_left.X + a.difference.X + 1,"#");
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] = '+';
            mvprintw( a.up_left.Y + x , a.up_left.X + a.difference.X ,"+");
            break;
    }


    return b;
}


void make_floor(room *a){

    for(int i = 0; i < 6;i++){
        for(int j = a[i].up_left.X + 1 ;j < a[i].difference.X + a[i].up_left.X ;j++){
            for(int h = a[i].up_left.Y ;h < a[i].difference.Y + a[i].up_left.Y - 1;h++){
                screen[a[i].floor][h][j] = '.';
                mvprintw(h,j,".");
            }
        }
    }

}

void make_winddow(room *a){

    for(int i = 0;i < 6;i++){

        int x,z;

        z = (rand() + i + 1) %4;
        switch(z){
            case 0:
                x = rand() % (a[i].difference.X - 1);
                while(screen[a[i].floor][a[i].up_left.Y - 1][a[i].up_left.X + 1 + x] == '+'){
                    x = rand() % (a[i].difference.X - 1);
                }
                screen[a[i].floor][a[i].up_left.Y - 1][a[i].up_left.X + 1 + x] = '=';
                mvprintw(a[i].up_left.Y - 1,a[i].up_left.X + 1 + x,"=");
                break;
            case 1:
                x = rand() % (a[i].difference.X - 1);
                while(screen[a[i].floor][a[i].up_left.Y + a[i].difference.Y - 1][a[i].up_left.X + 1 + x] == '+'){
                    x = rand() % (a[i].difference.X - 1);
                }
                screen[a[i].floor][a[i].up_left.Y + a[i].difference.Y - 1][a[i].up_left.X + 1 + x] = '=';
                mvprintw(a[i].up_left.Y + a[i].difference.Y - 1,a[i].up_left.X + 1 + x,"=");
                break;
            case 2:
                x = rand() % (a[i].difference.Y - 1);
                while(screen[a[i].floor][a[i].up_left.Y + x][a[i].up_left.X] == '+'){
                    x = rand () % (a[i].difference.Y - 1);
                }
                screen[a[i].floor][a[i].up_left.Y + x][a[i].up_left.X] = '=';
                mvprintw(a[i].up_left.Y + x,a[i].up_left.X,"=");
                break;
            case 3:
                x = rand() % (a[i].difference.Y - 1);
                while(screen[a[i].floor][a[i].up_left.Y + x][a[i].up_left.X + a[i].difference.X] == '+'){
                    x = rand() % (a[i].difference.Y - 1);
                }
                screen[a[i].floor][a[i].up_left.Y + x][a[i].up_left.X + a[i].difference.X] = '=';
                mvprintw(a[i].up_left.Y + x,a[i].up_left.X + a[i].difference.X,"=");

                break;
        }

    }
    
}

void rah(point a,point b,int c){
    int x = a.X;
    int y = a.Y;
    int z = 0;
    int w = 0;

    while(x != b.X || y != b.Y){
        z = rand() % 2;
        if(y < b.Y){

            if(x < b.X){

                if(z == 1){
                    if(screen[c][y][x + 1] == ' ' || screen[c][y][x + 1] == '#'){
                        x++;
                        screen[c][y][x] = '#';

                    }
                    else{
                        y++;
                        screen[c][y][x] = '#';

                    }
                }
                else{
                    if(screen[c][y + 1][x] == ' ' || screen[c][y + 1][x] == '#'){
                        y++;
                        screen[c][y][x] = '#';

                    }
                    else{
                        x++;
                        screen[c][y][x] = '#';

                    }
                }


            }
            else if(x > b.X){

                if(z == 1){
                    if(screen[c][y][x - 1] == ' ' || screen[c][y][x - 1] == '#'){
                        x--;
                        screen[c][y][x] = '#';

                    }
                    else{
                        y++;
                        screen[c][y][x] = '#';

                    }
                }
                else{
                    if(screen[c][y + 1][x] == ' ' || screen[c][y + 1][x] == '#'){
                        y++;
                        screen[c][y][x] = '#';

                    }
                    else{
                        x--;
                        screen[c][y][x] = '#';

                    }
                }

            }
            else if(x == b.X){
                if(screen[c][y + 1][x] == ' ' || screen[c][y + 1][x] == '#'){
                    y++;
                    screen[c][y][x] = '#';
                }
                else{

                    w = 15;

                    while((screen[c][y][x + w] != ' ' && screen[c][y][x + w] != '#') || x + w >= 119){
                        w--;
                    }

                    for(int j = 0 ;j < w;j++){
                        x++;
                        screen[c][y][x] = '#';
                    }

                }
            }

        }
        else if(y > b.Y){

            if(x < b.X){

                if(z == 1){
                    if(screen[c][y][x + 1] == ' ' || screen[c][y][x + 1] == '#'){
                        x++;
                        screen[c][y][x] = '#';

                    }
                    else{
                        y--;
                        screen[c][y][x] = '#';

                    }
                }
                else{
                    if(screen[c][y - 1][x] == ' ' || screen[c][y - 1][x] == '#'){
                        y--;
                        screen[c][y][x] = '#';

                    }
                    else{
                        x++;
                        screen[c][y][x] = '#';

                    }
                }

            }
            else if(x > b.X){

                if(z == 1){
                    if(screen[c][y][x - 1] == ' ' || screen[c][y][x - 1] == '#'){
                        x--;
                        screen[c][y][x] = '#';

                    }
                    else{
                        y--;
                        screen[c][y][x] = '#';

                    }
                }
                else{
                    if(screen[c][y - 1][x] == ' ' || screen[c][y - 1][x] == '#'){
                        y--;
                        screen[c][y][x] = '#';

                    }
                    else{
                        x--;
                        screen[c][y][x] = '#';

                    }
                }

            }
            else if(x == b.X){
                if((screen[c][y - 1][x] == ' ' || screen[c][y - 1][x] == '#') || x + w >= 119){
                    y--;
                    screen[c][y][x] = '#';
                }
                else{
                    w = 15;

                    while(screen[c][y][x + w] != ' ' && screen[c][y][x + w] != '#'){
                        w--;
                    }

                    for(int j = 0 ;j < w;j++){
                        x++;
                        screen[c][y][x] = '#';
                    }
                }

            }

        }
        else if(y == b.Y){

            if(x < b.X){
                if(screen[c][y][x + 1] == ' ' || screen[c][y][x + 1] == '#'){
                    x++;
                    screen[c][y][x] = '#';
                }
                else{
                    w = 8;

                    while((screen[c][y + w][x] != ' ' && screen[c][y + w][x] != '#') || y + w >= 29){
                        w--;
                    }

                    for(int j = 0 ;j < w;j++){
                        y++;
                        screen[c][y][x] = '#';
                    }
                }
            }
            else if(x > b.X){
                if(screen[c][y][x - 1] == ' ' || screen[c][y][x - 1] == '#'){
                    x--;
                    screen[c][y][x] = '#';
                }
                else{
                    w = 8;

                    while((screen[c][y + w][x] != ' ' && screen[c][y + w][x] != '#') || y + w >= 29){
                        w--;
                    }

                    for(int j = 0 ;j < w;j++){
                        y++;
                        screen[c][y][x] = '#';
                    }
                }
            }
            

        }

        chap(c,y,x,screen);

    }

}


void rahh(point a,point b,int c){
    int x = b.X,y = b.Y;
    int z = 0;
    while(x != a.X || y != a.Y){

        z = rand() %2;

        if(x > a.X && y > a.Y){
            if(z == 0 && y > 0){
                if(screen[c][y - 1][x] != '.' && screen[c][y - 1][x] != '|' && screen[c][y - 1][x] != '_' && 
                screen[c][y - 1][x] != '+' && screen[c][y - 1][x] != '=' && screen[c][y - 1][x] != '?' &&
                screen[c][y - 1][x] != '@'){
                    y--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(x > 0){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }

            }
            else if(z == 1 && x > 0){
                if(screen[c][y][x - 1] != '.' && screen[c][y][x - 1] != '|' && screen[c][y][x - 1] != '_' && 
                screen[c][y][x - 1] != '+' && screen[c][y][x - 1] != '=' && screen[c][y][x - 1] != '?' &&
                screen[c][y][x - 1] != '@'){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(y > 0){

                }
            }
        }
        else if(x < a.X && y > a.Y){
            if(z == 0 && y > 0){
                if(screen[c][y - 1][x] != '.' && screen[c][y - 1][x] != '|' && screen[c][y - 1][x] != '_' && 
                screen[c][y - 1][x] != '+' && screen[c][y - 1][x] != '=' && screen[c][y - 1][x] != '?' &&
                screen[c][y - 1][x] != '@'){
                    y--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(x < 29){
                    x++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }


            }
            else if(z == 1 && x < 29){
                if(screen[c][y][x + 1] != '.' && screen[c][y][x + 1] != '|' && screen[c][y][x + 1] != '_' && 
                screen[c][y][x + 1] != '+' && screen[c][y][x + 1] != '=' && screen[c][y][x + 1] != '?' &&
                screen[c][y][x + 1] != '@'){
                    x++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(y > 0){
                    y--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
            }
        }
        else if(x < a.X && y < a.Y){
            if(z == 0 && y < 119){
                if(screen[c][y + 1][x] != '.' && screen[c][y + 1][x] != '|' && screen[c][y + 1][x] != '_' && 
                screen[c][y + 1][x] != '+' && screen[c][y + 1][x] != '=' && screen[c][y + 1][x] != '?' &&
                screen[c][y + 1][x] != '@'){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(x < 29){
                    x++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }


            }
            else if(z == 1 && x < 29){
                if(screen[c][y][x + 1] != '.' && screen[c][y][x + 1] != '|' && screen[c][y][x + 1] != '_' && 
                screen[c][y][x + 1] != '+' && screen[c][y][x + 1] != '=' && screen[c][y][x + 1] != '?' &&
                screen[c][y][x + 1] != '@'){
                    x++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(y < 119){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
            }
        }
        else if(x > a.X && y < a.Y){
            if(z == 0 && y < 119){
                if(screen[c][y + 1][x] != '.' && screen[c][y + 1][x] != '|' && screen[c][y + 1][x] != '_' && 
                screen[c][y + 1][x] != '+' && screen[c][y + 1][x] != '=' && screen[c][y + 1][x] != '?' &&
                screen[c][y + 1][x] != '@'){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(x > 0){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }


            }
            else if(z == 1 && x > 0){
                if(screen[c][y][x - 1] != '.' && screen[c][y][x - 1] != '|' && screen[c][y][x - 1] != '_' && 
                screen[c][y][x - 1] != '+' && screen[c][y][x - 1] != '=' && screen[c][y][x - 1] != '?' &&
                screen[c][y][x - 1] != '@'){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                else if(y < 119){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
            }
        }
        else if(x == a.X && y > a.Y){
            if(screen[c][y - 1][x] != '.' && screen[c][y - 1][x] != '|' && screen[c][y - 1][x] != '_' && 
            screen[c][y - 1][x] != '+' && screen[c][y - 1][x] != '=' && screen[c][y - 1][x] != '?' &&
            screen[c][y - 1][x] != '@'){
                y--;
                screen[c][y][x] = '#';
                mvprintw(y,x,"#");
            }
            else{
                int hg = 15;
                        
                while((screen[c][y][x - hg] == '|' || screen[c][y][x - hg] == '_' || screen[c][y][x - hg] == '+' 
                || screen[c][y][x - hg] == '=' || screen[c][y][x - hg] == '.' || screen[c][y][x - hg] == '?' ||
                screen[c][y][x - hg] == '@') || x <= hg ){
                    hg--;
                }

                for(int j = 0;j < hg;j++){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                
                
            }
        }
        else if(x == a.X && y <  a.Y){
            if(screen[c][y + 1][x] != '.' && screen[c][y + 1][x] != '|' && screen[c][y + 1][x] != '_' && 
                screen[c][y + 1][x] != '+' && screen[c][y + 1][x] != '=' && screen[c][y + 1][x] != '?' &&
                screen[c][y + 1][x] != '@'){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
            }
            else{
                int hg = 15;
                        
                while(screen[c][y][x - hg] == '|' || screen[c][y][x - hg] == '_' || screen[c][y][x - hg] == '+' 
                || screen[c][y][x - hg] == '=' || screen[c][y][x - hg] == '.' || screen[c][y][x - hg] == '?' ||
                screen[c][y][x - hg] == '@' || x <= hg){
                    hg--;
                }

                for(int j = 0;j < hg;j++){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                
                
            }
        }
        else if(x > a.X && y == a.Y){
            if(screen[c][y][x - 1] != '.' && screen[c][y][x - 1] != '|' && screen[c][y][x - 1] != '_' && 
                screen[c][y][x - 1] != '+' && screen[c][y][x - 1] != '=' && screen[c][y][x - 1] != '?' &&
                screen[c][y][x - 1] != '@'){
                    x--;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
            }
            else{
                int hg = 8;
                        
                while(screen[c][y + hg][x] == '|' || screen[c][y + hg][x] == '_' || screen[c][y + hg][x] == '+' 
                || screen[c][y + hg][x] == '=' || screen[c][y + hg][x] == '.' || screen[c][y + hg][x] == '?' ||
                screen[c][y + hg][x] == '@' || y >= 29 - hg){
                    hg--;
                }

                for(int j = 0;j < hg;j++){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                
            }

        }
        else if(x < a.X && y == a.Y){
            if(screen[c][y][x + 1] != '.' && screen[c][y][x + 1] != '|' && screen[c][y][x + 1] != '_' && 
                screen[c][y][x  + 1] != '+' && screen[c][y][x + 1] != '=' && screen[c][y][x + 1] != '?' &&
                screen[c][y][x + 1] != '@'){
                    x++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
            }
            else{
                int hg = 8;
                while(screen[c][y + hg][x] == '|' || screen[c][y + hg][x] == '_' || screen[c][y + hg][x] == '+' 
                || screen[c][y + hg][x] == '=' || screen[c][y + hg][x] == '.' || screen[c][y + hg][x] == '?' ||
                screen[c][y + hg][x] == '@' || y >= 29 - hg){
                    hg--;
                }

                for(int j = 0;j < hg;j++){
                    y++;
                    screen[c][y][x] = '#';
                    mvprintw(y,x,"#");
                }
                
            }

        }

        refresh();
    }
}

void make_road(int pas[4],point p_door[4],point doors[4][6]){
    int x;

    

    



    for(int i = 0 ; i < 4;i++){
        clear();
        for(int j = 0 ; j < 30;j++){
            for(int h = 0;h < 120;h++){
                chap(i,j,h,screen);
            }
            printw("\n");
        }
        refresh();
        x = rand() % 2;
        if(x == 1){
            if(pas[i] == 0){
                rah(p_door[i],doors[i][1],i);
            }
            else{
                rah(doors[i][0],doors[i][1],i);
                
            }
            x = rand() % 2;
            if(x == 1){
                if(pas[i] == 1){
                    rah(p_door[i],doors[i][4],i);
                }
                else{
                    rah(doors[i][1],doors[i][4],i);
                }

                if(pas[i] == 4){
                    rah(p_door[i],doors[i][5],i);
                    rah(doors[i][3],p_door[i],i);
                }
                else{
                    rah(doors[i][3],doors[i][4],i);
                    rah(doors[i][4],doors[i][5],i);
                }

                if(pas[i] == 5){
                    rah(doors[i][2],p_door[i],i);
                }
                else{
                    rah(doors[i][2],doors[i][5],i);
                }
                
            }
            else{
                if(pas[i] == 1){
                    rah(p_door[i],doors[i][2],i);
                }
                else{
                    rah(doors[i][1],doors[i][2],i);
                }
                
                if(pas[i] == 2){
                    rah(p_door[i],doors[i][5],i);
                }
                else{
                    rah(doors[i][2],doors[i][5],i);
                }
                
                if(pas[i] == 5){
                    rah(doors[i][4],p_door[i],i);
                }
                else{
                    rah(doors[i][4],doors[i][5],i);
                }
                
                if(pas[i] == 4){
                    rah(doors[i][3],p_door[i],i);
                }
                else{
                    rah(doors[i][3],doors[i][4],i);
                }

            }
        }
        else{
            if(pas[i] == 0){
                rah(p_door[i],doors[i][3],i);
            }
            else{
                rah(doors[i][0],doors[i][3],i);
            }

            if(pas[i] == 3){
                rah(p_door[i],doors[i][4],i);
            }
            else{
                rah(doors[i][3],doors[i][4],i);
            }
            
            x = rand() % 2;
            if(x == 1){

                if(pas[i] == 4){
                    rah(doors[i][1],p_door[i],i);
                }
                else{
                    rah(doors[i][1],doors[i][4],i);
                }

                if(pas[i] == 1){
                    rah(p_door[i],doors[i][2],i);
                }
                else{
                    rah(doors[i][1],doors[i][2],i);
                }

                if(pas[i] == 2){
                    rah(p_door[i],doors[i][5],i);
                }
                else{
                    rah(doors[i][2],doors[i][5],i);
                }
            }
            else{

                if(pas[i] == 4){
                    rah(p_door[i],doors[i][5],i);
                }
                else{
                    rah(doors[i][4],doors[i][5],i);
                }

                if(pas[i] == 5){
                    rah(doors[i][2],p_door[i],i);
                }
                else{
                    rah(doors[i][2],doors[i][5],i);
                }

                if(pas[i] == 2){
                    rah(doors[i][1],p_door[i],i);
                }
                else{
                    rah(doors[i][1],doors[i][2],i);
                }
            }
            
        }

    

    }

}

void make_trap(room a){


    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    trap[a.floor][w][z] = '^';
    //mvprintw(w,z,"^");

}

void make_upstairs(room a){

    int z,w;
    
    do{
        z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
        w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;
    }while(screen[a.floor][w][z] == '&' || screen[a.floor][w][z] == '$');
    

    screen[a.floor][w][z] = '>';
    upstairs[a.floor].Z = a.floor;
    upstairs[a.floor].Y = w;
    upstairs[a.floor].X = z;
}

void make_downstairs(room a){

    int z,w;
    do{
        z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
        w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;
    }while(screen[a.floor][w][z] == '&' || screen[a.floor][w][z] == '$');

    screen[a.floor][w][z] = '<';
    downstairs[a.floor - 1].Z = a.floor;
    downstairs[a.floor - 1].Y = w;
    downstairs[a.floor - 1].X = z;
}

point secret_door(room a , point b){

    int x,z;

    z = rand() %4;
    switch(z){
        case 0:
            x = rand() % (a.difference.X - 1);
            while(screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] == '+' ||
            screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] == '='){
                x = rand() % (a.difference.X - 1);
            }
            b.Y = a.up_left.Y - 2;
            b.X = a.up_left.X + 1 + x;
            screen[a.floor][a.up_left.Y - 2][a.up_left.X + 1 + x] = '#';
            screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] = '?';
            mvprintw(a.up_left.Y - 1,a.up_left.X + 1 + x,"?");
            break;
        case 1:
            x = rand() % (a.difference.X - 1);
            while(screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] == '+' ||
            screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] == '='){
                x = rand() % (a.difference.X - 1);
            }
            b.Y = a.up_left.Y + a.difference.Y;
            b.X = a.up_left.X + 1 + x;
            screen[a.floor][a.up_left.Y + a.difference.Y][a.up_left.X + 1 + x] = '#';
            screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] = '?';
            mvprintw(a.up_left.Y + a.difference.Y - 1,a.up_left.X + 1 + x,"?");
            break;
        case 2:
            x = rand () % (a.difference.Y - 1);
            while(screen[a.floor][a.up_left.Y + x][a.up_left.X] == '+' || 
            screen[a.floor][a.up_left.Y + x][a.up_left.X] == '='){
                x = rand () % (a.difference.Y - 1);
            }
            b.Y = a.up_left.Y + x;
            b.X = a.up_left.X - 1;
            screen[a.floor][a.up_left.Y + x][a.up_left.X - 1] = '#';
            screen[a.floor][a.up_left.Y + x][a.up_left.X] = '?';
            mvprintw(a.up_left.Y + x,a.up_left.X,"?");
            break;
        case 3:
            x = rand() % (a.difference.Y - 1);
            while(screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] == '+' ||
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] == '='){
                x = rand() % (a.difference.Y - 1);
            }
            b.Y = a.up_left.Y + x;
            b.X = a.up_left.X + a.difference.X + 1;
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X + 1] = '#';
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] = '?';
            mvprintw(a.up_left.Y + x,a.up_left.X + a.difference.X,"?");
            break;
    }

    return b;

}


point pass_door(room a,point b){
    
    int x,z;

    z = rand() %4;
    switch(z){
        case 0:
            x = rand() % (a.difference.X - 1);
            while(screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] == '+' ||
            screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] == '='){
                x = rand() % (a.difference.X - 1);
            }
            b.Y = a.up_left.Y - 2;
            b.X = a.up_left.X + 1 + x;
            screen[a.floor][a.up_left.Y - 2][a.up_left.X + 1 + x] = '#';
            screen[a.floor][a.up_left.Y - 1][a.up_left.X + 1 + x] = '@';
            door_pass[pdoor_pointer].door.X = a.up_left.X + 1 + x;
            door_pass[pdoor_pointer].door.Y = a.up_left.Y - 1;
            mvprintw(a.up_left.Y - 1,a.up_left.X + 1 + x,"@");
            break;
        case 1:
            x = rand() % (a.difference.X - 1);
            while(screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] == '+' ||
            screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] == '='){
                x = rand() % (a.difference.X - 1);
            }
            b.Y = a.up_left.Y + a.difference.Y;
            b.X = a.up_left.X + 1 + x;
            screen[a.floor][a.up_left.Y + a.difference.Y][a.up_left.X + 1 + x] = '#';
            screen[a.floor][a.up_left.Y + a.difference.Y - 1][a.up_left.X + 1 + x] = '@';
            door_pass[pdoor_pointer].door.X = a.up_left.X + 1 + x;
            door_pass[pdoor_pointer].door.Y = a.up_left.Y + a.difference.Y - 1;
            mvprintw(a.up_left.Y + a.difference.Y - 1,a.up_left.X + x,"@");
            break;
        case 2:
            x = rand () % (a.difference.Y - 1);
            while(screen[a.floor][a.up_left.Y + x][a.up_left.X] == '+' || 
            screen[a.floor][a.up_left.Y + x][a.up_left.X] == '='){
                x = rand () % (a.difference.Y - 1);
            }
            b.Y = a.up_left.Y + x;
            b.X = a.up_left.X - 1;
            screen[a.floor][a.up_left.Y + x][a.up_left.X - 1] = '#';
            screen[a.floor][a.up_left.Y + x][a.up_left.X] = '@';
            door_pass[pdoor_pointer].door.X = a.up_left.X ;
            door_pass[pdoor_pointer].door.Y = a.up_left.Y + x;
            mvprintw(a.up_left.Y + x,a.up_left.X,"@");
            break;
        case 3:
            x = rand() % (a.difference.Y - 1);
            while(screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] == '+' ||
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] == '='){
                x = rand() % (a.difference.Y - 1);
            }
            b.Y = a.up_left.Y + x;
            b.X = a.up_left.X + a.difference.X + 1;
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X + 1] = '#';
            screen[a.floor][a.up_left.Y + x][a.up_left.X + a.difference.X] = '@';
            door_pass[pdoor_pointer].door.X = a.up_left.X + a.difference.X;
            door_pass[pdoor_pointer].door.Y = a.up_left.Y + x;
            mvprintw(a.up_left.Y + x,a.up_left.X + a.difference.X,"@");
            break;
    }

    if(a.floor < 2){
        int y;
        do{
            y = rand() % 4;
        }while((y == 0 && z == 0 && x == 0) || (y == 0 && z == 2 && x == 0) ||
        (y == 1 && z == 0 && x == a.difference.X - 2) || (y == 1 && z == 3 && x == 0)||
        (y == 2 && z == 2 && x == a.difference.Y - 2) || (y == 2 && z == 3 && x == 0) ||
        (y == 3 && z == 1 && x == a.difference.X - 2) || (y == 3 && z == 3 && x == a.difference.Y - 2));

        if(y == 0){
            screen[a.floor][a.up_left.Y][a.up_left.X + 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y;
        }
        else if(y == 1){
            screen[a.floor][a.up_left.Y][a.up_left.X + a.difference.X - 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y;
        }
        else if(y == 2){
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + 1]  = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y + a.difference.Y - 2;
        }
        else if(y == 3){
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + a.difference.X - 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y + a.difference.Y - 2;
        }

        door_pass[pdoor_pointer].pass_maker.Z =  a.floor;
        door_pass[pdoor_pointer].door.Z = a.floor;
        
    }
    else{
        int d;
        
        
        do{
            d = rand() % 4;
        }while((d == 0 && z == 0 && x == 0) || (d == 0 && z == 2 && x == 0) ||
        (d == 1 && z == 0 && x == a.difference.X - 2) || (d == 1 && z == 3 && x == 0)||
        (d == 2 && z == 2 && x == a.difference.Y - 2) || (d == 2 && z == 3 && x == 0) ||
        (d == 3 && z == 1 && x == a.difference.X - 2) || (d == 3 && z == 3 && x == a.difference.Y - 2));

        if(d == 0){
            screen[a.floor][a.up_left.Y][a.up_left.X + 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y;
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + a.difference.X - 1] = '$';
            door_pass[pdoor_pointer].pass_makertwo.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_makertwo.Y = a.up_left.Y + a.difference.Y - 2;

        }
        else if(d == 1){
            screen[a.floor][a.up_left.Y][a.up_left.X + a.difference.X - 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y;
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + 1] = '$';
            door_pass[pdoor_pointer].pass_makertwo.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_makertwo.Y = a.up_left.Y + a.difference.Y - 2;

        }
        else if(d == 2){
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + 1]  = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y + a.difference.Y - 2;
            screen[a.floor][a.up_left.Y][a.up_left.X + a.difference.X - 1] = '$';
            door_pass[pdoor_pointer].pass_makertwo.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_makertwo.Y = a.up_left.Y;

        }
        else if(d == 3){
            screen[a.floor][a.up_left.Y + a.difference.Y - 2][a.up_left.X + a.difference.X - 1] = '&';
            door_pass[pdoor_pointer].pass_maker.X = a.up_left.X + a.difference.X - 1;
            door_pass[pdoor_pointer].pass_maker.Y = a.up_left.Y + a.difference.Y - 2;
            screen[a.floor][a.up_left.Y][a.up_left.X + 1] = '$';
            door_pass[pdoor_pointer].pass_makertwo.X = a.up_left.X + 1;
            door_pass[pdoor_pointer].pass_makertwo.Y = a.up_left.Y;

        }

        door_pass[pdoor_pointer].pass_maker.Z =  a.floor;
        door_pass[pdoor_pointer].pass_makertwo.Z =  a.floor;
        door_pass[pdoor_pointer].door.Z = a.floor;
    }

    door_pass[pdoor_pointer].open = 0;
    door_pass[pdoor_pointer].try = 0;
    pdoor_pointer++;

    return b;

}

void show_pass(char a[5]){

    int y ;
    y = rand() % 2;
    
    if(y == 0 ){
        mvprintw(0,5,"                                                                                      ");
        mvprintw(0,5,"password : %c%c%c%c",a[0],a[1],a[2],a[3]);

    }
    else{
        mvprintw(0,5,"                                                                                      ");
        mvprintw(0,5,"password : %c%c%c%c",a[3],a[2],a[1],a[0]);

    }
    


}

void make_pass(makan ja){
    int z,x,c,v;

    for(int i = 0 ; i < pdoor_pointer;i++){
        if(door_pass[i].pass_maker.Z == ja.Z && door_pass[i].pass_maker.Y == ja.Y && door_pass[i].pass_maker.X == ja.X){
            
            
            z = rand() % 10;
            x = rand() % 10;
            c = rand() % 10;
            v = rand() % 10;

            door_pass[i].password[0] = 48 + z;
            door_pass[i].password[1] = 48 + x;
            door_pass[i].password[2] = 48 + c;
            door_pass[i].password[3] = 48 + v;
            door_pass[i].password[4] = '\0';

            show_pass(door_pass[i].password);

        }
        if(door_pass[i].pass_makertwo.Z == ja.Z && door_pass[i].pass_makertwo.Y == ja.Y && door_pass[i].pass_makertwo.X == ja.X){
            
            
            z = rand() % 10;
            x = rand() % 10;
            c = rand() % 10;
            v = rand() % 10;

            door_pass[i].passwordtwo[0] = 48 + z;
            door_pass[i].passwordtwo[1] = 48 + x;
            door_pass[i].passwordtwo[2] = 48 + c;
            door_pass[i].passwordtwo[3] = 48 + v;
            door_pass[i].passwordtwo[4] = '\0';

            show_pass(door_pass[i].passwordtwo);
        }

    }

}

void open_door(makan ja){
    char a[4];
    int x = 10;
    
    echo();
    mvprintw(0,5,"                                                                                   ");
    mvprintw(0,5,"Enter password : ");
    refresh();
    for(int i = 0 ; i  < pdoor_pointer;i++){
        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y && door_pass[i].door.X == ja.X){
            x = i;
        }
    }

    mvprintw(0,5,"                                                                                   ");
    mvprintw(0,5,"Enter password or if you want use key press 'K' %d: ",x);
    refresh();
    a[0] = getchar();
    refresh();
    if(a[0] == 'K' ){
        if(key == 0){
            mvprintw(0,5,"                                                                               ");
            mvprintw(0,5,"you don't have any key :/");
            refresh();
        }
        else{
            key--;
            
            int jak ;
            jak = rand() % 10;
            if(jak == 0){
                mvprintw(0,5,"                                                                               ");
                mvprintw(0,5,"key broked :(");
                b_key++;
                refresh();
            }
            else{
                door_pass[x].open = 1;
                mvprintw(0,5,"                                                                               ");
                mvprintw(0,5,"door is open");
                attron(COLOR_PAIR(9));
                mvprintw(ja.Y,ja.X,"@");
                attroff(COLOR_PAIR(9));
                refresh();
            }
        }
        
    }
    else{
        a[1] = getchar();
        refresh();
        a[2] = getchar();
        refresh();
        a[3] = getchar();
        refresh();
        
        
        if(ja.Z < 2){
            if(door_pass[x].try >= 3){
                
                attron(COLOR_PAIR(8));
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"RED MODE");
                attroff(COLOR_PAIR(8));
                refresh();
            }
            else if(strcmp(door_pass[x].password,a) == 0 ){
                door_pass[x].open = 1;
                
                attron(COLOR_PAIR(9));
                mvprintw(ja.Y,ja.X,"@");
                attroff(COLOR_PAIR(9));
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Correct password!");
                refresh();
            }
            else if(door_pass[x].try == 0){
                
                door_pass[x].try = 1;
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Yellow mode start");
                refresh();
                
            }
            else if(door_pass[x].try == 1){
                
                door_pass[x].try = 2;
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Orange mode start");
                refresh();
                
            }
            else{
                door_pass[x].try = 3;
                attron(COLOR_PAIR(8));
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Red mode start");
                attroff(COLOR_PAIR(8));
                refresh();
            }
        }
        else{

            mvprintw(29,10,"%s",door_pass[x].password);

            if(door_pass[x].try >= 3){
                
                attron(COLOR_PAIR(8));
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"RED MODE");
                attroff(COLOR_PAIR(8));
                refresh();
            }
            else if(strcmp(door_pass[x].password,a) == 0 ){
                
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Correct password! Enter second password : ");
                refresh();

                char b[4];
                b[0] = getchar();
                refresh();
                b[1] = getchar();
                refresh();
                b[2] = getchar();
                refresh();
                b[3] = getchar();
                refresh();


                if(strcmp(door_pass[x].passwordtwo,b) == 0){
                    door_pass[x].open = 1;
                    
                    attron(COLOR_PAIR(9));
                    mvprintw(ja.Y,ja.X,"@");
                    attroff(COLOR_PAIR(9));
                    mvprintw(0,5,"                                                                      ");
                    mvprintw(0,5,"Correct password!");
                    refresh();
                    
                }
                else if(door_pass[x].try == 0){
                    door_pass[x].try = 1;
                    mvprintw(0,5,"                                                                     ");
                    mvprintw(0,5,"Wrong password. Yellow mode start");
                    refresh();
                }
                else if(door_pass[x].try == 1){
                    door_pass[x].try = 2;
                    mvprintw(0,5,"                                                                     ");
                    mvprintw(0,5,"Wrong password. Orange mode start");
                    refresh();
                }
                else{
                    door_pass[x].try = 3;
                    attron(COLOR_PAIR(8));
                    mvprintw(0,5,"                                                                     ");
                    mvprintw(0,5,"Wrong password. Red mode start");
                    attroff(COLOR_PAIR(8));
                    refresh();
                }
            }
            else if(door_pass[x].try == 0){
                
                door_pass[x].try = 1;
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Yellow mode start");
                refresh();
                
            }
            else if(door_pass[x].try == 1){
                
                door_pass[x].try = 2;
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Orange mode start");
                refresh();
                
            }
            else{
                door_pass[x].try = 3;
                attron(COLOR_PAIR(8));
                mvprintw(0,5,"                                                                         ");
                mvprintw(0,5,"Wrong password. Red mode start");
                attroff(COLOR_PAIR(8));
                refresh();
            }
        }
    }

    noecho();

}

void make_food(room a){

    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    int x;
    x = rand() % 3;

    screen[a.floor][w][z] = 54 + x;

}

void make_weapon(room a){


    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    int x ;
    x = rand() % 4;
    x++;
    screen[a.floor][w][z] = 48 + x;

    if(x == 2){
        dagger[a.floor][w][z] = 10;
    }

    if(x == 3){
        magic[a.floor][w][z] = 8;
    }

    if(x == 4){
        arrow[a.floor][w][z] = 20;
    }
}


void make_spell(room a){


    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    int x;
    x = rand() %3;
    if(x == 0){
        screen[a.floor][w][z] = 'q' ;
    }
    else if(x == 1){
        screen[a.floor][w][z] = 'a';
    }
    else if(x == 2){
        screen[a.floor][w][z] = 'p';
    }
    

}

void make_gold(room a){


    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    screen[a.floor][w][z] = '0';
    
}

void make_blackgold(room a){


    int z,w;
    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    screen[a.floor][w][z] = 'b';
    
}

void make_key(room a){
    

    int z,w;
    do{
        z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
        w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;
    }while(screen[a.floor][w][z] == '>' || screen[a.floor][w][z] == '<');


    
    screen[a.floor][w][z] = 'f';
}

int food_meno(){
    clear();

    char k;
    /*
    mvprintw(5,10,"a)normal food : %d",food[0]);
    mvprintw(6,10,"b)power food %d",food[1]);
    mvprintw(7,10,"c)speed food %d",food[2]);
    refresh();
    k = getchar();

    

    if(k == 'a' && food[0] > 0){
        food[0]--;
        return 1;
    }
    else if(k == 'b' && food[1] > 0){
        food[1]--;
        return 2;
    }
    else if(k == 'c' && food[2] > 0){
        food[2]--;
        return 3;
    }
    else if(k == 'd' && food[3] > 0){
        food[3]--;
        return 4;
    }
    return 0;
    */
    for(int i = 0 ; i < 5;i++){
        switch(food[i].type){
            case 0:
                mvprintw(5 + i * 5,15,"%d) empty",i + 1);
                break;
            case 1:
                mvprintw(5 + i * 5,15,"%d) Normal food",i + 1);
                break;
            case 2:
                mvprintw(5 + i * 5,15,"%d) Power food",i + 1);
                break;
            case 3:
                mvprintw(5 + i * 5,15,"%d) Speed food",i + 1);
                break;

        }
    }
    int m = 0,n = 0;
    m = health / (max_health /20);
    n = hungry / (max_hungry /20);
    
    
    attron(COLOR_PAIR(3));
    mvprintw(10,50,"health");
    attroff(COLOR_PAIR(3));
    move(11,45);
    attron(COLOR_PAIR(9));
    for(int i = 0 ; i < m;i++){
        printw(" ");
    }
    attroff(COLOR_PAIR(9));

    attron(COLOR_PAIR(2));
    mvprintw(20,50,"hungry");
    attroff(COLOR_PAIR(2));
    move(21,45);
    attron(COLOR_PAIR(8));
    for(int i = 0 ; i < n;i++){
        printw(" ");
    }
    attroff(COLOR_PAIR(8));
    refresh();
    k = getchar();


    switch(food[k - 49].type){
        case 0:
            return 0;
            break;
        case 1:
            food[k - 49].type =  0;
            food[k - 49].time = 0;
            
            if(food[k - 49].expiration > 0){
                food[k - 49].expiration = 0;
                return 1;
            }
            food[k - 49].expiration = 0;
            return 2;
            break;
        case 2:
            food[k - 49].type =  0;
            food[k - 49].time = 0;
            if(food[k - 49].expiration == 0){
                food[k - 49].expiration = 0;
                return 3;
            }
            else if(food[k - 49].expiration == 1){
                food[k - 49].expiration = 0;
                return 2;
            }
            else{
                food[k - 49].expiration = 0;
                return 1;
            }
            break;
        case 3:
            food[k - 49].type =  0;
            food[k - 49].time = 0;
            if(food[k - 49].expiration == 0){
                food[k - 49].expiration = 0;
                return 4;
            }
            else if(food[k - 49].expiration == 1){
                food[k - 49].expiration = 0;
                return 2;
            }
            else{
                food[k - 49].expiration = 0;
                return 1;
            }
            break;
    }

}


int weapon_meno(){
    clear();

    char k;

    mvprintw(3,20,"weapon name");
    mvprintw(3,40,"character");
    mvprintw(3,60,"number");
    mvprintw(3,80,"range");
    mvprintw(3,100,"power");

    
    
    mvprintw(6,5,"short-range");
    mvprintw(15,5,"long-range");


    mvprintw(5,20,"a)Mace");
    mvprintw(5,40,"none");
    mvprintw(5,60,"1");
    mvprintw(5,80,"1");
    mvprintw(5,100,"5");



    mvprintw(7,20,"b)Sword");
    mvprintw(7,40,"1");
    mvprintw(7,60,"%d",weapon[0]);
    mvprintw(7,80,"1");
    mvprintw(7,100,"10");
    


    move(10,0);
    for(int i = 0 ; i < 120;i++){
        printw("_");
    }

    mvprintw(12,20,"c) Dagger");
    mvprintw(12,40,"2");
    mvprintw(12,60,"%d",weapon[1]);
    mvprintw(12,80,"5");
    mvprintw(12,100,"12");


    mvprintw(15,20,"d) Magic Wand");
    mvprintw(15,40,"3");
    mvprintw(15,60,"%d",weapon[2]);
    mvprintw(15,80,"10");
    mvprintw(15,100,"15");


    mvprintw(18,20,"e) Normal Arrow");
    mvprintw(18,40,"4");
    mvprintw(18,60,"%d",weapon[3]);
    mvprintw(18,80,"5");
    mvprintw(18,100,"5");

    

    refresh();
    while(TRUE){
        k  = getchar();
        if(k == 'w'){
            now_weapon = 0 ;
        }
        else if(k == 'a'){
            if(now_weapon == 0){
                return 1;
            }
            else{
                return 0;
            }
            
        }
        else if(k == 'b'){
            if(weapon[0] == 1){
                if(now_weapon == 0){
                    return 2;
                }
                else{
                    return 0;
                }
                
            }
            else{
                mvprintw(25,10,"                                                                         ");
                attron(COLOR_PAIR(2));
                mvprintw(25,10,"You do not have Sword");
                attroff(COLOR_PAIR(2));
            }
            
        }
        else if(k == 'c'){

            if(weapon[1] > 0){
                if(now_weapon == 0){
                    return 3;
                }
                else{
                    return 0;
                }
                
            }
            else{
                mvprintw(25,10,"                                                                         ");
                attron(COLOR_PAIR(2));
                mvprintw(25,10,"You do not have any Dagger");
                attroff(COLOR_PAIR(2));
            }
            
        }
        else if(k == 'd'){
            if(weapon[2] > 0){
                if(now_weapon == 0){
                    return 4;
                }
                else{
                    return 0;
                }
                
            }
            else{
                mvprintw(25,10,"                                                                         ");
                attron(COLOR_PAIR(2));
                mvprintw(25,10,"You do not have any Magic Wand");
                attroff(COLOR_PAIR(2));
            }
            
        }
        else if(k == 'e'){
            if(weapon[3] > 0){
                if(now_weapon == 0){
                    return 5;
                }
                else{
                    return 0;
                }
                
            }
            else{
                mvprintw(25,10,"                                                                         ");
                attron(COLOR_PAIR(2));
                mvprintw(25,10,"You do not have any Normal Arrow");
                attroff(COLOR_PAIR(2));
            }

        }
        else{
            mvprintw(25,10,"                                                                            ");
            mvprintw(25,10,"press correct button");
        }
        refresh();
    }
    
    
    

}

int spell_meno(){

    clear();

    char k;
    move(5,10);

    printw("a)Health : %d",spell[0]);
    printw("\n          ");


    printw("b)Speed : %d",spell[1]);
    printw("\n          ");


    printw("c)Damage : %d",spell[2]);
    printw("\n          ");

    refresh();
    k  = getchar();

    if(k == 'a' && spell[0] > 0){
        spell[0]--;
        return 1;
    }
    else if(k == 'b' && spell[1] > 0){
        spell[1]--;
        return 2;
    }
    else if(k == 'c' && spell[2] > 0){
        spell[2]--;
        return 3;
    }
    return 0;

}

void make_enemy(room a){

    int x = 0,z = 0,w = 0;

    if(a.floor < 2){
        x = rand() %3;
    }
    if(a.floor ==  2){
        x = rand() %4;
    }
    if(a.floor >= 3){
        x = rand() %5;
    }

    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    enemy[ene].place.Z = a.floor;
    enemy[ene].place.Y = w;
    enemy[ene].place.X = z;
    enemy[ene].sign =  0;

    switch(x){
        case 0:
            enemy[ene].type = 'D';
            enemy[ene].joon = 5;
            enemy[ene].power = 100;
            enemy[ene].movement = 0;
            break;
        case 1:
            enemy[ene].type = 'F';
            enemy[ene].joon = 10;
            enemy[ene].power = 150;
            enemy[ene].movement = 0;
            break;
        case 2:
            enemy[ene].type = 'G';
            enemy[ene].joon = 15;
            enemy[ene].power = 200;
            enemy[ene].movement = 5;
            break;
        case 3:
            enemy[ene].type = 'S';
            enemy[ene].joon = 20;
            enemy[ene].power = 250;
            enemy[ene].movement = 10;
            break;
        case 4:
            enemy[ene].type = 'U';
            enemy[ene].joon = 30;
            enemy[ene].power = 300;
            enemy[ene].movement = 5;
            break;
    }

    ene++;

}

void enemy_move(int a,makan ja){

    int b = 0,d = -1;

    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(enemy[a].place.X - 1 + i == ja.X && enemy[a].place.Y - 1 + j == ja.Y){
                
                b = 1;
            }
        }
    }

    if(b == 1){
        health -= enemy[a].power;
        mvprintw(0,5,"                                                                                            ");
        mvprintw(0,5,"enemy hit you");
    }
    else if((enemy[a].type == 'G' || enemy[a].type == 'U') && enemy[a].movement > 0){
        for(int i = 0;i < ene;i++){
            if(i != a){
                if(enemy[i].place.Z == enemy[a].place.Z && enemy[i].place.Y == enemy[a].place.Y && 
                enemy[i].place.X == enemy[a].place.X){
                    d = i;
                    break;
                }
            }
            
        }

        if(d == -1){
            chap(enemy[a].place.Z,enemy[a].place.Y,enemy[a].place.X,screen);
        }
        else{
            mvprintw(enemy[a].place.Y,enemy[a].place.X,"%c",enemy[d].type);
        }
           
        if(ja.X > enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.X++;
            enemy[a].place.Y++;
        }
        else if(ja.X > enemy[a].place.X && ja.Y == enemy[a].place.Y){
            enemy[a].place.X++;
        }
        else if(ja.X > enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.X++;
            enemy[a].place.Y--;
        }
        else if(ja.X == enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.Y++;
        }
        else if(ja.X == enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.Y--;
        }
        else if(ja.X < enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.X--;
            enemy[a].place.Y++;
        }
        else if(ja.X < enemy[a].place.X && ja.Y == enemy[a].place.Y){
            enemy[a].place.X--;
        }
        else if(ja.X < enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.X--;
            enemy[a].place.Y--;
        }

        enemy[a].movement--;
        mvprintw(enemy[a].place.Y,enemy[a].place.X,"%c",enemy[a].type);
        
    }
    else if(enemy[a].type == 'S' && enemy[a].movement > 0){

        for(int i = 0;i < ene;i++){
            if(i != a){
                if(enemy[i].place.Z == enemy[a].place.Z && enemy[i].place.Y == enemy[a].place.Y && 
                enemy[i].place.X == enemy[a].place.X){
                    d = i;
                    break;
                }
            }
            
        }

        if(d == -1){
            chap(enemy[a].place.Z,enemy[a].place.Y,enemy[a].place.X,screen);
        }
        else{
            mvprintw(enemy[a].place.Y,enemy[a].place.X,"%c",enemy[d].type);
        }

        if(ja.X > enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.X++;
            enemy[a].place.Y++;
        }
        else if(ja.X > enemy[a].place.X && ja.Y == enemy[a].place.Y){
            enemy[a].place.X++;
        }
        else if(ja.X > enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.X++;
            enemy[a].place.Y--;
        }
        else if(ja.X == enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.Y++;
        }
        else if(ja.X == enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.Y--;
        }
        else if(ja.X < enemy[a].place.X && ja.Y > enemy[a].place.Y){
            enemy[a].place.X--;
            enemy[a].place.Y++;
        }
        else if(ja.X < enemy[a].place.X && ja.Y == enemy[a].place.Y){
            enemy[a].place.X--;
        }
        else if(ja.X < enemy[a].place.X && ja.Y < enemy[a].place.Y){
            enemy[a].place.X--;
            enemy[a].place.Y--;
        }

        mvprintw(enemy[a].place.Y,enemy[a].place.X,"%c",enemy[a].type);
    }

    refresh();
}

void enemy_state(makan ja){
    
    int z = 9;
    if(ja.Z < 4){


        for(int i = 0 ; i < 6 ;i++){
            if(ja.X > otagh[ja.Z][i].up_left.X && 
            ja.X < otagh[ja.Z][i].up_left.X + otagh[ja.Z][i].difference.X){
                if(ja.Y > otagh[ja.Z][i].up_left.Y - 1 && 
                ja.Y < otagh[ja.Z][i].up_left.Y + otagh[ja.Z][i].difference.Y - 1){
                    z = i;
                }
            }
        }
    

        if(z == 9){
            return;
        }
        else{

            for(int i = 0 ;i < 12;i++){
                if(enemy[i].place.Z == ja.Z){
                    if(enemy[i].place.X > otagh[ja.Z][z].up_left.X &&
                    enemy[i].place.X < otagh[ja.Z][z].up_left.X + otagh[ja.Z][z].difference.X){
                        if(enemy[i].place.Y > otagh[ja.Z][z].up_left.Y - 1 &&
                        enemy[i].place.Y < otagh[ja.Z][z].up_left.Y + otagh[ja.Z][z].difference.Y - 1){
                            enemy_move(i,ja);
                        }
                    }
                }
            }

        }
    }
    else if(ja.Z == 4){
        for(int i = 12;i < 22;i++){
            for(int i = 12;i < 22;i++){
                if(enemy[i].place.Z == ja.Z){
                    if(enemy[i].place.X > ganj.up_left.X && 
                    enemy[i].place.X < ganj.up_left.X + ganj.difference.X){
                        if(enemy[i].place.Y > ganj.up_left.Y - 1 && 
                        enemy[i].place.Y < ganj.up_left.Y + ganj.difference.Y - 1){
                            enemy_move(i,ja);
                        }
                    }
                }
            }
        }
    }


}
/*
void make_ganj_room(){

    int z = 0,w = 0;

    if(sec[3] == 5){
        make_trap(otagh[3][2]);
        make_trap(otagh[3][2]);
        make_gold(otagh[3][2]);
        make_blackgold(otagh[3][2]);
        z = (rand() % (otagh[3][2].difference.X - 1)) + otagh[3][2].up_left.X + 1;
        w = (rand() % (otagh[3][2].difference.Y - 1)) + otagh[3][2].up_left.Y;

        enemy[ene].place.Z = otagh[3][2].floor;
        enemy[ene].place.Y = w;
        enemy[ene].place.X = z;
        enemy[ene].type = 'U';
        enemy[ene].joon = 30;
        enemy[ene].power = 300;
        enemy[ene].movement = 5;

        end.Z = 4;
        end.Y = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][2].up_left.Y;
        end.X = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][2].up_left.X + 1;
    }
    else if(sec[3] == 2){
        make_trap(otagh[3][5]);
        make_trap(otagh[3][5]);
        make_gold(otagh[3][5]);
        make_blackgold(otagh[3][5]);
        z = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][5].up_left.X + 1;
        w = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][5].up_left.Y;

        enemy[ene].place.Z = otagh[3][5].floor;
        enemy[ene].place.Y = w;
        enemy[ene].place.X = z;
        enemy[ene].type = 'U';
        enemy[ene].joon = 30;
        enemy[ene].power = 300;
        enemy[ene].movement = 5;

        end.Z = 4;
        end.Y = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][5].up_left.Y;
        end.X = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][5].up_left.X + 1;
    }
    else{
        z = rand() %2;
        if(z == 0){
            make_trap(otagh[3][5]);
            make_trap(otagh[3][5]);
            make_gold(otagh[3][5]);
            make_blackgold(otagh[3][5]);
            z = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][5].up_left.X + 1;
            w = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][5].up_left.Y;

            enemy[ene].place.Z = otagh[3][5].floor;
            enemy[ene].place.Y = w;
            enemy[ene].place.X = z;
            enemy[ene].type = 'U';
            enemy[ene].joon = 30;
            enemy[ene].power = 300;
            enemy[ene].movement = 5;

            end.Z = 4;
            end.Y = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][5].up_left.Y;
            end.X = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][5].up_left.X + 1;
        }
        else{
            make_trap(otagh[3][2]);
            make_trap(otagh[3][2]);
            make_gold(otagh[3][2]);
            make_blackgold(otagh[3][2]);
            z = (rand() % (otagh[3][2].difference.X - 1)) + otagh[3][2].up_left.X + 1;
            w = (rand() % (otagh[3][2].difference.Y - 1)) + otagh[3][2].up_left.Y;

            enemy[ene].place.Z = otagh[3][2].floor;
            enemy[ene].place.Y = w;
            enemy[ene].place.X = z;
            enemy[ene].type = 'U';
            enemy[ene].joon = 30;
            enemy[ene].power = 300;
            enemy[ene].movement = 5;

            end.Z = 3;
            end.Y = (rand() % (otagh[3][5].difference.Y - 1)) + otagh[3][2].up_left.Y;
            end.X = (rand() % (otagh[3][5].difference.X - 1)) + otagh[3][2].up_left.X + 1;
        }
    }

    screen[end.Z][end.Y][end.X] = 'E';
}
*/
void ganj_room(){


    ganj.floor = 4;
    ganj.up_left.X = (rand() %10) + 5;
    ganj.up_left.Y = (rand() %3) + 3;
    ganj.difference.X = (rand() %10) + 90;
    ganj.difference.Y = (rand() %3) + 20;

    
    for(int j = 0 ;j <= ganj.difference.X;j++){
        screen[ganj.floor][ganj.up_left.Y - 1][ganj.up_left.X + j] = '_';
        screen[ganj.floor][ganj.up_left.Y + ganj.difference.Y - 1][ganj.up_left.X + j] = '_';
        mvprintw(ganj.up_left.Y - 1,ganj.up_left.X + j,"_");
        mvprintw(ganj.up_left.Y + ganj.difference.Y - 1,ganj.up_left.X + j,"_");
    }
    
    
    for(int j = 0  ;j < ganj.difference.Y;j++){
        screen[ganj.floor][ganj.up_left.Y + j][ganj.up_left.X] = '|';
        screen[ganj.floor][ganj.up_left.Y + j][ganj.up_left.X + ganj.difference.X] = '|';
        mvprintw(ganj.up_left.Y + j,ganj.up_left.X,"|");
        mvprintw(ganj.up_left.Y + j,ganj.up_left.X + ganj.difference.X,"|");
    }
    

    for(int j = ganj.up_left.X + 1 ;j < ganj.difference.X + ganj.up_left.X;j++){
        for(int h = ganj.up_left.Y ;h < ganj.difference.Y + ganj.up_left.Y - 1;h++){
            screen[4][h][j] = '.';
            mvprintw(h,j,".");
        }
    }
    
    
    for(int i = 0 ; i < 5;i++){
        make_blackgold(ganj);
    }

    for(int i =0 ; i < 10;i++){
        make_gold(ganj);
    }

    make_downstairs(ganj);
    screen[downstairs[3].Z][downstairs[3].Y][downstairs[3].X] = 'i';

    for(int i = 0 ;i < 10;i++){
        make_trap(ganj);
        make_enemy(ganj);
    }

}

void taskbar(){
    mvprintw(31,5,"                                                                                                                         ");
    mvprintw(31,5,"Level : %d",level);
    mvprintw(31,20,"Health : %d(%d)",health,max_health);
    mvprintw(31,45,"Key : %d(%d)",key,b_key);
    mvprintw(31,65,"Gold : %d",gold);
    mvprintw(31,85,"food : %d(%d)",hungry,max_hungry);
    mvprintw(31,105,"score : %d",score);

}

void state(makan ja){
    if(food_speed > 0 && spell_speed > 0){
        if(hungry > 0){
            hungry--;
        }
        else{
            health--;
        }
        food_speed--;
        spell_speed--;
        for(int i = 0 ; i < 4;i++){
            if(ja.Z == otagh[i][sec[i]].floor){
                if(ja.Y < otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                ja.Y > otagh[i][sec[i]].up_left.Y - 1){
                    if(ja.X < otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                    ja.X > otagh[i][sec[i]].up_left.X){
                        health -= 1;
                    }
                }
            }
        }

        if(hungry > max_hungry - 1000 ){
            if(spell_health > 0){
                if( health < max_health - 1){
                health += 2;
                }
                else {
                    health = max_health;
                }
                spell_health--;
            }
            else{
                
                health ++;
                
            }
            
        }

        en_st = en_st %4;
        if(en_st == 0 || en_st == 1){
            enemy_state(ja);
        }
        en_st += 1;

        for(int i = 0 ; i < 5;i++){
            if(food[i].type > 0){
                food[i].time++;
                if(food[i].time >= 200){
                    food[i].time = 0;
                    food[i].expiration++;
                }
            }
        }

        if(food_power > 0){
            food_power--;
        }

        if(spell_power > 0){
            spell_power--;
        }
    }
    else if(food_speed > 0){
        if(hungry > 1){
            hungry -= 2;
        }
        else{
            health -= 2;
        }
        food_speed--;
        for(int i = 0 ; i < 4;i++){
            if(ja.Z == otagh[i][sec[i]].floor){
                if(ja.Y < otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                ja.Y > otagh[i][sec[i]].up_left.Y - 1){
                    if(ja.X < otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                    ja.X > otagh[i][sec[i]].up_left.X){
                        health -= 2;
                    }
                }
            }
        }

        if(hungry > max_hungry - 1000){
            if(spell_health > 0){
                if( health < max_health - 3){
                health += 4;
                }
                else {
                    health = max_health;
                }
                spell_health -= 2;
            }
            else{
                if( health < max_health - 1){
                health += 2;
                }
                else {
                    health = max_health;
                }
            }
            
        }

        en_st = en_st %4;
        if(en_st == 0 || en_st == 1){
            enemy_state(ja);
        }
        en_st += 2;

        for(int i = 0 ; i < 5;i++){
            if(food[i].type > 0){
                food[i].time += 2;
                if(food[i].time >= 200){
                    food[i].time = 0;
                    food[i].expiration++;
                }
            }
        }

        if(food_power >= 2){
            food_power -= 2;
        }
        else{
            food_power = 0;
        }

        if(spell_power >= 2){
            spell_power -= 2;
        }
        else{
            spell_power = 0;
        }
    }
    else if(spell_speed > 0){
        if(hungry > 1){
            hungry -= 2;
        }
        else{
            health -= 2;
        }
        spell_speed--;
        for(int i = 0 ; i < 4;i++){
            if(ja.Z == otagh[i][sec[i]].floor){
                if(ja.Y < otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                ja.Y > otagh[i][sec[i]].up_left.Y - 1){
                    if(ja.X < otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                    ja.X > otagh[i][sec[i]].up_left.X){
                        health -= 2;
                    }
                }
            }
        }

        if(hungry > max_hungry - 1000){
            if(spell_health > 0){
                if( health < max_health - 3){
                health += 4;
                }
                else {
                    health = max_health;
                }
                spell_health -= 2;
            }
            else{
                if( health < max_health - 1){
                health += 2;
                }
                else {
                    health = max_health;
                }
            }
            
        }

        en_st = en_st %4;
        if(en_st == 0 || en_st == 1){
            enemy_state(ja);
        }
        en_st += 2;

        for(int i = 0 ; i < 5;i++){
            if(food[i].type > 0){
                food[i].time += 2;
                if(food[i].time >= 200){
                    food[i].time = 0;
                    food[i].expiration++;
                }
            }
        }

        if(food_power >= 2){
            food_power -= 2;
        }
        else{
            food_power = 0;
        }

        if(spell_power >= 2){
            spell_power -= 2;
        }
        else{
            spell_power = 0;
        }

    }
    else{

        if(hungry > 3){
            hungry -= 4;
        }
        else{
            health -= 4;
        }
        for(int i = 0 ; i < 4;i++){
            if(ja.Z == otagh[i][sec[i]].floor){
                if(ja.Y < otagh[i][sec[i]].up_left.Y + otagh[i][sec[i]].difference.Y - 1 && 
                ja.Y > otagh[i][sec[i]].up_left.Y - 1){
                    if(ja.X < otagh[i][sec[i]].up_left.X + otagh[i][sec[i]].difference.X && 
                    ja.X > otagh[i][sec[i]].up_left.X){
                        health -= 4;
                    }
                }
            }
        }

        if(hungry > max_hungry - 1000){
            if(spell_health > 0){
                if( health < max_health - 7){
                health += 8;
                }
                else {
                    health = max_health;
                }
                spell_health -= 4;
            }
            else{
                if( health < max_health - 3){
                health += 4;
                }
                else {
                    health = max_health;
                }
            }
            
        }

        enemy_state(ja);

        for(int i = 0 ; i < 5;i++){
            if(food[i].type > 0){
                food[i].time++;
                if(food[i].time >= 200){
                    food[i].time = 0;
                    food[i].expiration++;
                }
            }
        }

        if(food_power >= 4){
            food_power -= 4;
        }
        else{
            food_power = 0;
        }

        if(spell_power >= 4){
            spell_power -= 4;
        }
        else{
            spell_power = 0;
        }

    }






    

    
}

void did(makan ja){
    if(screen[ja.Z][ja.Y][ja.X] == '#'){

        if(screen[ja.Z][ja.Y - 1][ja.X - 1] == '#' || screen[ja.Z][ja.Y - 1][ja.X - 1] == '+'|| 
        screen[ja.Z][ja.Y - 1][ja.X - 1] == '@' || screen[ja.Z][ja.Y - 1][ja.X - 1] == '='){
            chap(ja.Z,ja.Y - 1,ja.X - 1,screen);
            save[ja.Z][ja.Y - 1][ja.X - 1] = screen[ja.Z][ja.Y - 1][ja.X - 1];
        }
        if(screen[ja.Z][ja.Y - 1][ja.X] == '#' || screen[ja.Z][ja.Y - 1][ja.X] == '+'||
        screen[ja.Z][ja.Y - 1][ja.X] == '@' || screen[ja.Z][ja.Y - 1][ja.X] == '='){
            chap(ja.Z,ja.Y - 1,ja.X,screen);
            save[ja.Z][ja.Y - 1][ja.X] = screen[ja.Z][ja.Y - 1][ja.X];
        }
        if(screen[ja.Z][ja.Y - 1][ja.X + 1] == '#' || screen[ja.Z][ja.Y - 1][ja.X + 1] == '+'|| 
        screen[ja.Z][ja.Y - 1][ja.X + 1] == '@' || screen[ja.Z][ja.Y - 1][ja.X + 1] == '='){
            chap(ja.Z,ja.Y - 1,ja.X + 1,screen);
            save[ja.Z][ja.Y - 1][ja.X + 1] = screen[ja.Z][ja.Y - 1][ja.X + 1];
        }
        if(screen[ja.Z][ja.Y][ja.X - 1] == '#' || screen[ja.Z][ja.Y][ja.X - 1] == '+'|| 
        screen[ja.Z][ja.Y][ja.X - 1] == '@' || screen[ja.Z][ja.Y][ja.X - 1] == '='){
            chap(ja.Z,ja.Y,ja.X - 1,screen);
            save[ja.Z][ja.Y][ja.X - 1] = screen[ja.Z][ja.Y][ja.X - 1];
        }
        if(screen[ja.Z][ja.Y][ja.X + 1] == '#' || screen[ja.Z][ja.Y][ja.X + 1] == '+'|| 
        screen[ja.Z][ja.Y][ja.X + 1] == '@' || screen[ja.Z][ja.Y][ja.X + 1] == '='){
            chap(ja.Z,ja.Y,ja.X + 1,screen);
            save[ja.Z][ja.Y][ja.X + 1] = screen[ja.Z][ja.Y][ja.X + 1];
        }
        if(screen[ja.Z][ja.Y + 1][ja.X - 1] == '#' || screen[ja.Z][ja.Y + 1][ja.X - 1] == '+'|| 
        screen[ja.Z][ja.Y + 1][ja.X - 1] == '@' || screen[ja.Z][ja.Y + 1][ja.X - 1] == '='){
            chap(ja.Z,ja.Y + 1,ja.X - 1,screen);
            save[ja.Z][ja.Y + 1][ja.X - 1] = screen[ja.Z][ja.Y + 1][ja.X - 1];
        }
        if(screen[ja.Z][ja.Y + 1][ja.X] == '#' || screen[ja.Z][ja.Y + 1][ja.X] == '+'|| 
        screen[ja.Z][ja.Y + 1][ja.X] == '@' || screen[ja.Z][ja.Y + 1][ja.X] == '='){
            chap(ja.Z,ja.Y + 1,ja.X,screen);
            save[ja.Z][ja.Y + 1][ja.X] = screen[ja.Z][ja.Y + 1][ja.X];
        }
        if(screen[ja.Z][ja.Y + 1][ja.X + 1] == '#' || screen[ja.Z][ja.Y + 1][ja.X + 1] == '+'|| 
        screen[ja.Z][ja.Y + 1][ja.X + 1] == '@' || screen[ja.Z][ja.Y + 1][ja.X + 1] == '='){
            chap(ja.Z,ja.Y + 1,ja.X + 1,screen);
            save[ja.Z][ja.Y + 1][ja.X + 1] = screen[ja.Z][ja.Y + 1][ja.X + 1];
        }


    }
    else if(screen[ja.Z][ja.Y][ja.X] == '+' || screen[ja.Z][ja.Y][ja.X] == '?' || 
    screen[ja.Z][ja.Y][ja.X]  == '@' || screen[ja.Z][ja.Y][ja.X] == '=' || 
    screen[ja.Z][ja.Y][ja.X] == '>' || screen[ja.Z][ja.Y][ja.X] == '<' || screen[ja.Z][ja.Y][ja.X] == 'i'){

        int low = 0,high  = 0,right = 0,left = 0;

        while(screen[ja.Z][ja.Y + low][ja.X] != ' ' && screen[ja.Z][ja.Y + low][ja.X] != '#'){

            low++;

        }

        while(screen[ja.Z][ja.Y - high][ja.X] != ' ' && screen[ja.Z][ja.Y - high][ja.X] != '#'){

            high++;

        }

        while(screen[ja.Z][ja.Y][ja.X + right] != ' ' && screen[ja.Z][ja.Y][ja.X + right] != '#'){

            right++;

        }

        while(screen[ja.Z][ja.Y][ja.X - left] != ' ' && screen[ja.Z][ja.Y][ja.X - left] != '#'){

            left++;

        }

        for(int i = ja.Y - high + 1;i < ja.Y + low;i++){
            for(int j = ja.X - left + 1;j < ja.X + right;j++){

                chap(ja.Z,i,j,screen);
                save[ja.Z][i][j] = screen[ja.Z][i][j];

            }
        }
        
        for(int i = 0 ; i < ene;i++){
            if(enemy[i].place.Z == ja.Z){
                if(enemy[i].place.X > ja.X - left  && enemy[i].place.X < ja.X + right){
                    if(enemy[i].place.Y > ja.Y - high && enemy[i].place.Y < ja.Y + low){
                        enemy[i].sign = 1;
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }

            }
        }

    }
}

void get(makan ja){

    if(screen[ja.Z][ja.Y][ja.X] == '&'){
        make_pass(ja);
    }
    else if(screen[ja.Z][ja.Y][ja.X] == '$'){
            if(ja.Z == 2){
                show_pass(door_pass[2].passwordtwo);
            }
            else{
                show_pass(door_pass[3].passwordtwo);
            }
    }

    for(int i = 0 ; i < 4;i++){
        if(ja.Z == otagh[i][kab[i]].floor){
            if(ja.Y <= otagh[i][kab[i]].up_left.Y + otagh[i][kab[i]].difference.Y - 1 && 
            ja.Y >= otagh[i][kab[i]].up_left.Y - 1){
                if(ja.X <= otagh[i][kab[i]].up_left.X + otagh[i][kab[i]].difference.X && 
                ja.X >= otagh[i][kab[i]].up_left.X){
                    return;
                }
            }
        }
    }

                
    int f = 9;
    switch(screen[ja.Z][ja.Y][ja.X]){
        case '0':
            gold++;
            score++;
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find 1 gold");
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            break;
        case 'b':
            gold += 5;
            score += 5;
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find 5 gold");
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            break;
            /*
        case '2':
            weapon[1] =+ 10;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            dagger[ja.Z][ja.Y][ja.X] = 0;
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find 10 Dagger");
            break;
        case '3':
            weapon[2] =+ 8;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            magic[ja.Z][ja.Y][ja.X] = 0;
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find 8 Magic Wand");
            break;
        case '4':
            weapon[3] += 20;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            arrow[ja.Z][ja.Y][ja.X] = 0;
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find 20 Normal Arrow");
            break;*/
        case '1':
            weapon[0] = 1;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find a Sword");
            break;
        case '6':
            /*
            if(food[0] + food[1] + food[2] + food[3] < 5){
                food[0]++;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you find 1 normal food");
            }
            */
            for(int i = 4 ; i >= 0;i--){
                if(food[i].type == 0){
                    f = i;
                }
            }

            if(f == 9){
                break;
            }
            else{
                food[f].type = 1;
                food[f].time = 0;
                food[f].expiration = 0;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you find 1 Normal food");
            }

            break;
            
        case '7':
            /*
            if(food[0] + food[1] + food[2] + food[3] < 5){
                food[1]++;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you get 1 power food");
            }
            */
            for(int i = 4 ; i >= 0;i--){
                if(food[i].type == 0){
                    f = i;
                }
            }

            if(f == 9){
                break;
            }
            else{
                food[f].type = 2;
                food[f].time = 0;
                food[f].expiration = 0;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you find 1 Power food");
            }
            break;
        case '8':
            /*
            if(food[0] + food[1] + food[2] + food[3] < 5){
                food[2]++;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you get 1 speed food");
            }
            */

            for(int i = 4 ; i >= 0;i--){
                if(food[i].type == 0){
                    f = i;
                }
            }

            if(f == 9){
                break;
            }
            else{
                food[f].type = 3;
                food[f].time = 0;
                food[f].expiration = 0;
                screen[ja.Z][ja.Y][ja.X] = '.';
                save[ja.Z][ja.Y][ja.X] = '.';
                mvprintw(0,5,"                                                                          ");
                mvprintw(0,5,"you find 1 Speed food");
            }
            break;
        case 'q':
            spell_health += 40;
            spell[0]++;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you get 1 health spell");
            break;
        case 'a':
            spell_power += 10;
            spell[1]++;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you get 1 power spell");
            break;
        case 'p':
            spell_speed += 20;
            spell[2]++;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you get 1 speed spell");
            break;
        case 'f':
            key++;
            screen[ja.Z][ja.Y][ja.X] = '.';
            save[ja.Z][ja.Y][ja.X] = '.';
            mvprintw(0,5,"                                                                          ");
            mvprintw(0,5,"you find a key");
            break;
        

    }

    if(dagger[ja.Z][ja.Y][ja.X] > 0){
        weapon[1] += dagger[ja.Z][ja.Y][ja.X];
        screen[ja.Z][ja.Y][ja.X] = '.';
        save[ja.Z][ja.Y][ja.X] = '.';
        
        mvprintw(0,5,"                                                                          ");
        mvprintw(0,5,"you find %d Dagger",dagger[ja.Z][ja.Y][ja.X]);
        dagger[ja.Z][ja.Y][ja.X] = 0;
    }

    if(magic[ja.Z][ja.Y][ja.X] > 0){
        weapon[2] += magic[ja.Z][ja.Y][ja.X];
        screen[ja.Z][ja.Y][ja.X] = '.';
        save[ja.Z][ja.Y][ja.X] = '.';
        
        mvprintw(0,5,"                                                                          ");
        mvprintw(0,5,"you find %d Magic Wand",magic[ja.Z][ja.Y][ja.X]);
        magic[ja.Z][ja.Y][ja.X] = 0;
    }

    if(arrow[ja.Z][ja.Y][ja.X] > 0){
        weapon[3] += arrow[ja.Z][ja.Y][ja.X];
        screen[ja.Z][ja.Y][ja.X] = '.';
        save[ja.Z][ja.Y][ja.X] = '.';
        
        mvprintw(0,5,"                                                                          ");
        mvprintw(0,5,"you find %d Normal Arrow",arrow[ja.Z][ja.Y][ja.X]);
        arrow[ja.Z][ja.Y][ja.X] = 0;
    }

    if(trap[ja.Z][ja.Y][ja.X] == '^'){
        health -= 100;
        mvprintw(0,5,"                                                                          ");
        mvprintw(0,5,"Trap !!!!!");

    }
}

makan put_hero(room a){
    int z,w;
    makan k;

    z = (rand() % (a.difference.X - 1)) + a.up_left.X + 1;
    w = (rand() % (a.difference.Y - 1)) + a.up_left.Y;

    k.Z = a.floor;
    k.Y = w;
    k.X = z;

    screen[a.floor][w][z] = 'i';
    did(k);
    return k;
}

void end_game(){
    game_played++;
    info = fopen(acount_file,"w");
    fprintf(info,"%s",gmail);
    fprintf(info,"%s",enter_pass);
    fprintf(info,"%d",total_score);
    fprintf(info , "\n");
    fprintf(info,"%d",game_played);
    fprintf(info , "\n");
    fprintf(info,"%ld",signup_time);
    fprintf(info , "\n");
    fprintf(info,"%d",0);
    fprintf(info , "\n");
    fclose(info);
}

void save_game(makan ja){
    info = fopen(acount_file,"w");
    fprintf(info,"%s",gmail);
    fprintf(info,"%s",enter_pass);
    fprintf(info,"%d",total_score);
    fprintf(info , "\n");
    fprintf(info,"%d",game_played);
    fprintf(info , "\n");
    fprintf(info,"%ld",signup_time);
    fprintf(info , "\n");
    fprintf(info,"%d",1);
    fprintf(info , "\n");
    
    fprintf(info,"%d",ja.Z);
    fprintf(info , "\n");
    fprintf(info,"%d",ja.Y);
    fprintf(info , "\n");
    fprintf(info,"%d",ja.X);
    fprintf(info , "\n");

    for(int i = 0;i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0;h < 120;h++){
                fprintf(info,"%c",screen[i][j][h]);
                
            }
            fprintf(info , "\n");
        }
        fprintf(info , "\n");
        fprintf(info , "\n");
    }

    for(int i = 0;i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0;h < 120;h++){
                fprintf(info,"%c",save[i][j][h]);
                
            }
            fprintf(info , "\n");
        }
        fprintf(info , "\n");
        fprintf(info , "\n");
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fprintf(info,"%c",trap[i][j][h]);
            }
        }
    }

    for(int i = 0 ;i < 4;i++){
        fprintf(info,"%c",door_pass[2].passwordtwo[i]);
    }

    for(int i = 0 ;i < 4;i++){
        fprintf(info,"%c",door_pass[3].passwordtwo[i]);
    }

    for(int i = 0 ;i < 4;i++){
        for(int j = 0 ; j < 6;j++){
            fprintf(info,"%d",otagh[i][j].up_left.X);
            fprintf(info , "\n");
            fprintf(info,"%d",otagh[i][j].up_left.Y);
            fprintf(info , "\n");
            fprintf(info,"%d",otagh[i][j].difference.X);
            fprintf(info , "\n");
            fprintf(info,"%d",otagh[i][j].difference.Y);
            fprintf(info , "\n");
            fprintf(info,"%d",otagh[i][j].floor);
            fprintf(info , "\n");
        }
    }

    fprintf(info,"%d",ganj.up_left.X);
    fprintf(info , "\n");
    fprintf(info,"%d",ganj.up_left.Y);
    fprintf(info , "\n");
    fprintf(info,"%d",ganj.difference.X);
    fprintf(info , "\n");
    fprintf(info,"%d",ganj.difference.Y);
    fprintf(info , "\n");
    fprintf(info,"%d",ganj.floor);
    fprintf(info , "\n");

    for(int i = 0 ; i < 4;i++){
        fprintf(info,"%d",sec[i]);
        fprintf(info , "\n");
    }

    for(int i = 0 ; i < 4;i++){
        fprintf(info,"%d",kab[i]);
        fprintf(info , "\n");
    }

    for(int i = 0 ; i < 4;i++){
        fprintf(info,"%d",pas[i]);
        fprintf(info , "\n");
    }
    
    for(int i = 0;i < 4;i++){
        fprintf(info,"%d",downstairs[i].Z);
        fprintf(info , "\n");
        fprintf(info,"%d",downstairs[i].Y);
        fprintf(info , "\n");
        fprintf(info,"%d",downstairs[i].X);
        fprintf(info , "\n");
    }

    for(int i = 0 ; i < 4;i++){
        fprintf(info,"%d",upstairs[i].Z);
        fprintf(info , "\n");
        fprintf(info,"%d",upstairs[i].Y);
        fprintf(info , "\n");
        fprintf(info,"%d",upstairs[i].X);
        fprintf(info , "\n");
    }

    fprintf(info,"%d",pdoor_pointer);
    fprintf(info , "\n");

    for(int i = 0;i < pdoor_pointer;i++){
        fprintf(info,"%d",door_pass[i].door.Z);
        fprintf(info , "\n");
        fprintf(info,"%d",door_pass[i].door.Y);
        fprintf(info , "\n");
        fprintf(info,"%d",door_pass[i].door.X);
        fprintf(info , "\n");
        fprintf(info,"%d",door_pass[i].pass_maker.Z);
        fprintf(info , "\n");
        fprintf(info,"%d",door_pass[i].pass_maker.Y);
        fprintf(info , "\n");
        fprintf(info,"%d",door_pass[i].pass_maker.X);
        fprintf(info , "\n");
        
        if(i >= 2){
            fprintf(info,"%d",door_pass[i].pass_makertwo.Z);
            fprintf(info , "\n");
            fprintf(info,"%d",door_pass[i].pass_makertwo.Y);
            fprintf(info , "\n");
            fprintf(info,"%d",door_pass[i].pass_makertwo.X);
            fprintf(info , "\n");
        }
        

        
        
        
        
        fprintf(info , "\n");
        fprintf(info , "%d",door_pass[i].open);
        fprintf(info , "\n");
        fprintf(info , "%d",door_pass[i].try);
        fprintf(info , "\n");

        
    }

    fprintf(info,"%d",ene);
    fprintf(info , "\n");

    for(int i = 0 ; i < ene;i++){
        fprintf(info,"%c",enemy[i].type);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].joon);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].place.Z);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].place.Y);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].place.X);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].power);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].movement);
        fprintf(info , "\n");
        fprintf(info,"%d",enemy[i].sign);
        fprintf(info , "\n");
    }
    
    fprintf(info,"%d",mus);
    fprintf(info,"\n");
    fprintf(info,"%d",en_st);
    fprintf(info,"\n");
    fprintf(info,"%d",now_weapon);
    fprintf(info,"\n");
    fprintf(info,"%d",color_hero);
    fprintf(info,"\n");
    fprintf(info,"%d",spell_speed);
    fprintf(info,"\n");
    fprintf(info,"%d",spell_power);
    fprintf(info,"\n");
    fprintf(info,"%d",spell_health);
    fprintf(info,"\n");
    fprintf(info,"%d",food_speed);
    fprintf(info,"\n");
    fprintf(info,"%d",food_power);
    fprintf(info,"\n");
    fprintf(info,"%d",b_key);
    fprintf(info,"\n");
    fprintf(info,"%d",key);
    fprintf(info,"\n");
    fprintf(info,"%d",level);
    fprintf(info,"\n");
    fprintf(info,"%d",score);
    fprintf(info,"\n");
    fprintf(info,"%d",gold);
    fprintf(info,"\n");
    fprintf(info,"%d",max_hungry);
    fprintf(info,"\n");
    fprintf(info,"%d",hungry);
    fprintf(info,"\n");
    fprintf(info,"%d",max_health);
    fprintf(info,"\n");
    fprintf(info,"%d",health);
    fprintf(info,"\n");

    for(int i = 0 ; i < 5;i++){
        fprintf(info,"%d",food[i].type);
        fprintf(info,"\n");
        fprintf(info,"%d",food[i].time);
        fprintf(info,"\n");
        fprintf(info,"%d",food[i].expiration);
        fprintf(info,"\n");
    }

    for(int i = 0 ; i < 3;i++){
        fprintf(info,"%d",spell[i]);
        fprintf(info,"\n");
    }

    for(int i = 0 ; i < 5;i++){
        fprintf(info,"%d",weapon[i]);
        fprintf(info,"\n");
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fprintf(info,"%d",arrow[i][j][h]);
                fprintf(info,"\n");
            }
        }
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fprintf(info,"%d",magic[i][j][h]);
                fprintf(info,"\n");
            }
        }
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fprintf(info,"%d",dagger[i][j][h]);
                fprintf(info,"\n");
            }
        }
    }

    

    fclose(info);
}

void play(makan ja,int color){
    srand(time(0));
    char b = 'p';
    int f = 0,w = 0,s = 0,sy = 9,k = 0,win = 1,sav = 0,L = 0;
    makan sf;
    if(mus > 0){
        Mix_PlayMusic(music[mus - 1], -1);
    }
    


    while(TRUE){
        
        k = 0;
        L = 0;

        b = getchar();
        
        switch(b){
            case 'u':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                    enemy[i].place.X == ja.X + 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y - 1][ja.X + 1] != ' ' && screen[ja.Z][ja.Y - 1][ja.X + 1] != '|' && 
                screen[ja.Z][ja.Y - 1][ja.X + 1] != '_' && screen[ja.Z][ja.Y - 1][ja.X + 1] != '@' && 
                screen[ja.Z][ja.Y - 1][ja.X + 1] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y--;
                    ja.X++;
                    did(ja);

                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X + 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X + 1){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        
                        ja.Y--;
                        ja.X++;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y - 1;
                        sf.X =  ja.X + 1;
                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X + 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y - 1;
                    sf.X =  ja.X + 1;
                    did(sf);
                    chap_hero(ja,color);
                }
                get(ja);
                state(ja);
                taskbar();
                refresh();

                break;

            case 'y':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                    enemy[i].place.X == ja.X - 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y - 1][ja.X - 1] != ' ' && screen[ja.Z][ja.Y - 1][ja.X - 1] != '|' && 
                screen[ja.Z][ja.Y - 1][ja.X - 1] != '_' && screen[ja.Z][ja.Y - 1][ja.X - 1] != '@' &&
                screen[ja.Z][ja.Y - 1][ja.X - 1] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y--;
                    ja.X--;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X - 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X - 1){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        
                        ja.Y--;
                        ja.X--;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y - 1;
                        sf.X =  ja.X - 1;
                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X - 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y - 1;
                    sf.X =  ja.X - 1;
                    did(sf);
                    chap_hero(ja,color);

                }
                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;

            case 'h':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y && 
                    enemy[i].place.X == ja.X - 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y][ja.X - 1] != ' ' && screen[ja.Z][ja.Y][ja.X - 1] != '|' && 
                screen[ja.Z][ja.Y][ja.X - 1] != '_' && screen[ja.Z][ja.Y][ja.X - 1] != '@' &&
                screen[ja.Z][ja.Y][ja.X - 1] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.X--;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y][ja.X - 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y && door_pass[i].door.X == ja.X - 1){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        
                        ja.X--;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y;
                        sf.X =  ja.X - 1;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y][ja.X - 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y;
                    sf.X =  ja.X - 1;
                    did(sf);
                    chap_hero(ja,color);

                }

                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;

            case 'j':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                    enemy[i].place.X == ja.X){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y - 1][ja.X] != ' ' && screen[ja.Z][ja.Y - 1][ja.X] != '|' && 
                screen[ja.Z][ja.Y - 1][ja.X] != '_' && screen[ja.Z][ja.Y - 1][ja.X] != '@' &&
                screen[ja.Z][ja.Y - 1][ja.X] !=  '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y--;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X){
                            sy = i;
                        }
                    }
                    
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        
                        ja.Y--;
                        did(ja);
                        chap_hero(ja,color);
                
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y - 1;
                        sf.X =  ja.X;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y - 1][ja.X] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y - 1;
                    sf.X =  ja.X;
                    did(sf);
                    chap_hero(ja,color);

                }
                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;

            case 'b':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                    enemy[i].place.X == ja.X - 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y + 1][ja.X - 1] != ' ' && screen[ja.Z][ja.Y + 1][ja.X - 1] != '|' && 
                screen[ja.Z][ja.Y + 1][ja.X - 1] != '_' && screen[ja.Z][ja.Y + 1][ja.X - 1] != '@' &&
                screen[ja.Z][ja.Y + 1][ja.X - 1] != '=' && k !=  1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y++;
                    ja.X--;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X - 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X - 1){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        ja.Y++;
                        ja.X--;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y + 1;
                        sf.X =  ja.X - 1;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X - 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y + 1;
                    sf.X =  ja.X - 1;
                    did(sf);
                    chap_hero(ja,color);

                }
                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;

            case 'n':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                    enemy[i].place.X == ja.X + 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y + 1][ja.X + 1] != ' ' && screen[ja.Z][ja.Y + 1][ja.X + 1] != '|' && 
                screen[ja.Z][ja.Y + 1][ja.X + 1] != '_' && screen[ja.Z][ja.Y + 1][ja.X + 1] != '@' &&
                screen[ja.Z][ja.Y + 1][ja.X + 1] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y++;
                    ja.X++;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X + 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X + 1){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        ja.Y++;
                        ja.X++;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y + 1;
                        sf.X =  ja.X + 1;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X + 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y + 1;
                    sf.X =  ja.X + 1;
                    did(sf);
                    chap_hero(ja,color);

                }
                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;
            case 'k':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                    enemy[i].place.X == ja.X){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y + 1][ja.X] != ' ' && screen[ja.Z][ja.Y + 1][ja.X] != '|' && 
                screen[ja.Z][ja.Y + 1][ja.X] != '_' && screen[ja.Z][ja.Y + 1][ja.X] != '@' && 
                screen[ja.Z][ja.Y + 1][ja.X] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.Y++;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X){
                            sy = i;
                        }
                    }
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        ja.Y++;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y + 1;
                        sf.X = ja.X;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y + 1][ja.X] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y + 1;
                    sf.X =  ja.X;
                    did(sf);
                    chap_hero(ja,color);

                }

                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;

            case 'l':
                for(int i = 0 ; i < ene;i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y && 
                    enemy[i].place.X == ja.X + 1){
                        k = 1;
                    }
                }
                if(screen[ja.Z][ja.Y][ja.X + 1] != ' ' && screen[ja.Z][ja.Y][ja.X + 1] != '|' && 
                screen[ja.Z][ja.Y][ja.X + 1] != '_' && screen[ja.Z][ja.Y][ja.X + 1] != '@' && 
                screen[ja.Z][ja.Y][ja.X + 1] != '=' && k != 1){
                    chap(ja.Z,ja.Y,ja.X,screen);
                    ja.X++;
                    did(ja);
                    chap_hero(ja,color);
                    
                }
                else if(screen[ja.Z][ja.Y][ja.X + 1]  == '@'){
                    
                    for(int i = 0 ; i  < pdoor_pointer;i++){
                        if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y && door_pass[i].door.X == ja.X + 1){
                            sy = i;
                        }
                    }
                    
                    if(door_pass[sy].open == 1){
                        chap(ja.Z,ja.Y,ja.X,screen);
                        ja.X++;
                        did(ja);
                        chap_hero(ja,color);
                        
                    }
                    else{
                        sf.Z = ja.Z;
                        sf.Y = ja.Y;
                        sf.X =  ja.X + 1;

                        open_door(sf);
                    }
                }
                else if(screen[ja.Z][ja.Y][ja.X + 1] == '='){

                    sf.Z = ja.Z;
                    sf.Y = ja.Y;
                    sf.X =  ja.X + 1;
                    did(sf);
                    chap_hero(ja,color);

                }
                get(ja);
                state(ja);
                taskbar();
                refresh();
                break;
            case 'f':
                char g;
                g = getchar();

                switch (g){
                    case 'u':
                        while((screen[ja.Z][ja.Y - 1][ja.X + 1] == '#' || screen[ja.Z][ja.Y - 1][ja.X + 1] == '.' )&& 
                        trap[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            ja.X++;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'y':
                        while((screen[ja.Z][ja.Y - 1][ja.X - 1] == '#' || screen[ja.Z][ja.Y - 1][ja.X - 1] == '.' )&& 
                        trap[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'h':
                        while((screen[ja.Z][ja.Y][ja.X - 1] == '#' || screen[ja.Z][ja.Y][ja.X - 1] == '.' )&& 
                        trap[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'j':
                        while((screen[ja.Z][ja.Y - 1][ja.X ] == '#' || screen[ja.Z][ja.Y - 1][ja.X] == '.' )&& 
                        screen[ja.Z][ja.Y - 1][ja.X ] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'k':
                        while((screen[ja.Z][ja.Y + 1][ja.X] == '#' || screen[ja.Z][ja.Y + 1][ja.X] == '.' )&& 
                        screen[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'l':
                        while((screen[ja.Z][ja.Y][ja.X + 1] == '#' || screen[ja.Z][ja.Y][ja.X + 1] == '.' )&& 
                        screen[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.X++;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'b':
                        while((screen[ja.Z][ja.Y + 1][ja.X - 1] == '#' || screen[ja.Z][ja.Y + 1][ja.X - 1] == '.' )&& 
                        screen[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                    case 'n':
                        while((screen[ja.Z][ja.Y + 1][ja.X + 1] == '#' || screen[ja.Z][ja.Y + 1][ja.X + 1] == '.' )&& 
                        screen[ja.Z][ja.Y][ja.X] != '^'){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            ja.X++;
                            did(ja);
                            chap_hero(ja,color);
                            state(ja);
                            taskbar();
                            refresh();
                        }
                        break;
                }
                get(ja);

                break;
            case 'g':
                char s;
                s = getchar();

                switch(s){
                    case 'u':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                            enemy[i].place.X == ja.X + 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y - 1][ja.X + 1] != ' ' && screen[ja.Z][ja.Y - 1][ja.X + 1] != '|' && 
                        screen[ja.Z][ja.Y - 1][ja.X + 1] != '_' && screen[ja.Z][ja.Y - 1][ja.X + 1] != '@' && 
                        screen[ja.Z][ja.Y - 1][ja.X + 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            ja.X++;
                            did(ja);

                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X + 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X + 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                
                                ja.Y--;
                                ja.X++;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y - 1;
                                sf.X =  ja.X + 1;
                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X + 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y - 1;
                            sf.X =  ja.X + 1;
                            did(sf);
                            chap_hero(ja,color);
                        }
                        break;
                    case 'y':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                            enemy[i].place.X == ja.X - 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y - 1][ja.X - 1] != ' ' && screen[ja.Z][ja.Y - 1][ja.X - 1] != '|' && 
                        screen[ja.Z][ja.Y - 1][ja.X - 1] != '_' && screen[ja.Z][ja.Y - 1][ja.X - 1] != '@' &&
                        screen[ja.Z][ja.Y - 1][ja.X - 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X - 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X - 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                
                                ja.Y--;
                                ja.X--;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y - 1;
                                sf.X =  ja.X - 1;
                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X - 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y - 1;
                            sf.X =  ja.X - 1;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'h':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y && 
                            enemy[i].place.X == ja.X - 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y][ja.X - 1] != ' ' && screen[ja.Z][ja.Y][ja.X - 1] != '|' && 
                        screen[ja.Z][ja.Y][ja.X - 1] != '_' && screen[ja.Z][ja.Y][ja.X - 1] != '@' &&
                        screen[ja.Z][ja.Y][ja.X - 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y][ja.X - 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y && door_pass[i].door.X == ja.X - 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                
                                ja.X--;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y;
                                sf.X =  ja.X - 1;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y][ja.X - 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y;
                            sf.X =  ja.X - 1;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'j':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 && 
                            enemy[i].place.X == ja.X){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y - 1][ja.X] != ' ' && screen[ja.Z][ja.Y - 1][ja.X] != '|' && 
                        screen[ja.Z][ja.Y - 1][ja.X] != '_' && screen[ja.Z][ja.Y - 1][ja.X] != '@' &&
                        screen[ja.Z][ja.Y - 1][ja.X] !=  '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y--;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y - 1 && door_pass[i].door.X == ja.X){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                
                                ja.Y--;
                                did(ja);
                                chap_hero(ja,color);
                        
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y - 1;
                                sf.X =  ja.X;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y - 1][ja.X] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y - 1;
                            sf.X =  ja.X;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'k':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                            enemy[i].place.X == ja.X){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y + 1][ja.X] != ' ' && screen[ja.Z][ja.Y + 1][ja.X] != '|' && 
                        screen[ja.Z][ja.Y + 1][ja.X] != '_' && screen[ja.Z][ja.Y + 1][ja.X] != '@' && 
                        screen[ja.Z][ja.Y + 1][ja.X] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                ja.Y++;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y + 1;
                                sf.X = ja.X;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y + 1;
                            sf.X =  ja.X;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'l':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y && 
                            enemy[i].place.X == ja.X + 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y][ja.X + 1] != ' ' && screen[ja.Z][ja.Y][ja.X + 1] != '|' && 
                        screen[ja.Z][ja.Y][ja.X + 1] != '_' && screen[ja.Z][ja.Y][ja.X + 1] != '@' && 
                        screen[ja.Z][ja.Y][ja.X + 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.X++;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y][ja.X + 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y && door_pass[i].door.X == ja.X + 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                ja.X++;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y;
                                sf.X =  ja.X + 1;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y][ja.X + 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y;
                            sf.X =  ja.X + 1;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'n':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                            enemy[i].place.X == ja.X + 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y + 1][ja.X + 1] != ' ' && screen[ja.Z][ja.Y + 1][ja.X + 1] != '|' && 
                        screen[ja.Z][ja.Y + 1][ja.X + 1] != '_' && screen[ja.Z][ja.Y + 1][ja.X + 1] != '@' &&
                        screen[ja.Z][ja.Y + 1][ja.X + 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            ja.X++;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X + 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X + 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                ja.Y++;
                                ja.X++;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y + 1;
                                sf.X =  ja.X + 1;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X + 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y + 1;
                            sf.X =  ja.X + 1;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                    case 'b':
                        for(int i = 0 ; i < 13;i++){
                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + 1 && 
                            enemy[i].place.X == ja.X - 1){
                                k = 1;
                            }
                        }
                        if(screen[ja.Z][ja.Y + 1][ja.X - 1] != ' ' && screen[ja.Z][ja.Y + 1][ja.X - 1] != '|' && 
                        screen[ja.Z][ja.Y + 1][ja.X - 1] != '_' && screen[ja.Z][ja.Y + 1][ja.X - 1] != '@' &&
                        screen[ja.Z][ja.Y + 1][ja.X - 1] != '=' && k != 1){
                            chap(ja.Z,ja.Y,ja.X,screen);
                            ja.Y++;
                            ja.X--;
                            did(ja);
                            chap_hero(ja,color);
                            
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X - 1]  == '@'){
                            
                            for(int i = 0 ; i  < pdoor_pointer;i++){
                                if(door_pass[i].door.Z == ja.Z && door_pass[i].door.Y == ja.Y + 1 && door_pass[i].door.X == ja.X - 1){
                                    sy = i;
                                }
                            }
                            if(door_pass[sy].open == 1){
                                chap(ja.Z,ja.Y,ja.X,screen);
                                ja.Y++;
                                ja.X--;
                                did(ja);
                                chap_hero(ja,color);
                                
                            }
                            else{
                                sf.Z = ja.Z;
                                sf.Y = ja.Y + 1;
                                sf.X =  ja.X - 1;

                                open_door(sf);
                            }
                        }
                        else if(screen[ja.Z][ja.Y + 1][ja.X - 1] == '='){

                            sf.Z = ja.Z;
                            sf.Y = ja.Y + 1;
                            sf.X =  ja.X - 1;
                            did(sf);
                            chap_hero(ja,color);

                        }
                        break;
                }
                state(ja);
                taskbar();
                refresh();

                break;
            case 's':
                if(trap[ja.Z][ja.Y][ja.X - 1] == '^'){
                    mvprintw(ja.Y,ja.X - 1,"^");
                }
                if(trap[ja.Z][ja.Y - 1][ja.X - 1] == '^'){
                    mvprintw(ja.Y - 1,ja.X - 1,"^");
                }
                if(trap[ja.Z][ja.Y + 1][ja.X - 1] == '^'){
                    mvprintw(ja.Y + 1,ja.X - 1,"^");
                }
                if(trap[ja.Z][ja.Y - 1][ja.X] == '^'){
                    mvprintw(ja.Y - 1,ja.X,"^");
                }
                if(trap[ja.Z][ja.Y + 1][ja.X] == '^'){
                    mvprintw(ja.Y + 1,ja.X,"^");
                }
                if(trap[ja.Z][ja.Y - 1][ja.X + 1] == '^'){
                    mvprintw(ja.Y - 1,ja.X + 1,"^");
                }
                if(trap[ja.Z][ja.Y][ja.X + 1] == '^'){
                    mvprintw(ja.Y,ja.X + 1,"^");
                }
                if(trap[ja.Z][ja.Y + 1][ja.X + 1] == '^'){
                    mvprintw(ja.Y + 1,ja.X + 1,"^");
                }

                if(screen[ja.Z][ja.Y][ja.X - 1] == '?'){
                    mvprintw(ja.Y,ja.X - 1,"?");
                }
                if(screen[ja.Z][ja.Y - 1][ja.X - 1] == '?'){
                    mvprintw(ja.Y - 1,ja.X - 1,"?");
                }
                if(screen[ja.Z][ja.Y + 1][ja.X - 1] == '?'){
                    mvprintw(ja.Y + 1,ja.X - 1,"?");
                }
                if(screen[ja.Z][ja.Y - 1][ja.X] == '?'){
                    mvprintw(ja.Y - 1,ja.X,"?");
                }
                if(screen[ja.Z][ja.Y + 1][ja.X] == '?'){
                    mvprintw(ja.Y + 1,ja.X,"?");
                }
                if(screen[ja.Z][ja.Y - 1][ja.X + 1] == '?'){
                    mvprintw(ja.Y - 1,ja.X + 1,"?");
                }
                if(screen[ja.Z][ja.Y][ja.X + 1] == '?'){
                    mvprintw(ja.Y,ja.X + 1,"?");
                }
                if(screen[ja.Z][ja.Y + 1][ja.X + 1] == '?'){
                    mvprintw(ja.Y + 1,ja.X + 1,"?");
                }

                for(int i = 0 ; i < 13; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }
                refresh();
                break;
            case 'e':

                f = food_meno();


                clear();
                for(int i = 1 ;i < 30;i++){
                    for(int j = 0 ; j < 120;j++){
                        chap(ja.Z,i,j,save);
                    }
                    printw("\n");
                }
                chap_hero(ja,color);
                for(int i = 0 ; i < ene; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }
                
                if(f == 0){
                    mvprintw(0,5,"The cell is empty");
                }
                if(f == 1){
                    health -= 100;
                    mvprintw(0,5,"You ate rotten food");
                }
                if(f == 2){
                    if(hungry <= max_hungry - 500){
                        hungry += 500;
                    }
                    else{
                        hungry = max_hungry;
                    }
                    if(health <= max_health - 200){
                        health += 200;
                    }
                    else{
                        health = max_health;
                    }
                    mvprintw(0,5,"You ate Normal food");
                }
                if(f == 3){
                    if(hungry <= max_hungry - 500){
                        hungry += 500;
                    }
                    else{
                        hungry = max_hungry;
                    }
                    if(health <= max_health - 200){
                        health += 200;
                    }
                    else{
                        health = max_health;
                    }
                    food_power += 40;
                    mvprintw(0,5,"You ate Power food");
                }
                if(f == 4){
                    if(hungry <= max_hungry - 500){
                        hungry += 500;
                    }
                    else{
                        hungry = max_hungry;
                    }
                    if(health <= max_health - 200){
                        health += 200;
                    }
                    else{
                        health = max_health;
                    }
                    food_speed += 20;
                    mvprintw(0,5,"You ate Speed food");
                }
                taskbar();

                refresh();

                break;
            case 'i':
                
                w = weapon_meno();

                clear();
                for(int i = 1 ;i < 30;i++){
                    for(int j = 0 ; j < 120;j++){
                        chap(ja.Z,i,j,save);
                    }
                    printw("\n");
                }
                chap_hero(ja,color);
                for(int i = 0 ; i < ene; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }

                if(w == 0){
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"first put your weapon in your backpack!");
                }
                if(w == 1){
                    now_weapon = 1;
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"Mace is in your hand");
                }
                if(w == 2){
                    now_weapon = 2;
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"Sword is in your hand");
                }
                if(w == 3){
                    now_weapon = 3;
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"Dagger is in your hand");
                }
                if(w == 4){
                    now_weapon = 4;
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"Magic Wand is in your hand");
                }
                if(w == 5){
                    now_weapon = 5;
                    mvprintw(0,5,"                                                                                        ");
                    mvprintw(0,5,"Normal Arrow is in your hand");
                }
                
                taskbar();
                refresh();

                break;
            case 'w':
                now_weapon = 0;
                mvprintw(0,5,"                                                                               ");
                mvprintw(0,5,"weapon is in your bag. you do not have any weopon in hand.");
                refresh();
                break;
            case 'q':
                s = spell_meno();
                if(s == 1){
                    spell_health += 20;
                }
                if(s == 2){
                    spell_power += 40;
                }
                if(s == 3){
                    spell_speed += 10;
                }

                clear();

                for(int i = 1 ;i < 30;i++){
                    for(int j = 0 ; j < 120;j++){
                        chap(ja.Z,i,j,save);
                    }
                    printw("\n");
                }
                chap_hero(ja,color);
                for(int i = 0 ; i < ene; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }

                taskbar();
                refresh();

                break;
            case 'M':
                for(int i = 0 ; i < 30;i++){
                    for(int j = 0 ;j < 120;j++){
                        
                        chap(ja.Z,i,j,screen);
                    }
                    printw("\n");
                }
                chap_hero(ja,color);
                for(int i = 0 ; i < ene; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }
                taskbar();
                refresh();
                char fg ='p';
                while(fg != 'M'){
                    fg = getchar();
                }
                for(int i = 0 ; i < 30;i++){
                    for(int j = 0 ;j < 120;j++){
                        
                        chap(ja.Z,i,j,save);
                    }
                    printw("\n");
                }
                chap_hero(ja,color);
                for(int i = 0 ; i < ene; i++){
                    if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }
                taskbar();
                refresh();


                break;
            case '>':
                if(screen[ja.Z][ja.Y][ja.X] == '>'){

                    
                    ja.Y = downstairs[ja.Z].Y;
                    ja.X = downstairs[ja.Z].X;
                    ja.Z = downstairs[ja.Z].Z;

                    level++;

                    clear();
                    did(ja);

                    for(int i = 0; i < 30;i++){
                        for(int j = 0 ; j < 120;j++){
                            chap(ja.Z,i,j,save);
                        }
                        printw("\n");
                    }
                    

                    chap_hero(ja,color);
                    for(int i = 0 ; i < ene; i++){
                        if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                            mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                        }
                    }
                    state(ja);
                    taskbar();
                    


                    refresh();
                }
                break;
            case '<':
                if(screen[ja.Z][ja.Y][ja.X] == '<'){

                    
                    ja.Y = upstairs[ja.Z - 1].Y;
                    ja.X = upstairs[ja.Z - 1].X;
                    ja.Z = upstairs[ja.Z - 1].Z;

                    level--;

                    clear();

                    for(int i = 0; i < 30;i++){
                        for(int j = 0 ; j < 120;j++){
                            chap(ja.Z,i,j,save);
                        }
                        printw("\n");
                    }
                    chap_hero(ja,color);
                    for(int i = 0 ; i < ene; i++){
                        if(enemy[i].place.Z == ja.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                            mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                        }
                    }
                    state(ja);
                    taskbar();
                    refresh();
                }
                break;
            case 'B':
                if(kalam == 3){
                    mvprintw(0,5,"                                                                       ");
                    mvprintw(0,5,"your geust.you can not save the game");
                    refresh();
                }
                else{
                    save_game(ja);
                    return;
                }
                
                
            case ' ':
                char h = 'P';
                int ss = 0;
                switch(now_weapon){
                    case 0:
                        mvprintw(0,5,"                                                                                     ");
                        mvprintw(0,5,"You do not have any weapon in your hand !!");
                        break;
                    case 1:
                        for(int i = 0 ; i < ene;i++){
                            for(int j = 0 ; j < 3;j++){
                                for(int h = 0 ; h < 3;h++){
                                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 + j && 
                                    enemy[i].place.X == ja.X - 1 + h){
                                        if(spell_power > 0 && food_power > 0){
                                            enemy[i].joon -= 20;
                                        } 
                                        else if(spell_power > 0){
                                            enemy[i].joon -= 10;
                                        }
                                        else if(food_power > 0){
                                            enemy[i].joon -= 10;
                                        }
                                        else{
                                            enemy[i].joon -= 5;
                                        }
                                        
                                        if(enemy[i].joon <= 0){
                                            mvprintw(0,5,"                                                                                         ");
                                            mvprintw(0,5,"enemy is dead");
                                            chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                            enemy[i].place.Z = 100;
                                        }
                                    }

                                }
                            }
                        }
                        break;
                    case 2:
                        for(int i = 0 ; i < ene;i++){
                            for(int j = 0 ; j < 3;j++){
                                for(int h = 0 ; h < 3;h++){
                                    if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 + j && 
                                    enemy[i].place.X == ja.X - 1 + h){

                                        if(spell_power > 0 && food_power > 0){
                                            enemy[i].joon -= 40;
                                        } 
                                        else if(spell_power > 0){
                                            enemy[i].joon -= 20;
                                        }
                                        else if(food_power > 0){
                                            enemy[i].joon -= 20;
                                        }
                                        else{
                                            enemy[i].joon -= 10;
                                        }
                                        
                                        if(enemy[i].joon <= 0){
                                            mvprintw(0,5,"                                                                                         ");
                                            mvprintw(0,5,"enemy is dead");
                                            chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                            enemy[i].place.Z = 100;
                                        }
                                    }

                                }
                            }
                        }
                        break;
                    case 3:
                        if(weapon[1] == 0){
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"you do not have any Dagger !");
                        }
                        else{
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"choose direction");
                            refresh();
                            weapon[1]--;
                            h = getchar();
                            switch(h){
                                case 'u':
                                    for(int j = 1;j <= 5;j++){
                                        for(int i = 0 ;j < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y - j + 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X + j - 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y - 5][ja.X + 5]++;
                                        mvprintw(ja.Y - 5,ja.X + 5,"2");
                                    }

                                    break;
                                case 'y':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y - j + 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X - j + 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y - 5][ja.X - 5]++;
                                        mvprintw(ja.Y - 5,ja.X - 5,"2");
                                    }
                                    break;
                                case 'h':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y][ja.X - j + 1]++;
                                                mvprintw(ja.Y,ja.X - j + 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y][ja.X - 5]++;
                                        mvprintw(ja.Y,ja.X - 5,"2");
                                    }
                                    break;
                                case 'j':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y - j + 1][ja.X]++;
                                                mvprintw(ja.Y - j + 1,ja.X,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y - 5][ja.X]++;
                                        mvprintw(ja.Y - 5,ja.X,"2");
                                    }
                                    break;
                                case 'k':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y + j - 1][ja.X]++;
                                                mvprintw(ja.Y + j - 1,ja.X,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y + 5][ja.X]++;
                                        mvprintw(ja.Y + 5,ja.X,"2");
                                    }
                                    break;
                                case 'l':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y][ja.X + j - 1]++;
                                                mvprintw(ja.Y,ja.X + j - 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y][ja.X + 5]++;
                                        mvprintw(ja.Y,ja.X + 5,"2");
                                    }
                                    break;
                                case 'b':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y + j - 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X - j + 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y + 5][ja.X - 5]++;
                                        mvprintw(ja.Y + 5,ja.X - 5,"2");
                                    }
                                    break;
                                case 'n':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 48;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 24;
                                                }
                                                else{
                                                    enemy[i].joon -= 12;
                                                }

                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == ' '){
                                                ss = 1;
                                                dagger[ja.Z][ja.Y + j - 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X + j - 1,"2");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        dagger[ja.Z][ja.Y + 5][ja.X + 5]++;
                                        mvprintw(ja.Y + 5,ja.X + 5,"2");
                                    }
                                    break;
                                default:
                                    mvprintw(0,5,"                                                                      ");
                                    mvprintw(0,5,"select correct direction");
                                    weapon[1]++;
                            }
                        }
                        
                        break;
                    case 4:
                        if(weapon[2] == 0){
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"you do not have any Magic Wand");
                        }
                        else{
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"choose direction");
                            refresh();
                            weapon[2]--;
                            h = getchar();
                            switch(h){
                                case 'u':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y - j + 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X + j - 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y - 5][ja.X + 5]++;
                                        mvprintw(ja.Y - 5,ja.X + 5,"3");
                                    }

                                    break;
                                case 'y':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y - j + 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X - j + 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y - 5][ja.X - 5]++;
                                        mvprintw(ja.Y - 5,ja.X - 5,"3");
                                    }
                                    break;
                                case 'h':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y][ja.X - j + 1]++;
                                                mvprintw(ja.Y,ja.X - j + 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y][ja.X - 5]++;
                                        mvprintw(ja.Y,ja.X - 5,"3");
                                    }
                                    break;
                                case 'j':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y - j + 1][ja.X]++;
                                                mvprintw(ja.Y - j + 1,ja.X,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y - 5][ja.X]++;
                                        mvprintw(ja.Y - 5,ja.X,"3");
                                    }
                                    break;
                                case 'k':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y + j - 1][ja.X]++;
                                                mvprintw(ja.Y + j - 1,ja.X,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y + 5][ja.X]++;
                                        mvprintw(ja.Y + 5,ja.X,"3");
                                    }
                                    break;
                                case 'l':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y][ja.X + j - 1]++;
                                                mvprintw(ja.Y,ja.X + j - 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y][ja.X + 5]++;
                                        mvprintw(ja.Y,ja.X + 5,"3");
                                    }
                                    break;
                                case 'b':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y + j - 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X - j + 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y + 5][ja.X - 5]++;
                                        mvprintw(ja.Y + 5,ja.X - 5,"3");
                                    }
                                    break;
                                case 'n':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 60;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 30;
                                                }
                                                else{
                                                    enemy[i].joon -= 15;
                                                }
                                                
                                                enemy[i].movement = 0;
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == ' '){
                                                ss = 1;
                                                magic[ja.Z][ja.Y + j - 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X + j - 1,"3");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        magic[ja.Z][ja.Y + 5][ja.X + 5]++;
                                        mvprintw(ja.Y + 5,ja.X + 5,"3");
                                    }
                                    break;
                                default:
                                    mvprintw(0,5,"                                                                      ");
                                    mvprintw(0,5,"select correct direction");
                                    weapon[2]++;
                            }
                        }
                        
                        break;
                    case 5:
                        if(weapon[3] == 0){
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"you do not have any Normal Arrow !");
                        }
                        else{
                            mvprintw(0,5,"                                                                                 ");
                            mvprintw(0,5,"choose direction");
                            refresh();
                            weapon[3]--;
                            h = getchar();
                            switch(h){
                                case 'u':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X + j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y - j + 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X + j - 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y - 5][ja.X + 5]++;
                                        mvprintw(ja.Y - 5,ja.X + 5,"4");
                                    }

                                    break;
                                case 'y':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X - j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y - j + 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y - j + 1,ja.X - j + 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y - 5][ja.X - 5]++;
                                        mvprintw(ja.Y - 5,ja.X - 5,"4");
                                    }
                                    break;
                                case 'h':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X - j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y][ja.X - j + 1]++;
                                                mvprintw(ja.Y,ja.X - j + 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y][ja.X - 5]++;
                                        mvprintw(ja.Y,ja.X - 5,"4");
                                    }
                                    break;
                                case 'j':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y - j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y - j][ja.X] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y - j + 1][ja.X]++;
                                                mvprintw(ja.Y - j + 1,ja.X,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y - 5][ja.X]++;
                                        mvprintw(ja.Y - 5,ja.X,"4");
                                    }
                                    break;
                                case 'k':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y + j - 1][ja.X]++;
                                                mvprintw(ja.Y + j - 1,ja.X,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y + 5][ja.X]++;
                                        mvprintw(ja.Y + 5,ja.X,"4");
                                    }
                                    break;
                                case 'l':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y ][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y][ja.X + j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y][ja.X + j - 1]++;
                                                mvprintw(ja.Y,ja.X + j - 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y][ja.X + 5]++;
                                        mvprintw(ja.Y,ja.X + 5,"4");
                                    }
                                    break;
                                case 'b':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X - j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X - j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X - j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y + j - 1][ja.X - j + 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X - j + 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y + 5][ja.X - 5]++;
                                        mvprintw(ja.Y + 5,ja.X - 5,"4");
                                    }
                                    break;
                                case 'n':
                                    for(int j = 1 ; j <= 5;j++){
                                        for(int i = 0 ;i < ene;i++){
                                            if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y + j &&
                                            enemy[i].place.X == ja.X + j){
                                                ss = 1;
                                                mvprintw(0,5,"                                                                             ");
                                                mvprintw(0,5,"you  hit the enemy");
                                                if(spell_power > 0 && food_power > 0){
                                                    enemy[i].joon -= 20;
                                                } 
                                                else if(spell_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else if(food_power > 0){
                                                    enemy[i].joon -= 10;
                                                }
                                                else{
                                                    enemy[i].joon -= 5;
                                                }
                                                
                                                if(enemy[i].joon <= 0){
                                                    mvprintw(0,5,"                                                                                        ");
                                                    mvprintw(0,5,"you  hit the enemy.enemy is dead");
                                                    chap(enemy[i].place.Z,enemy[i].place.Y,enemy[i].place.X,screen);
                                                    enemy[i].place.Z = 100;
                                                }
                                                break;
                                            }
                                            else if(screen[ja.Z][ja.Y + j][ja.X + j] == '|' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '_' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '+' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '=' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '?' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == '@' ||
                                            screen[ja.Z][ja.Y + j][ja.X + j] == ' '){
                                                ss = 1;
                                                arrow[ja.Z][ja.Y + j - 1][ja.X + j - 1]++;
                                                mvprintw(ja.Y + j - 1,ja.X + j - 1,"4");
                                                chap_hero(ja,color);
                                                break;
                                            }
                                        }
                                        if(ss == 1){
                                            break;
                                        }
                                    }
                                    if(ss == 0){
                                        arrow[ja.Z][ja.Y + 5][ja.X + 5]++;
                                        mvprintw(ja.Y + 5,ja.X + 5,"4");
                                    }
                                    break;
                                default:
                                    mvprintw(0,5,"                                                                      ");
                                    mvprintw(0,5,"select correct direction");
                                    weapon[3]++;
                            }
                        }
                        
                        break;
                }

                get(ja);
                state(ja);
                taskbar();
                refresh();

                break;
            case 'a':
                if(b_key > 1){
                    b_key -= 2;
                    key++;
                    mvprintw(0,5,"                                                                                ");
                    mvprintw(0,5,"you made a key");
                }
                else{
                    mvprintw(0,5,"                                                                                ");
                    mvprintw(0,5,"you do not have enough broken key");
                }

                state(ja);
                taskbar();
                refresh();

                break;
        
        
        }
        
        if(health <= 0){
            clear();
            attron(COLOR_PAIR(2) | A_BOLD);
            mvprintw(15,57,"YOU LOSE");
            attroff(COLOR_PAIR(2) | A_BOLD);
            mvprintw(16,57,"Score = %d",score);
            if(kalam < 3){
                total_score += score;
                mvprintw(17,57,"your total score = %d",total_score);
                end_game();
            }
            refresh();
            getchar();
            return;
        }
        
        win = 1;
        for(int i = 12 ; i < ene;i++){
            if(enemy[i].joon > 0){
                win = 0;
            }
        }
    
        if(win == 1){
            score += 100;
            clear();
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(15,57,"YOU WIN");
            attroff(COLOR_PAIR(3) | A_BOLD);
            mvprintw(16,57,"Score = %d",score);
            if(kalam < 3){
                total_score += score;
                mvprintw(17,57,"your total score = %d",total_score);
                end_game();
            }
            refresh();
            getchar();
            return;
        }

        L = in_kab(ja);
        
        if(L > -1){
            move(1,0);
            for(int i = 1 ; i < 30;i++){
                for(int j = 0 ; j < 120;j++){
                    printw(" ");
                }
            }
            for(int t = 0 ; t < 3;t++){
                for(int d = 0;d < 3;d++){
                    
                    chap(ja.Z,ja.Y - 1 + t,ja.X - 1 + d,screen);
                    
                    for(int i = 0 ; i < ene;i++){
                        if(enemy[i].place.Z == ja.Z && enemy[i].place.Y == ja.Y - 1 + t &&
                        enemy[i].place.X == ja.X - 1 + d){
                            mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                        }
                    }
                    refresh();
                }
            }
            chap_hero(ja,color_hero);
            get(ja);
            taskbar();

            refresh();

        }
        
        
    }

    

}

void new_game(){
    

    room lak[4][6];
    

    for(int i = 0 ; i < 4;i++){
        otagh[i] = make_room(lak[i],i);
    }
    clear();

    

    for(int i = 0 ; i < 4;i++){
        make_winddow(otagh[i]);
        make_floor(otagh[i]);
    }

    

    point f[4][6],bikhod[4][6],pp[4],ash[4];
    int y = 0;
    

    for(int i = 0 ; i < 4;i++){
        y = rand() % 6;
        sec[i] = y;
    }

    for(int i = 0 ; i < 4;i++){
        do{
            y = rand() % 6;
        }while(y == sec[i]);
        kab[i] = y;
    }

    for(int i = 0 ; i < 4;i++){
        y = rand() % 6;
        pas[i] = y;
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0;j < 4;j++){
            make_spell(otagh[i][sec[i]]);
        }
    }

    for(int i = 0 ;i < 4;i++){
        for(int j = 0 ; j < 6;j++){
            make_food(otagh[i][j]);
        }
    }

    int w[3];
    for(int i = 0;i < 4;i++){
        for(int j = 0 ;j < 3;j++){
            w[j] = rand() %3;
            make_weapon(otagh[i][w[j]]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 6;j++){
            make_gold(otagh[i][j]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 2 ;j++){
            w[j] = rand() %2;
            make_blackgold(otagh[i][w[j]]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        w[0] = rand() %2;
        if(w[0] == 0){
            make_upstairs(otagh[i][2]);
        }
        else{
            make_upstairs(otagh[i][5]);
        }
    }

    for(int i = 1  ; i < 4;i++){
        make_downstairs(otagh[i][0]);
    }



    for(int i = 0 ; i < 4;i++){
        w[0] = rand() %6;
        make_key(otagh[i][0]);
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 6;j++){

            if(sec[i] == j){
                f[i][j] = secret_door(otagh[i][j],bikhod[i][j]);
            }
            else if(j != 0 || pas[i] != 0){
                f[i][j] = make_door(otagh[i][j],bikhod[i][j]);
            }

            
        }
    }

    for(int i = 0 ; i < 4;i++){
        pp[i] = pass_door(otagh[i][pas[i]],ash[i]);
    }


    int z[4];
    
    for(int i = 0 ; i < 4;i++){
        z[i] = rand()  % 10;
        door_pass[2].passwordtwo[i] = 48 + z[i];
    }
    
    door_pass[2].passwordtwo[4] = '\0';

    for(int i = 0 ; i < 4;i++){
        z[i] = rand()  % 10;
        door_pass[3].passwordtwo[i] = 48 + z[i];
    }
    
    door_pass[3].passwordtwo[4] = '\0';

    
    make_road(pas,pp,f);

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 3;j++){
            y = rand() %6;
            make_enemy(otagh[i][y]);
        }
    }

    for(int i = 0 ; i < 30;i++){
        for(int j = 0 ; j < 120;j++){
            screen[4][i][j] = ' ';
        }
    }

    ganj_room();

    for(int h = 0  ; h < 5;h++){
        clear();
        for(int i  = 0; i < 30;i++){
            for(int j = 0 ; j < 120;j++){
                chap(h,i,j,screen);
            }
        }
        refresh();
        getchar();
    }
    clear();


    adam = put_hero(otagh[0][0]);
    
    for(int i  = 0; i < 30;i++){
        for(int j = 0 ; j < 120;j++){
            chap(0,i,j,save);
        }
    }
    chap_hero(adam,color_hero);

    for(int i = 0 ;i < ene;i++){
        if(enemy[i].place.Z == adam.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
            mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
        }
    }
    

    refresh();
    

    play(adam,color_hero);


    



}

int resume_game(){
    char a;
    info = fopen(acount_file,"r");

    fgets(gmail,1000,info);
    fgets(enter_pass,1000,info);
    fscanf(info,"%d",&total_score);
    fscanf(info,"%d",&game_played);
    fscanf(info,"%ld",&signup_time);
    fscanf(info,"%d",&sign);

    fscanf(info,"%d",&adam.Z);
    fscanf(info,"%d",&adam.Y);
    fscanf(info,"%d",&adam.X);

    fscanf(info,"%c",&a);
    for(int i = 0 ; i < 5;i++){
        for(int j = 0;j < 30;j++){
            for(int h = 0;h < 120;h++){
                fscanf(info,"%c",&screen[i][j][h]);
            }
            fscanf(info,"%c",&a);
        }
        fscanf(info,"%c",&a);
        fscanf(info,"%c",&a);
    }
    /*
    for(int i = 0 ; i < 5;i++){
        clear();
        move(0,0);
        for(int j = 0; j < 30;j++){
            for(int h = 0;h < 120;h++){
                //printw("%c",screen[i][j][h]);
                chap(i,j,h,screen);
                refresh();
                //getchar();
            }
        }
        refresh();
        getchar();
    }

    */
    
    for(int i = 0 ; i < 5;i++){
        for(int j = 0;j < 30;j++){
            for(int h = 0;h < 120;h++){
                fscanf(info,"%c",&save[i][j][h]);
            }
            fscanf(info,"%c",&a);
        }
        fscanf(info,"%c",&a);
        fscanf(info,"%c",&a);
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fscanf(info,"%c",&trap[i][j][h]);
            }
        }
    }

    for(int i = 0 ;i < 4;i++){
        fscanf(info,"%c",&door_pass[2].passwordtwo[i]);
    }

    for(int i = 0 ;i < 4;i++){
        fscanf(info,"%c",&door_pass[3].passwordtwo[i]);
    }

    door_pass[2].passwordtwo[4] = '\0';
    door_pass[3].passwordtwo[4] = '\0';
    door_pass[0].password[4] = '\0';
    door_pass[1].password[4] = '\0';
    door_pass[2].password[4] = '\0';
    door_pass[3].password[4] = '\0';

    for(int i = 0 ; i < 4;i++){
        otagh[i] = (room *)malloc(6 * sizeof(room));
    }

    
    for(int i = 0 ; i < 4;i++){
        for(int j = 0;j < 6;j++){
            fscanf(info,"%d",&otagh[i][j].up_left.X);
            fscanf(info,"%d",&otagh[i][j].up_left.Y);
            fscanf(info,"%d",&otagh[i][j].difference.X);
            fscanf(info,"%d",&otagh[i][j].difference.Y);
            fscanf(info,"%d",&otagh[i][j].floor);

            
        }
    }
    

    fscanf(info,"%d",&ganj.up_left.X);
    fscanf(info,"%d",&ganj.up_left.Y);
    fscanf(info,"%d",&ganj.difference.X);
    fscanf(info,"%d",&ganj.difference.Y);
    fscanf(info,"%d",&ganj.floor);

    for(int i = 0;i < 4;i++){
        fscanf(info,"%d",&sec[i]);
    }

    for(int i = 0;i < 4;i++){
        fscanf(info,"%d",&kab[i]);
    }

    for(int i = 0;i < 4;i++){
        fscanf(info,"%d",&pas[i]);
    }

    for(int i = 0; i < 4;i++){
        fscanf(info,"%d",&downstairs[i].Z);
        fscanf(info,"%d",&downstairs[i].Y);
        fscanf(info,"%d",&downstairs[i].X);
    }

    for(int i = 0 ; i < 4;i++){
        fscanf(info,"%d",&upstairs[i].Z);
        fscanf(info,"%d",&upstairs[i].Y);
        fscanf(info,"%d",&upstairs[i].X);
    }

    fscanf(info,"%d",&pdoor_pointer);

    

    for(int i = 0 ; i < pdoor_pointer;i++){
        fscanf(info,"%d",&door_pass[i].door.Z);
        fscanf(info,"%d",&door_pass[i].door.Y);
        fscanf(info,"%d",&door_pass[i].door.X);
        fscanf(info,"%d",&door_pass[i].pass_maker.Z);
        fscanf(info,"%d",&door_pass[i].pass_maker.Y);
        fscanf(info,"%d",&door_pass[i].pass_maker.X);
        
        if(i >= 2){
            fscanf(info,"%d",&door_pass[i].pass_makertwo.Z);
            fscanf(info,"%d",&door_pass[i].pass_makertwo.Y);
            fscanf(info,"%d",&door_pass[i].pass_makertwo.X);
        }
        
        

        
        

        fscanf(info,"%d",&door_pass[i].open);
        fscanf(info,"%d",&door_pass[i].try);


    }
    

    fscanf(info,"%d",&ene);
    clear();
    for(int i = 0;i < ene;i++){
        fscanf(info,"%c",&a);
        fscanf(info,"%c",&enemy[i].type);
        fscanf(info,"%d",&enemy[i].joon);
        fscanf(info,"%d",&enemy[i].place.Z);
        fscanf(info,"%d",&enemy[i].place.Y);
        fscanf(info,"%d",&enemy[i].place.X);
        fscanf(info,"%d",&enemy[i].power);
        fscanf(info,"%d",&enemy[i].movement);
        fscanf(info,"%d",&enemy[i].sign);
        
        mvprintw(i,0,"%c",enemy[i].type);
        mvprintw(i,5,"%d",enemy[i].joon);
        mvprintw(i,10,"%d",enemy[i].movement);
        refresh();

    }
    getchar();

    fscanf(info,"%d",&mus);
    fscanf(info,"%d",&en_st);
    fscanf(info,"%d",&now_weapon);
    fscanf(info,"%d",&color_hero);
    fscanf(info,"%d",&spell_speed);
    fscanf(info,"%d",&spell_power);
    fscanf(info,"%d",&spell_health);
    fscanf(info,"%d",&food_speed);
    fscanf(info,"%d",&food_power);
    fscanf(info,"%d",&b_key);
    fscanf(info,"%d",&key);
    fscanf(info,"%d",&level);
    fscanf(info,"%d",&score);
    fscanf(info,"%d",&gold);
    fscanf(info,"%d",&max_hungry);
    fscanf(info,"%d",&hungry);
    fscanf(info,"%d",&max_health);
    fscanf(info,"%d",&health);

    for(int i = 0 ;i < 5;i++){
        fscanf(info,"%d",&food[i].type);
        fscanf(info,"%d",&food[i].time);
        fscanf(info,"%d",&food[i].expiration);
    }

    for(int i = 0;i < 3;i++){
        fscanf(info,"%d",&spell[i]);
    }

    for(int i = 0 ; i < 5;i++){
        fscanf(info,"%d",&weapon[i]);
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fscanf(info,"%d",&arrow[i][j][h]);
                
            }
        }
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fscanf(info,"%d",&magic[i][j][h]);
                
            }
        }
    }

    for(int i = 0 ; i < 5;i++){
        for(int j = 0 ;j < 30;j++){
            for(int h = 0; h < 120;h++){
                fscanf(info,"%d",&dagger[i][j][h]);
            }
        }
    }

    

    fclose(info);
}

int main(int argc, char *argv[])
{
    srand(time(0));

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
        return 1;
    }

    music[0] = Mix_LoadMUS("1. Dr. Dre, Snoop Dogg - Still D.R.E. (320) (1).mp3");
    music[1] = Mix_LoadMUS("Saeid Asayesh - Mohre Mar (320).mp3");
    music[2] = Mix_LoadMUS("02 Shadow Warriors.mp3");
    for(int i = 0;i < 3;i++){
            if(music[i] == NULL){
            fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
            return 1;
        }
    }



    for(int h = 0 ; h < 5;h++){
        for(int i = 0  ; i < 30;i++){
            for(int j = 0 ; j  < 120;j++){
            screen[h][i][j] =  ' ';
            save[h][i][j] = ' ';
            trap[h][i][j] = ' ';
            }
        }
    }

    
    char skiip[1000] = {};

    int men = 1;

    initscr();
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);

    init_pair(7,COLOR_WHITE,COLOR_BLUE);
    init_pair(8,COLOR_WHITE,COLOR_RED);
    init_pair(9,COLOR_WHITE,COLOR_GREEN);
    init_pair(10,COLOR_WHITE,COLOR_YELLOW);
    init_pair(11,COLOR_WHITE,COLOR_MAGENTA);

    curs_set(0);
    refresh();

    
    kalam = frist_meno();
    if(kalam == 1){
        acount_file = signup(skiip);
    }
    else if(kalam == 2){
        acount_file = signin(skiip);
    }
    
    if(kalam < 3){
        strcpy(acount_user,acount_file);
        for(int i = 0;i < 4;i++){
            acount_user[strlen(acount_user) - 1] = '\0';
        }
        info = fopen(acount_file,"r");
        fgets(gmail,1000,info);
        fgets(enter_pass,1000,info);
        fscanf(info,"%d",&total_score);
        fscanf(info,"%d",&game_played);
        fscanf(info,"%ld",&signup_time);
        fscanf(info,"%d",&sign);
        fclose(info);
    }
    
    while(men != 0){
        men = meno();
        if(men == 0){
            new_game();
        }
        else if(men == 1){
            if(sign == 0){
                clear();
                mvprintw(15,55,"You do not have any saved game!");
                refresh();
                getchar();
            }
            else{
                
                resume_game();
                
                
                for(int i  = 0; i < 30;i++){
                    for(int j = 0 ; j < 120;j++){
                        chap(adam.Z,i,j,save);
                        refresh();
                    }
                }
                
                chap_hero(adam,color_hero);

                for(int i = 0 ;i < ene;i++){
                    if(enemy[i].place.Z == adam.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
                        mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
                    }
                }
                refresh();
                play(adam,color_hero);
                break;
                
            }
            
        }
        else if(men == 2){
            scoreboard(acount_user);
        }
        else if(men == 3){
            setting_meno();
        }
        else if(men == 4){
            clear();
            if(kalam == 3){
                mvprintw(15,50,"You are geust");
            }
            else{
                mvprintw(5,15,"usrename : %s",acount_user);
                mvprintw(10,15,"gmail : %s",gmail);
                mvprintw(15,15,"password : %s",enter_pass);
                mvprintw(20,15,"Total score : %d",total_score);
                mvprintw(25,20,"Exprince : %s",exprincee(signup_time));
            }
            refresh();
            getchar();
        }
    }

    /*

    char b[1000],d[1000],skip[1000],m[1000];
    int lo[5],lip;
    char *a;
    FILE *user;
    room * ko;
    room c[6];
    point doo[6] , po[6],jil,sr;
    pdoor_pointer = 0;
    


    

    //user = fopen("username.txt","r");
    //po = (point *)malloc(6 * sizeof(point));
    //ko = (room *)malloc(6 * sizeof(room));
    //mvprintw(29,119,"#");
    //refresh();
    //scanw("%s",b);
    //a =signup(b);
    //a = signin(b);
    //scoreboard(a);
    //lo = sakhti();
    //scanf("%s",c);
    //lip = hero_color();
    //clear();
    
    //lo = meno();
    
    
    room lak[4][6];
    

    for(int i = 0 ; i < 4;i++){
        otagh[i] = make_room(lak[i],i);
    }
    clear();

    

    for(int i = 0 ; i < 4;i++){
        make_winddow(otagh[i]);
        make_floor(otagh[i]);
    }

    

    point f[4][6],bikhod[4][6],pp[4],ash[4];
    int y = 0;
    

    for(int i = 0 ; i < 4;i++){
        y = rand() % 6;
        sec[i] = y;
    }

    for(int i = 0 ; i < 4;i++){
        y = rand() % 6;
        pas[i] = y;
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0;j < 4;j++){
            make_spell(otagh[i][sec[i]]);
        }
    }

    for(int i = 0 ;i < 4;i++){
        for(int j = 0 ; j < 6;j++){
            make_food(otagh[i][j]);
        }
    }

    int w[3];
    for(int i = 0;i < 4;i++){
        for(int j = 0 ;j < 3;j++){
            w[j] = rand() %3;
            make_weapon(otagh[i][w[j]]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 6;j++){
            make_gold(otagh[i][j]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 2 ;j++){
            w[j] = rand() %2;
            make_blackgold(otagh[i][w[j]]);
        }
    }

    for(int i = 0 ; i < 4;i++){
        w[0] = rand() %2;
        if(w[0] == 0){
            make_upstairs(otagh[i][2]);
        }
        else{
            make_upstairs(otagh[i][5]);
        }
    }

    for(int i = 1  ; i < 4;i++){
        make_downstairs(otagh[i][0]);
    }



    for(int i = 0 ; i < 4;i++){
        w[0] = rand() %6;
        make_key(otagh[i][0]);
    }

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 6;j++){

            if(sec[i] == j){
                f[i][j] = secret_door(otagh[i][j],bikhod[i][j]);
            }
            else if(j != 0 || pas[i] != 0){
                f[i][j] = make_door(otagh[i][j],bikhod[i][j]);
            }

            
        }
    }

    for(int i = 0 ; i < 4;i++){
        pp[i] = pass_door(otagh[i][pas[i]],ash[i]);
    }


    int z[4];
    
    for(int i = 0 ; i < 4;i++){
        z[i] = rand()  % 10;
        door_pass[2].passwordtwo[i] = 48 + z[i];
    }
    
    door_pass[2].passwordtwo[4] = '\0';

    for(int i = 0 ; i < 4;i++){
        z[i] = rand()  % 10;
        door_pass[3].passwordtwo[i] = 48 + z[i];
    }
    
    door_pass[3].passwordtwo[4] = '\0';

    
    make_road(pas,pp,f);

    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 3;j++){
            y = rand() %6;
            make_enemy(otagh[i][y]);
        }
    }

    for(int i = 0 ; i < 30;i++){
        for(int j = 0 ; j < 120;j++){
            screen[4][i][j] = ' ';
        }
    }

    ganj_room();

    for(int h = 0  ; h < 5;h++){
        clear();
        for(int i  = 0; i < 30;i++){
            for(int j = 0 ; j < 120;j++){
                chap(h,i,j,screen);
            }
        }
        refresh();
        getchar();
    }
    clear();


    adam = put_hero(otagh[0][0]);
    
    for(int i  = 0; i < 30;i++){
        for(int j = 0 ; j < 120;j++){
            chap(0,i,j,save);
        }
    }
    chap_hero(adam,color_hero);

    for(int i = 0 ;i < ene;i++){
        if(enemy[i].place.Z == adam.Z && enemy[i].sign == 1 && enemy[i].joon > 0){
            mvprintw(enemy[i].place.Y,enemy[i].place.X,"%c",enemy[i].type);
        }
    }
    

    refresh();
    

    play(adam,color_hero);
    

    /*

    for(int h = 0 ; h < 4;h++){
        for(int i = 0  ; i < 30;i++){
            for(int j = 0 ; j  < 120;j++){
            screen[h][i][j] =  ' ';
            save[h][i][j] = ' ';
            }
        }
    }

    ko = make_room(c,0);
    for(int i = 0 ;i < 6;i++){
        po[i] = make_door(ko[i],doo[i]);
    }
    sr = secret_door(ko[1],jil);
    make_winddow(ko);
    make_floor(ko);
    make_trap(ko[0]);
    
    refresh();
    rah(po[5],po[0],0);
    rah(po[1],po[3],0);
    rah(po[3],po[4],0);
    rah(po[0],po[3],0);
    rah(po[2],po[5],0);
    refresh();
    //play(adam);
    make_gold(ko[3]);
    make_key(ko[3]);
    make_blackgold(ko[3]);
    jil = pass_door(ko[0],jil);
    make_blackgold(ko[5]);
    rah(jil,sr,0);
    //rah(po[1],jil,0);
    //rah(po,0,1);
    refresh();
    clear();

    
    move(0,0);
    for(int i = 0 ; i < 30;i++){
        
        for(int j = 0 ; j < 120;j++){
            
            chap(0,i,j,screen);
        }
        printw("\n");
    }
    taskbar();
    chap_hero(adam,color_hero);

    

    refresh();
    play(adam,color_hero);
    //rah(po,2,1);
    //rah(po,3,2);
    //rah(po,5,2);
    //rah(po,4,3);
    //make_road(ko,po);
    refresh();*/
    getchar();
    endwin();


    return 0;
}



