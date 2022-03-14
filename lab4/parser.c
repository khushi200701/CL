#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

void followfirst(char , int , int);
void findfirst(char , int , int);
void follow(char c);

int count,n=0;
char firstArray[15][100];
char followArray[15][100];
int m=0;
char production[15][10], first[15];
char f[15];
int k;
char ck;
int e;

int main(int argc,char **argv)
{
	int jm=0;
	int km=0,line=0;
	int i,choice;
	char c,ch;
	FILE* filePointer;
	int bufferLength = 255;

	filePointer = fopen("text.txt", "r");

	while(fgets(production[line], bufferLength, filePointer)) { //Reading the productions after removing left recursion from the file text.txt.
	
		    production[line][strlen(production[line])-1]='\0'; 
		    printf("%s\n", production[line]);
		    line++;
	}
	
	fclose(filePointer);
	
	count=line; // Count is the number of productions.
	int _var;
	char done[count];
	int ptr = -1;
	for(k=0;k<count;k++){ 
		for(_var=0;_var<100;_var++){
			firstArray[k][_var] = '!';	// Filling an array of size[count][100] with '!'
		}
	}
	int point1 = 0,point2,x;
	for(k=0;k<count;k++)
	{
		c=production[k][0];		//Storing the Non-Terminal in c.
		point2 = 0;
		x = 0;
		for(_var = 0; _var <= ptr; _var++)
			if(c == done[_var])
				x = 1;
		if (x == 1)
			continue;
		findfirst(c,0,0);
		ptr+=1;
		done[ptr] = c;
		printf("\n First(%c)= { ",c);
		firstArray[point1][point2++] = c;
		for(i=0+jm;i<n;i++){
			int start = 0,chk = 0;
  			for(start=0;start<point2;start++){
  				if (first[i] == firstArray[point1][start]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c, ",first[i]);		//Printing first of the non-terminal.
  				firstArray[point1][point2++] = first[i]; //Storing the first of c in firstArray
			}
		}
		printf("}\n");
		jm=n;
		point1++;
	}
	printf("\n");
	printf("-----------------------------------------------\n\n");
	char donee[count];
	ptr = -1;
	for(k=0;k<count;k++){
		for(_var=0;_var<100;_var++){
			followArray[k][_var] = '!';
		}
	}
	point1 = 0;
	int land = 0;
	for(e=0;e<count;e++)
  	{
		ck=production[e][0];
		point2 = 0;
		x = 0;
		for(_var = 0; _var <= ptr; _var++)
			if(ck == donee[_var])
				x = 1;
		if (x == 1)
			continue;
  		land += 1;
		follow(ck);
  		ptr+=1;
		donee[ptr] = ck;
  		printf(" Follow(%c) = { ",ck);
  		followArray[point1][point2++] = ck;
  		for(i=0+km;i<m;i++){
  			int start = 0,chk = 0;
  			for(start=0;start<point2;start++){
  				if (f[i] == followArray[point1][start]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c, ",f[i]);
  				followArray[point1][point2++] = f[i];
  			}
  		}
  		printf(" }\n\n");
		km=m;
		point1++; 
	}
	char ter[10];
	for(k=0;k<10;k++){
		ter[k] = '!';
	}
	int ap,vp,sid = 0;
	for(k=0;k<count;k++){
		for(_var=0;_var<count;_var++){
			if(!isupper(production[k][_var]) && production[k][_var]!= '#' && production[k][_var] != '=' && production[k][_var] != '\0'){
				vp = 0;
				for(ap = 0;ap < sid; ap++){
					if(production[k][_var] == ter[ap]){
						vp = 1;								//so that there is no repeatition of the list of terminals
						break;
					}
				}
				if(vp == 0){
					ter[sid] = production[k][_var];
					sid ++;
				}
				
			}
		}
	}
	ter[sid] = '$';
	sid++;
	printf("\n\t\t\t\t\t\t\t The LL(1) Parsing Table for the above grammer :-");
	printf("\n\t\t\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	for(ap = 0;ap < sid; ap++){
		printf("\t%c\t",ter[ap]);
	}
	
	printf("\n");
	char first_prod[count][sid];
	for(ap=0;ap<count;ap++){
		int destiny = 0;
		k = 2;
		int ct = 0;
		char tem[100];
		while(production[ap][k] != '\0'){   // breaking E=TR into E=T
			if(!isupper(production[ap][k])){
				tem[ct++] = production[ap][k];
				tem[ct++] = '_';
				tem[ct++] = '\0';
				k++;
				break;
			}
			else{
				int z=0;
				int t = 0;
				for(z=0;z<count;z++){
					if(firstArray[z][0] == production[ap][k]){
						for(t=1;t<100;t++){
							if(firstArray[z][t] != '!'){
								tem[ct++] = firstArray[z][t];
							}
							else
								break;
						}
					break;
					}
				}
				tem[ct++] = '_';
			}
			k++;
		}
		int z = 0,t;		
		for(t = 0;t<ct;t++){
			if(tem[t] == '#'){
				z = 1;
			}
			else if(tem[t] == '_'){
				if(z == 1){
					z = 0;
				}
				else
					break;
			}
			else{
				first_prod[ap][destiny++] = tem[t];
			}
		}
	}
	char table[land][sid+1];
	ptr = -1;
	for(ap = 0; ap < land ; ap++){
		for(_var = 0; _var < (sid + 1) ; _var++){
			table[ap][_var] = '!';
		}
	}
	for(ap = 0; ap < count ; ap++){
		ck = production[ap][0];
		x = 0;
		for(_var = 0; _var <= ptr; _var++)
			if(ck == table[_var][0])
				x = 1;
		if (x == 1)
			continue;
		else{
			ptr = ptr + 1;
			table[ptr][0] = ck;
		}
	}
	for(ap = 0; ap < count ; ap++){
		int t = 0;
		while(first_prod[ap][t] != '\0'){
			int to,ni=0;
			for(to=0;to<sid;to++){
				if(first_prod[ap][t] == ter[to]){
					ni = 1;
				}
			}
			if(ni == 1){
				char xz = production[ap][0];
				int cz=0;
				while(table[cz][0] != xz){
					cz = cz + 1;
				}
				int vz=0;
				while(ter[vz] != first_prod[ap][t]){
					vz = vz + 1;
				}
				table[cz][vz+1] = (char)(ap + 65);
			}
			t++;
		}
	}
	for(k=0;k<sid;k++){
		for(_var=0;_var<100;_var++){
			if(firstArray[k][_var] == '!'){
				break;
			}
			else if(firstArray[k][_var] == '#'){
				int fz = 1;
				while(followArray[k][fz] != '!'){
					char xz = production[k][0];
					int cz=0;
					while(table[cz][0] != xz){
						cz = cz + 1;
					}
					int vz=0;
					while(ter[vz] != followArray[k][fz]){
						vz = vz + 1;
					}
					table[k][vz+1] = '#';
					fz++;	
				}
				break;
			}
		}
	}
	for(ap = 0; ap < land ; ap++){
		printf("%c\t",table[ap][0]);
		for(_var = 1; _var < (sid + 1) ; _var++){
			if(table[ap][_var] == '!')
				printf("\t\t");
			else if(table[ap][_var] == '#')
				printf("%c=#\t\t",table[ap][0]);
			else{
				int mum = (int)(table[ap][_var]);
				mum -= 65;
				printf("%s\t\t",production[mum]);
			}
		}
		printf("\n");
	}
	int j;
	printf("\n\nPlease enter the desired INPUT STRING = ");
	char input[100];
	scanf("%s%c",input,&ch);
	printf("\n\t\t\t\t\t\tStack\t\t\tInput\t\t\tAction");
	printf("\n\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	int i_ptr = 0,s_ptr = 1;
	char stack[100];
	stack[0] = '$';
	stack[1] = table[0][0];
	while(s_ptr != -1){
		printf("\t\t\t\t\t\t");
		int _var1 = 0;
		for(_var1=0;_var1<=s_ptr;_var1++){
			printf("%c",stack[_var1]);
		}
		printf("\t\t\t");
		_var1 = i_ptr;
		while(input[_var1] != '\0'){
			printf("%c",input[_var1]);
			_var1++;
		}
		printf("\t\t\t");
		char her = input[i_ptr];
		char him = stack[s_ptr];
		s_ptr--;
		if(!isupper(him)){
			if(her == him){
				i_ptr++;
				printf("POP ACTION\n");
			}
			else{
				printf("\nString Not Accepted by LL(1) Parser\n");
				exit(0);
			}
		}
		else{
			for(i=0;i<sid;i++){
				if(ter[i] == her)
					break;
			}
			char produ[100];
			for(j=0;j<land;j++){
				if(him == table[j][0]){
					if (table[j][i+1] == '#'){
						printf("%c=#\n",table[j][0]);
						produ[0] = '#';
						produ[1] = '\0';
					}
					else if(table[j][i+1] != '!'){
						int mum = (int)(table[j][i+1]);
						mum -= 65;
						strcpy(produ,production[mum]);
						printf("%s\n",produ);
					}
					else{
						printf("\nString Not Accepted by LL(1) Parser\n");
						exit(0);
					}
				}
			}
			int le = strlen(produ);
			le = le - 1;
			if(le == 0){
				continue;
			}
			for(j=le;j>=2;j--){
				s_ptr++;
				stack[s_ptr] = produ[j];
			}
		}
	}

	if (input[i_ptr] == '\0'){
		printf("\n\t\t\t\t\t\t\t\tYOUR STRING HAS BEEN ACCEPTED\n");
	}
	else
		printf("\n\t\t\t\t\t\t\t\tYOUR STRING HAS BEEN REJECTED\n");
}

void follow(char c)
{
	int i ,j;
	if(production[0][0]==c){
 		f[m++]='$';
 	}
 	for(i=0;i<10;i++)
 	{
  		for(j=2;j<10;j++)
  		{
   			if(production[i][j]==c)
   			{
    			if(production[i][j+1]!='\0'){
					followfirst(production[i][j+1],i,(j+2));
 				}
    			if(production[i][j+1]=='\0'&&c!=production[i][0]){
     				follow(production[i][0]);
				}
   			}   
  		}
 	}
}

void findfirst(char c ,int q1 , int q2)
{
	int j;
	if(!(isupper(c))){
		first[n++]=c;
	}
	for(j=0;j<count;j++)
	{
		if(production[j][0]==c)
		{
			if(production[j][2]=='#'){  // E=#
				if(production[q1][q2] == '\0')
					first[n++]='#';
				else if(production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) 
				{
					findfirst(production[q1][q2], q1, (q2+1));
				}
				else
					first[n++]='#';
			}
			else if(!isupper(production[j][2])){ //R=+TR
				first[n++]=production[j][2];
			}
			else {
				findfirst(production[j][2], j, 3);  //E=TR
			}
		}
	}	
}

void followfirst(char c, int c1 , int c2)
{
    int k;
    if(!(isupper(c)))
		f[m++]=c;
	else{
		int i=0,j=1;
		for(i=0;i<count;i++)
		{
			if(firstArray[i][0] == c)
				break;
		}
		while(firstArray[i][j] != '!')
		{
			if(firstArray[i][j] != '#'){
				f[m++] = firstArray[i][j];
			}
			else{
				if(production[c1][c2] == '\0'){
					follow(production[c1][0]);
				}
				else{
					followfirst(production[c1][c2],c1,c2+1);
				}
			}
			j++;
		}
	}
}


		
	
