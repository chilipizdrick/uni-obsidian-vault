use glam::{Quat, Vec3};
use glium::{
    BackfaceCullingMode, Depth, DrawParameters, Frame, IndexBuffer, Program, Surface, VertexBuffer,
    uniform,
};

use crate::{
    app::App,
    types::{Color, Pos},
    utils::{model_transform, projection_transform, view_transform},
};

const POSITIONS: [Pos; 7] = [
    Pos::new(1.0, 0.0, 0.0),
    Pos::new(0.5, 0.866, 0.0),
    Pos::new(-0.5, 0.866, 0.0),
    Pos::new(-1.0, 0.0, 0.0),
    Pos::new(-0.5, -0.866, 0.0),
    Pos::new(0.5, -0.866, 0.0),
    Pos::new(0.0, 0.0, 5.0),
];

const COLORS: [Color; 7] = [
    Color::RED,
    Color::YELLOW,
    Color::GREEN,
    Color::CYAN,
    Color::BLUE,
    Color::MAGENTA,
    Color::WHITE,
];

const INDICES: [u16; 30] = [
    4, 2, 0, 2, 1, 0, 4, 3, 2, 0, 5, 4, 1, 6, 0, 2, 6, 1, 3, 6, 2, 4, 6, 3, 5, 6, 4, 0, 6, 5,
];

const CAMERA_POSITION: Vec3 = Vec3::new(6.666, -6.666, 6.666);

pub fn draw_scene2(app: &App, frame: &mut Frame) {
    frame.clear_color_srgb_and_depth((0.3, 0.3, 0.3, 1.0), 1.0);

    let program = Program::from_source(
        &app.display,
        include_str!("./scene2_vert.glsl"),
        include_str!("./scene2_frag.glsl"),
        Some(include_str!("./scene2_geom.glsl")),
    )
    .unwrap();

    let positions_buf = VertexBuffer::new(&app.display, &POSITIONS).unwrap();

    let colors_buf = VertexBuffer::new(&app.display, &COLORS).unwrap();

    let indices = IndexBuffer::new(
        &app.display,
        glium::index::PrimitiveType::TrianglesList,
        &INDICES,
    )
    .unwrap();

    let draw_parameters = DrawParameters {
        depth: Depth {
            test: glium::DepthTest::IfLess,
            write: true,
            ..Default::default()
        },
        backface_culling: BackfaceCullingMode::CullClockwise,
        ..Default::default()
    };

    let model_transform = model_transform(Vec3::splat(1.0), Vec3::ZERO, Quat::IDENTITY);
    let view_transform = view_transform(CAMERA_POSITION, Vec3::ZERO, Vec3::Z);

    let light_direction = light_position_on_ellipse(app.time);

    let dimensions = app.window.inner_size();
    let aspect_ratio = dimensions.width as f32 / dimensions.height as f32;
    let projection_transform =
        projection_transform(std::f32::consts::PI / 3.0, aspect_ratio, 0.1, 100.0);

    let uniforms = uniform! {
        model: model_transform.to_cols_array_2d(),
        view: view_transform.to_cols_array_2d(),
        projection: projection_transform.to_cols_array_2d(),
        light_direction: light_direction.to_array(),
    };

    frame
        .draw(
            (&positions_buf, &colors_buf),
            &indices,
            &program,
            &uniforms,
            &draw_parameters,
        )
        .unwrap();
}

fn light_position_on_ellipse(t: f32) -> Vec3 {
    let u = Vec3::new(12.0, 12.0, 0.0);
    let v = Vec3::new(0.0, 7.0, 7.0);
    let c = Vec3::new(6.666, -6.666, 6.666);
    c + t.cos() * u + t.sin() * v
}
