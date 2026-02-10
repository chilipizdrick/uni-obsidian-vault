#import "lib.typ": *

#set page(margin: 0cm)
#image("./parts/titul.pdf", width: 100%, height: 100%)

#show: template.with()
#counter(page).update(2)

#show table.cell: set align(horizon + center)

#set page(
  "a4",
  numbering: (..nums) => {
    let string = nums.pos().at(0)
    align(right)[#string]
  },
  header: align(
    right,
  )[_Ершов Алексей Геннадьевич КМБО-03-23. Вариант 5_],
)

#for i in range(1, 10) {
  counter("task").update(i)

  if i != 1 {
    pagebreak()
  }

  counter(math.equation).update(0)

  heading(level: 1, "Задача " + str(i))

  include "parts/" + str(i) + ".typ"
}
