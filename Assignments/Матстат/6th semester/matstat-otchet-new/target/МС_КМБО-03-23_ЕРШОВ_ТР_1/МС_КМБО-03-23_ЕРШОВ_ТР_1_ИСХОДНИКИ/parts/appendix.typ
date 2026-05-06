#show heading.where(level: 2): set heading(outlined: false)
#show heading.where(level: 3): set heading(outlined: false)

= Приложение

#heading(
  level: 2,
  outlined: false,
)[Приложение 1. Код решения задачи 1]

#let code = read("../assets/code/MS_62_1.py")
#raw(code, block: true, lang: "py")

#pagebreak()

#heading(
  level: 2,
  outlined: false,
)[Приложение 2. Код решения задачи 2]

#let code = read("../assets/code/MS_62_2.py")
#raw(code, block: true, lang: "py")

#pagebreak()

#heading(
  level: 2,
  outlined: false,
)[Приложение 3. Код решения задачи 3]

#let code = read("../assets/code/MS_62_3.py")
#raw(code, block: true, lang: "py")

