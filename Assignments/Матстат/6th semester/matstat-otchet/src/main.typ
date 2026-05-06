#import "lib.typ": *

#show: template.with()

#include-pdf-page("./assets/МС_ТР_Титульный лист.pdf")

#counter(page).update(2)

#outline()

#state("pagebreak-h1").update(true)

// #show heading: set heading(numbering: "1.")
// #show heading.where(level: 1): set heading(numbering: "Глава 1.")

#include "./parts/task.typ"
#include "./parts/theory.typ"
#include "./parts/results.typ"
#bibliography("./common/bibliography.bib")
#include "./parts/appendix.typ"

// #show heading: set heading(numbering: none)

// #include "./parts/conclusion.typ"


