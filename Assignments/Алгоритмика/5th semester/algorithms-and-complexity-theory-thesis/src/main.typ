#import "lib.typ": *

#show: template.with()
#counter(page).update(3)

#outline()

#state("pagebreak-h1").update(true)

#include "./parts/task.typ"

#show heading: set heading(numbering: "1.")
#show heading.where(level: 1): set heading(numbering: "Глава 1.")

#include "./parts/theory.typ"
#include "./parts/results.typ"

#show heading: set heading(numbering: none)

#include "./parts/conclusion.typ"

#bibliography("./common/bibliography.bib")

#include "./parts/appendix.typ"
