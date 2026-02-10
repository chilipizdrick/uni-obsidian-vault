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
    margin: (top: 2cm, bottom: 1.5cm, left: 1cm, right: 1cm),
    numbering: "1",
    number-align: center + bottom,
    header: footnote_reset(),
  )

  set par(
    justify: true,
    linebreaks: "optimized",
    first-line-indent: (amount: 2.5em, all: true),
    leading: 1em,
    spacing: 1.5em,
  )

  show heading: set heading(numbering: none)
  show heading: it => {
    set align(center)
    set block(above: 1.5em, below: 1em)

    if it.level == 1 {
      set text(font: font-type, size: heading1-font-size)
    } else if it.level == 2 {
      set text(font: font-type, size: heading2-font-size)
    } else {
      set text(font: font-type, size: font-size)
    }

    it
  }

  // Reset figure counters on new level 1 heading
  show heading.where(level: 1): it => {
    let kinds = query(figure).map(fig => fig.kind).dedup()
    for kind in kinds {
      counter(figure.where(kind: kind)).update(0)
    }
    counter("definition").update(0)
    it
  }

  set enum(indent: 2.5em)
  set list(indent: 2.5em)

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
    numbering: num => {
      let count = context counter("task").get().at(0)
      "(" + count + "." + str(num) + ")"
    },
    supplement: [Уравнение],
  )

  set figure(numbering: num => {
    let part_cnt = context counter(heading.where(level: 1)).get().at(0)
    [#part_cnt.#num]
  })


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

  // Set outline style
  show outline: set outline(indent: 1.5em, depth: 3, title: "Содержание")
  // show outline.entry: set outline.entry(fill: none)

  // Add a page break before all headings of level 1 except the first one
  state("pagebreak-h1").update(false)
  show heading: it => {
    if it.level == 1 and state("pagebreak-h1").get() {
      pagebreak()
    }
    it
  }

  // Set bibliography style
  show bibliography: set bibliography(
    title: "Список литературы",
    full: true,
    // style: "./csl/bib-style.csl",
  )

  body
}

#let definition(body) = {
  let part_cnt = context counter(heading.where(level: 1)).get().at(0)
  let def_cnt = context counter("definition").get().at(0)
  context counter("definition").step()
  [*Определение #part_cnt.#def_cnt.* #body]
}

#let ma = math.upright("M")
#let di = math.upright("D")
#let cov = math.upright("cov")
