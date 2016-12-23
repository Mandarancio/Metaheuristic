function srate(res)
  x = res(:,3);
  y = res(:,8);
  xx = [];
  yy = [];
  sy = [];
  lerr = [];
  uerr = [];
  c = x(1);
  t=0;
  cc = 0;
  for i=1:rows(x)
    
    if (x(i)!=c)     
      xx(end+1)=c;
      yy(end+1)=t/cc;
      t=0;
      cc=0;
      c=x(i);
    endif
    if (y(i)<=-1356.48)
      t ++;
    endif
    cc ++;
  endfor
  
  xx(end+1)=c;
  yy(end+1)=t/cc;
  
  h=plot(xx,yy,'o-');
  hold on;
  
  legend('success rate');

  xlabel('n_evals');
  ylabel('success rate');
  #xlim([min(xx),max(xx)]);
  set(h, 'MarkerSize', 6, 'MarkerFaceColor', [.3 1 .3],'MarkerEdgeColor', [0 .5 0]);
endfunction