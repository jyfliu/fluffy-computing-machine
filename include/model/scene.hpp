#pragma once

#include <model/object.hpp>
#include <utils/glm.hpp>

#include <string>
#include <vector>
#include <memory>


namespace fcm {

class Scene {
  // std string for testing purposes
  std::string _name;
  std::vector<std::unique_ptr<Object>> _objects;
public:
  Scene(std::string name): _name{std::move(name)} {}
  const std::string &name() const {return _name;}

  void insert(std::unique_ptr<Object> obj) { _objects.emplace_back(std::move(obj)); }
  const std::vector<std::unique_ptr<Object>> &objects() const { return _objects; }
};

}