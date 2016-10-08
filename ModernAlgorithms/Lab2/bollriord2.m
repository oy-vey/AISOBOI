function ij=bollriord2(ij, m)
for i=1:length(ij)
	a = ij(1,i);
	ij(1,i) = transformation(a, m);
	b = ij(2,i);
	ij(2,i) = transformation(b, m);
end


function z=transformation(e, m)
	x = 0;
    if (mod(e,m) > 0) 
    	x = 1;
    endif
    z = idivide(e,m) + x;