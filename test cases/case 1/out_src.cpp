
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <values.h>
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <alloc.h>
#define TOL 0.001
#define booksize 1024
#define blocklen 4
#define blockwidth 4
#define width 512L 
#define len 512L   

FILE *bookfile,*testfile,*outfile,*indexfile;
int row,col,codewordindex;
unsigned codebook[booksize][blockwidth][blocklen],
	 current[blockwidth][blocklen];

int vqindex[16384];

double PSNRtmp1=0.0,PSNRtmp2=0.0,PSNR,mins;

double dist(unsigned int x[blockwidth][blocklen],   
	   unsigned int y[blockwidth][blocklen])
{
  int index1,index2,t;
  double buf;
  buf=0.0;
  for (index1=0;index1<blockwidth;index1++)
    for (index2=0;index2<blocklen;index2++)
    {
      t=x[index1][index2]-y[index1][index2];
      buf+=pow(t,2);
    }
  return (buf);                                      
}

int encoder(unsigned int training[blockwidth][blocklen])   
{
  int bookindex,i;
  double tmp;
  mins=MAXFLOAT;        
  for (i=0;i<booksize;i++)
  {
    tmp=dist(training,codebook[i]);      
    if (tmp < 0.0)
    {
      cout << "error!";
      exit(1);
    }
    if (tmp<mins)
    {
      bookindex=i;
      mins=tmp;
    }
  }
  return (bookindex);       
}
void getblock(int row,int col,unsigned buffer[blockwidth][blocklen],
	      FILE *getfile)
{
unsigned char input[blocklen];
unsigned long filepos1,filepos2;
int x,y;

  filepos1=len*row+col;    
  for (x=0;x<blockwidth;x++)   
  {
    filepos2=filepos1+len*x;
    fseek(getfile,filepos2,SEEK_SET);    
    fread(input,sizeof(char),blocklen,getfile); 
      for (y=0;y<blocklen;y++)
	buffer[x][y]=(unsigned)input[y];
  }
}

void codebook_input(FILE *infile,unsigned book[][blockwidth][blockwidth],
		    int size)
{
  int inputindex1,inputindex2,inputindex3;
  unsigned char tempinput[blocklen]; 

  for (inputindex1=0;inputindex1<size;inputindex1++)
    for (inputindex2=0;inputindex2<blockwidth;inputindex2++)
    {
      fread(tempinput,sizeof(char),blocklen,infile);
      for (inputindex3=0;inputindex3<blocklen;inputindex3++)
	book[inputindex1][inputindex2][inputindex3]=(unsigned)tempinput[inputindex3];
    }
}


void writeout(unsigned vector[blockwidth][blocklen],int row,int col,
	      FILE *outfile)
{
  unsigned long filepos1,filepos2;
  unsigned char out[blocklen];
  int i,j;
  filepos1=len*row+col;         
  for (i=0;i<blockwidth;i++)
  {
    filepos2=filepos1+len*i;
    for (j=0;j<blocklen;j++)
      out[j]=(unsigned char) vector[i][j];
    fseek(outfile,filepos2,SEEK_SET);
    fwrite(out,sizeof(char),blocklen,outfile);
  }
}

main()
{
int x,y,i,temp,bnum;   
clock_t Start,End;   
clrscr();
row=col=0;
if ((bookfile=fopen("d:\\cccj\\working\\VQBOOK1024_44_1_airplane","r+b"))==NULL)
{
  cout << "Codebook file open error !!";
  getche();
  exit(1);
}
if ((testfile=fopen("d:\\cccj\\working\\512x512\\gold","r+b"))==NULL) 
{
  cout << "Test file open error !!";
  getche();
  exit(1);
}
if ((outfile=fopen("d:\\cccj\\working\\exp1\\vqgold256_44_1","w+b"))==NULL) 
{
  cout << "Output file open error !!";
  getche();
  exit(1);
}
if ((indexfile=fopen("d:\\cccj\\working\\exp1\\idxpeppers512_44_1","w+b"))==NULL) 
{
  cout << "Index file open error !!";
  getche();
  exit(1);
}
codebook_input(bookfile,codebook,booksize); 
Start=clock();
bnum=0;
while (row < width)  
  {

    getblock(row,col,current,testfile);   
    codewordindex=encoder(current);
    vqindex[bnum]=codewordindex;
    bnum++;
    writeout(codebook[codewordindex],row,col,outfile);
    for (x=0;x<blockwidth;x++)
      for (y=0;y<blocklen;y++)
      {
	temp=codebook[codewordindex][x][y]-current[x][y];
	PSNRtmp2+=pow(temp,2);
      }
    col+=blocklen;     
    if (col>=len)      
    {
      row+=blockwidth; 
      cout << "Row=" << row << "\n";
      col=0;
    }
  }

  for(i=0;i<4096;i++)
  {
    fprintf(indexfile,"%d\n",vqindex[i]) ;
  }
  for(i=0;i<4096;i++)
  {
    cout << vqindex[i]<< "\n" ;
  }
  PSNRtmp1=pow(255,2);
  PSNRtmp2=PSNRtmp2/262144.0;
  PSNR=10.0*log10(PSNRtmp1/PSNRtmp2);
  cout << "blocknum= " << bnum << "\n";
  cout << "\nThe PSNR is : " << PSNR;
  End=clock();
  cout << "\n The time == " << (End-Start)/(CLK_TCK*60);

  fclose(bookfile);
  fclose(testfile);
  fclose(outfile);
  fclose(indexfile);
  getche();
  return 0;
}
