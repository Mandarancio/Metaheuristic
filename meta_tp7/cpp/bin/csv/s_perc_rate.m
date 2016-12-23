function s_perc_rate(res,perc,kk='g')
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
  best = -1356.5;
  for i=1:rows(x)
    
    if (x(i)!=c)     
      xx(end+1)=c;
      yy(end+1)=t/cc;
      t=0;
      cc=0;
      c=x(i);
    endif
    if (abs((y(i)-best)/y(i))<=perc)
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
  ylabel('% rate');
  #xlim([min(xx),max(xx)]);
  set(h, 'MarkerSize', 6, 'MarkerFaceColor', kk,'MarkerEdgeColor', [0 .5 0]);
endfunction