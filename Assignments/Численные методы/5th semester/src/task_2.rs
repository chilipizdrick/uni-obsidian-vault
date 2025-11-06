pub fn task_2() {
    #![allow(clippy::approx_constant)]

    let y_i = [-0.20136, 0.0, 0.20136, 0.41152, 0.64350];
    let dx = 0.2;

    println!("Значения y: {:?}", y_i);

    let der_1 = (y_i[2] - y_i[1]) / dx;
    println!("Первая левая производная: {der_1}",);

    let der_2 = (y_i[3] - y_i[2]) / dx;
    println!("Первая правая производная: {der_2}",);

    let der_3 = (y_i[3] - y_i[1]) / (2.0 * dx);
    println!("Первая центральная производная: {der_3}",);

    let der_4 = (y_i[3] - 2.0 * y_i[2] + y_i[1]) / (dx * dx);
    println!("Вторая центральная производная: {der_4}",);
}
