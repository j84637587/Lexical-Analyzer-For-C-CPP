/* This program is the VQ's codec processes. */
/*You must train the super codebook well before execute the codec process. */
/* This prog. has been modified for data hiding based on VQ codebook proj.*/
/* First, this prog. will output the VQ index file.*/
/* The following two steps are belong to another prog.*/
/* Second, these indexes are sequently embedded into codewords of VQ codebook.*/
/* Finally, decompress the image based on the indexes hiding in the codebook.*/
/* Modified 2005/6/29*/
/* Further modified 2007/12/11 for reversible secret image trans.*/
//<============
//<============
// 512*512/4/4=16384
/* Distortion calculation */
/* return back the distortion to main procedure */
/* Encoding */
/* Is MAXFLOAT A CONSTANT ?? */
/* training[4][4] , codebook[32][4][4] */
/* Return value */
/*  len == 512L , width = 512L , why " L " ?? */
/*  offset length , because image size = 512 X 512 */
/* Adjust file position */
/* Read data from file position  */
/* tempinput[16] is used as a 16 char buffer */
/* Write the decoded vector to a file */
/* The pos. of upper_left pixel of current input vector */
/* bnum is the total number of blocks */
/* clock_t can be defined by time.h */
/* The bookfile is a codebook file which is the output of the trainsup.cpp pro.*/
/* CODEBOOK file */
// <=====================
/* output the decoded image */
// <=================
/* VQ index file*/
// <==============
/* codebook is pointed by bookfile */
/* width = 512L */
/* current[4][4] will save the current input vector */
/* ( row , col ) is adjusted to ( row , col + 4 ) */
/* If col >= 512L then the first row of blocks of the input image is read . */
/* Adjust to next row of input vectors */
/*Write VQ index file. */
/*Compute the PSNR value. */
/*The PSNR value is ok. */
/*Check by cccj 2004/2/11*/
