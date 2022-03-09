#ifndef _vobo_math_h_
#define _vobo_math_h_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace vobo {

uint numberDigits(double number, int precision=6);

std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix);
std::ostream& operator<<(std::ostream& os, const glm::vec4& vector);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vector);

}  // namespace vobo
#endif  //_vobo_math_h_ header