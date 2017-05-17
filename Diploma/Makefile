TEX = cover/*.tex main/*.tex util/*.tex Diploma.tex bib/*.tex bib/*.bib #pics/*.tikz
AUX = cover/*.aux main/*.aux util/*.aux bib/*.aux Diploma.bbl Diploma.aux Diploma.toc Diploma.blg *.fls Diploma.fdb_latexmk Diploma.log Diploma.out Diploma.toc

Diploma.pdf: $(TEX) bsustyle/bsureport.cls
	latexmk -xelatex -pdf Diploma.tex #&& open Diploma.pdf

clean:
	rm -f Diploma.pdf $(AUX)
