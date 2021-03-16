#include <stdio.h>                                                       
#include <string.h>                                                      
#include <stdlib.h>
#include <math.h>
#define LEN 1026

//STRUTTURE
typedef struct list{
	struct list *next;
	char *string;
}Text;

typedef struct node{
	int ind1, ind2, totrigheP, totrigheN, totbackup;
	char command;
	char **backup;
	Text *Rlist, *Ulist;
	struct node *prev, *next;
}URlist;

//VARIABILI GLOBALI
int TotRighe=0, size=20000, U_node=0, R_node=0, URcounter=0, mall=0, flag=0, cflag=0, dflag=0, True=1;
char **vect;
URlist *h, *SP, *z, *SUPPORTO;
Text *tempU, *tempR;

int c_to_int(char *x, int dim){
	int i, sum=0, b=0, c=0;
	c=dim;
	for(i=0; i<c; i++){
		b=(x[i]-'0')*(pow(10,(dim-1)));
		sum=sum+b;
		dim--;
	}
	return sum;
}

int minimum(int a, int b){
	if(a<=b)
		return a;
	return b;
}

void Push(int idx1, int idx2, char cmd, char *pstr, char *cstr) { 
	if(mall == 0){
		z = NULL;
		z = (URlist*)malloc(sizeof(URlist));
		U_node++;
		z->Rlist = NULL;
		z->Ulist = NULL;
		z->ind1 = idx1;
		z->ind2 = idx2;
		z->command = cmd;
		z->totrigheP = TotRighe;
		z->backup = NULL;

		if(h == NULL){	
			h = z;
			SP = z;
			z->next = NULL;
			z->prev = NULL;
		}
		else{	
			SP->next = z;
			z->next = NULL;
			z->prev = SP;
			SP = z;
		}

		mall = 1; 
	}

	if(cstr != "F"){
		Text *a = (Text*)malloc(sizeof(Text));
		a->string=malloc(sizeof(char)*(strlen(cstr)+1));
		a->string = cstr;

		if(z->Rlist == NULL){	
			a->next = NULL;
			z->Rlist = a;
			tempR = a;
		}
		else{	
			tempR->next = a;
			tempR = a;
			a->next = NULL;
		}
	}

	Text *b = (Text*)malloc(sizeof(Text));
	b->string=malloc(sizeof(char)*(strlen(pstr)+1));
	b->string = pstr;

	if(z->Ulist == NULL){	
		b->next = NULL;
		z->Ulist = b;
		tempU = b;
	}
	else{	
		tempU->next = b;
		tempU = b;
		b->next = NULL;
	}
}

void ResetStatoU(){
	int k, i, a, f, g, h, j;
	k=URcounter;
	a=URcounter;
	f=U_node;
	g=R_node;
	h=U_node;
	j=R_node;

	SUPPORTO=SP;
	SP->totrigheN=TotRighe;

	while(k>0 && SUPPORTO->prev!=NULL){
		TotRighe=SUPPORTO->totrigheP;
		SUPPORTO=SUPPORTO->prev;
		f--;
		g++;
		k--;
		SUPPORTO->totrigheN=TotRighe;
		if(SUPPORTO->backup!=NULL){
			SP=SUPPORTO;
			a=k;
			h=f;
			j=g;
		}
	}

	URcounter=a;
	U_node=h;
	R_node=j;
	TotRighe=SP->totrigheN;

	for(i=1; i<=SP->totbackup; i++)
		vect[i]=SP->backup[i];
}

void ResetStatoR(){
	int k, i, a, h, j, f, g;
	k=URcounter;
	a=URcounter;
	f=U_node;
	g=R_node;
	h=U_node;
	j=R_node;

	SUPPORTO=SP;
	if(flag==0)
		SUPPORTO=SUPPORTO->next;

	while(k<0 && SUPPORTO->next!=NULL){
		k++;
		f++;
		g--;
		if(SUPPORTO->backup!=NULL){
			SP=SUPPORTO;
			flag=0;
			a=k;
			h=f;
			j=g;
		}

		SUPPORTO=SUPPORTO->next;
	}

	URcounter=a;
	U_node=h;
	R_node=j;
	TotRighe=SP->totrigheN;

	for(i=1; i<=SP->totbackup; i++)
		vect[i]=SP->backup[i];		
}

void Undo(){
	int ind1, ind2, diff, k, f, tot;
	char instruction;
	
	ResetStatoU();

	while(URcounter>0){
		URcounter--;
		U_node--;
		R_node++;		
		SP->totrigheN = TotRighe;
		instruction = SP->command;
		ind1 = SP->ind1;
		ind2 = SP->ind2;
		diff = (ind2-ind1)+1;
		tot=SP->totrigheP;

		switch(instruction){
			case 'c': { int j=0;
						tempU=SP->Ulist;

						for(diff; diff>0; tempU = tempU->next, ind1++, diff--)
							vect[ind1+j] = tempU->string;
						
						break;
					  }

			case 'd': {	k = TotRighe;
						f = tot;

						while(k>=ind1){   
							vect[f] = vect[k];           
							f--;
							k--;
						}

						k = k+1;
						tempU=SP->Ulist;
						while(tempU != NULL){
							vect[k] = tempU->string;
							tempU = tempU->next;
							k++;
						}
						break;
					  }
		}
		TotRighe=tot;
		if(SP!=NULL)
			SP=SP->prev;
	} 
}
	
void Redo(){
	int ind1, ind2, diff, tot;
	char instruction;

	if(SP==NULL){
		SP=h;
		flag=1;
	}

	ResetStatoR();

	while(URcounter<0){
		URcounter++;
		R_node--;
		U_node++;
		
		if(SP->next!=NULL && flag==0)
			SP=SP->next;

		flag=0;
		instruction = SP->command;
		ind1 = SP->ind1;
		ind2 = SP->ind2;
		diff = (ind2-ind1)+1;
		tot = SP->totrigheN;

		switch(instruction){
			case 'c': { int j=0;
						tempR=SP->Rlist;

						for(diff; diff>0; tempR = tempR->next, ind1++, diff--)					
							vect[ind1] = tempR->string;
						
						break;
					  }

			case 'd': {	int a, b;
						a = ind2+1;
						b = ind1;

						if(a<=TotRighe){
							while(a<=TotRighe){
								vect[b] = vect[a];	
								a++;
								b++;
							} 

							TotRighe = TotRighe-diff;
						}
						else if(ind1<=TotRighe)
								TotRighe = ind1-1;

						break;
					  }
		}
		TotRighe = tot;
	}
}

void BackupStato(){
	int i;
	SP->backup=NULL;
	SP->backup=malloc(sizeof(char*)*(TotRighe+200));
	for(i=1; vect[i]!=NULL; i++)
		SP->backup[i]=vect[i];
	SP->totbackup=i;	
}

int main(int argc, char const *argv[]){

	int i, j, idx1, idx2, diff=0, cont=1;
	char supp1[LEN], supp2[LEN], cmd[LEN], str[LEN], command;

	vect = malloc(sizeof(char*)*size);
	h = NULL;
	SP = NULL;
	tempU = NULL;
	tempR = NULL;


	while(True){

		cflag=0;
		dflag=0;
		mall=0;

		fgets(cmd, LEN, stdin);
    
    	//QUIT
        if(cmd[0] == 'q')
            return 0;

        //PARSING
        for(i=0; cmd[i] != ',' && cmd[i] != 'u' && cmd[i] != 'r'; i++) 
            supp1[i] = cmd[i]; 
        
        supp1[i]='\0';   
        idx1 = c_to_int(supp1, strlen(supp1));

        if(cmd[i] == ','){
            j=i+1;
            i=0;
            for(j; cmd[j] != 'p' && cmd[j] != 'c' && cmd[j] != 'd'; j++){
                supp2[i] = cmd[j];
                i++;
            }
            
            supp2[i]='\0';
            idx2 = c_to_int(supp2, strlen(supp2));
			diff=idx2-idx1+1;

            command = cmd[j];
        }else
        	command = cmd[i];


        if(command=='p' || command == 'c' || command == 'd'){
        	if(URcounter>0)
        		Undo();
        	if(URcounter<0)
        		Redo();

        	if(command != 'p'){
        		R_node=0;
        		URcounter=0;
			    if(SP!=NULL)
			    	SP->next=NULL;
			    
			    if(SP==NULL)
        			h=NULL;
        	}
        }


        switch(command){
        	//PRINT
        	case 'p' : { if(idx1!=0)
        				 	while(idx1<=idx2 && idx1<=TotRighe){
        				 		printf("%s", vect[idx1]);
	        					idx1++;
	        				 }

        				 while(idx1<=idx2){
        				 printf(".\n");
        				 idx1++;
        				 }
        				 break;
        				}

        	//CHANGE			
        	case 'c' : { char sovrascritto='\0';
        				 char *support=NULL;
        				 for(idx1; idx1<=idx2; idx1++){
	 		        		 fgets(str, LEN, stdin);

			        		 if(TotRighe>=size-10){
			        			 size = size+5000;
			        			 vect=realloc(vect, sizeof(char *) * size); 
			        		 }

			        		
			        		 if(idx1<=TotRighe){
							 	 if(cont%20==0)
							 	 	cflag=1;

							 	 cont++;
							 	 support = vect[idx1];
							 	 if(vect[idx1]!=NULL) 
								 	vect[idx1]=NULL;
								 vect[idx1]=malloc(sizeof(char)*(strlen(str)+1));
								 Push(idx1, idx2, command, support, vect[idx1]);
								 strcpy(vect[idx1], str);			        		 	 
							 }
							 else{
								
								 if(vect[idx1]!=NULL) 
								 	vect[idx1]=NULL;
			        			 vect[idx1]=malloc(sizeof(char)*(strlen(str)+1));
			        			 Push(idx1, idx2, command, &sovrascritto, vect[idx1]);
			        			 strcpy(vect[idx1], str);
			        			 TotRighe++;
							 }
		        	 	 }	

		        		 if(getchar()!='.')
			        		 return 0;
			    	
			    		 getchar();

			    		 break;

        				}

        	//DELETE			
        	case 'd' : { int x=idx1;
        				 int y=idx2;
        				 int p=diff;

        				 if(idx1>TotRighe || idx2==0)
        				 	Push(idx1, idx2, 'A', "A", "A");

			             if(idx2<TotRighe){
			             	 dflag=1;
			             	 while(idx1<=idx2){
			             	 	Push(idx1, idx2, command, vect[idx1], "A");
			             	 	idx1++;
			             	 }

			             	 idx1=x;

			                 for(idx2; idx2<TotRighe; idx1++, idx2++)	
			                     vect[idx1] = vect[idx2+1];

			                 for(diff; diff>0; diff--, idx1++)
			                 	vect[idx1] = NULL;

			                 TotRighe = TotRighe-p;			                 
			             }
			             else{	
			             	 for(idx1; idx1<=TotRighe; vect[idx1] = NULL, idx1++)
			                 	 Push(idx1, TotRighe, command, vect[idx1], "A");

			                 if(x<=TotRighe)
			                 	TotRighe = x-1;
			             } 

			             break;
        				}

        	//UNDO
        	case 'u' : { URcounter = URcounter+idx1;
						 if(URcounter>0)
						 	URcounter=minimum(U_node, URcounter);

        				 break;
        				}

        	//REDO
        	case 'r' : { URcounter = URcounter-idx1;
						 if(URcounter<0)
						 	URcounter=(-1)*minimum(abs(R_node), abs(URcounter));

        				 break;
        				}
        }

        if((command=='c' && cflag==1) || (command=='d' && dflag==1)){
        	BackupStato();
        }
	}	
}