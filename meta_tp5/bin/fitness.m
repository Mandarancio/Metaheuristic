## Copyright (C) 2016 Martino Ferrari
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} fitness (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Martino Ferrari <martino@martino-desktop>
## Created: 2016-11-27
function [f]=fitness(t0,t1,imgs,labels)
  t = ones(rows(imgs),1);
  t (:,end+1:end+25)= sigmd(imgs*t0);
  #t = sigmd(imgs*t0);
  t = sigmd(t*t1);
  f = sum(power(labels-t,2))/rows(imgs)
  #f = norm(labels-t)^2/rows(imgs)
endfunction

