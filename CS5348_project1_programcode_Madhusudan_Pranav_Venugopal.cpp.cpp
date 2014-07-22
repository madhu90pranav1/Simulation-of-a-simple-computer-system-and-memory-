/*
CS 5348 Operating Systems Concepts
Project 1
Exploring Multiple Processes and IPC
Implementation Language: C++

Name : Madhusudan Pranav Venugopal
UTD ID: 2021163441
netid: mxv130430

*/

#include<iostream> /*This section of the code contains the header files*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fstream>
#include<string.h>
#include<cstdlib>
#include<stdio.h>


using namespace std; // Informs about the use of standard naming system


int pipedesc1[2],pipedesc2[2],pipedesc3[2],pipedesc4[2]; //Declaration of the pipes variables

void cpuprocess(int N)  // Method containing the task to be done by the CPU process or parent process
{

  //Intialisation of the varibles used in this method.
  int i=0,AC,IR,PC,SP=0,port,X=0,Y=0,value,add,wadd,wdata;
  int operation=-3000,mode=0,sp1=-9999,sp2=-19999,sp,itimer=0;
  int syspos=18888,usrpos=-8888,stackpos;
  char alpha;
  PC=0;
  

  // Beginning of the section of the code under label c 
 c:
 
  /* Checks if the timer value has been reached , if reached, resets the timer value
     and goes to the part of the code dealing with the interrupt handling */
  
  if(itimer==N) 
    {itimer=0;
      goto e;
        
    }
  i=PC;

  /* Sending the PC value to memory and getting the IR value from the memory*/
  
  write(pipedesc1[1],&PC,sizeof(PC));
  read(pipedesc2[0],&IR,sizeof(IR));

  //  Switching based on the IR value and performing each instruction

  switch(IR)
    {
    case 0:
      {
	PC=PC+1;
	break;

      }
    case 1:
      {
        // Load value into accumulator (AC)
	i++;
	PC=PC+2;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 2:
      {
        // Load the value at the address into the accumulator (AC)
	i=PC+1;
	PC=PC+2;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&add,sizeof(add));
	write(pipedesc1[1],&add,sizeof(add));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 3:
      {
        /*Load the value from the address found in the address into the AC*/
	i=PC+1;
	PC=PC+2;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&add,sizeof(add));
	write(pipedesc1[1],&add,sizeof(add));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 4:
      {
        //Load the value at (address+X) into the AC
        PC=PC+2;
	i++;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&add,sizeof(add));
	i=add+X;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;

      }
    case 5:
      {
        //Load the value at (address+Y) into the AC
        PC=PC+2;
	i++;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&add,sizeof(add));
	i=add+Y;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 6:
      {
        //Load from (Sp+X) into the AC
	PC=PC+1;
	if(mode==0)
	  stackpos=usrpos;
	if(mode==1)
	  stackpos=syspos;
	write(pipedesc1[1],&stackpos,sizeof(stackpos));
	read(pipedesc2[0],&SP,sizeof(SP));
	i=SP+X+1;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 7:
      {
	//Store the value in the AC into the address
        i=PC+1;
	PC=PC+2;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&add,sizeof(add));
	wadd=add;
	wdata=AC;
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&wadd,sizeof(wadd));
	write(pipedesc4[1],&wdata,sizeof(wdata));
	break;
      }
    case 8:
      {
        //Gets a random int from 1 to 100 into the AC
	PC=PC+1;
	AC=rand()%100;
	break;
      }
    case 9:
      {
        /*If port=1, writes AC as an int to the screen
	  If port=2, writes AC as a char to the screen*/

	PC=PC+2;
	i++;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&port,sizeof(port));
	if(port==1)
	  cout<<AC;
	else if(port ==2)
	  { alpha=AC;
	    cout<<alpha;
	  }
	break;
      }
    case 10:
      {
        //Add the value in X to the AC
	PC=PC+1;
	AC=AC+X;
	break;
      }
    case 11:
      {
        //Add the value in Y to the AC
	PC=PC+1;
	AC=AC+Y;
	break;
      }
    case 12:
      {
        //Subtract the value in X from the AC
	PC=PC+1;
	AC=AC-X;
	break;
      }
    case 13:
      {
        //Subtract the value in Y from the AC
	PC=PC+1;
	AC=AC-Y;
	break;
      }
    case 14:
      {
        //Copy the value in the AC to X
	PC=PC+1;
	X=AC;
	break;
      }
    case 15:
      {
        //Copy the value in X to the AC
	PC=PC+1;
	AC=X;
	break;
      }
    case 16:
      {
        //Copy the value in the AC to Y
	PC=PC+1;
	Y=AC;
	break;
      }
    case 17:
      {
        //Copy the value in Y to the AC
	PC=PC+1;
	AC=Y;
	break;
      }
    case 18:
      {
        //Copy the value in AC to the SP
	PC=PC+1;
	SP=AC;
	break;
      }
    case 19:
      {
        //Copy the value in SP to the AC
	if(mode==0)
	  stackpos=usrpos;
	if(mode==1)
	  stackpos=syspos;
	write(pipedesc1[1],&stackpos,sizeof(stackpos));
	read(pipedesc2[0],&SP,sizeof(SP));
	PC=PC+1;
	AC=SP;
	break;
      }
    case 20:
      {
        //Jump to the address
	i=i+1;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	PC=value;
	break;
      }
    case 21:
      {
        //Jump to the address only if the value in the AC is zero
	i=i+1;
	if( AC==0)
	  {
	    write(pipedesc1[1],&i,sizeof(i));
	    read(pipedesc2[0],&value,sizeof(value));
	    PC=value;
	  }
	else
	  PC=PC+2;

	break;
      }
    case 22:
      {
        /*Jump to the address only if the value in the AC is not zero*/
	i=i+1;
	if(AC!=0)
	  {
	    write(pipedesc1[1],&i,sizeof(i));
	    read(pipedesc2[0],&value,sizeof(value));
	    PC=value;
	  }
	else
	  {
	    PC=PC+2;
	  }
	break;
      }
    case 23:
      {
        //Push return address onto stack, jump to the address  
	i=PC+1;
	PC=PC+2;
	if(mode==0)
	  sp=sp1;
	else
	  sp=sp2;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	
	write(pipedesc1[1],&operation,sizeof(operation));
	wdata=PC;
	wadd=sp;
	write(pipedesc1[1],&wadd,sizeof(wadd));
	write(pipedesc4[1],&wdata,sizeof(wdata));
	PC=value;
	
	break;
      }
    case 24:
      { //Pop return address from the stack, jump to the address
	if(mode==0)
          sp=sp1;
	else
	  sp=sp2;
	i=sp;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	PC=value;
	
	break;
      }
    case 25:
      { //Increment the value in X
	X=X+1;
	PC=PC+1;
	break;
      }
    case 26:
      { //Decrement the value in X
	PC=PC+1;
	X=X-1;
	break;
      }
    case 27:
      { //Push AC onto stack
	PC=PC+1;
	if(mode==0)
	  sp=sp1;
	else
	  sp=sp2;
	wadd=sp;
	wdata=AC;
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&wadd,sizeof(wadd));
	write(pipedesc4[1],&wdata,sizeof(wdata));
	break;
      }
    case 28:
      {
        //Pop from stack into AC
	PC=PC+1;
	if(mode==0)
	  sp=sp1;
	else
	  sp=sp2;
	i=sp;
	write(pipedesc1[1],&i,sizeof(i));
	read(pipedesc2[0],&value,sizeof(value));
	AC=value;
	break;
      }
    case 29:
      {
	/*Set system mode, switch stack, push SP and PC, set new SP and PC*/
	if(mode==0)
	  stackpos=usrpos;
	if(mode==1)
	  stackpos=syspos;
	write(pipedesc1[1],&stackpos,sizeof(stackpos));
	read(pipedesc2[0],&SP,sizeof(SP));
	PC=PC+1;
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&sp1,sizeof(sp1));
	write(pipedesc4[1],&SP,sizeof(SP));
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&sp1,sizeof(sp1));
	write(pipedesc4[1],&PC,sizeof(PC));
	mode=1;
	write(pipedesc1[1],&sp2,sizeof(sp2));
	read(pipedesc2[0],&SP,sizeof(SP));
	PC=1500;
	break;
      }
    case 30: //Restore registers, set user mode
      {
	mode=0;
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&sp2,sizeof(sp2));
	write(pipedesc4[1],&SP,sizeof(SP));
	write(pipedesc1[1],&operation,sizeof(operation));
	write(pipedesc1[1],&sp2,sizeof(sp2));
	write(pipedesc4[1],&PC,sizeof(PC));
	write(pipedesc1[1],&sp1,sizeof(sp1));
	read(pipedesc2[0],&PC,sizeof(PC));
	write(pipedesc1[1],&sp1,sizeof(sp1));
	read(pipedesc2[0],&SP,sizeof(SP));
	break;
            
            
      }
    case 50:  //End execution
      {
	i=2001;

	write(pipedesc1[1],&i,sizeof(i));
	wait(NULL);
	exit(0);
	break;
      }

    }
  if(mode==0) /* Increasing the instruction timer when it is in user mode*/
    itimer++;

  // Part of the code to ensure system memory area protection

  if(PC<1000)
    {i++;
      
      goto c;
}
  else if(PC>=1000&&PC<2000)
    {
      if(mode==1)
	{i++;
	  
	  goto c;
	}
      else if(mode==0&&PC>=1000) 
	{/*Exit with error incase user program accesses system memory*/
	  cout<<endl<<" User program accessing system memory";
	  i=2001;
	  write(pipedesc1[1],&i,sizeof(i));
	  wait(NULL);// Wait for memory process to exit before exiting            
	  exit(0);
	}
     }    
    
  else if(i==2001) // Exit when end of program instruction
    {
      write(pipedesc1[1],&i,sizeof(i));
      wait(NULL); // Wait for memory process to exit before exiting
      exit(0);
    
    }

   /* Part of the program of for handling the intstruction time out interrupt*/

 e:  
  if(mode==0)
    stackpos=usrpos;
  if(mode==1)
    stackpos=syspos;
  write(pipedesc1[1],&stackpos,sizeof(stackpos));
  read(pipedesc2[0],&SP,sizeof(SP));
  write(pipedesc1[1],&operation,sizeof(operation));
  write(pipedesc1[1],&sp1,sizeof(sp1));
  write(pipedesc4[1],&SP,sizeof(SP));
  write(pipedesc1[1],&operation,sizeof(operation));
  write(pipedesc1[1],&sp1,sizeof(sp1));
  write(pipedesc4[1],&PC,sizeof(PC));
  write(pipedesc1[1],&sp2,sizeof(sp2));
  mode=1;
  read(pipedesc2[0],&SP,sizeof(SP));
  PC=1000;
  goto c;
    
}

/* Memory array with 2000 integer spaces 
   0-999 for user code  and 1000-1999 for system code */

int memory[2000];  

int memoryread(int i) // Method to read value from the memory array
{
  return(memory[i]);
}

void memorywrite(int i, int data) 
{/* Method to write the value into the memory array*/
  memory[i]=data;
}

void initialread(char filename[20]) 
{/* Method to intialize the values of the mmeory array*/
  // Initialisation of the variables used in this method
  char a[50000],c[1000][50],*p,d[200],*p1,c1[1000][10],jumpdata[10];
  int i=0,length=0,j=0,b=0,linelength=0;
  int count1=0,intdat,wordlength,mp=0,m=0;
  fstream f;

  f.open(filename);
  for(int t=0;t<=200;t++)
    d[t]='\0';

  /* Reading from the file and insertion the instructions and data into the correct locations in
    the memory array*/

  while(!f.eof())
    {
      f.read((char *)&a,sizeof(a));

    }
  
  length=strlen(a);
  p=strtok(a,"\n");
  while(p!=NULL)
    {if(strcmp(p,"\n")==0)
	continue;
      else{
	sprintf(c[i],"%s",p);
	p=strtok(NULL,"\n");
	i++;}
    }
  
  count1=i;
  for(b=0;b<count1;b++)
    {if(c[b][0]!=' ')
      {
	p1=strtok(c[b]," ");
	sprintf(c1[m],"%s",p1);
	m++;
      }
    }
  
  b=0;
  count1=m;
  while(b<count1)
    {
      if(c1[b][0]!='.')
	{
          intdat=atoi(c1[b]);
          memory[b]=intdat;
          b++;
	}
      else if(c1[b][0]=='.')
	{
          wordlength=strlen(c1[b]);
          for(j=1;j<wordlength;j++)
            jumpdata[j-1]=c1[b][j];
	  goto j;

	}
    }
 j:
  mp=atoi(jumpdata);
  b++;
  while(b<count1)
    {
      if(c1[b][0]!='.')
	{
          intdat=atoi(c1[b]);
          memory[mp]=intdat;
          b++;
	  mp++;
	}
      else if(c1[b][0]=='.')
	{
          wordlength=strlen(c1[b]);
          for(j=1;j<wordlength;j++)
            jumpdata[j-1]=c1[b][j];
	  goto j;
	}
    }

  

}

void memoryprocess(char filename[20]) 
{/* method containing the code for memory process*/
  int i=0,value,wadd,wdata,operation;
  initialread(filename);  // method to initialize the memory array
  
  int sp1=-9999,sp2=-19999;
  int sysp=1999;
  int usrp=999;
  int syspos=-18888,usrpos=-8888;
 r:         /*Part of the memory process code for reading from the memory array*/
  read(pipedesc1[0],&i,sizeof(i));
  if(i!=2001)
    {if(i!=-3000)
	{
	  if(i==syspos)
	    {value=sysp;
	      goto q;
	    }
	  if(i==usrpos)
	    {value=usrp;
	      goto q;
	    }

	  if(i==sp1)
	    {
	      if(usrp==999)
		i=usrp;
	      else
		i=++usrp;
	    }
	  if(i==sp2)
	    {
	      if(sysp==1999)
		i=sysp;
	      else
		i=++sysp;
	    }
	    
	  value=memoryread(i); // Obtaining the value at memory location i
	q:
	  write(pipedesc2[1],&value,sizeof(value));
	  goto r;
	}
      else
	{
	  goto w;
	}
    }
  else
    _exit(0);
 w:  /* Part of the memory process code for writing into the memory array */
  read(pipedesc1[0],&wadd,sizeof(wadd));
  read(pipedesc4[0],&wdata,sizeof(wdata));
  if(wadd==sp1)
    {
      wadd=usrp--;
    }
  if(wadd==sp2)
    {
      wadd=sysp--;
    }
  memorywrite(wadd,wdata); /* Calling the method to write into the memory array*/
  goto r;
}
int main(int argc,char *argv[]) // main function of the program
{
  // Initialisation of the variables used in main function
  char filename[20];
  int N;

  // Storing the command line argments in local variables

  strcpy(filename,argv[1]);
  N=atoi(argv[2]);
  pid_t processid;

  /* Creation of the pipes and indication of error incase of error in creation of pipes*/

  if( pipe(pipedesc1)==-1)
    cout<<endl<<"pipe1 error";
  if(pipe(pipedesc2)==-1)
    cout<<endl<<"pipe2 error";
  if(pipe(pipedesc3)==-1)
    cout<<endl<<"pipe3 error";
  if(pipe(pipedesc4)==-1)
    cout<<endl<<"pipe4 error";

  /*Creation of parent process ( CPU process ) and child process 
    using fork() */
  /* Directing the two process towards their respective individual tasks*/
  processid=fork();
  switch(processid) 
    {
    case -1:
      {
        cout<<endl<<"Forking error"; /* Indicates the a failure in forking process */
        break;
      }
    case 0:  //Child process
      { 
        memoryprocess(filename); /* Calls the method containing the child process code */
        break;

      }
    default: //Parent process
      {
        
        cpuprocess(N);// Calls the method containing the parent process code
        break;

      }
    }
  return 0;// Indication of normal termination of the program
}
