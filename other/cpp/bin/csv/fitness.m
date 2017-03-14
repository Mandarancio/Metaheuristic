function [z] = fitness(x,y)
  n = columns(x);
  m = columns(y);
  z =zeros(n,m);
  for i=1:n 
    xi = x(i);
    for j=1:m
      yi = y(j);
      z(i,j)=-abs(xi/2*sin(sqrt(xi)))-abs(yi*sin(30*sqrt(x/y)));
    endfor
  endfor 
endfunction