all: fsim.pdf gsim4.pdf e14.pdf


e14.pdf : e14.tex
	platex e14.tex && platex e14.tex && pdvips -o e14.ps e14.dvi  && dvipdf e14.dvi

gsim4.pdf : gsim4.tex
	platex gsim4.tex && platex gsim4.tex && pdvips -o gsim4.ps gsim4.dvi  && dvipdf gsim4.dvi

fsim.pdf : fsim.tex
	platex fsim.tex && platex fsim.tex && pdvips -o fsim.ps fsim.dvi  && dvipdf fsim.dvi 

clean:
	rm *.log *.aux *.dvi *.pdf *.ps

