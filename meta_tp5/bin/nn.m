clear;

load 'X.data';
load 'Y.data';
load 'save.mat';

imgs = ones(200,1);
imgs(:,end+1:end+400)=X;
labels = Y;


f= fitness(teta0,teta1,imgs,labels)


##{
N = 10;
bf = 1.0;
landscape=[];
fmean = 0;
for i=1:N
  t0 = rand(401,25)*10-5;
  t1  = rand(26,1)*10-5;
  f = fitness(t0,t1,imgs,labels);
  landscape(end+1)=f;
  fmean +=f;
  if (f<bf)
    bf=f;
  endif
endfor

fmean/=N;
display("mean: ");
display(fmean);
display("best: ");
display(bf);
display("sigma: ");
display(std(landscape));

plot(landscape);
legend('f(NN)');
xlabel('iterations');
ylabel('fitness');
title('Landscape');

figure();

hist(landscape,20);
title('Landscape Distribution');
legend('hist(f(NN))');
xlabel('fitness');
ylabel('occurecies');
%x=(t0*imgs')';
%size(x)
##}