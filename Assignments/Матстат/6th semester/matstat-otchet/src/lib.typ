#import "@preview/unify:0.7.1": *
#import "@preview/codly:1.3.0": *
#import "@preview/physica:0.9.5": *

#let template(
  font-type: "Times New Roman",
  font-size: 14pt,
  heading1-font-size: 16pt,
  heading2-font-size: 14pt,
  link-color: blue,
  body,
) = {
  set text(
    font: font-type,
    lang: "ru",
    size: font-size,
    fallback: true,
    hyphenate: false,
  )

  let footnote_reset() = {
    counter(footnote).update(0)
  }

  set page(
    margin: (top: 2cm, bottom: 2cm, left: 3cm, right: 1.5cm),
    numbering: "1",
    number-align: right + bottom,
    header: footnote_reset(),
  )

  set par(
    justify: true,
    linebreaks: "optimized",
    first-line-indent: (amount: 1.25em, all: true),
    leading: 1.5em,
    spacing: 1.5em,
  )

  show table: set par(leading: 0.5em, spacing: 1em)
  set table(align: center + horizon)

  show heading: set heading(numbering: none)
  show heading: set align(center)
  show heading: set block(above: 2em, below: 2em)

  show heading.where(level: 1): it => {
    set text(size: heading1-font-size)

    pagebreak(weak: true)

    it
  }

  show heading.where(level: 2): it => {
    set text(size: heading2-font-size)

    it
  }

  set enum(indent: 1.5cm)
  set list(indent: 1.5cm)

  set ref(supplement: it => {
    if it.func() == figure {}
  })

  show: codly-init.with()
  codly(
    number-format: none,
    zebra-fill: rgb("#f7f7f7"),
    stroke: 1pt + gray,
    lang-format: none,
    smart-indent: true,
  )

  show raw.where(block: true): set par(first-line-indent: 0em)
  show raw: set text(size: 10pt, font: "JetBrains Mono NL")

  set math.equation(
    numbering: num => [(#num)],
    supplement: [Уравнение],
  )

  set figure(numbering: num => [#num])

  show figure: align.with(center)
  set figure.caption(separator: [ --- ])
  show figure: set block(breakable: false)

  show figure.where(kind: image): set figure(supplement: [Рисунок])
  show figure.where(kind: image): set figure.caption(position: bottom)

  show figure.where(kind: table): set figure(supplement: [Таблица])
  show figure.where(kind: table): set figure.caption(position: top)

  show figure.where(kind: raw): set figure(supplement: [Код])
  show figure.where(kind: raw): set figure.caption(position: bottom)

  // Set footnotes to be denoted with asterisks
  set footnote(numbering: it => {
    "*" * counter(footnote).get().at(0)
  })

  // Set citation style
  set cite(style: "gost-r-705-2008-numeric")

  // Set outline style
  show outline: set outline(indent: 1.5em, depth: 3, title: "Содержание")
  // show outline.entry: set outline.entry(fill: none)

  // Set bibliography style
  show bibliography: set bibliography(
    title: "Список литературы",
    full: true,
    style: "./common/gost-r-7-0-5-2008.csl",
  )

  body
}


#let definition(body) = {
  let part_cnt = context counter(heading.where(level: 1)).get().at(0)
  let def_cnt = context counter("definition").get().at(0)
  context counter("definition").step()
  [*Определение #part_cnt.#def_cnt.* #body]
}

#let include-pdf-page(pdf-path) = {
  page(
    margin: 0pt,
    header: none,
    footer: none,
  )[
    #image(pdf-path, width: 100%, height: 100%)
  ]
}

