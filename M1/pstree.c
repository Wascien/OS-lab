#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include<string.h>
#include<stdlib.h>
//#include <errno.h>
#include <sys/types.h>
#define PATH "/proc" 
#define check_value(a,b) a==b
#define STR_EQUAL(a,b) !strcmp(a,b)

typedef enum Flag{
  none,
  show_pid=1,
  sort_pid=1<<1,
  hidden_thread=1<<2,
  PPID=1<<3,
  Full=(1<<4)-1,
} Flag_t;
struct process
{
  char *p_name;
  char *p_pid;
  char *p_ppid;
  struct process*bro;
  struct process* son;
};
typedef struct process process;

process* create_process(const char*,const char*,const char*ppid);
void insert(process*,process*);
process* walk_all_process(const char *path,Flag_t flag);
process* read_process_status(const char*dir_path,const char* dir_name);
process* search_node(process*,const char *);
int p_tree(process*,int,int*,int);
int is_pid(const char*);

void get_state(int *state,const char *arg){
  if(STR_EQUAL(arg,"-t")){
    *state=*state|hidden_thread;
  }else if(STR_EQUAL(arg,"-p")){  
    *state=*state|show_pid;
  }else if(STR_EQUAL(arg,"-n")){
    *state=*state|sort_pid;
  }
}

int main(int argc, char *argv[]) {
  int buf[1024] = {0};
  int state=0;
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    //printf("argv[%d] = %s\n", i, argv[i]);
    get_state(&state,argv[i]);
    if(is_pid(argv[i])){
      state|=PPID;
    }
  }
  assert(!argv[argc]);
  process* p=walk_all_process(PATH,state);
  if(state&PPID){
    p=search_node(p,argv[argc-1]);
    p->bro=NULL;
  }
  //printf("--now--\n");
  p_tree(p,0,buf,state);
  //printf("--now2--\n");
  printf("\n");
  return 0;
}

int is_pid(const char* name){
	int flag = 0;
	for (; *name; ++name)
		if (*name < '0' || *name > '9')
			return 0;
	return 1;
}

process* create_process(const char*p_name,const char*pid,const char* ppid){
  assert(p_name!=NULL&&pid!=NULL);
  process *p=(process*)malloc(sizeof(process));
  p->p_name=(char*)malloc(sizeof(char)*(strlen(p_name)+1));
  p->p_pid= (char*)malloc(sizeof(char)*(strlen(pid)+1));
  p->p_ppid= (char*)malloc(sizeof(char)*(strlen(ppid)+1));
  
  assert(p->p_name!=NULL&&p->p_pid!=NULL);
  strcpy(p->p_name,p_name);
  strcpy(p->p_pid,pid);
  strcpy(p->p_ppid,ppid);
  p->bro=NULL;
  p->son=NULL;
  return p;
}

process* walk_all_process(const char *path,Flag_t state){
  assert(path!=NULL);
  DIR *dir=0;
  int size=1024;
  struct dirent *entry;
  dir=opendir(path);
  char cache[size];
  if(dir==NULL){
    perror("fail opendir");
    return NULL;
  }
  process *head=create_process("","0","-1");
  while((entry=readdir(dir))){
    if(is_pid(entry->d_name)){
      process*node=read_process_status(path,entry->d_name);
      insert(head,node);
      //printf("name:%s pid:(%s)\n",node->p_name,node->p_pid);
      if(!(state&hidden_thread)){
        DIR *taskDir;
        struct dirent *subEntry;
        sprintf(cache,"%s/%s/%s",path,entry->d_name,"task");
        taskDir=opendir(cache);
        if(dir==NULL){
            perror("fail opendir task");
            return NULL;
        }
        while ((subEntry=readdir(taskDir)))
        {
          if(is_pid(subEntry->d_name)){
             if(!strcmp(subEntry->d_name,entry->d_name)){
              continue;
             }
             process*subNode=read_process_status(cache,subEntry->d_name);
             if(check_value(subNode,NULL)){
                continue;
             }
             insert(head,subNode);
          }
        }
      }
    }
  }
  return head;
}

process* read_process_status(const char*dir_path,const char* dir_name){
   const int size=1024;
   FILE* fp;
   char cache[size];

   strcpy(cache,dir_path);
   strcat(cache,"/");
   strcat(cache,dir_name);
   strcat(cache,"/");
   strcat(cache,"status");

   fp=fopen(cache,"r");
   char pid[size], ppid[size], name[size],tgid[size];
   while ((fscanf(fp, "%s", cache)) != EOF)
   {
      if (strcmp(cache, "Pid:") == 0) {
        fscanf(fp, "%s", pid);
        //printf("PID %s\n",pid);
      }
      if (strcmp(cache, "PPid:") == 0) {
        fscanf(fp, "%s", ppid);
      }
      if (strcmp(cache, "Name:") == 0) {
        fscanf(fp, "%s", name);
      }
      if (strcmp(cache, "Tgid:") == 0) {
        fscanf(fp, "%s", tgid);
      }
   }
   process *p=NULL;
   //printf("pid:%s    tgid:%s",pid,tgid);
   //assert(strcmp(pid,tgid)==0);
   //printf("\n\n%s %s %s %s\n\n",pid,ppid,name,tgid);
   //printf("------1------\n");   
      
    if(!strcmp(pid,tgid)){
      p=create_process(name,pid,ppid);
    }else{
      sprintf(cache,"{%s}",name);  
      //printf("------now------\n");   
      p=create_process(cache,pid,tgid);
    }
   fclose(fp);
   return p;
}

int p_tree(process*head,int len,int*buf,int state){
  if(head==NULL){
    return -1;
  }
  int flag=state&show_pid;
  while (head)
  {
    printf("%s",head->p_name);
    if(flag){
      printf("(%s)",head->p_pid);
    }
    if(head->son){
      if(!head->son->bro){
        printf("\u2500\u2500\u2500");
      }else{
        printf("\u2500\u252c\u2500");
      }
      int size=strlen(head->p_name)+len+3+(flag*(strlen(head->p_pid)+2));
      if(head->son->bro)buf[size-2]=1;
      p_tree(head->son,size,buf,state);
    }
    head=head->bro;
    if(head){
      printf("\n");
      if(!head->bro)buf[len-2]=0;
      for(int i=0;i<len-2;i++){
        if(buf[i])printf("\u2502");
        else{
          printf(" ");
        }
      }
      if(!head->bro){
        printf("\u2514\u2500");
      }else{
        printf("\u251c\u2500");
      }
    }
  }

  return 0;
}
 void insert(process* root,process *node){
    assert(root!=NULL);
    if(!strcmp(node->p_ppid,root->p_ppid)){
      process *p=root;
      while(p->bro){
        p=p->bro;
      }
      p->bro=node;
      return;
    }
    if(!strcmp(node->p_ppid,root->p_pid)){
      if(root->son==NULL){
        root->son=node;
      }else{
        insert(root->son,node);
      }
      return;
    }
    process*p=root->son;
    while (p)
    {
      insert(p,node);
      p=p->bro;
    }
    return;
 }

process* search_node(process*head,const char*pid){
  //printf("--------\n");
  if(head==NULL){
    return NULL;
  }
  if(STR_EQUAL(head->p_pid,pid)){
    return head;
  }
  process *p=NULL;
  p=search_node(head->son,pid);
  if(p)return p;
  return search_node(head->bro,pid);
}
