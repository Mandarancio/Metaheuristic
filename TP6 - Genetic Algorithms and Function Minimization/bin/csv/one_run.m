function one_run(res)
  it = rows(res);
  x=1:it;
  w=1;
  y= res(:,8);
  plot(x,y,'r:+',"linewidth", w);
  hold on;
  [counts,bins] = hist(y,20);
  barh(bins,counts,'w')
  m = mean(y);
  s = std(y);
  plot([1,it],[m,m],'g-',"linewidth", w);
  plot([1,it],[m-s,m-s],'b:',"linewidth", w);
  plot([1,it],[m+s,m+s],'b:',"linewidth", w);
  
  xlabel('iterations');
  ylabel('fitness');
  legend('Fitness','Distribution','Mean','STD')
  xlim([1,it]);
  set(gca, "linewidth", w, "fontsize", 12) 
endfunction