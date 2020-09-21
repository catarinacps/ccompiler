(setq org-latex-packages-alist
      '(("cache=false" "minted") ("T1" "fontenc") ("utf8" "inputenx") ("" "placeins")))
(setq org-latex-listings 'minted)
(setq org-latex-minted-options
      '(("breaklines") ("breakafter" "d") ("linenos" "true") ("xleftmargin" "\\parindent")))
(setq org-latex-pdf-process
      '("latexmk -pdflatex='pdflatex -shell-escape -interaction=nonstopmode' -f -pdf -outdir=%o %f"))
