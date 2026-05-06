use std::time::Instant;

use glium::{
    Display, Texture2d,
    glutin::surface::WindowSurface,
    texture::RawImage2d,
    winit::{
        application::ApplicationHandler,
        dpi::PhysicalSize,
        event::{KeyEvent, WindowEvent},
        event_loop::{self, ActiveEventLoop},
        keyboard::{Key, NamedKey},
        window::{Window, WindowId},
    },
};
use image::GenericImageView;

use crate::scenes::{
    scene1::draw_scene1, scene2::draw_scene2, scene3::draw_scene3, scene4::draw_scene4,
};

pub struct App {
    pub window: Window,
    pub display: Display<WindowSurface>,
    pub time: f32,
    pub texture: Texture2d,
    scene: Scene,
    last_update: Instant,
}

enum Scene {
    Scene1,
    Scene2,
    Scene3,
    Scene4,
}

impl ApplicationHandler for App {
    fn resumed(&mut self, _event_loop: &event_loop::ActiveEventLoop) {}

    fn window_event(
        &mut self,
        event_loop: &ActiveEventLoop,
        _window_id: WindowId,
        event: WindowEvent,
    ) {
        use glium::winit::event::WindowEvent as WE;

        let now = Instant::now();
        self.time += (now - self.last_update).as_secs_f32();
        self.last_update = now;

        match event {
            WE::CloseRequested => event_loop.exit(),
            WE::RedrawRequested => self.draw(),
            WE::KeyboardInput { event, .. } => self.handle_keyboard_input(event),
            WE::Resized(size) => self.handle_window_resize(size),
            _ => {}
        }

        self.window.request_redraw();
    }
}

impl App {
    pub fn new(window: Window, display: Display<WindowSurface>) -> Self {
        let image = load_texture_image();
        let texture = Texture2d::new(&display, image).unwrap();
        Self {
            window,
            display,
            scene: Scene::Scene1,
            time: 0.0,
            texture,
            last_update: Instant::now(),
        }
    }

    fn handle_keyboard_input(&mut self, event: KeyEvent) {
        match event.logical_key {
            Key::Character(char) => match char.as_str() {
                "1" => self.scene = Scene::Scene1,
                "2" => self.scene = Scene::Scene2,
                "3" => self.scene = Scene::Scene3,
                "4" => self.scene = Scene::Scene4,
                _ => {}
            },
            Key::Named(NamedKey::Space) => self.time = 0.0,
            _ => {}
        }
    }

    fn handle_window_resize(&mut self, size: PhysicalSize<u32>) {
        self.display.resize(size.into());
    }

    fn draw(&self) {
        let mut frame = self.display.draw();

        match self.scene {
            Scene::Scene1 => draw_scene1(self, &mut frame),
            Scene::Scene2 => draw_scene2(self, &mut frame),
            Scene::Scene3 => draw_scene3(self, &mut frame),
            Scene::Scene4 => draw_scene4(self, &mut frame),
        };

        frame.finish().unwrap();
    }
}

fn load_texture_image() -> RawImage2d<'static, u8> {
    let image = image::load_from_memory_with_format(
        include_bytes!("../assets/bricks.png"),
        image::ImageFormat::Png,
    )
    .unwrap();

    RawImage2d::from_raw_rgba(image.as_bytes().to_vec(), image.dimensions())
}
