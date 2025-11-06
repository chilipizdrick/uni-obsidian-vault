use std::f64::consts::PI;

use plotlib::page::Page;
use plotlib::repr::Plot;
use plotlib::style::{LineStyle, PointMarker, PointStyle};
use plotlib::view::ContinuousView;

pub fn task_3() {
    let x_i = vec![0.0, PI / 6.0, PI / 3.0, PI / 2.0];
    let y_i: Vec<f64> = x_i.iter().map(|&x| x * x.sin()).collect();
    let points: Vec<(f64, f64)> = x_i.into_iter().zip(y_i).collect();
    let f = |x: f64| x * x.sin();
    let x_new = PI / 4.0;

    let y_new = f(x_new);
    println!("Значение оригинальной функции f(x) = x * sin(x) в точке x = pi/4:         {y_new}");
    let y_new = lagrange_approx_poly(&points, x_new);
    println!("Интерполированное значение в точке x = pi/4 при помощи полинома Лагранжа: {y_new}");
    let y_new = newton_approx_poly(&points, x_new);
    println!("Интерполированное значение в точке x = pi/4 при помощи полинома Ньютона:  {y_new}");

    plot(&points, f);
}

fn lagrange_approx_poly(points: &[(f64, f64)], point: f64) -> f64 {
    let mut res = 0.0;
    for (i, (xi, yi)) in points.iter().enumerate() {
        let mut l_i = 1.0;
        for (j, (xj, _)) in points.iter().enumerate() {
            if i != j {
                l_i *= (point - *xj) / (*xi - *xj);
            }
        }
        res += yi * l_i;
    }
    res
}

fn newton_table(points: &[(f64, f64)]) -> Vec<f64> {
    let n = points.len();
    let mut coef = vec![0.0; n];
    let mut div: Vec<f64> = points.iter().map(|p| p.1).collect();
    coef[0] = div[0];
    for j in 1..n {
        for i in 0..(n - j) {
            div[i] = (div[i + 1] - div[i]) / (points[i + j].0 - points[i].0);
        }
        coef[j] = div[0];
    }
    coef
}

fn newton_approx_poly(points: &[(f64, f64)], point: f64) -> f64 {
    let coeffs = newton_table(points);
    let mut res = 0.0;
    for k in (0..coeffs.len()).rev() {
        res = res * (point - points[k.min(points.len() - 1)].0) + coeffs[k];
    }
    res
}

fn plot(points: &[(f64, f64)], original: fn(f64) -> f64) {
    let (x_min, x_max) = points
        .iter()
        .fold((f64::INFINITY, f64::NEG_INFINITY), |(mn, mx), (x, _)| {
            (mn.min(*x), mx.max(*x))
        });

    let margin = PI / 6.0;
    let x_start = x_min - margin;
    let x_end = x_max + margin;

    let steps: usize = 1000;
    let delta_x = (x_end - x_start) / steps as f64;
    let xs: Vec<f64> = (0..=steps).map(|i| x_start + i as f64 * delta_x).collect();

    let data_original: Vec<(f64, f64)> = xs.iter().map(|&x| (x, original(x))).collect();

    let data_lagrange: Vec<(f64, f64)> = xs
        .iter()
        .map(|&x| (x, lagrange_approx_poly(points, x)))
        .collect();

    let data_newton: Vec<(f64, f64)> = xs
        .iter()
        .map(|&x| (x, newton_approx_poly(points, x)))
        .collect();

    let plot_original = Plot::new(data_original)
        .line_style(LineStyle::new().colour("black").width(2.0))
        .legend("Ориг. функция".to_string());

    let point_table = Plot::new(points.into()).point_style(
        PointStyle::new()
            .colour("black")
            .marker(PointMarker::Square),
    );

    let plot_lagrange = Plot::new(data_lagrange)
        .line_style(LineStyle::new().colour("red").width(2.0))
        .legend("Прибл. многоч. Лагранжа".to_string());

    let plot_newton = Plot::new(data_newton)
        .line_style(LineStyle::new().colour("blue").width(4.0))
        .legend("Прибл. многоч. Ньютона".to_string());

    let view = ContinuousView::new()
        .add(point_table)
        .add(plot_original)
        .add(plot_newton)
        .add(plot_lagrange)
        .x_label("x")
        .y_label("y");

    Page::single(&view).save("task_3.svg").unwrap();
    println!("График сохранён в task_3.svg");
}
