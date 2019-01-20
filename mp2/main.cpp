#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base;
  base.readFromFile("base.png");
  base.lighten(1);
  Image sticker1, sticker2, sticker3, sticker4, sticker5, sticker6, sticker7;
  sticker1.readFromFile("sticker1.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");
  sticker4.readFromFile("sticker4.png");
  sticker5.readFromFile("sticker5.png");
  sticker6.readFromFile("sticker6.png");
  sticker7.readFromFile("sticker7.png");

  sticker1.scale(120, 120);
  sticker2.scale(300, 300);
  sticker3.scale(300, 300);
  sticker4.scale(300, 300);
  sticker5.scale(300, 300);
  sticker6.scale(300, 300);
  sticker7.scale(300, 300);

  StickerSheet skt(base, 7);
  skt.addSticker(sticker2, 50, 50);
  skt.addSticker(sticker4, 500, 50);
  skt.addSticker(sticker3, 850, 50);
  skt.addSticker(sticker5, 50, 450);
  skt.addSticker(sticker7, 450, 450);
  skt.addSticker(sticker6, 850, 450);
  skt.addSticker(sticker1, 1080, 0);

  Image out = skt.render();
  out.writeToFile("myImage.png");


  return 0;
}
