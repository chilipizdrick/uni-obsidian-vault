#import "lib.typ": *

#show: template.with(
  enable-figure-supplements: false,
  enable-figure-numbering: false,
)

#include-pdf-page("./assets/МС_ТР_Титульный лист.pdf")

#counter(page).update(2)

#outline()
#include "./parts/task.typ"
#include "./parts/theory.typ"
#include "./parts/results.typ"
#bibliography("./assets/bibliography.bib")
#include "./parts/appendix.typ"

