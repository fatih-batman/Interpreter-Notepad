#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



bool isDelimiter(char c)
{
    if (c == ' ' || c == '*' || c== '/'
        || c == ';' || c == '>' ||
        c == '<' || c == '{' || c == '}')
        return (true);
    return (false);
}

char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                sizeof(char) * (right - left + 2));



    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}



bool isDataTypes(char* str){

    int len=strlen(str);
    int i=0;
    int start=0;
    for(i;i<len;i++){
        if(str[i]=='<' && start==0){
            start=1;
        }
        else if(str[i]=='>' && start==1){
            return (true);
        }
    }
    return false;
}

bool isBasicCommands(char* str){  //commandsların block yapıları anlaşılmadı??
    int len=strlen(str);
    int i=0;
    int start=0;
    for(i;i<len;i++){
        if( ( (str[i]=='m' && str[i+1]=='a' && str[i+2]=='k' && str[i+3]=='e')
        || (str[i]=='g' && str[i+1]=='o') ) && start==0)  start=1;
        else if(str[i]==';' && start==1 ) return (true);
    }
    return false;
}


bool isControlStructures(char* str){   //düzeltilmesi gerekiyor.

    int len=strlen(str);
    int i=0;
    int start=0;
    int bracket=0;
    for(i;i<len;i++){
        if( ( (str[i]=='i' && str[i+1]=='f' && str[i+2]=='n' && str[i+3]=='o'
               && str[i+4]=='t')
        || (str[i]=='i' && str[i+1]=='f') ) && start==0) {
            start=1;
        }   // str nin içini kontrol etme mekanizması??

        else{
        if(str[i]=='{' ) bracket++;
        else if(str[i]=='}' && bracket==1)return true;
        if( isDataTypes(str) && start==1 ) start++;
        else if( isBasicCommands(str) && start==2 ) return (true);
        }
    }
    return false;


 /*   if ( (str[0]=='i' && str[1]=='f' && str[2]=='n' && str[3]=='o'
               && str[4]=='t') || (str[0]=='i' && str[1]=='f')    ){
                    int len=strlen(str);
                    int start=1;
                    int bracket=0;
                        for(int i=0;i<=len;i++){
                            if(str[i]=='{')  bracket++;
                        if(str[i]=='}' && bracket==1) return true;   //right++ varmı muallak
                        if (i==len && bracket==1) printf("ERROR! Control Structure cannot terminate before the file end.\n");
                                                   }

                        if(bracket==0){
                        for(int j=0;j<=len;j++){
                        if (str[j]==';' && start==1) return true;
                        if (j==len) printf("ERROR! Control Structure without block cannot terminate before the file end.\n");  }
                                      }                                             }  */
                                        }



            void applyBasicCommands2 (char str[],int boyut){

                    for (int i = 0; i < boyut; i++) printf("%s\n", str[i]);


                                                }



                void applyBasicCommands (char* str){
                char current[100];
                printf("%s",getcwd(current,100));// current directory tut



                char *token;
                char *token_arr[1024];
                int count = 0;
                token = strtok(str," </>;");
                while (token != NULL)
                  {
                    token_arr[count] = token;
                      count++;
                      token = strtok(NULL, " </>;");
                      }





                    for (int i = 0; i < count; i++) printf("%s\n", token_arr[i]);



                    if(!strcmp(token_arr[0],"make")){
                        for (int m=1; m<=count-1; m++) {



                            mkdir(token_arr[m]);
                            chdir(token_arr[m]);
                        }
                    }




                else if(!strcmp(token_arr[0],"go")){
                    int c=strlen(token_arr);
                    for(int j=0;j<=c;j++){
                        printf("%s %d",token_arr[j],j);
                    }



                    chdir(token_arr[1]);//döngü de kurulabilir
                    chdir(token_arr[2]);
                    chdir(token_arr[3]);//nurse olmadığı için current yapamadı
                    printf("%s",getcwd(current,100));//dolayısıyla çıktıda görünmüyor



                }
            }


            void applyControlStructures(char* str){
                // deleteNewLineCharacter() kullan.
                char *token;
                char *token_arr[100];
                int count = 0;
                token = strtok(str," </>\n");
                while (token != NULL)
                  {
                    token_arr[count] = token;
                      count++;
                      token = strtok(NULL, " </>");
                      }

                      for (int i = 0; i < count; i++) printf("%s%d\n", token_arr[i],i);





                    int if_sayisi=0;
                    int block_sayisi=0;
                    bool if_sarti=true;
                    for (int i = 0; i < count; i++){

                        if( !strcmp(token_arr[i],"if") ){
                            //printf("GGGGGGGGGGGGGGGGGGGG%s\n",token_arr[i]);
                            if_sayisi++; }
                     //   else if() // Burada if in şartları kaydedilmesi lazım.
                        else if( !strcmp(token_arr[i],"{") ) block_sayisi++;
                       else if( !strcmp(token_arr[i],"}") ){ block_sayisi--; if_sayisi--;}
                   else if( (!strcmp(token_arr[i],"make") || !strcmp(token_arr[i],"go")&& block_sayisi==0
                         && if_sayisi==1 && if_sarti) ) //
                           {
                                for(int j=i;j<count;j++) {
                                    if( !strcmp(token_arr[j],";") ){
                                            char* commands[10];
                                            strncpy ( commands, token_arr+i, j-1-i );
                                           printf("%s %s %s AAAAAAAAAA\n",commands[0],commands[1],commands[2]);
                                           //printf("%s %s %s",token_arr[i],token_arr[i+1],token_arr[i+2]);
                                          // applyBasicCommands2(commands,j-i-1); // Bu kısım yapılmalı.
                                          i=j;
                                          break;
                                                                    }
                                                        }
                           }
               /*     else if (if_sayisi>=1 && block_sayisi==1 && if_sarti){
                        if (!strcmp(token_arr[i],"make") || !strcmp(token_arr[i],"go")){
                            for(int j=i;j<count;j++) {
                                    if( !strcmp(token_arr[j],";") ){ // j ninci eleman ; dır.
                                            char* commands[10];
                                            strncpy ( commands, token_arr+i, j-1 );
                                           printf("%s %s %s AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",commands[0],commands[1],commands[2]);
                                          // applyBasicCommands2(commands,j-i-1); // Bu kısım yapılmalı.
                                          i=j;
                                          break;
                                                                    }
                                                     }
                                                                                        }
                        else if ( !strcmp(token_arr[i],"if") ) {
                                bool if_sarti_ic=true;
                                char* data[8];
                                for(int t=i;t<count;t++){
                                    if( !strcmp(token_arr[t],"make") && !strcmp(token_arr[t],"go") ){
                                        // Burada datalar bi arraya kopyalanabilir.
                                            i=t;
                                            break;
                                }

                                if ((!strcmp(token_arr[i],"make") || !strcmp(token_arr[i],"go")) && if_sarti_ic ){
                            for(int j=i;j<count;j++) {
                                    if( !strcmp(token_arr[j],";") ){ // j ninci eleman ; dır.
                                            char* commands[10];
                                            strncpy ( commands, token_arr+i, j-1 );
                                           printf("%s %s %s AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",commands[0],commands[1],commands[2]);
                                          // applyBasicCommands2(commands,j-i-1); // Bu kısım yapılmalı.
                                          i=j;
                                          break;
                                                                    }
                                                     }
                                                                                        }

                        }  //if_statement();
                                                                         } }
                    else if(if_sayisi>=1 && block_sayisi>1 && if_sarti){} // recursive çalışmalı */
                                                        }
                                                        }



            void deleteNewLineCharacter(char* str){  //Henüz çalışmıyor.
           /* char *pch = strstr(str, "\n");
                while(pch != NULL)
                {
                    strncpy(pch, " ", 1);
                    pch = strstr(str, "\n");
                }

               // if( (ptr = strchr(str, '\n')) != NULL) *ptr = '\0';  */
                }








void interpreter(char* str)
{
    FILE *dosya;
    dosya =fopen("code.lex.txt","w");
    int left = 0, right = 0;
    int len = strlen(str);


    while (right <= len && left <= right) {


        //printf("right=%d",right);
        if (str[right]=='<'){
                    int len=strlen(str);
                    for(int i=right;i<=len;i++){
                            right++;
                        if (str[right]=='>')
                            { //right=right+1;
                                break;
                            }
                        if (i==len)
    printf("ERROR! Data Type cannot terminate before the file end.\n");  }
                        }

        else if ( (str[right]=='m' && str[right+1]=='a' && str[right+2]=='k' && str[right+3]=='e')
                 || (str[right]=='g' && str[right+1]=='o') ) {
                    int len=strlen(str);
                    for(int i=right;i<=len;i++){
                            right++;
                        if (str[right]==';')
                            { //right=right+1;  //burası muallak ????
                                break;
                            }
                        if (i==len)
    printf("ERROR! Command cannot terminate before the file end.\n");  }
                        }

                        else if ( (str[right]=='i' && str[right+1]=='f' && str[right+2]=='n' && str[right+3]=='o'
               && str[right+4]=='t') || (str[right]=='i' && str[right+1]=='f')    ){
                    int len=strlen(str);
                    int start=1;
                    int bracket=0;
                        for(int i=right;i<=len;i++){
                            if(str[i]=='{')  bracket++;
                        if(str[i]=='}' && bracket==1){right=i; break; }  //right++ varmı muallak
                        if (i==len && bracket==1) printf("ERROR! Control Structure cannot terminate before the file end.\n");
                                                   }

                        if(bracket==0){
                        for(int j=right;j<=len;j++){
                        right++;
                        if (str[right]==';' && start==1) break;
                        if (j==len) printf("ERROR! Control Structure without block cannot terminate before the file end.\n");  }
                                      }                                             }


            else if (isDelimiter(str[right]) == false) right++;





if (isDelimiter(str[right]) == true && left == right) {
            right++;
            left = right;
            }

         else if (isDelimiter(str[right]) == true && left != right
                || (right == len && left != right)) {
           // char* subStr = subString(str, left, right - 1);
           // char* subStr2 = subString(str, left, right);
            char* subStr3=subString(str,left,right);
            char* subStr4=subString(str,left,right);

   /*         if (isKeyword(subStr) == true)
                printf("Keyword (%s)\n",subStr);
                //fprintf(dosya,"Keyword (%s)\n",subStr);  */

            if (isControlStructures(subStr4)==true){
                    //printf("naber4 ");
                printf("Control Structures (%s)\n",subStr4);
                applyControlStructures(subStr4);
                right++;
            }

            else if (isBasicCommands(subStr3)==true){
                    //printf("naber3 ");
                printf("Basic Commands (%s)\n",subStr3);
                applyBasicCommands(subStr3);
                right++;
            }


         /*   else if (isDataTypes(subStr2)==true){
                    printf("naber2 ");
                printf("Data Types (%s)\n",subStr2);
                // yapılacak işler var.
                right++;
            }  */



      /*      else if (isString(subStr)== true ){
                printf("String(%s)\n",subStr);
                fprintf(dosya,"String (%s)\n",subStr3);
            }   */

          /*  else if (validIdentifier(subStr) == true
                    && isDelimiter(str[right - 1]) == false)
                    if (strlen(subStr)>21) printf("ERROR! Maximum identifier size is 20 characters.\n");
                    else {
                        for(int i=0;i<strlen(subStr);i++) subStr[i]=toupper(subStr[i]);
                        printf("Identifer (%s)\n",subStr);
                        fprintf(dosya,"Identifier (%s)\n",subStr);
                         }   */


     /*       else if (validIdentifier(subStr) == false
                    && isDelimiter(str[right - 1]) == false)
                printf("Not Valid Identifier (%s)\n",subStr);   */
            left = right;
                                                            }
                                    } //while döngüsü biter
    }



int main()
{

    FILE *fp;
    long lSize;
    char *buffer;



    char fnamer[100]="";
    printf("Lutfen sonunda .txt olacak şekilde dosya adını giriniz. \n");
    scanf("%s",&fnamer);

    if ((fp = fopen(fnamer, "rb")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    if( !fp ) perror("blah.txt"),exit(1);



    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
    if( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);


    char CURRENT_DIRECTORY[] = "C:\Windows10\Desktop\project 2"; //directory=klasor demek C:\Users\Windows10\Desktop\project 2


    interpreter(buffer);

    fclose(fp);
    free(buffer);
    return (0);




}
