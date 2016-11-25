function [y]= sigm(x)
  y=zeros(rows(x),columns(x));
  for i=1:rows(x)
    for j=1:columns(y)
      y(i,j)=1./(1+exp(-x(i,j)));
    endfor
  endfor
endfunction

function [tag] = NN(img)
  tag = sigm(sigm(sigm(img)*teta0)*teta1);
endfunction

NN(psn,X(1,:))