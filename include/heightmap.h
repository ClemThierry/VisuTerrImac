#ifndef __HEIGHT_MAP_H__
#define __HEIGHT_MAP_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class HeightMap {
  int wi;
  int hi;
  const unsigned char *data;
  glm::vec2 world_to_map;
  float height_norm;
  float hOffset;

  float get_pixel(int x, int y);

  public:
    HeightMap(glm::vec2 world_size, const unsigned char *data, int data_w, int data_h, int data_max, float hMin, float hMax);
    float get_height(glm::vec2 pos);

    HeightMap() = default;
};

#endif