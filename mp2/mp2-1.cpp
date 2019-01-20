#include <iostream>
#include "Image.h"

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale2x.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");

  std::cout << "Using Image::scale to create `scale3.65x.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(3.65);
  alma.writeToFile("scale3.65x.png");

  std::cout << "Using Image::scale to create `scale600x200.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(600, 200);
  alma.writeToFile("scale600x200.png");

  std::cout << "Using Image::scale to create `scale1200x1200.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(1200, 1200);
  alma.writeToFile("scale1200x1200.png");

  std::cout << "Using Image::scale to create `scale1500x1200.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(1500, 1200);
  alma.writeToFile("scale1500x1200.png");

  std::cout << "Using Image::scale to create `scale1799x1200.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(1799, 1200);
  alma.writeToFile("scale1799x1200.png");

  return 0;
}
