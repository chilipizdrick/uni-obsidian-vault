use gauss_jordan_elimination::*;
use plotlib::page::Page;
use plotlib::repr::Plot;
use plotlib::style::{LineStyle, PointMarker, PointStyle};
use plotlib::view::ContinuousView;

pub fn task_5() {
    #![allow(clippy::approx_constant)]

    let x_i = [0.1, 0.5, 0.9, 1.3, 1.7, 2.1];
    let y_i = [-2.3026, -0.69315, -0.10536, 0.26236, 0.53063, 0.74194];

    let x_star = 0.8;

    let polynomial = least_squares_method(&x_i, &y_i, 1);
    println!(
        "МНК 1-ой степени, x: {}: {}",
        x_star,
        calc_polynom(&polynomial, x_star)
    );
    let polynomial = least_squares_method(&x_i, &y_i, 2);
    println!(
        "МНК 2-ой степени, x: {}: {}",
        x_star,
        calc_polynom(&polynomial, x_star)
    );
    let polynomial = least_squares_method(&x_i, &y_i, 3);
    println!(
        "МНК 3-ой степени, x: {}: {}",
        x_star,
        calc_polynom(&polynomial, x_star)
    );

    let s1 = sum_of_sq_dev(&x_i, &y_i, 1);
    println!("Сумма квадратов отклонения для МНК 1-ой степени: {s1}");
    let s2 = sum_of_sq_dev(&x_i, &y_i, 2);
    println!("Сумма квадратов отклонения для МНК 2-ой степени: {s2}");
    let s3 = sum_of_sq_dev(&x_i, &y_i, 3);
    println!("Сумма квадратов отклонения для МНК 3-ей степени: {s3}");

    plot(&x_i, &y_i, f64::ln, x_star);
}

fn least_squares_method(xs: &[f64], ys: &[f64], n: usize) -> Vec<f64> {
    #![allow(clippy::needless_range_loop)]

    let mut matrix = vec![vec![0.0; n + 2]; n + 1];

    for k in 0..=n {
        for i in 0..=n {
            matrix[k][i] = xs.iter().map(|&x| x.powi((k + i) as i32)).sum();
        }
        matrix[k][n + 1] = xs
            .iter()
            .zip(ys.iter())
            .map(|(&x, &y)| y * x.powi(k as i32))
            .sum();
    }

    gauss_jordan_elimination_generic(&mut matrix);

    matrix.iter().map(|row| row[n + 1]).collect()
}

fn sum_of_sq_dev(xs: &[f64], ys: &[f64], n: usize) -> f64 {
    let poly = least_squares_method(xs, ys, n);
    xs.iter()
        .zip(ys.iter())
        .map(|(&x, &y)| (calc_polynom(&poly, x) - y).powi(2))
        .sum()
}

fn calc_polynom(coeff: &[f64], x: f64) -> f64 {
    coeff
        .iter()
        .enumerate()
        .map(|(i, &c)| c * x.powi(i as i32))
        .sum()
}

fn plot(xs: &[f64], ys: &[f64], f: fn(f64) -> f64, x_star: f64) {
    let (x_min, x_max) = xs
        .iter()
        .fold((f64::INFINITY, f64::NEG_INFINITY), |(mn, mx), x| {
            (mn.min(*x), mx.max(*x))
        });

    let margin = (x_max - x_min) * 0.2;
    let x_start = 0.01;
    let x_end = x_max + margin;

    let steps: usize = 1000;
    let dx = (x_end - x_start) / steps as f64;
    let xss: Vec<f64> = (0..=steps).map(|i| x_start + i as f64 * dx).collect();

    let data_original = xss.iter().map(|&x| (x, f(x))).collect();
    let plot_original = Plot::new(data_original)
        .line_style(LineStyle::new().colour("black").width(2.0))
        .legend("ln(x)".to_string());

    let experimental_points = xs.iter().copied().zip(ys.iter().copied()).collect();
    let plot_points = Plot::new(experimental_points).point_style(
        PointStyle::new()
            .marker(PointMarker::Square)
            .colour("black"),
    );

    let mut view = ContinuousView::new()
        .add(plot_original)
        .add(plot_points)
        .x_label("x")
        .y_label("y");

    for (mut degree, color) in ["red", "green", "blue"]
        .iter()
        .map(|x| x.to_string())
        .enumerate()
    {
        degree += 1;
        let poly = least_squares_method(xs, ys, degree);
        let data_lsm: Vec<(f64, f64)> = xss.iter().map(|&x| (x, calc_polynom(&poly, x))).collect();

        let plot_lsm = Plot::new(data_lsm)
            .line_style(LineStyle::new().colour(color).width(2.0))
            .legend(format!("МНК {} степени", degree).to_string());

        let x_stared = Plot::new(vec![(x_star, calc_polynom(&poly, x_star))]).point_style(
            PointStyle::new()
                .colour("red")
                .size(4.0)
                .marker(PointMarker::Square),
        );

        view = view.add(plot_lsm);
        view = view.add(x_stared);
    }

    Page::single(&view).save("task_5.svg").unwrap();
    println!("График сохранён в task_5.svg");
}
