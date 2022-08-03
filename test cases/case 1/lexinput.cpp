/* This program is the VQ's codec processes. */
/*You must train the super codebook well before execute the codec process. */
/* This prog. has been modified for data hiding based on VQ codebook proj.*/
/* First, this prog. will output the VQ index file.*/

/* The following two steps are belong to another prog.*/
/* Second, these indexes are sequently embedded into codewords of VQ codebook.*/
/* Finally, decompress the image based on the indexes hiding in the codebook.*/
/* Modified 2005/6/29*/
/* Further modified 2007/12/11 for reversible secret image trans.*/
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
//<============
#define len 512L   
//<============

FILE *bookfile,*testfile,*outfile,*indexfile;
int row,col,codewordindex;
unsigned codebook[booksize][blockwidth][blocklen],
	 current[blockwidth][blocklen];

int vqindex[16384];
// 512*512/4/4=16384

double PSNRtmp1=0.0,PSNRtmp2=0.0,PSNR,mins;

/* Distortion calculation */
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
/* return back the distortion to main procedure */
}

/* Encoding */
int encoder(unsigned int training[blockwidth][blocklen])   
{
  int bookindex,i;
  double tmp;
  mins=MAXFLOAT;        
/* Is MAXFLOAT A CONSTANT ?? */
  for (i=0;i<booksize;i++)
  {
    tmp=dist(training,codebook[i]);      
/* training[4][4] , codebook[32][4][4] */
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
/* Return value */
}
void getblock(int row,int col,unsigned buffer[blockwidth][blocklen],
	      FILE *getfile)
{
unsigned char input[blocklen];
unsigned long filepos1,filepos2;
int x,y;

  filepos1=len*row+col;    
/*  len == 512L , width = 512L , why " L " ?? */
  for (x=0;x<blockwidth;x++)   
/*  offset length , because image size = 512 X 512 */
  {
    filepos2=filepos1+len*x;
    fseek(getfile,filepos2,SEEK_SET);    
/* Adjust file position */
    fread(input,sizeof(char),blocklen,getfile); 
/* Read data from file position  */
      for (y=0;y<blocklen;y++)
	buffer[x][y]=(unsigned)input[y];
  }
}

void codebook_input(FILE *infile,unsigned book[][blockwidth][blockwidth],
		    int size)
{
  int inputindex1,inputindex2,inputindex3;
  unsigned char tempinput[blocklen]; 
/* tempinput[16] is used as a 16 char buffer */

  for (inputindex1=0;inputindex1<size;inputindex1++)
    for (inputindex2=0;inputindex2<blockwidth;inputindex2++)
    {
      fread(tempinput,sizeof(char),blocklen,infile);
      for (inputindex3=0;inputindex3<blocklen;inputindex3++)
	book[inputindex1][inputindex2][inputindex3]=(unsigned)tempinput[inputindex3];
    }
}

/* Write the decoded vector to a file */

void writeout(unsigned vector[blockwidth][blocklen],int row,int col,
	      FILE *outfile)
{
  unsigned long filepos1,filepos2;
  unsigned char out[blocklen];
  int i,j;
  filepos1=len*row+col;         
/* The pos. of upper_left pixel of current input vector */
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
/* bnum is the total number of blocks */
clock_t Start,End;   
/* clock_t can be defined by time.h */
clrscr();
row=col=0;
/* The bookfile is a codebook file which is the output of the trainsup.cpp pro.*/
/* CODEBOOK file */
if ((bookfile=fopen("d:\\cccj\\working\\VQBOOK1024_44_1_airplane","r+b"))==NULL)
{
  cout << "Codebook file open error !!";
  getche();
  exit(1);
}
if ((testfile=fopen("d:\\cccj\\working\\512x512\\gold","r+b"))==NULL) 
// <=====================
{
  cout << "Test file open error !!";
  getche();
  exit(1);
}
/* output the decoded image */
if ((outfile=fopen("d:\\cccj\\working\\exp1\\vqgold256_44_1","w+b"))==NULL) 
// <=================
{
  cout << "Output file open error !!";
  getche();
  exit(1);
}
/* VQ index file*/
if ((indexfile=fopen("d:\\cccj\\working\\exp1\\idxpeppers512_44_1","w+b"))==NULL) 
// <==============
{
  cout << "Index file open error !!";
  getche();
  exit(1);
}
codebook_input(bookfile,codebook,booksize); 
/* codebook is pointed by bookfile */
Start=clock();
bnum=0;
while (row < width)  
/* width = 512L */
  {

    getblock(row,col,current,testfile);   
/* current[4][4] will save the current input vector */
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
/* ( row , col ) is adjusted to ( row , col + 4 ) */
    if (col>=len)      
/* If col >= 512L then the first row of blocks of the input image is read . */
    {
      row+=blockwidth; 
/* Adjust to next row of input vectors */
      cout << "Row=" << row << "\n";
      col=0;
    }
  }

/*Write VQ index file. */
  for(i=0;i<4096;i++)
  {
    fprintf(indexfile,"%d\n",vqindex[i]) ;
  }
  for(i=0;i<4096;i++)
  {
    cout << vqindex[i]<< "\n" ;
  }
/*Compute the PSNR value. */
/*The PSNR value is ok. */
/*Check by cccj 2004/2/11*/
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
