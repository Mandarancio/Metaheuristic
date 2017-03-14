function analyze(x,y,xlab,ylab, leg)
  xx = [];
  yy = [];
  sy = [];
  lerr = [];
  uerr = [];
  c = x(1);
  t=[];
  for i=1:rows(x)
    
    if (x(i)!=c)     
      xx(end+1)=c;
      yy(end+1)=mean(t);
      sy(end+1)= std(t);
      uerr(end+1) = abs(max(t) - mean(t));
      lerr(end+1) = abs(min(t)-mean(t));
      t=[];
      c=x(i);
    endif
    
    t(end+1) = y(i);
  endfor
  
  xx(end+1)=c;
  yy(end+1)=mean(t);
  sy(end+1)= std(t);
  uerr(end+1) = abs(max(t) - mean(t));
  lerr(end+1) = abs(min(t)-mean(t));
  
  h=plot(xx,yy,'o-');
  set(h, 'MarkerSize', 6, 'MarkerFaceColor', [.3 1 .3],'MarkerEdgeColor', [0 .5 0]);

  hold on;
  h=plot(xx,yy-lerr,'ro:');
  set(h, 'MarkerSize', 6, 'MarkerFaceColor', [1 .3 .3],'MarkerEdgeColor', [0 .5 0]);
  h=plot(xx,yy+lerr,'go:');
  set(h, 'MarkerSize', 6, 'MarkerFaceColor', [.3 .3 1],'MarkerEdgeColor', [0 .5 0]);
  
  title(leg);
  legend('mean','min value','max value');

  xlabel(xlab);
  ylabel(ylab);
  xlim([min(xx),max(xx)]);

 endfunction
  