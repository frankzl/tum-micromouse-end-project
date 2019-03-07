# How to use?

If you're using a linux distribution or macOS, there should be a program called `pdflatex` and `bibtex`

# Initial Run
1. `pdflatex scifile.tex`
2. `bibtex scifile`
3. `pdflatex scifile.tex`


After that, whenever you update any `.tex` file, rerun `pdflatex scifile.tex` and if you update the `scibib.bib`, rerun `bibtex scifile`.

