#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define ERROR printf("WRONG ENTRY OF WORD")


typedef struct TrieNode
{
 int end;
 char letter,*meaning;
 struct TrieNode *tries[26];
}T;

T *tries[26];

void put_word(char *word,char *meaning)
{
 T *(*temp),*new;
 int i=0,j,n;
 temp=malloc(sizeof(T*)*26);
 temp=tries;
 while(1)
 {
  if((int)word[i]>=97)
   n=(int)word[i]-97;
  else
   n=(int)word[i]-65;
  if(n<=-1 || n>=26)
   { ERROR;break; }
  
  if(temp[n]==NULL) 
  {
   new=(T*)malloc(sizeof(T));
   new->letter=word[i];
   temp[n]=new;
  
   if(word[i+1]=='\0')
   {
   temp[n]->end=1;
   temp[n]->meaning=(char*)malloc(sizeof(char)*(strlen(meaning)));
   strcpy(temp[n]->meaning,meaning);  
   return;
   }
    temp=new->tries;
  }
 else
 { 
  if(word[i+1]=='\0')
   {
    printf("\nWord Exists !");
    return;
   }
  
   temp=temp[n]->tries;
  }
  i++;
 }
}

void get_meaning(char *word)
{
 int i=0,n;
 T *(*temp);
 temp=malloc(sizeof(T*)*26);
 temp=tries;
 while(1)
 {
    
  if((int)word[i]>=97)
   n=(int)word[i]-97;
  else
   n=(int)word[i]-65;
  if(n<=-1 || n>=26)
   { ERROR;break; }
  
  if(temp[n]==NULL)
   { ERROR;return; }
  if(temp[n]->end==1 && word[i+1]=='\0')
   { fprintf(stdout,"\nMeaning :%s",temp[n]->meaning); return; }
  temp=temp[n]->tries;
  i++;
  if(word[i]=='\0')
   { ERROR; return; }
 
 }
}

void disp(T *(*arr))
{
 int i;
 for(i=0;i<26;i++)
  {
   if(arr[i]!=NULL)
    {
    printf("\n%c",arr[i]->letter);
    if(arr[i]->end==1)
     printf("\t: %s",arr[i]->meaning);
    disp(arr[i]->tries);
    }
  }
}


void delete_word(char *word)
{
 T *(*temp);
 int i=0,pos,j,n;
 
 temp=malloc(sizeof(T*)*26);
 temp=tries;
 while(1)
 {
  if(word[i]=='\0')
  { ERROR;return; }
 
  if((int)word[i]>=97)
   n=(int)word[i]-97;
  else
   n=(int)word[i]-65;
  if(n<=-1 || n>=26)
   { ERROR;break; }
  
  if(i==0)
   pos=n;
 
   if(temp[n]==NULL)
   { ERROR; return; }

   if(word[i+1]=='\0' && temp[n]->end==1)
   {
    for(j=0;j<26;j++)
    {
     if(temp[n]->tries[j]!=NULL)
      break;
    }   
    if(j<=25)
    {
     temp[n]->meaning=(char*)realloc(temp[n]->meaning,sizeof(char)*0);
     temp[n]->end=0;
    }
    else
    {
     tries[pos]=NULL;
    }  
    fprintf(stdout,"\nDELETED");return;
   }
   
   temp=temp[n]->tries; 
  i++;
 }
}


int main(void)
{
 int op;
 char *word,*meaning;
 word=(char*)malloc(sizeof(char));
 meaning=(char*)malloc(sizeof(char)); 
         
 do
 {
  fprintf(stdout,"\n\n1)Add Word\n2)Get Meaning\n3)Delete Word\nEnter op: ");
  fscanf(stdin,"%d",&op);
  switch(op)
  {
   case 1:
          word=(char*)realloc(word,sizeof(char)*50);
          meaning=(char*)realloc(meaning,sizeof(char)*100);
          fprintf(stdout,"\nWord:");
          fscanf(stdin,"%s",word);
          fprintf(stdout,"\nMeaning:");
          getchar();
          fgets(meaning,98,stdin);
          put_word(word,meaning);
          disp(tries);
          break;        
   case 2:
          word=(char*)realloc(word,sizeof(char)*50);
          fprintf(stdout,"\nWord:");
          fscanf(stdin,"%s",word);
          get_meaning(word);
          break;
  case 3: 
          word=(char*)realloc(word,sizeof(char)*50);
          fprintf(stdout,"\nWord:");
          fscanf(stdin,"%s",word);
          delete_word(word);
          disp(tries);
          break;        
  default: 
          word=(char*)realloc(word,sizeof(char)*0);
          meaning=(char*)realloc(meaning,sizeof(char)*0);                 
  }
 }while(op<=3);
 return 0;
}
