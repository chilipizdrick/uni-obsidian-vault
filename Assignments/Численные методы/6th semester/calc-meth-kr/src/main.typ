#import "lib.typ": *

#show: template.with()

// #include-pdf-page("./assets/title.pdf")

#counter(page).update(2)

#outline()

#include "./parts/task.typ"
#include "./parts/subtasks.typ"
#include "./parts/results.typ"
#include "./parts/conclusion.typ"

#bibliography("./assets/bibliography.bib")

#include "./parts/appendix.typ"

