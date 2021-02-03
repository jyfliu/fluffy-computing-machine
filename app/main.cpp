#include <iostream>
#include <memory>
#include <random>

#include <chrono>
#include <thread>

#include <physics/physics.hpp>
#include <render/render.hpp>
#include <utils/glew.hpp>
#include <utils/glfw.hpp>

#include <model/object.hpp>
#include <model/scene.hpp>

int main(void) {
  std::cout << "Hello there\n";

  std::cout << "Initializing physics...\n";
  fcm::init_physics();
  std::cout << "Initializing renderer...\n";
  auto window = fcm::init_renderer();

  if (window.get() == nullptr) {
    std::cerr << "Render initialization failed\n";
  }

  fcm::Scene scene{"Scene 1"};

  // temporarily do this stuff here
  auto s1 = std::make_unique<fcm::Sphere>();
  s1->name = "s1";
  s1->radius = 1;
  s1->mass = 1;
  s1->moment_of_inertia = 1;
  s1->mat = fcm::STEEL;
  s1->position = {-2, 0, 0};
  s1->velocity = {4, 0, 0};

  auto s2 = std::make_unique<fcm::Sphere>();
  s2->name = "s2";
  s2->radius = 2;
  s2->mass = 1;
  s2->moment_of_inertia = 4;
  s2->mat = fcm::STEEL;
  s2->position = {7, 3, 0};
  s2->velocity = {-4, -2, 0};

  auto s3 = std::make_unique<fcm::Sphere>();
  s3->name = "s3";
  s3->radius = 1;
  s3->mass = 10;
  s3->moment_of_inertia = 10;
  s3->mat = fcm::STEEL;
  s3->position = {-2.5, 3.5, 0};
  s3->velocity = {3, -3, 0};

  auto s4 = std::make_unique<fcm::Sphere>();
  s4->name = "s4";
  s4->radius = 3;
  s4->mass = 2;
  s4->moment_of_inertia = 18;
  s4->mat = fcm::STEEL;
  s4->position = {4, -5, 0};
  s4->velocity = {0, 4, 0};

  // scene.insert(std::move(s1));
  // scene.insert(std::move(s2));
  // scene.insert(std::move(s3));
  // scene.insert(std::move(s4));

  for (int i = 0; i < 25; ++i) {
    auto s = std::make_unique<fcm::Sphere>();
    s->name = std::string("s") + std::to_string(i);
    s->radius = 1 + std::rand() % 3 / 3. * 0.2;
    s->mass = std::rand() % 2 + 1;
    s->moment_of_inertia = s->mass * s->radius * s->radius;
    s->mat = fcm::STEEL;
    s->position = {(i % 5) * 2.5 - 5, (i / 5) * 2.5 - 5, 0};
    s->velocity = {std::rand() % 13 - 6, std::rand() % 13 - 6, 0};
    scene.insert(std::move(s));
  }

  // main loop
  auto prev = std::chrono::high_resolution_clock::now();
  do {
    auto now = std::chrono::high_resolution_clock::now();
    double dt = std::chrono::duration<double>(now - prev).count();
    prev = now;
    fcm::update(scene, dt); // TODO time steps
    fcm::render(scene, window.get());

  } while (glfw::glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS and
           glfw::glfwWindowShouldClose(window.get()) == 0);

  fcm::destroy_renderer(std::move(window));

  std::cout << "Goodbye\n";

  return 0;
}
