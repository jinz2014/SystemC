close;
load('D:\Sc_lib\sc1\msvc60\examples\fft_fxpt\result.mat');
t=linspace(0,4,16);
y1=exp(-(1+j)*t);
subplot(2,2,1);
stem(t,abs(y1),'b');
title('Data in T domain');
y2=(result(1:16)+i*result(17:32));
hold on;
plot(t,abs(ifft(y2)),'r');
xlabel('t(s)');ylabel('abs(exp(-(1+i)*t)');
legend('orignal','IFFT after FP FFT');
subplot(2,2,2);
stem(linspace(-1,1,16),fftshift(abs(fft(y1))),'rv');
title('Data in fre. domain');
hold on ;
plot(linspace(-1,1,16),fftshift(abs(y2)),'b');
xlabel('*pi');ylabel('FFT(y)');
legend('FP','DB');
subplot(2,2,3);
stem(t,(abs(y1)-abs(ifft(y2))).^2);
title('Diff. in T domain');
xlabel('t(s)');ylabel('Pow. of err');
subplot(2,2,4);
stem(linspace(-1,1,16),(fftshift(abs(fft(y1)))-fftshift(abs(y2))).^2);
title('Diff. in fre. domain');
xlabel('*pi');ylabel('Pow. of err');