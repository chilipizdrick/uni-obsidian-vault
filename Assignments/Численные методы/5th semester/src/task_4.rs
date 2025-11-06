use plotlib::{
    page::Page,
    repr::Plot,
    style::{LineStyle, PointMarker, PointStyle},
    view::ContinuousView,
};

pub fn task_4() {
    #![allow(clippy::approx_constant)]

    let x_i = [0.1, 0.5, 0.9, 1.3, 1.7];
    let y_i = [-2.3026, -0.69315, -0.10536, 0.26236, 0.53063];
    let new_x = 0.8;

    println!("Настоящее значение ln(0.8): {}", f64::ln(new_x));

    let coeffs = interpolate(&x_i, &y_i);
    let new_y = eval(&coeffs, new_x);
    println!("Заданный x: {}, интерполированный y: {}", new_x, new_y);

    let x_with_der = x_i[2];
    // let x_1 = eval_second_derivative(&coeffs, x_with_der);
    // println!(
    //     "Значение второй производной в точке x = {}: {}",
    //     x_with_der, x_1
    // );

    let c = &coeffs;

    for j in 2..=3 {
        let t = (x_with_der - c.x[j - 1]) / (c.x[j] - c.x[j - 1]);

        let x_2nd_spline = -2.0 * c.a[j] + 2.0 * c.b[j] - 3.0 * 2.0 * t * c.b[j] - 2.0 * c.a[j]
            + 3.0 * 2.0 * t * c.a[j];
        println!(
            "Значение второй производной в точке x = {} сплайна {}: {}",
            x_with_der, j, x_2nd_spline
        );
    }

    plot(&x_i, &y_i, new_x);
}

#[derive(Debug)]
pub struct Coeffs {
    a: Vec<f64>,
    b: Vec<f64>,
    #[allow(unused)]
    c: Vec<f64>,
    #[allow(unused)]
    d: Vec<f64>,
    k: Vec<f64>,
    x: Vec<f64>,
    y: Vec<f64>,
    n: usize,
}

pub fn interpolate(x: &[f64], y: &[f64]) -> Coeffs {
    let n = x.len() - 1;
    let mut a = vec![0.0; n + 1];
    let mut b = vec![0.0; n + 1];
    let mut c = vec![0.0; n + 1];
    let mut d = vec![0.0; n + 1];
    let mut c_prime = Vec::new();
    let mut d_prime = Vec::new();
    let mut k = Vec::new();

    let diffx1 = x[1] - x[0];
    let diffx2 = x[n] - x[n - 1];
    let diffy1 = y[1] - y[0];
    let diffy2 = y[n] - y[n - 1];

    a[0] = 0.0;
    c[0] = 1.0 / diffx1;
    b[0] = 2.0 * c[0];
    d[0] = 3.0 * diffy1 / (diffx1 * diffx1);

    let computed = (1..n)
        .map(|i| {
            let diffx1 = x[i] - x[i - 1];
            let diffx2 = x[i + 1] - x[i];
            let diffy1 = y[i] - y[i - 1];
            let diffy2 = y[i + 1] - y[i];

            let ai = 1.0 / diffx1;
            let ci = 1.0 / diffx2;
            let bi = 2.0 * (ai + ci);
            let di = 3.0 * (diffy1 / (diffx1 * diffx1) + diffy2 / (diffx2 * diffx2));

            (ai, bi, ci, di)
        })
        .collect::<Vec<_>>();

    for (idx, (ai, bi, ci, di)) in computed.into_iter().enumerate() {
        let i = idx + 1;
        a[i] = ai;
        b[i] = bi;
        c[i] = ci;
        d[i] = di;
    }

    a[n] = 1.0 / diffx2;
    b[n] = 2.0 * a[n];
    c[n] = 0.0;
    d[n] = 3.0 * diffy2 / (diffx2 * diffx2);

    c_prime.resize(n, 0.0);
    d_prime.resize(n + 1, 0.0);

    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for i in 1..n {
        c_prime[i] = c[i] / (b[i] - a[i] * c_prime[i - 1]);
        d_prime[i] = (d[i] - a[i] * d_prime[i - 1]) / (b[i] - a[i] * c_prime[i - 1]);
    }

    d_prime[n] = (d[n] - a[n] * d_prime[n - 1]) / (b[n] - a[n] * c_prime[n - 1]);

    k.resize(n + 1, 0.0);

    k[n] = d_prime[n];
    for i in (0..n).rev() {
        k[i] = d_prime[i] - c_prime[i] * k[i + 1];
    }
    let computed = (1..=n)
        .map(|i| {
            let diffx1 = x[i] - x[i - 1];
            let diffy1 = y[i] - y[i - 1];

            let ai = k[i - 1] * diffx1 - diffy1;
            let bi = -k[i] * diffx1 + diffy1;

            (ai, bi)
        })
        .collect::<Vec<_>>();

    for (idx, (ai, bi)) in computed.into_iter().enumerate() {
        let i = idx + 1;
        a[i] = ai;
        b[i] = bi;
    }

    Coeffs {
        a,
        b,
        c,
        d,
        k,
        x: x.to_vec(),
        y: y.to_vec(),
        n,
    }
}

pub fn eval(c: &Coeffs, new_x: f64) -> f64 {
    if new_x < c.x[0] || new_x > c.x[c.n] {
        if new_x < c.x[0] {
            c.k[0] * (new_x - c.x[0]) + c.y[0]
        } else {
            c.k[c.n] * (new_x - c.x[c.n]) + c.y[c.n]
        }
    } else {
        let mut j: usize = 1;
        while new_x > c.x[j] && j < c.n {
            j += 1;
        }

        let t = (new_x - c.x[j - 1]) / (c.x[j] - c.x[j - 1]);

        (1.0 - t) * c.y[j - 1] + t * c.y[j] + t * (1.0 - t) * (c.a[j] * (1.0 - t) + c.b[j] * t)
    }
}

pub fn eval_derivative(c: &Coeffs, new_x: f64) -> f64 {
    if new_x < c.x[0] || new_x > c.x[c.n] {
        if new_x < c.x[0] { c.k[0] } else { c.k[c.n] }
    } else {
        let mut j: usize = 1;
        while new_x > c.x[j] && j < c.n {
            j += 1;
        }

        let t = (new_x - c.x[j - 1]) / (c.x[j] - c.x[j - 1]);

        -c.y[j - 1] + c.y[j] + c.a[j] - 2.0 * t * c.a[j] + 2.0 * t * c.b[j]
            - 3.0 * t * t * c.b[j]
            - 2.0 * t * c.a[j]
            + 3.0 * t * t * c.a[j]
    }
}

pub fn eval_second_derivative(c: &Coeffs, new_x: f64) -> f64 {
    if new_x < c.x[0] || new_x > c.x[c.n] {
        0.0
    } else {
        let mut j: usize = 1;
        while new_x > c.x[j] && j < c.n {
            j += 1;
        }

        let t = (new_x - c.x[j - 1]) / (c.x[j] - c.x[j - 1]);

        -2.0 * c.a[j] + 2.0 * c.b[j] - 3.0 * 2.0 * t * c.b[j] - 2.0 * c.a[j]
            + 3.0 * 2.0 * t * c.a[j]
    }
}

pub fn plot(xs: &[f64], ys: &[f64], x_star: f64) {
    let coeffs = interpolate(xs, ys);

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

    let x_stared = Plot::new(vec![(x_star, eval(&coeffs, x_star))]).point_style(
        PointStyle::new()
            .colour("red")
            .size(4.0)
            .marker(PointMarker::Square),
    );

    let points = Plot::new(xs.iter().copied().zip(ys.iter().copied()).collect()).point_style(
        PointStyle::new()
            .colour("#505050")
            .size(4.0)
            .marker(PointMarker::Square),
    );

    let mut view = ContinuousView::new().x_label("x").y_label("y");

    let data: Vec<(f64, f64)> = xss.iter().map(|&x| (x, eval(&coeffs, x))).collect();

    let plot_original = Plot::new(data)
        .line_style(LineStyle::new().colour("red").width(2.0))
        .legend("Сплайн".to_string());

    let ln_plot = Plot::new(xss.iter().map(|&x| (x, f64::ln(x))).collect())
        .line_style(LineStyle::new().colour("black").width(2.0))
        .legend("ln(x)".to_string());

    let x_stared_ln = Plot::new(vec![(x_star, f64::ln(x_star))]).point_style(
        PointStyle::new()
            .colour("red")
            .size(4.0)
            .marker(PointMarker::Square),
    );

    view = view
        .add(ln_plot)
        .add(plot_original)
        .add(points)
        .add(x_stared_ln)
        .add(x_stared);

    Page::single(&view).save("task_4.svg").unwrap();
    println!("График сохранён в task_4.svg");
}
