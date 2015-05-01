//#define fx_db sc_int<16>
//#define DOUBLE_FFT
#ifdef DOUBLE_FFT
  #define fx_db double  
#else 
  #define fx_db sc_int<16>  
  #undef DOUBLE_FFT
#endif 
#define  SFT 8
