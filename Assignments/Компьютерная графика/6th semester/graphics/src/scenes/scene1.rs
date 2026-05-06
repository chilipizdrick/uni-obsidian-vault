use glam::{Quat, Vec3};
use glium::{Frame, IndexBuffer, Program, Surface, VertexBuffer, uniform};

use crate::{
    app::App,
    types::{Color, Normal, Pos},
    utils::{model_transform, projection_transform, view_transform},
};

const CAMERA_POSITION: Vec3 = Vec3::new(20.0, 20.0, 20.0);
const LIGHT_DIRECTION: Vec3 = Vec3::new(1.0, 1.0, 1.0);

const POSITIONS: [Pos; 6] = [
    Pos::new(1.0, 0.0, 0.0),
    Pos::new(0.5, 0.866, 0.0),
    Pos::new(-0.5, 0.866, 0.0),
    Pos::new(-1.0, 0.0, 0.0),
    Pos::new(-0.5, -0.866, 0.0),
    Pos::new(0.5, -0.866, 0.0),
];

const NORMALS: [Normal; 6] = [
    Normal::new(0.0, 0.0, 1.0),
    Normal::new(0.0, 0.0, 1.0),
    Normal::new(0.0, 0.0, 1.0),
    Normal::new(0.0, 0.0, 1.0),
    Normal::new(0.0, 0.0, 1.0),
    Normal::new(0.0, 0.0, 1.0),
];

const COLORS: [Color; 6] = [
    Color::RED,
    Color::YELLOW,
    Color::GREEN,
    Color::CYAN,
    Color::BLUE,
    Color::MAGENTA,
];

const INDICES: [u16; 12] = [0, 2, 4, 0, 1, 2, 2, 3, 4, 4, 5, 0];

pub fn draw_scene1(app: &App, frame: &mut Frame) {
    frame.clear_color_srgb(0.3, 0.3, 0.3, 1.0);

    let program = Program::from_source(
        &app.display,
        include_str!("./scene1_vert.glsl"),
        include_str!("./scene1_frag.glsl"),
        None,
    )
    .unwrap();

    let positions = VertexBuffer::new(&app.display, &POSITIONS).unwrap();
    let normals = VertexBuffer::new(&app.display, &NORMALS).unwrap();
    let colors = VertexBuffer::new(&app.display, &COLORS).unwrap();

    let indices = IndexBuffer::new(
        &app.display,
        glium::index::PrimitiveType::TrianglesList,
        &INDICES,
    )
    .unwrap();

    let draw_parameters = Default::default();

    let rotation = Quat::from_rotation_x(app.time);
    let model_transform = model_transform(Vec3::splat(10.0), Vec3::ZERO, rotation);
    // let model_transform = model_transform(Vec3::splat(10.0), Vec3::ZERO, Quat::IDENTITY);

    let view_transform = view_transform(CAMERA_POSITION, Vec3::ZERO, Vec3::Z);

    let dimensions = app.window.inner_size();
    let aspect_ratio = dimensions.width as f32 / dimensions.height as f32;
    let projection_transform =
        projection_transform(std::f32::consts::PI / 3.0, aspect_ratio, 0.1, 100.0);

    let uniforms = uniform! {
        model: model_transform.to_cols_array_2d(),
        view: view_transform.to_cols_array_2d(),
        projection: projection_transform.to_cols_array_2d(),
        light_direction: LIGHT_DIRECTION.to_array(),
    };

    frame
        .draw(
            (&positions, &normals, &colors),
            &indices,
            &program,
            &uniforms,
            &draw_parameters,
        )
        .unwrap();
}
