function ij=bollriord(n)


ij = [1; 1];
degs = [2];

for i=2:n
  ij = [ij [i; 0]];
  degs = [degs 1];
  probabilities(degs, i);
  x = sum(rand >= cumsum(probabilities(degs, i))) + 1;
  degs(1,x)+= 1;
  ij(2,i) = x;
end


function probs=probabilities(degs, len)
	probs = ones(1,len);
	n = len;
	div = 2 * n - 1;

	for i=1:n
		probs(1,i) = degs(1,i)/div;
	end