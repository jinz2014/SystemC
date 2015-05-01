/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sink.cpp - This is the implementation file for the synchronous process
             "sink".

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "systemc.h"
#include "sink.h"
#include <stdio.h>
#include <string.h> /* For strcmp() */
#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS */
#include "mat.h"
#include "math.h"
#include "D:\Sc_lib\sc1\msvc60\examples\fft_fxpt\globals.h"
void sink::entry()
{
 sc_int<16> tmp;
 int tmp_out;
 int incr=0;
 fp_real = fopen("out_real","w");
 fp_imag = fopen("out_imag","w");

 data_ack.write(false);

 while(true)
 { 
   wait_until(data_ready.delayed() == true);
   tmp = in_real.read();
   tmp_out = tmp;
   data[incr]=tmp_out/pow(2,SFT);
   fprintf(fp_real,"%d  \n",tmp_out);
   tmp = in_imag.read();
   tmp_out = tmp;
   data[incr+DL]=tmp_out/pow(2,SFT);
   fprintf(fp_imag,"%d  \n",tmp_out);
   data_ack.write(true);
   wait_until(data_ready.delayed() == false);
   data_ack.write(false); 
   if(++incr==16) GenMat();
 }
}
////////////////////////////////////////////////////////
/*
 * MAT-file creation program
 *
 * See the MATLAB API Guide for compiling information.
 *
 * Calling syntax:
 *
 *   matcreat
 *
 * Create a MAT-file which can be loaded into MATLAB.
 *
 * This program demonstrates the use of the following functions:
 *
 *  matClose
 *  matGetVariable
 *  matOpen
 *  matPutVariable
 *  matPutVariableAsGlobal
 *
 * Copyright 1984-2000 The MathWorks, Inc.
 * $Revision: 1.9 $
 */
#define BUFSIZE 256

int sink::GenMat() {
  MATFile *pmat;
  mxArray *pa;
  const char *file = "result.mat";
  int status; 

  printf("Creating file %s...\n\n", file);
  pmat = matOpen(file, "w");
  if (pmat == NULL) {
    printf("Error creating file %s\n", file);
    printf("(Do you have write permission in this directory?)\n");
    return(EXIT_FAILURE);
  }

  pa = mxCreateDoubleMatrix(1,DL*2,mxREAL);
  if (pa == NULL) {
      printf("%s : Out of memory on line %d\n", __FILE__,
              __LINE__); 
      printf("Unable to create mxArray.\n");
      return(EXIT_FAILURE);
  }
  
  memcpy((void *)(mxGetPr(pa)), (void *)data, sizeof(data));    
  

  status = matPutVariable(pmat, "result", pa);
  if (status != 0) {
      printf("%s :  Error using matPutVariable on line %d\n",
              __FILE__, __LINE__);
      return(EXIT_FAILURE);
  } 
  /* Clean up. */
  mxDestroyArray(pa);  
  if (matClose(pmat) != 0) {    
	  printf("Error closing file %s\n",file);
      return(EXIT_FAILURE);  }
  /* End. */
  printf("Done\n");
  sc_stop();
  return(EXIT_SUCCESS);
}
