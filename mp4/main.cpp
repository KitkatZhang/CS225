
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;       png.readFromFile("tests/i.png");
  FloodFilledImage image(png);
  DFS dfs(png, Point(40, 40), 0.05);
  BFS bfs(png, Point(100, 5), 0.05);
  DFS dfs1(png, Point(5, 100), 0.05);
  BFS bfs1(png, Point(200, 125), 0.05);
  MyColorPicker my(20);
  RainbowColorPicker rainbow(0.05);
  HSLAPixel a1 = HSLAPixel(11,0.8,0.5);
  HSLAPixel a2 = HSLAPixel(230,0.8,0.2);
  GridColorPicker grid(a1, a2, 20);
  GridColorPicker grid1(a2, a1, 20);
  image.addFloodFill( dfs, my );
  image.addFloodFill( bfs, rainbow );
  image.addFloodFill( dfs1, grid);
  image.addFloodFill( bfs1, grid1);
  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
