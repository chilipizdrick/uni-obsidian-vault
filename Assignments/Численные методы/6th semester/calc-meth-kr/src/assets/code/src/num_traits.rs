pub trait Zero {
    const ZERO: Self;

    fn is_zero(&self) -> bool;
}

impl Zero for f64 {
    const ZERO: Self = 0.0;

    #[inline]
    fn is_zero(&self) -> bool {
        self.abs() < f64::EPSILON
    }
}

impl Zero for f32 {
    const ZERO: Self = 0.0;

    #[inline]
    fn is_zero(&self) -> bool {
        self.abs() < f32::EPSILON
    }
}

pub trait One {
    const ONE: Self;

    fn is_one(&self) -> bool;
}

impl One for f64 {
    const ONE: Self = 1.0;

    fn is_one(&self) -> bool {
        self.abs() < 1.0 + f64::EPSILON
    }
}

impl One for f32 {
    const ONE: Self = 1.0;

    fn is_one(&self) -> bool {
        self.abs() < 1.0 + f32::EPSILON
    }
}
