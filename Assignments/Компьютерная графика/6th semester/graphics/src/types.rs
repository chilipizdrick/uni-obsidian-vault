use glium::{implement_uniform_block, implement_vertex, uniforms::AsUniformValue};

#[derive(Debug, Clone, Copy)]
pub struct Pos {
    pub position: [f32; 3],
}

implement_vertex!(Pos, position);

impl Pos {
    pub const fn new(x: f32, y: f32, z: f32) -> Self {
        Self {
            position: [x, y, z],
        }
    }
}

#[derive(Debug, Clone, Copy)]
pub struct Normal {
    pub normal: [f32; 3],
}

implement_vertex!(Normal, normal);

impl Normal {
    pub const fn new(x: f32, y: f32, z: f32) -> Self {
        Self { normal: [x, y, z] }
    }
}

#[derive(Debug, Clone, Copy)]
pub struct Color {
    pub color: [f32; 4],
}

implement_vertex!(Color, color);

#[allow(unused)]
impl Color {
    pub const fn new(r: f32, g: f32, b: f32, a: f32) -> Self {
        Self {
            color: [r, g, b, a],
        }
    }

    pub const RED: Self = Self::new(1.0, 0.0, 0.0, 1.0);
    pub const GREEN: Self = Self::new(0.0, 1.0, 0.0, 1.0);
    pub const BLUE: Self = Self::new(0.0, 0.0, 1.0, 1.0);
    pub const YELLOW: Self = Self::new(1.0, 1.0, 0.0, 1.0);
    pub const MAGENTA: Self = Self::new(1.0, 0.0, 1.0, 1.0);
    pub const CYAN: Self = Self::new(0.0, 1.0, 1.0, 1.0);
    pub const WHITE: Self = Self::new(1.0, 1.0, 1.0, 1.0);
    pub const BLACK: Self = Self::new(0.0, 0.0, 0.0, 1.0);
}

#[derive(Debug, Clone, Copy)]
pub struct TexCoord {
    pub tex_coords: [f32; 2],
}

implement_vertex!(TexCoord, tex_coords);

impl TexCoord {
    pub const fn new(x: f32, y: f32) -> Self {
        Self { tex_coords: [x, y] }
    }
}
