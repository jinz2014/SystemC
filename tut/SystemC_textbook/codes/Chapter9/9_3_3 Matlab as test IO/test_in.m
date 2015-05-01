close;
t=linspace(0,4,16);
y1=exp(-(1+j)*t);
y=[real(y1),imag(y1)];
save('D:\Sc_lib\sc1\msvc60\examples\fft_fxpt\test.mat','y');
subplot(2,2,1);
stem(t,abs(y1),'b');
title('Data in T domain');
